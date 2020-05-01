//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: NaIHit.cc 69586 2013-05-08 14:20:11Z gcosmo $
//
/// \file NaIHit.cc
/// \brief Implementation of the NaIHit class

#include "NaIHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<NaIHit>* NaIHitAllocator = 0;

NaIHit::NaIHit(G4int copyNrVal): G4VHit()
{
   eDep = 0.;
   trackLength = 0.;
   copyNr = copyNrVal;
}


NaIHit::~NaIHit() {}


NaIHit::NaIHit(const NaIHit& right): G4VHit()
{
  eDep        = right.eDep;
  trackLength = right.trackLength;
  copyNr = right.copyNr;
}

const NaIHit& NaIHit::operator=(const NaIHit& right)
{
  eDep        = right.eDep;
  trackLength = right.trackLength;
  copyNr = right.copyNr;
  return *this;
}


G4int NaIHit::operator==(const NaIHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

void NaIHit::Add(G4double energyDep, G4double trackLen) {
  eDep += energyDep; 
  trackLength += trackLen;
}

G4double NaIHit::GetEdep() { 
  return eDep; 
}

G4double NaIHit::GetTrackLength() { 
  return trackLength; 
}

G4int NaIHit::GetCopyNr() { 
  return copyNr; 
}
