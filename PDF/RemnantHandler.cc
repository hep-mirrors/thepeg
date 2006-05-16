// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RemnantHandler class.
//

#include "RemnantHandler.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantHandler.tcc"
#endif

using namespace ThePEG;

RemnantHandler::RemnantHandler(bool multi)
  : isMultiCapable(multi) {}

RemnantHandler::RemnantHandler(const RemnantHandler & x)
  : HandlerBase(x), isMultiCapable(x.isMultiCapable) {}

RemnantHandler::~RemnantHandler() {}

int RemnantHandler::nDim(const PartonBin &, bool) const {
  return 0;
}

void RemnantHandler::
boostRemnants(PartonBinInstance & pb) const {}

void RemnantHandler::persistentOutput(PersistentOStream & os) const {
  os << isMultiCapable;
}

void RemnantHandler::persistentInput(PersistentIStream & is, int) {
  is >> isMultiCapable;
}

bool RemnantHandler::
recreateRemnants(PartonBinInstance & pb, tPPtr oldp, tPPtr newp, double newl,
		 Energy2 scale, const LorentzMomentum & p,
		 const PVector & prev) const {
  if ( !oldp || !prev.empty() ) return false;
  vector<double> rv;
  for ( int i = 0, N = pb.bin()->remDim(); i < N; ++i) rv.push_back(rnd());
  newp->set5Momentum(generate(pb, pb.bin()->remDim()? &rv[0]: 0, scale, p));
  boostRemnants(pb);
  return true;
}  

bool RemnantHandler::
recreateRemnants(PartonBinInstance & pb, tPPtr oldp, tPPtr newp, double newl,
		 Energy2 scale, Energy2 shat,
		 const LorentzMomentum & p, const PVector & prev) const {
  if ( !oldp || !prev.empty() ) return false;
  vector<double> rv;
  int rd = pb.bin()->remDim();
  for ( int i = 0; i < rd; ++i) rv.push_back(rnd());
  newp->set5Momentum(generate(pb, rd > 0? &rv[0]: 0, scale, shat, p));
  boostRemnants(pb);
  return true;
}  

AbstractClassDescription<RemnantHandler> RemnantHandler::initRemnantHandler;

void RemnantHandler::Init() {

  static ClassDocumentation<RemnantHandler> documentation
    ("This is the base class to be used by models describing remnants.");

}

RemnantHandlerException::
RemnantHandlerException(string p0, string p, string r, string mess) {
  theMessage << "Creating remnants for particle '" << p0 << "' when extracting "
	     << "parton '" << p << "' using remnant handler '" << r
	     << "' failed. " << mess;
  severity(warning);
}

