
#include "NaISD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"


NaISD::NaISD(const G4String& name, 
             const G4String& hitsCollectionName,
             G4int depthVal) : G4VSensitiveDetector(name)
{
  collectionName.insert(hitsCollectionName);
  hitsCollection=0L;
  depth = depthVal;
}

NaISD::~NaISD() 
{ 
}

void NaISD::Initialize(G4HCofThisEvent* hce)
{
  hitsCollection = new NaIHitsCollection(SensitiveDetectorName, collectionName[0]); 
//last - check

  auto hitsCollId = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hitsCollId, hitsCollection ); 
}
    

G4bool NaISD::ProcessHits(G4Step* step, G4TouchableHistory*)
{  
  G4double edep = GetEnergyDeposit(step);
  G4double trackLenght = GetTrackLength(step);  
  G4int copyNr = GetCopyNr(step);

  if ( edep==0. && trackLenght == 0. ) return false;      
  
  G4int hitsNr = hitsCollection->entries();   
  G4bool moduleAlreadyHit = false;
  for(G4int i=0; i<hitsNr; i++)
  {
	  G4int moduleCopyNr = (*hitsCollection)[i]->GetCopyNr();
      if(copyNr == moduleCopyNr)
      {
         (*hitsCollection)[i]->Add(edep, trackLenght); 
         moduleAlreadyHit = true;		  
         break;
      }
  }
  
  if(!moduleAlreadyHit)
  {
	  	NaIHit* aHit = new NaIHit(copyNr);
	  	aHit->Add(edep, trackLenght); 
		hitsCollection->insert( aHit );	 
		 
  }    
  return true;
}


G4double NaISD::GetEnergyDeposit(G4Step* step)
{
    return step->GetTotalEnergyDeposit();
}

G4double NaISD::GetTrackLength(G4Step* step)
{
  G4double stepLength = 0.;
  //if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) 
  //{
    stepLength = step->GetStepLength();
  //}
  return stepLength;
}

G4int NaISD::GetCopyNr(G4Step* step)
{
	G4int voulmeNr =
    step->GetPostStepPoint()->GetTouchable()->GetReplicaNumber(depth);
	return voulmeNr;
}

