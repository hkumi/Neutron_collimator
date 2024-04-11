#include "run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
MyRunAction::MyRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->SetNtupleMerging(true);
    man->SetVerboseLevel( 1 );
    

    
 
    man->CreateNtuple("thermal","thermal");
    man->CreateNtupleDColumn("Energy");
    man->FinishNtuple(0);

    man->CreateNtuple("Epithermal","Epithermal");
    man->CreateNtupleDColumn("Energy");
    man->FinishNtuple(1);

    man->CreateNtuple("fast","fast");
    man->CreateNtupleDColumn("Energy");
    man->FinishNtuple(2);



    man->CreateNtuple("Zthermal","Zthermal");
    man->CreateNtupleDColumn("Z_axis");
    man->FinishNtuple(3);
   
    man->CreateNtuple("ZEpi","ZEpi");
    man->CreateNtupleDColumn("Z_axis");
    man->FinishNtuple(4);

    man->CreateNtuple("ZFast","ZFast");
    man->CreateNtupleDColumn("Z_axis");
    man->FinishNtuple(5);



    man->CreateH2("xy1 ","xy1", 100, -10, 10, 100, -10, 10.0);
    man->CreateH2("xy2 ","xy2", 100, -10, 10, 100, -10, 10.0);
    man->CreateH2("xy3 ","xy3", 100, -10, 10, 100, -10, 10.0);

    man->CreateH2("a1 ","angle vs energy_1", 100, 0, 60, 100, 0, 0.025);
    man->CreateH2("a2 ","angle vs energy_2", 100, 0, 60, 100, 0.025, 50000.0);
    man->CreateH2("a3 ","angle vs energy_3", 100, 0, 60, 100, 50000, 2000000.0);

    man->CreateH1("thermalEnergy","thermalEnergy", 100,0 , 0.025);
    man->CreateH1("EpithermalEnergy ","EpithermalEnergy", 100,0.025 , 50000);
    man->CreateH1("FastEnergy ","FastEnergy", 100,50000 , 2000000);

   
    
    




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
