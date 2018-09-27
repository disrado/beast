cmake_minimum_required(VERSION 3.10)

project(app LANGUAGES CXX)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES 
    "src/*.cpp"
)

add_executable(${PROJECT_NAME}
	${${PROJECT_NAME}_SOURCES}
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME}
	${CONAN_LIBS}
	https
	utils
	stdc++fs
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
        ${CONAN_LIBS}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/modules/app/assets
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
	COMMENT "Copying app configuration emails..."
)
