//
// $Id: RunAction.cc 15.10.2018 A Fijalkowska $
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "G4Run.hh"

RunAction::RunAction(): G4UserRunAction()
{ 
    std::cout << "być może to czas na stworzenie pliku wyjściowego" << std::endl;
    timer = new G4Timer;
}


RunAction::~RunAction()
{
    std::cout <<"destruktor RunAction, zapis i zamknięcie pliku" << std::endl;  
    delete timer;
}

void RunAction::BeginOfRunAction(const G4Run* run)
{ 
   G4cout << "### Run " << run->GetRunID() << " start." << G4endl; 
   timer->Start();	

}


void RunAction::EndOfRunAction(const G4Run* run)
{
   timer->Stop();
   G4cout << "number of event = " << run->GetNumberOfEvent() 
          << " " << *timer << G4endl;  

}



