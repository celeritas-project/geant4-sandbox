//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/include/DetectorConstruction.hh
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1


// Geant4
#include "G4VUserDetectorConstruction.hh"


//class G4GlobalMagFieldMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction(G4VPhysicalVolume *setWorld = 0);
    virtual G4VPhysicalVolume *Construct();
    
private:
    G4VPhysicalVolume *b_World;
    //static G4ThreadLocal G4GlobalMagFieldMessenger*  b_MagFieldMessenger;
};


#endif
