#[[ fatpound ]]#

cmake_minimum_required(VERSION 3.30)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")

project(CxxMade VERSION 1.0 LANGUAGES CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES TRUE)
set(CMAKE_CXX_MODULE_STD ON)

include(${CMAKE_SOURCE_DIR}/CompileOptions.cmake)

add_library(FatPound STATIC)

target_include_directories(FatPound PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(FatPound PRIVATE ${CMAKE_SOURCE_DIR}/include/FatModules)
target_include_directories(FatPound PRIVATE ${CMAKE_SOURCE_DIR}/include/FatModules/Win32_)

target_compile_definitions(FatPound PRIVATE UNICODE)
target_compile_definitions(FatPound PRIVATE FAT_BUILDING_ON_WINDOWS=1)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(FatPound PRIVATE IN_DEBUG=1)
    target_compile_definitions(FatPound PRIVATE IN_RELEASE=0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(FatPound PRIVATE IN_RELEASE=1)
    target_compile_definitions(FatPound PRIVATE IN_DEBUG=0)
endif()

file(GLOB_RECURSE MOD_IMPL_UNITS "include/**/*.cxx")
file(GLOB_RECURSE MOD_INTF_UNITS "include/**/*.ixx")

set(MODULES ${MOD_INTF_UNITS})

target_sources(FatPound
    PUBLIC
    FILE_SET CXX_MODULES FILES
        ${MODULES}
)

target_compile_features(FatPound
    PRIVATE   cxx_std_23
    INTERFACE cxx_std_23
)

set(SOURCES
    ${MOD_IMPL_UNITS}
    src/Main.cxx
)

add_executable(CxxMade
    ${SOURCES}
)

target_link_libraries(CxxMade
    PUBLIC
        FatPound
    PRIVATE
        Fat::CompileOptions
)
