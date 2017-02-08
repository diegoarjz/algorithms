file(GLOB srcs "*.h" "*.cpp")

# add the library
add_library(Geometry ${srcs})

add_subdirectory("tests")
