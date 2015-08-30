file(GLOB_RECURSE SRC *.cpp *.h *.hpp)

include_directories(
  ${CMAKE_SOURCE_DIR}/example/application
  ${CMAKE_SOURCE_DIR}/src
)

add_library(Singleton SHARED ${SRC})

if( UNIX )
  install(TARGETS Singleton DESTINATION bin)
elseif( WIN32 )
  install(TARGETS Singleton DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()
