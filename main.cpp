#include <iostream>
#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/ProgressLog.h"
#include "TCanvas.h"
#include "TH1D.h"

using namespace std;
using namespace Pythia8;

const double PI = 4.0 * atan(1.0);

int main() {
    Pythia pythia;
    pythia.readString("Beams:eCM = 13000.0");
    pythia.readString("HardQCD:all = on");
    pythia.readString("PDF:pSet = LHAPDF6:CT14lo");
    pythia.init();

    TCanvas* c = new TCanvas("c", "c");
    TH1D* hpT = new TH1D("hpT", "Transverse Momentum", 100, 0.0, 2.0);
    TH1D* hy = new TH1D("hy", "Rapidity", 100, -15.0, 15.0);
    TH1D* heta = new TH1D("heta", "PseudoRapidity", 100, -15.0, 15.0);
    TH1D* hphi = new TH1D("hphi", "Azimuthal Angle", 100, -PI, PI);
    TH1D* htheta = new TH1D("htheta", "Polar Angle", 100, 0.0, PI);

    int nEvent = 100000;

    ProgressLog logger(nEvent);

    for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
        if (!pythia.next()) continue;
        for (int i = 0; i < pythia.event.size(); ++i) {
            if (pythia.event[i].isFinal() && pythia.event[i].isCharged()) {
                hpT->Fill(pythia.event[i].pT());
                hy->Fill(pythia.event[i].y());
                heta->Fill(pythia.event[i].eta());
                hphi->Fill(pythia.event[i].phi());
                htheta->Fill(pythia.event[i].theta());
            }
        }
        logger(iEvent);
    }

    pythia.stat();

    hpT->Scale(pythia.info.sigmaGen() / (pythia.info.nAccepted() * 0.02));
    hy->Scale(pythia.info.sigmaGen() / (pythia.info.nAccepted() * 3.0 / 10.0));
    heta->Scale(pythia.info.sigmaGen() / (pythia.info.nAccepted() * 3.0 / 10.0));
    hphi->Scale(pythia.info.sigmaGen() / (pythia.info.nAccepted() * PI / 50.0));
    htheta->Scale(pythia.info.sigmaGen() / (pythia.info.nAccepted() * PI / 100.0));

    hpT->SetTitle("Transverse Momentum;p_{T} [GeV/c];#frac{d#sigma}{dp_{T}}#left[#frac{mb}{GeV/c}#right]");
    hy->SetTitle("Rapidity;y;#frac{d#sigma}{dy}#left[mb#right]");
    heta->SetTitle("PseudoRapidity;#eta;#frac{d#sigma}{d#eta}#left[mb#right]");
    hphi->SetTitle("Azimuthal Angle;#phi [rad];#frac{d#sigma}{d#phi}#left[#frac{mb}{rad}#right]");
    htheta->SetTitle("Polar Angle;#theta [rad];#frac{d#sigma}{d#theta}#left[#frac{mb}{rad}#right]");

    hpT->Draw();
    c->Draw();
    c->Print("Pythia8Example-pT.pdf");

    hy->Draw();
    c->Draw();
    c->Print("Pythia8Example-y.pdf");

    heta->Draw();
    c->Draw();
    c->Print("Pythia8Example-eta.pdf");

    hphi->Draw();
    c->Draw();
    c->Print("Pythia8Example-phi.pdf");

    htheta->Draw();
    c->Draw();
    c->Print("Pythia8Example-theta.pdf");

    return 0;
}