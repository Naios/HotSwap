file(GLOB_RECURSE Application_SRC *.cpp *.hpp)

include_directories(
  ${CMAKE_SOURCE_DIR}/src
)

add_executable(Application ${Application_SRC})

target_link_libraries(Application
  HotSwap
#  ${Boost_LIBRARIES}
)
