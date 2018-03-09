#ifndef ACTIONINITIALIZATION_H_
#define ACTIONINITIALIZATION_H_

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization
{

 public:

  ActionInitialization();
  ~ActionInitialization();

  void BuildForMaster() const;
  void Build() const;

 private:
  

}; /** class ActionInitialization **/

#endif /** ACTIONINITIALIZATION_H_ **/
