// Template for other simulations also main file.

#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
	G4RunManager *runManager = new G4RunManager();
	
	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyActionInitialization());
	
	runManager->Initialize();
	
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	UImanager->ApplyCommand("/vis/open OGL");   //Activates display.
	UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
	//Changes initial position of look.
	UImanager->ApplyCommand("/vis/drawVolume"); //Draws the volume.
	UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true"); //Updates display.
	UImanager->ApplyCommand("/vis/scene/add/trajectories smooth"); //Shows particle trajectory.
	UImanager->ApplyCommand("/vis/scene/endofEventAction accumulate"); //Accumulates all events that happen in one run.
	
	
	ui->SessionStart();	
	
	
	return 0;
}
