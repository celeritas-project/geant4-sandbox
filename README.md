
Geant4-Sandbox
==============


# About:

Sandbox for running and testing Geant4. It loads a gdml input file, runs a
simulation, and produces a ROOT output file.


# Dependencies:

* Geant4 compiled with
  * Qt
  * OpenGL
  * Xerces
* ROOT
* Pythia8


# How to install:

From the sandbox folder:

```
$ mkdir build  
$ cd build  
$ cmake ..  
$ make
```


# How to run:

From the build folder:

```
$ ./g4-sandbox [options] [input.gdml]
```

## Options:

* `-v`: Opens the Qt GUI.
* `-n N`: Runs N events.  
* `-f [filename]`: Selects a user-specified ROOT output filename. If not
provided, the filename will be automatically defined as "rootout.root".   
* `-p [flag]`: Prints information according to the selected flag:   
  * `aux`: Auxiliary information.   
  * `phys`: Full list of physics constructors.   
* `-o`: Checks for overlaps.
* `-gen [pythiaInput] [hepevtOutput]`: Runs Pythia8 generator and produces
a Geant4 HEPEVT file.
* `-i [hepevtInput]`: Reads a Geant4 HEPEVT file as input for transporting
particles into the gdml geometry.

## Examples:  

`$ ./g4-sandbox -p aux input.gdml`: Opens the gdml, prints auxiliary information.  
`$ ./g4-sandbox -v -o -n 100 input.gdml`: Opens the gdml, checks for overlaps,
runs 100 events, and opens the GUI. Upon closing the GUI, the ROOT file is saved
to disk.  
`$ ./g4-sandbox -n 100 -f out.root input.gdml`: Opens the gdml, runs 100 events,
saves the ROOT file to disk as "out.root".  
`$ ./g4-sandbox -n 1 -gen pythiaInput.cmd hepevt.data -i hepevt.data input.gdml`:
Runs Pythia8 generator using the parameters specified in pythiaInput.cmd and
stores the result of the simulation in the hepevt.data file. Then, the code
loads the hepevt.data file as the input for the Geant4 simulation, runs 1 event,
and produces a ROOT output file.



# Files / folders description:

* **cms2018.gdml**: self-explanatory.
* **gui_menu.mac**: Adds options to the menu bar of the GUI session.
* **init.mac**: Macro with initialization commands for the GUI session.
* **pythiaInput.cmd**: Pythia8 input example, to be used with the `-gen` option.
* **slabsGeometry.gdml**: Basic geometry composed by 4 slabs of stainless steel.
* **vis.mac**: Macro for the GUI gdml visualization settings.
* **g4PhysicsTableParser/**: External code for parsing the ascii physics tables
produced by Geant4 and creating a single root output file. The folder also
includes the g4PhysicsTableReader, which shows how to read the data stored in
the ROOT file produced by the g4PhysicsTableParser.



# Notes / Issues

Currently, trying to view simulated events in the cms2018.gdml geometry using
`-v` takes an unsurmountable amount of time. Running events with the GUI is only
fine for small geometries.


___
**Stefano Tognini**  
**Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.**
