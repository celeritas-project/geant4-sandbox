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

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();    
    virtual ~PrimaryGeneratorAction();
    
    virtual void GeneratePrimaries(G4Event* event);
    
    G4ParticleGun* GetParticleGun();
        
private:
    G4ParticleGun*  b_particleGun;
};


#endif
