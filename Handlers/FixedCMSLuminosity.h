// -*- C++ -*-
#ifndef ThePEG_FixedCMSLuminosity_H
#define ThePEG_FixedCMSLuminosity_H
//
// This is the declaration of the <!id>FixedCMSLuminosity<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>FixedCMSLuminosity<!!id> class describes an experiment
// with incoming particles colliding with precicely defined and
// opposite momenta. It is derived from the
// <!class>LuminosityFunction<!!class> base class.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:LuminosityFunction.html">LuminosityFunction.h</a>
// 

#include "LuminosityFunction.h"
// #include "FixedCMSLuminosity.fh"
// #include "FixedCMSLuminosity.xh"

namespace ThePEG {

class FixedCMSLuminosity: public LuminosityFunction {

public:

  inline FixedCMSLuminosity();
  inline FixedCMSLuminosity(const FixedCMSLuminosity &);
  virtual ~FixedCMSLuminosity();
  // Standard ctors and dtor

public:

  inline virtual bool canHandle(const cPDPair &) const;
  // Return true if this luminosity function can actually handle a
  // given pair of incoming particles.

  inline virtual Energy maximumCMEnergy() const;
  // Return the center of mass energy.

  inline Energy energy() const;
  // The average total energy in the cms of the incoming particles.

public:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  Energy theEnergy;
  // The total energy in the collisons.

private:

  static ClassDescription<FixedCMSLuminosity> initFixedCMSLuminosity;

  FixedCMSLuminosity & operator=(const FixedCMSLuminosity &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<FixedCMSLuminosity,1> {
  typedef LuminosityFunction NthBase;
};

template <>
struct ClassTraits<FixedCMSLuminosity>:
    public ClassTraitsBase<FixedCMSLuminosity> {
  static string className() { return "/ThePEG/FixedCMSLuminosity"; }
  static string library() { return "FixedCMSLuminosity.so"; }
};

}

#include "FixedCMSLuminosity.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FixedCMSLuminosity.tcc"
#endif

#endif /* ThePEG_FixedCMSLuminosity_H */
