//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   sandbox/main.cpp
 * \author Stefano Tognini
 * \brief  Sandbox  for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//


// Project
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PythiaGenerator.hh"
#include "PrintInfo.hh"

// Geant4
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4GDMLParser.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "G4VisExecutive.hh"
#include "FTFP_BERT.hh"
#include "G4VModularPhysicsList.hh"
#include "G4GenericPhysicsList.hh"
#include "G4PhysicsTable.hh"


int main(int argc, char** argv)
{
    //------------------------- The trivial solution ------------------------//
    if (argc == 1)
    {
        G4cout << "Check README.md for more info." << G4endl;
        return 0;
    }
    
    //--------------------------- Terminal inputs ---------------------------//
    bool isGUIEnable = false;
    bool isBeamOn = false;
    bool isPrintAux = false;
    bool isPrintPhysics = false;
    bool isOverlapCheck = false;
    bool isCustomRootFile = false;
    G4String rootFile;
    bool isPythiaGenOn = false;
    G4String pythiaGenInput;
    G4String pythiaGenOutput;
    bool isHepevtInput = false;
    G4String hepevtInput;
    int numberOfEvents = 1;
    
    for (int i = 1; i < argc; i++)
    {
        // Flag for enabling the GUI
        if (G4String(argv[i]) == "-v")
        {
            isGUIEnable = true;
        }
        
        // Flag for running a user-specified number of events
        if (G4String(argv[i]) == "-n")
        {
            isBeamOn = true;
            numberOfEvents = std::stoi(G4String(argv[i+1]), nullptr, 0);
        }
        
        // Flag for printing information
        if (G4String(argv[i]) == "-p")
        {
            // Auxiliary information
            if (G4String(argv[i+1]) == "aux")
            {
                isPrintAux = true;
            }
            
            // Physics constructor list
            if (G4String(argv[i+1]) == "phys")
            {
                isPrintPhysics = true;
            }
        }
        
        // Flag for checking for overlaps in the geometry
        if (G4String(argv[i]) == "-o")
        {
            isOverlapCheck = true;
        }
        
        // Flag for custom ROOT filename
        if (G4String(argv[i]) == "-f")
        {
            isCustomRootFile = true;
            rootFile = argv[i+1];
        }
        
        // Flag for Pythia generator
        if (G4String(argv[i]) == "-gen")
        {
            isPythiaGenOn = true;
            pythiaGenInput = argv[i+1];
            pythiaGenOutput = argv[i+2];
        }
        
        // Flag for Pythia hepevt input
        if (G4String(argv[i]) == "-i")
        {
            isHepevtInput = true;
            hepevtInput = argv[i+1];
        }
    }
    
    
    //------------------------------ Run Manager ----------------------------//
#ifdef G4MULTITHREADED
    G4int nThreads = 4;
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(nThreads);
#else
    auto runManager = new G4RunManager;
#endif
    
    
    //------------------------ Detector Construction ------------------------//
    // Fetching the GDML input file
    std::string fileName = argv[argc-1];
    
    G4GDMLParser parser;
    
    if (isOverlapCheck)
    {
        parser.SetOverlapCheck(true);
    }
    
    parser.Read(fileName);
    
    if (isPrintAux)
    {
        PrintAuxInfo(parser);
    }
    
    G4VPhysicalVolume* worldPhysicalVolume = parser.GetWorldVolume();
    auto detConstruction = new DetectorConstruction(worldPhysicalVolume);
    
    runManager->SetUserInitialization(detConstruction);
    
    
    //----------------------------- Physics list ----------------------------//
    // Printing full list of physics constructors
    if (isPrintPhysics)
    {
        PrintPhysicsList();
    }
    
    // Selecting the desired physics packages
    // Currently adding only EM physics
    std::vector<G4String>* physicsConstructor = new std::vector<G4String>;
    physicsConstructor->push_back("G4EmStandardPhysics");
    
    // Building the Physics List
    G4VModularPhysicsList* physicsList =
    new G4GenericPhysicsList(physicsConstructor);
    
    // For a full Physics List, use the following pointer instead
    //G4VModularPhysicsList* physicsList = new FTFP_BERT;
    
    // Initializing the Physics List
    runManager->SetUserInitialization(physicsList);
    
    
    //--------------------------- PythiaGenerator ---------------------------//
    if (isPythiaGenOn)
    {
        PythiaGenerator pythia;
        
        pythia.SelectInput(pythiaGenInput);
        pythia.SetOutputName(pythiaGenOutput);
        pythia.Run();
    }
    
    //------------------------ Action Initialization ------------------------//
    // The ActionInitialization class is responsible for calling all the
    // remaining classes:
    //
    // - PrimaryGeneratorAction: Sets up the particle gun or Pythia input.
    // - RunAction: Opens ROOT file, creates ntuples at the beginning of the
    //   run, and writes/closes the ROOT file at the end.
    // - EventAction: Records event-like data into the ntuples.
    // - SteppingAction: Records particle-step-like data into the ntuples.
    
    ActionInitialization* actionInitialization = new ActionInitialization();
    
    if (isCustomRootFile)
    {
        actionInitialization->SetRootOutputFile(rootFile);
    }
    if (isHepevtInput)
    {
        actionInitialization->SetPythiaInputFile(hepevtInput);
    }
    
    runManager->SetUserInitialization(actionInitialization);
    
    
    //------------------------------ UI Manager -----------------------------//
    auto UImanager = G4UImanager::GetUIpointer();
    
    // Initializing the UIManager kernel
    UImanager->ApplyCommand("/run/initialize");
    
    // Uncoment to print loaded physics list
    //UImanager->ApplyCommand("/process/em/verbose 1");
    
    
    //--------------------------------- GUI ---------------------------------//
    if (isGUIEnable)
    {
        // Visualization manager
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
        
        // Starting user interface
        G4UIExecutive* userInterface = nullptr;
        userInterface = new G4UIExecutive(argc, argv);
        
        // Executing interface config macros
        UImanager->ApplyCommand("/control/execute init.mac");
        UImanager->ApplyCommand("/control/execute vis.mac");
        UImanager->ApplyCommand("/control/execute gui_menu.mac");
        
        // Running events
        if (isBeamOn)
        {
            G4String beamOn = "/run/beamOn ";
            beamOn.append(G4String(std::to_string(numberOfEvents)));
            UImanager->ApplyCommand(beamOn);
        }
        
        // Opening GUI session
        userInterface->SessionStart();
        
        // Cleaning up after closing session
        delete userInterface;
        delete visManager;
    }
    
    
    //-------------------------- Terminal (no GUI) --------------------------//
    else
    {
        if (isBeamOn)
        {
            runManager->BeamOn(numberOfEvents);
        }
    }
    
    
    //------------------------- Dumping physics tables ----------------------//
    // See PrintInfo.hh
    
    // Using UImanager
    //DumpPhysicsTables("/path/to/folder");
    
    // Looping over particles and processes manually
    //DumpPhysicsTablesManually("/path/to/folder");
    
    
    //---------------------------- Job termination --------------------------//
    // User actions, physics list, and detector construction are owned and
    // deleted by the run manager
    delete runManager;
}
