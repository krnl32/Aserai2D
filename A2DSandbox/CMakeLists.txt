file(GLOB_RECURSE A2DSandboxSources
	"${CMAKE_CURRENT_SOURCE_DIR}/A2DSandbox.cpp"
)

if(WIN32)
	add_definitions(-DASERAI2D_PLATFORM_WINDOWS)
endif(WIN32)

add_definitions(-DASERAI2D_DEBUG)

add_executable(${A2DSANDBOX_TARGET_NAME} ${A2DSandboxSources})

target_include_directories(${A2DSANDBOX_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")

target_link_libraries(${A2DSANDBOX_TARGET_NAME} PRIVATE ${A2DENGINE_TARGET_NAME} glm spdlog imgui stb_image)
