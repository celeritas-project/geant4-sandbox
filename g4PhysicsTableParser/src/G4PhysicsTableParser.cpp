//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   g4PhysicsTableParser/src/G4PhysicsTableParser.cpp
 * \author Stefano Tognini
 * \brief  G4PhysicsTableParser class implementation
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#include "G4PhysicsTableParser.hh"


//------------------------------ CreateRootFile -----------------------------//
void G4PhysicsTableParser::CreateRootFile(std::string rootFilename)
{
    this->rootOutputFilename = rootFilename;
    this->rootOutput = new TFile(rootFilename.c_str(), "recreate");
    rootOutput->Write();
    rootOutput->Close();
    
    std::cout << "Created " << rootFilename << std::endl;
}


//---------------------------- AddPhysicsTableTree --------------------------//
void G4PhysicsTableParser::AddPhysicsTableTree(std::string physTableAscFile)
{
    // Opening input
    std::ifstream inputFile;
    inputFile.open(physTableAscFile, std::ios::in);
    
    // Updating the physTableAscFile string to become the TTree name
    // Removing .asc at the end
    physTableAscFile.erase(physTableAscFile.length() - 4);
    
    // Removing the directory path, if any
    std::size_t lastPathSlash = physTableAscFile.find_last_of("/");
    physTableAscFile = physTableAscFile.substr(lastPathSlash + 1);
    
    // Replacing special characters. ROOT TTrees do not bode well with them
    ReplaceCharacters(physTableAscFile, ".", "_");
    ReplaceCharacters(physTableAscFile, "+", "Plus");
    ReplaceCharacters(physTableAscFile, "-", "Minus");
    
    // Updating root file
    rootOutput = new TFile(rootOutputFilename.c_str(), "update");
    
    // Creating the TTree
    TTree *tree = new TTree(physTableAscFile.c_str(),
                            physTableAscFile.c_str());
    
    tree->Branch("edgeMin", &edgeMin, "edgeMin/D");
    tree->Branch("edgeMax", &edgeMax, "edgeMax/D");
    tree->Branch("numberOfNodes", &numberOfNodes, "numberOfNodes/I");
    tree->Branch("vectorType", &vectorType, "vectorType/I");
    tree->Branch("binVector", &binVector);
    tree->Branch("dataVector", &dataVector);
    
    // Reading file
    inputFile >> this->tableSize;
    
    for (int i = 0; i < this->tableSize; i++)
    {
        binVector.clear();
        dataVector.clear();
        
        inputFile >> this->vectorType;
        inputFile >> this->edgeMin >> this->edgeMax >> this->numberOfNodes;
        inputFile >> this->size;
        
        if (this->size == 0)
        {
            std::cout << "Size 0" << std::endl;
            this->rootOutput->Close();
            inputFile.close();
            return;
        }
        
        double bin, data;
        for (int j = 0; j < size; j++)
        {
            inputFile >> bin >> data;
            
            this->binVector.push_back(bin);
            this->dataVector.push_back(data);
        }
        
        tree->Fill();
    }
    
    // Writing and closing files
    this->rootOutput->Write();
    this->rootOutput->Close();
    inputFile.close();
    
    std::cout << "  Added " << physTableAscFile << std::endl;
}


//---------------------------- ReplaceCharacters ----------------------------//
void G4PhysicsTableParser::ReplaceCharacters(std::string &aString,
                                         std::string const search,
                                         std::string const replace)
{
    size_t position = 0;
    
    while ((position = aString.find(search, position)) != std::string::npos)
    {
        aString.replace(position, search.length(), replace);
        position += replace.length();
    }
}
