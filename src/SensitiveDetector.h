#ifndef SENSITIVEDETECTOR_H_
#define SENSITIVEDETECTOR_H_

#include "G4VSensitiveDetector.hh"
#include <vector>
#include "DetectorHit.h"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class SensitiveDetector : public G4VSensitiveDetector
{

 public:

  SensitiveDetector(const G4String &name);
  ~SensitiveDetector();

  void Initialize(G4HCofThisEvent *collection);
  G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  void EndOfEvent(G4HCofThisEvent *collection);
  
 private:

  DetectorHitCollection *mCollection;
  //  std::vector<DetectorHit *> mCollection;

}; /** class SensitiveDetector **/

#endif /** SENSITIVEDETECTOR_H_ **/
