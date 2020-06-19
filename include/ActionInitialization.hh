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

// Project
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"


class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization
{
public:
    G4String rootOutputFile;
    G4String pythiaInputFile;
    bool isCustomRootFile = false;
    bool isPythiaInput = false;
    
    ActionInitialization();
    virtual ~ActionInitialization();
    
    virtual void Build() const;
    
    // In case of multithread
    virtual void BuildForMaster() const;
    
    void IsPythiaHepevtInput(bool &isPythia);
    void SetRootOutputFile(G4String rootOutputFile);
    void SetPythiaInputFile(G4String pythiaInputFile);
};


#endif


