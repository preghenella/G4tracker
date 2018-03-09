#ifndef EVENTACTION_H_
#define EVENTACTION_H_

#include "G4UserEventAction.hh"

class G4Event;
class RunAction;

class EventAction : public G4UserEventAction
{

 public:

  EventAction(RunAction *aRunAction);
  ~EventAction();

  void BeginOfEventAction(const G4Event *aEvent);
  void EndOfEventAction(const G4Event *aEvent);
  
 private:

  RunAction *mRunAction;
  
}; /** class EventAction **/

#endif /** EVENTACTION_H_ **/
