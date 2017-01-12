file(GLOB srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(source ${srcs})
    string(REPLACE ".cpp" "" testname ${source})

    add_executable(${testname} ${source})
    target_link_libraries(${testname} Sorting)
    target_link_libraries(${testname} boost_unit_test_framework)
    add_test(NAME ${testname} COMMAND ${testname})

endforeach(source ${srcs})
