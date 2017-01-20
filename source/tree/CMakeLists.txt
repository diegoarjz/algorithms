file(GLOB srcs "*.h" "*.cpp")

# add the library
add_library(Tree ${srcs})

add_subdirectory("tests")
