cmake_minimum_required(VERSION 3.31.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(OpenGLLearn)

# 子项目
add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/stb_image)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)

# exe
add_executable(OpenGLLearn)


target_sources(OpenGLLearn PRIVATE
        src/main.cpp
        src/window_manager.cpp
        src/vao_manager.cpp
        src/shader_manager.cpp
        src/texture_manager.cpp
)

# 头文件
target_include_directories(OpenGLLearn PUBLIC include)

# link 库文件
target_link_libraries(OpenGLLearn glfw)
target_link_libraries(OpenGLLearn glad)
target_link_libraries(OpenGLLearn glm)
target_link_libraries(OpenGLLearn stb_image)
target_link_libraries(OpenGLLearn opengl32.lib)