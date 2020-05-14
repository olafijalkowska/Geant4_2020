void Plot3D()
{
    //otwarcie pliku
    TFile* f = new TFile("NaIDetOutput.root");
    TTree* t=(TTree*)f->Get("NaIInfo");

    double xMin = 0;
    double xMax = 40;
    int nBinsX = 1*(xMax-xMin);
    double yMin = 0;
    double yMax = 400;
    int nBinsY = 1*(yMax-yMin);
    double zMin = 0;
    double zMax = 1;
    int nBinsZ = 100*(zMax-zMin);
    TH3F* IdId = new TH3F("IdId","det ID vs det ID",nBinsX,xMin,xMax, nBinsY, yMin, yMax, nBinsZ, zMin, zMax);
    gStyle->SetOptStat(0);
    t->Draw("energyDep:eventId:detectorId>>IdId");
    IdId->Draw("BOX2");

}
