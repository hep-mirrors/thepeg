// -*- C++ -*-
#ifndef ThePEG_AlphaEMBase_H
#define ThePEG_AlphaEMBase_H
// This is the declaration of the AlphaEMBase class.

#include "ThePEG/Interface/Interfaced.h"
#include "StandardModelBase.fh"
// #include "AlphaEMBase.fh"
// #include "AlphaEMBase.xh"

namespace ThePEG {

/**
 * AlphaEMBase an abstract base class used by the StandardModelBase
 * class to implement the electro-magnetic coupling. Concrete
 * sub-classes must implement the value(Energy2, const
 * StandardModelBase &) function.
 *
 *
 * @see StandardModelBase.
 * 
 */
class AlphaEMBase: public Interfaced {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline AlphaEMBase();

  /**
   * Copy-constructor.
   */
  inline AlphaEMBase(const AlphaEMBase &);

  /**
   * Destructor.
   */
  virtual ~AlphaEMBase();
  //@}

public:

  /**
   * The \f$\alpha_{EM}\f$. Return the value of the coupling at a
   * given \a scale using the given standard model object, \a sm. This
   * is the only virtual function to be implemented by base classes.
   */
  virtual double value(Energy2 scale, const StandardModelBase & sm) const = 0;

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

private:

  /**
   * Describe an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<AlphaEMBase> initAlphaEMBase;

  /**
   *  Private and non-existent assignment operator.
   */
  AlphaEMBase & operator=(const AlphaEMBase &);

};

/** This template specialization informs ThePEG about the base classes
 *  of AlphaEMBase. */
template <>
struct BaseClassTrait<AlphaEMBase,1>: public ClassTraitsType {
  /** Typedef of the first base class of AlphaEMBase. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  AlphaEMBase class. */
template <>
struct ClassTraits<AlphaEMBase>: public ClassTraitsBase<AlphaEMBase> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::AlphaEMBase"; }
};

}

#include "AlphaEMBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "AlphaEMBase.tcc"
#endif

#endif /* ThePEG_AlphaEMBase_H */
