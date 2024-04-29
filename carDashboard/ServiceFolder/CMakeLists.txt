project (SerivceFolder LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)

 add_library(ServiceLibrary
     SHARED
     serviceconnection.h serviceconnection.cpp)

 target_link_libraries(ServiceLibrary PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)





