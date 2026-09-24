//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file PS3EventAction.cc
/// \brief Implementation of the PS3EventAction class

#include "PS3EventAction.hh"
#include "PS3RunAction.hh"
#include "PS3Analysis.hh"
#include "PS3DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PS3EventAction::PS3EventAction(PS3RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.)
{
  // Front face of the envelope, where the particle gun sits
  // (env_sizeZ = 10 m in PS3DetectorConstruction, centered at the origin)
  z0 = -0.5 * 10*m;
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PS3EventAction::~PS3EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PS3EventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PS3EventAction::EndOfEventAction(const G4Event*)
{   
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleDColumn(/*ntupleId=*/0, /*colId=*/0, fEdep/1000);
  analysisManager->AddNtupleRow();
}

void PS3EventAction::FillHistograms(G4double e, G4double z, G4double x, G4double y) 
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // fill the per-step shower ntuple (id 1): E in GeV, positions in cm,
  // z measured from the front face of the envelope (the gun position)
  analysisManager->FillNtupleDColumn(1, 0, e/GeV);
  analysisManager->FillNtupleDColumn(1, 1, (z - z0)/cm);
  analysisManager->FillNtupleDColumn(1, 2, std::sqrt(x*x + y*y)/cm);
  analysisManager->FillNtupleDColumn(1, 3, x/cm);
  analysisManager->FillNtupleDColumn(1, 4, y/cm);
  analysisManager->AddNtupleRow(1);
  //G4int h2Id = analysisManager->GetH2Id("EdepKTeV");
  //analysisManager->FillH2(h2Id, x, y, e); // LB -- doesn't appear to be filled?
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
