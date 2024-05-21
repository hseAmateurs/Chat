# CMakeLists.txt в src/client

project(Client)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets Sql Network REQUIRED)

set(SOURCES
        client.cpp
        core/mainWindow.cpp
        core/mainWindow.h
        core/loginSystem.cpp
        core/loginSystem.h
        core/chatWindow.cpp
        core/chatWindow.h

)

set(NETWORK
        network/server.h
)


set(UTILS
        utils/config.h
        utils/database.cpp
        utils/database.h
        utils/scripts/tables.h
        utils/cacher.cpp
        utils/cacher.h
)

set(UI_FILES
        core/mainwindow.ui
        core/loginsystem.ui
        core/chatwindow.ui
)

set(WIDGETS
        widgets/widget.cpp
        widgets/widget.h
        widgets/folderWidget.h
        widgets/userWidget.h
)

add_executable(Client WIN32
        ${SOURCES}
        ${UTILS}
        ${UI_FILES}
        ${WIDGETS}
        ${NETWORK}
        textures/res.qrc
)

target_link_libraries(Client PRIVATE Qt5::Widgets Qt5::Sql Qt5::Network)
