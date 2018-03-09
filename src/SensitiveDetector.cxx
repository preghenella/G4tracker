#include "SensitiveDetector.h"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "RunAction.h"
#include "TTree.h"

/******************************************************************************/

SensitiveDetector::SensitiveDetector(const G4String &name) :
  G4VSensitiveDetector(name),
  mCollection(nullptr)
{
  /** default constructor **/

  collectionName.insert("collectionName");

}

/******************************************************************************/

SensitiveDetector::~SensitiveDetector()
{
  /** default destructor **/
}

/******************************************************************************/

void
SensitiveDetector::Initialize(G4HCofThisEvent *collection)
{
  /** initialize **/

  /*
  mCollection.clear();
  auto runm = G4RunManager::GetRunManager();
  auto runa = dynamic_cast<const RunAction *>(runm->GetUserRunAction());
  if (!runa) abort();
  auto hitt = runa->GetHitTree();
  hitt->Branch(SensitiveDetectorName, "std::vector<DetectorHit *>", &mCollection);
  */

  mCollection = new DetectorHitCollection(SensitiveDetectorName, "collectionName");
  auto id = G4SDManager::GetSDMpointer()->GetCollectionID("collectionName");
  collection->AddHitsCollection(id, mCollection);
}

/******************************************************************************/

G4bool
SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *history)
{
  /** process hits **/

  auto energy = aStep->GetTotalEnergyDeposit();
  //  if (energy <= 0.) return false;
  auto trackId = aStep->GetTrack()->GetTrackID();
  auto chamberId = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
  auto position = aStep->GetPostStepPoint()->GetPosition();
  
  auto hit = new DetectorHit;
  hit->SetTrackId(trackId);
  hit->SetChamberId(chamberId);
  hit->SetEnergy(energy);
  hit->SetXYZ(position.getX(), position.getY(), position.getZ());
  mCollection->insert(hit);  

  //  mCollection.push_back(hit);

  //  hit->Print();
  /*
  newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
  newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()
                                               ->GetCopyNumber());
  newHit->SetEdep(edep);
  newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());
  */

  
  return true;
}

/******************************************************************************/

void
SensitiveDetector::EndOfEvent(G4HCofThisEvent *collection)
{
  /** end of event **/

  //  G4cout << "END-OF-EVENT-SENSITIVE: " << SensitiveDetectorName << G4endl;
}

/******************************************************************************/
/******************************************************************************/
