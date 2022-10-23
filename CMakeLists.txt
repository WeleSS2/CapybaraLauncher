cmake_minimum_required(VERSION 3.18)

project(WH3_Mod_MenagerApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QML_IMPORT_TRACE = 1)
find_package(Qt6 COMPONENTS Gui Qml Quick)
qt_add_executable(WH3_Mod_MenagerApp src/main.cpp
    src/exit.cpp
    src/steamtools.cpp
    src/cmodslistfile.cpp
    src/cmodslistfilling.cpp
    src/windowsfunctions.cpp
    src/localfiles.cpp
    src/globaldata.cpp
    src/sortingmodlist.cpp
    src/modpackslist.cpp
    src/modpackscontent.cpp
    src/qtgeneralbackend.cpp
)

qt_add_resources(WH3_Mod_MenagerApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

find_package(STEAMAPI REQUIRED PATHS ${PROJECT_SOURCE_DIR}/external/STEAM_API)
target_include_directories(WH3_Mod_MenagerApp PRIVATE "${STEAMAPI_INCLUDE_DIRS}")

target_link_libraries(WH3_Mod_MenagerApp PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Qml
    ${STEAMAPI_LIBRARIES}
)

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)
set( LIST_NEEDED_DLL
    ${PROJECT_SOURCE_DIR}/external/STEAM_API/lib/win64/steam_api64.dll
)

foreach( file_i ${LIST_NEEDED_DLL})
    add_custom_command(
    TARGET WH3_Mod_MenagerApp
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${file_i} $<TARGET_FILE_DIR:WH3_Mod_MenagerApp>
)

endforeach( file_i )
