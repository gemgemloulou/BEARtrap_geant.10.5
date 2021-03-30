//
//  PrimaryGeneratorAction.cc
//
//
//  Created by Gemma Wilson on 29/03/2021.
//

#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"
#include "G4UImanager.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
:G4VUserPrimaryGeneratorAction(),fParticleGun(0),generator(0){
    
    G4bool simpleGen = true;
    
    if (simpleGen == 1){
        G4int n_particle = 1;
        fParticleGun = new G4ParticleGun(n_particle);
    }else{
        generator = new G4GeneralParticleSource();
        G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
        fParticleGun->SetParticleEnergy(0.5*MeV);
        fParticleGun->SetParticlePosition(G4ThreeVector(0.*m,0.*m,0.*m));
        
    }
}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
    if (simpleGen==1){
        delete fParticleGun;
    }else{
        delete generator;
    }
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
    if (simpleGen==1){
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }else{
        generator->GeneratePrimaryVertex(anEvent);
    }
