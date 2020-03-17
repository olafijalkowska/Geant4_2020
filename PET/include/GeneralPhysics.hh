// $Id: GeneralPhysics.hh 2016-15-11 A Fijalkowska $
//
/// \file GeneralPhysics.hh
/// \brief Definition of the GeneralPhysics class
/// Class taken from example optical/LXe/
//
//
#ifndef GeneralPhysics_h
#define GeneralPhysics_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "G4VPhysicsConstructor.hh"

class GeneralPhysics : public G4VPhysicsConstructor
{
  public:

    GeneralPhysics(const G4String& name = "general");
    virtual ~GeneralPhysics();

    // This method will be invoked in the Construct() method.
    // each particle type will be instantiated
    virtual void ConstructParticle();
 
    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type
    virtual void ConstructProcess();

};

#endif
