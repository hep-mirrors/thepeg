// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PDFCuts class.
//

#include "PDFCuts.h"
#include "ThePEG/Handlers/KinematicalCuts.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PDFCuts.tcc"
#endif

using namespace ThePEG;

PDFCuts::
PDFCuts(const KinematicalCuts & kc, bool first, const SInterval & S,
	const SInterval & sHatIn) {
  SInterval sHat(max(sHatIn.lower(), kc.sHatMin()),
		 min(sHatIn.upper(), kc.sHatMax()));
  double xmin = sqrt(sHat.lower()/S.upper());
  double xmax = sqrt(sHat.upper()/S.lower());
  theScale = SInterval(kc.scaleMin(), kc.scaleMax());
  double x1max = min(xmax*exp(kc.yStarMax()), kc.x1Max());
  double x2max = min(xmax*exp(-kc.yStarMin()), kc.x2Max());
  if ( first ) {
    double x1min = max(xmin*exp(kc.yStarMin()), kc.x1Min());
    theSMax = x2max*S.upper();
    theL = Interval<double>(log(1.0/x1max), log(1.0/x1min));
  } else {
    double x2min = max(xmin*exp(-kc.yStarMax()), kc.x2Min());
    theSMax = x1max*S.upper();
    theL = Interval<double>(log(1.0/x2max), log(1.0/x2min));
  }
}

PDFCuts::
PDFCuts(const KinematicalCuts & kc, bool first, Energy maxEnergy) {
  SInterval sHat(kc.sHatMin(), kc.sHatMax());
  double xmin = sqrt(sHat.lower())/maxEnergy;
  double xmax = 1.0;
  theScale = SInterval(kc.scaleMin(), kc.scaleMax());
  double x1max = min(xmax*exp(kc.yStarMax()), kc.x1Max());
  double x2max = min(xmax*exp(-kc.yStarMin()), kc.x2Max());
  if ( first ) {
    double x1min = max(xmin*exp(kc.yStarMin()), kc.x1Min());
    theSMax = x2max*sqr(maxEnergy);
    theL = Interval<double>(-log(x1max), -log(x1min));
  } else {
    double x2min = max(xmin*exp(-kc.yStarMax()), kc.x2Min());
    theSMax = x1max*sqr(maxEnergy);
    theL = Interval<double>(-log(x2max), -log(x2min));
  }
}

