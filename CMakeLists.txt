# Главный конфигурационный файл, в котором указываются общие зависимости

cmake_minimum_required(VERSION 3.26)
project(Chat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление подкаталогов для клиента и сервера
add_subdirectory(src/client)
add_subdirectory(src/server)

add_custom_target(both
        COMMAND start $<TARGET_FILE:Server>
        COMMAND start $<TARGET_FILE:Client>
        DEPENDS Server Client
)
