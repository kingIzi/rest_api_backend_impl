cmake_minimum_required(VERSION 3.16)

project(rest_api_backend_impl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Network Core REQUIRED)

set_source_files_properties(Colors.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)
set_source_files_properties(Typography.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_executable(apprest_api_backend_impl
    main.cpp restapi.cpp restapi.hpp user.cpp user.hpp
)

qt_add_qml_module(apprest_api_backend_impl
    URI rest_api_backend_impl
    VERSION 1.0
    QML_FILES main.qml Colors.qml Typography.qml SignInForm.qml LandingPage.qml SignUpForm.qml
    RESOURCES fonts/ZenKakuGothicNew-Regular.ttf fonts/ZenKakuGothicNew-Bold.ttf fonts/ZenKakuGothicNew-Light.ttf
)

set_target_properties(apprest_api_backend_impl PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(apprest_api_backend_impl
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(apprest_api_backend_impl
    PRIVATE Qt6::Quick Qt6::Network Qt6::Core)
