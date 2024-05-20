# CMakeLists.txt в src/server

project(Server)

add_executable(Server server.cpp)

target_link_libraries(Server PRIVATE ws2_32)
