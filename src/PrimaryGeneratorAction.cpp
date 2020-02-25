//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/src/PrimaryGeneratorAction.cpp
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


// Project
#include "PrimaryGeneratorAction.hh"

// Geant4
#include "G4RunManager.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


//------------------------- PrimaryGeneratorAction --------------------------//
PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(), b_particleGun(nullptr)
{
    // Creating the particle gun
    G4int numberOfParticles = 1;
    b_particleGun = new G4ParticleGun(numberOfParticles);
    
    // Defining a standard particle ID, direction, energy, and position
    // WARNING: Values may be overwritten by EventAction::BeginOfEventAction
    auto particle =
    G4ParticleTable::GetParticleTable()->FindParticle("proton");
    
    b_particleGun->SetParticleDefinition(particle);
    b_particleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    b_particleGun->SetParticleEnergy(0.5 * GeV);
    b_particleGun->SetParticlePosition(G4ThreeVector(0, 0., +9 * cm));
}


//------------------------- ~PrimaryGeneratorAction -------------------------//
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete b_particleGun;
}


//--------------------------- GeneratePrimaries -----------------------------//
// Function called at the begining of each event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    b_particleGun->GeneratePrimaryVertex(event);
}


//---------------------------- GetParticleGun -------------------------------//
G4ParticleGun* PrimaryGeneratorAction::GetParticleGun()
{
    return b_particleGun;
}
