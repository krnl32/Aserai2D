file(GLOB_RECURSE A2DEditorSources
	"${CMAKE_CURRENT_SOURCE_DIR}/A2DEditor.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/Panel.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/PanelManager.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/PanelManager.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/ConsolePanel.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/ConsolePanel.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/AssetManagerPanel.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/AssetManagerPanel.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/EntityPropertiesPanel.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/EntityPropertiesPanel.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/SceneGraphPanel.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Panels/SceneGraphPanel.cpp"
)

if(WIN32)
	add_definitions(-DASERAI2D_PLATFORM_WINDOWS)
endif(WIN32)

add_definitions(-DASERAI2D_DEBUG)

add_executable(${A2DEDITOR_TARGET_NAME} ${A2DEditorSources})

target_include_directories(${A2DEDITOR_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")

target_link_libraries(${A2DEDITOR_TARGET_NAME} PRIVATE ${A2DENGINE_TARGET_NAME} glm spdlog imgui stb_image)
