// -*- C++ -*-
//
// ReweightMinPT.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_ReweightMinPT_H
#define ThePEG_ReweightMinPT_H
// This is the declaration of the ReweightMinPT class.

#include "ThePEG/MatrixElement/ReweightBase.h"
// #include "ReweightMinPT.fh"
// #include "ReweightMinPT.xh"

namespace ThePEG {

/**
 * The ReweightMinPT class reweights matrix elements with the minimum
 * of the transverse momenta of the outgoing partons to some power.
 *
 * @see ReweightBase
 * 
 */
class ReweightMinPT: public ReweightBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline ReweightMinPT();

  /**
   * Copy-constructor.
   */
  inline ReweightMinPT(const ReweightMinPT &);

  /**
   * Destructor.
   */
  virtual ~ReweightMinPT();
  //@}

public:

  /**
   * Return the wieght for the kinematical configuation provided by
   * the assigned XComb object (in the LastXCombInfo base class).
   */
  virtual double weight() const;

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
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr fullclone() const;
  //@}

protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish();

  /**
   * Rebind pointer to other Interfaced objects. Called in the setup phase
   * after all objects used in an EventGenerator has been cloned so that
   * the pointers will refer to the cloned objects afterwards.
   * @param trans a TranslationMap relating the original objects to
   * their respective clones.
   * @throws RebindException if no cloned object was found for a given pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in
   * this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * The weight is the minimum pt/scale to a \a power.
   */
  double power;

  /**
   * The weight is the minimum pt/\a scale to a power.
   */
  Energy scale;

private:

  /**
   * Describe a concrete base class with persistent data.
   */
  static ClassDescription<ReweightMinPT> initReweightMinPT;

  /**
   *  Private and non-existent assignment operator.
   */
  ReweightMinPT & operator=(const ReweightMinPT &);

};

}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of ReweightMinPT. */
template <>
struct BaseClassTrait<ReweightMinPT,1>: public ClassTraitsType {
  /** Typedef of the first base class of ReweightMinPT. */
  typedef ReweightBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the ReweightMinPT class and the shared object where it is defined. */
template <>
struct ClassTraits<ReweightMinPT>: public ClassTraitsBase<ReweightMinPT> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::ReweightMinPT"; }
  /** Return the name of the shared library be loaded to get
   *  access to the ReweightMinPT class and every other class it uses
   *  (except the base class). */
  static string library() { return "ReweightMinPT.so"; }
};

/** @endcond */

}

#include "ReweightMinPT.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ReweightMinPT.tcc"
#endif

#endif /* ThePEG_ReweightMinPT_H */
