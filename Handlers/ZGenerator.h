// -*- C++ -*-
#ifndef ThePEG_ZGenerator_H
#define ThePEG_ZGenerator_H
// This is the declaration of the ZGenerator class.

#include "ThePEG/Config/ThePEG.h"
// #include "ZGenerator.fh"
// #include "ZGenerator.xh"
#include "ThePEG/Handlers/HandlerBase.h"

namespace ThePEG {

/**
 * ZGenerator is the base class for all classes implementing models to
 * generate the momentum fraction, \f$z\f$, taken by hadrons produced in a
 * hadronization scenario.
 * 
 * It inherits from <code>HandlerBase</code> class which among other
 * things provides forward access to the random number generator of
 * the EventGenerator class.
 * 
 * @see \ref ZGeneratorInterfaces "The interfaces"
 * defined for ZGenerator.
 * @see HandlerBase
 * @see EventGenerator
 */
class ZGenerator: public HandlerBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline ZGenerator();

  /**
   * Copy-constructor.
   */
  inline ZGenerator(const ZGenerator &);

  /**
   * Destructor.
   */
  virtual ~ZGenerator();
  //@}

public:

  /** @name Virtual functions mandated by the ZGenerator base class. */
  //@{
  /**
   * Return the momentum fraction. Assume that an initial
   * (anti-)(di-)quark \a q1 produces a hadron and leaves behind
   * another (anti-)(di-)quark \a q2. The hadron is assumed to have a
   * squared transverse mass, \a mT2, w.r.t. the initial quark
   * direction.
   * @return the energy fraction.
   */
  virtual double generate(cPDPtr q1, cPDPtr q2, Energy2 mT2 ) const =0;
  //@}

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();


private:

  /**
   * Describe an abstract class without persistent data.
   */
  static AbstractClassDescription<ZGenerator> initZGenerator;

};


/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the base class of
 * ZGenerator.
 */
template <>
struct BaseClassTrait<ZGenerator,1>: public ClassTraitsType {
  /** Typedef of the base class of ZGenerator. */
  typedef HandlerBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * ZGenerator class.
 */
template <>
struct ClassTraits<ZGenerator>: public ClassTraitsBase<ZGenerator> {
  /** Return the class name.  */
  static string className() { return "ThePEG::ZGenerator"; }
};
  
/** @endcond */

}

#include "ZGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ZGenerator.tcc"
#endif

#endif /* ThePEG_ZGenerator_H */
