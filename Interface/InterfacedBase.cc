// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the InterfacedBase class.
//

#include "InterfacedBase.h"
#include "ThePEG/Repository/BaseRepository.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/EnumIO.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "InterfacedBase.tcc"
#endif

using namespace ThePEG;

InterfacedBase::~InterfacedBase() {}

void InterfacedBase::readSetup(istream &) throw(SetupException) {}

void InterfacedBase::persistentOutput(PersistentOStream & os) const {
  os << fullName() << isLocked << isTouched << oenum(initState);
}

void InterfacedBase::persistentInput(PersistentIStream & is, int) {
  string n;
  is >> n >> isLocked >> isTouched >> ienum(initState);
  name(n);
}

AbstractClassDescription<InterfacedBase> InterfacedBase::initInterfacedBase;

void InterfacedBase::Init() {}

void InterfacedBase::UpdateChecker::check(tIBPtr ip, bool & touch) {
  if ( !ip ) return;
  ip->update();
  if ( ip->touched() ) touch = true;
}

