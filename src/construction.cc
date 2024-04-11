#include "construction.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include <algorithm>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{

    DefineMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::DefineMaterials()
{

  G4NistManager *nist = G4NistManager::Instance();
  G4int ncomponents, natoms;
  G4double massfraction;

  G4double Vdens = 1.e-25*g/cm3;
  G4double Vpres = 1.e-19*pascal;
  G4double Vtemp = 0.1*kelvin;

  G4double a, z;
  C = nist->FindOrBuildElement("C");
  N  = new G4Element("Nitrogen","N",7.,14.007*g/mole);
  O  = new G4Element("Oxygen","O",8.,15.999*g/mole);
  F  = new G4Element("Fluorine","F",9.,18.998*g/mole);

  // boron
  G4Isotope* B10 = new G4Isotope("B10", 5, 10);
  G4Isotope* B11 = new G4Isotope("B11", 5, 11);
  G4Element* B = new G4Element("Boron", "B", ncomponents=2);
  B->AddIsotope(B10, 19.9*perCent);
  B->AddIsotope(B11, 80.1*perCent);
  G4Material* boron = new G4Material("boron", 2.46*g/cm3, ncomponents=1, kStateSolid,293*kelvin, 1*atmosphere);
  boron->AddElement(B, natoms=1);

   // pressurized water
  G4Element* H  = new G4Element("TS_H_of_Water" ,"H" , 1., 1.0079*g/mole);
  G4Material* H2O =
  new G4Material("Water_ts", 1.000*g/cm3, ncomponents=2,
                         kStateLiquid, 593*kelvin, 150*bar);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  H2O->GetIonisation()->SetMeanExcitationEnergy(78.0*eV);
  // vacuum
  Vacc = new G4Material("Galactic", z=1, a=1.01*g/mole, Vdens, kStateGas, Vtemp, Vpres);
  // air
  G4Element* N = new G4Element("Nitrogen", "N", 7., 14.01*g/mole);
  Air = new G4Material("air", 1.290*mg/cm3, ncomponents=2, kStateGas, 293*kelvin, 1*atmosphere);
  Air->AddElement(N, massfraction=70.*perCent);
  Air->AddElement(O, massfraction=30.*perCent);

  // polyethilene
  G4Element* Hpe = new G4Element("TS_H_of_Polyethylene", "H", 1, 1.0079*g/mole);
  G4Element* Cpe = new G4Element("Carbon", "C", 6, 12.01*g/mole);
  polyethylene = new G4Material("polyethylene", 0.93*g/cm3, ncomponents=2, kStateSolid, 293*kelvin, 1*atmosphere);
  polyethylene->AddElement(Hpe, natoms=4);
  polyethylene->AddElement(Cpe, natoms=2);

  // borated polyethilene
  b_polyethylene = new G4Material("b_polyethylene",0.94*g/cm3,ncomponents=4,kStateSolid,293*kelvin,1*atmosphere);
  b_polyethylene->AddElement(Hpe, 11.6*perCent);
  b_polyethylene->AddElement(Cpe, 61.2*perCent);
  b_polyethylene->AddElement(B, 5*perCent);
  b_polyethylene->AddElement(O, 22.2*perCent);
  

  // Define the lead material
  leadMaterial = new G4Material("Lead", 82, 207.2 * g/mole, 11.35 * g/cm3);

  //...............creating the materials for the scintillator..............................
  //----------------------------------- CarbonTetrafluoride ------------------------
  G4double pressure = 0.0328947*atmosphere; //25Torr
  G4double temperature = 293.15*kelvin; // 
  CF4 = new G4Material("CF4", 0.1223*mg/cm3,2,kStateGas,temperature,pressure);
  CF4->AddElement(C,1);
  CF4->AddElement(F,4);

//....................End of scintillator material........................................




}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
  // The world
  fBoxSize = 2*m;


  sBox = new G4Box("world",                             //its name
                   fBoxSize/2,fBoxSize/2,fBoxSize/2);   //its dimensions

  fLBox = new G4LogicalVolume(sBox,                     //its shape
                             Vacc,                      //its material
                             "World");                  //its name

  fPBox = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(),            //at (0,0,0)
                            fLBox,                      //its logical volume
                            "World",                    //its name
                            0,                          //its mother  volume
                            false,                      //no boolean operation
                            0);                         //copy number

//The HDPE_block1

  fblockSize = 10*cm;


  HDPE_Box1 = new G4Box("HDPE1",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV1 = new G4LogicalVolume(HDPE_Box1,                     //its shape
                              polyethylene,                      //its material
                             "HDPE1");                  //its name

  HDPE_PV1 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,0,5*cm),            //at (0,0,0)
                             HDPE_LV1,                      //its logical volume
                            "HDPE1",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

//The HDPE_block2


  HDPE_Box2 = new G4Box("HDPE2",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV2 = new G4LogicalVolume(HDPE_Box2,                     //its shape
                              polyethylene,                      //its material
                             "HDPE2");                  //its name

  HDPE_PV2 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,10*cm,5*cm),            //at (0,0,0)
                             HDPE_LV2,                      //its logical volume
                            "HDPE2",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

 //The HDPE_block3


  HDPE_Box3 = new G4Box("HDPE3",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV3 = new G4LogicalVolume(HDPE_Box3,                     //its shape
                              polyethylene,                      //its material
                             "HDPE3");                  //its name

  HDPE_PV3 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,-10*cm,5*cm),            //at (0,0,0)
                             HDPE_LV3,                      //its logical volume
                            "HDPE3",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

  //The HDPE_block4


  HDPE_Box4 = new G4Box("HDPE4",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV4 = new G4LogicalVolume(HDPE_Box4,                     //its shape
                              polyethylene,                      //its material
                             "HDPE4");                  //its name

  HDPE_PV4 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,10*cm,15*cm),            //at (0,0,0)
                             HDPE_LV4,                      //its logical volume
                            "HDPE4",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

//The HDPE_block5


  HDPE_Box5 = new G4Box("HDPE5",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV5 = new G4LogicalVolume(HDPE_Box5,                     //its shape
                              polyethylene,                      //its material
                             "HDPE5");                  //its name

  HDPE_PV5 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,-10*cm,15*cm),            //at (0,0,0)
                             HDPE_LV5,                      //its logical volume
                            "HDPE5",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number
 //The HDPE_block6


  HDPE_Box6 = new G4Box("HDPE6",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV6 = new G4LogicalVolume(HDPE_Box6,                     //its shape
                              polyethylene,                      //its material
                             "HDPE6");                  //its name

  HDPE_PV6 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(10*cm,0,5*cm),            //at (0,0,0)
                             HDPE_LV6,                      //its logical volume
                            "HDPE6",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

  //The HDPE_block7


  HDPE_Box7 = new G4Box("HDPE7",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV7 = new G4LogicalVolume(HDPE_Box7,                     //its shape
                              polyethylene,                      //its material
                             "HDPE7");                  //its name

  HDPE_PV7 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(-10*cm,0,5*cm),            //at (0,0,0)
                             HDPE_LV7,                      //its logical volume
                            "HDPE7",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


//The HDPE_block8


  HDPE_Box8 = new G4Box("HDPE8",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV8 = new G4LogicalVolume(HDPE_Box8,                     //its shape
                              polyethylene,                      //its material
                             "HDPE8");                  //its name

  HDPE_PV8 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(10*cm,10*cm,5*cm),            //at (0,0,0)
                             HDPE_LV8,                      //its logical volume
                            "HDPE8",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


     //The HDPE_block9


  HDPE_Box9 = new G4Box("HDPE9",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV9 = new G4LogicalVolume(HDPE_Box9,                     //its shape
                              polyethylene,                      //its material
                             "HDPE9");                  //its name

  HDPE_PV9 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(10*cm,-10*cm,5*cm),            //at (0,0,0)
                             HDPE_LV9,                      //its logical volume
                            "HDPE9",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

//The HDPE_block10

  HDPE_Box10 = new G4Box("HDPE10",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV10 = new G4LogicalVolume(HDPE_Box10,                     //its shape
                              polyethylene,                      //its material
                             "HDPE10");                  //its name

  HDPE_PV10 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(-10*cm,10*cm,5*cm),            //at (0,0,0)
                             HDPE_LV10,                      //its logical volume
                            "HDPE10",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

   //The HDPE_block11

  HDPE_Box11 = new G4Box("HDPE11",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV11 = new G4LogicalVolume(HDPE_Box11,                     //its shape
                              polyethylene,                      //its material
                             "HDPE11");                  //its name

  HDPE_PV11 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(-10*cm,-10*cm,5*cm),            //at (0,0,0)
                             HDPE_LV11,                      //its logical volume
                            "HDPE11",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


//The HDPE_block12


  HDPE_Box12 = new G4Box("HDPE12",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV12 = new G4LogicalVolume(HDPE_Box12,                     //its shape
                              polyethylene,                      //its material
                             "HDPE12");                  //its name

  HDPE_PV12 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(-10*cm,-10*cm,15*cm),            //at (0,0,0)
                             HDPE_LV12,                      //its logical volume
                            "HDPE12",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number
 //The HDPE_block13


  HDPE_Box13 = new G4Box("HDPE13",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV13 = new G4LogicalVolume(HDPE_Box13,                     //its shape
                              polyethylene,                      //its material
                             "HDPE13");                  //its name

  HDPE_PV13 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(10*cm,10*cm,15*cm),            //at (0,0,0)
                             HDPE_LV13,                      //its logical volume
                            "HDPE13",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

//The HDPE_block14


  HDPE_Box14 = new G4Box("HDPE14",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV14 = new G4LogicalVolume(HDPE_Box14,                     //its shape
                              polyethylene,                      //its material
                             "HDPE14");                  //its name

  HDPE_PV14 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(10*cm,-10*cm,15*cm),            //at (0,0,0)
                             HDPE_LV14,                      //its logical volume
                            "HDPE14",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number



  //The HDPE_block15

  HDPE_Box15 = new G4Box("HDPE15",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV15 = new G4LogicalVolume(HDPE_Box15,                     //its shape
                              polyethylene,                      //its material
                             "HDPE15");                  //its name

  HDPE_PV15 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(-10*cm,10*cm,15*cm),            //at (0,0,0)
                             HDPE_LV15,                      //its logical volume
                            "HDPE15",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

//The HDPE_block16


  HDPE_Box16 = new G4Box("HDPE16",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV16 = new G4LogicalVolume(HDPE_Box16,                     //its shape
                              polyethylene,                      //its material
                             "HDPE16");                  //its name

  HDPE_PV16 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(-10*cm,0*cm,15*cm),            //at (0,0,0)
                             HDPE_LV16,                      //its logical volume
                            "HDPE16",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

   

//The HDPE_block17

  HDPE_Box17 = new G4Box("HDPE17",                             //its name
                   fblockSize/2,fblockSize/2,fblockSize/2);   //its dimensions

  HDPE_LV17 = new G4LogicalVolume(HDPE_Box17,                     //its shape
                              polyethylene,                      //its material
                             "HDPE17");                  //its name

  HDPE_PV17 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(10*cm,0*cm,15*cm),            //at (0,0,0)
                             HDPE_LV17,                      //its logical volume
                            "HDPE17",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number



  


//The lead1
  fLeadSize = 10*cm;


  Lead_Box = new G4Box("Lead",                             //its name
                   fLeadSize/2,fLeadSize/2, 5*cm/2);   //its dimensions

  Lead_LV = new G4LogicalVolume(Lead_Box,                     //its shape
                              leadMaterial,                      //its material
                             "Lead");                  //its name

  Lead_PV = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,0,12.5*cm),            //at (0,0,0)
                             Lead_LV,                      //its logical volume
                            "Lead",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


   G4VisAttributes* red = new G4VisAttributes(G4Colour::Red());

   red->SetVisibility(true);
   red->SetForceAuxEdgeVisible(true);

   Lead_LV->SetVisAttributes(red);
 

   //The Borated polythylene_block1 with pinhole

  

  BoratedSize = 30*cm;
  Borated_thickness = 3*cm;
  Borated_Box1 = new G4Box("Borated1",                             //its name
                   BoratedSize/2,BoratedSize/2,Borated_thickness/2);   //its dimensions



  Hole = new G4Tubs("BoxHole", 0.0*cm, 3*cm, 1.5*cm, 0*deg, 360*deg);

  Hole_LV = new G4LogicalVolume(Hole,                     //its shape
                              Vacc,                      //its material
                             "H1");                  //its name

   Borated_LV1 = new G4LogicalVolume(Borated_Box1,                     //its shape
                              b_polyethylene,                      //its material
                             "Borated1", 0,0,0);                  //its name



  Borated_PV1 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0*cm,0*cm,21.5*cm),            //at (0,0,0)
                             Borated_LV1,                      //its logical volume
                            "Borated1",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

  Hole_PV = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0*cm,0*cm,0*cm),            //at (0,0,0)
                             Hole_LV,                      //its logical volume
                            "H1",                    //its name
                            Borated_LV1,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number




   G4VisAttributes* green = new G4VisAttributes(G4Colour::Green());

   green->SetVisibility(true);
   green->SetForceAuxEdgeVisible(true);

   Borated_LV1->SetVisAttributes(green);

/*
   //The lead1
  


  Lead_Box1 = new G4Box("Lead1",                             //its name
                   BoratedSize/2,BoratedSize/2,5*cm/2);   //its dimensions

  Lead_LV1 = new G4LogicalVolume(Lead_Box1,                     //its shape
                              leadMaterial,                      //its material
                             "Lead1");                  //its name

  Lead_PV1 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,0,25.5*cm),            //at (0,0,0)
                             Lead_LV1,                      //its logical volume
                            "Lead",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


   G4VisAttributes* yellow= new G4VisAttributes(G4Colour::Yellow());

   yellow->SetVisibility(true);
   yellow->SetForceAuxEdgeVisible(true);

   Lead_LV1->SetVisAttributes(yellow);

*/

 //the converter
/*
 auto shield = new G4Box("shield", 50*cm, 50*cm, 0.1/2*mm);
 auto  lShield = new G4LogicalVolume(shield, polyethylene, "Shield");    
 auto  pShield = new G4PVPlacement(0,
                                               G4ThreeVector(0.*cm, 0.*cm, 50*cm),
                                               lShield,
                                               "Shield",
                                               fLBox,
                                               false,
                                               0,true); 
*/
 // the detector. 

  
  G4double ScThick_1 =  3.0*cm;

  auto sScore_1 = new G4Box("sScore_1",
                            50/2*cm,50/2*cm,ScThick_1/2);

  auto fLScore_1 = new G4LogicalVolume(sScore_1,
                                       Vacc,
                                      "fLScore_1");

  auto fPScore_r_1 = new G4PVPlacement(0,
                                    G4ThreeVector(0.*cm,0.*cm,50.155*cm),
                                    fLScore_1,
                                    "fPScore_r_1",
                                    fLBox,
                                    false,
                                    0,true);
  

  fScoringVolume_1 = fLScore_1;




  return fPBox;
}

//...ooooooooooooooooo..................................oooooooooooooooooooo......



void DetectorConstruction::ConstructSDandField()
{
 // sensitive detectors -----------------------------------------------------
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  SDman->SetVerboseLevel(0);

  //Define Multi-Detector and Register
  //--------------------------------------------------------------------------------------------
  G4MultiFunctionalDetector* det = new G4MultiFunctionalDetector("IonPro");
  SDman->AddNewDetector(det);
//  fLScore->SetSensitiveDetector(det);
}
