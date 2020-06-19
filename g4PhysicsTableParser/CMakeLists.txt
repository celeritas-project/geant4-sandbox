#-----------------------------------------------------------------------------#
#/*!
# * \file   CMakeLists.txt
# * \author Stefano Tognini
# * \brief  CMakeLists of g4PhysicsTableParser.
# */
#-----------------------------------------------------------------------------#


#------------------------------------------------------------------------------
# Setting up the project
#------------------------------------------------------------------------------
project(g4PhysicsTableParser LANGUAGES CXX)

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)


#------------------------------------------------------------------------------
# Setting environmental variables
#------------------------------------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})


#------------------------------------------------------------------------------
# Finding packages
#------------------------------------------------------------------------------
find_package(ROOT REQUIRED)


#------------------------------------------------------------------------------
# Adding the executable, and linking it to the needed libraries
#------------------------------------------------------------------------------
add_executable(g4PhysicsTableParser main.cpp
  src/G4PhysicsTableParser.cpp
  include/G4PhysicsTableParser.hh
)

target_include_directories(g4PhysicsTableParser PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(g4PhysicsTableParser PRIVATE
  ROOT::Core ROOT::Tree
)


#------------------------------------------------------------------------------
# Installing the executable to the current directory
#------------------------------------------------------------------------------
install(TARGETS g4PhysicsTableParser DESTINATION .)
