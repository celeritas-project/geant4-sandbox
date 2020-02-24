//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/src/DetectorConstruction.cpp
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


// Project
#include "DetectorConstruction.hh"


//---------------------------- DetectorConstruction -------------------------//
DetectorConstruction::DetectorConstruction(G4VPhysicalVolume *setWorld)
{
    b_World = setWorld;
}


//-------------------------------- Construct --------------------------------//
G4VPhysicalVolume* DetectorConstruction::Construct()
{
    return b_World;
}
