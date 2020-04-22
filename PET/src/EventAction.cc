
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"


EventAction::EventAction()
{
    output.open("Secondaries.txt");
}
 
EventAction::~EventAction()
{
    output.close();
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    output << SteppingAction::nrOfSec << std::endl;
    SteppingAction::nrOfSec=0;

    G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
    if(!hitsCollOfThisEvent)
        return;


    G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
    G4int naIcollId = SDmanager->GetCollectionID("naISensitiveDet/eDep");
    //std::cout<<naIcollId << std::endl;
    


  G4THitsMap<G4double>* NaIHitsCollection = static_cast<G4THitsMap<G4double>*>( hitsCollOfThisEvent->GetHC(naIcollId));


/*  for ( auto it : *hitsMap->GetMap() ) {
    // hitsMap->GetMap() returns the map of std::map<G4int, G4double*>
    std::cout <<*(it.first) << " " << *(it.second)<<std::endl;
  }*/
  
  
     std::map< G4int,G4double*>* NaIcolMap = NaIHitsCollection->GetMap();
    std::map< G4int,G4double*>::iterator itr;
    for (itr = NaIcolMap->begin(); itr != NaIcolMap->end(); itr++) 
    {
        std::cout << (itr->first) << " " << *(itr->second) << std::endl;

    }
  
      

}



