// -*- C++ -*-
//$Id$
// ----------------------------------------------------
#ifndef ThePEG_ZGenerator_H
#define ThePEG_ZGenerator_H
//
// This is the declaration of the <!id>ZGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>ZGenerator<!!id> is the base class for all classes 
// implementing models to generate the momentum fraction (Z) 
// taken by hadrons produced during the fragmentation phase.
// 
// It inherits from <!id>HandlerBase<!!id> class which among other
// things provides forward access to the random number generator of
// the <!class>EventGenerator<!!class> class.
// 
// CLASSDOC SUBSECTION See also:
//
// <a href="http:HandlerBase.html">HandlerBase.h</a>,
// <a href="http:EventGenerator.html">EventGenerator.h</a>
// 

#include "ThePEG/Config/ThePEG.h"
// #include "ZGenerator.fh"
// #include "ZGenerator.xh"
#include "ThePEG/Handlers/HandlerBase.h"

namespace ThePEG {

class ZGenerator: public HandlerBase {

public:

  inline ZGenerator();
  inline ZGenerator(const ZGenerator &);
  virtual ~ZGenerator();
  // Standard ctors and dtor

public:
  virtual double generate(cPDPtr q1, cPDPtr q2, Energy2 mT2 ) const =0;
  // Return the momentum fraction Z, of the fragmented hadron givent
  // its two constituent flavours (quark, antiquark) or (quark, diquark)
  // and transverse mass squared.
 
  static void Init();
  // Standard Init function used to initialize the interface.


private:
  static AbstractClassDescription<ZGenerator> initZGenerator;

};


template <>
struct BaseClassTrait<ZGenerator,1> {
  typedef HandlerBase NthBase;
};

template <>
struct ClassTraits<ZGenerator>: public ClassTraitsBase<ZGenerator> {
  static string className() { return "/ThePEG/ZGenerator"; }
};
  
}

#include "ZGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ZGenerator.tcc"
#endif

#endif /* ThePEG_ZGenerator_H */
