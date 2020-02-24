
README
======


About:
------

Sandbox for running and testing Geant4. It loads a gdml input file, runs events
using the particle gun, and produces a ROOT output file.


Dependencies:
-------------

* Geant4 compiled with
  * Qt
  * OpenGL
  * Xerces
* ROOT


How to install:
---------------

From the sandbox folder:

```
$ mkdir build  
$ cd build  
$ cmake ..  
$ make
```


How to run:
-----------

From the build folder:

```
$ ./main [options] [input.gdml]
```

Options:

* `-v`: Opens the Qt GUI.
* `-n N`: Runs N events.  
* `-p [flag]`: Prints information according to the selected flag:   
  * `aux`: Auxiliary information.   
  * `phys`: Full list of physics constructors.   
* `-o`: Checks for overlaps.

Examples:  

`$ ./main -p aux input.gdml`: Opens the gdml, prints auxiliary information.  
`$ ./main -v -o -n 100 input.gdml`: Opens the gdml, checks for overlaps, runs 100 events, and opens the GUI. Upon closing the GUI, the ROOT file is saved to disk.  
`$ ./main -n 100 input.gdml`: Opens the gdml, runs 100 events, saves the ROOT file to disk.


Extra files:
------------

* slabsGeometry.gdml: Basic geometry composed by 4 slabs of stainless steel.
* cms2018.gdml: self-explanatory.

___
**Stefano Tognini**  
**Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.**
