// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LastXCombInfo class.
//

#include "LastXCombInfo.h"
#include "XComb.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LastXCombInfo.tcc"
#endif


using namespace ThePEG;

LastXCombInfoBase::LastXCombInfoBase() {}

LastXCombInfoBase::LastXCombInfoBase(const LastXCombInfoBase & x)
: theLastXComb(x.theLastXComb) {}

LastXCombInfoBase::~LastXCombInfoBase() {}


