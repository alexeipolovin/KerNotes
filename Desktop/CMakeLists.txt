#set(CMAKE_PREFIX_PATH "E:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake")
set(CMAKE_PREFIX_PATH "/home/rob/Qt/5.15.2/gcc_64/lib/cmake")
cmake_minimum_required(VERSION 3.5)

project(KerNotes LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network REQUIRED)
#set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/app_icon.rc")
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS WebEngine REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5WebSockets REQUIRED)
#find_package(Qt5WebEngineWidgets REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS WebEngineCore REQUIRED)

set(PROJECT_SOURCES
        src/cpp/main.cpp
        src/cpp/mainwindow.cpp
        src/headers/mainwindow.h
        src/headers/webconnector.h
        src/cpp/webconnector.cpp
        src/headers/untextedit.h
        src/cpp/untextedit.cpp
        src/headers/settingswindow.h
        src/cpp/settingswindow.cpp
        src/headers/socketclient.h
        src/cpp/socketclient.cpp
        src/headers/uncomplete.h
        src/cpp/uncomplete.cpp
        src/resources/res.qrc
        src/headers/appearancesettings.h
        src/cpp/appearancesettings.cpp
        libraries/markdownhighliter/markdownhighlighter.h
        libraries/markdownhighliter/qmarkdowntextedit.h
        libraries/markdownhighliter/qownlanguagedata.h
        libraries/markdownhighliter/qplaintexteditsearchwidget.h
        libraries/markdownhighliter/qownlanguagedata.h
        libraries/markdownhighliter/markdownhighlighter.cpp
        libraries/markdownhighliter/qmarkdowntextedit.cpp
        libraries/markdownhighliter/qownlanguagedata.cpp
        libraries/markdownhighliter/qplaintexteditsearchwidget.cpp
        libraries/qjsontreeview/qjsonmodel.cpp
        libraries/qjsontreeview/qjsonmodel.h
        libraries/markdownhighliter/qplaintexteditsearchwidget.ui
        libraries/markdownhighliter/ui_qplaintexteditsearchwidget.h
        )

add_executable(KerNotes
    ${PROJECT_SOURCES}
    )


target_link_libraries(KerNotes PRIVATE Qt5::Gui)
target_link_libraries(KerNotes PRIVATE Qt5::Widgets)
target_link_libraries(KerNotes PRIVATE Qt5::Network)
target_link_libraries(KerNotes PRIVATE Qt5::WebSockets)
#target_link_libraries(KerNotes PRIVATE Qt${QT_VERSION_MAJOR}::WebEngine)
#target_link_libraries(KerNotes PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
