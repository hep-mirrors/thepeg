// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the NuclearPhotonPDF class.
//

#include "NuclearPhotonPDF.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/StandardModel/StandardModelBase.h"

using namespace ThePEG;

NuclearPhotonPDF::NuclearPhotonPDF() : q2Min_(ZERO), q2Max_(2.*GeV2)
{}

bool NuclearPhotonPDF::canHandleParticle(tcPDPtr particle) const {
  // all nucleons above the proton
  return abs(particle->iCharge())>4 && abs(particle->id()) > 1000000000;
}

cPDVector NuclearPhotonPDF::partons(tcPDPtr ) const {
  // only photon
  return cPDVector(1,getParticleData(ParticleID::gamma));
}

double NuclearPhotonPDF::xfl(tcPDPtr ion, tcPDPtr gamma, Energy2 qq,
			       double l, Energy2 ) const {

  if(gamma->id()!=ParticleID::gamma) return 0.;
  double x(exp(-l));

  // photon virtuality allowed by kinematics
  Energy2 qqkinmin = sqr(ion->mass()*x)/(1-x);
  Complex form = form_->formFactor(ion,qq);
  return SM().alphaEM()*sqr(ion->iCharge()/3)/Constants::pi*(1.-x)*(1-qqkinmin/qq)*norm(form);
}

double NuclearPhotonPDF::xfvl(tcPDPtr , tcPDPtr , Energy2 ,
				double , Energy2 ) const {
  // valence density is zero
  return 0.0;
}

double NuclearPhotonPDF::
flattenScale(tcPDPtr ion, tcPDPtr, const PDFCuts & c,
	     double l, double z, double & jacobian) const {
  double x = exp(-l);
  // pair<int,int> AZ = massAndZ(ion->id());
  // Energy2 qqmax = min(min(q2Max_,sqr(hbarc/(aFact_*pow(AZ.first,1./3.)))),0.25*sqr(x)*c.sMax());
  Energy2 qqmax = min(q2Max_,0.25*sqr(x)*c.sMax());
  Energy2 qqmin = max(q2Min_, sqr(ion->mass()*x)/(1-x));
  if(qqmin>=qqmax) {
    jacobian = 0.;
    return 0.;
  }
  double low(log(qqmin/c.scaleMaxL(l))),upp(log(qqmax/c.scaleMaxL(l)));
  // jacobian factor
  jacobian *= log(qqmax/qqmin);
  return exp(low+z*(upp-low));
}

double NuclearPhotonPDF::flattenL(tcPDPtr, tcPDPtr, const PDFCuts & c,
				  double z, double & jacobian) const {
  jacobian *= c.lMax() - c.lMin();
  return c.lMin() + z*(c.lMax() - c.lMin());
}

IBPtr NuclearPhotonPDF::clone() const {
  return new_ptr(*this);
}

IBPtr NuclearPhotonPDF::fullclone() const {
  return new_ptr(*this);
}

void NuclearPhotonPDF::persistentOutput(PersistentOStream & os) const {
  os << ounit(q2Min_,GeV2) << ounit(q2Max_,GeV2) << form_;
}

void NuclearPhotonPDF::persistentInput(PersistentIStream & is, int) {
  is >> iunit(q2Min_,GeV2) >> iunit(q2Max_,GeV2) >> form_;
}

// The following static variable is needed for the type
// description system in ThePEG.
DescribeClass<NuclearPhotonPDF,PDFBase>
describeThePEGNuclearPhotonPDF("ThePEG::NuclearPhotonPDF", "NucleonFormFactor.so NuclearPhotonPDF.so");

void NuclearPhotonPDF::Init() {

  static ClassDocumentation<NuclearPhotonPDF> documentation
    ("The NuclearPhotonPDF class implements the PDf for the radiation of a photon from a heavy ion.");
     
  static Parameter<NuclearPhotonPDF,Energy2> interfaceQ2Min
    ("Q2Min",
     "Minimum value of the magnitude of Q^2 for the photon",
     &NuclearPhotonPDF::q2Min_, GeV2, ZERO, ZERO, 100.0*GeV2,
     false, false, Interface::limited);

  static Parameter<NuclearPhotonPDF,Energy2> interfaceQ2Max
    ("Q2Max",
     "Maximum value of the magnitude of Q^2 for the photon",
     &NuclearPhotonPDF::q2Max_, GeV2, 4.0*GeV2, ZERO, 100.0*GeV2,
     false, false, Interface::limited);
  
  static Reference<NuclearPhotonPDF,NucleonFormFactor> interfaceFormFactor
    ("FormFactor",
     "The form factor",
     &NuclearPhotonPDF::form_, false, false, true, false, false);

}

