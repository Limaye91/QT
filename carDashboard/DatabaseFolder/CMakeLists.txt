cmake_minimum_required(VERSION 3.5)
project(DatabaseFolder LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Sql REQUIRED)

add_library(DatabaseLibrary SHARED
    databaseconnection.cpp  # Include source files here
    databaseconnection.h    # Include header files here
)

target_link_libraries(DatabaseLibrary PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)
