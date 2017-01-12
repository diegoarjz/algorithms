file(GLOB srcs "*.h" "*.cpp")

# add the library
add_library(Sorting ${srcs})

add_subdirectory("tests")
