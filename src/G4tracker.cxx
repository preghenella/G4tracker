#include "G4UIExecutive.hh"
#include "G4RunManager.hh"
#include "FTFP_BERT.hh"
#include "G4GenericPhysicsList.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.h"
#include "ActionInitialization.h"

#include <boost/program_options.hpp>
#include <vector>
#include <string> 

int
main(int argc, char **argv)
{
  
  
  namespace po = boost::program_options;
  po::options_description desc("Options");
  desc.add_options()
    ("help", "Print help messages")
    ("config,c", po::value<std::string>()->required(), "Configuration file")
    ("display,d", "Event display")
    //    ("physics,p", po::value<std::vector<std::string>>()->multitoken(), "Physics list constructors")
   ;
  
  std::string config;
  std::vector<G4String> physicsList;
  
  /** process arguments **/
  try {
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    
    /** help **/ 
    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 1;
    }
    
    /** configuration **/
    if (vm.count("config"))
      config = vm["config"].as<std::string>();
      
    /** physics list **/
    if (vm.count("physics"))
      for (const auto &x :  vm["physics"].as<std::vector<std::string>>())
	physicsList.push_back(x);
      
  }
  catch(std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cout << desc << std::endl;
    return 1;
  }


  auto run = new G4RunManager;
  auto detector = new DetectorConstruction;
  auto physics = new FTFP_BERT;
  std::vector<G4String> physicsLis = {"G4EmStandardPhysics"};
  //  auto physics = new G4GenericPhysicsList(&physicsLis);
  auto action = new ActionInitialization;
  
  run->SetUserInitialization(detector);
  run->SetUserInitialization(physics);
  run->SetUserInitialization(action);

  auto ui = new G4UIExecutive(argc, argv);
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  auto uim = G4UImanager::GetUIpointer();
  uim->ApplyCommand("/control/execute " + config);
  ui->SessionStart();
  
}
