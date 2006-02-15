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

#include "ThePEG/Handlers/StandardXComb.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

ReweightBase::ReweightBase() {}

ReweightBase::ReweightBase(const ReweightBase & x)
  : HandlerBase(x), LastXCombInfo<>(x) {}

ReweightBase::~ReweightBase() {}

void ReweightBase::setXComb(tXCombPtr xc) {
  theLastXComb = xc;
}

void ReweightBase::persistentOutput(PersistentOStream & os) const {
  os << theLastXComb;
}

void ReweightBase::persistentInput(PersistentIStream & is, int) {
  is >> theLastXComb;
}

AbstractClassDescription<ReweightBase> ReweightBase::initReweightBase;
// Definition of the static class description member.

void ReweightBase::Init() {

  static ClassDocumentation<ReweightBase> documentation
    ("There is no documentation for the ThePEG::ReweightBase class");

}

