//Detector construction class source file. Cherenkov detector.

#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	//Get predefined parameters for materials.
	
	G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
	//Silicon molecule (name, density of material, number of components)
	SiO2->AddElement(nist->FindOrBuildElement("Si"), 1); //Elements.
	SiO2->AddElement(nist->FindOrBuildElement("O"), 2);
	
	G4Material *H2O = new G4Material("H2O", 1*g/cm3, 2);
	//Water molecule (name, density of material, number of components)
	H2O->AddElement(nist->FindOrBuildElement("H"), 2); //Elements.
	H2O->AddElement(nist->FindOrBuildElement("O"), 1);
	
	G4Element *C = nist->FindOrBuildElement("C"); //Carbon molecule.
	
	G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
	//Aerogel, that has the 3 above components.
	Aerogel->AddMaterial(SiO2, 62.5*perCent);
	Aerogel->AddMaterial(H2O, 37.4*perCent);
	Aerogel->AddElement(C, 0.1*perCent);
	
	G4double energy[2] = {1.239841939*eV/0.3, 1.239841939*eV/0.7};
	//Defining energy and doing conversion from wavelength to energy (blue light, red light)
	
	G4double rindexAerogel[2] = {1.1, 1.1};
	//Refractive index of AeroGel
	
	
	G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
	//Material properties (name, energy, refractive index, number of values in array)
	
	Aerogel->SetMaterialPropertiesTable(mptAerogel);
	
	
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR"); 
	//Searches for material G4_AIR and defines it as worldMat.
	
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	//1 meter height, width and length box shaped world volume. (Half lengths)

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	//Creates the logic volume from the previous parameters.
	
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	//Physical volumeparameters = (rotation, center, logical volume, name, mother volume, boolean operations, copy number, should check for overlaps or not)
	
	G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
	
	G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");
	
	G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);
	
	
	
	return physWorld; //Has to return highest mother volume.

}

