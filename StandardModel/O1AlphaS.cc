// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the O1AlphaS class.
//

#include "O1AlphaS.h"
#include "ThePEG/CLHEPWrap/PhysicalConstants.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "O1AlphaS.tcc"
#endif

using namespace ThePEG;

O1AlphaS::~O1AlphaS() {}

IBPtr O1AlphaS::clone() const {
  return new_ptr(*this);
}

IBPtr O1AlphaS::fullclone() const {
  return new_ptr(*this);
}

double O1AlphaS::value(Energy2 scale, const StandardModelBase &) const {
  return 12.0*pi/((33.0-2.0*Nf(scale))*log(scale/sqr(LambdaQCD(Nf(scale)))));
}

vector<Energy2> O1AlphaS::flavourThresholds() const {
  vector<Energy2> thresholds;
  for ( unsigned long f = 1; f <= theMaxFlav; ++f ) {
    PDPtr p = getParticleData(f);
    if ( p ) thresholds.push_back(sqr(p->mass() + p->CC()->mass()));
  }
  return thresholds;
}

vector<Energy> O1AlphaS::LambdaQCDs() const {
  vector<Energy> lambdas(theMaxFlav);
  vector<Energy2> thresholds = flavourThresholds();
  lambdas[theLambdaFlavour - 1] = theLambdaQCD;
  for ( unsigned int f = theLambdaFlavour - 1; f > 1; --f ) {
    lambdas[f-1] =
      sqrt(thresholds[f]*
	   exp(-log(thresholds[f]/sqr(lambdas[f]))*
	       (33.0-2.0*(f+1))/(33.0-2.0*f)));
  }
  lambdas[0] = lambdas[1];
  for ( unsigned int f = theLambdaFlavour; f < theMaxFlav; ++f ) {
    lambdas[f] =
      sqrt(thresholds[f]*
	   exp(-log(thresholds[f]/sqr(lambdas[f-1]))*
	       (33.0-2.0*f)/(33.0-2.0*(f+1))));
  }
  return lambdas;
}  

void O1AlphaS::persistentOutput(PersistentOStream & os) const {
  os << ounit(theLambdaQCD, GeV) << theLambdaFlavour << theMaxFlav;
}

void O1AlphaS::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theLambdaQCD, GeV) >> theLambdaFlavour >> theMaxFlav;
}

ClassDescription<O1AlphaS> O1AlphaS::initO1AlphaS;

void O1AlphaS::Init() {

   static ClassDocumentation<O1AlphaS> documentation
    ("There is no documentation for the ThePEG::O1AlphaS class");

 static Parameter<O1AlphaS,Energy> interfaceLambdaQCD
    ("LambdaQCD",
     "The \\f$\\Lambda_{QCD}\\f$ in GeV for "
     "<interface>LambdaFlav</interface> active "
     "flavours. The value for other numbers of active flavours is derived by "
     "assuming that \\f$\\alpha_S\\f$ is continuous.",
     &O1AlphaS::theLambdaQCD, GeV, 0.25*GeV, 0.0*GeV, 10.0*GeV,
     false, false, true);

  static Parameter<O1AlphaS,unsigned int> interfaceMaxFlav
    ("MaxFlav",
     "The maximum number of flavours used to calculate \\f$\\alpha_S\\f$.",
     &O1AlphaS::theMaxFlav, 6, 3, 8,
     false, false, true);

  static Parameter<O1AlphaS,unsigned int> interfaceLambdaFlavour
    ("LambdaFlav",
     "The number of active flavours for which LambdaQCD is specified.",
     &O1AlphaS::theLambdaFlavour, 4, 3, 8,
     false, false, true, 0, 0, 0, &O1AlphaS::getMaxFlav, 0);

}

