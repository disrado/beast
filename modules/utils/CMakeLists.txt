cmake_minimum_required(VERSION 3.10)

project(utils LANGUAGES CXX)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES 
    "src/*.cpp"
)

add_library(${PROJECT_NAME}
    STATIC
        ${${PROJECT_NAME}_SOURCES}
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        logger
        ${CONAN_LIBS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
        extern/include/logger
        ${CONAN_LIBS}
)