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
    fantomLogVol=0L;
    cylinderLogVol=0L;
    man = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() 
{
    if(worldLogic != 0L)
        delete worldLogic;
    if(fantomLogVol != 0L)
        delete fantomLogVol;        
    if(cylinderLogVol != 0L)
        delete cylinderLogVol; 
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    //ConstructHumanFantom();
    ConstructCylinder();
    ConstructNaIDet();
    //ConstructSpine();
    
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

G4Material* DetectorConstruction::MakeWater()
{
    G4Element* H = man->FindOrBuildElement("H");
    G4Element* O = man->FindOrBuildElement("O");
    G4Material* water = new G4Material("water", 1.0*g/cm3, 2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);
    return water;

}

void DetectorConstruction::ConstructHumanFantom()
{   
    G4double radiusMax = 15*cm;
    G4double length = 170*cm;
    HumanFantom *fantom = new HumanFantom(length, radiusMax);

	G4ThreeVector pos(0,0,0); 
	G4RotationMatrix *pRot = new G4RotationMatrix();
	fantom->Place(0, pos, "fantom", worldLogic, 0); 
	
}





void DetectorConstruction::ConstructCylinder()
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

     G4ThreeVector pos(0,0, 0);
     new G4PVPlacement(0,pos,cylinderLogVol, "cylinderPhy",worldLogic,0,0);
}
//NaI
//wysokość 10 cm
//promień 3 cm
//teflon 3 mm
//aluminium 3 mm
//delta 0.153294282 rad

void DetectorConstruction::ConstructNaIDet()
{
   G4LogicalVolume* aluLogic = ConstructAluLayer();
   G4LogicalVolume* teflonLogic = ConstructTeflonLayer(); 
   G4LogicalVolume* naiLogic = ConstructCrystal();   
   G4ThreeVector pos(0,0,0);
   new G4PVPlacement(0, pos, naiLogic, "naiPhys", teflonLogic, 0, 0);   
   new G4PVPlacement(0, pos, teflonLogic, "teflonPhys", aluLogic, 0, 0);
   int nrOfDet = 36;
   double angle = 360./nrOfDet*deg;
   double radius = 46.6*cm;
   for(int i = 0; i !=36; ++i)
   {
       G4RotationMatrix* rot = new G4RotationMatrix();
       //rot->rotateX(90*deg);
       rot->rotateZ(angle*i);
       rot->rotateX(90*deg);
       G4ThreeVector detPos(radius*sin(angle*i),radius*cos(angle*i),0);
       new G4PVPlacement(rot, detPos, aluLogic, "aluPhys", cylinderLogVol, 0, i);
   }
}

G4LogicalVolume* DetectorConstruction::ConstructAluLayer()
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

G4LogicalVolume* DetectorConstruction::ConstructTeflonLayer()
{
   G4double rMin = 0;
   G4double rMax = 3.3 *cm;
   G4double halfLength = 5.3 *cm; 
   G4Tubs* solid = new G4Tubs("solid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* teflon = man->FindOrBuildMaterial("G4_TEFLON");

   
   G4LogicalVolume* teflonLogic = new G4LogicalVolume(solid, teflon,"teflonLogic");
   G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(1,1,1, 0.5));
   visAttr->SetForceSolid(true);
   visAttr->SetForceAuxEdgeVisible(true);
   teflonLogic->SetVisAttributes(visAttr);
   return teflonLogic;
}

G4LogicalVolume* DetectorConstruction::ConstructCrystal()
{
   G4double rMin = 0;
   G4double rMax = 3. *cm;
   G4double halfLength = 5. *cm; 
   G4Tubs* crystal = new G4Tubs("crystal", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* nai = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");

   
   G4LogicalVolume* naiLogic = new G4LogicalVolume(crystal, nai,"naiLogic");
   G4VisAttributes* naiVis = new G4VisAttributes(G4Colour(1,1,0));
   naiVis->SetForceSolid(true);
   naiVis->SetForceAuxEdgeVisible(true);
   naiLogic->SetVisAttributes(naiVis);
   return naiLogic;
}

void DetectorConstruction::ConstructSpine()
{
   G4double rMin = 0;
   G4double rMax = 3 *cm;
   G4double halfLength = 85./2. *cm; 
   G4Tubs* aluSolid = new G4Tubs("aluSolid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* alu = new G4Material("aluminum", 2.7*g/cm3, 1);
   G4Element* Al = man->FindOrBuildElement("Al");
   alu->AddElement(Al, 1);
   
   G4LogicalVolume* aluLogic = new G4LogicalVolume(aluSolid, alu,"spineLogic");
   G4VisAttributes* aluVis = new G4VisAttributes(G4Colour(1,1.,1));
   //aluVis->SetForceSolid(true);
   aluVis->SetForceAuxEdgeVisible(true);
   aluLogic->SetVisAttributes(aluVis);
   G4ThreeVector pos(0,10*cm,halfLength);
   new G4PVPlacement(0, pos, aluLogic, "aluPhys", fantomLogVol, 0, 0);
}

void DetectorConstruction::ConstructSDandField() 
{


}






