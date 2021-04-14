#include "PlasHit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4ios.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

G4Allocator<PlasHit> PlasHitAllocator;

PlasHit::PlasHit(){;}

PlasHit::~PlasHit(){;}

PlasHit::PlasHit(const PlasHit& right):G4VHit(){
    edep = right.edep;
}

const PlasHit& PlasHit::operator=(const PlasHit& right){
    edep = right.edep;
    return *this;
}


void PlasHit::Draw(){
}

void PlasHit::Print(){;}


