#-----------------------------------------------------------------------------#
#/*!
# * \file   sandbox/CMakeLists.txt
# * \author Stefano Tognini
# * \brief  CMakeLists for the Geant4-sandbox of the Celeritas Project.
# * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
# */
#-----------------------------------------------------------------------------#


#------------------------------------------------------------------------------
# Setting up the project
#------------------------------------------------------------------------------
project(geant4-sandbox)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)


#------------------------------------------------------------------------------
# Locating sources and headers of the project
#------------------------------------------------------------------------------
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


#------------------------------------------------------------------------------
# Setting Geant4_DIR and project sources
#------------------------------------------------------------------------------
list(APPEND CMAKE_PREFIX_PATH $ENV{Geant4_DIR})


#------------------------------------------------------------------------------
# Finding Geant4 package, activating all available Vis drivers by default
#------------------------------------------------------------------------------
option(WITH_GEANT4_VIS "Build with Geant4 Vis drivers" ON)

if(WITH_GEANT4_VIS)
  find_package(Geant4 REQUIRED gdml vis_all)

else()
  find_package(Geant4 REQUIRED gdml)

endif()


#------------------------------------------------------------------------------
# Adding the executable, and linking it to all libraries
#------------------------------------------------------------------------------
add_executable(g4-sandbox main.cpp ${sources} ${headers})

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})

target_link_libraries(g4-sandbox PRIVATE ${Geant4_LIBRARIES})


#------------------------------------------------------------------------------
# Copying scripts and gdml files to the build directory
#------------------------------------------------------------------------------
set(SCRIPTS init.mac vis.mac gui_menu.mac slabsGeometry.gdml cms2018.gdml)

foreach(_script ${SCRIPTS})
  configure_file(${PROJECT_SOURCE_DIR}/${_script}
                 ${PROJECT_BINARY_DIR}/${_script}
                 COPYONLY)

endforeach()


#------------------------------------------------------------------------------
# Installing the executable to the current directory
#------------------------------------------------------------------------------
install(TARGETS g4-sandbox DESTINATION .)
