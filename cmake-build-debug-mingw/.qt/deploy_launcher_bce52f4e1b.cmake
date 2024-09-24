include(C:/Users/Martin/cxx/launcher/cmake-build-debug-mingw/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/launcher-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_ALL_MODULES_FOUND_VIA_FIND_PACKAGE "ZlibPrivate;EntryPointPrivate;Core;Gui;Widgets")

qt6_deploy_runtime_dependencies(
    EXECUTABLE C:/Users/Martin/cxx/launcher/cmake-build-debug-mingw/launcher.exe
    GENERATE_QT_CONF
    NO_TRANSLATIONS
)
