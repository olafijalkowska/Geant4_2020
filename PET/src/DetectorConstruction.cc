//
// $Id: DetectorConstruction.cc 12.16.2016 A. Fijalkowska $
//
/// \file DetectorConstruction.cc
/// \brief DetectorConstruction class
//
//
#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh" //tworzenie physical volume
#include "G4SystemOfUnits.hh" //jednostki
#include "G4VisAttributes.hh" //sposob wyświetlania, kolory itp

#include "G4Box.hh" //prostopadłościan
#include "G4Tubs.hh" //walec
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"

#include "HumanFantom.hh"


DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    ring=0;
}

DetectorConstruction::~DetectorConstruction() 
{
    if(worldLogic != 0L)
        delete worldLogic;
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructHumanFantom();
	ConstructDetectorsRing();
    return worldPhys;
}

G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{
    G4double worldX = 1.5*m;
    G4double worldY = 1.5*m;
    G4double worldZ = 1.5*m;
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,
                           CLHEP::universe_mean_density, 
                           kStateGas, 3.e-18*pascal, 2.73*kelvin);
                           
    worldLogic = new G4LogicalVolume(worldSolid, vaccum,"worldLogic", 0,0,0);
    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;
}

void DetectorConstruction::ConstructHumanFantom()
{   
    G4double radiusMax = 15*cm;
    G4double length = 170*cm;
    HumanFantom *fantom = new HumanFantom(length, radiusMax);

	G4ThreeVector pos(0,0,0); 
	//G4RotationMatrix *pRot = new G4RotationMatrix();
	fantom->Place(0, pos, "fantom", worldLogic, 0); 
	
}

void DetectorConstruction::ConstructDetectorsRing()
{   
    ring = new DetectorsRing();

	G4ThreeVector p(0,0,0); 
	//G4RotationMatrix *pRot = new G4RotationMatrix();
	ring->Pos(0, p, "ring", worldLogic, 0);
}

void DetectorConstruction::ConstructSDandField() 
{

    ring->ConstructSDandField();
}
