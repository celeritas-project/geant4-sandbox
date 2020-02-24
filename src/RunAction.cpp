//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/src/RunAction.cpp
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


// Project
#include "RunAction.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "Analysis.hh"

// Geant4
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


//---------------------------- BeginOfRunAction -----------------------------//
void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    CreateRootFile("rootout.root");
}


//-------------------------------- RunAction --------------------------------//
RunAction::RunAction(PrimaryGeneratorAction* primGenAct)
: G4UserRunAction(), b_primary(primGenAct)
{ 
    // Setting G4RunManager to print event number
    G4RunManager::GetRunManager()->SetPrintProgress(1);
    
    ClearStepVectorMembers();

    CreateRootNtuples();
}


//------------------------------- ~RunAction --------------------------------//
RunAction::~RunAction()
{
    delete G4AnalysisManager::Instance();
}


//------------------------------ EndOfRunAction -----------------------------//
void RunAction::EndOfRunAction(const G4Run* run)
{
    FillRunNtuple(run);
    
    FillEventNtuple();
    
    FillTrackNtuple();
    
    FinishRootFile();
}


//----------------------------- CreateRootFile ------------------------------//
void RunAction::CreateRootFile(G4String rootFileName)
{
    // Calling the analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    
    // Opening the new file;
    analysisManager->OpenFile(rootFileName);
}


//------------------------------ FillRunData --------------------------------//
void RunAction::FillRunData(G4int &eventID,
                            G4int &trackID,
                            G4int &parentID,
                            G4int &pdg,
                            G4double &Eloss,
                            G4double &stepLen,
                            G4ThreeVector &stepPosition,
                            G4ThreeVector &stepMomentum,
                            G4double &globalTime)
{
    this->d_vec_eventID.push_back(eventID);
    this->d_vec_trackID.push_back(trackID);
    this->d_vec_parentID.push_back(parentID);
    this->d_vec_pdg.push_back(pdg);
    this->d_vec_stepEloss.push_back(Eloss);
    this->d_vec_stepLen.push_back(stepLen);
    this->d_vec_stepPosition.push_back(stepPosition);
    this->d_vec_stepMomentum.push_back(stepMomentum);
    this->d_vec_stepGTime.push_back(globalTime);
}


//---------------------------- CreateRootNtuples ----------------------------//
void RunAction::CreateRootNtuples()
{
    // Calling the analysis manager to write the ROOT output file
    auto analysisManager = G4AnalysisManager::Instance();
    
    // In case we need directories
    //analysisManager->SetNtupleDirectoryName("sim");
    
    // Setting up flags
    //analysisManager->SetNtupleMerging(true);
    analysisManager->SetVerboseLevel(1);
    
    // Creating ntuples
    // -- run
    analysisManager->CreateNtuple("run", "truth");           // ntupleID = 0
    analysisManager->CreateNtupleIColumn("nEvents");         // | columnID = 0
    analysisManager->CreateNtupleSColumn("primaryName");     // | columnID = 1
    analysisManager->CreateNtupleIColumn("primaryPDG");      // | columnID = 2
    analysisManager->CreateNtupleDColumn("primaryE");        // | columnID = 3
    analysisManager->CreateNtupleDColumn("primaryP");        // | columnID = 4
    analysisManager->CreateNtupleDColumn("primaryDirX");     // | columnID = 5
    analysisManager->CreateNtupleDColumn("primaryDirY");     // | columnID = 6
    analysisManager->CreateNtupleDColumn("primaryDirZ");     // | columnID = 7
    
    // -- event
    analysisManager->CreateNtuple("event", "truth");         // ntupleID = 1
    analysisManager->CreateNtupleIColumn("evtID");           // | columnID = 0
    analysisManager->CreateNtupleIColumn("nTracks");         // | columnID = 1
    analysisManager->CreateNtupleIColumn("trkIDlist",        // |
                                         d_vec_trkIDlist);   // | columnID = 2
    
    // -- track
    analysisManager->CreateNtuple("track", "truth");         // ntupleID = 2
    analysisManager->CreateNtupleIColumn("evtID");           // | columnID = 0
    analysisManager->CreateNtupleIColumn("trkID");           // | columnID = 1
    analysisManager->CreateNtupleIColumn("trkParentID");     // | columnID = 2
    analysisManager->CreateNtupleIColumn("trkPDG");          // | columnID = 3
    analysisManager->CreateNtupleDColumn("trkEloss");        // | columnID = 4
    analysisManager->CreateNtupleDColumn("trkLen");          // | columnID = 5
    analysisManager->CreateNtupleDColumn("trkVtxX");         // | columnID = 6
    analysisManager->CreateNtupleDColumn("trkVtxY");         // | columnID = 7
    analysisManager->CreateNtupleDColumn("trkVtxZ");         // | columnID = 8
    analysisManager->CreateNtupleDColumn("trkStepX",         // |
                                         d_vec_trkStepX);    // | columnID = 9
    analysisManager->CreateNtupleDColumn("trkStepY",         // |
                                         d_vec_trkStepY);    // | columnID = 10
    analysisManager->CreateNtupleDColumn("trkStepZ",         // |
                                         d_vec_trkStepZ);    // | columnID = 11
    analysisManager->CreateNtupleDColumn("trkStepPx",        // |
                                         d_vec_trkStepPx);   // | columnID = 12
    analysisManager->CreateNtupleDColumn("trkStepPy",        // |
                                         d_vec_trkStepPy);   // | columnID = 13
    analysisManager->CreateNtupleDColumn("trkStepPz",        // |
                                         d_vec_trkStepPz);   // | columnID = 14
    analysisManager->CreateNtupleDColumn("trkStepGlobalTime",// |
                                         d_vec_trkStepGTime);// | columnID = 15
    
    // -- step
    analysisManager->CreateNtuple("step", "truth");          // ntupleID = 3
    analysisManager->CreateNtupleIColumn("evtID");           // | columnID = 0
    analysisManager->CreateNtupleIColumn("trkID");           // | columnID = 1
    analysisManager->CreateNtupleIColumn("stepPDG");         // | columnID = 2
    analysisManager->CreateNtupleSColumn("stepMaterial");    // | columnID = 3
    analysisManager->CreateNtupleSColumn("stepVolume");      // | columnID = 4
    analysisManager->CreateNtupleDColumn("stepEloss");       // | columnID = 5
    analysisManager->CreateNtupleDColumn("stepGlobalTime");  // | columnID = 6
    analysisManager->CreateNtupleDColumn("stepX");           // | columnID = 7
    analysisManager->CreateNtupleDColumn("stepY");           // | columnID = 8
    analysisManager->CreateNtupleDColumn("stepZ");           // | columnID = 9
    analysisManager->CreateNtupleDColumn("stepPx");          // | columnID = 10
    analysisManager->CreateNtupleDColumn("stepPy");          // | columnID = 11
    analysisManager->CreateNtupleDColumn("stepPz");          // | columnID = 12
    analysisManager->CreateNtupleIColumn("stepStatus");      // | columnID = 13
    analysisManager->CreateNtupleSColumn("stepProcessName"); // | columnID = 14

    //---------------------------------------------------------------//
    // The step status enum is defined in G4StepStatus.hh:
    // (geant4-src/source/track/include/G4StepStatus.hh)
    //
    // 0: Step reached the world boundary.
    // 1: Step defined by a geometry boundary.
    // 2: Step defined by a PreStepDoItVector.
    // 3: Step defined by a AlongStepDoItVector.
    // 4: Step defined by a PostStepDoItVector.
    // 5: Step defined by the user Step limit in the logical volume.
    // 6: Step defined by an exclusively forced PostStepDoIt process.
    // 7: Step not defined yet.
    //---------------------------------------------------------------//
    
    // Finishing
    analysisManager->FinishNtuple();
}


//------------------------------ FillEventNtuple ----------------------------//
void RunAction::FillEventNtuple()
{
    // Calling analysis manager to write ROOT file
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // Clearing the vector
    d_vec_trkIDlist.clear();
    
    // Looping over entries to separate event-like data
    G4int numberOfEntries = d_vec_eventID.size();
    
    G4int ntracks = 0;
    G4int thisTrackID = d_vec_trackID.at(0);
    G4int previousTrackID = thisTrackID;
    G4int thisEventID = d_vec_eventID.at(0);
    G4int previousEventID = thisEventID;
    
    // For (i == 0) in the loop
    d_vec_trkIDlist.push_back(thisTrackID);
    
    for (int i = 0; i < numberOfEntries; i++)
    {
        thisEventID = d_vec_eventID.at(i);
        thisTrackID = d_vec_trackID.at(i);
        
        // If it is the same event
        if (thisEventID == previousEventID)
        {
            // If a new track is found in the same event, store it
            if (thisTrackID != previousTrackID)
            {
                d_vec_trkIDlist.push_back(thisTrackID);
                previousTrackID = thisTrackID;
            }
            
            // Covering the extreme case of a run with only one event
            if (i == numberOfEntries - 1)
            {
                // Filling ntuple: event
                ntracks = d_vec_trkIDlist.size();
                
                analysisManager->FillNtupleIColumn(1, 0, previousEventID);
                analysisManager->FillNtupleIColumn(1, 1, ntracks);
                analysisManager->AddNtupleRow(1);
            }
        }
        
        // Case a new event is found
        else
        {
            // If eventID changes, previous event needs to be recorded...
            // Filling ntuple: event
            ntracks = d_vec_trkIDlist.size();
            
            analysisManager->FillNtupleIColumn(1, 0, previousEventID);
            analysisManager->FillNtupleIColumn(1, 1, ntracks);
            analysisManager->AddNtupleRow(1);
            
            // ... event data needs to be reset...
            d_vec_trkIDlist.clear();
            
            // ... we need to start recording the new event data...
            d_vec_trkIDlist.push_back(thisTrackID);
            
            // ... and need to make sure we can re-enter first if statement
            previousEventID = thisEventID;
        }
    }
}


//------------------------------ FillTrackNtuple ----------------------------//
void RunAction::FillTrackNtuple()
{
    // Calling analysis manager to write ROOT file
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // Clearing vectors that will be filled in the next for loop
    d_vec_trkStepX.clear();
    d_vec_trkStepY.clear();
    d_vec_trkStepZ.clear();
    d_vec_trkStepPx.clear();
    d_vec_trkStepPy.clear();
    d_vec_trkStepPz.clear();
    d_vec_trkStepGTime.clear();
    
    // Separating data withing different tracks
    G4int numberOfEntries = d_vec_trackID.size();
    
    G4int thisTrackID = d_vec_trackID.at(0);
    G4int previousTrackID = thisTrackID;
    G4int thisEventID = d_vec_eventID.at(0);
    G4int previousEventID = thisEventID;
    
    G4int trackParentID = 0;
    G4int trackPDG = 0;
    G4double trackEloss = 0;
    G4double trackLen = 0;
    
    
    for (int i = 0; i < numberOfEntries; i++)
    {
        thisTrackID = d_vec_trackID.at(i);
        thisEventID = d_vec_eventID.at(i);
        
        // Case step data is still from the same eventID
        if (thisEventID == previousEventID)
        {
            // If step is also from the same track, fill data in
            if (thisTrackID == previousTrackID)
            {
                trackParentID = d_vec_parentID.at(i);
                trackPDG = d_vec_pdg.at(i);
                trackEloss += d_vec_stepEloss.at(i);
                trackLen += d_vec_stepLen.at(i);
                d_vec_trkStepX.push_back(d_vec_stepPosition.at(i).getX());
                d_vec_trkStepY.push_back(d_vec_stepPosition.at(i).getY());
                d_vec_trkStepZ.push_back(d_vec_stepPosition.at(i).getZ());
                d_vec_trkStepPx.push_back(d_vec_stepMomentum.at(i).getX());
                d_vec_trkStepPy.push_back(d_vec_stepMomentum.at(i).getY());
                d_vec_trkStepPz.push_back(d_vec_stepMomentum.at(i).getZ());
                d_vec_trkStepGTime.push_back(d_vec_stepGTime.at(i));
            }
            
            // Covering the extreme case of a run with only one event
            if (i == numberOfEntries - 1)
            {
                // Filling ntuple: track
                G4double trackVtxX = d_vec_trkStepX.at(0);
                G4double trackVtxY = d_vec_trkStepY.at(0);
                G4double trackVtxZ = d_vec_trkStepX.at(0);
                
                analysisManager->FillNtupleIColumn(2, 0, previousEventID);
                analysisManager->FillNtupleIColumn(2, 1, previousTrackID);
                analysisManager->FillNtupleIColumn(2, 2, trackParentID);
                analysisManager->FillNtupleIColumn(2, 3, trackPDG);
                analysisManager->FillNtupleDColumn(2, 4, trackEloss);
                analysisManager->FillNtupleDColumn(2, 5, trackLen);
                analysisManager->FillNtupleDColumn(2, 6, trackVtxX);
                analysisManager->FillNtupleDColumn(2, 7, trackVtxY);
                analysisManager->FillNtupleDColumn(2, 8, trackVtxZ);
                
                analysisManager->AddNtupleRow(2);
            }
        }
        
        // Case a new event is found
        else
        {
            // If eventID changes, previous event needs to be recorded...
            // Filling ntuple: track
            G4double trackVtxX = d_vec_trkStepX.at(0);
            G4double trackVtxY = d_vec_trkStepY.at(0);
            G4double trackVtxZ = d_vec_trkStepX.at(0);
            
            analysisManager->FillNtupleIColumn(2, 0, previousEventID);
            analysisManager->FillNtupleIColumn(2, 1, previousTrackID);
            analysisManager->FillNtupleIColumn(2, 2, trackParentID);
            analysisManager->FillNtupleIColumn(2, 3, trackPDG);
            analysisManager->FillNtupleDColumn(2, 4, trackEloss);
            analysisManager->FillNtupleDColumn(2, 5, trackLen);
            analysisManager->FillNtupleDColumn(2, 6, trackVtxX);
            analysisManager->FillNtupleDColumn(2, 7, trackVtxY);
            analysisManager->FillNtupleDColumn(2, 8, trackVtxZ);
            
            analysisManager->AddNtupleRow(2);
            
            // ... track data needs to be reset...
            trackEloss = 0;
            trackLen = 0;
            d_vec_trkStepX.clear();
            d_vec_trkStepY.clear();
            d_vec_trkStepZ.clear();
            d_vec_trkStepPx.clear();
            d_vec_trkStepPy.clear();
            d_vec_trkStepPz.clear();
            d_vec_trkStepGTime.clear();
            
            // ... we need to start recording the new track data...
            trackPDG = d_vec_pdg.at(i);
            trackEloss += d_vec_stepEloss.at(i);
            trackLen += d_vec_stepLen.at(i);
            d_vec_trkStepX.push_back(d_vec_stepPosition.at(i).getX());
            d_vec_trkStepY.push_back(d_vec_stepPosition.at(i).getY());
            d_vec_trkStepZ.push_back(d_vec_stepPosition.at(i).getZ());
            d_vec_trkStepPx.push_back(d_vec_stepMomentum.at(i).getX());
            d_vec_trkStepPy.push_back(d_vec_stepMomentum.at(i).getY());
            d_vec_trkStepPz.push_back(d_vec_stepMomentum.at(i).getZ());
            d_vec_trkStepGTime.push_back(d_vec_stepGTime.at(i));
            
            // ... and need to make sure we can re-enter first if statement
            previousTrackID = thisTrackID;
            previousEventID = thisEventID;
        }
    }
}


//------------------------------- FillRunNtuple -----------------------------//
void RunAction::FillRunNtuple(const G4Run* run)
{
    // Calling analysis manager to write ROOT file
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // Filling ntuple: run
    G4String primaryName =
    b_primary->GetParticleGun()->GetParticleDefinition()->GetParticleName();
    G4int primaryPDG =
    b_primary->GetParticleGun()->GetParticleDefinition()->GetPDGEncoding();
    G4double primaryE = b_primary->GetParticleGun()->GetParticleEnergy();
    G4int numberOfEvents = run->GetNumberOfEvent();
    G4double primaryP = b_primary->GetParticleGun()->GetParticleMomentum();
    G4ParticleMomentum primaryDir =
    b_primary->GetParticleGun()->GetParticleMomentumDirection();
    
    
    // Filling in the data
    analysisManager->FillNtupleIColumn(0, 0, numberOfEvents);
    analysisManager->FillNtupleSColumn(0, 1, primaryName);
    analysisManager->FillNtupleIColumn(0, 2, primaryPDG);
    analysisManager->FillNtupleDColumn(0, 3, primaryE);
    analysisManager->FillNtupleDColumn(0, 4, primaryP);
    analysisManager->FillNtupleDColumn(0, 5, primaryDir.getX());
    analysisManager->FillNtupleDColumn(0, 6, primaryDir.getY());
    analysisManager->FillNtupleDColumn(0, 7, primaryDir.getZ());
    
    analysisManager->AddNtupleRow(0);
}


//------------------------------ FinishRootFile -----------------------------//
void RunAction::FinishRootFile()
{
    // Writing and closing ROOT file
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->Write();
    analysisManager->CloseFile();
}


//-------------------------- ClearStepVectorMembers -------------------------//
void RunAction::ClearStepVectorMembers()
{
    this->d_vec_eventID.clear();
    this->d_vec_trackID.clear();
    this->d_vec_parentID.clear();
    this->d_vec_pdg.clear();
    this->d_vec_stepEloss.clear();
    this->d_vec_stepLen.clear();
    this->d_vec_stepPosition.clear();
    this->d_vec_stepMomentum.clear();
    this->d_vec_stepGTime.clear();
}
