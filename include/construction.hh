#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

//#include "detector.hh"
class G4LogicalVolume;
class G4Material;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

    DetectorConstruction();
   ~DetectorConstruction();

    G4LogicalVolume *GetScoringVolume() const {return fScoringVolume_1;}
    G4LogicalVolume *GetScoringVolume_2() const {return fScoringVolume_2;}
    G4LogicalVolume *GetScoringVolume_3() const {return fScoringVolume_3;}
    G4LogicalVolume *GetScoringVolume_4() const {return fScoringVolume_4;}
    G4LogicalVolume *GetScoringVolume_5() const {return fScoringVolume_5;}
    G4LogicalVolume *GetScoringVolume_6() const {return fScoringVolume_6;}
    G4LogicalVolume *GetScoringVolume_7() const {return fScoringVolume_7;}
    G4LogicalVolume *GetScoringVolume_8() const {return fScoringVolume_8;}
    G4LogicalVolume *GetScoringVolume_9() const {return fScoringVolume_9;}
    G4LogicalVolume *GetScoringVolume_10() const {return fScoringVolume_10;}

    G4LogicalVolume *GetScoringVolume1() const {return fScoringVolume2;}

    virtual G4VPhysicalVolume* Construct();
    void ConstructOPPAC_1(G4double Pos_PPAC_1);
    void ConstructOPPAC_2(G4double Pos_PPAC_2);
    void ConstructOPPAC_3(G4double Pos_PPAC_3);
    void ConstructOPPAC_4(G4double Pos_PPAC_4);
    void ConstructOPPAC_5(G4double Pos_PPAC_5);
    void ConstructOPPAC_6(G4double Pos_PPAC_6);
    void ConstructOPPAC_7(G4double Pos_PPAC_7);
    void ConstructOPPAC_8(G4double Pos_PPAC_8);
    void ConstructOPPAC_9(G4double Pos_PPAC_9);
    void ConstructOPPAC_10(G4double Pos_PPAC_10);
    void ConstructSilicon_detector(G4double Pos_Silicon);
    void CreateAndPlaceShield(G4double thickness, G4double size, G4double position, G4LogicalVolume* motherVolume) ;
    void Sphereball( G4double position);

private:
     G4Box  *HDPE_Box1,*Lead_Box,*HDPE_Box2, *sBox,*HDPE_Box3,*HDPE_Box4,*HDPE_Box5,*HDPE_Box6,*HDPE_Box7,*HDPE_Box8,*HDPE_Box9,*HDPE_Box10;
     G4Box  *HDPE_Box11,*HDPE_Box12,*HDPE_Box13,*HDPE_Box14,*HDPE_Box15,*HDPE_Box16,*HDPE_Box17;
     G4VPhysicalVolume *Lead_PV,*HDPE_PV1,*HDPE_PV2, *HDPE_PV3,*HDPE_PV4,*HDPE_PV5,*HDPE_PV6,*HDPE_PV7,*HDPE_PV8,*HDPE_PV9,*HDPE_PV10;
     G4VPhysicalVolume *HDPE_PV11,*HDPE_PV12,*HDPE_PV13,*HDPE_PV14,*HDPE_PV15,*HDPE_PV16,*HDPE_PV17;
     G4LogicalVolume   *fLBox,*Lead_LV,*HDPE_LV1,*HDPE_LV2,*HDPE_LV3,*HDPE_LV4,*HDPE_LV5,*HDPE_LV6,*HDPE_LV7,*HDPE_LV8,*HDPE_LV9,*HDPE_LV10;
     G4LogicalVolume   *HDPE_LV11,*HDPE_LV12,*HDPE_LV13,*HDPE_LV14,*HDPE_LV15,*HDPE_LV16,*HDPE_LV17;
     G4LogicalVolume   *fScoringVolume_1,*fScoringVolume_2,*fScoringVolume_3,*fScoringVolume_4;
     G4LogicalVolume   *fScoringVolume2,*fScoringVolume_5, *fScoringVolume_6;
     G4LogicalVolume   *fScoringVolume_7,*fScoringVolume_8,*fScoringVolume_9,*fScoringVolume_10;
     G4double       mat_thickness;

     G4VPhysicalVolume *fPBox;

     G4double           fBoxSize, fblockSize,fLeadSize;
     G4Material*        fMaterial;
     G4Material *Air, *b_polyethylene,  *polyethylene, *NaI, *CF4 ;
     G4Material  * leadMaterial;
     G4Element  *Na, *I, *C,*N,*O,*F;
     G4Material *Vacc;

     void DefineMaterials();
     virtual void ConstructSDandField();
     G4GenericMessenger *fMessenger;
     G4bool isPPAC, isScintillator;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif





