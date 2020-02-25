//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/include/ActionInitialization.hh
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#ifndef EventAction_h
#define EventAction_h 1


// C++
#include <vector>

// Geant4
#include "G4UserEventAction.hh"
#include "globals.hh"


class PrimaryGeneratorAction;
class RunAction;

class EventAction : public G4UserEventAction
{
public:
    G4int d_eventID;
    G4double d_trackEnergy;
    G4double d_trackLength;
    PrimaryGeneratorAction* b_primary;
    RunAction* b_runAction;

    EventAction(PrimaryGeneratorAction* primGenAct, RunAction* run);
    virtual ~EventAction();
    
    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void  EndOfEventAction(const G4Event* event);
    
    void AddStep(G4double &stepdEdX, G4double &stepLength);
    
    G4int GetEventID();
};


#endif


