#------------------------------------------------------------------------------
# \file   pythia8-sandbox/pythiaInput.cmd
# \author Stefano Tognini
# \brief  Pythia8 input file used in the geant4-Sandbox.
# \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
#------------------------------------------------------------------------------


# Main
Main:numberOfEvents = 2

# Misc
Beams:eCM = 8000.
HardQCD:all = on
PhaseSpace:pTHatMin = 20.

# Init
Init:showProcesses = off
Init:showMultipartonInteractions = off
Init:showChangedParticleData = off

# Stat
Stat:showProcessLevel = off
Stat:showErrors = off
