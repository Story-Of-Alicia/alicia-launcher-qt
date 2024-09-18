cmake_minimum_required(VERSION 3.29)
project(launcher LANGUAGES CXX)
add_compile_options(-g)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS -static-libstdc++)

endif()

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/res)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(launcher
        src/main.cpp src/launcher.cpp src/MasterWindow.cpp src/util.cpp
        src/res/MasterWindow.ui src/res/master.qrc
        src/include/MasterWindow.hpp src/include/launcher.hpp src/include/util.hpp
)

qt_add_resources(launcher src/res/master.qrc)

target_include_directories(launcher PRIVATE src/include)

target_link_libraries(launcher PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

set_target_properties(launcher PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
)
