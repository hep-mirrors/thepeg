// -*- C++ -*-
#ifndef THEPEG_MultiCutBase_H
#define THEPEG_MultiCutBase_H
//
// This is the declaration of the MultiCutBase class.
//

#include "ThePEG/Interface/Interfaced.h"
#include "MultiCutBase.fh"
#include "Cuts.fh"

namespace ThePEG {

/**
 * This class corresponds to a kinematical cut to be made on a set of
 * outgoing particles from a hard sub-process.
 *
 * There are three virtual functions to be overridden by concrete
 * sub-classes. minS() and maxS() should return the minimum and
 * maximum invariant mass of of a set of particle types. In addition
 * the passCut() function should return true if a set of particle
 * with a given types and given momenta will pass the cuts.
 *
 * @see \ref MultiCutBaseInterfaces "The interfaces"
 * defined for MultiCutBase.
 */
class MultiCutBase: public Interfaced {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline MultiCutBase();

  /**
   * The copy constructor.
   */
  inline MultiCutBase(const MultiCutBase &);

  /**
   * The destructor.
   */
  virtual ~MultiCutBase();
  //@}

public:

  /** @name Virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * Return the minimum allowed value of the squared invariant mass of
   * a set of outgoing partons of the given types. Typically used to
   * cut off the tails of the mass of a resonance for efficiency.
   */
  virtual Energy2 minS(const tcPDVector & pv) const = 0;

  /**
   * Return the maximum allowed value of the squared invariant mass of
   * a set of outgoing partons of the given types. Typically used to
   * cut off the tails of the mass of a resonance for efficiency.
   */
  virtual Energy2 maxS(const tcPDVector & pv) const = 0;

  /**
   * Return true if a set of outgoing particles with typea \a ptype
   * and corresponding momenta \a p passes the cuts.
   */
  virtual bool passCuts(tcCutsPtr parent, const tcPDVector & ptype,
			const vector<LorentzMomentum> & p) const;

  /**
   * Return true if the given vector of particles passes the cuts.
   */
  bool passCuts(tcCutsPtr parent, const tcPVector & p) const;
  //@}

public:

  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

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
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  inline virtual void doinitrun();

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
   * @throws RebindException if no cloned object was found for a given
   * pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this
   * object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<MultiCutBase> initMultiCutBase;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  MultiCutBase & operator=(const MultiCutBase &);

};

}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of MultiCutBase. */
template <>
struct BaseClassTrait<MultiCutBase,1> {
  /** Typedef of the first base class of MultiCutBase. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the MultiCutBase class and the shared object where it is defined. */
template <>
struct ClassTraits<MultiCutBase>
  : public ClassTraitsBase<MultiCutBase> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::MultiCutBase"; }
};

/** @endcond */

}

#include "MultiCutBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MultiCutBase.tcc"
#endif

#endif /* THEPEG_MultiCutBase_H */
