// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Amplitude class.
//

#include "Amplitude.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Amplitude.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

Amplitude::Amplitude() {}

Amplitude::Amplitude(const Amplitude & x)
  : HandlerBase(x) {}

Amplitude::~Amplitude() {}

void Amplitude::persistentOutput(PersistentOStream &) const {
  // os <<;
}

void Amplitude::persistentInput(PersistentIStream &, int) {
  // is >> ;
}

AbstractClassDescription<Amplitude> Amplitude::initAmplitude;
// Definition of the static class description member.

void Amplitude::rebind(const TranslationMap & trans)
  throw(RebindException) {
  HandlerBase::rebind(trans);
}

void Amplitude::Init() {
  static ClassDocumentation<Amplitude> documentation
    ("This the abstract class from which any amplitude class, associated with ",
     "a vertex inherits from.");
}



Complex Amplitude::overestimateValue( const tcPDVector & particles,
				      const vector<Lorentz5Momentum> & momenta, 
				      const vector<int> & helicities ) {
  return value(particles,momenta,helicities);
}


Complex Amplitude::value( const PVector & particles,
			  const vector<int> & helicities ) {
  tcPDVector dataParticles;
  vector<Lorentz5Momentum> momenta;
  for ( PVector::const_iterator cit = particles.begin();
	cit != particles.end(); ++cit ) {
    dataParticles.push_back( (*cit)->dataPtr() );
    momenta.push_back( (*cit)->momentum() );
  }
  return value(dataParticles,momenta,helicities);
}


Complex Amplitude::overestimateValue( const PVector & particles,
				      const vector<int> & helicities ) {
  tcPDVector dataParticles;
  vector<Lorentz5Momentum> momenta;
  for ( PVector::const_iterator cit = particles.begin();
	cit != particles.end(); ++cit ) {
    dataParticles.push_back( (*cit)->dataPtr() );
    momenta.push_back( (*cit)->momentum() );
  }
  return overestimateValue(dataParticles,momenta,helicities);
}


