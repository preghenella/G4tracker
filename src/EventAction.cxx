#include "EventAction.h"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "DetectorHit.h"
#include "RunAction.h"
#include "TTree.h"

/******************************************************************************/

EventAction::EventAction(RunAction *aRunAction) :
  G4UserEventAction(),
  mRunAction(aRunAction)
{
  /** default constructor **/
}

/******************************************************************************/

EventAction::~EventAction()
{
  /** default destructor **/
}

/******************************************************************************/

void
EventAction::BeginOfEventAction(const G4Event *aEvent)
{
  /** begin of event action **/

  mRunAction->ClearBuffer("Layer_SD");
}

/******************************************************************************/

void
EventAction::EndOfEventAction(const G4Event *aEvent)
{
  /** end of event action **/

  auto hce = aEvent->GetHCofThisEvent();
  if (!hce) return;

  bool chamberHit[6] = {false, false, false, false, false, false};
  
  auto sdm = G4SDManager::GetSDMpointer();
  auto id = sdm->GetCollectionID("collectionName");
  auto collection = static_cast<DetectorHitCollection *>(hce->GetHC(id));  
  for (G4int ih = 0; ih < collection->GetSize(); ih++) {
    auto hit = static_cast<DetectorHit *>(collection->GetHit(ih));
    auto chamberId = hit->GetChamberId();
    if (hit->GetTrackId() == 1 && !chamberHit[chamberId]) {
      mRunAction->FillHitChamber(chamberId);
      chamberHit[chamberId] = true;
    }
    //    mRunAction->AddHit("Layer_SD", hit);
  }

  //  mRunAction->FillHitTree();
}

/******************************************************************************/
