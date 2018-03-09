#include "RunAction.h"
#include "TFile.h"
#include "TTree.h"
#include "G4Run.hh"
#include "G4SDManager.hh"
#include "G4HCtable.hh"

/******************************************************************************/

RunAction::RunAction() :
  G4UserRunAction(),
  mOutputFile(nullptr),
  mTrackTree(nullptr),
  mHitTree(nullptr),
  mHitChamber(nullptr),
  mHitBuffer()
{
  /** default constructor **/
}

/******************************************************************************/

RunAction::~RunAction()
{
  /** default destructor **/

  delete mTrackTree;
  delete mHitTree;
  delete mHitChamber;
  delete mOutputFile;
}

/******************************************************************************/

void
RunAction::BeginOfRunAction(const G4Run *aRun)
{
  /** begin of run action **/
  
  mOutputFile = TFile::Open(Form("G4tracker.%03d.root", aRun->GetRunID()), "RECREATE");
  mTrackTree = new TTree("tracks", "Tree with tracks");
  mHitTree = new TTree("hits", "Tree with hits");
  mHitTree->Branch("Layer_SD", "std::vector<DetectorHit *>", &mHitBuffer["Layer_SD"]);

  mHitChamber = new TH1F("hHitChamber", "", 6, 0, 6);
  
  /*
  auto sdm = G4SDManager::GetSDMpointer();
  auto hct = sdm->GetHCtable();
  for (G4int i = 0; i < hct->entries(); i++) {
    auto sdname = hct->GetSDname(i);
    auto hcname = hct->GetHCname(i);
    mHitTree->Branch(hcname, "
  }
  */

}

/******************************************************************************/

void
RunAction::EndOfRunAction(const G4Run *aRun)
{
  /** end of run action **/

  mTrackTree->Write();
  mHitTree->Write();
  mHitChamber->Write();
  mOutputFile->Close();
}

/******************************************************************************/
