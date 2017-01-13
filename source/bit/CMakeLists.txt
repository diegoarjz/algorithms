file(GLOB srcs "*.h" "*.cpp")

# add the library
add_library(Bit ${srcs})

add_subdirectory("tests")
