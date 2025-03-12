file(GLOB_RECURSE A2DEngineSources
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Assertion.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/DeltaTime.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Engine.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Engine.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Window.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Window.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/EventManager.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/EventManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/UUID.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/UUID.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Logger.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Logger.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Input/InputCodes.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Input/InputManager.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Input/InputManager.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Scene/Scene.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Scene/Scene.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Scene/SceneCamera.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Scene/SceneCamera.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Utils/DateTime.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Utils/DateTime.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Utils/FileIO.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Utils/FileIO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Utils/fnv.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/Asset/Asset.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Asset/Types.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Asset/AssetManager.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Asset/AssetManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Asset/SpritesheetAsset.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Asset/SpritesheetAsset.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Asset/TextureAsset.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Asset/TextureAsset.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/RenderBatch.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Camera.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Renderer2D.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Renderer2D.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Render.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Render.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/FrameBuffer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/FrameBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/IndexBuffer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/IndexBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shader.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Texture2D.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Texture2D.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/VertexArray.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/VertexArray.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/VertexBuffer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/VertexBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/VertexBufferLayout.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/VertexBufferLayout.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/AImGui.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/AImGui.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Editor/EditorCamera.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Editor/EditorCamera.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/ECS/ComponentPool.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ECS/Registry.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ECS/Registry.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ECS/Types.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ECS/Types.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Components/CameraComponent.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Components/KeyboardComponent.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Components/RigidBodyComponent.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Components/SpriteComponent.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Components/TransformComponent.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/Systems/CameraControlSystem.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Systems/CameraControlSystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Systems/KeyboardMovementSystem.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Systems/KeyboardMovementSystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Systems/MovementSystem.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Systems/MovementSystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Systems/RenderSystem.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Systems/RenderSystem.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Events/Event.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Events/CollisionEvent.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Events/WindowEvents.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/Platform/FileDialog.h"
)

if(WIN32)
	file(GLOB_RECURSE A2DEnginePlatformSources
		"${CMAKE_CURRENT_SOURCE_DIR}/Platform/Win32/FileDialogImplWin32.cpp"
	)

	add_definitions(-DASERAI2D_PLATFORM_WINDOWS)
endif(WIN32)

add_definitions(-DASERAI2D_ENGINE)

set(A2DEngineSources ${A2DEngineSources} ${A2DEnginePlatformSources})
add_library(${A2DENGINE_TARGET_NAME} STATIC ${A2DEngineSources})

find_package(OpenGL REQUIRED)

target_include_directories(${A2DENGINE_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_link_libraries(${A2DENGINE_TARGET_NAME} PRIVATE glfw glad glm spdlog imgui stb_image)
