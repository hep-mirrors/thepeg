// -*- C++ -*-
#ifndef ThePEG_LuminosityFunction_H
#define ThePEG_LuminosityFunction_H
// This is the declaration of the LuminosityFunction class.

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.fh"
#include "ThePEG/Utilities/Interval.h"

// #include "LuminosityFunction.fh"
// #include "LuminosityFunction.xh"

namespace ThePEG {

/**
 * The LuminosityFunction describes the momentum distribution of the
 * incoming beams in an experiment. This is used by a EventHandler to
 * generate collisions in their CM system. The LuminosityFunction will
 * be asked to produce a LorentzRotation giving the transformation to
 * the laboratory system.
 *
 * The LuminosityFunction inherits from the LastXCombInfo class to
 * give easy access to the information of the generated primary
 * sub-process in the selected XComb.
 *
 * @see \ref LuminosityFunctionInterfaces "The interfaces"
 * defined for LuminosityFunction.
 * @see LuminosityFunction
 * @see XComb
 * 
 */
class LuminosityFunction: public HandlerBase, public LastXCombInfo<> {

  /** EventHandler is a friend. */
  friend class EventHandler;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  LuminosityFunction();

  /**
   * Copy-constructor.
   */
  LuminosityFunction(const LuminosityFunction &);

  /**
   * Destructor.
   */
  virtual ~LuminosityFunction();
  //@}

  /** @name Virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * Return true if this luminosity function can actually handle a
   * given pair of incoming particles.
   */
  virtual bool canHandle(const cPDPair &) const = 0;

  /**
   * Return the maximum possible center of mass energy for an event.
   */
  virtual Energy maximumCMEnergy() const = 0;

  /**
   * Return the rotation needed to transform from the collision cm
   * system to the labotatory system. This default version returns the
   * unit transformation.
   */
  virtual LorentzRotation getBoost() const;

  /**
   * How many random numbers are needed to generate a phase space
   * point? Default is zero in which means the energy of the incoming
   * particles is fixed. The only other reasonable values are 1 and 2.
   */
  virtual int nDim(const cPDPair &) const;

  /**
   * The value of the luminosity function for the given particle types
   * for the given energy fractions l1 and l2 (\f$l=\log(1/x)\f$). The
   * default version returns 1 if l1 and l2 are zero otherwize zero.
   */
  virtual double value(const cPDPair &, double l1, double l2) const;

  /**
   * Generate energy fractions l1 and l2 (\f$l=\log(1/x)\f$) given
   * 'nDim()' random numbers in the range ]0,1[ given by the
   * iterators. The jacobian argument must be multiplied by the
   * jacobian of the variable transformation to l1 and l2. The default
   * version is just a delta function with a jacobian of 1.
   */
  virtual pair<double,double>
  generateLL(const double * r, double & jacobian) const;
  //@}

public:

  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(PersistentOStream & os) const;

  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(PersistentIStream & is, int version);
  //@}

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

  /**
   * Set information about the selected XComb.
   */
  void select(tXCombPtr);

private:

  /**
   * Describe an abstract class with persistent data.
   */
  static AbstractClassDescription<LuminosityFunction>
  initLuminosityFunction;

  /**
   *  Private and non-existent assignment operator.
   */
  LuminosityFunction & operator=(const LuminosityFunction &);

};

/**
 * This template specialization informs ThePEG about the
 * base class of LuminosityFunction.
 */
template <>
struct BaseClassTrait<LuminosityFunction,1>: public ClassTraitsType {
  /** Typedef of the base class of LuminosityFunction. */
  typedef HandlerBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * LuminosityFunction class.
 */
template <>
struct ClassTraits<LuminosityFunction>:
    public ClassTraitsBase<LuminosityFunction> {
  /** Return the class name. */
  static string className() { return "ThePEG::LuminosityFunction"; }
};

}

#include "LuminosityFunction.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LuminosityFunction.tcc"
#endif

#endif /* ThePEG_LuminosityFunction_H */
