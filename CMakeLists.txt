cmake_minimum_required(VERSION 3.20)
project(
    unit-circle
    VERSION 1.0.0
    LANGUAGES CXX)

file(GLOB SRC_LIST "src/*.cpp")

find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 imgui::imgui glfw)
include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/headers")
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_SOURCE_DIR}
    COMMENT "Created ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.exe")
