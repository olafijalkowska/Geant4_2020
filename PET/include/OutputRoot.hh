#ifndef OutputRoot_H
#define OutputRoot_H 1
#include "G4RootAnalysisManager.hh" 

class OutputRoot 
{
	public:
    static OutputRoot* GetInstance()
    {
       if(instance)
           return instance;
       else
       {
          instance = new OutputRoot();
          return instance;
       }
    }
	void SaveOutput();
	void CreateFile(G4String filename);
	void AddNaIHit(int eventId, int detectorId, double enDep, double stepLength);
	private:
	OutputRoot();
	static OutputRoot* instance;
	G4RootAnalysisManager* rootManager;
	void CreateNaITuple();
	int NaIDetectorTupleId;

};

#endif
