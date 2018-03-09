#ifndef RUNACTION_H_
#define RUNACTION_H_

#include "G4UserRunAction.hh"
#include <map>
#include <vector>
#include <string>
#include "TTree.h"
#include "TH1.h"

class G4Run;
class TFile;
//class TTree;
class DetectorHit;

class RunAction : public G4UserRunAction
{

 public:

  RunAction();
  ~RunAction();

  void BeginOfRunAction(const G4Run *run);
  void EndOfRunAction(const G4Run *run);

  TTree *GetHitTree() const {return mHitTree;};

  void ClearBuffer(std::string name) {mHitBuffer[name].clear();};
  void AddHit(std::string name, DetectorHit *hit) {mHitBuffer[name].push_back(hit);};
  void FillHitTree() {mHitTree->Fill();};
  void FillHitChamber(int chamber) {mHitChamber->Fill(chamber);};
  
 private:

  TFile *mOutputFile;
  TTree *mTrackTree;
  TTree *mHitTree;
  TH1   *mHitChamber;
  std::map<std::string, std::vector<DetectorHit *>> mHitBuffer;
  
}; /** class RunAction **/

#endif /** RUNACTION_H_ **/
