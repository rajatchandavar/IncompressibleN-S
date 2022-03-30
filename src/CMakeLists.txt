cmake_minimum_required(VERSION 3.1)
project(incompressible_NS)

set( CMAKE_CXX_COMPILER "g++")
set( CMAKE_CXX_FLAGS "-pg -O3 -Wall" )

include_directories( . })

add_executable(incompressible main.cpp Grid.cpp solver.cpp SOR.cpp Boundary_Conditions.cpp write2file.cpp)

SET(ADDITIONAL_CLEAN_FILES "")

LIST(APPEND ADDITIONAL_CLEAN_FILES "${build}CMakeCache.txt")
LIST(APPEND ADDITIONAL_CLEAN_FILES "${build}cmake_install.cmake")
LIST(APPEND ADDITIONAL_CLEAN_FILES "${build}Makefile.txt")

LIST(APPEND ADDITIONAL_CLEAN_FILES "${build/CMakeFiles}")

LIST(APPEND ADDITIONAL_CLEAN_FILES "${results}Pressure.txt")
#LIST(APPEND ADDITIONAL_CLEAN_FILES "${../results}x-velocity.txt")
#LIST(APPEND ADDITIONAL_CLEAN_FILES "${../results}y-velocity.txt")

GET_DIRECTORY_PROPERTY(clean_files ADDITIONAL_MAKE_CLEAN_FILES)
LIST(APPEND            clean_files ${ADDITIONAL_CLEAN_FILES})
#LIST(REMOVE_DUPLICATES clean_files)
LIST(REMOVE_ITEM       clean_files "")
SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${clean_files}")
