// -*- C++ -*-
#ifndef ThePEG_ReweightBase_H
#define ThePEG_ReweightBase_H
// This is the declaration of the ReweightBase class.

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
// #include "ReweightBase.fh"
// #include "ReweightBase.xh"

namespace ThePEG {

/**
 * The ReweightBase class is the base class of all objects
 * representing external biases to matrix elements. These can be used
 * to enhance certain matrix elements or certain phase space
 * regions. They can be used in to ways, either to completely change
 * the matrix element (re-weight), in which case the total cross
 * section will be affected or, when using weighted events in an
 * EventHandler, to pre-weight certain events but leaving the cross
 * section unchanged
 *
 * There is only one virtual function which must be overridden in
 * derived classes: weight().
 *
 * @see \ref ReweightBaseInterfaces "The interfaces"
 * defined for ReweightBase.
 * @see MEBase
 * @see EventHandler
 * @see SubProcessHandler
 */
class ReweightBase: public HandlerBase, public LastXCombInfo<> {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline ReweightBase();

  /**
   * Copy-constructor.
   */
  inline ReweightBase(const ReweightBase &);

  /**
   * Destructor.
   */
  virtual ~ReweightBase();
  //@}

public:

  /**
   * Return the wieght for the kinematical configuation
   * previously provided by the last call to setKinematics().
   */
  virtual double weight() const = 0;

  /**
   * Set the kinematics for the corresponding sub-process to be use in
   * the reweighting.
   */
  void setKinematics(Energy2 shat, tcPDPair in, const cPDVector & out,
		     const Lorentz5Momentum & pina,
		     const Lorentz5Momentum & pinb,
		     const vector<Lorentz5Momentum> & pout);

  /**
   * Set the types and momenta of the incoming and outgoing partons to
   * be used in the reweighting.
   */
  void setKinematics(tPPair in, const PVector & out);

  /**
   * Set the types and momenta of the incoming and outgoing partons to
   * be used in the reweighting.
   */
  inline void setKinematics(const SubProcess & sub);

  /**
   * Set the types and momenta of the incoming and outgoing partons to
   * be used in the reweighting.
   */
  void setXComb(tXCombPtr);

  /**
   * This method does nothing in this base class. Derived classes may
   * override it to setup derived quantities obtained from the
   * information provided by a call to setKinematics(...). (Allways
   * called from the setKinematics() methods.)
   */
  inline virtual void setKinematics();

  /**
   * Clear the information previously provided by a call to
   * setKinematics().
   */
  virtual void clearKinematics();

public:

  /**
   * Return the last set invariant mass squared.
   */
  inline Energy2 sHat() const;

  /**
   * Return the types of the last set incoming partons.
   */
  inline const cPDPair & inData() const;

  /**
   * Return the types of the last set outgoing partons.
   */
  inline const cPDVector & outData() const;

  /**
   * Return the momentum of the last set first incoming parton.
   */
  inline const Lorentz5Momentum & inMomentumA() const;

  /**
   * Return the momentum of the last set incoming second parton.
   */
  inline const Lorentz5Momentum & inMomentumB() const;

  /**
   * Return the momenta of the last set outgoing partons.
   */
  inline const vector<Lorentz5Momentum> & outMomentum() const;

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

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving and
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
   * The last set invariant mass squared.
   */
  Energy2 theLastSHat;

  /**
   * The types of the last set incoming partons.
   */
  cPDPair theLastInData;

  /**
   * The types of the last set outgoing partons.
   */
  cPDVector theLastOutData;

  /**
   * The momentum of the last set first incoming parton.
   */
  Lorentz5Momentum theLastInMomentumA;

  /**
   * The momentum of the last set second incoming parton.
   */
  Lorentz5Momentum theLastInMomentumB;

  /**
   * The momenta of the last set outgoing partons.
   */
  vector<Lorentz5Momentum> theLastOutMomentum;

private:

  /**
   * Describe an abstract base class with persistent data.
   */
  static AbstractClassDescription<ReweightBase> initReweightBase;

  /**
   *  Private and non-existent assignment operator.
   */
  ReweightBase & operator=(const ReweightBase &);

};

}


namespace ThePEG {

/**
 * This template specialization informs ThePEG about the base class of
 * ReweightBase.
 */
template <>
struct BaseClassTrait<ReweightBase,1>: public ClassTraitsType {
  /** Typedef of the base class of ReweightBase. */
  typedef HandlerBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * ReweightBase class.
 */
template <>
struct ClassTraits<ReweightBase>: public ClassTraitsBase<ReweightBase> {
  /** Return the class name. */
  static string className() { return "ThePEG::ReweightBase"; }
};

}

#include "ReweightBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ReweightBase.tcc"
#endif

#endif /* ThePEG_ReweightBase_H */
