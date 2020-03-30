
#include "HumanFantom.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh" 


HumanFantom::HumanFantom(double heigh, double radius)
{
    ConstructFantom(heigh, radius);
    ConstructSpine(heigh);
}

void HumanFantom::ConstructFantom(double heigh, double radius)
{
    G4double radiusMin = 0;
    G4double radiusMax = radius;
    G4double length = heigh;
    G4Tubs* fantomSolid = new G4Tubs("fantomSolid", radiusMin, radiusMax, length/2., 0*deg, 360*deg);
    G4Material* water = MakeWater();
    fantomLogVol = new G4LogicalVolume(fantomSolid, water, "fantomLogVol");

     
    G4VisAttributes* fantomVisAtt = new G4VisAttributes( G4Colour(1,0.8,0.8));
	fantomVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
	//fantomVisAtt->SetForceSolid(true);
	fantomLogVol->SetVisAttributes(fantomVisAtt);

	//G4ThreeVector pos(0,0,0);    
	//new G4PVPlacement(0, pos, fantomLogVol, "fantom", worldLogic, 0, 0);

}

G4Material* HumanFantom::MakeWater()
{
    G4NistManager* man=G4NistManager::Instance();
    G4Element* H = man->FindOrBuildElement("H");
    G4Element* O = man->FindOrBuildElement("O");
    G4Material* water = new G4Material("water", 1.0*g/cm3, 2);
    water->AddElement(H, 2);
    water->AddElement(O, 1);
    return water;

}

void HumanFantom::ConstructSpine(double heigh)
{
   G4double rMin = 0;
   G4double rMax = 3 *cm;
   G4double halfLength = heigh/4.; 
   G4Tubs* spineSolid = new G4Tubs("spineSolid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4NistManager* man=G4NistManager::Instance();
   G4Material* bone = man->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");

   
   G4LogicalVolume* spineLogVol = new G4LogicalVolume(spineSolid, bone,"spineLogic");
   G4VisAttributes* spineVis = new G4VisAttributes(G4Colour(1,1.,1));
   //aluVis->SetForceSolid(true);
   spineVis->SetForceAuxEdgeVisible(true);
   spineLogVol->SetVisAttributes(spineVis);
   G4ThreeVector pos(0,10*cm,halfLength);
   new G4PVPlacement(0, pos, spineLogVol, "spinePhys", fantomLogVol, 0, 0);
}


void HumanFantom::Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo)
{
    new G4PVPlacement(pRot, tlate, fantomLogVol, pName,  pMotherLogical, 0,pCopyNo);
}

