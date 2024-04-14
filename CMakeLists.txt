# Главный конфигурационный файл, в котором указываются общие зависимости

cmake_minimum_required(VERSION 3.26)
project(Chat)

set(CMAKE_CXX_STANDARD 17)

# Добавление подкаталогов для клиента и сервера
add_subdirectory(src/client)
add_subdirectory(src/server)

add_custom_target(run_all
        COMMAND start $<TARGET_FILE:Server>
        COMMAND start $<TARGET_FILE:Client>
        DEPENDS Server Client
)
