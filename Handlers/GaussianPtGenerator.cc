// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the GaussianPtGenerator class.
//

#include "GaussianPtGenerator.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/CLHEPWrap/Transverse.h"
#include "ThePEG/Repository/EventGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "GaussianPtGenerator.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

GaussianPtGenerator::~GaussianPtGenerator() {}

TransverseMomentum GaussianPtGenerator::generate() const {
  pair<Energy,Energy> ret;
  Energy pt = 0.0*GeV;
  while ( ( pt = theSigma*sqrt(-log(rnd())) ) > theUpperCut ) {}
  double phi = rnd(2.0*Constants::pi);
  ret.first = pt*cos(phi);
  ret.second = pt*sin(phi);

  return ret;
}


void GaussianPtGenerator::persistentOutput(PersistentOStream & os) const {
  os << ounit(theSigma, GeV) << ounit(theUpperCut, GeV);
}

void GaussianPtGenerator::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theSigma, GeV) >> iunit(theUpperCut, GeV);
}

ClassDescription<GaussianPtGenerator> GaussianPtGenerator::initGaussianPtGenerator;
// Definition of the static class description member.

void GaussianPtGenerator::Init() {

  static ClassDocumentation<GaussianPtGenerator> documentation
    ("The ThePEG::GaussianPtGenerator class generates a gaussian "
     "transverse momentum.");

  static Parameter<GaussianPtGenerator,Energy> interfaceSigma
    ("Sigma",
     "The width of the Gaussian distribution. The average squared transverse momentum is Sigma squared.",
     &GaussianPtGenerator::theSigma, GeV, 1.0*GeV, 0.0*GeV, 10.0*GeV,
     true, false, true);

  static Parameter<GaussianPtGenerator,Energy> interfaceUpperCut
    ("UpperCut",
     "Upper cutoff for the transverse momentum distribution.",
     &GaussianPtGenerator::theUpperCut, GeV, 5.0*GeV, 0.0*GeV, 50.0*GeV,
     true, false, true);

}

