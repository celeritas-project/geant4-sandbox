//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/src/ActionInitialization.cpp
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#include "ActionInitialization.hh"


//--------------------------- ActionInitialization --------------------------//
ActionInitialization::ActionInitialization()
: G4VUserActionInitialization()
{}


//-------------------------- ~ActionInitialization --------------------------//
ActionInitialization::~ActionInitialization()
{}


//------------------------------ BuildForMaster -----------------------------//
// In case of multithread
void ActionInitialization::BuildForMaster() const
{
    //SetUserAction(new RunAction(new PrimaryGeneratorAction(isPythiaHepevtInput)));
}


//---------------------------------- Build ----------------------------------//
void ActionInitialization::Build() const
{
    PrimaryGeneratorAction* primaryGenAction =
    new PrimaryGeneratorAction(isPythiaInput, pythiaInputFile);
    
    
    RunAction* runAction;
    
    if (isCustomRootFile)
    {
        runAction = new RunAction(primaryGenAction, rootOutputFile);
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


//--------------------------- IsPythiaHepevtInput ---------------------------//
void ActionInitialization::IsPythiaHepevtInput(bool &isPythia)
{
    this->isPythiaInput = isPythia;
}


//---------------------------- SetRootOutputFile ----------------------------//
void ActionInitialization::SetRootOutputFile(G4String rootOutputFile)
{
    this->rootOutputFile = rootOutputFile;
    this->isCustomRootFile = true;
}


//---------------------------- SetPythiaInputFile ---------------------------//
void ActionInitialization::SetPythiaInputFile(G4String pythiaInputFile)
{
    this->pythiaInputFile = pythiaInputFile;
    this->isPythiaInput = true;
}
