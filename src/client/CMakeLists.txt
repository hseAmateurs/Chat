# CMakeLists.txt в src/client

project(Client)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)

set(SOURCES
        client.cpp
        core/mainWindow.cpp
        core/mainWindow.h
        core/loginSystem.cpp
        core/loginSystem.h
        core/chatWindow.cpp
        core/chatWindow.h

)

set(SETTINGS
        settings/config.h
)

set(CACHING
        caching/database.cpp
        caching/database.h
        caching/scripts/tables.h
        caching/cacher.cpp
        caching/cacher.h
)

set(UI_FILES
        core/mainwindow.ui
        core/loginsystem.ui
        core/chatwindow.ui
)

add_executable(Client
        ${SOURCES}
        ${SETTINGS}
        ${CACHING}
        ${UI_FILES}
)

target_link_libraries(Client PRIVATE Qt5::Widgets Qt5::Sql)
