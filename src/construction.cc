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

  //Graphite 
  mat_graphite = nist->FindOrBuildMaterial("G4_GRAPHITE");
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
  G4double pressure = 0.046*atmosphere; //35Torr
  G4double temperature = 293.15*kelvin; // 
  CF4 = new G4Material("CF4", 0.1223*mg/cm3,2,kStateGas,temperature,pressure);
  CF4->AddElement(C,1);
  CF4->AddElement(F,4);


   // ------------------------------------ Polypropilene ------------------------------------

  nist->FindOrBuildMaterial("G4_POLYPROPYLENE");
  PP = G4Material::GetMaterial("G4_POLYPROPYLENE");

  
//----------------------------------- Aluminium ------------------------------------
 
   G4double density;
   Aluminium = new G4Material("Al", z = 13., a = 26.98 * g / mole,
                        density = 2.7 * g / cm3);
 


//....................End of scintillator material........................................




}

G4VPhysicalVolume *DetectorConstruction::Construct()
{

   

  // The world
  fBoxSize = 5*m;


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
                   10*cm/2,10*cm/2,1*cm/2);   //its dimensions

  HDPE_LV1 = new G4LogicalVolume(HDPE_Box1,                     //its shape
                              polyethylene,                      //its material
                             "HDPE1");                  //its name

  HDPE_PV1 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,0,0.5*cm),            //at (0,0,0)
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

    //The HDPE_block18


  HDPE_Box18 = new G4Box("HDPE18",                             //its name
                   fblockSize/2,fblockSize/2,10*cm/2);   //its dimensions

  HDPE_LV18 = new G4LogicalVolume(HDPE_Box18,                     //its shape
                              polyethylene,                      //its material
                             "HDPE18");                  //its name

  HDPE_PV18 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(10*cm,-10*cm,25*cm),            //at (0,0,0)
                             HDPE_LV18,                      //its logical volume
                            "HDPE18",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

    //The HDPE_block19


  HDPE_Box19 = new G4Box("HDPE19",                             //its name
                   fblockSize/2,fblockSize/2,10*cm/2);   //its dimensions

  HDPE_LV19 = new G4LogicalVolume(HDPE_Box19,                     //its shape
                              polyethylene,                      //its material
                             "HDPE19");                  //its name

  HDPE_PV19 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(-10*cm,-10*cm,25*cm),            //at (0,0,0)
                             HDPE_LV19,                      //its logical volume
                            "HDPE19",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);

     //The HDPE_block20


  HDPE_Box20 = new G4Box("HDPE20",                             //its name
                   fblockSize/2,fblockSize/2,10*cm/2);   //its dimensions

  HDPE_LV20 = new G4LogicalVolume(HDPE_Box20,                     //its shape
                              polyethylene,                      //its material
                             "HDPE20");                  //its name

  HDPE_PV20 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(10*cm,10*cm,25*cm),            //at (0,0,0)
                             HDPE_LV20,                      //its logical volume
                            "HDPE20",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

 //The HDPE_block21

  HDPE_Box21 = new G4Box("HDPE21",                             //its name
                   fblockSize/2,fblockSize/2,10*cm/2);   //its dimensions

  HDPE_LV21 = new G4LogicalVolume(HDPE_Box21,                     //its shape
                              polyethylene,                      //its material
                             "HDPE21");                  //its name

  HDPE_PV21 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(-10*cm,10*cm,25*cm),            //at (0,0,0)
                             HDPE_LV21,                      //its logical volume
                            "HDPE21",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

//The HDPE_block22


  HDPE_Box22 = new G4Box("HDPE22",                             //its name
                   fblockSize/2,fblockSize/2,10*cm/2);   //its dimensions

  HDPE_LV22 = new G4LogicalVolume(HDPE_Box22,                     //its shape
                              polyethylene,                      //its material
                             "HDPE22");                  //its name

  HDPE_PV22 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(-10*cm,0*cm,25*cm),            //at (0,0,0)
                             HDPE_LV22,                      //its logical volume
                            "HDPE22",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

//The HDPE_block23

  HDPE_Box23 = new G4Box("HDPE23",                             //its name
                   fblockSize/2,fblockSize/2,10*cm/2);   //its dimensions

  HDPE_LV23 = new G4LogicalVolume(HDPE_Box23,                     //its shape
                              polyethylene,                      //its material
                             "HDPE23");                  //its name

  HDPE_PV23 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(10*cm,0*cm,25*cm),            //at (0,0,0)
                             HDPE_LV23,                      //its logical volume
                            "HDPE23",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


 //The HDPE_block24
  

  HDPE_Box24 = new G4Box("HDPE24",                             //its name
                   fblockSize/2,fblockSize/2,10*cm/2);   //its dimensions

  HDPE_LV24 = new G4LogicalVolume(HDPE_Box24,                     //its shape
                              polyethylene,                      //its material
                             "HDPE24");                  //its name

  HDPE_PV24 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,10*cm,25*cm),            //at (0,0,0)
                             HDPE_LV24,                      //its logical volume
                            "HDPE24",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

//The HDPE_block25


  HDPE_Box25 = new G4Box("HDPE25",                             //its name
                   fblockSize/2,fblockSize/2,10*cm/2);   //its dimensions

  HDPE_LV25 = new G4LogicalVolume(HDPE_Box25,                     //its shape
                              polyethylene,                      //its material
                             "HDPE25");                  //its name

  HDPE_PV25 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,-10*cm,25*cm),            //at (0,0,0)
                             HDPE_LV25,                      //its logical volume
                            "HDPE25",                    //its name
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
                            G4ThreeVector(0,0,3.5*cm),            //at (0,0,0)
                             Lead_LV,                      //its logical volume
                            "Lead",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


   G4VisAttributes* red = new G4VisAttributes(G4Colour::Red());

   red->SetVisibility(true);
   red->SetForceAuxEdgeVisible(true);

   Lead_LV->SetVisAttributes(red);

//................................................................................
   // Graphite block1 
/*
  fGraphiteSize = 10*cm;


  Graphite_Box = new G4Box("Grap",                             //its name
                   fGraphiteSize/2,fGraphiteSize/2, 5*cm/2);   //its dimensions

  Graphite_LV = new G4LogicalVolume(Graphite_Box,                     //its shape
                              mat_graphite,                      //its material
                             "Grap");                  //its name

  Graphite_PV = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,0,17.5*cm),            //at (0,0,0)
                             Graphite_LV,                      //its logical volume
                            "Grap",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number

  Hole3 = new G4Tubs("BoxHole3", 0.0*cm, 3*cm, 2.5*cm, 0*deg, 360*deg);

  Hole_LV3 = new G4LogicalVolume(Hole3,                     //its shape
                                 Vacc,                      //its material
                                 "H3");    
 

   // Graphite block2 


  Graphite_Box2 = new G4Box("Grap2",                             //its name
                   30*cm/2,3*cm/2, 20*cm/2);   //its dimensions

  Graphite_LV2 = new G4LogicalVolume(Graphite_Box2,                     //its shape
                              mat_graphite,                      //its material
                             "Grap2");                  //its name

  Graphite_PV2 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,6.5*cm,10*cm),            //at (0,0,0)
                             Graphite_LV2,                      //its logical volume
                            "Grap2",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number
  // // Graphite block3


  Graphite_Box3 = new G4Box("Grap3",                             //its name
                   30*cm/2,3*cm/2, 20*cm/2);   //its dimensions

  Graphite_LV3 = new G4LogicalVolume(Graphite_Box3,                     //its shape
                              mat_graphite,                      //its material
                             "Grap3");                  //its name

  Graphite_PV3 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0,-6.5*cm,10*cm),            //at (0,0,0)
                             Graphite_LV3,                      //its logical volume
                            "Grap3",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


  */
//.........................................................................................................................................
  //The Borated polythylene_block1 with pinhole

  BoratedSize = 30*cm;
  Borated_thickness = 3*cm;
  Borated_Box1 = new G4Box("Borated1",                             //its name
                   BoratedSize/2,  BoratedSize/2,Borated_thickness/2);   //its dimensions



  Hole = new G4Tubs("BoxHole", 0.0*cm, 0.75*cm, 1.5*cm, 0*deg, 360*deg);  // the diameter of the exit(pinhole) is 3cm. In G4 we use halfsize of the radius. 

  Hole_LV = new G4LogicalVolume(Hole,                     //its shape
                              Vacc,                      //its material
                             "H1");                  //its name

   Borated_LV1 = new G4LogicalVolume(Borated_Box1,                     //its shape
                              b_polyethylene,                      //its material
                             "Borated1", 0,0,0);                  //its name



  Borated_PV1 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0*cm,0*cm,31.5*cm),            //at (0,0,0)
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

//..................................................
/*
  Hole_PV3 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0*cm,0*cm,0*cm),            //at (0,0,0)
                            Hole_LV3,                      //its logical volume
                            "H3",                    //its name
                            Graphite_LV,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number



*/
//.......................................................................

   G4VisAttributes* green = new G4VisAttributes(G4Colour::Green());

   green->SetVisibility(true);
   green->SetForceAuxEdgeVisible(true);

   Borated_LV1->SetVisAttributes(green);


   //The lead2
  

  LeadSize = 3*cm;
  Lead_Box2 = new G4Box("Lead2",                             //its name
                   30*cm/2,LeadSize/2,33*cm/2);   //its dimensions

  Lead_LV2 = new G4LogicalVolume(Lead_Box2,                     //its shape
                              leadMaterial,                      //its material
                             "Lead2");                  //its name

  Lead_PV2 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0*cm,16.5*cm,16.5*cm),            //at (0,0,0)
                             Lead_LV2,                      //its logical volume
                            "Lead2",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


  G4VisAttributes* yellow= new G4VisAttributes(G4Colour::Yellow());

  yellow->SetVisibility(true);
  yellow->SetForceAuxEdgeVisible(true);

  Lead_LV2->SetVisAttributes(red);



     //The lead3
 
  Lead_Box3 = new G4Box("Lead3",                             //its name
                   3*cm/2,30*cm/2, 33*cm/2);   //its dimensions

  Lead_LV3 = new G4LogicalVolume(Lead_Box3,                     //its shape
                              leadMaterial,                      //its material
                             "Lead3");                  //its name

  Lead_PV3 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(16.5*cm,0*cm,16.5*cm),            //at (0,0,0)
                             Lead_LV3,                      //its logical volume
                            "Lead3",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


   
  Lead_LV3->SetVisAttributes(red);

  //The lead4

  Lead_Box4 = new G4Box("Lead4",                             //its name
                   3*cm/2,30*cm/2, 33*cm/2);   //its dimensions

  Lead_LV4 = new G4LogicalVolume(Lead_Box4,                     //its shape
                              leadMaterial,                      //its material
                             "Lead4");                  //its name

  Lead_PV4 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(-16.5*cm,0*cm,16.5*cm),            //at (0,0,0)
                             Lead_LV4,                      //its logical volume
                            "Lead4",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number


   
  Lead_LV4->SetVisAttributes(red);

  //The lead5

  Lead_Box5 = new G4Box("Lead5",                             //its name
                   30*cm/2,30*cm/2, 3*cm/2);   //its dimensions

  Lead_LV5 = new G4LogicalVolume(Lead_Box5,                     //its shape
                              leadMaterial,                      //its material
                             "Lead5");                  //its name

  Lead_PV5 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0*cm,0*cm,34.5*cm),            //at (0,0,0)
                             Lead_LV5,                      //its logical volume
                            "Lead5",                    //its name
                            fLBox,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number
  Hole_PV2 = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(0*cm,0*cm,0*cm),            //at (0,0,0)
                             Hole_LV,                      //its logical volume
                            "H2",                    //its name
                             Lead_LV5,                          //its mother  volume
                            false,                      //no boolean operation
                            0,true);                         //copy number




   
  Lead_LV5->SetVisAttributes(red);



   // Define dimensions and materials
G4double shieldThickness = 0.001*cm; // 10 microns
G4double ppThickness = 0.0001*cm;    // 1 micrometer
G4double coatingThickness = 0.00001*cm; // 0.1 micrometer
G4double gasThickness = 0.3*cm; // 3mm for CF4 gas
G4double size = 70*cm;

// Loop for 100 iterations
for (int i = 0; i < 100; ++i) {
    // Calculate z position for this iteration
    G4double zStart = 112.0*cm + i*0.5*cm ; // Adjust z position for each iteration

    // Create and place shield (polyethylene)
    auto shield = new G4Box("shield", size/2, size/2, shieldThickness/2);
    auto lShield = new G4LogicalVolume(shield, polyethylene, "Shield");

    auto pShield = new G4PVPlacement(0,
                                      G4ThreeVector(0.*cm, 0.*cm, zStart),
                                      lShield,
                                      "Shield",
                                      fLBox,
                                      false,
                                      0, true);

    // Create and place polypropylene foil
    G4Box* foilSolid = new G4Box("foilSolid", size/2, size/2, ppThickness/2);
    G4LogicalVolume* PPCoating = new G4LogicalVolume(foilSolid, PP, "PPCoating");

    G4double zFoil = zStart + shieldThickness + ppThickness/2; // Place foil right after shield
    G4PVPlacement* foilCoating = new G4PVPlacement(0,
                                                   G4ThreeVector(0.*cm, 0.*cm, zFoil),
                                                   PPCoating,
                                                   "PPCoating",
                                                   fLBox,
                                                   false,
                                                   0, true);

    PPCoating->SetVisAttributes(yellow);

    // Create and place aluminum coating
    G4Box* coatingSolid = new G4Box("coatingSolid", size/2, size/2, coatingThickness/2);
    G4LogicalVolume* lCoating = new G4LogicalVolume(coatingSolid, Aluminium, "AluminiumCoating");

    G4double zCoating = zFoil + ppThickness/2 + coatingThickness/2; // Place aluminum coating after foil
    auto pCoating = new G4PVPlacement(0,
                                      G4ThreeVector(0.*cm, 0.*cm, zCoating),
                                      lCoating,
                                      "AluminiumCoating",
                                      fLBox,
                                      false,
                                      0, true);

    lCoating->SetVisAttributes(red);

    // Create and place CF4 gas
    G4Box* sScore = new G4Box("sScore", size/2, size/2, gasThickness/2);
    G4LogicalVolume* fLScore = new G4LogicalVolume(sScore, CF4, "fLScore");

    G4double zGas = zCoating + coatingThickness/2 + gasThickness/2; // Place CF4 gas after coating
    auto fPScore = new G4PVPlacement(0,
                                     G4ThreeVector(0.*cm, 0.*cm, zGas),
                                     fLScore,
                                     "fPScore",
                                     fLBox,
                                     false,
                                     0, true);

    //fScoringVolume_1 = fLScore;
    // After creating each scoring volume, push it to the vector
    fScoringVolumes.push_back(fLScore);


    // Place a second aluminum coating
    G4Box* coatingSolid2 = new G4Box("coatingSolid2", size/2, size/2, coatingThickness/2);
    G4LogicalVolume* lCoating2 = new G4LogicalVolume(coatingSolid2, Aluminium, "AluminiumCoating2");

    G4double zCoating2 = zGas + gasThickness/2 + coatingThickness/2; // Place second aluminum coating
    auto pCoating2 = new G4PVPlacement(0,
                                       G4ThreeVector(0.*cm, 0.*cm, zCoating2),
                                       lCoating2,
                                       "AluminiumCoating2",
                                       fLBox,
                                       false,
                                       0, true);

    lCoating2->SetVisAttributes(red);

    // Place a second polypropylene foil
    G4Box* foilSolid2 = new G4Box("foilSolid2", size/2, size/2, ppThickness/2);
    G4LogicalVolume* PPCoating2 = new G4LogicalVolume(foilSolid2, PP, "PPCoating2");

    G4double zFoil2 = zCoating2 + coatingThickness/2 + ppThickness/2; // Place second polypropylene foil
    G4PVPlacement* foilCoating2 = new G4PVPlacement(0,
                                                    G4ThreeVector(0.*cm, 0.*cm, zFoil2),
                                                    PPCoating2,
                                                    "PPCoating2",
                                                    fLBox,
                                                    false,
                                                    0, true);

    PPCoating2->SetVisAttributes(yellow);
}



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
