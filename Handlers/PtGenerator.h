// -*- C++ -*-
#ifndef ThePEG_PtGenerator_H
#define ThePEG_PtGenerator_H
// This is the declaration of the PtGenerator class.

#include "ThePEG/Config/ThePEG.h"
// #include "PtGenerator.fh"
// #include "PtGenerator.xh"
#include "ThePEG/Handlers/HandlerBase.h"

namespace ThePEG {

/**
 * PtGenerator is the base for all classes implementing alternative
 * models for transverse momentum generation.  It inherits from the
 * HandlerBase which among other things provides forward access to the
 * random number object held by the EventGenerator object.
 *
 * @see HandlerBase,
 * @see EventGenerator.
 *
 */
class PtGenerator: public HandlerBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline PtGenerator();

  /**
   * Copy-constructor.
   */
  inline PtGenerator(const PtGenerator &);

  /**
   * Destructor.
   */
  virtual ~PtGenerator();
  //@}

public:

  /** @name Virtual functions to be implemented by sub-classes. */
  //@{
  /**
   * Generate (\f$k_x, k_y\f$) components of the transverse
   * momentum.
   */
  virtual pair<Energy,Energy> generate() const =0;
  //@}

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

private:

  /**
   * Describe an abstract class without persistent data.
   */
  static AbstractClassDescription<PtGenerator> initPtGenerator;

  /**
   * Private and non-existent assignment operator.
   */
   PtGenerator & operator=(const PtGenerator &);

};


/**
 * This template specialization informs ThePEG about the
 * base class of PtGenerator.
 */
template <>
struct BaseClassTrait<PtGenerator,1>: public ClassTraitsType {
  /** Typedef of the base class of PtGenerator. */
  typedef HandlerBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * PtGenerator class.
 */
template <>
struct ClassTraits<PtGenerator>: public ClassTraitsBase<PtGenerator> {
  /** Return the class name. */
  static string className() { return "ThePEG::PtGenerator"; }
};


}

#include "PtGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PtGenerator.tcc"
#endif

#endif /* ThePEG_PtGenerator_H */
