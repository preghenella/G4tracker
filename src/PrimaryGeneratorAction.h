#ifndef PRIMARYGENERATORACTION_H_
#define PRIMARYGENERATORACTION_H_

#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;
class G4ParticleGun;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

 public:

  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction();

  void GeneratePrimaries(G4Event *event);

 private:

  G4ParticleGun *mParticleGun;
  
}; /** class PrimaryGeneratorAction **/

#endif /** PRIMARYGENERATORACTION_H_ **/
