// $Id: DetectorConstruction.hh 15.10.2018 A. Fijalkowska $
//
/// \file DetectorConstruction.hh
/// \brief Kasa trzymająca geometrię detektora
//
//
#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"  //wbudowane materiały
#include "G4Material.hh" //materiały

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction(); //konstuktor
    virtual ~DetectorConstruction(); //destruktor
    virtual G4VPhysicalVolume* Construct(); //tu będzie wszystko budowane
    virtual void ConstructSDandField(); //tu póżniej zdefiniujemy czułe elementy detektora

  private:
    G4LogicalVolume* worldLogic; //świat
    G4LogicalVolume* fantomLogVol;
    G4LogicalVolume* cylinderLogVol;
    G4NistManager* man;
    //G4VPhysicalVolume* worldPhys;
    G4VPhysicalVolume* ConstructWorld(); //metoda w której świat zostanie zbudowany
    void ConstructHumanFantom();
    void ConstructCylinder();
    void ConstructNaIDet();
    G4LogicalVolume* ConstructAluLayer();
    G4LogicalVolume* ConstructTeflonLayer();
    G4Material* MakeWater();

    
 
};

#endif
