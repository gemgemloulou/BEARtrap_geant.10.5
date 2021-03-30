//
//  RunAction.cc
//
//
//  Created by Gemma Wilson on 29/03/2021.
//
#include "RunAction.hh"
#include "EventAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

RunAction::RunAction(EventAction* EvAct):G4UserRunAction(),fEventAction(EvAct){
}

RunAction::~RunAction(){
}

void RunAction::BeginOfRunAction(const G4Run* aRun){
    G4int runnum = aRum->GetRunID();
    G4cout << "Run ID= " << runnum << G4endl;
    if(runnum==0){
        G4int initEID = 0;
        fEventAction->InitializeEID(initEID);
    }
}

void RunAction::EndOfRunAction(const G4Run*){
}
