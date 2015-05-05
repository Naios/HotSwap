file(GLOB_RECURSE Application_SRC *.cpp *.hpp)

include_directories(
  ${CMAKE_SOURCE_DIR}/src
)

add_executable(Application ${Application_SRC})

if ( UNIX )
  target_link_libraries(Application
    ${Boost_LIBRARIES}
    HotSwap
    dl
  )
else()
  target_link_libraries(Application
    ${Boost_LIBRARIES}
    HotSwap
  )
endif()

if( UNIX )
  install(TARGETS Application DESTINATION bin)
elseif( WIN32 )
  install(TARGETS Application DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()
