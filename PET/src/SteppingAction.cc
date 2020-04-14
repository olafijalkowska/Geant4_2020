//
// $Id: SteppingAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
#include "SteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"

SteppingAction::SteppingAction():G4UserSteppingAction()
{

}

SteppingAction::~SteppingAction() {}


void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
    G4Track* theTrack = theStep->GetTrack();
    G4String volumeName = theTrack->GetVolume()->GetName();
    if(volumeName == "fantom")
    {
        auto secondaries =	theStep->GetSecondaryInCurrentStep ();
    
        nrOfSec+=secondaries->size();
        //std::cout << nrOfSec << std::endl;
    }


}

void SteppingAction::PrintStep(const G4Step* theStep)
{
    
    G4Track* theTrack = theStep->GetTrack();
    G4String particleName = theTrack->GetDefinition()->GetParticleName();      
    G4String processName =theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    
    G4double energy = theTrack->GetKineticEnergy() ;
    G4String volumeName = theTrack->GetVolume()->GetName();
    G4double deltaEn = theStep->GetDeltaEnergy();
    int trackNr = theTrack->GetTrackID ();

    std::cout << " trackNr: " << trackNr
              << " particle: " << particleName
		      << " process: " << processName
		      << " kinetic energy " << energy/MeV
		      << " delta en: " << deltaEn
		      << " voulme name: " << volumeName << std::endl;

}

int SteppingAction::nrOfSec=0;
