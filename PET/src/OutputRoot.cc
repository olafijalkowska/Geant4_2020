#include "OutputRoot.hh"


OutputRoot::OutputRoot()
{
   rootManager=G4RootAnalysisManager::Instance();
   
   rootManager->SetFirstNtupleId(0);
   

}

void OutputRoot::CreateFile(G4String filename)
{
    rootManager->OpenFile(filename);
    NaIDetectorTupleId=0;
    CreateNaITuple();

}
void OutputRoot::SaveOutput()
{
   rootManager->Write();
   rootManager->CloseFile();
}

void OutputRoot::CreateNaITuple()
{
   rootManager->CreateNtuple("NaIInfo","Energy deposit and step lenght in NaI detector");
   rootManager->CreateNtupleIColumn("eventId");
   rootManager->CreateNtupleIColumn("detectorId");
   rootManager->CreateNtupleDColumn("energyDep");
   rootManager->CreateNtupleDColumn("stepLength");
   rootManager->FinishNtuple();
}

void OutputRoot::AddNaIHit(int eventId, int detectorId, double enDep, double stepLength)
{
    int cloId=0;
    rootManager->FillNtupleIColumn(NaIDetectorTupleId, cloId, eventId);
    rootManager->FillNtupleIColumn(NaIDetectorTupleId, ++cloId, detectorId);
    rootManager->FillNtupleDColumn(NaIDetectorTupleId, ++cloId, enDep);
    rootManager->FillNtupleDColumn(NaIDetectorTupleId, ++cloId, stepLength);
    rootManager->AddNtupleRow(NaIDetectorTupleId);
}
OutputRoot* OutputRoot::instance=0;
