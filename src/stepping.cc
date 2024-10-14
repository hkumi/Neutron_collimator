#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
    fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
  
    // Only proceed if the particle is a proton
    if (step->GetTrack()->GetDefinition()->GetParticleName() == "proton") {
        G4AnalysisManager *man = G4AnalysisManager::Instance();

        // Get detector construction and logical volume
        const DetectorConstruction *detectorConstruction = static_cast<const DetectorConstruction*>
            (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        
        G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

        // Loop over all scoring volumes
        for (int i = 0; i < 100; ++i) {
            G4LogicalVolume *fScoringVolume_i = detectorConstruction->GetScoringVolume(i);

            if (volume == fScoringVolume_i) {
                // If the proton is in the current scoring volume, record the data
                G4double edep = step->GetTotalEnergyDeposit();

                // If it's the first step in the volume, save the position and energy
                if (step->IsFirstStepInVolume()) {
                    G4StepPoint *postStepPoint = step->GetPostStepPoint();
                    G4double ekin_1 = postStepPoint->GetKineticEnergy() / MeV;
                    G4ThreeVector posPhoton1 = postStepPoint->GetPosition() / cm;

                    // Use the index i to select the corresponding histogram
                    man->FillH2(i, posPhoton1[0], posPhoton1[1]); // Use `i` as the histogram ID for each detector

                    // Store the energy in the corresponding ntuple row for this detector
                    man->FillNtupleDColumn(i, 0, ekin_1);
                    man->AddNtupleRow(i); // Ensure each detector has its own ntuple row
                }

                // Add energy deposit to event action for this specific scoring volume
                fEventAction->AddEdep(i, edep);
                break; // Stop looping once we've found the correct scoring volume
            }
        }
    }
}

