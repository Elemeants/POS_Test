cmake_minimum_required(VERSION 2.4)

project(Console_POS_System)
include_directories(${PROJECT_SOURCE_DIR})

add_library(decoration decorations.cpp)
add_library(gui gui.cpp)
add_library(inventario inventario.cpp)
add_library(pedido pedido.cpp)
add_library(producto producto.cpp)
add_library(user_manager user_manager.cpp)
add_library(user user.cpp)
add_executable(main main.cpp)
target_link_libraries(main decoration gui inventario pedido producto user_manager user)