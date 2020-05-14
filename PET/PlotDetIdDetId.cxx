void PlotDetIdDetId()
{
    //otwarcie pliku
    TFile* f = new TFile("NaIDetOutput.root");
    TTree* t=(TTree*)f->Get("NaIInfo");

    double xMin = 0;
    double xMax = 40;
    int nBinsX = 1*(xMax-xMin);
    double yMin = 0;
    double yMax = 200;
    int nBinsY = 1*(yMax-yMin);
    TH2F* IdId = new TH2F("IdId","det ID vs det ID",nBinsX,xMin,xMax, nBinsY, yMin, yMax);
    gStyle->SetOptStat(0);//brak legendy
    t->Draw("eventId:detectorId>>IdId");
    IdId->Draw("colz");
}
