#include "event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
    fEdep = 0.;
    fEdep1 = 0.;
    fEdep_2 = 0.;
    fEdep_3 = 0.;
    fEdep_4 = 0.;
    fEdep_5 = 0.;
    fEdep_6 = 0.;
    fEdep_7 = 0.;
    fEdep_8 = 0.;
    fEdep_9 = 0.;
    fEdep_10 = 0.;

    thickness_count = 0.;


}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
    fEdep1 = 0.;
    fEdep_2 = 0.;
    fEdep_3 = 0.;
    fEdep_4 = 0.;
    fEdep_5 = 0.;
    fEdep_6 = 0.;
    fEdep_7 = 0.;
    fEdep_8 = 0.;
    fEdep_9 = 0.;
    fEdep_10 = 0.;

    thickness_count = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
       G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
       G4int numberOfEvents = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
       G4int count = 0;

       G4AnalysisManager *man = G4AnalysisManager::Instance();

       if (fEdep > 0.0) {
         // G4cout << "Number of events: " << evt << G4endl;
          //G4cout << "Energy deposition: " << fEdep*MeV << G4endl;
          //man->FillNtupleDColumn(1, 0, fEdep);
          //man->AddNtupleRow(1);
          theCollID.push_back(evt);
          G4int Ncol = theCollID.size();
          //G4cout << "total number events OPPAC_1:"<< Ncol << G4endl;


       }

       if (fEdep_2 > 0.0){
          //man->FillNtupleDColumn(2,0,fEdep_2);
          //man->AddNtupleRow(2);

       }

       if (fEdep_3 > 0.0){
          //man->FillNtupleDColumn(3,0,fEdep_3);
          //man->AddNtupleRow(3);

       }

       if (fEdep_4 > 0.0){
          //man->FillNtupleDColumn(4,0,fEdep_4);
          //man->AddNtupleRow(4);

       }

       if (fEdep_5 > 0.0){
          //man->FillNtupleDColumn(5,0,fEdep_5);
          //man->AddNtupleRow(5);


       }

       if (fEdep_6 > 0.0){
          //man->FillNtupleDColumn(6,0,fEdep_6);
          //man->AddNtupleRow(6);

       }

       if (fEdep_7 > 0.0){
          //man->FillNtupleDColumn(7,0,fEdep_7);
          //man->AddNtupleRow(7);


       }

       if (fEdep_8 > 0.0){
          //man->FillNtupleDColumn(8,0,fEdep_8);
          //man->AddNtupleRow(8);


       }

       if (fEdep_9 > 0.0){
          //man->FillNtupleDColumn(9,0,fEdep_9);
          //man->AddNtupleRow(9);


       }

       if (fEdep_10 > 0.0){
          //man->FillNtupleDColumn(10,0,fEdep_10);
          //man->AddNtupleRow(10);

       }

       if (fEdep1 > 0.0){
          man->FillNtupleDColumn(11, 0, fEdep1);
          man->AddNtupleRow(11);
       }

}
