cmake_minimum_required(VERSION 3.10)
project(stb_image)

# 添加 GLAD 源文件
add_library(stb_image STATIC
        include/stb_image.h
        src/stb_image.cpp
)

# 包含目录 - 设置为 PUBLIC 以便主项目也能访问
target_include_directories(stb_image PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

