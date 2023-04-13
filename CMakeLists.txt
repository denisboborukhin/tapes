project(teachable_dictionary)
cmake_minimum_required (VERSION 3.22.1 FATAL_ERROR)

set (PROJECT_NAME tapes)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER clang++)

set(TAPE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TAPE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/tape.cpp)

#set(PROGRAM_NAME dictionary_manager)
#set(MAIN_PROGRAM_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

#cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PROJECT_PARRENT_PATH)

include_directories (include)

add_library (${PROJECT_NAME} STATIC ${TAPE_SOURCE})

add_compile_options(-g -Wall)

#main

#clang-tidy
option(CLANG_TIDY "Include clang-tidy" OFF)
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    message (clang-tidy " from " ${CMAKE_SOURCE_DIR}/.clang-tidy)
    
    set (CMAKE_CXX_CLANG_TIDY
        "clang-tidy;-format-style=file:${CMAKE_SOURCE_DIR}/.clang-tidy;-checks=*"
    )
endif()

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
    set_target_properties (${PROGRAM_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif ()

add_subdirectory (tests)
