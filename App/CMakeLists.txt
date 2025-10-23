cmake_minimum_required(VERSION 3.16)

set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/AppConfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/AppConfig.h)

add_executable(App
               source/main.cpp
              )

# raylib is built as a subdirectory, no need for find_package
# The raylib target is already available from the parent CMakeLists.txt

target_link_libraries(App PRIVATE
                      raylib
                     )

if (APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

target_include_directories(App PRIVATE
                           ${CMAKE_SOURCE_DIR}/raylib/src
                           ${CMAKE_SOURCE_DIR}/App/include
                           ${CMAKE_CURRENT_BINARY_DIR}/include
                          )

target_compile_definitions(App PRIVATE)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/AppConfig.h DESTINATION include)