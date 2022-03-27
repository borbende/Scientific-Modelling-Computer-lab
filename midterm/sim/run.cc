#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance(); //Can do this, since only singleton in simulation.

	man->OpenFile("outpput.csv");

	man->CreateNtuple("Hits", "Hits"); //Creates rows.
	man->CreateNtupleIColumn("fEvents"); //"I" stands for integer, fill columns.
	man->CreateNtupleDColumn("fX"); //"D" stands for double values.
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(0); //Ntuple no. 0 is finished. (First Ntuple)

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man->Write();
	man->CloseFile();

}


