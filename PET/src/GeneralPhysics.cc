// $Id: GeneralPhysics.cc 15.10.2018 A.Fijalkowska
//
/// \file GeneralPhysics.cc
/// \brief Implementation of the GeneralPhysics class
/// Class taken from example optical/LXe/
//
#include "GeneralPhysics.hh"
//#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4GenericIon.hh"
#include "G4Decay.hh"

GeneralPhysics::GeneralPhysics(const G4String& name)
                     :  G4VPhysicsConstructor(name) {}

GeneralPhysics::~GeneralPhysics() {}


void GeneralPhysics::ConstructParticle()
{
  G4GenericIon::GenericIonDefinition();
}

void GeneralPhysics::ConstructProcess()
{
    G4Decay* fDecayProcess = new G4Decay();
    auto aParticleIterator=GetParticleIterator();
    aParticleIterator->reset();
    while( (*aParticleIterator)() )
    {
        G4ParticleDefinition* particle = aParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        if (fDecayProcess->IsApplicable(*particle))
         {
             pmanager ->AddProcess(fDecayProcess);
             pmanager ->SetProcessOrdering(fDecayProcess, idxPostStep);
             pmanager ->SetProcessOrdering(fDecayProcess, idxAtRest);
    }
  }
}
