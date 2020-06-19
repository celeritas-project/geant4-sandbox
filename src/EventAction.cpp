//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/src/EventAction.cpp
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#include "EventAction.hh"


//---------------------------- BeginOfEventAction ---------------------------//
void EventAction::BeginOfEventAction(const G4Event* event)
{
    // Particle gun only
    if (!b_primary->isPythiaHepevtInput)
    {
        // Initialisation per event
        d_eventID = event->GetEventID();
        d_trackEnergy = 0;
        d_trackLength = 0;
        
        //G4ThreeVector direction = RandomUnitaryThreeVector();
        G4ThreeVector direction(1., 0., 0.);
        //G4ThreeVector pos(-100*mm, -100*mm, -100*mm);
        //b_primary->GetParticleGun()->SetParticlePosition(pos);
        //b_primary->GetParticleGun()->SetParticleMomentumDirection(direction);
        G4double primaryE = b_primary->GetParticleGun()->GetParticleEnergy();
        
        b_runAction->FillRunEventData(primaryE, direction);
    }
}


//------------------------------- EventAction -------------------------------//
EventAction::EventAction(PrimaryGeneratorAction* primGenAct, RunAction* run)
: G4UserEventAction(), d_eventID(0), d_trackEnergy(0.), d_trackLength(0.),
b_primary(primGenAct), b_runAction(run)
{}


//------------------------------ ~EventAction -------------------------------//
EventAction::~EventAction()
{}


//----------------------------- EndOfEventAction ----------------------------//
void EventAction::EndOfEventAction(const G4Event* /*event*/)
{
    if (b_primary->isPythiaHepevtInput)
    {
        d_eventID++;
    }
}


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


//-------------------------- RandomUnitaryThreeVector -----------------------//
G4ThreeVector EventAction::RandomUnitaryThreeVector()
{      
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
            
    //G4ThreeVector direction(sign[0] * G4UniformRand(),
                            //sign[1] * G4UniformRand(),
                            //sign[2] * G4UniformRand());
    
    G4ThreeVector direction(1,
                            0,
                            0);
    return direction;
}
