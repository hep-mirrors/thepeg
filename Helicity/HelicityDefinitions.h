// -*- C++ -*-
#ifndef THEPEG_HelicityDefinitions_H
#define THEPEG_HelicityDefinitions_H
//
// This is the declaration of the <!id>HelicityDefinitions<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
//

#include "ThePEG/Config/ThePEG.h"
// #include "HelicityDefinitions.fh"
// #include "HelicityDefinitions.xh"

namespace ThePEG {
namespace Helicity {

class HelicityDefinitions {

public:

  inline static int getDirac() {
    return 1;
  }

};

}
}

#endif /* THEPEG_HelicityDefinitions_H */
