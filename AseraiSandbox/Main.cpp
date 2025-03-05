#include <iostream>

#include <AseraiEngine/Core/AseraiApp.h>
#include <AseraiEngine/Core/Logger.h>
#include <AseraiEngine/Scene/Scene.h>
#include <AseraiEngine/Utils/AssetManager.h>

#include <AseraiEngine/Components/RigidBodyComponent.h>
#include <AseraiEngine/Components/SpriteComponent.h>

namespace Aserai
{
	class AseraiSandbox : public AseraiApp
	{
	public:
		AseraiSandbox(const WindowProps& windowProps)
			: AseraiApp(windowProps)
		{
			ASERAI_LOG_INFO("Initialized AseraiSandbox");

			m_AssetManager = std::make_shared<AssetManager>();

			m_Renderer2D->SetAlphaBlending(true);
			m_ActiveScene = std::make_shared<Scene>("Sandbox");

			// Simple Entities
			Entity entity1 = m_ActiveScene->CreateEntity();
			entity1.AddComponent<RigidBodyComponent>(glm::vec3({ 0.1, 0.0, 0.0 }));
			entity1.AddComponent<SpriteComponent>(glm::vec4({ 1.0f, 0.0f, 0.0f, 1.0f }), 0, 0, 1);

			Entity entity2 = m_ActiveScene->CreateEntity();
			entity2.AddComponent<RigidBodyComponent>(glm::vec3({ 0.1, 0.0, 0.0 }));
			entity2.AddComponent<SpriteComponent>(glm::vec4({ 0.0f, 1.0f, 0.0f, 1.0f }), 0, 0, 0);

			Entity entity3 = m_ActiveScene->CreateEntity();
			entity3.AddComponent<RigidBodyComponent>(glm::vec3({ 0.0, 0.1, 0.0 }));
			entity3.AddComponent<SpriteComponent>(m_AssetManager->GetTexture("../Assets/Textures/wall_brick.png"));

			Entity entity4 = m_ActiveScene->CreateEntity();
			entity4.AddComponent<RigidBodyComponent>(glm::vec3({ 0.0, -0.1, 0.0 }));
			entity4.AddComponent<SpriteComponent>(m_AssetManager->GetTexture("../Assets/Textures/panther_tank_jlee104.png"), 0, 0, 2);
		}

		virtual void OnProcessInput() override
		{
			if (m_InputManager->IsKeyPressed(KeyCode::Escape))
				Shutdown();
		}

		virtual void OnUpdate(DeltaTime dt) override
		{
			ASERAI_LOG_INFO("FPS: {}", (1000 / (dt * 1000)));

			m_ActiveScene->OnRuntimeUpdate(dt);
		}

		virtual void OnRender(DeltaTime dt, const std::shared_ptr<Renderer2D>& renderer) override
		{
			renderer->ResetRenderStats();
			renderer->SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
			renderer->Clear();

			m_ActiveScene->OnRuntimeRender(dt, renderer);

			/*std::cout << "DrawCall Count: " << renderer->GetRenderStats().DrawCallCount << std::endl;
			std::cout << "Quad Count: " << renderer->GetRenderStats().QuadCount << std::endl;
			std::cout << "Vertex Count: " << renderer->GetRenderStats().GetVertexCount() << std::endl;
			std::cout << "Index Count: " << renderer->GetRenderStats().GetIndexCount() << std::endl;*/
		}

	private:
		std::shared_ptr<AssetManager> m_AssetManager;
		std::shared_ptr<Scene> m_ActiveScene;
	};
}

int main(int argc, char* argv)
{
	Aserai::AseraiSandbox sandbox({ "AseraiSandbox", 640, 480, true });
	sandbox.Run();
	return 0;
}
