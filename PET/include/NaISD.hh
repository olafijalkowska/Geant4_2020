
#ifndef NaISD_h
#define NaISD_h 1

#include "G4VSensitiveDetector.hh"
#include "NaIHit.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;


class NaISD : public G4VSensitiveDetector
{
  public:
    NaISD(const G4String& name, 
                     const G4String& hitsCollectionName, 
                     G4int depthVal);
    virtual ~NaISD();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);

  private:
    NaIHitsCollection* hitsCollection;
    G4int  depth;
    
    G4double GetEnergyDeposit(G4Step* step);
    G4double GetTrackLength(G4Step* step);
    G4int GetCopyNr(G4Step* step);
};

#endif

