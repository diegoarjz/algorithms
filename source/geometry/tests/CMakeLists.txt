file(GLOB srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(source ${srcs})
    string(REPLACE ".cpp" "" testname ${source})

    add_executable(${testname} ${source})
    target_link_libraries(${testname} boost_unit_test_framework)
    target_link_libraries(${testname} Geometry)
    target_link_libraries(${testname} Utils)

    target_include_directories(${testname} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/source/Utils/")

    add_test(NAME ${testname} COMMAND ${testname})
endforeach(source ${srcs})
