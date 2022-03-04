cmake_minimum_required(VERSION 3.20)

project(simple-project LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(QuaZip-Qt5)

add_executable(simple-project
  main.cpp
)

add_subdirectory(MathFunctions)
target_link_libraries(simple-project Qt${QT_VERSION_MAJOR}::Core MathFunctions)

install(TARGETS simple-project)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${simple-project_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${simple-project_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)

if(WIN32)
    #dlls
    include(HandleFunctions.txt)
    find_package(ZLIB)
    get_target_property(raw_path_zlib ZLIB::ZLIB LOCATION)
    handleZlib(${raw_path_zlib} path_zlib)
    if(NOT EXISTS ${path_zlib})
        message("ZLIB: not find")
    endif()
    get_target_property(QuaZip_location QuaZip::QuaZip LOCATION)
    list(APPEND list_dlls ${path_zlib} ${QuaZip_location})
    install(
        FILES
        ${list_dlls}
        DESTINATION bin
        )
    #qt dlls
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")
    add_custom_command(TARGET simple-project
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/windeployqt"
        COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --dir "${CMAKE_CURRENT_BINARY_DIR}/windeployqt" "$<TARGET_FILE:simple-project>"
        )
    install(
        DIRECTORY
        "${CMAKE_CURRENT_BINARY_DIR}/windeployqt/"
        DESTINATION bin
        )
endif()


