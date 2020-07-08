//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   g4PhysicsTableParser/g4PhysicsTableReader.cpp
 * \author Stefano Tognini
 * \brief  Code for reading the root output from the g4PhysicsTableParser
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

// C++
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"


int main(int argc, char **argv)
{
    // Covering any wrong number of inputs
    if (argc != 2)
    {
        std::cout << "Usage: ./g4PhysicsTableReader file.root" << std::endl;
        return 0;
    }
        
    // Opening root file
    TFile *rootInput = new TFile(argv[1], "open");
    
    // Getting list of keys -- i.e. list of elements in rootInput
    TList *list = rootInput->GetListOfKeys();

    // Get list iterator
    TIter iter(list->MakeIterator());
    
    // Creating the variables to reference the TTree leaves
    double edgeMin, edgeMax;
    int numberOfNodes, vectorType;
    std::vector<double> *binVector = 0;
    std::vector<double> *dataVector = 0;
    
    // Looping over the objects found in rootInput
    while (TObject* object = iter())
    {
        // Getting the object's name and type
        TKey* key = (TKey*)object;
        std::string keyName = key->GetName();
        std::string keyType = key->GetClassName();
        
        // Safeguard to avoid reading a non-tree object
        // Just in case we add something else to the file in the future
        if (keyType != "TTree") continue;
        
        // Creating a tree pointer
        TTree *tree = (TTree*)rootInput->Get(keyName.c_str());
        
        // Setting up std::cout
        std::cout << std::setprecision(3);
        std::cout << std::fixed;
        std::cout << std::scientific;
        
        // Looping over the tree
        long long numberOfTreeEntries = tree->GetEntries();
        
        std::cout << keyName << std::endl;
        std::cout << " | tableSize: " << numberOfTreeEntries << std::endl;
        
        for (int i = 0; i < numberOfTreeEntries; i++)
        {
            tree->GetEntry(i);
            
            // Fetching the values in each tree leaf
            edgeMin       = tree->GetLeaf("edgeMin")->GetValue();
            edgeMax       = tree->GetLeaf("edgeMax")->GetValue();
            numberOfNodes = tree->GetLeaf("numberOfNodes")->GetValue();
            vectorType    = tree->GetLeaf("vectorType")->GetValue();
            tree->SetBranchAddress("binVector", &binVector);
            tree->SetBranchAddress("dataVector", &dataVector);

            // Printing the data
            std::cout << " |" << std::endl;
            std::cout << " | --------------------------" << std::endl;
            std::cout << " | ENTRY " << i << std::endl;
            std::cout << " | --------------------------" << std::endl;
            std::cout << " | edgeMin       : " << edgeMin << std::endl;
            std::cout << " | edgeMax       : " << edgeMax << std::endl;
            std::cout << " | numberOfNodes : " << numberOfNodes << std::endl;
            std::cout << " | vectorType    : " << vectorType << std::endl;
            std::cout << " | binVector      dataVector" << std::endl;
            
            // Looping over binVector and dataVector
            for (int j = 0; j < binVector->size(); j++)
            {
                std::cout << " | | ";
                std::cout << std::left << std::setw(12) << std::setfill(' ');
                std::cout << binVector->at(j);
                std::cout << " | " << dataVector->at(j) << std::endl;
            }
        }
        
        std::cout << std::endl;
        std::cout << std::endl;
    }
}
