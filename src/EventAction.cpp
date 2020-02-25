//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/src/EventAction.cpp
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


// Project
#include "EventAction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "Analysis.hh"

// Geant4
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"


//---------------------------- BeginOfEventAction ---------------------------//
void EventAction::BeginOfEventAction(const G4Event * event)
{
    // Initialisation per event
    d_eventID = event->GetEventID();
    d_trackEnergy = 0;
    d_trackLength = 0;
    
    // Randomizing particle direction
    G4int sign[3];
    
    for (int i = 0; i < 3; i++)
    {
        if (G4UniformRand() > 0.5)
        {
            sign[i] = 1;
        }
        else
        {
            sign[i] = -1;
        }
    }
        
    G4ThreeVector direction(sign[0] * G4UniformRand(),
                            sign[1] * G4UniformRand(),
                            sign[2] * G4UniformRand());
    
    b_primary->GetParticleGun()->SetParticleMomentumDirection(direction);
    G4double primaryE = b_primary->GetParticleGun()->GetParticleEnergy();

    b_runAction->FillRunEventData(primaryE, direction);
}


//------------------------------- EventAction -------------------------------//
EventAction::EventAction(PrimaryGeneratorAction* primGenAct, RunAction* run)
: G4UserEventAction(), d_trackEnergy(0.), d_trackLength(0.),
b_primary(primGenAct), b_runAction(run)
{}


//------------------------------ ~EventAction -------------------------------//
EventAction::~EventAction()
{}


//----------------------------- EndOfEventAction ----------------------------//
void EventAction::EndOfEventAction(const G4Event* /*event*/)
{}


//--------------------------------- AddStep ---------------------------------//
void EventAction::AddStep(G4double &stepdEdX, G4double &stepLength)
{
    d_trackEnergy += stepdEdX;
    d_trackLength += stepLength;
}


//-------------------------------- GetEventID -------------------------------//
G4int EventAction::GetEventID()
{
    return d_eventID;
}
