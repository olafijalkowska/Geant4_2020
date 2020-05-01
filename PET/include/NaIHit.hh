
/// \file NaIHit.hh
/// \brief Definition of the NaIHit class

#ifndef NaIHit_h
#define NaIHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"

/// NaIHit
///
/// Klasa 

class NaIHit : public G4VHit
{
  public:
    NaIHit(G4int copyNrVal);
    NaIHit(const NaIHit&);
    virtual ~NaIHit();

    // operators
    const NaIHit& operator=(const NaIHit&);
    G4int operator==(const NaIHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods to handle data
    void Add(G4double energyDep, G4double trackLen);

    // get methods
    G4double GetEdep();
    G4double GetTrackLength();
    G4int GetCopyNr();
      
  private:
    G4double eDep;        ///< Energy deposit in the sensitive volume
    G4double trackLength; ///< Track length in the  sensitive volume
    G4int copyNr;
};


using NaIHitsCollection = G4THitsCollection<NaIHit>;
extern G4ThreadLocal G4Allocator<NaIHit>* NaIHitAllocator;


inline void* NaIHit::operator new(size_t)
{
  if (!NaIHitAllocator) {
    NaIHitAllocator = new G4Allocator<NaIHit>;
  }
  void *hit;
  hit = (void *) NaIHitAllocator->MallocSingle();
  return hit;
}

inline void NaIHit::operator delete(void *hit)
{
  if (!NaIHitAllocator) {
    NaIHitAllocator = new G4Allocator<NaIHit>;
  }
  NaIHitAllocator->FreeSingle((NaIHit*) hit);
}


#endif
