#ifndef DETECTORCONSTRUCTION_H_
#define DETECTORCONSTRUCTION_H_

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{

 public:
  
  DetectorConstruction();
  virtual ~DetectorConstruction();
  
  G4VPhysicalVolume *Construct();
  void ConstructSDandField();
  
 private:

}; /** class DetectorConstruction **/

#endif /** DETECTORCONSTRUCTION_H_ **/
