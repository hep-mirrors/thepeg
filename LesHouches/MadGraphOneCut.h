// -*- C++ -*-
#ifndef THEPEG_MadGraphOneCut_H
#define THEPEG_MadGraphOneCut_H
//
// This is the declaration of the MadGraphOneCut class.
//

#include "ThePEG/Cuts/OneCutBase.h"

namespace ThePEG {

/**
 * Objects of the MadGraphOneCut class can be created automatically by
 * the MadGraphReader class when scanning event files for information
 * about cuts. It is also possible to create objects by hand and use
 * it as any other OneCutBase object.
 *
 * @see \ref MadGraphOneCutInterfaces "The interfaces"
 * defined for MadGraphOneCut.
 */
class MadGraphOneCut: public OneCutBase {

public:

  /**
   * Enumerate the different kinds of cuts made by MadGraph.
   */
  enum CutType {
    PT,  /**< The minimum transverse momentum of a particle. */
    ETA, /**< The maximum (absolute value of) pseudo-rapidity of a particle. */
    XPT  /**< The minimum transverse momentum of the particle with
	      largest transverse momentum. */
  };

  /**
   * Enumerate the types of particles the cut is made on.
   */
  enum PType {
    JET, /**< The cut applies only to coloured particles. */
    LEP, /**< The cut applies only to leptons. */
    PHO, /**< The cut applies only to photons. */
    BOT  /**< The cut applies only to bottom quarks. */
  };

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline MadGraphOneCut();

  /**
   * The constructor used by the MadGraphReader.
   * @param t is the type of the cut.
   * @param p is the type of particles the cut is applied to.
   * @param c is the value of the cut (in units of GeV where applicable).
   */
  inline MadGraphOneCut(CutType t, PType p, double c);

  /**
   * The copy constructor.
   */
  inline MadGraphOneCut(const MadGraphOneCut &);

  /**
   * The destructor.
   */
  virtual ~MadGraphOneCut();
  //@}

public:

  /** @name Virtual functions mandated by the base class. */
  //@{
  /**
   * Return the minimum allowed value of the transverse momentum of an
   * outgoing parton.
   */
  virtual Energy minKT(tcPDPtr p) const;

  /**
   * Return the minimum allowed pseudo-rapidity of an outgoing parton
   * of the given type. The pseudo-rapidity is measured in the lab
   * system.
   */
  virtual double minEta(tcPDPtr p) const;

  /**
   * Return the maximum allowed pseudo-rapidity of an outgoing parton
   * of the given type. The pseudo-rapidity is measured in the lab
   * system.
   */
  virtual double maxEta(tcPDPtr p) const;

  /**
   * Return the minimum allowed value of the transverse momentum of
   * the outgoing parton with the lagrest transverse momentum. This
   * version simply returns minKt().
   */
  virtual Energy minMaxKT(tcPDPtr p) const;

  /**
   * Return true if a particle with type \a ptype and momentum \a p
   * passes the cuts. The \a parent contains information about the
   * kinematics of the hard sub-process.
   */
  virtual bool passCuts(tcCutsPtr parent,
			tcPDPtr ptype, LorentzMomentum p) const;
  //@}

protected:

  /**
   * Returns true if cut should be applied to a particle of type \a p.
   */
  bool checkType(tcPDPtr p) const;

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
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
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
   * The type of this cut.
   */
  CutType cutType;

  /**
   * The type of particles this cut applies to.
   */
  PType particleType;

  /**
   * The value of the cut to be applied.
   */
  double theCut;

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<MadGraphOneCut> initMadGraphOneCut;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  MadGraphOneCut & operator=(const MadGraphOneCut &);

};

}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of MadGraphOneCut. */
template <>
struct BaseClassTrait<MadGraphOneCut,1> {
  /** Typedef of the first base class of MadGraphOneCut. */
  typedef OneCutBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the MadGraphOneCut class and the shared object where it is defined. */
template <>
struct ClassTraits<MadGraphOneCut>
  : public ClassTraitsBase<MadGraphOneCut> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::MadGraphOneCut"; }
  /** Return the name(s) of the shared library (or libraries) be loaded to get
   *  access to the MadGraphOneCut class and any other class on which it depends
   *  (except the base class). */
  static string library() { return "MadGraphReader.so"; }
};

/** @endcond */

}

#include "MadGraphOneCut.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MadGraphOneCut.tcc"
#endif

#endif /* THEPEG_MadGraphOneCut_H */
