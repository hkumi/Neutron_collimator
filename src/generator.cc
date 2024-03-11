#include "generator.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    //fParticleGun = new G4ParticleGun(1);
    fParticleGun = new G4GeneralParticleSource();
/*    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "neutron";
    G4ParticleDefinition *particle = particleTable->FindParticle("neutron");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(2.0*MeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,-19.*mm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  */  

}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
/*
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();

      G4String particleName = "neutron";
      G4ParticleDefinition *particle = particleTable->FindParticle("");
 
      G4ThreeVector pos(0.,0.,0.);
      G4ThreeVector mom(0.,0.,1.);
      fParticleGun->SetParticlePosition(pos);
      fParticleGun->SetParticleMomentumDirection(mom);
      fParticleGun->SetParticleMomentum(2.0*MeV);
      fParticleGun->SetParticleDefinition(particle);

  */  //G4ThreeVector gunDirection = G4ThreeVector(0, 0, 1);
    //gunDirection += 0.2 * G4ThreeVector(G4UniformRand() - 0.5, G4UniformRand() - 0.5, 0);
    //fParticleGun->SetParticleMomentumDirection(gunDirection);

    fParticleGun->GeneratePrimaryVertex(anEvent);

}
