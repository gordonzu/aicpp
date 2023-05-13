include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(BINARY unit_tests_run)

# set(
#     TEST_SOURCES 
#     main.cpp
#     vacuum_environment_test.cpp
# )

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

add_executable(${BINARY} ${TEST_SOURCES})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gtest_main pthread)

add_test(NAME ${BINARY} COMMAND ${BINARY})

