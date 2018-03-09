#ifndef DETECTORHIT_H_
#define DETECTORHIT_H_

#include "G4VHit.hh"
#include "G4THitsCollection.hh"

class DetectorHit : public G4VHit
{

 public:
  DetectorHit();
  ~DetectorHit();

  void SetTrackId(int val) {mTrackId = val;};
  void SetChamberId(int val) {mChamberId = val;};
  void SetEnergy(double val) {mEnergy = val;};
  void SetXYZ(double x, double y, double z) {
    mXYZ[0] = x;
    mXYZ[1] = y;
    mXYZ[2] = z;
  };
  
  int GetTrackId() const {return mTrackId;};
  int GetChamberId() const {return mChamberId;};
  double GetEnergy() const {return mEnergy;};
  
 private:

  int mTrackId;
  int mChamberId;
  double mEnergy;
  double mXYZ[3];
  
}; /** class DetectorHit **/

typedef G4THitsCollection<DetectorHit> DetectorHitCollection;

#endif /** DETECTORHIT_H_ **/
