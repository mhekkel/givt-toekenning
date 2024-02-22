cmake_minimum_required(VERSION 3.22)

project(givt-toekenning LANGUAGES CXX)

set(CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(date REQUIRED)
find_package(libmcfp REQUIRED)

add_executable(givt-toekenning
	givt-toekenning.cpp
)

target_link_libraries(givt-toekenning date::date libmcfp::libmcfp)
