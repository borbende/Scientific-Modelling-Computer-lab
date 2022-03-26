//Physics list source file.

#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
	RegisterPhysics (new G4EmStandardPhysics());
	//Electromagnetic interaction.
	RegisterPhysics (new G4OpticalPhysics());
	//Optical photons included.
}

MyPhysicsList::~MyPhysicsList()
{}
