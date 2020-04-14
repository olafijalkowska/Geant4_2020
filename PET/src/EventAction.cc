
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"


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
}



