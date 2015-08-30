file(GLOB_RECURSE SRC *.cpp *.h *.hpp)

include_directories(
  ${CMAKE_SOURCE_DIR}/example/application
  ${CMAKE_SOURCE_DIR}/src
)

add_library(MyModule SHARED ${SRC})

target_link_libraries(MyModule
  Singleton
)

if( UNIX )
  install(TARGETS MyModule DESTINATION bin)
elseif( WIN32 )
  install(TARGETS MyModule DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()
