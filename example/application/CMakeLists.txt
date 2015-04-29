file(GLOB_RECURSE Application_SRC *.cpp *.hpp)

add_executable(Application ${Application_SRC})

target_link_libraries(Application
  HotSwap
)
