#include "DetectorConstruction.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "PlasSD.hh"
#include <iostream>
#include <iomanip>

DetectorConstruction::DetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct(){
    static const G4double inch = 2.54*cm;
    G4NistManager* manager = G4NistManager::Instance();
    manager->SetVerbose(0);
    G4double a, z;
    G4double density, fractionmass;
    G4int ncomponents, natoms;

 // *********************************************************************************************
 // ************************                                            *************************
 // ************************              M A T E R I A L S             *************************
 // ************************                                            *************************
 // *********************************************************************************************
    
    G4Element* C = new G4Element("Carbon","C", z= 6., a= 12.01*g/mole);
    G4Element* Na = new G4Element("Sodium","Na", z=11., a=22.98977*g/mole);
    G4Element* Pb = new G4Element("Lead","Pb", z=82., a=207.19*g/mole);
    G4Element* K = new G4Element("Potassium","K", z=19., a=39.0983*g/mole);
    G4Element* Ba = new G4Element("Barium","Ba", z=56., a=137.327*g/mole);
    G4Element* As = new G4Element("Arsenic","As", z=33., a=74.9216*g/mole);
    G4Element* Ti = new G4Element("Titanium","Ti", z=22., a=47.467*g/mole);
    G4Element* Al = new G4Element("Aluminum","Al", z=13., a=26.98*g/mole);
    G4Element* H  = manager->FindOrBuildElement(1);
    G4Element* N  = manager->FindOrBuildElement(7);
    G4Element* O  = manager->FindOrBuildElement(8);
    G4Element* Bi = manager->FindOrBuildElement(83);
    G4Element* Ge = manager->FindOrBuildElement(32);
    G4Element* Si = manager->FindOrBuildElement(14);
    G4Element* I  = manager->FindOrBuildElement(53);
    G4Element* Cs = manager->FindOrBuildElement(55);
    G4Element* Be = manager->FindOrBuildElement("Be");
    G4Element* Rb = manager->FindOrBuildElement("Rb");
    G4Element* Fe = manager->FindOrBuildElement("Fe");
    G4Element* Cr = manager->FindOrBuildElement("Cr");
    G4Element* Ni = manager->FindOrBuildElement("Ni");
    G4Element* Cu = manager->FindOrBuildElement("Cu");
    
    G4Material* Scintillator = new G4Material("Scintillator", density= 1.032*g/cm3, ncomponents=2);
    Scintillator->AddElement(C, natoms=9); Scintillator->AddElement(H, natoms=10);
    
    G4Material* Germanium = new G4Material("Germanium", density= 5.3*g/cm3, ncomponents=1);
    Germanium->AddElement(Ge, natoms=1);
    
    G4Material* Delrin = new G4Material("Delrin", density= 1.51*g/cm3, ncomponents=3);
    Delrin->AddElement(C, natoms=6); Delrin->AddElement(H, natoms=10); Delrin->AddElement(O, natoms=4);
    
    G4Material* BGO = new G4Material("BGO", density= 7.10*g/cm3, ncomponents=3);
    BGO->AddElement(O, natoms=12); BGO->AddElement(Ge, natoms= 3); BGO->AddElement(Bi, natoms= 4);
    
    G4Material* CsI = new G4Material("CsI", density= 4.534*g/cm3, ncomponents=2);
    CsI->AddElement(Cs, natoms=1); CsI->AddElement(I, natoms=1);
    
    G4Material* NaI = new G4Material("NaI", density= 3.67*g/cm3, ncomponents=2);
    NaI->AddElement(Na, natoms=1); NaI->AddElement(I, natoms=1);
    
    G4Material* Lead = new G4Material("Lead", density= 11.34*g/cm3, ncomponents=1);
    Lead->AddElement(Pb, natoms=1);

    G4Material* Silicon = new G4Material("Silicon", density= 2.330*g/cm3, ncomponents=1);
    Silicon->AddElement(Si, natoms=1);
    
    G4Material* Steel = new G4Material("Steel", density= 7.93*g/cm3, ncomponents=3);
    Steel->AddElement(Ni, fractionmass=0.11); Steel->AddElement(Cr, fractionmass=0.18); Steel->AddElement(Fe, fractionmass=0.71);
    
    G4Material* Beryllium = new G4Material("Beryllium", density= 1.850*g/cm3, ncomponents=1);
    Beryllium->AddElement(Be, natoms=1);
    
    G4Material* Titanium = new G4Material("Titanium", density= 4.540*g/cm3, ncomponents=1);
    Titanium->AddElement(Ti, natoms=1);
    
    G4Material* Aluminum = new G4Material("Aluminum", density= 2.7*g/cm3, ncomponents=1);
    Aluminum->AddElement(Al, natoms=1);
    
    G4Material* Mylar = new G4Material("Mylar", density= 1.39*g/cm3, ncomponents=3);
    Mylar->AddElement(C, fractionmass=0.625); Mylar->AddElement(H, fractionmass=0.042); Mylar->AddElement(O, fractionmass=0.333);
    
    G4Material* MCPglass = new G4Material("MCPglass", density= 2.5*g/cm3, ncomponents=9);
    MCPglass->AddElement(Pb, fractionmass=0.478);
    MCPglass->AddElement(O, fractionmass=0.258);
    MCPglass->AddElement(Si, fractionmass=0.182);
    MCPglass->AddElement(K, fractionmass=0.042);
    MCPglass->AddElement(Rb, fractionmass=0.018);
    MCPglass->AddElement(Ba, fractionmass=0.013);
    MCPglass->AddElement(As, fractionmass=0.004);
    MCPglass->AddElement(Cs, fractionmass=0.003);
    MCPglass->AddElement(Na, fractionmass=0.002);
    
    G4Material* Kapton = new G4Material("Kapton", density=1.42*g/cm3, ncomponents=4);
    Kapton->AddElement(H, fractionmass=0.026362);
    Kapton->AddElement(C, fractionmass=0.691133);
    Kapton->AddElement(N, fractionmass=0.073270);
    Kapton->AddElement(O, fractionmass=0.209235);
    
    // light guide
    G4Material* pmma = new G4Material("pmma", density=1.18*g/cm3, ncomponents=3);
    pmma->AddElement(C, natoms=5); pmma->AddElement(H, natoms=8); pmma->AddElement(O, natoms=2);
    
    G4Material* ceramic = new G4Material("ceramic", density=3.95*g/cm3, ncomponents=2);
    ceramic->AddElement(Al, natoms=2); ceramic->AddElement(O, natoms=3);
    
    G4Material* copper = new G4Material("copper", density=8.96*g/cm3,ncomponents=1);
    copper->AddElement(Cu, natoms=1);
    
// *********************************************************************************************
// ************************                                            *************************
// ************************     R O T A T I O N  M A T R I C E S       *************************
// ************************                                            *************************
// *********************************************************************************************

// Rotations around x-axis
  G4RotationMatrix* rm45 = new G4RotationMatrix(); rm45->rotateX(45.*deg);
  G4RotationMatrix* rm315 = new G4RotationMatrix(); rm315->rotateX(315.*deg);
  G4RotationMatrix* rm225 = new G4RotationMatrix(); rm225->rotateX(225.*deg);
  G4RotationMatrix* rm135 = new G4RotationMatrix(); rm135->rotateX(135.*deg);
  G4RotationMatrix* rm90 = new G4RotationMatrix(); rm90->rotateX(90.*deg);
  G4RotationMatrix* rm180 = new G4RotationMatrix(); rm180->rotateX(180.*deg);
  G4RotationMatrix* rm270 = new G4RotationMatrix(); rm270->rotateX(270.*deg);
  
// Rotations around y-axis
 G4RotationMatrix* rmy45 = new G4RotationMatrix(); rmy45->rotateY(45.*deg);
 G4RotationMatrix* rmy90 = new G4RotationMatrix(); rmy90->rotateY(90.*deg);
 G4RotationMatrix* rmy135 = new G4RotationMatrix(); rmy135->rotateY(135.*deg);
  
// Rotations around z-axis
 G4RotationMatrix* rmz45 = new G4RotationMatrix(); rmz45->rotateZ(45.*deg);
 
 G4RotationMatrix* rmz315 = new G4RotationMatrix(); rmz315->rotateZ(315.*deg);
 G4RotationMatrix* rmz225 = new G4RotationMatrix(); rmz225->rotateZ(225.*deg);
 G4RotationMatrix* rmz135 = new G4RotationMatrix(); rmz135->rotateZ(135.*deg);
 G4RotationMatrix* rmz90 = new G4RotationMatrix(); rmz90->rotateZ(90.*deg);
 G4RotationMatrix* rmz180 = new G4RotationMatrix(); rmz180->rotateZ(180.*deg);
 G4RotationMatrix* rmz270 = new G4RotationMatrix(); rmz270->rotateZ(270.*deg);
 
// newer rotation matrices, to go around more than one axis
 G4RotationMatrix* rm45rmy180 = new G4RotationMatrix(); rm45rmy180->rotateX(45.*deg); rm45rmy180->rotateY(180.*deg);
 G4RotationMatrix* rm315rmy180 = new G4RotationMatrix(); rm315rmy180->rotateX(315.*deg); rm315rmy180->rotateY(180.*deg);
 G4RotationMatrix* rm225rmy180 = new G4RotationMatrix();rm225rmy180->rotateX(225.*deg); rm225rmy180->rotateY(180.*deg);
 G4RotationMatrix* rm135rmy180 = new G4RotationMatrix(); rm135rmy180->rotateX(135.*deg); rm135rmy180->rotateY(180.*deg);
 G4RotationMatrix* rm90rmy90 = new G4RotationMatrix(); rm90rmy90->rotateX(90.*deg); rm90rmy90->rotateY(90.*deg);
 G4RotationMatrix* rm90rmz45 = new G4RotationMatrix(); rm90rmz45->rotateX(90.*deg); rm90rmz45->rotateZ(45.*deg);
 G4RotationMatrix* rmy45rmz45 = new G4RotationMatrix(); rmy45rmz45->rotateY(45.*deg); rmy45rmz45->rotateZ(45.*deg);
 G4RotationMatrix* rmy135rmz45 = new G4RotationMatrix(); rmy135rmz45->rotateY(135.*deg); rmy135rmz45->rotateZ(45.*deg);
 G4RotationMatrix* rmy90rm135 = new G4RotationMatrix(); rmy90rm135->rotateY(180.*deg); rmy90rm135->rotateX(135.*deg);
 G4RotationMatrix* rmz315rm90 = new G4RotationMatrix(); rmz315rm90->rotateZ(315.*deg); rmz315rm90->rotateX(90.*deg);
 G4RotationMatrix* rmz225rm90 = new G4RotationMatrix(); rmz225rm90->rotateZ(225.*deg); rmz225rm90->rotateX(90.*deg);
 G4RotationMatrix* rmz45rm90 = new G4RotationMatrix(); rmz45rm90->rotateZ(45.*deg); rmz45rm90->rotateX(90.*deg);
 G4RotationMatrix* rmz135rm90 = new G4RotationMatrix(); rmz135rm90->rotateZ(135.*deg); rmz135rm90->rotateX(90.*deg);
 G4RotationMatrix* rmz90rmy90 = new G4RotationMatrix(); rmz90rmy90->rotateZ(90.*deg); rmz90rmy90->rotateY(90.*deg);
 G4RotationMatrix* rmx45rmy90 = new G4RotationMatrix(); rmx45rmy90->rotateX(45.*deg); rmx45rmy90->rotateY(90.*deg);
 G4RotationMatrix* rmx90rmy90 = new G4RotationMatrix(); rmx90rmy90->rotateX(90.*deg); rmx90rmy90->rotateY(90.*deg);
 G4RotationMatrix* rmx180rmy90 = new G4RotationMatrix(); rmx180rmy90->rotateX(180.*deg); rmx180rmy90->rotateY(90.*deg);
 G4RotationMatrix* rmx270rmy90 = new G4RotationMatrix(); rmx270rmy90->rotateX(270.*deg); rmx270rmy90->rotateY(90.*deg);
    

// Define a vacuum
    G4double pressure, temperature;
    G4Material* Vacuum = new G4Material("Vacuum", z=1., a=1.008*g/mole, density= 1.e-25*g/cm3, kStateGas, temperature= 273.*kelvin, pressure= 1.3e-7*pascal);


//%%%%%%%%%%%%%%%%%%%%% Map of locations within trap %%%%%%%%%%%%%%%%%%%%%
//
//                                    | +x (top)
//                                    |
//                                    |
//                                    | +y = out of the page (front)
//                                    |
//    -z (left) ----------------------------------------------- +z (right)
//                                    |
//                                    | -y = into the page (back)
//                                    |
//                                    |
//                                    | -x (bottom)
//

   G4double WorldSizeX = 0.8*m; G4double WorldSizeY = 0.8*m; G4double WorldSizeZ = 0.8*m;
   G4Box* solidWorld = new G4Box("World",WorldSizeX, WorldSizeY, WorldSizeZ);
   G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,Vacuum,"World");
   
// G4PhysicalVolume* name = new G4PVPlacement(rotation, location, logical name, its name, its mother volume, boolean, copy number);
   G4VPhysicalVolume* physiWorld = new G4PVPlacement(0,G4ThreeVector(),logicWorld,"World",0,false,0);


    // *********************************************************************************************
    // *******************                                                       *******************
    // *******************     B E T A  D E T E C T O R  C O M P O N E N T S     *******************
    // *******************                                                       *******************
    // *********************************************************************************************

// General parameters for dE-E detectors

// Distance between center of trap and fronts of dE-E detectors
    G4double ScintDist = 57*mm; //ugh
    
// Thicknesses of components and rotations
    G4double KaptonWindowThickness = 2*4*um;
    G4RotationMatrix* KaptonWindow_rmLF = rm180;  //left-front
    G4RotationMatrix* KaptonWindow_rmBF = rmy90;  //bottom-front
    
// Kapton window sanwiched between two Al layers of this thickness
    G4double AlLayerThickness = 2*0.18*um;
    G4RotationMatrix* AlLayer_rmLF = rm180;
    G4RotationMatrix* AlLayer_rmBF = rmy90;
   
// Kapton window & Al layers sanwiched between two kapton layers of this thickness
    G4double KaptonSandwichThickness = 2*0.069*inch;
    G4RotationMatrix* KaptonSandwich_rmLF = rm180;
    G4RotationMatrix* KaptonSandwich_rmBF = rmy90;
   
    G4double EntryPortAThickness = 5.08*mm;
    G4RotationMatrix* EntryPortA_rmLF = rm180;
    G4RotationMatrix* EntryPortA_rmBF = rmy90;
    
    G4double EntryPortBThickness = 2*6.985*mm;
    G4RotationMatrix* EntryPortB_rmLF = rm180;
    G4RotationMatrix* EntryPortB_rmBF = rmy90;
   
    G4double LongerHousingThickness = 2*47.1629*mm;
    G4RotationMatrix* LongerHousing_rmLF = rm180;
    G4RotationMatrix* LongerHousing_rmBF = rmy90;
   
    G4double LightGuideThickness = 2*3.175*mm;
    G4RotationMatrix* LightGuide_rmLF = rm180;
    G4RotationMatrix* LightGuide_rmBF = rmy90;

    G4double LightGuideExtraThickness = 2*2.6712*mm;
    G4RotationMatrix* LightGuideExtra_rmLF = rm180;
    G4RotationMatrix* LightGuideExtra_rmBF = rmy90;
    
    G4double dEThickness = 2*0.5*mm;
    G4RotationMatrix* dE_rmLF = rm180;
    G4RotationMatrix* dE_rmBF = rmy90;
    
// Mylar foil is sandwiched between the dE detector and the extra light guide material
    G4double MylarFoilThickness = 2*3.8*um;
    G4RotationMatrix* MylarFoil_rmLF = rm180;
    G4RotationMatrix* MylarFoil_rmBF = rmy90;
    
    G4double EThickness = 2*50.8*mm;
    G4RotationMatrix* E_rmLF = rm180;
    G4RotationMatrix* E_rmBF = rmy90;
    
    G4double FudgeFactor = 2*mm;

// General parameters for dE-E detectors (END)


// Sandwich pieces for Kapton window
   G4Tubs* KaptonSandwich = new G4Tubs("KaptonSandwich",45*mm,55*mm,KaptonSandwichThickness/2,0.*deg,360.*deg);
   G4LogicalVolume* logicKaptonSandwich = new G4LogicalVolume(KaptonSandwich,Steel,"KaptonSandwich");
   G4VisAttributes* SandwichVisAtt = new G4VisAttributes(G4Colour(5.,3.,0.));
   SandwichVisAtt->SetForceSolid(true);
   logicKaptonSandwich->SetVisAttributes(SandwichVisAtt);
   
   
// Location: Kapton sandwich pieces (left-front)

   G4double KaptonSandwich1_x = 0;
   G4double KaptonSandwich1_y = 0;
   G4double KaptonSandwich1_z = -(ScintDist + KaptonSandwichThickness/2);
   std::cout << "KaptonSandwich1_z = " << std::setprecision(8) << KaptonSandwich1_z << std::endl;
   
   G4double KaptonSandwich2_x = 0;
   G4double KaptonSandwich2_y = 0;
   G4double KaptonSandwich2_z = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness/2);
   std::cout << "KaptonSandwich2_z = " << std::setprecision(8) << KaptonSandwich2_z << std::endl;

   G4VPhysicalVolume* physiKaptonSandwich1 =
    new G4PVPlacement(KaptonSandwich_rmLF,G4ThreeVector(KaptonSandwich1_x,KaptonSandwich1_y,KaptonSandwich1_z),logicKaptonSandwich,"KaptonSandwich1",logicWorld,false,0);

   G4VPhysicalVolume* physiKaptonSandwich2 =
    new G4PVPlacement(KaptonSandwich_rmLF,G4ThreeVector(KaptonSandwich2_x,KaptonSandwich2_y,KaptonSandwich2_z),logicKaptonSandwich,"KaptonSandwich2",logicWorld,false,0);

   // Location: Kapton sandwich pieces (bottom-front)

   G4double KaptonSandwich9_x = -(ScintDist + KaptonSandwichThickness/2);
   G4double KaptonSandwich9_y = 0;
   G4double KaptonSandwich9_z = 0;
   std::cout << "KaptonSandwich9_z = " << std::setprecision(8) << KaptonSandwich9_z << std::endl;
   
   G4double KaptonSandwich10_x = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness/2);
   G4double KaptonSandwich10_y = 0;
   G4double KaptonSandwich10_z = 0;
   std::cout << "KaptonSandwich10_z = " << std::setprecision(8) << KaptonSandwich10_z << std::endl;

   G4VPhysicalVolume* physiKaptonSandwich9 =
    new G4PVPlacement(KaptonSandwich_rmBF,G4ThreeVector(KaptonSandwich9_x,KaptonSandwich9_y,KaptonSandwich9_z),logicKaptonSandwich,"KaptonSandwich9",logicWorld,false,0);

   G4VPhysicalVolume* physiKaptonSandwich10 =
    new G4PVPlacement(KaptonSandwich_rmBF,G4ThreeVector(KaptonSandwich10_x,KaptonSandwich10_y,KaptonSandwich10_z),logicKaptonSandwich,"KaptonSandwich10",logicWorld,false,0);

// Sandwich pieces for Kapton window (END)=================================


// Kapton window
    G4Tubs* KaptonWindow = new G4Tubs("KaptonWindow",0.*mm,55*mm,KaptonWindowThickness/2,0.*deg,360.*deg);
   
    G4LogicalVolume* logicKaptonWindow = new G4LogicalVolume(KaptonWindow,Kapton,"KaptonWindow");
    
// Location: Kapton window (left-front)

    G4double KaptonWindow1_x = 0;
    G4double KaptonWindow1_y = 0;
    G4double KaptonWindow1_z = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness/2);
    std::cout << "KaptonWindow1_z = " << std::setprecision(8) << KaptonWindow1_z << std::endl;
   
    G4VPhysicalVolume* physiKaptonWindow1 = new G4PVPlacement(KaptonWindow_rmLF, G4ThreeVector(KaptonWindow1_x,KaptonWindow1_y,KaptonWindow1_z),logicKaptonWindow,"KaptonWindow1",logicWorld,false,0);
    
// Location: Kapton window (bottom-front)

    G4double KaptonWindow5_x = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness/2);
    G4double KaptonWindow5_y = 0;
    G4double KaptonWindow5_z = 0;
    std::cout << "KaptonWindow5_z = " << std::setprecision(8) << KaptonWindow5_z << std::endl;
   
    G4VPhysicalVolume* physiKaptonWindow5 = new G4PVPlacement(KaptonWindow_rmBF,G4ThreeVector(KaptonWindow5_x,KaptonWindow5_y,KaptonWindow5_z),logicKaptonWindow,"KaptonWindow5",logicWorld,false,0);
 
// Kapton window (END)
   

// Aluminium layers around Kapton
    G4Tubs* AlLayer= new G4Tubs("AlLayer",0.*mm,55*mm,AlLayerThickness,0.*deg,360.*deg);
    G4LogicalVolume* logicAlLayer = new G4LogicalVolume(AlLayer,Aluminum,"AlLayer");

// Location: Aluminum layers (left-front)
    G4double AlLayer1_x = 0;
    G4double AlLayer1_y = 0;
    G4double AlLayer1_z = -(ScintDist + KaptonSandwichThickness + AlLayerThickness/2);
    std::cout << "AlLayer1_z = " << std::setprecision(8) << AlLayer1_z << std::endl;

    G4double AlLayer2_x = 0;
    G4double AlLayer2_y = 0;
    G4double AlLayer2_z = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness/2);
    std::cout << "AlLayer2_z = " << std::setprecision(8) << AlLayer2_z << std::endl;

    G4VPhysicalVolume* physiAlLayer1 = new G4PVPlacement(AlLayer_rmLF,G4ThreeVector(AlLayer1_x,AlLayer1_y,AlLayer1_z),logicAlLayer,"AlLayer1",logicWorld,false,0);
    G4VPhysicalVolume* physiAlLayer2 = new G4PVPlacement(AlLayer_rmLF,G4ThreeVector(AlLayer2_x,AlLayer2_y,AlLayer2_z),logicAlLayer,"AlLayer2",logicWorld,false,0);


// Location: Aluminum layers (bottom-front)
   
    G4double AlLayer9_x = -(ScintDist + KaptonSandwichThickness + AlLayerThickness/2);
    G4double AlLayer9_y = 0;
    G4double AlLayer9_z = 0;
    std::cout << "AlLayer9_z = " << std::setprecision(8) << AlLayer9_z << std::endl;

    G4double AlLayer10_x = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness/2);
    G4double AlLayer10_y = 0;
    G4double AlLayer10_z = 0;
    std::cout << "AlLayer10_z = " << std::setprecision(8) << AlLayer10_z << std::endl;

    G4VPhysicalVolume* physiAlLayer9 = new G4PVPlacement(AlLayer_rmBF,G4ThreeVector(AlLayer9_x,AlLayer9_y,AlLayer9_z),logicAlLayer,"AlLayer9",logicWorld,false,0);
    G4VPhysicalVolume* physiAlLayer10 = new G4PVPlacement(AlLayer_rmBF,G4ThreeVector(AlLayer10_x,AlLayer10_y,AlLayer10_z),logicAlLayer,"AlLayer10",logicWorld,false,0);
  
// Aluminium layer on Kapton (END)
   
   
// Detector entry ports

    G4Cons* solidEntryPortA = new G4Cons("solidEntryPortA",45*mm,55*mm,49*mm,67*mm,EntryPortAThickness/2,0*deg,360*deg);
    G4Cons* solidEntryPortB = new G4Cons("solidEntryPortB",62.*mm,67*mm,77*mm,82.0*mm,EntryPortBThickness/2,0*deg,360*deg);

    G4LogicalVolume* logicEntryPortA = new G4LogicalVolume(solidEntryPortA,Steel,"logicEntryPortA");
   
    G4LogicalVolume* logicEntryPortB = new G4LogicalVolume(solidEntryPortB,Steel,"logicEntryPortB");
   
    G4VisAttributes * EntryPortAVisAtt = new G4VisAttributes(G4Colour(0.9,0.7,0.));//yellow
    G4VisAttributes * EntryPortBVisAtt = new G4VisAttributes(G4Colour(0.7,0.7,0.));
    EntryPortBVisAtt->SetForceSolid(true);
    EntryPortAVisAtt->SetForceSolid(true);
    logicEntryPortA->SetVisAttributes(EntryPortAVisAtt);
    logicEntryPortB->SetVisAttributes(EntryPortBVisAtt);
  
// Location: Entry ports (left-front)
   
    G4double EntryPortA1_x = 0;
    G4double EntryPortA1_y = 0;
    G4double EntryPortA1_z = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness/2);
    std::cout << "EntryPortA1_z = " << std::setprecision(10) << EntryPortA1_z << std::endl;

    G4double EntryPortB1_x = 0;
    G4double EntryPortB1_y = 0;
    G4double EntryPortB1_z = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + EntryPortBThickness/2);
    std::cout << "EntryPortB1_z = " << std::setprecision(10) << EntryPortB1_z << std::endl;

    G4VPhysicalVolume* physiEntryPortA1 = new G4PVPlacement(EntryPortA_rmLF,G4ThreeVector(EntryPortA1_x,EntryPortA1_y,EntryPortA1_z),logicEntryPortA,"EntryPortA1",logicWorld,false,0);
    G4VPhysicalVolume* physiEntryPortB1 = new G4PVPlacement(EntryPortB_rmLF,G4ThreeVector(EntryPortB1_x,EntryPortB1_y,EntryPortB1_z),logicEntryPortB,"EntryPortB1",logicWorld,false,0);
  
// Location: Entry ports (bottom-front)
   
    G4double EntryPortA5_x = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness/2);
    G4double EntryPortA5_y = 0;
    G4double EntryPortA5_z = 0;
    std::cout << "EntryPortA5_z = " << std::setprecision(10) << EntryPortA5_z << std::endl;

    G4double EntryPortB5_x = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + EntryPortBThickness/2);
    G4double EntryPortB5_y = 0;
    G4double EntryPortB5_z = 0;
    std::cout << "EntryPortB5_z = " << std::setprecision(10) << EntryPortB5_z << std::endl;

    G4VPhysicalVolume* physiEntryPortA5 = new G4PVPlacement(EntryPortA_rmBF,G4ThreeVector(EntryPortA5_x,EntryPortA5_y,EntryPortA5_z),logicEntryPortA,"EntryPortA5",logicWorld,false,0);
    G4VPhysicalVolume* physiEntryPortB5 = new G4PVPlacement(EntryPortB_rmBF,G4ThreeVector(EntryPortB5_x,EntryPortB5_y,EntryPortB5_z),logicEntryPortB,"EntryPortB5",logicWorld,false,0);
  
// Detector entry ports (END)
    
// Surrounding metal housing for plastic scintillator
   G4Tubs* SolidLongerHousing = new G4Tubs("SolidLongerHousing",77*mm,82*mm,LongerHousingThickness/2,0.*deg,360.*deg); //ugh
  
   G4LogicalVolume* logicLongerHousing = new G4LogicalVolume(SolidLongerHousing,Steel,"logicLongerHousing");
  
   G4VisAttributes * longerHousingVisAtt = new G4VisAttributes(G4Colour(0.5,0.7,0.0));
   longerHousingVisAtt->SetForceSolid(true);
   logicLongerHousing->SetVisAttributes(longerHousingVisAtt);

// Location: Housing (left-front)
   G4double LongerHousing1_x = 0;
   G4double LongerHousing1_y = 0;
   G4double LongerHousing1_z = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + EntryPortBThickness + LongerHousingThickness/2);
   std::cout << "LongerHousing1_z = " << std::setprecision(10) << LongerHousing1_z << std::endl;

   G4VPhysicalVolume* physiLongerHousing1 = new G4PVPlacement(LongerHousing_rmLF,G4ThreeVector(LongerHousing1_x,LongerHousing1_y,LongerHousing1_z),logicLongerHousing,"longerHousing1",logicWorld,false,0);

// Location: Housing (bottom-front)
   G4double LongerHousing5_x = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + EntryPortBThickness + LongerHousingThickness/2);
   G4double LongerHousing5_y = 0;
   G4double LongerHousing5_z = 0;
   std::cout << "LongerHousing5_z = " << std::setprecision(10) << LongerHousing5_z << std::endl;

   G4VPhysicalVolume* physiLongerHousing5 = new G4PVPlacement(LongerHousing_rmBF,G4ThreeVector(LongerHousing5_x,LongerHousing5_y,LongerHousing5_z),logicLongerHousing,"longerHousing5",logicWorld,false,0);
 
// Surrounding metal housing for plastic scintillator (END)
    
// Light guides
   G4Tubs* solidLightGuide = new G4Tubs("lightGuide",56*mm,60*mm,LightGuideThickness/2,0.*deg,360.*deg);
   G4LogicalVolume* logicLightGuide = new G4LogicalVolume(solidLightGuide,pmma,"logicLightGuide");
   G4VisAttributes* lightGuideVisAtt = new G4VisAttributes(G4Colour(0.4,0.,0.4));//shade of purple
   lightGuideVisAtt->SetForceSolid(true);
   logicLightGuide->SetVisAttributes(lightGuideVisAtt);
 
// Location: Light guide (left-front)
   G4double LightGuide1_x = 0;
   G4double LightGuide1_y = 0;
   G4double LightGuide1_z = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideThickness/2);
   std::cout << "LightGuide1_z = " << std::setprecision(10) << LightGuide1_z << std::endl;
  
   G4VPhysicalVolume* physiLightGuide1 = new G4PVPlacement(LightGuide_rmLF,G4ThreeVector(LightGuide1_x,LightGuide1_y,LightGuide1_z),logicLightGuide,"lightGuide1",logicWorld,false,0);
    
// Location: Light guide (bottom-front)
   G4double LightGuide5_x = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideThickness/2);
   G4double LightGuide5_y = 0;
   G4double LightGuide5_z = 0;
   std::cout << "LightGuide5_z = " << std::setprecision(10) << LightGuide5_z << std::endl;

   G4VPhysicalVolume* physiLightGuide5 = new G4PVPlacement(LightGuide_rmBF,G4ThreeVector(LightGuide5_x,LightGuide5_y,LightGuide5_z),logicLightGuide,"lightGuide5",logicWorld,false,0);
 
// Light guides (END)
    
// Extra part of light guide
   G4Tubs* solidLightGuideExtra = new G4Tubs("LightGuideExtra",53.5*mm,56*mm,LightGuideExtraThickness/2,0.*deg,360.*deg);
   G4LogicalVolume* logicLightGuideExtra = new G4LogicalVolume(solidLightGuideExtra,pmma,"logicLightGuideExtra");
   G4VisAttributes* LightGuideExtraVisAtt = new G4VisAttributes(G4Colour(0.,0.7,0.3));//shade of green
   LightGuideExtraVisAtt->SetForceSolid(true);
   logicLightGuideExtra->SetVisAttributes(LightGuideExtraVisAtt);

// Location: Light guide extra (left-front)
   G4double LightGuideExtra1_x = 0;
   G4double LightGuideExtra1_y = 0;
   G4double LightGuideExtra1_z = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness/2);
   std::cout << "LightGuideExtra1_z = " << std::setprecision(10) << LightGuideExtra1_z << std::endl;

   G4VPhysicalVolume* physiLightGuideExtra1 = new G4PVPlacement(LightGuideExtra_rmLF,G4ThreeVector(LightGuideExtra1_x,LightGuideExtra1_y,LightGuideExtra1_z),logicLightGuideExtra,"lightGuideExtra1",logicWorld,false,0);
  
// Location: Light guide extra (bottom-front)

   G4double LightGuideExtra5_x = -(ScintDist + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness/2);
   G4double LightGuideExtra5_y = 0;
   G4double LightGuideExtra5_z = 0;
   std::cout << "LightGuideExtra5_z = " << std::setprecision(10) << LightGuideExtra5_z << std::endl;

   G4VPhysicalVolume* physiLightGuideExtra5 = new G4PVPlacement(LightGuideExtra_rmBF,G4ThreeVector(LightGuideExtra5_x,LightGuideExtra5_y,LightGuideExtra5_z),logicLightGuideExtra,"lightGuideExtra5",logicWorld,false,0);
  
// Extra part of light guide (END)
   
   
// Delta E detectors
    G4Trap* solidPlastic = new G4Trap("Scintillator",dEThickness/2,0*deg,90*deg,25.*mm,0.0001*mm,50.*mm,0*deg,25*mm,0.0001*mm,50*mm,0*deg);
    //G4Trap(<#const G4String &pName#>, <#G4double pDz#>, <#G4double pTheta#>, <#G4double pPhi#>, <#G4double pDy1#>, <#G4double pDx1#>, <#G4double pDx2#>, <#G4double pAlp1#>, <#G4double pDy2#>, <#G4double pDx3#>, <#G4double pDx4#>, <#G4double pAlp2#>)
   
    G4LogicalVolume* logicdE1 = new G4LogicalVolume(solidPlastic,Scintillator,"Scintillator_dE1");
    G4LogicalVolume* logicdE2 = new G4LogicalVolume(solidPlastic,Scintillator,"Scintillator_dE2");
    G4LogicalVolume* logicdE3 = new G4LogicalVolume(solidPlastic,Scintillator,"Scintillator_dE3");
    G4LogicalVolume* logicdE4 = new G4LogicalVolume(solidPlastic,Scintillator,"Scintillator_dE4");
    G4LogicalVolume* logicdE5 = new G4LogicalVolume(solidPlastic,Scintillator,"Scintillator_dE5");
    G4LogicalVolume* logicdE6 = new G4LogicalVolume(solidPlastic,Scintillator,"Scintillator_dE6");
    G4LogicalVolume* logicdE7 = new G4LogicalVolume(solidPlastic,Scintillator,"Scintillator_dE7");
    G4LogicalVolume* logicdE8 = new G4LogicalVolume(solidPlastic,Scintillator,"Scintillator_dE8");

    G4VisAttributes * plasticVisAtt1 = new G4VisAttributes(G4Colour::Black());
    G4VisAttributes * plasticVisAtt2 = new G4VisAttributes(G4Colour::Red());
    G4VisAttributes * plasticVisAtt3 = new G4VisAttributes(G4Colour::Green());
    G4VisAttributes * plasticVisAtt4 = new G4VisAttributes(G4Colour::Magenta());
    
    plasticVisAtt1->SetForceSolid(true);
    plasticVisAtt2->SetForceSolid(true);
    plasticVisAtt3->SetForceSolid(true);
    plasticVisAtt4->SetForceSolid(true);
    
    logicdE1->SetVisAttributes(plasticVisAtt1);
    logicdE2->SetVisAttributes(plasticVisAtt2);
    logicdE3->SetVisAttributes(plasticVisAtt3);
    logicdE4->SetVisAttributes(plasticVisAtt4);
    logicdE5->SetVisAttributes(plasticVisAtt1);
    logicdE6->SetVisAttributes(plasticVisAtt2);
    logicdE7->SetVisAttributes(plasticVisAtt3);
    logicdE8->SetVisAttributes(plasticVisAtt4);
   
   

    G4double Plastic1_x = 0.*mm;
    G4double Plastic1_y = 25.*mm;
    G4double Plastic1_z = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness + dEThickness/2);
    std::cout << "Plastic1_x = " << std::setprecision(10) << Plastic1_x << std::endl;
    std::cout << "Plastic1_y = " << std::setprecision(10) << Plastic1_y << std::endl;
    std::cout << "Plastic1_z = " << std::setprecision(10) << Plastic1_z << std::endl;
    G4VPhysicalVolume* physiPlastic1 = new G4PVPlacement(0,G4ThreeVector(Plastic1_x,Plastic1_y,Plastic1_z),logicdE1,"Scintillator_dE1",logicWorld,false,0);

    G4double Plastic2_x = -25.*mm;
    G4double Plastic2_y = 0.*mm;
    G4double Plastic2_z = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness + dEThickness/2);
    std::cout << "Plastic2_x = " << std::setprecision(10) << Plastic2_x << std::endl;
    std::cout << "Plastic2_y = " << std::setprecision(10) << Plastic2_y << std::endl;
    std::cout << "Plastic2_z = " << std::setprecision(10) << Plastic2_z << std::endl;
    G4VPhysicalVolume* physiPlastic2 = new G4PVPlacement(rmz270,G4ThreeVector(Plastic2_x,Plastic2_y,Plastic2_z),logicdE2,"Scintillator_dE2",logicWorld,false,0);
   
    G4double Plastic3_x = 0.*mm;
    G4double Plastic3_y = -25.*mm;
    G4double Plastic3_z = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness + dEThickness/2);
    std::cout << "Plastic3_x = " << std::setprecision(10) << Plastic3_x << std::endl;
    std::cout << "Plastic3_y = " << std::setprecision(10) << Plastic3_y << std::endl;
    std::cout << "Plastic3_z = " << std::setprecision(10) << Plastic3_z << std::endl;
    G4VPhysicalVolume* physiPlastic3 = new G4PVPlacement(rmz180,G4ThreeVector(Plastic3_x,Plastic3_y,Plastic3_z),logicdE3,"Scintillator_dE3",logicWorld,false,0);

    G4double Plastic4_x = 25*mm;
    G4double Plastic4_y = 0.*mm;
    G4double Plastic4_z = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness + dEThickness/2);
    std::cout << "Plastic4_x = " << std::setprecision(10) << Plastic4_x << std::endl;
    std::cout << "Plastic4_y = " << std::setprecision(10) << Plastic4_y << std::endl;
    std::cout << "Plastic4_z = " << std::setprecision(10) << Plastic4_z << std::endl;
    G4VPhysicalVolume* physiPlastic4 = new G4PVPlacement(rmz90,G4ThreeVector(Plastic4_x,Plastic4_y,Plastic4_z),logicdE4,"Scintillator_dE4",logicWorld,false,0);

    
    G4double Plastic5_x = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness + dEThickness/2);
    G4double Plastic5_y = 25*mm;
    G4double Plastic5_z = 0.*mm;
    std::cout << "Plastic5_x = " << std::setprecision(10) << Plastic5_x << std::endl;
    std::cout << "Plastic5_y = " << std::setprecision(10) << Plastic5_y << std::endl;
    std::cout << "Plastic5_z = " << std::setprecision(10) << Plastic5_z << std::endl;
    G4VPhysicalVolume* physiPlastic5 = new G4PVPlacement(rmy90,G4ThreeVector(Plastic5_x,Plastic5_y,Plastic5_z),logicdE5,"Scintillator_dE5",logicWorld,false,0);
  
    G4double Plastic6_x = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness + dEThickness/2);
    G4double Plastic6_y = 0.*mm;
    G4double Plastic6_z = 25.*mm;
    std::cout << "Plastic6_x = " << std::setprecision(10) << Plastic6_x << std::endl;
    std::cout << "Plastic6_y = " << std::setprecision(10) << Plastic6_y << std::endl;
    std::cout << "Plastic6_z = " << std::setprecision(10) << Plastic6_z << std::endl;
    G4VPhysicalVolume* physiPlastic6 = new G4PVPlacement(rmx270rmy90,G4ThreeVector(Plastic6_x,Plastic6_y,Plastic6_z),logicdE6,"Scintillator_dE6",logicWorld,false,0);
   
    G4double Plastic7_x = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness + dEThickness/2);
    G4double Plastic7_y = -25.*mm;
    G4double Plastic7_z = 0.*mm;
    std::cout << "Plastic7_x = " << std::setprecision(10) << Plastic7_x << std::endl;
    std::cout << "Plastic7_y = " << std::setprecision(10) << Plastic7_y << std::endl;
    std::cout << "Plastic7_z = " << std::setprecision(10) << Plastic7_z << std::endl;
    G4VPhysicalVolume* physiPlastic7 = new G4PVPlacement(rmx180rmy90,G4ThreeVector(Plastic7_x,Plastic7_y,Plastic7_z),logicdE7,"Scintillator_dE7",logicWorld,false, 0);

    G4double Plastic8_x = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness + dEThickness/2);
    G4double Plastic8_y = 0.*mm;
    G4double Plastic8_z = -25.*mm;
    std::cout << "Plastic8_x = " << std::setprecision(10) << Plastic8_x << std::endl;
    std::cout << "Plastic8_y = " << std::setprecision(10) << Plastic8_y << std::endl;
    std::cout << "Plastic8_z = " << std::setprecision(10) << Plastic8_z << std::endl;
    G4VPhysicalVolume* physiPlastic8 = new G4PVPlacement(rmx90rmy90,G4ThreeVector(Plastic8_x,Plastic8_y,Plastic8_z),logicdE8,"Scintillator_dE8",logicWorld,false,0);

// Delta E detectors (END)
   
// Thin mylar foils
    G4Tubs* solidMylar = new G4Tubs("Mylar",0.*mm,53.34*mm,3.8*um,0.*deg,360.*deg);
    G4LogicalVolume* logicMylar = new G4LogicalVolume(solidMylar,Mylar,"Mylar");
    G4VisAttributes * mylarVisAtt = new G4VisAttributes(G4Colour(0.,0.,1.));//dark blue
    mylarVisAtt->SetForceSolid(true);
    logicMylar->SetVisAttributes(mylarVisAtt);
   
// Location: Mylar foil (left-front)
    G4double Mylar1_x = 0;
    G4double Mylar1_y = 0;
    G4double Mylar1_z = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness/2);
    std::cout << "Mylar1_z = " << std::setprecision(10) << Mylar1_z << std::endl;
    G4VPhysicalVolume* physiMylar1 = new G4PVPlacement(MylarFoil_rmLF,G4ThreeVector(Mylar1_x,Mylar1_y,Mylar1_z),logicMylar,"Mylar1",logicWorld,false,0);
   
// Location: Mylar foil (bottom-front)
    G4double Mylar5_x = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness/2);
    G4double Mylar5_y = 0;
    G4double Mylar5_z = 0;
    std::cout << "Mylar5_z = " << std::setprecision(10) << Mylar5_z << std::endl;
    G4VPhysicalVolume* physiMylar5 = new G4PVPlacement(MylarFoil_rmBF,G4ThreeVector(Mylar5_x,Mylar5_y,Mylar5_z),logicMylar,"Mylar5",logicWorld,false,0);

// Thin mylar foils (END)
       

// E detectors
    G4Tubs* solidE_B = new G4Tubs("E_B scint",0.*mm,66.675*mm,50.8*mm,0.*deg,360.*deg);
    G4Tubs* solidE_L = new G4Tubs("E_L scint",0.*mm,66.675*mm,50.8*mm,0.*deg,360.*deg);
 
    G4LogicalVolume* logicE1 = new G4LogicalVolume(solidE_L,Scintillator,"E1_scint");
   
    G4LogicalVolume* logicE5 = new G4LogicalVolume(solidE_B,Scintillator,"E5_scint");

    G4VisAttributes * DSSDVisAtt = new G4VisAttributes(G4Colour(0.,0.4,0.));
    DSSDVisAtt->SetForceSolid(true);
    logicE1->SetVisAttributes(DSSDVisAtt);
    logicE5->SetVisAttributes(DSSDVisAtt);
   
// Location: E detector (left-front)

    G4double E1_x = 0*mm;
    G4double E1_y = 0*mm;
    G4double E1_z = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness + dEThickness + EThickness/2);
    std::cout << "E1_z = " << std::setprecision(10) << E1_z << std::endl;

    G4VPhysicalVolume* physiE1 = new G4PVPlacement(E_rmLF,G4ThreeVector(E1_x,E1_y,E1_z),logicE1,"E1_scint",logicWorld,false,0);
   
// Location: E detector (bottom-front)
    G4double E5_x = -(ScintDist + FudgeFactor + KaptonSandwichThickness + AlLayerThickness + KaptonWindowThickness + AlLayerThickness + KaptonSandwichThickness + EntryPortAThickness + LightGuideExtraThickness + MylarFoilThickness + dEThickness + EThickness/2);
    G4double E5_y = 0*mm;
    G4double E5_z = 0*mm;
    std::cout << "E5_z = " << std::setprecision(10) << E5_z << std::endl;

    G4VPhysicalVolume* physiE5 = new G4PVPlacement(E_rmBF,G4ThreeVector(E5_x,E5_y,E5_z),logicE5,"E5_scint",logicWorld,false,0);
   
// E detectors (END)
   


// *********************************************************************************************
// ************************                                            *************************
// ************************          M C P  C O M P O N E N T S        *************************
// ************************                                            *************************
// *********************************************************************************************

// MCP rotations
    G4RotationMatrix* MCP_rmt = rmy90;  //top MCP
    G4RotationMatrix* MCP_rmr = 0;      //right MCP

// MCP plate dimensions
    G4double MCP_Plate_width = 80*mm;
    G4double MCP_Plate_length = 100*mm;
    G4double MCP_Plate_thickness = 3*1.5*mm; //Z-stack (three 1.5-mm-thick plates)
// MCP border dimensions
    G4double MCP_Border_width = MCP_Plate_width + 10*mm;
    G4double MCP_Border_length = MCP_Plate_length + 10*mm;
    G4double MCP_Border_thickness = 1.28*mm;
// MCP ceramic plate dimensions
    G4double MCP_CeramicPlate_width = MCP_Plate_width + 10*mm;
    G4double MCP_CeramicPlate_length = MCP_Plate_length + 10*mm;
    G4double MCP_CeramicPlate_thickness = 1*mm; //Z-stack (three 1.5-mm-thick plates)
// MCP ceramic base plate dimensions
    G4double MCP_CeramicBasePlate_width = MCP_Plate_width + 15*mm;
    G4double MCP_CeramicBasePlate_length = MCP_Plate_length + 15*mm;
    G4double MCP_CeramicBasePlate_thickness = 5.2*mm; //Z-stack (three 1.5-mm-thick plates)

// Distance from front face of MCP plate to center of trap
    G4double MCP_Plate_distance = 65*mm;
// Distance between the two borders of an MCP
    G4double MCP_DistBetweenBorders = 1.9*mm;
// Distance from front face of each border to center of trap
    G4double MCP_Border1_distance = MCP_Plate_distance-MCP_Border_thickness-MCP_DistBetweenBorders-MCP_Border_thickness;
    G4double MCP_Border2_distance = MCP_Plate_distance-MCP_Border_thickness;
// Distance between back of MCP and front of ceramic plate
    G4double MCP_DistBetweenMCPAndCeramicPlate = 3.38*mm;
// Distance from front face of ceramic plate to center of trap
    G4double MCP_CeramicPlate_distance = MCP_Plate_distance+MCP_Plate_thickness+MCP_DistBetweenMCPAndCeramicPlate;
// Distance between back of ceramic plate and front of ceramic base plate
    G4double MCP_DistBetweenCeramicPlateAndCeramicBasePlate = 2.8*mm;
// Distance from front face of ceramic base plate to center of trap
    G4double MCP_CeramicBasePlate_distance = MCP_CeramicPlate_distance+MCP_CeramicPlate_thickness+MCP_DistBetweenCeramicPlateAndCeramicBasePlate;


// Location of center of MCP plate
    G4double MCP_Plate_location = MCP_Plate_distance+MCP_Plate_thickness/2;
// Location of center of border 1
    G4double MCP_Border1_location = MCP_Border1_distance+MCP_Border_thickness/2;
// Location of center of border 2
    G4double MCP_Border2_location = MCP_Border2_distance+MCP_Border_thickness/2;
// Location of center of ceramic plate
    G4double MCP_CeramicPlate_location = MCP_CeramicPlate_distance+MCP_CeramicPlate_thickness/2;
// Location of center of ceramic base plate
    G4double MCP_CeramicBasePlate_location = MCP_CeramicBasePlate_distance+MCP_CeramicBasePlate_thickness/2;


// MCP plates
    G4Box* MCPnew = new G4Box("MCPnew", MCP_Plate_width/2, MCP_Plate_length/2, MCP_Plate_thickness/2);
    
    G4LogicalVolume* logicMCPtop = new G4LogicalVolume(MCPnew, MCPglass, "MCPtop");
    G4LogicalVolume* logicMCPright = new G4LogicalVolume(MCPnew, MCPglass, "MCPright");

    G4VisAttributes * MCPVisAtt = new G4VisAttributes(G4Colour(0.0,0.329,0.329));//bluish-green
    MCPVisAtt->SetForceWireframe(true);
    logicMCPtop->SetVisAttributes(MCPVisAtt);
    logicMCPright->SetVisAttributes(MCPVisAtt);
  
// Location: MCP 1 (top)
   G4VPhysicalVolume* physiMCPone = new G4PVPlacement(MCP_rmt,G4ThreeVector(MCP_Plate_location,0.,0.),logicMCPtop,"MCPtop",logicWorld,false,0);
   
// Location: MCP 2 (right)
   G4VPhysicalVolume* physiMCPtwo = new G4PVPlacement(MCP_rmr,G4ThreeVector(0.,0.,MCP_Plate_location),logicMCPright,"MCPright",logicWorld,false,0);
   
// MCP plates (END)
   
// MCP border pieces
    G4Box* MCPBorderOuter = new G4Box("MCPBorderOuter", MCP_Border_width/2, MCP_Border_length/2, MCP_Border_thickness/2);
    G4Box* MCPBorderInner = new G4Box("MCPBorderInner", MCP_Plate_width/2, MCP_Plate_length/2, 0.1+MCP_Border_thickness/2);
    G4SubtractionSolid* MCPBorder = new G4SubtractionSolid("MCPBorder",MCPBorderOuter,MCPBorderInner,0,G4ThreeVector(0.,0.,0.));

    G4LogicalVolume* logicMCPBorder = new G4LogicalVolume(MCPBorder, ceramic, "MCPBorder");

    G4VisAttributes * MCPBorderVisAtt = new G4VisAttributes(G4Colour(0.8,0.5,0.4));
    MCPBorderVisAtt->SetForceSolid(true);
    logicMCPBorder->SetVisAttributes(MCPBorderVisAtt);
   
// Location: MCP border pieces (top)
    G4VPhysicalVolume* physiMCPBorderTop1 = new G4PVPlacement(MCP_rmt,G4ThreeVector(MCP_Border1_location,0.,0.),logicMCPBorder,"MCPBorderTop1",logicWorld,false,0);
    G4VPhysicalVolume* physiMCPBorderTop2 = new G4PVPlacement(MCP_rmt,G4ThreeVector(MCP_Border2_location,0.,0.),logicMCPBorder,"MCPBorderTop2",logicWorld,false,0);

// Location: MCP border pieces (right)
    G4VPhysicalVolume* physiMCPBorderRight1 = new G4PVPlacement(MCP_rmr,G4ThreeVector(0.,0.,MCP_Border1_location),logicMCPBorder,"MCPBorderRight1",logicWorld,false,0);
    G4VPhysicalVolume* physiMCPBorderRight2 = new G4PVPlacement(MCP_rmr,G4ThreeVector(0.,0.,MCP_Border2_location),logicMCPBorder,"MCPBorderRight2",logicWorld,false,0);


// Thin ceramic plates behind MCP plates
    G4Box* MCPCeramicPlate = new G4Box("MCPCeramicPlate",MCP_CeramicPlate_width/2,MCP_CeramicPlate_length/2,MCP_CeramicPlate_thickness/2);
    G4LogicalVolume* logicMCPCeramicPlateTop = new G4LogicalVolume(MCPCeramicPlate, ceramic, "MCPCeramicPlateTop");
    G4LogicalVolume* logicMCPCeramicPlateRight = new G4LogicalVolume(MCPCeramicPlate, ceramic, "MCPCeramicPlateRight");
   
    G4VisAttributes * MCPCeramicPlateVisAtt = new G4VisAttributes(G4Colour(0.8,0.5,0.4));
    MCPCeramicPlateVisAtt->SetForceWireframe(true);
    logicMCPCeramicPlateTop->SetVisAttributes(MCPCeramicPlateVisAtt);
    logicMCPCeramicPlateRight->SetVisAttributes(MCPCeramicPlateVisAtt);
  
// Location: MCP Ceramic Plate (top)
    G4VPhysicalVolume* physiMCPCeramicPlateTop = new G4PVPlacement(MCP_rmt,G4ThreeVector(MCP_CeramicPlate_location,0.,0.),logicMCPCeramicPlateTop,"MCPCeramicPlateTop",logicWorld,false,0);

// Location: MCP Ceramic Plate (right)
    G4VPhysicalVolume* physiMCPCeramicPlateRight = new G4PVPlacement(MCP_rmr,G4ThreeVector(0.,0.,MCP_CeramicPlate_location),logicMCPCeramicPlateRight,"MCPCeramicPlateRight",logicWorld,false,0);

// Ceramic base plates attached to MCPs
    G4Box* MCPCeramicBasePlateOuter = new G4Box("MCPCeramicBasePlateOuter", MCP_CeramicBasePlate_width/2, MCP_CeramicBasePlate_length/2, MCP_CeramicBasePlate_thickness/2);
    G4Box* MCPCeramicBasePlateInner = new G4Box("MCPCeramicBasePlateInner", MCP_Plate_width/2, MCP_Plate_length/2, 0.1+MCP_CeramicBasePlate_thickness/2);
    G4SubtractionSolid* MCPCeramicBasePlate = new G4SubtractionSolid("MCPCeramicBasePlate",MCPCeramicBasePlateOuter,MCPCeramicBasePlateInner,0,G4ThreeVector(0.,0.,0.));

    G4LogicalVolume* logicMCPCeramicBasePlate = new G4LogicalVolume(MCPCeramicBasePlate, ceramic, "MCPCeramicBasePlate");

    G4VisAttributes * MCPCeramicBasePlateVisAtt = new G4VisAttributes(G4Colour(0.8,0.5,0.4));
    MCPCeramicBasePlateVisAtt->SetForceWireframe(true);
    logicMCPCeramicBasePlate->SetVisAttributes(MCPCeramicBasePlateVisAtt);
   
// Location: Ceramic base plate (top)
    G4VPhysicalVolume* physiMCPCeramicBasePlateTop = new G4PVPlacement(MCP_rmt,G4ThreeVector(MCP_CeramicBasePlate_location,0.,0.),logicMCPCeramicBasePlate,"MCPCeramicBasePlateTop",logicWorld,false,0);
    
// Location: Ceramic base plate (right)
    G4VPhysicalVolume* physiMCPCeramicBasePlateRight = new G4PVPlacement(MCP_rmr,G4ThreeVector(0.,0.,MCP_CeramicBasePlate_location),logicMCPCeramicBasePlate,"MCPCeramicBasePlateRight",logicWorld,false,0);


// *********************************************************************************************
// ************************                                            *************************
// ************************     I O N  T R A P  C O M P O N E N T S    *************************
// ************************                                            *************************
// *********************************************************************************************

    G4double  ElectrodeRadius = 1.5875*mm;
    G4double  ElectrodeLength = 50*cm;
    G4RotationMatrix* Electrode_rm = rm90;
    G4double RFElectrodeDist = 8*mm; // Distance between center of trap and center of RF electrode
    G4double GroundElectrodeDist = 13*mm; // Distance between center of trap and center of ground electrode
   
// Trap support plate
    G4double TrapSupportPlateWidth = 25.4*mm;  //Both trap support plates (TSP): Outer radius (just a guess)
    G4double TrapSupportPlateThickness = 1.02*mm;  //Both TSPs: Thickness (a guess)
    G4RotationMatrix* TrapSupportPlate_rm = rm90;  //Both TSPs: Rotation
    G4double TrapSupportPlateDist = (67.56/2)*mm + TrapSupportPlateThickness/2;

// Properties of pieces to be subtracted (8 holes from the electrodes four small holes, and one large hole are subtracted from a square of width TrapSupportPlateWidth to form one trap support plate):
     G4double TSPElectrodeHoleRadius = ElectrodeRadius;
     G4double TSPElectrodeHoleThickness = TrapSupportPlateThickness+0.1*mm;  //thickness of electrode hole
     G4double TSPSegmentRadius = 1.635*mm;  //radius of small hole
     G4double TSPSegmentThickness = TrapSupportPlateThickness+0.1*mm;  //thickness of small hole
     G4double TSPSegmentDist = 9.525*mm;  //distance from center of trap to center of small hole (25.4/2 - 4.81 + 1.635 mm)
     G4double TSPHoleRadius = 6.35*mm;  //radius of large hole in center of TSP
     G4double TSPHoleThickness = TrapSupportPlateThickness+0.1*mm;  //thickness of large hole
   
// Main RF shield
     //Inner box will be subtracted from outer box to form shield
    G4double MainRFShield_OuterBoxWidth = 95.25*mm;
    G4double MainRFShield_OuterBoxLength = 508*mm;
    G4double MainRFShield_InnerBoxWidth = 92.76*mm;
    G4double MainRFShield_InnerBoxLength = 508*mm+1*mm;
   
    G4double MainRFShield_HoleWidth1 = 2*37*mm;
    G4double MainRFShield_HoleLength1 = 2*37*mm;
    G4double MainRFShield_HoleThickness1 = (95.25-92.76+1)*mm;
    G4double MainRFShield_HoleWidth2 = 2*50*mm;
    G4double MainRFShield_HoleLength2 = 2*37*mm;
    
    G4double MainRFShield_HoleThickness2 = (95.25-92.76+1)*mm;
    G4double MainRFShield_HoleWidth3 = 2*50*mm;
    G4double MainRFShield_HoleLength3 = 2*37*mm;
    G4double MainRFShield_HoleThickness3 = (95.25-92.76+1)*mm;
    G4double MainRFShield_HoleWidth4 = 2*37*mm;
    G4double MainRFShield_HoleLength4 = 2*37*mm;
    G4double MainRFShield_HoleThickness4 = (95.25-92.76+1)*mm;
    G4RotationMatrix* MainRFShield_Hole1_rm = rmy90; //Rotation of hole 1
    G4RotationMatrix* MainRFShield_Hole2_rm = rmy90; //Rotation of hole 2
    G4RotationMatrix* MainRFShield_Hole3_rm = rmz90rmy90; //Rotation of hole 3
    G4RotationMatrix* MainRFShield_Hole4_rm = rmz90rmy90; //Rotation of hole 4

    G4RotationMatrix* MainRFShield_rm = rm90;  //Rotation of shield
   
// Electrodes (4 RF electrodes, 4 ground electrodes)
    G4Tubs* SolidElectrode = new G4Tubs("SolidElectrode",0*mm,ElectrodeRadius,ElectrodeLength/2,0.*deg,360.*deg);
    G4LogicalVolume* logicRFElectrode = new G4LogicalVolume(SolidElectrode,Steel,"logicRFElectrode");
    G4LogicalVolume* logicGroundElectrode = new G4LogicalVolume(SolidElectrode,Steel,"logicGroundElectrode");
   
    G4VisAttributes * RFElectrodeVisAtt = new G4VisAttributes(G4Colour(0.8,0.4,0.0));
    G4VisAttributes * GroundElectrodeVisAtt = new G4VisAttributes(G4Colour(0.753,0.753,0.753));
    RFElectrodeVisAtt->SetForceSolid(true);
    GroundElectrodeVisAtt->SetForceSolid(true);
    logicRFElectrode->SetVisAttributes(RFElectrodeVisAtt);
    logicGroundElectrode->SetVisAttributes(GroundElectrodeVisAtt);
   
    G4double RFElectrode1_x = RFElectrodeDist/sqrt((double)2);
    G4double RFElectrode1_y = 0*mm;
    G4double RFElectrode1_z = RFElectrodeDist/sqrt((double)2);
    G4VPhysicalVolume* physiRFElectrode1 = new G4PVPlacement(Electrode_rm,G4ThreeVector(RFElectrode1_x,RFElectrode1_y,RFElectrode1_z),logicRFElectrode,"RFElectrode1",logicWorld,false,0);

    G4double RFElectrode2_x = RFElectrodeDist/sqrt((double)2);
    G4double RFElectrode2_y = 0*mm;
    G4double RFElectrode2_z = -RFElectrodeDist/sqrt((double)2);
    G4VPhysicalVolume* physiRFElectrode2 = new G4PVPlacement(Electrode_rm,G4ThreeVector(RFElectrode2_x,RFElectrode2_y,RFElectrode2_z),logicRFElectrode,"RFElectrode2",logicWorld,false,0);
 
    G4double RFElectrode3_x = -RFElectrodeDist/sqrt((double)2);
    G4double RFElectrode3_y = 0*mm;
    G4double RFElectrode3_z = RFElectrodeDist/sqrt((double)2);
    G4VPhysicalVolume* physiRFElectrode3 = new G4PVPlacement(Electrode_rm,G4ThreeVector(RFElectrode3_x,RFElectrode3_y,RFElectrode3_z),logicRFElectrode,"RFElectrode3",logicWorld,false,0);
 
    G4double RFElectrode4_x = -RFElectrodeDist/sqrt((double)2);
    G4double RFElectrode4_y = 0*mm;
    G4double RFElectrode4_z = -RFElectrodeDist/sqrt((double)2);
    G4VPhysicalVolume* physiRFElectrode4 = new G4PVPlacement(Electrode_rm,G4ThreeVector(RFElectrode4_x,RFElectrode4_y,RFElectrode4_z),logicRFElectrode,"RFElectrode4",logicWorld,false,0);
   
    G4double GroundElectrode1_x = GroundElectrodeDist/sqrt((double)2);
    G4double GroundElectrode1_y = 0*mm;
    G4double GroundElectrode1_z = GroundElectrodeDist/sqrt((double)2);
    G4VPhysicalVolume* physiGroundElectrode1 = new G4PVPlacement(Electrode_rm,G4ThreeVector(GroundElectrode1_x,GroundElectrode1_y,GroundElectrode1_z),logicGroundElectrode,"GroundElectrode1",logicWorld,false,0);

    G4double GroundElectrode2_x = GroundElectrodeDist/sqrt((double)2);
    G4double GroundElectrode2_y = 0*mm;
    G4double GroundElectrode2_z = -GroundElectrodeDist/sqrt((double)2);
    G4VPhysicalVolume* physiGroundElectrode2 = new G4PVPlacement(Electrode_rm,G4ThreeVector(GroundElectrode2_x,GroundElectrode2_y,GroundElectrode2_z),logicGroundElectrode,"GroundElectrode2",logicWorld,false,0);

    G4double GroundElectrode3_x = -GroundElectrodeDist/sqrt((double)2);
    G4double GroundElectrode3_y = 0*mm;
    G4double GroundElectrode3_z = GroundElectrodeDist/sqrt((double)2);
    G4VPhysicalVolume* physiGroundElectrode3 = new G4PVPlacement(Electrode_rm,G4ThreeVector(GroundElectrode3_x,GroundElectrode3_y,GroundElectrode3_z),logicGroundElectrode,"GroundElectrode3",logicWorld,false,0);

    G4double GroundElectrode4_x = -GroundElectrodeDist/sqrt((double)2);
    G4double GroundElectrode4_y = 0*mm;
    G4double GroundElectrode4_z = -GroundElectrodeDist/sqrt((double)2);
    G4VPhysicalVolume* physiGroundElectrode4 = new G4PVPlacement(Electrode_rm,G4ThreeVector(GroundElectrode4_x,GroundElectrode4_y,GroundElectrode4_z),logicGroundElectrode,"GroundElectrode4",logicWorld,false,0);


// Trap-support plates
    G4Box* SolidTSPBox = new G4Box("SolidTSPBox",TrapSupportPlateWidth/2,TrapSupportPlateWidth/2,TrapSupportPlateThickness/2);
    G4Tubs* SolidTSPHole = new G4Tubs("SolidTSPHole",0*mm,TSPHoleRadius,TSPHoleThickness/2,0.*deg,360.*deg);
    G4Tubs* SolidTSPSegment = new G4Tubs("SolidTSPSegment",0*mm,TSPSegmentRadius,TSPSegmentThickness/2,0.*deg,360.*deg);
    G4Tubs* SolidTSPElectrodeHole = new G4Tubs("SolidTSPElectrodeHole",0*mm,TSPElectrodeHoleRadius,TSPElectrodeHoleThickness/2,0.*deg,360*deg);
    
    //G4subtractionSolid *name = new G4SubtractionSolid(name,solid1-solid2,rotation,translatio of solid2)
    G4SubtractionSolid* SolidTSPv1 = new G4SubtractionSolid("SolidTSPv1",SolidTSPBox,SolidTSPHole,0,G4ThreeVector(0,0,0));
    G4double TSPSegTrans = TSPSegmentDist;
    G4SubtractionSolid* SolidTSPv2 = new G4SubtractionSolid("SolidTSPv2",SolidTSPv1,SolidTSPSegment,0,G4ThreeVector(TSPSegTrans,0,0));
    G4SubtractionSolid* SolidTSPv3 = new G4SubtractionSolid("SolidTSPv3",SolidTSPv2,SolidTSPSegment,0,G4ThreeVector(-TSPSegTrans,0,0));
    G4SubtractionSolid* SolidTSPv4 = new G4SubtractionSolid("SolidTSPv4",SolidTSPv3,SolidTSPSegment,0,G4ThreeVector(0,TSPSegTrans,0));
    G4SubtractionSolid* SolidTSPv5 = new G4SubtractionSolid("SolidTSPv5",SolidTSPv4,SolidTSPSegment,0,G4ThreeVector(0,-TSPSegTrans,0));
  
    RFElectrode1_x = RFElectrodeDist/sqrt((double)2);
    RFElectrode1_y = RFElectrodeDist/sqrt((double)2);
    RFElectrode1_z = 0*mm;

    RFElectrode2_x = RFElectrodeDist/sqrt((double)2);
    RFElectrode2_y = -RFElectrodeDist/sqrt((double)2);
    RFElectrode2_z = 0*mm;

    RFElectrode3_x = -RFElectrodeDist/sqrt((double)2);
    RFElectrode3_y = RFElectrodeDist/sqrt((double)2);
    RFElectrode3_z = 0*mm;

    RFElectrode4_x = -RFElectrodeDist/sqrt((double)2);
    RFElectrode4_y = -RFElectrodeDist/sqrt((double)2);
    RFElectrode4_z = 0*mm;

    GroundElectrode1_x = GroundElectrodeDist/sqrt((double)2);
    GroundElectrode1_y = GroundElectrodeDist/sqrt((double)2);
    GroundElectrode1_z = 0*mm;

    GroundElectrode2_x = GroundElectrodeDist/sqrt((double)2);
    GroundElectrode2_y = -GroundElectrodeDist/sqrt((double)2);
    GroundElectrode2_z = 0*mm;

    GroundElectrode3_x = -GroundElectrodeDist/sqrt((double)2);
    GroundElectrode3_y = GroundElectrodeDist/sqrt((double)2);
    GroundElectrode3_z = 0*mm;

    GroundElectrode4_x = -GroundElectrodeDist/sqrt((double)2);
    GroundElectrode4_y = -GroundElectrodeDist/sqrt((double)2);
    GroundElectrode4_z = 0*mm;

    G4SubtractionSolid* SolidTSPv6 = new G4SubtractionSolid("SolidTSPv6",SolidTSPv5,SolidTSPElectrodeHole,0,G4ThreeVector(RFElectrode1_x,RFElectrode1_y,RFElectrode1_z));
    G4SubtractionSolid* SolidTSPv7 = new G4SubtractionSolid("SolidTSPv7",SolidTSPv6,SolidTSPElectrodeHole,0,G4ThreeVector(RFElectrode2_x,RFElectrode2_y,RFElectrode2_z));
    G4SubtractionSolid* SolidTSPv8 = new G4SubtractionSolid("SolidTSPv8",SolidTSPv7,SolidTSPElectrodeHole,0,G4ThreeVector(RFElectrode3_x,RFElectrode3_y,RFElectrode3_z));
    G4SubtractionSolid* SolidTSPv9 = new G4SubtractionSolid("SolidTSPv9",SolidTSPv8,SolidTSPElectrodeHole,0,G4ThreeVector(RFElectrode4_x,RFElectrode4_y,RFElectrode4_z));
    G4SubtractionSolid* SolidTSPv10 = new G4SubtractionSolid("SolidTSPv10",SolidTSPv9,SolidTSPElectrodeHole,0,G4ThreeVector(GroundElectrode1_x,GroundElectrode1_y,GroundElectrode1_z));
    G4SubtractionSolid* SolidTSPv11 = new G4SubtractionSolid("SolidTSPv11",SolidTSPv10,SolidTSPElectrodeHole,0,G4ThreeVector(GroundElectrode2_x,GroundElectrode2_y,GroundElectrode2_z));
    G4SubtractionSolid* SolidTSPv12 = new G4SubtractionSolid("SolidTSPv12",SolidTSPv11,SolidTSPElectrodeHole,0,G4ThreeVector(GroundElectrode3_x,GroundElectrode3_y,GroundElectrode3_z));
    G4SubtractionSolid* SolidTrapSupportPlate = new G4SubtractionSolid("SolidTSPv13",SolidTSPv12,SolidTSPElectrodeHole,0,G4ThreeVector(GroundElectrode4_x,GroundElectrode4_y,GroundElectrode4_z));

    G4LogicalVolume* logicTrapSupportPlate = new G4LogicalVolume(SolidTrapSupportPlate,Steel,"logicTrapSupportPlate");
   
    G4VisAttributes * TrapSupportPlateVisAtt = new G4VisAttributes(G4Colour(0.753,0.753,0.753));
    TrapSupportPlateVisAtt->SetForceSolid(true);
    logicTrapSupportPlate->SetVisAttributes(TrapSupportPlateVisAtt);
   
    G4double TrapSupportPlate1_x = 0*mm;
    G4double TrapSupportPlate1_y = TrapSupportPlateDist;
    G4double TrapSupportPlate1_z = 0*mm;
    G4VPhysicalVolume* physiTrapSupportPlate1 = new G4PVPlacement(TrapSupportPlate_rm,G4ThreeVector(TrapSupportPlate1_x,TrapSupportPlate1_y,TrapSupportPlate1_z),logicTrapSupportPlate,"TrapSupportPlate1",logicWorld,false,0);
   
    G4double TrapSupportPlate2_x = 0*mm;
    G4double TrapSupportPlate2_y = -TrapSupportPlateDist;
    G4double TrapSupportPlate2_z = 0*mm;
    G4VPhysicalVolume* physiTrapSupportPlate2 = new G4PVPlacement(TrapSupportPlate_rm,G4ThreeVector(TrapSupportPlate2_x,TrapSupportPlate2_y,TrapSupportPlate2_z),logicTrapSupportPlate,"TrapSupportPlate2",logicWorld,false,0);
  
// Main RF shield (Long rectangular tube)
    G4Box* SolidMainRFShield_OuterBox = new G4Box("SolidMainRFShield_OuterBox",MainRFShield_OuterBoxWidth/2,MainRFShield_OuterBoxWidth/2,MainRFShield_OuterBoxLength/2);
    G4Box*SolidMainRFShield_InnerBox = new G4Box("SolidMainRFShield_InnerBox",MainRFShield_InnerBoxWidth/2,MainRFShield_InnerBoxWidth/2,MainRFShield_InnerBoxLength/2);
    G4Box*SolidMainRFShield_Hole1 = new G4Box("SolidMainRFShield_Hole1",MainRFShield_HoleWidth1/2,MainRFShield_HoleThickness1/2,MainRFShield_HoleLength1/2);
    G4Box*SolidMainRFShield_Hole2 = new G4Box("SolidMainRFShield_Hole2",MainRFShield_HoleWidth2/2,MainRFShield_HoleThickness2/2,MainRFShield_HoleLength2/2);
    G4Box*SolidMainRFShield_Hole3 = new G4Box("SolidMainRFShield_Hole3",MainRFShield_HoleWidth3/2,MainRFShield_HoleThickness3/2,MainRFShield_HoleLength3/2);
    G4Box*SolidMainRFShield_Hole4 = new G4Box("SolidMainRFShield_Hole4",MainRFShield_HoleWidth4/2,MainRFShield_HoleThickness4/2,MainRFShield_HoleLength4/2);
    
    G4SubtractionSolid* SolidMainRFShieldv1 = new G4SubtractionSolid("SolidMainRFShieldv1",SolidMainRFShield_OuterBox,SolidMainRFShield_InnerBox,0,G4ThreeVector(0,0,0));
    G4double MainRFShield_HoleDist = MainRFShield_InnerBoxWidth/2 + (MainRFShield_OuterBoxWidth-MainRFShield_InnerBoxWidth)/4;
    G4SubtractionSolid* SolidMainRFShieldv2 = new G4SubtractionSolid("SolidMainRFShieldv2",SolidMainRFShieldv1,SolidMainRFShield_Hole1,MainRFShield_Hole1_rm,G4ThreeVector(0,MainRFShield_HoleDist,0));
    G4SubtractionSolid* SolidMainRFShieldv3 = new G4SubtractionSolid("SolidMainRFShieldv3",SolidMainRFShieldv2,SolidMainRFShield_Hole2,MainRFShield_Hole2_rm,G4ThreeVector(0,-MainRFShield_HoleDist,0));
    G4SubtractionSolid* SolidMainRFShieldv4 = new G4SubtractionSolid("SolidMainRFShieldv4",SolidMainRFShieldv3,SolidMainRFShield_Hole3,MainRFShield_Hole3_rm,G4ThreeVector(MainRFShield_HoleDist,0,0));
    G4SubtractionSolid* SolidMainRFShield = new G4SubtractionSolid("SolidMainRFShieldv5",SolidMainRFShieldv4,SolidMainRFShield_Hole4,MainRFShield_Hole4_rm,G4ThreeVector(-MainRFShield_HoleDist,0,0));
   
    G4LogicalVolume* logicMainRFShield = new G4LogicalVolume(SolidMainRFShield,Steel,"logicMainRFShield");

    G4VisAttributes * MainRFShieldVisAtt = new G4VisAttributes(G4Colour(0.8,0.4,0.0));
    MainRFShieldVisAtt->SetForceSolid(true);
    logicMainRFShield->SetVisAttributes(MainRFShieldVisAtt);
       
    G4VPhysicalVolume* physiMainRFShield = new G4PVPlacement(MainRFShield_rm,G4ThreeVector(0,0,0),logicMainRFShield,"MainRFShield",logicWorld,false,0);



// *********************************************************************************************
// ************************                                            *************************
// ************************         H P G e  D E T E C T O R S         *************************
// ************************                                            *************************
// *********************************************************************************************

 
    G4RotationMatrix* T_Clover_rm = rmy90;  //TR_Clover: Rotation
    G4RotationMatrix* R_Clover_rm = 0;  //BR_Clover: Rotation
   
    G4double CloverEndcapThickness = 0.1*25.4*mm;
    G4double CloverEndcapWidth = 2*((3.69-0.2)*25.4*mm)/sqrt((double)2);
// Distance from center of trap to front of endcap
    G4double CloverEndcapDist = 85*mm;
    G4double CloverCrystalThickness = 70*mm;
    G4double CloverCrystalWidth = 95*mm;
// Distance from back of endcap to front of crystal
    G4double CloverEndcapCrystalDist = 0*mm;

    G4Box* solidCloverEndcap = new G4Box("solidCloverEndcap", CloverEndcapWidth/2, CloverEndcapWidth/2, CloverEndcapThickness/2);
   
    G4LogicalVolume* logicCloverEndcap = new G4LogicalVolume(solidCloverEndcap, Steel, "logicCloverEndcap");
   
    G4VisAttributes* CloverEndcapVisAtt = new G4VisAttributes(G4Colour(0.0,0.329,0.329));//bluish-green
    CloverEndcapVisAtt->SetForceWireframe(true);
    logicCloverEndcap->SetVisAttributes(CloverEndcapVisAtt);
   
// Location: Clover (Top)
    G4double T_CloverEndcap_x = (CloverEndcapDist + CloverEndcapThickness/2);
    G4double T_CloverEndcap_y = 0;
    G4double T_CloverEndcap_z = 0;
    G4VPhysicalVolume* physiT_CloverEndcap = new G4PVPlacement(T_Clover_rm,G4ThreeVector(T_CloverEndcap_x, T_CloverEndcap_y, T_CloverEndcap_z),logicCloverEndcap,"T_CloverEndcap",logicWorld,false,0);
   
// Location: Clover (Right)
    G4double R_CloverEndcap_x = 0;
    G4double R_CloverEndcap_y = 0;
    G4double R_CloverEndcap_z = CloverEndcapDist + CloverEndcapThickness/2;
    G4VPhysicalVolume* physiR_CloverEndcap = new G4PVPlacement(R_Clover_rm,G4ThreeVector(R_CloverEndcap_x, R_CloverEndcap_y, R_CloverEndcap_z),logicCloverEndcap,"R_CloverEndcap",logicWorld,false,0);

// Crystals

    G4Box* solidCloverCrystal = new G4Box("solidCloverCrystal", CloverCrystalWidth/2, CloverCrystalWidth/2, CloverCrystalThickness/2);
    G4LogicalVolume* logicCloverCrystal = new G4LogicalVolume(solidCloverCrystal, Germanium, "logicCloverCrystal");
   
    G4VisAttributes * CloverCrystalVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,0));//green
    CloverCrystalVisAtt->SetForceWireframe(true);
    logicCloverCrystal->SetVisAttributes(CloverCrystalVisAtt);
   
// Location: Clover (Top)
    G4double T_CloverCrystal_x = (CloverEndcapDist + CloverEndcapThickness + CloverEndcapCrystalDist + CloverCrystalThickness/2);
    G4double T_CloverCrystal_y = 0;
    G4double T_CloverCrystal_z = 0;
    G4VPhysicalVolume* physiT_CloverCrystal = new G4PVPlacement(T_Clover_rm,G4ThreeVector(T_CloverCrystal_x, T_CloverCrystal_y, T_CloverCrystal_z),logicCloverCrystal,"T_CloverCrystal",logicWorld,false,0);
   
// Location: Clover (Right)
    G4double R_CloverCrystal_x = 0;
    G4double R_CloverCrystal_y = 0;
    G4double R_CloverCrystal_z = CloverEndcapDist + CloverEndcapThickness + CloverEndcapCrystalDist + CloverCrystalThickness/2;
    G4VPhysicalVolume* physiR_CloverCrystal = new G4PVPlacement(R_Clover_rm,G4ThreeVector(R_CloverCrystal_x, R_CloverCrystal_y, R_CloverCrystal_z),logicCloverCrystal,"R_CloverCrystal",logicWorld,false,0);

//%%%%%%%%%%%%%%%%% Defining sensitive detectors %%%%%%%%%%%%%%%%%%%%%%%%
  
    PlasSD* dE1 = new PlasSD("dE1"); PlasSD* dE2 = new PlasSD("dE2"); PlasSD* dE3 = new PlasSD("dE3"); PlasSD* dE4 = new PlasSD("dE4");
    PlasSD* E1 = new PlasSD("E1");
    PlasSD* dE5 = new PlasSD("dE5"); PlasSD* dE6 = new PlasSD("dE6");PlasSD* dE7 = new PlasSD("dE7"); PlasSD* dE8 = new PlasSD("dE8");
    PlasSD* E5= new PlasSD("E5");

    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    SDman->AddNewDetector(dE1);SDman->AddNewDetector(dE2); SDman->AddNewDetector(dE3);SDman->AddNewDetector(dE4);
    SDman->AddNewDetector(E1);
    SDman->AddNewDetector(dE5); SDman->AddNewDetector(dE6); SDman->AddNewDetector(dE7); SDman->AddNewDetector(dE8);
    SDman->AddNewDetector(E5);
    
    logicdE1->SetSensitiveDetector(dE1); logicdE2->SetSensitiveDetector(dE2); logicdE3->SetSensitiveDetector(dE3); logicdE4->SetSensitiveDetector(dE4);
    logicE1->SetSensitiveDetector(E1);
    logicdE5->SetSensitiveDetector(dE5); logicdE6->SetSensitiveDetector(dE6); logicdE7->SetSensitiveDetector(dE7); logicdE8->SetSensitiveDetector(dE8);
    logicE5->SetSensitiveDetector(E5);
    
    return physiWorld;
}

