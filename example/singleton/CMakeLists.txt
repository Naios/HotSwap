file(GLOB_RECURSE SRC *.cpp *.h *.hpp)

include_directories(
  ${CMAKE_SOURCE_DIR}/example/application
  ${CMAKE_SOURCE_DIR}/example/dependency
  ${CMAKE_SOURCE_DIR}/src
)

add_library(Singleton SHARED ${SRC})

target_link_libraries(Singleton
  MyDependency
)

if( UNIX )
  install(TARGETS Singleton
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
  )
elseif( WIN32 )
  install(TARGETS Singleton DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()
