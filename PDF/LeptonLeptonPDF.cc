// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LeptonLeptonPDF class.
//

#include "LeptonLeptonPDF.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/Maths.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/StandardModel/StandardModelBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"

using namespace ThePEG;

IBPtr LeptonLeptonPDF::clone() const {
  return new_ptr(*this);
}

IBPtr LeptonLeptonPDF::fullclone() const {
  return new_ptr(*this);
}

bool LeptonLeptonPDF::canHandleParticle(tcPDPtr particle) const {
  return ( abs(particle->id()) < 20 || abs(particle->id()) > 10 );
}

bool LeptonLeptonPDF::hasPoleIn1(tcPDPtr particle, tcPDPtr parton) const {
  return particle == parton;
}

cPDVector LeptonLeptonPDF::partons(tcPDPtr p) const {
  cPDVector ret;
  if ( canHandleParticle(p) ) ret.push_back(p);
  return ret;
}

double LeptonLeptonPDF::
xfl(tcPDPtr particle, tcPDPtr  parton, Energy2 partonScale, double l,
    Energy2) const {
  using namespace Constants;
  if ( parton != particle || l < 0.0 ) return 0.0;
  static const double gf = 3.0/4.0 - EulerGamma;
  const double x = exp(-l);
  const double eps = Math::exp1m(-l);
  const double lx = -l;
  const double l1x = log(eps);
  const double beta2 =
    SM().alphaEM()*(log(partonScale/sqr(particle->mass()))-1.0)/pi;
  return x*(beta2*pow(eps, beta2-1.0)*exp(gf*beta2)/Math::gamma(beta2+1.0)
	    - 0.5*beta2*(1.0+x) + sqr(beta2)*((1.0+x)*(-4.0*l1x+3.0*lx)
					      - 4.0*lx/eps - 5.0 - x)/8.0);
}

double LeptonLeptonPDF::
xfvl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
     double l, Energy2 particleScale) const {
  return xfl(particle, parton, partonScale, l, particleScale);
}

double LeptonLeptonPDF::
xfvx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
     double x, double eps, Energy2 particleScale) const {
  using Math::log1m;
  return xfl(particle, parton, partonScale,
	     (x < 0.5 || eps <= 0.0)? -log(x): -log1m(eps), particleScale);
}

double LeptonLeptonPDF::
flattenL(tcPDPtr particle, tcPDPtr,
	 const PDFCuts & c, double z, double & jacobian) const {
  using namespace Constants;
  using Math::log1m;
  Energy2 scale = min(c.sMax(), c.scaleMax());
  if ( c.scaleMin() > 0.0*GeV2 ) scale = min(scale, c.scaleMin());
  double beta2 =
    SM().alphaEM()*(log(scale/sqr(particle->mass()))-1.0)/pi;
//   double zpow = pow(z, 1.0/beta2);
//   jacobian = zpow/(1.0/beta2+1);
//   return z*zpow;
//  double l = pow(z, 1.0/beta2);
//  jacobian = l/(z*beta2);
//  z = max(z, pow(std::numeric_limits<double>::min()*1.5, beta2));
  double eps = pow(z, 1.0/beta2);
  double l = -log1m(eps);
  jacobian *= eps/(beta2*z*(1.0 - eps));
  return l;
}

NoPIOClassDescription<LeptonLeptonPDF> LeptonLeptonPDF::initLeptonLeptonPDF;

void LeptonLeptonPDF::Init() {

  static ClassDocumentation<LeptonLeptonPDF> documentation
    ("Describes the distribution of leptons within leptons, ie. the energy "
     "loss of leptons due to radiation of soft photons.");

}

