#include <iostream>
#include <string>

#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"

using namespace std;

// Open Event TTree contained in a TFile and save the relative histogram to file
// argv[1] root file name to read
// argv[2] variable branch
// argv[3-5] addittional plotting info (bins,xmin,xmax)
// if no additional info required type default as argv[3]
int main(int argc, char* argv[]) {

    // open data file and get TTree of events
    const char *filename = argv[1];
    TFile* rfile = new TFile(filename, "READ");
    TTree *tev = (TTree*)rfile->Get("Events");

    // variable we want to plot 
    const char *branch = argv[2];


    // info to construct histogram from the branch
    string temp = argv[2];
    temp.append(" >> ");
    temp.append(branch);

    string check = argv[3];
    if(check != "default") {

	temp.append("(");
	temp.append(argv[3]);
	temp.append(",");
	temp.append(argv[4]);
	temp.append(",");
	temp.append(argv[5]);
	temp.append(")");
    }

    const char* histinfo = temp.c_str();

    // as of now the variable we plot is also the histogram name
    cout << histinfo << endl;


    // create histogram from branchname and retrieve pointer
    tev->Draw(histinfo, "", "goff");
    TH1F *h = (TH1F*)gDirectory->Get(branch);

    // save current working area and open/update histograms file
    TDirectory* currentDir = gDirectory;
    TFile* wfile = new TFile("histograms.root", "UPDATE");
    h->Write();


    // close writing file and restore working area
    wfile->Close();
    delete wfile;
    currentDir->cd();

    // close and delete reading file
    rfile->Close();
    delete rfile;
 
    return 0;
}
