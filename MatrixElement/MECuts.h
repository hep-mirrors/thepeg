// -*- C++ -*-
#ifndef ThePEG_MECuts_H
#define ThePEG_MECuts_H
// This is the declaration of the MECuts class.

#include "ThePEG/Interface/Interfaced.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.fh"
#include "ThePEG/Utilities/Triplet.h"
#include "ThePEG/PDT/StandardMatchers.h"
// #include "MECuts.fh"
// #include "MECuts.xh"

namespace ThePEG {

/**
 * The MECuts class is (currently not at all) used to make cuts on
 * generated phase space points for the hard interaction. A MECuts
 * object is selected for each matrix element. The CollisionHandler
 * has a default MECuts object, which may be overridden by the
 * selected SubProcessHandler object, which in turn may be overridden
 * by the selected MEBase object.
 *
 * The MECuts is used in two different ways. Individual handlers may
 * use the specific member functions which specify cuts on individual
 * variables. In addition the cut() member functions are always called
 * by the CollisionHandler to automatically check that all cuts are
 * passed. It is possible to derive new classes from the MECuts class,
 * in which case the virtual newcut() methods may be overridden and
 * will be called from the cut() methods.
 *
 *
 * @see CollisionHandler
 * @see SubProcessHandler
 * @see MEBase
 * @see Collision
 * @see SubProcess
 * 
 */
class MECuts: public Interfaced {

public:

  /**
   * Standard ctors and dtor
   */
  MECuts();
  /**
   * Standard ctors and dtor
   */
  MECuts(const MECuts &);
  /**
   * Standard ctors and dtor
   */
  virtual ~MECuts();

public:

  /**
   * This method is called by the CollisionHandler with the primary
   * SubProcess provided in its cm frame.
   */
  void cut(const SubProcess &) const ThePEG_THROW_SPEC((Veto));

public:

  /**
   * The minimum and maximum values of the invariant mass (squared) of
   * the hard sub-process.
   */
  inline Energy mHatMin() const;
  /**
   * The minimum and maximum values of the invariant mass (squared) of
   * the hard sub-process.
   */
  inline Energy mHatMax() const;
  /**
   * The minimum and maximum values of the invariant mass (squared) of
   * the hard sub-process.
   */
  inline Energy sHatMin() const;
  /**
   * The minimum and maximum values of the invariant mass (squared) of
   * the hard sub-process.
   */
  inline Energy sHatMax() const;

  /**
   * The minimum and maximum values of the transverse momentum of the
   * outgoing particles in the hard sub-process.
   */
  inline Energy pTHatMin() const;
  /**
   * The minimum and maximum values of the transverse momentum of the
   * outgoing particles in the hard sub-process.
   */
  inline Energy pTHatMax() const;

  /**
   * Additional cut on the transverse momenta of the hard sub-process
   * for s-channel hard sub-processes for outgoing particles of mass
   * less than singularMassMax().
   */
  inline Energy pTHatSingularMin() const;
  /**
   * Additional cut on the transverse momenta of the hard sub-process
   * for s-channel hard sub-processes for outgoing particles of mass
   * less than singularMassMax().
   */
  inline Energy singularMassMax() const;

  /**
   * The minimum and maximum value of cosine of the scattering angle
   * in the restframe of a hard 2->2 scattering.
   */
  inline double cTHMin() const;
  /**
   * The minimum and maximum value of cosine of the scattering angle
   * in the restframe of a hard 2->2 scattering.
   */
  inline double cTHMax() const;

  /**
   * The minimum and maximum value of that of a hard 2->2 scattering.
   */
  inline Energy2 tHatMin() const;
  /**
   * The minimum and maximum value of that of a hard 2->2 scattering.
   */
  inline Energy2 tHatMax() const;

  /**
   * The minimum and maximum value of uhat of a hard 2->2 scattering.
   */
  inline Energy2 uHatMin() const;
  /**
   * The minimum and maximum value of uhat of a hard 2->2 scattering.
   */
  inline Energy2 uHatMax() const;

  /**
   * The minimum and maximum value of the scale in a hard scattering
   * as defined by the Handlers which performed the hard scattering.
   */
  inline Energy2 scaleMin() const;
  /**
   * The minimum and maximum value of the scale in a hard scattering
   * as defined by the Handlers which performed the hard scattering.
   */
  inline Energy2 scaleMax() const;

public:

  /**
   * Standard functions for writing and reading from persistent streams.
   */
  void persistentOutput(PersistentOStream &) const;
  /**
   * Standard functions for writing and reading from persistent streams.
   */
  void persistentInput(PersistentIStream &, int);

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

protected:

  /**
   * This method is called by the corresponding cut method with the
   * primary SubProcess provided in its cm frame. This bas-class
   * method does nothing.
   */
  virtual void newcut(const SubProcess &) const ThePEG_THROW_SPEC((Veto));

protected:

  /**
   * Standard Interfaced virtual functions.
   */
  virtual void doupdate() throw(UpdateException);
  /**
   * Standard Interfaced virtual functions.
   */
  inline virtual void doinit() throw(InitException);
  /**
   * Standard Interfaced virtual functions.
   */
  inline virtual void dofinish();

  /**
   * Standard clone method.
   */
  virtual IBPtr clone() const;

private:

  /**
   * The minimum and maximum values of the invariant mass of
   * the hard sub-process.
   */
  Energy theMHatMin;
  /**
   * The minimum and maximum values of the invariant mass of
   * the hard sub-process.
   */
  Energy theMHatMax;

  /**
   * The minimum and maximum values of the transverse momentum of the
   * outgoing particles in the hard sub-process.
   */
  Energy thePTHatMin;
  /**
   * The minimum and maximum values of the transverse momentum of the
   * outgoing particles in the hard sub-process.
   */
  Energy thePTHatMax;

  /**
   * Additional cut on the transverse momenta of the hard sub-process
   * for s-channel hard sub-processes for outgoing particles of mass
   * less than theSingularMassMax.
   */
  Energy thePTHatSingularMin;
  /**
   * Additional cut on the transverse momenta of the hard sub-process
   * for s-channel hard sub-processes for outgoing particles of mass
   * less than theSingularMassMax.
   */
  Energy theSingularMassMax;

  /**
   * The minimum and maximum value of cosine of the scattering angle
   * in the restframe of a hard 2->2 scattering.
   */
  double theCTHMin;
  /**
   * The minimum and maximum value of cosine of the scattering angle
   * in the restframe of a hard 2->2 scattering.
   */
  double theCTHMax;

  /**
   * The minimum and maximum value of that of a hard 2->2 scattering.
   */
  Energy2 theTHatMin;
  /**
   * The minimum and maximum value of that of a hard 2->2 scattering.
   */
  Energy2 theTHatMax;

  /**
   * The minimum and maximum value of uhat of a hard 2->2 scattering.
   */
  Energy2 theUHatMin;
  /**
   * The minimum and maximum value of uhat of a hard 2->2 scattering.
   */
  Energy2 theUHatMax;

  /**
   * The minimum and maximum value of the scale in a hard scattering
   * as defined by the Handlers which performed the hard scattering.
   */
  Energy2 theScaleMin;
  /**
   * The minimum and maximum value of the scale in a hard scattering
   * as defined by the Handlers which performed the hard scattering.
   */
  Energy2 theScaleMax;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<MECuts> initMECuts;

  /**
   *  Private and non-existent assignment operator.
   */
  MECuts & operator=(const MECuts &);

};

/**
 * This template specialization informs ThePEG about the base class of
 * MECuts.
 */
template <>
struct BaseClassTrait<MECuts,1>: public ClassTraitsType {
  /** Typedef of the base class of MECuts. */
  typedef Interfaced NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * MECuts class.
 */
template <>
struct ClassTraits<MECuts>:
  /** Return the class name. */
    public ClassTraitsBase<MECuts> {
  static string className() { return "ThePEG::MECuts"; }
};

}

#include "MECuts.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MECuts.tcc"
#endif

#endif /* ThePEG_MECuts_H */
