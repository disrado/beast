cmake_minimum_required(VERSION 3.10)

project(server LANGUAGES CXX)

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
        ${CONAN_LIBS}
        utils
        logger
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
        extern/logger/include
        ${CONAN_LIBS}
)