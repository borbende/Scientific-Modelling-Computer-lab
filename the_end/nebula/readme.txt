After installing Geant4 and creating the simulation:

-open the terminal

-source the "geant4make.sh" file

-navigate to the NEBULA directory

-create a folder named build

-use commands: "cmake .." and then "make" to build the simulation

-start simulation with command: ./project_nebula "QBBC", where instead of QBBC you can use the other 4 physics lists listed in the project_nebula.cc file as well

-in the interface, type: /control/execute vis.mac

-then, type: /control/execute init_vis.mac

You can declare the number and type of particles you wish to run in the "init_vis.mac" file and their energy in this and in the "PrimaryGeneratorAction.cc" file.