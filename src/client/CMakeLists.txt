# CMakeLists.txt в src/client

project(Client)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
        client.cpp
        mainWindow.cpp
        mainWindow.h
        mainwindow.ui
        loginSystem.cpp
        loginSystem.h
        loginsystem.ui
        authorisation.cpp
        authorisation.h
        chatWindow.cpp
        chatWindow.h
        chatwindow.ui
)

add_executable(Client
        ${SOURCES}
)

target_link_libraries(Client PRIVATE Qt5::Widgets)
