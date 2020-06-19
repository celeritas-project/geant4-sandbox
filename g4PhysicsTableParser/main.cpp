//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   g4PhysicsTableParser/main.cpp
 * \author Stefano Tognini
 * \brief  Code for parsing Geant4 ascii physics tables
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#include "G4PhysicsTableParser.hh"


int main(int argc, char **argv)
{
    //---------------------- Wrong number of arguments ----------------------//
    if (argc != 3)
    {
        std::cout << "Usage: ./G4PhysicsTableParser ";
        std::cout << "physicsTablesList.txt rootOutput.root";
        std::cout << std::endl;
        return 0;
    }
    
    //--------------------- Opening physics tables list ---------------------//
    std::ifstream inputList;
    inputList.open(argv[1], std::ios::in);
    
    if (!inputList)
    {
        std::cout << "[ERROR] Could not open input file" << std::endl;
        return 1;
    }
    
    std::cout << "Opened " << argv[1] << std::endl;
    
    //--------- Starting parser and looping over the list of files ----------//
    G4PhysicsTableParser parser;
    parser.CreateRootFile(argv[2]);
    
    std::string filename;
    while (std::getline(inputList, filename))
    {
        parser.AddPhysicsTableTree(filename);
    }
    
    inputList.close();
    std::cout << "Done" << std::endl;
    return 0;
}
