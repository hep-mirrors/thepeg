// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ACDCSampler class.
//

#include "ThePEG/Handlers/ACDCSampler.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Repository/EventGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ACDCSampler.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

ACDCSampler::~ACDCSampler() {}

void ACDCSampler::initialize() {
  theSampler.setRnd(generator()->random());
  theSampler.eps(theEps);
  theSampler.margin(theMargin);
  theSampler.nTry(2);
  theSampler.maxTry(eventHandler()->maxLoop());
  bool nozero = false;
  for ( int i = 0, N = eventHandler()->nBins(); i < N; ++i )
    if ( theSampler.addFunction(eventHandler()->nDim(i), eventHandler()) )
      nozero = true;
  if ( !nozero ) throw EventInitNoXSec(*eventHandler());
  theSampler.clear();
}

double ACDCSampler::generate() {
  if ( !theSampler.generate() )
    throw EventLoopException(*eventHandler());
  lastPoint() = theSampler.lastPoint();
  return 1.0;
}

void ACDCSampler::rejectLast() {
  theSampler.reject();
}

CrossSection ACDCSampler::integratedXSec() const {
  return theSampler.integral()*nanobarn/sqr(hbarc);
}

int ACDCSampler::lastBin() const {
  return theSampler.last() - 1;
}

double ACDCSampler::sumWeights() const {
  return theSampler.n();
}

void ACDCSampler::dofinish() {
  if ( eventHandler() && eventHandler()->statLevel() > 1 )
    generator()->log()
      << "Statistics for the ACDC sampler:" << endl
      << "Number of bins:" << setw(10) << theSampler.nBins() << endl
      << "Depth of bins: " << setw(10) << theSampler.depth() << endl
      << "efficiency:    " << setw(10) << theSampler.efficiency() << endl;
  if ( theSampler.compensating() )
    generator()->logfile()
      << "The run was ended while the ACDCSampler '" << name()
      << "' was still trying to compensate for weights larger than 1. "
      << "The cross section estimates may therefore be statistically "
      << "inaccurate." << endl;
    
    SamplerBase::dofinish();
}

void ACDCSampler::doinitrun() {
  SamplerBase::doinitrun();
  theSampler.setRnd(generator()->random());
  theSampler.eps(theEps);
  theSampler.margin(theMargin);
  theSampler.nTry(theNTry);
  theSampler.maxTry(eventHandler()->maxLoop());
  bool nozero = false;
  for ( int i = 0, N = eventHandler()->nBins(); i < N; ++i )
    if ( theSampler.addFunction(eventHandler()->nDim(i), eventHandler()) )
      nozero = true;
  if ( !nozero ) throw EventInitNoXSec(*eventHandler());
}

void ACDCSampler::persistentOutput(PersistentOStream & os) const {
  os << theEps << theMargin << theNTry;
  theSampler.output(os);
}

void ACDCSampler::persistentInput(PersistentIStream & is, int) {
  is >> theEps >> theMargin >> theNTry;
  theSampler.input(is);
  if ( generator() ) theSampler.setRnd(generator()->random());
}

ClassDescription<ACDCSampler> ACDCSampler::initACDCSampler;
// Definition of the static class description member.

void ACDCSampler::Init() {

  static ClassDocumentation<ACDCSampler> documentation
    ("This class inherits from \\classnam{SampleBase} and implements "
     "the Auto Compensating Divide-and-Conquer phase space generator, "
     "\\classname{ACDCGen}.");

  static Parameter<ACDCSampler,double> interfaceMargin
    ("Margin",
     "The factor controlling the loss of efficiency when compensating "
     "for a previously underestimated phase space point. If close to one, "
     "the efficiency is increased at the expence of increased number "
     "of cells.",
     &ACDCSampler::theMargin, 1.1, 1.0, 2.0, true, false, true);

  static Parameter<ACDCSampler,double> interfaceEps
    ("Epsilon",
     "The smallest possible cell division allowed.",
     &ACDCSampler::theEps, 100.0*Constants::epsilon, Constants::epsilon,
     1.0e-6, true, false, true);

  static Parameter<ACDCSampler,int> interfaceNTry
    ("Ntry",
     "The number of phase space points tried in the initialization.",
     &ACDCSampler::theNTry, 100, 2, 1000000, true, false, true);

}

