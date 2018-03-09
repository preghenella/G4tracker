project(G4tracker)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

set(CMAKE_INSTALL_PREFIX $ENV{HOME})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    DetectorConstruction.cxx
    SensitiveDetector.cxx
    DetectorHit.cxx
    ActionInitialization.cxx
    RunAction.cxx
    EventAction.cxx
    PrimaryGeneratorAction.cxx
    )

set(HEADERS
    DetectorConstruction.h
    SensitiveDetector.h
    DetectorHit.h
    ActionInitialization.h
    RunAction.h
    EventAction.h
    PrimaryGeneratorAction.h
    )

ROOT_GENERATE_DICTIONARY(G__G4trackerLibrary ${HEADERS} LINKDEF G4trackerLibrary_LinkDef.h)

add_library(G4trackerLibrary SHARED ${SOURCES} G__G4trackerLibrary.cxx)
target_link_libraries(G4trackerLibrary ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})
install(TARGETS G4trackerLibrary LIBRARY DESTINATION lib)

add_executable(G4tracker G4tracker.cxx)
target_link_libraries(G4tracker G4trackerLibrary ${Boost_PROGRAM_OPTIONS_LIBRARY})
install(TARGETS G4tracker RUNTIME DESTINATION bin)
