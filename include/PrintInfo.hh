//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/include/PrintInfo.hh
 * \author Stefano Tognini
 * \brief  Printing functions for the sandbox.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


#ifndef PrintInfo_h
#define PrintInfo_h 1


// Geant4
#include "G4GDMLParser.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4GeometryManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4PhysListFactory.hh"
#include "G4PhysicsConstructorFactory.hh"


void PrintAuxList(const G4GDMLAuxListType* auxInfoList,
                  G4String prepend = "| ")
{
    for (std::vector<G4GDMLAuxStructType>::const_iterator aux_iterator =
         auxInfoList->begin();
         aux_iterator != auxInfoList->end();
         aux_iterator++)
    {
        G4String str = aux_iterator->type;
        G4String val = aux_iterator->value;
        G4String unit = aux_iterator->unit;
        
        G4cout << prepend << str << "\t" << val  << " " << unit <<
        G4endl;
        
        if (aux_iterator->auxList)
        {
            PrintAuxList(aux_iterator->auxList, prepend + "| ");
        }
    }
}


static void PrintAuxInfo(const G4GDMLParser &parser)
{
    G4cout << G4endl;
    
    const G4LogicalVolumeStore* logicalVolumeStore =
    G4LogicalVolumeStore::GetInstance();
    
    std::vector<G4LogicalVolume*>::const_iterator lv_iterator;
    
    for (lv_iterator = logicalVolumeStore->begin();
         lv_iterator != logicalVolumeStore->end();
         lv_iterator++)
    {
        G4GDMLAuxListType auxInfo =
        parser.GetVolumeAuxiliaryInformation(*lv_iterator);
        
        if (auxInfo.size() > 0)
            G4cout << "Auxiliary Information is found for Logical Volume "
            << (*lv_iterator)->GetName() << G4endl;
        
        PrintAuxList(&auxInfo);
    }
    
    G4cout << G4endl;
    G4cout << "Global auxiliary info:" << G4endl;
    G4cout << G4endl;
    PrintAuxList(parser.GetAuxList());
    G4cout << G4endl;
    
    
    G4VPhysicalVolume* world =
    const_cast<G4VPhysicalVolume*>(parser.GetWorldVolume());
    
    G4Navigator* navigator = new G4Navigator();
    navigator->SetWorldVolume(world);
    
    G4GeometryManager::GetInstance()
    ->CloseGeometry(navigator->GetWorldVolume());
    
    size_t g4NumberOfLogVol = G4LogicalVolumeStore::GetInstance()->size();
    size_t g4NumberOfPhysVol = G4PhysicalVolumeStore::GetInstance()->size();

    G4cout << "Number of volumes in " << world->GetName() << ":" << G4endl;
    G4cout << "  Logical : " << g4NumberOfLogVol << G4endl;
    G4cout << "  Physical: " << g4NumberOfPhysVol << G4endl;
    G4cout << G4endl;
}


static void PrintPhysicsList()
{
    G4cout << G4endl;
    G4cout << "List of all available Physics constructors:" << G4endl;
    G4cout << "-------------------------------------------" << G4endl;

    G4PhysicsConstructorRegistry* g4pctorFactory =
    G4PhysicsConstructorRegistry::Instance();
    
    g4pctorFactory->PrintAvailablePhysicsConstructors();
    
    G4cout << G4endl;
}
  

#endif
