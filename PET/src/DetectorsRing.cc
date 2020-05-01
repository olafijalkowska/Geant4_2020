#include "DetectorsRing.hh"

#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh" 
#include "G4Material.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4SDManager.hh"
#include "NaISD.hh"

DetectorsRing::DetectorsRing()
{
    man = G4NistManager::Instance();
    NaILogic=0;
	ConstructCylinder();
	ConstructNaIDet();
	//ConstructSDandField();

}

void DetectorsRing::ConstructCylinder()
{
     G4Material* ppy = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
     G4double rMin = 40*cm;
     G4double rMax = 55*cm;
     G4double length = 15*cm;
     G4Tubs* theCylinder = new G4Tubs("theCylinder", rMin, rMax, length/2, 0*deg, 360*deg);
     cylinderLogVol = new G4LogicalVolume(theCylinder, ppy, "cylinderLogVol");

     G4VisAttributes* cylinderAtt = new G4VisAttributes(G4Colour(0.5,0.5,0.5, 0.7));
     cylinderAtt->SetForceAuxEdgeVisible(true);
     cylinderAtt->SetForceSolid(true);
     cylinderLogVol->SetVisAttributes(cylinderAtt);
     //G4ThreeVector pos(0,0, 0);
    // new G4PVPlacement(0,pos,cylinderLogVol,"cylinderPhy",worldLogic,0,0);
}

G4Material* DetectorsRing::MakeNaI()
{
	G4Element* Na = man->FindOrBuildElement("Na");
	G4Element* I = man->FindOrBuildElement("I");
	G4Material* NaI = new G4Material("NaI", 3.67*g/cm3, 2);
	NaI->AddElement(Na, 1);
	NaI->AddElement(I, 1);
	return NaI;
}

void DetectorsRing::ConstructNaIDet()
{
   G4LogicalVolume* aluLogic = ConstructAluLayer();
   G4LogicalVolume* teflonLogic = ConstructTeflonLayer(); 
   NaILogic = ConstructNaILayer();   

   G4ThreeVector cryspos(0,0,0); 
   new G4PVPlacement(0, cryspos, NaILogic, "NaIPhys", teflonLogic, 0, 0);
   
   G4ThreeVector pos(0,0,0); 
   new G4PVPlacement(0, pos, teflonLogic, "teflonPhys", aluLogic, 0, 0);

   int nrOfDet = 36;
   double angle = 360./nrOfDet*deg;
   double ringRadius = 46.6*cm;
   for(int i=0; i != 36; i++) {
	   G4ThreeVector naiDetPos(ringRadius*sin(i*angle),ringRadius*cos(i*angle),0);
	   G4RotationMatrix* rot = new G4RotationMatrix();
	   rot->rotateZ(i*angle);
	   rot->rotateX(90*deg);
	   new G4PVPlacement(rot, naiDetPos, aluLogic, "aluPhys", cylinderLogVol, 0, i);
   }
}

G4LogicalVolume* DetectorsRing::ConstructAluLayer()
{
   G4double rMin = 0;
   G4double rMax = 3.6 *cm;
   G4double halfLength = 5.6 *cm; 
   G4Tubs* aluSolid = new G4Tubs("aluSolid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* alu = new G4Material("aluminum", 2.7*g/cm3, 1);
   G4Element* Al = man->FindOrBuildElement("Al");
   alu->AddElement(Al, 1);
   
   G4LogicalVolume* aluLogic = new G4LogicalVolume(aluSolid, alu,"aluLogic");
   G4VisAttributes* aluVis = new G4VisAttributes(G4Colour(255./255,102./255.,0));
   //aluVis->SetForceSolid(true);
   aluVis->SetForceAuxEdgeVisible(true);
   aluLogic->SetVisAttributes(aluVis);
   return aluLogic;
}

G4LogicalVolume* DetectorsRing::ConstructTeflonLayer()
{
   G4double rMin = 0;
   G4double rMax = 3.3 *cm;
   G4double halfLength = 5.3 *cm; 
   G4Tubs* solid = new G4Tubs("solid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* teflon = man->FindOrBuildMaterial("G4_TEFLON");

   
   G4LogicalVolume* teflonLogic = new G4LogicalVolume(solid, teflon,"teflonLogic");
   G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(1,1,1));
   //visAttr->SetForceSolid(true);
   visAttr->SetForceAuxEdgeVisible(true);
   teflonLogic->SetVisAttributes(visAttr);
   return teflonLogic;
}

G4LogicalVolume* DetectorsRing::ConstructNaILayer()
{
	G4double rMin = 0;
	G4double rMax = 3.*cm;
	G4double halfLength = 5.*cm;
	G4Tubs* crystal = new G4Tubs("crystal", rMin, rMax, halfLength, 0*deg, 360*deg);
	G4Material* NaI = MakeNaI();

	G4LogicalVolume* NaILogicLoc = new G4LogicalVolume(crystal, NaI, "NaILogic");
	G4VisAttributes* vis = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
    vis->SetForceSolid(true);
    vis->SetForceAuxEdgeVisible(true);
    NaILogicLoc->SetVisAttributes(vis);
    return NaILogicLoc;
}

void DetectorsRing::Pos(G4RotationMatrix *rotate, 
                        G4ThreeVector &vect, 
                        const G4String &name, 
                        G4LogicalVolume *MotherLogical, 
                        G4int CopyNo)
{
    new G4PVPlacement(rotate, vect, cylinderLogVol, name,  MotherLogical, 0, CopyNo);
}


void DetectorsRing::ConstructSDandField()
{
   /* G4MultiFunctionalDetector* detector =
    new G4MultiFunctionalDetector("naISensitiveDet");
    G4int depth = 2;
    G4VPrimitiveScorer* energyDepScorer = new G4PSEnergyDeposit("eDep",depth);
    detector->RegisterPrimitive(energyDepScorer);
    NaILogic->SetSensitiveDetector(detector);
    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    SDmanager->AddNewDetector(detector);*/
    

    NaISD* naISD = new NaISD("naISD", "eDep", 2);//konstruktor

   G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(naISD);//rejestracja w G4SDManager
    NaILogic->SetSensitiveDetector(naISD);
}

