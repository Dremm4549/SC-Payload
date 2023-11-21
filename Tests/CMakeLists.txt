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

add_executable(PayloadTests Tests.cpp)
target_link_libraries(PayloadTests gtest_main gmock_main)