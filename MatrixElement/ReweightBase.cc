// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ReweightBase class.
//

#include "ReweightBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ReweightBase.tcc"
#endif

#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

ReweightBase::~ReweightBase() {}

void ReweightBase::
setKinematics(Energy2 shat, tcPDPair in,
	      const cPDVector & out,
	      const Lorentz5Momentum & pina,
	      const Lorentz5Momentum & pinb,
	      const vector<Lorentz5Momentum> & pout) {
  theLastSHat = shat;
  theLastInData = in;
  theLastOutData.clear();
  theLastOutData = out;
  theLastInMomentumA = pina;
  theLastInMomentumB = pinb;
  theLastOutMomentum = pout;
  setKinematics();
}

void ReweightBase::setKinematics(tPPair in, const PVector & out) {
  theLastSHat =  (in.first->momentum() + in.second->momentum()).m2();
  theLastInData = make_pair(in.first->dataPtr(), in.second->dataPtr());
  theLastInMomentumA = in.first->momentum();
  theLastInMomentumB = in.second->momentum();
  theLastOutData.clear();
  theLastOutMomentum.clear();
  for ( PVector::size_type i = 0; i < out.size(); ++i ) {
    theLastOutMomentum.push_back(out[i]->momentum());
    theLastOutData.push_back(out[i]->dataPtr());
  }
  setKinematics();
}

void ReweightBase::setXComb(tXCombPtr xc) {
  theLastXComb = xc;
  theLastSHat = lastSHat();
}

void ReweightBase::clearKinematics() {
  theLastSHat = -1.0*GeV;
  theLastXComb = tXCombPtr();
}

void ReweightBase::persistentOutput(PersistentOStream & os) const {
  os << ounit(theLastSHat, GeV) << theLastInData << theLastOutData
     << ounit(theLastInMomentumA, GeV) << ounit(theLastInMomentumB, GeV)
     << ounit(theLastOutMomentum, GeV);
}

void ReweightBase::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theLastSHat, GeV) >> theLastInData >> theLastOutData
     >> iunit(theLastInMomentumA, GeV) >> iunit(theLastInMomentumB, GeV)
     >> iunit(theLastOutMomentum, GeV);
}

AbstractClassDescription<ReweightBase> ReweightBase::initReweightBase;
// Definition of the static class description member.

void ReweightBase::Init() {

  static ClassDocumentation<ReweightBase> documentation
    ("There is no documentation for the ThePEG::ReweightBase class");

}

