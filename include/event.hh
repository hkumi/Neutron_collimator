#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "run.hh"
#include "G4UserSteppingAction.hh"
#include "construction.hh"

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction(MyRunAction*);
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    //void AddEdep(G4double edep) { fEdep += edep; }
    void AddEdep(int index, G4double edep) {
        fEdep[index] += edep;
    }


    void SetPosition(G4ThreeVector p) { fPosition = p; }
    
private:
    //G4double fEdep;
    G4ThreeVector fPosition;
    G4double fEdep1;
    std::vector<G4double> fEdep; 

};

#endif

