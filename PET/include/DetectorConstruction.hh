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
#include "G4NistManager.hh"  
#include "G4Material.hh" 
#include "DetectorsRing.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction(); //konstuktor
    virtual ~DetectorConstruction(); //destruktor
    virtual G4VPhysicalVolume* Construct(); 
    virtual void ConstructSDandField(); 

  private:
    G4LogicalVolume* worldLogic;
    G4VPhysicalVolume* ConstructWorld();
    void ConstructHumanFantom();
    void ConstructDetectorsRing();
    DetectorsRing *ring;
};

#endif
