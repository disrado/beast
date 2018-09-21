cmake_minimum_required(VERSION 3.10)

project(beast LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(conan)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP CMAKE_TARGETS BUILD missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(modules/app)
add_subdirectory(modules/https)

if (ENABLE_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif ()