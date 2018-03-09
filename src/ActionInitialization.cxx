#include "ActionInitialization.h"
#include "RunAction.h"
#include "EventAction.h"
#include "PrimaryGeneratorAction.h"

/******************************************************************************/

ActionInitialization::ActionInitialization() :
  G4VUserActionInitialization()
{
  /** default constructor **/
}

/******************************************************************************/

ActionInitialization::~ActionInitialization()
{
  /** default destructor **/
}

/******************************************************************************/

void
ActionInitialization::BuildForMaster() const
{
  /** build for master **/

  SetUserAction(new RunAction);
}

/******************************************************************************/

void
ActionInitialization::Build() const
{
  /** build **/

  auto primgenAction = new PrimaryGeneratorAction;
  auto runAction = new RunAction;
  auto eventAction = new EventAction(runAction);
  
  
  SetUserAction(primgenAction);
  SetUserAction(runAction);
  SetUserAction(eventAction);
}

