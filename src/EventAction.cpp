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
}


//------------------------------- EventAction -------------------------------//
EventAction::EventAction()
: G4UserEventAction(), d_trackEnergy(0.), d_trackLength(0.)
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
