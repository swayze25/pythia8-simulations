# pp Collisions via PYTHIA8

### Beam & Energies :

Simulation of proton-proton collisions at LHC energies via PYHTIA8 event generator is done and the output is stored in the root file:
* int nEvents = 10000; (can be changed)
* idA = 2212 & idB = 2212 (proton-proton beams)
* eA  = 7000. & eB  = 7000. & eCM  = 7000. (default LHC values)
* HardQCD:all = on

1. The Event data (4mom, eta, rap) is stored in eventdata.root and eventdata as a log file
2. Macro eventgen.cc creates pp collision using Pythia8 libraries, linked with makefile.
3. Makefiles used to import the relevant ROOT and Pythia headers and libraries
4. run.csh for shell scripting/automation

--------------------------------------------------------------------------------------------

### To Run:

1. Make sure your PYTHIA is built with ROOT
2. Copy the Makefile and Makefile.inc from the examples folder of your PYTHIA directory to this folder (replace the Makefiles in this repository with your own)
3. type on the Terminal : ./run.csh
