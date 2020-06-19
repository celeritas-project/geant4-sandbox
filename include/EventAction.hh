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
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserEventAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

// Project
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "Analysis.hh"


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
    G4ThreeVector RandomUnitaryThreeVector();
};


#endif


