#include "run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
MyRunAction::MyRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->SetNtupleMerging(true);
    man->SetVerboseLevel(1);

    // Create 100 ntuples and histograms for each detector
    for (int i = 0; i < 100; ++i) {
        // Create a unique ntuple for each detector
        std::stringstream ntupleName;
        ntupleName << "Energy_Spectrum_" << i;
        man->CreateNtuple(ntupleName.str(), "Energy_Spectrum of detected protons");
        man->CreateNtupleDColumn("Energy");  // Single energy column
        man->FinishNtuple(i);  // Use index i as the ID for each ntuple

        // Create a unique 2D histogram for each detector
        std::stringstream histName;
        histName << "xy_" << i;
        man->CreateH2(histName.str(), "Spatial distribution of detected protons", 100, -40, 40, 100, -40, 40);
    }
}

MyRunAction::~MyRunAction()
{
}

void MyRunAction::BeginOfRunAction(const G4Run* run )
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    man->OpenFile("output"+strRunID.str()+".root");
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}

