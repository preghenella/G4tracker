#include "DetectorConstruction.h"
#include "SensitiveDetector.h"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

/******************************************************************************/

DetectorConstruction::DetectorConstruction() :
  G4VUserDetectorConstruction()
{
  /** default constructor **/

  G4cout << "default constructor" << G4endl;
}

/******************************************************************************/

DetectorConstruction::~DetectorConstruction()
{
  /** default destructor **/

  G4cout << "default destructor" << G4endl;
}

/******************************************************************************/

G4VPhysicalVolume *
DetectorConstruction::Construct()
{
  /** construct **/

  /** materials **/
  G4NistManager *nist = G4NistManager::Instance();
  auto air = nist->FindOrBuildMaterial("G4_AIR");
  auto silicon = nist->FindOrBuildMaterial("G4_Si");
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  /** air world **/
  auto worldS = new G4Box("World_S", 50.*cm, 50.*cm, 50.*cm);
  auto worldLV = new G4LogicalVolume(worldS, air, "World_LV");
  auto worldPV = new G4PVPlacement(0,               // no rotation
				   G4ThreeVector(), // at (0,0,0)
				   worldLV,         // its logical volume
				   "World_PV",         // its name
				   0,               // its mother  volume
				   false,           // no boolean operations
				   0,               // copy number
				   false); // checking overlaps    

  /** silicon layer **/
  auto layerS = new G4Box("Layer_S", 25.*cm, 25.*cm, 0.0125*cm);
  auto layerLV = new G4LogicalVolume(layerS, silicon, "Layer_LV");
  
  double layerR[6] = {3.9, 7.6, 15.0, 23.9, 38.0, 43.0};
  for (G4int i = 0; i < 6; i++)
    auto layerPV = new G4PVPlacement(0,
				     G4ThreeVector(0., 0., layerR[i]*cm),
				     layerLV,
				     "Layer_PV",
				     worldLV,
				     false,
				     i,
				     false);
  
  return worldPV;
}

/******************************************************************************/

void
DetectorConstruction::ConstructSDandField()
{
  /** construct sensitive detector and field **/

  auto sensitive = new SensitiveDetector("Layer_SD");
  G4SDManager::GetSDMpointer()->AddNewDetector(sensitive);
  SetSensitiveDetector("Layer_LV", sensitive, true);

  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue = G4ThreeVector();
  auto MagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  MagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  G4AutoDelete::Register(MagFieldMessenger);
  
}

/******************************************************************************/

