//Header for sensitive detectors to detect photons.

#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();

	track->SetTrackStatus(fStopAndKill); //When the photon enters the detector, it is killed and the track is not propagated further.
	//With this Z component is the same everywhere, thus the photons are always detected on the upper surface of the detector.

	G4StepPoint *preStepPoint = aStep->GetPreStepPoint(); //Information when photon enters SD.
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); //Information when photon leaves SD.

	G4ThreeVector posPhoton = preStepPoint->GetPosition(); //Position of photon upon entering SD.

	//G4cout << "Photon position: " << posPhoton << G4endl; //Shows positions of photons entering the SD in the terminal.

	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	
	G4int copyNo = touchable->GetCopyNumber();//From the physical volume, where the photon enters, we get the prevously defined copy number in the construction (j+i*100).

	//G4cout << "Copy number: " << copyNo << G4endl;

	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation(); //Gets the exact position of the detector in the world volume.
	
	G4cout << "Detector position: " << posDetector << G4endl;

	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID(); //Gets event number, basically the index of each event.

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0, evt); //First column filled with event number.
	man->FillNtupleDColumn(1, posDetector[0]);
	man->FillNtupleDColumn(2, posDetector[1]);
	man->FillNtupleDColumn(3, posDetector[2]);
	man->AddNtupleRow(0);


	return true;
}
