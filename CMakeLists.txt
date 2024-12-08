cmake_minimum_required(VERSION 3.16)

project(Checkers VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appCheckers
    src/main.cpp
)
list(APPEND QML_IMPORT_PATH gui/Singleton/CheckersTheme.qml)
set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/qml ${CMAKE_BINARY_DIR}/imports CACHE STRING "" FORCE)

set_source_files_properties(gui/Singleton/CheckersTheme.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(appCheckers
    URI Checkers
    VERSION 1.0
    QML_FILES
        gui/Main.qml
        QML_FILES gui/Singleton/CheckersTheme.qml
        RESOURCES
        SOURCES src/checkersmodel.h src/checkersmodel.cpp
        QML_FILES gui/GameBoard.qml
        QML_FILES gui/Piece.qml
        QML_FILES gui/frontEnd.js
        SOURCES src/game.h src/game.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCheckers PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCheckers
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCheckers
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appCheckers
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
