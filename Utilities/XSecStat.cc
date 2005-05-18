// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the XSecStat class.
//

#include "XSecStat.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "XSecStat.tcc"
#endif

namespace ThePEG {

PersistentOStream & operator<<(PersistentOStream & os, const XSecStat & x) {
  x.output(os);
  return os;
}

PersistentIStream & operator>>(PersistentIStream & is, XSecStat & x) {
  x.input(is);
  return is;
}

}

using namespace ThePEG;

void XSecStat::output(PersistentOStream & os) const {
  os << theMaxXSec << theAttempts << theAccepted
     << theSumWeights << theSumWeights2;
}

void XSecStat::input(PersistentIStream & is) {
  is >> theMaxXSec >> theAttempts >> theAttempts
     >> theSumWeights >> theSumWeights2;
  lastWeight = 0.0;
}

