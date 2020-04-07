//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/include/PrimaryGeneratoryAction.hh
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1


// Geant4
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"


class G4ParticleGun;
class G4Event;
class G4VPrimaryGenerator;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    bool isPythiaHepevtInput;

    PrimaryGeneratorAction(bool const &isPythiaHepevtInput,
                           G4String pythiaInputFile);
    
    virtual ~PrimaryGeneratorAction();
    
    virtual void GeneratePrimaries(G4Event* event);
    
    G4ParticleGun* GetParticleGun();
    G4VPrimaryGenerator* GetHepevt();
    
private:
    G4ParticleGun*  b_particleGun;
    G4VPrimaryGenerator* b_hepevt;
};


#endif
