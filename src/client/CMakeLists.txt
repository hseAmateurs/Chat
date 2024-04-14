# CMakeLists.txt в src/client

project(Client)

add_executable(Client client.cpp)

# Для платформы windows используем статическую библиотеку sfml
if (WIN32)
    set(SFML_ROOT ${CMAKE_SOURCE_DIR}/sfml/${CMAKE_CXX_COMPILER_ID})
    set(SFML_STATIC_LIBRARIES TRUE)

    # Поиск компонентов библиотеки
    find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

    if (SFML_FOUND)
        # Добавление headers
        target_include_directories(Client PRIVATE ${SFML_INCLUDE_DIR})
        # Линковка библиотек
        target_link_libraries(Client PRIVATE sfml-graphics sfml-window sfml-system)
    endif ()
endif ()
