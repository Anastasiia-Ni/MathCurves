cmake_minimum_required(VERSION 3.5)

project(Math_Curves VERSION 0.1 LANGUAGES CXX)

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
        renderarea.cpp
        renderarea.h
)

add_executable(Math_Curves ${PROJECT_SOURCES})

target_include_directories(Math_Curves PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Math_Curves PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


set_target_properties(Math_Curves PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Math_Curves
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Math_Curves
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Math_Curves)
endif()
