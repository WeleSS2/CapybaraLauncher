cmake_minimum_required(VERSION 3.18)

project(CapybaraLauncher LANGUAGES CXX VERSION 0.7)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QML_IMPORT_TRACE = 1)
find_package(Qt6 REQUIRED COMPONENTS Gui Qml Quick Network WebEngineQuick WebView)
find_package(OpenSSL REQUIRED)
set(ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/content/resources/capybaraIcon.ico)
set(RC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/content/resources/capybaraIcon.rc)

file(GLOB_RECURSE CPPEXECFILES "src/*.cpp")

qt_add_executable(CapybaraLauncher ${CPPEXECFILES}
    ${RC_FILE})


qt_add_resources(CapybaraLauncher "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(STEAMAPI REQUIRED PATHS ${PROJECT_SOURCE_DIR}/external/STEAM_API)
target_include_directories(CapybaraLauncher PRIVATE
    "${STEAMAPI_INCLUDE_DIRS}"
    ${OPENSSL_INCLUDE_DIR})
target_link_libraries(CapybaraLauncher PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::WebEngineQuick
    Qt${QT_VERSION_MAJOR}::WebView
    ${STEAMAPI_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)
#-- GameConnector config part
file(GLOB_RECURSE GAMECONFILES "gameconnector/*.cpp")
qt_add_executable(GameConnector ${GAMECONFILES})
target_include_directories(GameConnector PRIVATE
    src/utility/loggingsystem.cpp
    "${STEAMAPI_INCLUDE_DIRS}"
)


target_link_libraries(GameConnector PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Network
    ${STEAMAPI_LIBRARIES}
)
#target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)
set( LIST_NEEDED_DLL
    ${PROJECT_SOURCE_DIR}/external/STEAM_API/lib/win64/steam_api64.dll
    ${PROJECT_SOURCE_DIR}/update.bat
)

foreach( file_i ${LIST_NEEDED_DLL})
    add_custom_command(
    TARGET CapybaraLauncher
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${file_i} $<TARGET_FILE_DIR:CapybaraLauncher>
)

endforeach( file_i )
