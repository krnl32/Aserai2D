#include "A2DEngine/Core/Window.h"
#include "A2DEngine/Core/Logger.h"
#include "A2DEngine/Events/WindowEvents.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Aserai2D
{
	static void APIENTRY DebugMessageCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		ASERAI_LOG_ERROR("[OpenGL Error]({}) {}", type, message);
	}

	Window::Window()
		: m_Initialized(false), m_NativeWindow(nullptr)
	{
	}

	bool Window::Init(const WindowProperties& props)
	{
		m_WinPrivData.Name = props.Name;
		m_WinPrivData.Width = props.Width;
		m_WinPrivData.Height = props.Height;
		m_WinPrivData.VSync = props.VSync;
		if (!InitContext()) return false;
		glfwSetWindowUserPointer(m_NativeWindow, &m_WinPrivData);
		return m_Initialized = true;
	}

	void Window::Destroy()
	{
		if (m_Initialized)
		{
			glfwSetErrorCallback(nullptr);
			glfwDestroyWindow(m_NativeWindow);
			glfwTerminate();
			m_Initialized = false;
		}
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_NativeWindow);
	}

	const WindowProperties& Window::GetProperties() const
	{
		return (WindowProperties&)m_WinPrivData;
	}

	void Window::SetProperties(const WindowProperties& props)
	{
		m_WinPrivData.Name = props.Name;
		m_WinPrivData.Width = props.Width;
		m_WinPrivData.Height = props.Height;
		m_WinPrivData.VSync = props.VSync;
	}

	bool Window::IsVSync() const
	{
		return m_WinPrivData.VSync;
	}

	void Window::SetVSync(bool vsync)
	{
		m_WinPrivData.VSync = vsync;
		glfwSwapInterval(m_WinPrivData.VSync ? 1 : 0);
	}

	uint32_t Window::GetWidth() const
	{
		return m_WinPrivData.Width;
	}

	uint32_t Window::GetHeight() const
	{
		return m_WinPrivData.Height;
	}

	void Window::SetupWindowEvents(const std::shared_ptr<EventManager>& eventManager)
	{
		m_WinPrivData.EventManager = eventManager;

		glfwSetWindowCloseCallback(m_NativeWindow, [](GLFWwindow* window)
			{
				WindowPrivateData& data = *(WindowPrivateData*)glfwGetWindowUserPointer(window);
				auto eventManager = data.EventManager;
				eventManager->Emit<WindowCloseEvent>();
			});

		glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowPrivateData& data = *(WindowPrivateData*)glfwGetWindowUserPointer(window);
				auto eventManager = data.EventManager;
				data.Width = width;
				data.Height = height;
				eventManager->Emit<WindowResizeEvent>(width, height);
			});
	}

	bool Window::InitContext()
	{
		if (!glfwInit())
		{
			ASERAI_LOG_ERROR("FAILED glfwInit");
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef ASERAI_ENGINE_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		m_NativeWindow = glfwCreateWindow(m_WinPrivData.Width, m_WinPrivData.Height, m_WinPrivData.Name.c_str(), nullptr, nullptr);
		if (!m_NativeWindow)
		{
			ASERAI_LOG_ERROR("FAILED glfwCreateWindow for {}", m_WinPrivData.Name);
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_NativeWindow);
		glfwSwapInterval(m_WinPrivData.VSync ? 1 : 0);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			ASERAI_LOG_ERROR("FAILED gladLoadGLLoader");
			glfwTerminate();
			return false;
		}

		//glDebugMessageCallback(DebugMessageCallback, nullptr);

		//ASERAI_LOG_INFO("OpenGL: Version({}), Renderer({}), Vendor({}) ", glGetString(GL_VERSION), glGetString(GL_RENDERER), glGetString(GL_VENDOR));

		glfwShowWindow(m_NativeWindow);
		ASERAI_LOG_DEBUG("Initialized Window Context");
		return true;
	}
}
