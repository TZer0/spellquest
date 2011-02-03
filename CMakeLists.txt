CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
project(spellquest)

# Set output directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Find packages
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_SOURCE_DIR}/cmake/Utils")

#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREAD ON)
#find_package(Boost 1.34 COMPONENTS thread REQUIRED)
find_package(PhysFS REQUIRED)

# Optional parameters
set(CPPFLAGS "-O2" CACHE STRING "Compiler flags to use")
set(LINKFLAGS "" CACHE STRING "Linker flags to use")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKFLAGS}")

# Add additional compiler flags
add_definitions(${CPPFLAGS})

# Add addition linker flags
link_libraries(${PHYSFS_LIBRARY})
set(CMAKE_EXE_LINKER_FLAGS ${LINKFLAGS})

# Add source directories
add_subdirectory(src/)
add_subdirectory(tests/)

