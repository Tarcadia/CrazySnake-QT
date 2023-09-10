cmake_minimum_required(VERSION 3.5)

project(QTSnake VERSION 0.1 LANGUAGES CXX)

INCLUDE_DIRECTORIES(/home/tarcadia/Projects/QTSnake)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QTSnake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        scene/scenemenu/scenemenu.h scene/scenemenu/scenemenu.cpp scene/scenemenu/scenemenu.ui
        resources.qrc
        components/qsliderlabel.h components/qsliderlabel.cpp

        scene/scenehelp/scenehelp.h scene/scenehelp/scenehelp.cpp scene/scenehelp/scenehelp.ui
        scene/scenegame/scenegame.h scene/scenegame/scenegame.cpp scene/scenegame/scenegame.ui
        components/qclickimage.h components/qclickimage.cpp
        scene/sceneendgame/sceneendgame.h scene/sceneendgame/sceneendgame.cpp scene/sceneendgame/sceneendgame.ui
        game.h game.cpp





    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QTSnake APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QTSnake SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QTSnake
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QTSnake PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QTSnake)
endif()
set_target_properties(QTSnake PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QTSnake
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QTSnake)
endif()
