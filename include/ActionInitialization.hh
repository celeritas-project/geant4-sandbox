//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/include/ActionInitialization.hh
 * \author Stefano Tognini
 * \brief  Sandbox program for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#ifndef ActionInitialization_h
#define ActionInitialization_h 1


// Geant4
#include "G4VUserActionInitialization.hh"
#include "globals.hh"

class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization();
    ActionInitialization(G4String rootFile);
    virtual ~ActionInitialization();
    
    virtual void Build() const;
    
    // In case of multithread
    virtual void BuildForMaster() const;
    
private:
    G4String rootFile;
    bool isCustomRootFile;
};


#endif


