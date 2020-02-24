#-----------------------------------------------------------------------------#
#/*!
# * \file   sandbox/CMakeLists.txt
# * \author Stefano Tognini
# * \brief  CMakeLists for the Geant4-sandbox of the Celeritas Project.
# * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
# */
#-----------------------------------------------------------------------------#


#------------------------------------------------------------------------------
# Setting the install directory to be the current one and setting Geant4_DIR

set(CMAKE_INSTALL_PREFIX . CACHE PATH "CMake prefix" FORCE)
set(Geant4_DIR $ENV{Geant4_DIR})


#------------------------------------------------------------------------------
# Setting up the project

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(sandbox)


#------------------------------------------------------------------------------
# Finding Geant4 package, activating all available Vis drivers by default

option(WITH_GEANT4_VIS "Build with Geant4 Vis drivers" ON)

if(WITH_GEANT4_VIS)
  find_package(Geant4 REQUIRED gdml vis_all)

else()
  find_package(Geant4 REQUIRED gdml)

endif()


#------------------------------------------------------------------------------
# Setting up Geant4 include directories and compile definitions

include(${Geant4_USE_FILE})


#------------------------------------------------------------------------------
# Locating sources and headers of the GDML Viewer

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


#------------------------------------------------------------------------------
# Adding the executable, and linking it to the Geant4 libraries

add_executable(main main.cpp ${sources} ${headers})
target_link_libraries(main ${Geant4_LIBRARIES} )


#------------------------------------------------------------------------------
# Copying all scripts to the build directory

set(SCRIPTS init.mac vis.mac gui_menu.mac slabsGeometry.gdml cms2018.gdml)

foreach(_script ${SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


#------------------------------------------------------------------------------
# Adding main to the project target
# (Avoiding the need of typing the program name after make)

add_custom_target(sandbox DEPENDS main)


#------------------------------------------------------------------------------
# Installing the executable to the current directory

install(TARGETS main DESTINATION .)

