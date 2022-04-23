//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "Analysis.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  std::vector<std::string> rod_names = detectorConstruction->get_rod_names();

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
  analysisManager->AddNtupleRow();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

