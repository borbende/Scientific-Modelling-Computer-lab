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
	G4double rindexWorld[2] = {1.0, 1.0};
	//Refractive index of the world (now air inside) to make the photons propagate through to the SD.
	
	
	G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
	//Material properties (name, energy, refractive index, number of values in array)
	
	Aerogel->SetMaterialPropertiesTable(mptAerogel);
	
	
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR"); 
	//Searches for material G4_AIR and defines it as worldMat.

	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

	worldMat->SetMaterialPropertiesTable(mptWorld);

	
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	//1 meter height, width and length box shaped world volume. (Half lengths)

	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	//Creates the logic volume from the previous parameters.
	
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
	//Physical volumeparameters = (rotation, center, logical volume, name, mother volume, boolean operations, copy number, should check for overlaps or not)
	
	G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
	
	G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");
	
	G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);
	
	G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);
	//Creates detector volume for detecting photons.

	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicalDetector");
	
	for(G4int i = 0; i < 100; i++) //X and Y coordinates depend on the indices. Array for detectors. Shifting is needed to be inside mother volume. Same for Z. Copy number has to be function to place detector in different locations.
	{
		for(G4int j = 0; j < 100; j++)
		{
			G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100, -0.5*m+(j+0.5)*m/100, 0.49*m), logicDetector, "physDetector", logicWorld, false, j+i*100, true); 
		}
	} 

	return physWorld; //Has to return highest mother volume.

}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicDetector->SetSensitiveDetector(sensDet);


}





