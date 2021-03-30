#include "EventAction.hh"
#include "Analysis.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "PlasHit.hh"

#include <iostream>
#include <fstream>

using namespace std;

ofstream outputFile("GEANT4_output.txt");

EventAction::EventAction():G4UserEventAction(),fTotalEnergyDeposit(0.){
   
    dE1_HCID = -1; dE2_HCID = -1; dE3_HCID = -1; dE4_HCID = -1;
    E1_HCID = -1;
    
    dE5_HCID = -1; dE6_HCID = -1; dE7_HCID = -1; dE8_HCID = -1;
    E5_HCID = -1;
    
    counter = 0;

    outputFile << "DecayCounter, " << "Top MCP, " << "Right MCP, "
    << "dE1, " << "dE2, " << "dE3, " << "dE4, " << "E1, "
    << "dE5, " << "dE6, " << "dE7, " << "dE8, " << "E5\n" << endl;
}

EventAction::~EventAction(){
}

void EventAction::BeginOfEventAction( const G4Event* evt){
 fTotalEnergyDeposit = 0.;
  
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    if (dE1_HCID<0)dE1_HCID = SDman->GetCollectionID("dE1");
    if (dE2_HCID<0)dE2_HCID = SDman->GetCollectionID("dE2");
    if (dE3_HCID<0)dE3_HCID = SDman->GetCollectionID("dE3");
    if (dE4_HCID<0)dE4_HCID = SDman->GetCollectionID("dE4");
    
    if (E1_HCID<0)E1_HCID = SDman->GetCollectionID("E1");

    if (dE5_HCID<0)dE5_HCID = SDman->GetCollectionID("dE5");
    if (dE6_HCID<0)dE6_HCID = SDman->GetCollectionID("dE6");
    if (dE7_HCID<0)dE7_HCID = SDman->GetCollectionID("dE7");
    if (dE8_HCID<0)dE8_HCID = SDman->GetCollectionID("dE8");
    
    if (E5_HCID<0)E5_HCID = SDman->GetCollectionID("E5");
    
}

void EventAction::EndOfEventAction( const G4Event* evt)
{
    G4double dE1 = 0.; G4double dE2 = 0.; G4double dE3 = 0.; G4double dE4 = 0.;
    G4double E1 = 0.;
    G4double dE5 = 0.; G4double dE6 = 0.; G4double dE7 = 0.; G4double dE8 = 0.;
    G4double E5 = 0.;
    
    if(dE1_HCID<0 && E1_HCID<0 && dE2_HCID<0 && dE3_HCID<0 && dE4_HCID<0 && dE5_HCID<0 && E5_HCID<0 && dE6_HCID<0 && dE7_HCID<0 && dE8_HCID<0) return;
    
    G4HCofThisEvent * PlasHCE = evt->GetHCofThisEvent();
    PlasHitsCollection* dE1_HC = 0;
    PlasHitsCollection* dE2_HC = 0;
    PlasHitsCollection* dE3_HC = 0;
    PlasHitsCollection* dE4_HC = 0;
    PlasHitsCollection* E1_HC = 0;
    PlasHitsCollection* dE5_HC = 0;
    PlasHitsCollection* dE6_HC = 0;
    PlasHitsCollection* dE7_HC = 0;
    PlasHitsCollection* dE8_HC = 0;
    PlasHitsCollection* E5_HC = 0;

    if(PlasHCE){
        dE1_HC = (PlasHitsCollection*)(PlasHCE->GetHC(dE1_HCID));
        dE2_HC = (PlasHitsCollection*)(PlasHCE->GetHC(dE2_HCID));
        dE3_HC = (PlasHitsCollection*)(PlasHCE->GetHC(dE3_HCID));
        dE4_HC = (PlasHitsCollection*)(PlasHCE->GetHC(dE4_HCID));
        E1_HC = (PlasHitsCollection*)(PlasHCE->GetHC(E1_HCID));
        dE5_HC = (PlasHitsCollection*)(PlasHCE->GetHC(dE5_HCID));
        dE6_HC = (PlasHitsCollection*)(PlasHCE->GetHC(dE6_HCID));
        dE7_HC = (PlasHitsCollection*)(PlasHCE->GetHC(dE7_HCID));
        dE8_HC = (PlasHitsCollection*)(PlasHCE->GetHC(dE8_HCID));
        E5_HC = (PlasHitsCollection*)(PlasHCE->GetHC(E5_HCID));
            
    }

    if (dE1_HC){
        G4double dE1_totalE = 0;
        int n_hit = dE1_HC->entries();
        for (int i = 0; i<n_hit; i++){
            dE1_totalE += (*dE1_HC)[i]->GetEdep();
        }
        dE1 = dE1_totalE;
    }

    if (dE2_HC){
        G4double dE2_totalE = 0;
        int n_hit = dE2_HC->entries();
        for (int i = 0; i<n_hit; i++){
            dE2_totalE += (*dE2_HC)[i]->GetEdep();
        }
        dE2 = dE2_totalE;
    }

    if (dE3_HC){
        G4double dE3_totalE = 0;
        int n_hit = dE3_HC->entries();
        for ( int i=0; i<n_hit; i++){
            dE3_totalE += (*dE3_HC)[i]->GetEdep();
        }
        dE3 = dE3_totalE;
    }

    if (dE4_HC){
        G4double dE4_totalE = 0;
        int n_hit = dE4_HC->entries();
        
        for (int i=0; i<n_hit; i++){
            dE4_totalE += (*dE4_HC)[i]->GetEdep();
        }
        dE4 = dE4_totalE;
    }
    
    
    if (E1_HC){
           G4double E1_totalE = 0;
           int n_hit = E1_HC->entries();
           
           for ( int i= 0; i<n_hit; i++){
               E1_totalE += (*E1_HC)[i]->GetEdep();
           }
           E1 = E1_totalE;
       }
    
    
    if (dE5_HC){
        G4double dE5_totalE = 0;
        int n_hit = dE5_HC->entries();
        for ( int i=0 ; i<n_hit; i++){
            dE5_totalE += (*dE5_HC)[i]->GetEdep();
        }
        dE5 = dE5_totalE;
    }

    if (dE6_HC){
        G4double dE6_totalE = 0;
        int n_hit = dE6_HC->entries();
        for ( int i=0; i<n_hit; i++){
            dE6_totalE += (*dE6_HC)[i]->GetEdep();
        }
        dE6 = dE6_totalE;
    }

    if (dE7_HC){
        G4double dE7_totalE = 0;
        int n_hit = dE7_HC->entries();
        for ( int i=0; i<n_hit; i++){
            dE7_totalE += (*dE7_HC)[i]->GetEdep();
        }
        dE7 = dE7_totalE;
    }

    if (dE8_HC){
        G4double dE8_totalE = 0;
        int n_hit = dE8_HC->entries();
        for ( int i=0; i<n_hit; i++){
            dE8_totalE += (*dE8_HC)[i]->GetEdep();
        }
        dE8 = dE8_totalE;
    }

    if (E5_HC){
    G4double E5_totalE = 0;
    int n_hit = E5_HC->entries();
    for ( int i=0; i<n_hit; i++){
        E5_totalE += (*E5_HC)[i]->GetEdep();
    }
        E5 = E5_totalE;
    }
    

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    if (dE1>0.0)analysisManager->FillH1(1, dE1/keV);
    if (dE2>0.0)analysisManager->FillH1(2, dE2/keV);
    if (dE3>0.0)analysisManager->FillH1(3, dE3/keV);
    if (dE4>0.0)analysisManager->FillH1(4, dE4/keV);
    
    if (E1>0.0)analysisManager->FillH1(9, E1/keV);
    
    if (dE5>0.0)analysisManager->FillH1(5, dE5/keV);
    if (dE6>0.0)analysisManager->FillH1(6, dE6/keV);
    if (dE7>0.0)analysisManager->FillH1(7, dE7/keV);
    if (dE8>0.0)analysisManager->FillH1(8, dE8/keV);
    
    if (E5>0.0)analysisManager->FillH1(10, E5/keV);
       
    counter++;

    outputFile << EID << ", 0, 0, "
    << dE1/keV << ", " << dE2/keV << ", " << dE3/keV <<  ", " << dE4/keV <<  ", "
    << E1/keV << ", "
    << dE5/keV << ", " << dE6/keV << ", " << dE7/keV << ", " << dE8/keV <<  ", "
    << E5/keV << endl;
}

