file(GLOB_RECURSE HotSwap_SRC *.cpp *.hpp)
add_library(HotSwap STATIC ${HotSwap_SRC})

#target_link_libraries(HotSwap
#  ${Boost_LIBRARIES}
#)

if (${UNIX})
    target_link_libraries(HotSwap dl)
endif()
