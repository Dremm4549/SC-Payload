cmake_minimum_required(VERSION 3.7)

project(ScPayload)

set(CMAKE_CXX_STANDARD 20)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(ScPayload main.cpp)
target_link_libraries(ScPayload ${Boost_LIBRARIES} Threads::Threads)