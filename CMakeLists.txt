cmake_minimum_required(VERSION 3.16)

project(GS_GPGPU VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(ARCH_DIR "x64")
else()
  set(ARCH_DIR "x86")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ARCH_DIR}/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ARCH_DIR}/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ARCH_DIR}/$<CONFIG>)

foreach(OUTPUTCONFIG Debug Release RelWithDebInfo MinSizeRel)
  foreach(OUTPUTTYPE RUNTIME LIBRARY ARCHIVE)
    set(CMAKE_${OUTPUTTYPE}_OUTPUT_DIRECTORY_${OUTPUTCONFIG} 
      ${CMAKE_BINARY_DIR}/${ARCH_DIR}/${OUTPUTCONFIG})
  endforeach()
endforeach()

add_subdirectory(raylib)
add_subdirectory(App)

# Assets operations (only if Assets directory exists)
set(ASSETS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Assets)
set(ASSETS_DEST_DIR ${CMAKE_BINARY_DIR}/${ARCH_DIR}/$<CONFIG>/Assets)

if(EXISTS ${ASSETS_SOURCE_DIR})
  add_custom_target(copy_assets ALL
                    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_SOURCE_DIR} ${ASSETS_DEST_DIR}
                    COMMENT "Copying assets to output directory")
  add_dependencies(App copy_assets)
endif()