//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/src/SteppingAction.cpp
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#include "SteppingAction.hh"


//----------------------------- SteppingAction ------------------------------//
SteppingAction::SteppingAction(EventAction* eventAction, RunAction* runAction)
: G4UserSteppingAction(), b_EventAction(eventAction), b_RunAction(runAction)
{}


//---------------------------- ~SteppingAction ------------------------------//
SteppingAction::~SteppingAction()
{}


//--------------------------- UserSteppingAction ----------------------------//
void SteppingAction::UserSteppingAction(const G4Step* step)
{
    FillStepNtuple(step);
    
    // Collecting data for the track/event ntuples
    // (in RunAction::EndOfRunAction)
    G4int eventID = b_EventAction->GetEventID();
    G4int trackID = step->GetTrack()->GetTrackID();
    G4int parentID = step->GetTrack()->GetParentID();
    G4int PDG = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
    G4double Eloss = step->GetTotalEnergyDeposit();
    G4double globalTime = step->GetPreStepPoint()->GetGlobalTime();
    G4ThreeVector worldPosition = step->GetPreStepPoint()->GetPosition();
    G4ThreeVector momentum = step->GetPreStepPoint()->GetMomentum();
    G4double stepLength = step->GetStepLength();
    
    b_EventAction->AddStep(Eloss, stepLength);
    
    b_RunAction->FillRunStepData(eventID,
                                 trackID,
                                 parentID,
                                 PDG,
                                 Eloss,
                                 stepLength,
                                 worldPosition,
                                 momentum,
                                 globalTime);
}


//----------------------------- FillStepNtuple ------------------------------//
void SteppingAction::FillStepNtuple(const G4Step *step)
{
    // Collecting true info for each step
    G4int eventID = b_EventAction->GetEventID();
    G4int trackID = step->GetTrack()->GetTrackID();
    G4int PDG = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
    G4double Eloss = step->GetTotalEnergyDeposit();
    G4double length = step->GetStepLength();
    G4double globalTime = step->GetPreStepPoint()->GetGlobalTime();
    G4ThreeVector worldPosition = step->GetPreStepPoint()->GetPosition();
    G4ThreeVector momentum = step->GetPreStepPoint()->GetMomentum();
    G4String materialName = step->GetPreStepPoint()->GetMaterial()->GetName();
    G4String volName = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();
    G4int processStatus = step->GetPostStepPoint()->GetStepStatus();
    G4String processName = "undefined";

    // Status 7 means process not defined yet
    // See enum description in src/RunAction.cpp: RunAction::CreateRootNtuples
    if (processStatus != 7)
    {
        processName =
        step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    }

    // Filling in the data
    auto analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->FillNtupleIColumn(3,  0, eventID);
    analysisManager->FillNtupleIColumn(3,  1, trackID);
    analysisManager->FillNtupleIColumn(3,  2, PDG);
    analysisManager->FillNtupleSColumn(3,  3, materialName);
    analysisManager->FillNtupleSColumn(3,  4, volName);
    analysisManager->FillNtupleDColumn(3,  5, Eloss);
    analysisManager->FillNtupleDColumn(3,  6, length);
    analysisManager->FillNtupleDColumn(3,  7, globalTime);
    analysisManager->FillNtupleDColumn(3,  8, worldPosition.getX());
    analysisManager->FillNtupleDColumn(3,  9, worldPosition.getY());
    analysisManager->FillNtupleDColumn(3, 10, worldPosition.getZ());
    analysisManager->FillNtupleDColumn(3, 11, momentum.getX());
    analysisManager->FillNtupleDColumn(3, 12, momentum.getY());
    analysisManager->FillNtupleDColumn(3, 13, momentum.getZ());
    analysisManager->FillNtupleIColumn(3, 14, processStatus);
    analysisManager->FillNtupleSColumn(3, 15, processName);

    analysisManager->AddNtupleRow(3);
}
