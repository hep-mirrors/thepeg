// -*- C++ -*-
//$Id$
// -----------------------------------------------------
#ifndef ThePEG_PtGenerator_H
#define ThePEG_PtGenerator_H
//
// This is the declaration of the <!id>PtGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description: The <!id>PtGenerator<!!id> is the
// base for all classes implementing alternative models for transverse
// momentum.  It inherits from the <!class>HandlerBase<!!class> which
// among other things provides forward access to the flat random
// number function held by the <!class>EventGenerator<!!class> object.
//
// CLASSDOC SUBSECTION See also:
// 
// <a href="http:HandlerBase.html">HandlerBase.h</a>,
// <a href="http:EventGenerator.html">EventGenerator.h</a>.
//

#include "ThePEG/Config/ThePEG.h"
// #include "PtGenerator.fh"
// #include "PtGenerator.xh"
#include "ThePEG/Handlers/HandlerBase.h"

namespace ThePEG {

class PtGenerator: public HandlerBase {

public:
  inline PtGenerator();
  inline PtGenerator(const PtGenerator &);
  virtual ~PtGenerator();
  // Standard ctors and dtor

public:
  virtual pair<Energy,Energy> generate() const =0;
  // Return (px, py) components of the transverse momentum.

public:
  static void Init();
  // Standard Init function used to initialize the interface.

private:
  static AbstractClassDescription<PtGenerator> initPtGenerator;

  //PtGenerator & operator=(const PtGenerator &);
  // Private and non-existent assignment operator.

};


template <>
struct BaseClassTrait<PtGenerator,1> {
  typedef HandlerBase NthBase;
};

template <>
struct ClassTraits<PtGenerator>: public ClassTraitsBase<PtGenerator> {
  static string className() { return "/ThePEG/PtGenerator"; }
};


}

#include "PtGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PtGenerator.tcc"
#endif

#endif /* ThePEG_PtGenerator_H */
