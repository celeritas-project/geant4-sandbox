//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/include/PythiaGenerator.hh
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#ifndef PythiaGenerator_h
#define PythiaGenerator_h 1


//C++
#include <iostream>

// Pythia8
#include "Pythia8/Pythia.h"

// Geant4
#include "G4String.hh"


class PythiaGenerator
{
public:
    Pythia8::Pythia b_pythia;
    
    PythiaGenerator();
    ~PythiaGenerator();
    
    void SelectInput(G4String pythiaInputFilename);
    void SetOutputName(G4String pythiaOutputFilename);
    void Run();
    
private:
    std::string pythiaInputFilename;
    std::string pythiaOutputFilename;
};


#endif
