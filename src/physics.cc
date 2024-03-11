#include "physics.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

// particles
#include "NeutronHPphysics.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4Cerenkov.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList()
:G4VModularPhysicsList()
{
  G4int verb = 1;
  SetVerboseLevel(verb);

  //add new units
  //
  new G4UnitDefinition( "millielectronVolt", "meV", "Energy", 1.e-3*eV);   
  new G4UnitDefinition( "mm2/g",  "mm2/g", "Surface/Mass", mm2/g);
  new G4UnitDefinition( "um2/mg", "um2/mg","Surface/Mass", um*um/mg);  
  // mandatory for G4NuclideTable
  //
  const G4double meanLife = 1*nanosecond, halfLife = meanLife*std::log(2);
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(halfLife);  
  // Neutron Physics
  RegisterPhysics( new NeutronHPphysics("neutronHP"));
  // Optical Physics
//   RegisterPhysics(new G4EmStandardPhysics());

   RegisterPhysics(new G4OpticalPhysics());

  // Hadron Elastic scattering
  //RegisterPhysics( new HadronElasticPhysicsHP(verb) );

  //RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP(verb));

  // Ion Elastic scattering
  //
 // RegisterPhysics( new G4IonElasticPhysics(verb));
  
  // Ion Inelastic physics
  //RegisterPhysics( new G4IonPhysicsXS(verb));

   // EM physics
  //RegisterPhysics(new ElectromagneticPhysics());
  RegisterPhysics(new G4EmStandardPhysics());
  
  // Decay
//  RegisterPhysics(new G4DecayPhysics());

  // Radioactive decay
  //RegisterPhysics(new RadioactiveDecayPhysics());
  ////RegisterPhysics(new G4RadioactiveDecayPhysics());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void PhysicsList::ConstructParticle()
{
  G4BosonConstructor  pBosonConstructor;
  pBosonConstructor.ConstructParticle();

  G4LeptonConstructor pLeptonConstructor;
  pLeptonConstructor.ConstructParticle();

  G4MesonConstructor pMesonConstructor;
  pMesonConstructor.ConstructParticle();

  G4BaryonConstructor pBaryonConstructor;
  pBaryonConstructor.ConstructParticle();

  G4IonConstructor pIonConstructor;
  pIonConstructor.ConstructParticle();

  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCuts()
{
  SetCutValue(0*mm, "proton");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
