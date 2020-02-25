//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/include/RunAction.hh
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#ifndef RunAction_h
#define RunAction_h 1


// C++
#include <vector>

// Geant4
#include "G4UserRunAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "Analysis.hh"


class G4Run;
class PrimaryGeneratorAction;
class EventAction;


class RunAction : public G4UserRunAction
{
public:
    RunAction(PrimaryGeneratorAction* primGenAct);
    virtual ~RunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run* run);
    
    void FillRunStepData(G4int &eventID,
                         G4int &trackID,
                         G4int &parentID,
                         G4int &pdg,
                         G4double &Eloss,
                         G4double &stepLen,
                         G4ThreeVector &stepPosition,
                         G4ThreeVector &stepMomentum,
                         G4double &globalTime);
    
    void FillRunEventData(G4double &primaryE,
                          G4ThreeVector &primaryDir);
    
private:
    PrimaryGeneratorAction* b_primary;
    
    // Event
    std::vector<G4double> d_vec_primaryE;
    std::vector<G4ThreeVector> d_vec_primaryDir;
    std::vector<G4int> d_vec_trkIDlist;

    
    // Track
    std::vector<G4double> d_vec_trkStepX;
    std::vector<G4double> d_vec_trkStepY;
    std::vector<G4double> d_vec_trkStepZ;
    std::vector<G4double> d_vec_trkStepPx;
    std::vector<G4double> d_vec_trkStepPy;
    std::vector<G4double> d_vec_trkStepPz;
    std::vector<G4double> d_vec_trkStepGTime;
    
    // Step
    std::vector<G4int> d_vec_eventID;
    std::vector<G4int> d_vec_trackID;
    std::vector<G4int> d_vec_parentID;
    std::vector<G4int> d_vec_pdg;
    std::vector<G4double> d_vec_stepEloss;
    std::vector<G4double> d_vec_stepLen;
    std::vector<G4ThreeVector> d_vec_stepPosition;
    std::vector<G4ThreeVector> d_vec_stepMomentum;
    std::vector<G4double> d_vec_stepGTime;
    
    void CreateRootFile(G4String rootFileName);
    void CreateRootNtuples();
    void FillEventNtuple();
    void FillTrackNtuple();
    void FillRunNtuple(const G4Run* run);
    void FinishRootFile();
    void ClearStepVectorMembers();
    G4double CalculatePrimaryMomentum();
};


#endif

