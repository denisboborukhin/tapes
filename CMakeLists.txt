project(teachable_dictionary)
cmake_minimum_required (VERSION 3.16.2 FATAL_ERROR)

set (PROJECT_NAME tapes)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER clang++)

set(TAPE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SORTER tape_sorter)
set(TAPE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/tape.cpp)
set(SORTER_TAPE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/tape_sorter.cpp)
set(MAIN_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_definitions(-DPROJECT_DIR_PATH=\"${CMAKE_SOURCE_DIR}\""/")
include_directories (include)

add_library(${PROJECT_NAME} STATIC ${TAPE_SOURCE})
add_library(${SORTER} STATIC ${SORTER_TAPE_SOURCE})
target_link_libraries(${SORTER} PUBLIC ${PROJECT_NAME})

add_compile_options(-g -Wall)

#main
add_executable(sort_tape ${MAIN_SOURCE})
target_link_libraries (sort_tape PRIVATE ${PROJECT_NAME} ${SORTER})
add_custom_target (run_sort_tape 
    COMMAND ./sort_tape
)
add_dependencies (run_sort_tape sort_tape)

#clang-format
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    message (clang-format " from " ${CMAKE_SOURCE_DIR}/.clang-format)

    file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
    add_custom_target(
        clang_format
        COMMAND clang-format
        -i
        -style=file:${CMAKE_SOURCE_DIR}/.clang-format
        ${ALL_SOURCE_FILES}
    )
endif()

#sanitizers
option(ADD_SANITIZERS "Build with sanitizers" ON)
if (ADD_SANITIZERS)
    message ("Build with sanitizers")

    add_compile_options (-fsanitize=address -fsanitize=undefined)
    set_target_properties (${PROJECT_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
    set_target_properties (${SORTER} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif ()

add_subdirectory (tests)
