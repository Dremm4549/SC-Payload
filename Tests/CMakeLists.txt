cmake_minimum_required(VERSION 3.22)
project(PayloadTests)

include(FetchContent)
FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG main)
FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
	FetchCOntent_Populate(googletest)
	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

add_library(TelemLibrary "../source code/Telem.cpp")
add_library(PayloadLibrary "../source code/Payload.cpp")
add_library(PacketLibrary "../source code/Packet.cpp")
add_library(ImageDataLibrary "../source code/ImageData.cpp")

add_executable(PayloadTests Tests.cpp)
target_link_libraries(PayloadTests gtest_main gmock_main)
target_link_libraries(PayloadTests TelemLibrary)
target_link_libraries(PayloadTests PayloadLibrary)
target_link_libraries(PayloadTests PacketLibrary)
target_link_libraries(PayloadTests ImageDataLibrary)

