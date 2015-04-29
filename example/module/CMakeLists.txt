file(GLOB_RECURSE SRC *.cpp *.h *.hpp)
add_library(MyModule SHARED ${SRC})
