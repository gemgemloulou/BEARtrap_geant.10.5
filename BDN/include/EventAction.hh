#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"

class EventAction : public G4UserEventAction{
  public:
    EventAction();
   ~EventAction();

  public:
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
    void addEdep(G4double Edep){ fTotalEnergyDeposit += Edep; };
    G4double GetEnergyDeposit(){ return fTotalEnergyDeposit; };

    void addEvent(G4int event_counter){ EID += event_counter; };
    void InitializeEID(G4int EID_value){ EID = EID_value; };
        
  private:
    G4double fTotalEnergyDeposit;

    G4int dE1_HCID; G4int dE2_HCID; G4int dE3_HCID; G4int dE4_HCID;
    G4int E1_HCID;
    G4int dE5_HCID; G4int dE6_HCID; G4int dE7_HCID; G4int dE8_HCID;
    G4int E5_HCID;

    G4int counter;
    G4int EID;
};

#endif
