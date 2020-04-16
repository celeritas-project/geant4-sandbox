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
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4HEPEvtInterface.hh"



//------------------------- PrimaryGeneratorAction --------------------------//
PrimaryGeneratorAction::PrimaryGeneratorAction(bool const
                                               &isPythiaInput,
                                               G4String pythiaInputFile)
: G4VUserPrimaryGeneratorAction(), isPythiaHepevtInput(isPythiaInput),
 b_particleGun(nullptr)
{
    // Pythia8 HEPEVT input file
    if (isPythiaHepevtInput)
    {
        b_hepevt = new G4HEPEvtInterface(pythiaInputFile, 1);
    }

    // Particle gun
    else
    {
        // Creating the particle gun
        G4int numberOfParticles = 1;
        b_particleGun = new G4ParticleGun(numberOfParticles);
        
        // Defining a standard particle ID, direction, energy, and position
        // WARNING: Values may be overwritten by
        //          EventAction::BeginOfEventAction
        G4ParticleDefinition* particle;
        particle = G4ParticleTable::GetParticleTable()->FindParticle("e-");
        
        b_particleGun->SetParticleDefinition(particle);
        b_particleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
        b_particleGun->SetParticleEnergy(1 * TeV);
        b_particleGun->SetParticlePosition(G4ThreeVector());
    }
    
    // slabsGeometry.gdml center is at (0, 0, 9*cm)
    // cms2018.gdml center is at (0, 0, 0)
}


//------------------------- ~PrimaryGeneratorAction -------------------------//
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    if (isPythiaHepevtInput)
    {
        delete b_hepevt;
    }
    
    // Particle gun
    else
    {
        delete b_particleGun;
    }
}


//--------------------------- GeneratePrimaries -----------------------------//
// Function called at the begining of each event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    if (isPythiaHepevtInput)
    {
        b_hepevt->SetParticlePosition(G4ThreeVector());
        b_hepevt->GeneratePrimaryVertex(event);
    }
    // Particle gun
    else
    {
        b_particleGun->GeneratePrimaryVertex(event);
    }
}


//---------------------------- GetParticleGun -------------------------------//
G4ParticleGun* PrimaryGeneratorAction::GetParticleGun()
{
    return b_particleGun;
}


//------------------------------ GetHepevt ----------------------------------//
G4VPrimaryGenerator* PrimaryGeneratorAction::GetHepevt()
{
    return b_hepevt;
}
