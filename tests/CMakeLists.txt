set (SOURCE_TAPE_TEST ${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp)

include_directories (${TAPE_INCLUDES})

#tests
option(TESTING "Include testing" ON)
if (TESTING)
    message ("Include " ${PROJECT_NAME} " testing")

    find_package (GTest REQUIRED)
    include_directories (${GTEST_INCLUDE_DIRS})

    add_executable (${PROJECT_NAME}_tests ${SOURCE_TAPE_TEST})
    
    if (ADD_SANITIZERS)
        set_target_properties (${PROJECT_NAME}_tests PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
    endif()
    
    target_link_libraries (${PROJECT_NAME}_tests PUBLIC GTest::GTest GTest::Main ${PROJECT_NAME} ${SORTER})
       
    enable_testing ()

    add_custom_target (run_${PROJECT_NAME}_tests 
        COMMENT "Running " ${PROJECT_NAME} "_tests"
        COMMAND ./${PROJECT_NAME}_tests
    )
    add_dependencies (run_${PROJECT_NAME}_tests ${PROJECT_NAME}_tests)
endif ()


