//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/include/ActionInitialization.hh
 * \author Stefano Tognini
 * \brief  Sandbox program for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#ifndef ActionInitialization_h
#define ActionInitialization_h 1


// Geant4
#include "G4VUserActionInitialization.hh"


class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization();
    virtual ~ActionInitialization();
    
    virtual void Build() const;
    
    // In case of multithread
    virtual void BuildForMaster() const;
};


#endif


