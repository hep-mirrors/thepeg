// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LorentzRotation class.
//

#include "LorentzRotation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LorentzRotation.tcc"
#endif


using namespace ThePEG;

// output operator
std::ostream & LorentzRotation::print( std::ostream & os ) const
{
  os <<    "Spin 1   Transform: \n " << _one 
     << "\n Spin 1/2 Transform: \n " << _half << "\n";
  return os;
}
