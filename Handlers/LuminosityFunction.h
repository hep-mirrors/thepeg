// -*- C++ -*-
#ifndef ThePEG_LuminosityFunction_H
#define ThePEG_LuminosityFunction_H
//
// This is the declaration of the <!id>LuminosityFunction<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>LuminosityFunction<!!id> describes the momentum
// distribution of the incoming beams in an experiment. This is used by a
// <!class>EventHandler<!!class> to generate collisions in their CM
// system. The <!id>LuminosityFunction<!!id> will be asked to produce a
// <!id>LorentzRotation<!!id> giving the transformation to the
// laboratory system.
//
// The <!id>LuminosityFunction<!!id> inherits from the
// <!class>LastXCombInfo<!!class> class to give easy access to the
// information of the generated primary sub-process in the selected
// <!class>XComb<!!class>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:LuminosityFunction.html">LuminosityFunction.h</a>
// <a href="http:XComb.html">XComb.h</a>
// 

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.fh"
#include "ThePEG/Utilities/Interval.h"

// #include "LuminosityFunction.fh"
// #include "LuminosityFunction.xh"

namespace ThePEG {

class LuminosityFunction: public HandlerBase, public LastXCombInfo<> {

  friend class EventHandler;

public:

  LuminosityFunction();
  LuminosityFunction(const LuminosityFunction &);
  virtual ~LuminosityFunction();
  // Standard ctors and dtor

  virtual bool canHandle(const cPDPair &) const = 0;
  // Return true if this luminosity function can actually handle a
  // given pair of incoming particles.

  virtual Energy maximumCMEnergy() const = 0;
  // Return the maximum possible center of mass energy for an event.

  virtual LorentzRotation getBoost() const;
  // Return the rotation needed to transform from the collision cm
  // system to the labotatory system.

  virtual int nDim(const cPDPair &) const;
  // How many random numbers are needed to generate a phase space
  // point? Default is zero in which means the energy of the incoming
  // particles is fixed. The only other reasonable values are 1 and 2.

  virtual double value(const cPDPair &, double l1, double l2) const;
  // The value of the luminosity function for the given particle types
  // for the given energy fractions l1 and l2 (l=log(1/x)). The
  // default version returns 1 if l1 and l2 are zero otherwize zero.

  virtual pair<double,double>
  generateLL(const double * r, double & jacobian) const;
  // Generate energy fractions l1 and l2 (l=log(x)) given 'nDim()'
  // random numbers in the range ]0,1[ given by the iterators. The
  // jacobian argument must be multiplied by the jacobian of the
  // variable transformation to l1 and l2. The default version is just
  // a delta function with a jacobian of 1.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  void select(tXCombPtr);
  // Set information about the selected XComb.

private:

  static AbstractClassDescription<LuminosityFunction>
  initLuminosityFunction;

  LuminosityFunction & operator=(const LuminosityFunction &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<LuminosityFunction,1> {
  typedef HandlerBase NthBase;
};

template <>
struct ClassTraits<LuminosityFunction>:
    public ClassTraitsBase<LuminosityFunction> {
  static string className() { return "/ThePEG/LuminosityFunction"; }
};

}

#include "LuminosityFunction.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LuminosityFunction.tcc"
#endif

#endif /* ThePEG_LuminosityFunction_H */
