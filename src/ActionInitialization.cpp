//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/src/ActionInitialization.cpp
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


// Project
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"


//--------------------------- ActionInitialization --------------------------//
ActionInitialization::ActionInitialization()
: G4VUserActionInitialization(), rootFile("rootout.root"),
isCustomRootFile(false)
{}

ActionInitialization::ActionInitialization(G4String rootFile)
: G4VUserActionInitialization(), rootFile(rootFile),
isCustomRootFile(true)
{}


//-------------------------- ~ActionInitialization --------------------------//
ActionInitialization::~ActionInitialization()
{}


//------------------------------ BuildForMaster -----------------------------//
// In case of multithread
void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction(new PrimaryGeneratorAction));
}


//---------------------------------- Build ----------------------------------//
void ActionInitialization::Build() const
{
    PrimaryGeneratorAction* primaryGenAction = new PrimaryGeneratorAction();
    RunAction* runAction;
    
    if (isCustomRootFile)
    {
        runAction = new RunAction(primaryGenAction, rootFile);
    }
    else
    {
        runAction = new RunAction(primaryGenAction);
    }
    
    EventAction* eventAction = new EventAction(primaryGenAction, runAction);
    SteppingAction* steppingAction = new SteppingAction(eventAction,
                                                        runAction);
    
    SetUserAction(primaryGenAction);
    SetUserAction(runAction);
    SetUserAction(eventAction);
    SetUserAction(steppingAction);
}  

