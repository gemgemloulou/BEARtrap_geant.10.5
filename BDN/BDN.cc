#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "Analysis.hh"

#include "G4UImanager.hh"
#include "Randomize.hh"
#include "G4PhysListFactory.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "SteppingVerbose.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

int main(int argc,char** argv) {

	//choose the Random engine
	G4Random::setTheEngine(new CLHEP::RanecuEngine);

	// Construct the default run manager
	#ifdef G4MULTITHREADED
	G4MTRunManager* runManager = new G4MTRunManager;
	#else
    G4VSteppingVerbose::SetInstance(new SteppingVerbose);
    G4RunManager* runManager = new G4RunManager;
	#endif

	// set mandatory initialization classes
	runManager->SetUserInitialization(new DetectorConstruction);
	runManager->SetUserInitialization(new PhysicsList);

	// set user action classes
	runManager->SetUserInitialization(new ActionInitialization());

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetFirstHistoId(1);

	G4String fileName = "BDN";
	analysisManager->OpenFile(fileName);

	// Creating histograms

	analysisManager->CreateH1("1","Plastic dE 1",2000,0,20000);
	analysisManager->CreateH1("2","Plastic dE 2",2000,0,20000);
	analysisManager->CreateH1("3","Plastic dE 3",2000,0,20000);
	analysisManager->CreateH1("4","Plastic dE 4",2000,0,20000);
  analysisManager->CreateH1("9","Plastic E 1",2000,0,20000);

	analysisManager->CreateH1("5","Plastic dE 5",2000,0,20000);
	analysisManager->CreateH1("6","Plastic dE 6",2000,0,20000);
	analysisManager->CreateH1("7","Plastic dE 7",2000,0,20000);
	analysisManager->CreateH1("8","Plastic dE 8",2000,0,20000);
	analysisManager->CreateH1("10","Plastic E 5",2000,0,20000);


	//Initialize G4 kernel
	runManager->Initialize();

//These 4 lines moved here by Barbara Wang (2/13/2015)
#ifdef G4VIS_USE
     G4VisManager* visManager = new G4VisExecutive;
     visManager->Initialize();
#endif

	// get the pointer to the User Interface manager
	G4UImanager* UI = G4UImanager::GetUIpointer();

  if (argc!=1){
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
    }else{

    #ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
      ui->SessionStart();
      delete ui;
    #endif
    }


#ifdef G4VIS_USE
     delete visManager;
#endif

    analysisManager->Write();
    analysisManager->CloseFile();
    delete runManager;
    delete analysisManager;

    return 0;
}
