# TODO:
# change Object class location to util/types folder
# change name of Object to Attribute

# keep EnvironmentObject's name and location  

# is Percept now an EnvironmentObject? 




project(aicpp)
cmake_minimum_required(VERSION 2.6)

include_directories(
                    "$ENV{GTEST_INC}"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src"
                   )
link_directories   (
                    "$ENV{GTEST_LIB}"
                   )

set(CMAKE_CXX_FLAGS "-std=c++17 -ggdb3 -Wall -Wno-unused-variable -O0 -fmax-errors=1")

set(
    sources
    main.cpp
    src/agent/agent.cpp
    src/environment/wall.cpp
    src/environment/world.cpp
    src/environment/xyenv/xy_environment.cpp
    src/environment/xyenv/xy_environment_state.cpp
    src/util/datastructure/xy_location.cpp
    src/agent/agent_programs/table_driven.cpp
    src/agent/dynamic_object.cpp
    src/agent/action.cpp

    test/vacuum_environment_test.cpp
    test/reflex_vacuum_agent_test.cpp
    test/percept_test.cpp
	test/base_object_test.cpp
    test/table_test.cpp
    test/percept_sequence_test.cpp
    test/xy_environment_test.cpp
    test/simple_rule_test.cpp
    test/tabledriven_agent_program_test.cpp
   )

add_executable(aicpp ${sources})
target_link_libraries(aicpp gtest)
target_link_libraries(aicpp pthread)

add_custom_command(TARGET aicpp
                   POST_BUILD
                   COMMAND "make")

add_custom_command(TARGET aicpp
                   POST_BUILD
#                  COMMAND valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all ./aicpp)
#                  COMMAND valgrind --tool=memcheck --leak-check=yes ./aicpp)
                   COMMAND ./aicpp)

