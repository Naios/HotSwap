file(GLOB_RECURSE SRC *.cpp *.h *.hpp)

include_directories(
  ${CMAKE_SOURCE_DIR}/src
)

add_library(MyModule SHARED ${SRC})
