cmake_minimum_required(VERSION 3.10)
project(glad)

# 添加 GLAD 源文件
add_library(glad STATIC 
    src/glad.c
)

# 包含目录 - 设置为 PUBLIC 以便主项目也能访问
target_include_directories(glad PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(glad opengl32)
