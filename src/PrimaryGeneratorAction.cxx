#include "PrimaryGeneratorAction.h"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

/******************************************************************************/

PrimaryGeneratorAction::PrimaryGeneratorAction() :
  G4VUserPrimaryGeneratorAction()
{
  /** default constructor **/

  mParticleGun = new G4ParticleGun(1);
  auto particle = G4ParticleTable::GetParticleTable()->FindParticle("proton");
  mParticleGun->SetParticleDefinition(particle);
  mParticleGun->SetParticleMomentum(G4ThreeVector(0., 0., 300.*MeV));
  
}

/******************************************************************************/

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  /** default destructor **/

  delete mParticleGun;
}

/******************************************************************************/

void
PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
  /** generate primaries **/

  mParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -25.*cm));
  mParticleGun->GeneratePrimaryVertex(event);  
}

/******************************************************************************/
