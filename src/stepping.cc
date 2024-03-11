#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
  if (step->GetTrack()->GetDefinition()->GetParticleName() == "proton" && step->GetPostStepPoint()->GetProcessDefinedStep() != nullptr ) {
     G4AnalysisManager *man = G4AnalysisManager::Instance();

     const DetectorConstruction *detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
     G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

     G4LogicalVolume *fScoringVolume_1 = detectorConstruction->GetScoringVolume();
     G4LogicalVolume *fScoringVolume_2 = detectorConstruction->GetScoringVolume_2();
     G4LogicalVolume *fScoringVolume_3 = detectorConstruction->GetScoringVolume_3();
     G4LogicalVolume *fScoringVolume_4 = detectorConstruction->GetScoringVolume_4();
     G4LogicalVolume *fScoringVolume_5 = detectorConstruction->GetScoringVolume_5();
     G4LogicalVolume *fScoringVolume_6 = detectorConstruction->GetScoringVolume_6();
     G4LogicalVolume *fScoringVolume_7 = detectorConstruction->GetScoringVolume_7();
     G4LogicalVolume *fScoringVolume_8 = detectorConstruction->GetScoringVolume_8();
     G4LogicalVolume *fScoringVolume_9 = detectorConstruction->GetScoringVolume_9();
     G4LogicalVolume *fScoringVolume_10 = detectorConstruction->GetScoringVolume_10();

     G4LogicalVolume *fScoringVolume2 = detectorConstruction->GetScoringVolume1();



     G4Track* track = step->GetTrack();
     G4double TrackID = step->GetTrack()->GetTrackID();
     //track->SetTrackStatus(fStopAndKill);
     G4int stepNumber = track->GetCurrentStepNumber();
     //G4cout << "the track material:" << TrackID << G4endl;


     G4double edep = step->GetTotalEnergyDeposit();
     G4double edep1 = step->GetTotalEnergyDeposit();
     G4double edep_2 = step->GetTotalEnergyDeposit();
     G4double edep_3 = step->GetTotalEnergyDeposit();
     G4double edep_4 = step->GetTotalEnergyDeposit();
     G4double edep_5 = step->GetTotalEnergyDeposit();
     G4double edep_6 = step->GetTotalEnergyDeposit();
     G4double edep_7 = step->GetTotalEnergyDeposit();
     G4double edep_8 = step->GetTotalEnergyDeposit();
     G4double edep_9 = step->GetTotalEnergyDeposit();
     G4double edep_10 = step->GetTotalEnergyDeposit();

     // If it's the first step in the volume, save the position.
     G4ThreeVector posPhoton;
     G4StepPoint *preStepPoint;
     G4StepPoint *postStepPoint ;
     G4double ekin_1 ;

     if (volume == fScoringVolume_1){
        fEventAction->AddEdep(edep);
        if (step->IsFirstStepInVolume() ){
           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_1  = postStepPoint->GetKineticEnergy()/keV;
           G4ThreeVector p0_1 = postStepPoint->GetMomentumDirection();
           G4double angle_1 = std::acos(p0_1.z());
           G4ThreeVector posPhoton1 = postStepPoint->GetPosition()/cm;

           man->FillH2(0, posPhoton1[0], posPhoton1[1]);
           man->FillH2(10, angle_1/deg, ekin_1);

           man->FillH1(0,  posPhoton1[2]);
           man->FillNtupleDColumn(1, 1, ekin_1);
           man->AddNtupleRow(1);

      /*

        if(preStepPoint->GetStepStatus() == fGeomBoundary && ekin_1 >= 1.5 && ekin_1 <= 1.6) {
          G4cout << "Step starts on geometry boundary" << G4endl;
          G4double elos = step->GetTotalEnergyDeposit();
          G4cout << "energy  at 1.5MeV =  "<< ekin_1 << G4endl;
          man->FillNtupleDColumn(12, 0, elos);
          man->AddNtupleRow(12);


        }*/
           //man->FillNtupleDColumn(12, 0, energy);
           //man->AddNtupleRow(12);
        }
     }
     if (volume == fScoringVolume_2){
        fEventAction->AddEdep_2(edep_2);
        if (step->IsFirstStepInVolume()){
           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_2  = postStepPoint->GetKineticEnergy()/keV;
           G4ThreeVector p0_2 = postStepPoint->GetMomentumDirection();
           G4double angle_2 = std::acos(p0_2.z());

           G4ThreeVector posPhoton2 = postStepPoint->GetPosition()/cm;

           man->FillH2(1, posPhoton2[0], posPhoton2[1]);
           man->FillH2(11, angle_2/deg, ekin_2);

           man->FillH1(1, posPhoton2[2]);
           man->FillNtupleDColumn(2, 1, ekin_2);
           man->AddNtupleRow(2);




        }

     }

     if (volume == fScoringVolume_3){
        fEventAction->AddEdep_3(edep_3);
        if (step->IsFirstStepInVolume()){

           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_3  = postStepPoint->GetKineticEnergy()/keV;
           G4ThreeVector p0_3 = postStepPoint->GetMomentumDirection();
           G4double angle_3 = std::acos(p0_3.z());

           G4ThreeVector posPhoton3 = postStepPoint->GetPosition()/cm;

           man->FillH2(2, posPhoton3[0], posPhoton3[1]);
           man->FillH2(12, angle_3/deg, ekin_3);

           man->FillH1(2, posPhoton3[2]);
           man->FillNtupleDColumn(3, 1, ekin_3);
           man->AddNtupleRow(3);



        }
     }
     if (volume == fScoringVolume_4){
        fEventAction->AddEdep_4(edep_4);
        if (step->IsFirstStepInVolume()){

           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_4  = postStepPoint->GetKineticEnergy()/keV;
           G4ThreeVector p0_4 = postStepPoint->GetMomentumDirection();
           G4double angle_4 = std::acos(p0_4.z());


           G4ThreeVector posPhoton4 = postStepPoint->GetPosition()/cm;

           man->FillH2(3, posPhoton4[0], posPhoton4[1]);
           man->FillH2(13, angle_4/deg, ekin_4);

           man->FillH1(3, posPhoton4[2]);
           man->FillNtupleDColumn(4, 1, ekin_4);
           man->AddNtupleRow(4);



        }
     }
     if (volume == fScoringVolume_5){
        fEventAction->AddEdep_5(edep_5);
        if (step->IsFirstStepInVolume()){

           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_5  = postStepPoint->GetKineticEnergy()/keV;
           G4ThreeVector p0_5 = postStepPoint->GetMomentumDirection();
           G4double angle_5 = std::acos(p0_5.z());

           G4ThreeVector posPhoton5 = postStepPoint->GetPosition()/cm;

           man->FillH2(4, posPhoton5[0], posPhoton5[1]);
           man->FillH2(14, angle_5/deg, ekin_5);

           man->FillH1(4,  posPhoton5[2]);
           man->FillNtupleDColumn(5, 1, ekin_5);
           man->AddNtupleRow(5);



        }

     }

     if (volume == fScoringVolume_6){
        fEventAction->AddEdep_6(edep_6);
        if (step->IsFirstStepInVolume()){

           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_6  = postStepPoint->GetKineticEnergy()/keV;
           G4ThreeVector p0_6 = postStepPoint->GetMomentumDirection();
           G4double angle_6 = std::acos(p0_6.z());

           G4ThreeVector posPhoton6 = postStepPoint->GetPosition()/cm;

           man->FillH2(5, posPhoton6[0], posPhoton6[1]);
           man->FillH2(15, angle_6/deg, ekin_6);

           man->FillH1(5, posPhoton6[2]);
           man->FillNtupleDColumn(6, 1, ekin_6);
           man->AddNtupleRow(6);


        }
     }

     if (volume == fScoringVolume_7){
        fEventAction->AddEdep_7(edep_7);
        if (step->IsFirstStepInVolume()){

           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_7  = postStepPoint->GetKineticEnergy()/keV;
           G4ThreeVector p0_7 = postStepPoint->GetMomentumDirection();
           G4double angle_7 = std::acos(p0_7.z());

           G4ThreeVector posPhoton7 = postStepPoint->GetPosition()/cm;


           man->FillH2(6, posPhoton7[0], posPhoton7[1]);
           man->FillH2(16, angle_7/deg, ekin_7);

           man->FillH1(6,  posPhoton7[2]);
           man->FillNtupleDColumn(7, 1, ekin_7);
           man->AddNtupleRow(7);


        }
     }

     if (volume == fScoringVolume_8){
        fEventAction->AddEdep_8(edep_8);
        if (step->IsFirstStepInVolume()){

           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_8  = postStepPoint->GetKineticEnergy()/keV;
           G4ThreeVector p0_8 = postStepPoint->GetMomentumDirection();
           G4double angle_8 = std::acos(p0_8.z());

           G4ThreeVector posPhoton8 = postStepPoint->GetPosition()/cm;

           man->FillH2(7, posPhoton8[0], posPhoton8[1]);
           man->FillH2(17, angle_8/deg, ekin_8);

           man->FillH1(7,  posPhoton8[2]);
           man->FillNtupleDColumn(8, 1, ekin_8);
           man->AddNtupleRow(8);



        }

     }

      if (volume == fScoringVolume_9){
        fEventAction->AddEdep_9(edep_9);
        if (step->IsFirstStepInVolume()){

           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_9  = postStepPoint->GetKineticEnergy()/keV;
           G4ThreeVector p0_9 = postStepPoint->GetMomentumDirection();
           G4double angle_9 = std::acos(p0_9.z());

           G4ThreeVector posPhoton9 = postStepPoint->GetPosition()/cm;


           man->FillH2(8, posPhoton9[0], posPhoton9[1]);
           man->FillH2(18, angle_9/deg, ekin_9);

           man->FillH1(8, posPhoton9[2]);
           man->FillNtupleDColumn(9, 1, ekin_9);
           man->AddNtupleRow(9);



        }

     }

     if (volume == fScoringVolume_10){
        fEventAction->AddEdep_10(edep_10);
        if (step->IsFirstStepInVolume()){

           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_10  = postStepPoint->GetKineticEnergy()/keV;
           G4ThreeVector p0_10 = postStepPoint->GetMomentumDirection();
           G4double angle_10 = std::acos(p0_10.z());

           G4ThreeVector posPhoton10 = postStepPoint->GetPosition()/cm;

           man->FillH2(9, posPhoton10[0], posPhoton10[1]);
           man->FillH2(19, angle_10/deg, ekin_10);

           man->FillH1(9, posPhoton10[2]);
           man->FillNtupleDColumn(10, 1, ekin_10);
           man->AddNtupleRow(10);



        }
     }

     if (volume == fScoringVolume2){
        fEventAction->AddEdep1(edep1);
     }

  }
  //else
  //{
    //step->GetTrack()->SetTrackStatus(fStopAndKill);
  //}

}



