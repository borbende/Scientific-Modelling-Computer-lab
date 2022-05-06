#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "Analysis.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"



SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}



SteppingAction::~SteppingAction()
{}



void SteppingAction::UserSteppingAction(const G4Step* step)
{
  const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  std::vector<std::string> rod_names = detectorConstruction->get_rod_names();

  const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();   //Needed to get the event ID-s.

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  // X,y,Z coordinates
  G4ThreeVector XYZ = step->GetTrack()->GetPosition();
  G4double X = XYZ[0];
  G4double Y = XYZ[1];
  G4double Z = XYZ[2];

  // 1. column: energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();

  // 2. column: name of the particle
  G4String partStep = step->GetTrack()->GetParticleDefinition()->GetParticleName();

  // 3. column: name of the volume the particle currently in
  G4String volumeStep = volume->GetName();

  // 4. column: name of the process
  G4String procStep = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

  // 5. column: track ID
  G4int parttrack = step->GetTrack()->GetTrackID();

  // 6. column: event ID
  G4int partev = evt->GetEventID();

  // At the end of every step, get analysis manager and fill it with values
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Fill ntuple
  analysisManager->FillNtupleDColumn(0, X);
  analysisManager->FillNtupleDColumn(1, Y);
  analysisManager->FillNtupleDColumn(2, Z);
  analysisManager->FillNtupleDColumn(3, edepStep);
  analysisManager->FillNtupleSColumn(4, partStep);
  analysisManager->FillNtupleSColumn(5, volumeStep);
  analysisManager->FillNtupleSColumn(6, procStep);
  analysisManager->FillNtupleIColumn(7, parttrack);
  analysisManager->FillNtupleIColumn(8, partev);
  analysisManager->AddNtupleRow();
}

