# CMakeLists.txt в src/client

project(Client)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
        client.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        loginsystem.cpp
        loginsystem.h
        loginsystem.ui
        authorisation.h
        authorisation.cpp
)

add_executable(Client
        ${SOURCES}
)

target_link_libraries(Client PRIVATE Qt5::Widgets)
