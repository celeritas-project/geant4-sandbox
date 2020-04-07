//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/src/PythiaGenerator.cpp
 * \author Stefano Tognini
 * \brief  Sandbox for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


// Project
#include "PythiaGenerator.hh"


//----------------------------- PythiaGenerator -----------------------------//
PythiaGenerator::PythiaGenerator()
{}


//---------------------------- ~PythiaGenerator -----------------------------//
PythiaGenerator::~PythiaGenerator()
{}


//------------------------------- SelectInput -------------------------------//
void PythiaGenerator::SelectInput(G4String pythiaInputFilename)
{
    this->pythiaInputFilename = pythiaInputFilename;
}


//------------------------------ SetOutputName ------------------------------//
void PythiaGenerator::SetOutputName(G4String pythiaOutputFilename)
{
    this->pythiaOutputFilename = pythiaOutputFilename;
}


//----------------------------------- Run -----------------------------------//
void PythiaGenerator::Run()
{
    // Creating hepevt output file
    std::ofstream hepevtOut(this->pythiaOutputFilename, std::ios::out);
    
    // Loading configs from the input file
    this->b_pythia.readFile(this->pythiaInputFilename);
    
    // Fetching the number of events from the input file
    int numberOfEvents = this->b_pythia.mode("Main:numberOfEvents");
    
    this->b_pythia.init();
    
    //-----------------------------------------------------------------------//
    // Running events and writing them to the hepevt output file
    //-----------------------------------------------------------------------//
    //                             HEPEVT Format
    //                            ---------------
    // The full HEPEVT format is NOT used by the G4HEPEvtInterface.
    // Full and Geant4 formats are shown below, with the terms used by the
    // Geant4 interface marked with an X.
    //
    // [ ] eventNumber [x] numberOfParticles
    //  status PDG mother1 mother2 daughter2 daughter2 Px Py Pz E m x y z t
    // [  x     x                      x         x     x  x  x    x        ]
    //
    // The (x, y, z) vertex is not included in the HEPEVT file and is
    // specified by the PrimaryGeneratorAction::GeneratePrimaries() method.
    //-----------------------------------------------------------------------//
    
    for (int event_i = 0; event_i < numberOfEvents; event_i++)
    {
        if (!this->b_pythia.next()) continue;
        
        hepevtOut << "\t" <<this->b_pythia.event.size() << std::endl;
        
        for (int particle_i = 0; particle_i < this->b_pythia.event.size();
             particle_i++)
        {
            if (this->b_pythia.event[particle_i].isFinal())
            {
                hepevtOut << b_pythia.event[particle_i].status();
                hepevtOut << " ";
                hepevtOut << this->b_pythia.event[particle_i].id();
                hepevtOut << " ";
                hepevtOut << this->b_pythia.event[particle_i].daughter1();
                hepevtOut << " ";
                hepevtOut << this->b_pythia.event[particle_i].daughter2();
                hepevtOut << " ";
                hepevtOut << this->b_pythia.event[particle_i].px();
                hepevtOut << " ";
                hepevtOut << this->b_pythia.event[particle_i].py();
                hepevtOut << " ";
                hepevtOut << this->b_pythia.event[particle_i].pz();
                hepevtOut << " ";
                hepevtOut << this->b_pythia.event[particle_i].m();
                hepevtOut << std::endl;
            }
        } /* end of particle loop */
    } /* end of event loop */
    
    // Closing hepevt output file
    hepevtOut.close();
}

