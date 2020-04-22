#ifndef DetectorsRing_H
#define DetectorsRing_H 1
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh" 
#include "G4Material.hh" 

class DetectorsRing 
{
	public:
	DetectorsRing();
	void Pos(G4RotationMatrix *rotate, 
                        G4ThreeVector &vect, 
                        const G4String &name, 
                        G4LogicalVolume *MotherLogical, 
                        G4int CopyNo);
	void ConstructSDandField();
	
	private:
    G4LogicalVolume* cylinderLogVol;
    G4NistManager* man;
    void ConstructCylinder();
    void ConstructNaIDet();
    G4LogicalVolume* ConstructAluLayer();
    G4LogicalVolume* ConstructTeflonLayer();
    G4LogicalVolume* ConstructNaILayer();
	G4Material* MakeNaI();
	G4LogicalVolume* NaILogic;
};

#endif
