//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/include/SteppingAction.hh
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#ifndef SteppingAction_h
#define SteppingAction_h 1


// Geant4
#include "G4UserSteppingAction.hh"


class DetectorConstruction;
class EventAction;
class RunAction;

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction(EventAction* eventAction, RunAction* runAction);
    virtual ~SteppingAction();
    
    virtual void UserSteppingAction(const G4Step* step);
    
private:
    EventAction*  b_EventAction;
    RunAction* b_RunAction;
    
    virtual void FillStepNtuple(const G4Step* step);
};


#endif
