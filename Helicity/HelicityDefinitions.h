// -*- C++ -*-
#ifndef THEPEG_HelicityDefinitions_H
#define THEPEG_HelicityDefinitions_H
//
// This is the declaration of the <!id>HelicityDefinitions<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//  The <!id>HelicityDefinitions<!!id> class is a static class which
//  contains information on which representation of the Dirac matrix
//  is being used. All the code can in principle cope with either of
//  the defintions described in the <!id>LorentzSpinor<!!id> class
//  however the valid choices and the default to be used are defined
//  here.
//
//  The normal choice for the default is the use of the HELAS
//  representation, however if you are using external packages which
//  use another definition then it may be worth changing the default
//  choice here.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="LorentzSpinor.html">LorentzSpinor.h</a>,
// <a href="LorentzSpinorBar.html">LorentzSpinorBar.h</a>.
//
// Author: Peter Richardson
//

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Exception.h"
// #include "HelicityDefinitions.fh"
// #include "HelicityDefinitions.xh"

namespace ThePEG {
namespace Helicity {

class HelicityDefinitions {

public:

  inline static int getDirac(){return _idirac;}

  inline static bool validDirac(int i ){return i>=_idiracmin && i <=_idiracmax;}

private:

  HelicityDefinitions();
  // static class can't be created

  static const int _idirac=2;
  // default choice of the dirac matrix representation
  static const int _idiracmin=1,_idiracmax=2;
  // valid choices of the representation

};

class HelicityLogicalError: public Exception {};

class HelicityConsistencyError: public Exception {};

}
}

#endif /* THEPEG_HelicityDefinitions_H */
