cmake_minimum_required(VERSION 3.5)

project(carDashboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(DatabaseFolder)
add_subdirectory(ServiceFolder)
add_subdirectory(googletest)
add_subdirectory(googlemock)
add_subdirectory(data)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        dashboardclass.cpp
        dashboardclass.h
        dashboardclass.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(carDashboard
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        userdialog.h userdialog.cpp userdialog.ui
        adduserdialog.h adduserdialog.cpp adduserdialog.ui
        maindashboard1.h maindashboard1.cpp maindashboard1.ui
        Resources.qrc
        servicetesting.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET carDashboard APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(carDashboard SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(carDashboard
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_include_directories(carDashboard PUBLIC ServiceFolder)
target_link_libraries(carDashboard PRIVATE ServiceLibrary)


target_include_directories(carDashboard PUBLIC DatabaseLibrary)
target_link_libraries(carDashboard PRIVATE DatabaseLibrary)

target_include_directories(carDashboard PUBLIC data)
target_link_libraries(carDashboard PRIVATE datalibrary)


target_include_directories(carDashboard PUBLIC googletest)
target_link_libraries(carDashboard PRIVATE gtest)

target_include_directories(carDashboard PUBLIC googlemock)
target_link_libraries(carDashboard PRIVATE gmock)








target_link_libraries(carDashboard PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)



# target_link_libraries(carDashboard PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.carDashboard)
endif()
set_target_properties(carDashboard PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS carDashboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(carDashboard)
endif()
