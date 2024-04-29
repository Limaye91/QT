project (fold LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Sql REQUIRED)

add_library(fold
    SHARED
    fold.cpp fold.h)

target_link_libraries(fold PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(fold PRIVATE Qt${QT_VERSION_MAJOR}::Sql)




