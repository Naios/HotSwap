file(GLOB_RECURSE HotSwap_SRC *.cpp *.hpp)
add_library(HotSwap STATIC ${HotSwap_SRC})

if ( UNIX )
  target_link_libraries(HotSwap
    ${Boost_LIBRARIES}
    dl
  )
else()
  target_link_libraries(HotSwap
    ${Boost_LIBRARIES}
  ) 
endif()
