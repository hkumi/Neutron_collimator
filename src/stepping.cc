#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
  if (step->GetTrack()->GetDefinition()->GetParticleName() == "neutron" ) {
     G4AnalysisManager *man = G4AnalysisManager::Instance();

     const DetectorConstruction *detectorConstruction = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
     G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

     G4LogicalVolume *fScoringVolume_1 = detectorConstruction->GetScoringVolume();
     

     
     G4Track* track = step->GetTrack();
     G4double TrackID = step->GetTrack()->GetTrackID();
     //track->SetTrackStatus(fStopAndKill);
     G4int stepNumber = track->GetCurrentStepNumber();
     //G4cout << "the track material:" << TrackID << G4endl; 


     G4double edep = step->GetTotalEnergyDeposit();
     G4double edep1 = step->GetTotalEnergyDeposit();
     

     // If it's the first step in the volume, save the position.
     G4ThreeVector posPhoton; 
     G4StepPoint *preStepPoint; 
     G4StepPoint *postStepPoint ;   
     G4double ekin_1 ; 

     if (volume != fScoringVolume_1) return;
        fEventAction->AddEdep(edep);
        if (step->IsFirstStepInVolume() ){
           preStepPoint = step->GetPreStepPoint();
           postStepPoint = step->GetPostStepPoint();
           G4double ekin_1  = postStepPoint->GetKineticEnergy()/eV;
           if (ekin_1 < 0.025) { 
              G4ThreeVector p0_1 = postStepPoint->GetMomentumDirection();
              G4double angle_1 = std::acos(p0_1.z());
              G4ThreeVector posPhoton1 = postStepPoint->GetPosition()/cm;

              man->FillH2(0, posPhoton1[0], posPhoton1[1]);
              man->FillH2(3, angle_1/deg, ekin_1);

              man->FillH1(0, ekin_1);
          
              man->FillNtupleDColumn(0, 0, ekin_1);
              man->AddNtupleRow(0);

              man->FillNtupleDColumn(3, 0, posPhoton1[2]);
              man->AddNtupleRow(3);
           }
           else if (ekin_1 >= 0.025 && ekin_1 <= 50000.0){
                   G4ThreeVector p0_1 = postStepPoint->GetMomentumDirection();
                   G4double angle_1 = std::acos(p0_1.z());
                   G4ThreeVector posPhoton1 = postStepPoint->GetPosition()/cm;

                   man->FillH2(1, posPhoton1[0], posPhoton1[1]);
                   man->FillH2(4, angle_1/deg, ekin_1);

                   man->FillH1(1, ekin_1);

                   man->FillNtupleDColumn(1, 0, ekin_1);
                   man->AddNtupleRow(1);

                   man->FillNtupleDColumn(4, 0, posPhoton1[2]);
                   man->AddNtupleRow(4);
 
           }
           else{
              G4ThreeVector p0_1 = postStepPoint->GetMomentumDirection();
              G4double angle_1 = std::acos(p0_1.z());
              G4ThreeVector posPhoton1 = postStepPoint->GetPosition()/cm;

              man->FillH2(2, posPhoton1[0], posPhoton1[1]);
              man->FillH2(5, angle_1/deg, ekin_1);

              man->FillH1(2, ekin_1);

              man->FillNtupleDColumn(2, 0, ekin_1);
              man->AddNtupleRow(2);

              man->FillNtupleDColumn(5, 0, posPhoton1[2]);
              man->AddNtupleRow(5);
              }
        }
     
     
     
     

    

  }
  //else
  //{
    //step->GetTrack()->SetTrackStatus(fStopAndKill);
  //}

}
