//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   g4PhysicsTableParser/include/G4PhysicsTableParser.cpp
 * \author Stefano Tognini
 * \brief  G4PhysicsTableParser class description
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

// C++
#include <iostream>
#include <fstream>
#include <vector>

// Root
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"


class G4PhysicsTableParser
{
public:
    void CreateRootFile(std::string rootFilename);
    
    void AddPhysicsTableTree(std::string physTableAscFile);
    
    void ReplaceCharacters(std::string &aString,
                       std::string const search,
                       std::string const replace);
        
private:
    TFile * rootOutput;
    std::string rootOutputFilename;
    
    int tableSize;
    int vectorType;
    double edgeMin;
    double edgeMax;
    int numberOfNodes;
    int size;
    
    std::vector<double> binVector;  // Stores energy info
    std::vector<double> dataVector; // Stores XS/Eloss info
};
