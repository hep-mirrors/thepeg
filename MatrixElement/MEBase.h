// -*- C++ -*-
#ifndef ThePEG_MEBase_H
#define ThePEG_MEBase_H
// This is the declaration of the MEBase class.

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/MatrixElement/DiagramBase.h"
#include "ThePEG/MatrixElement/ColourLines.h"
#include "ThePEG/MatrixElement/Amplitude.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
#include "ThePEG/Handlers/StandardXComb.fh"

#include "MEBase.fh"
// #include "MEBase.xh"

namespace ThePEG {

/**
 * The MEBase class is the base class of all objects
 * representing hard matrix elements in ThePEG. There are three
 * methods which must be overridden by a concrete subclass:<BR>
 *
 * includedDiagrams(tcPDPair) should return a vector of DiagramBase
 * objects describing the diagrams used for this matrix element for
 * the given pair of incoming parton types. These DiagramBases are
 * used to identify the incoming and outgoing partons which can be
 * handled by the process generation scheme, and is also used to
 * cnstruct a corresponding SubProcess object.
 *
 * scale() should return the scale associated with the phase space
 * point set with the last call to setKinematics(...) or
 * generateKinematics(...).
 *
 * me() should return the the matrix element squared using the the
 * type and momentum of the incoming and outgoing partons, previously
 * set by the setKinematics(...) or generateKinematics(...) member
 * functions, accessible through the methods meMomenta() and
 * mePartonData() inherited from LastXCombInfo, and/or from
 * information stored by sub classes. The returned value should be
 * dimensionless suitable scaled by the total invariant mass squared
 * (accessible through the sHat() member function). Any user of this
 * method must make sure that the setKinematics(...) member function
 * has been appropriately called before.
 *
 * colourGeometries() should return a Selector with the possible
 * ColourLines objects weighted by their relative probabilities given
 * the information set by the last call to setKinematics(...) or
 * generateKinematics(...).
 *
 * There are other virtula functions which may be overridden as listed
 * below.
 *
 * @see \ref MEBaseInterfaces "The interfaces"
 * defined for MEBase.
 * @see DiagramBase
 * @see ColourLines
 * 
 */
class MEBase: public HandlerBase, public LastXCombInfo<StandardXComb> {

public:

  /** A vector of pointers to DiagramBase objects. */
  typedef vector<DiagPtr> DiagramVector;
  /** The size_type used in the DiagramVector. */
  typedef DiagramVector::size_type DiagramIndex;
  /** A vector of pointers to ReweightBase objects. */
  typedef vector<ReweightPtr> ReweightVector;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  MEBase();

  /**
   * Copy-constructor.
   */
  MEBase(const MEBase &);

  /**
   * Destructor.
   */
  virtual ~MEBase();
  //@}

public:

  /** @name Virtual functions to be overridden by sub-classes.. */
  //@{
  /**
   * Return the order in \f$\alpha_S\f$ in which this matrix element
   * is given.
   */
  virtual unsigned int orderInAlphaS() const = 0;

  /**
   * Return the order in \f$\alpha_{EM}\f$ in which this matrix
   * element is given. Returns 0.
   */
  virtual unsigned int orderInAlphaEW() const = 0;

  /**
   * Return the matrix element for the kinematical configuation
   * previously provided by the last call to setKinematics(), suitably
   * scaled by sHat() to give a dimension-less number.
   */
  virtual double me2() const = 0;

  /**
   * Return the scale associated with the phase space point provided
   * by the last call to setKinematics().
   */
  virtual Energy2 scale() const = 0;

  /**
   * Return the value of \f$\alpha_S\f$ associated with the phase
   * space point provided by the last call to setKinematics(). This
   * versions returns SM().alphaS(scale()).
   */
  virtual double alphaS() const;

  /**
   * Return the value of \f$\alpha_EM\f$ associated with the phase
   * space point provided by the last call to setKinematics(). This
   * versions returns SM().alphaEM(scale()).
   */
  virtual double alphaEM() const;

  /**
   * Set the typed and momenta of the incoming and outgoing partons to
   * be used in subsequent calls to me() and colourGeometries().
   */
  void setKinematics(tPPair in, const PVector & out);

  /**
   * Set the typed and momenta of the incoming and outgoing partons to
   * be used in subsequent calls to me() and colourGeometries()
   * according to the associated XComb object. If the function is
   * overridden in a sub class the new function must call the base
   * class one first.
   */
  virtual void setKinematics();

  /**
   * construct the spin information for the interaction
   */
  virtual void constructVertex(tSubProPtr sub);

  /**
   * The number of internal degreed of freedom used in the matrix
   * element. This default version returns 0;
   */
  virtual int nDim() const;

  /**
   * Generate internal degrees of freedom given nDim() uniform random
   * numbers in the interval ]0,1[. To help the phase space generator,
   * the 'dSigHatDR' should be a smooth function of these numbers,
   * although this is not strictly necessary. The return value should
   * be true of the generation succeeded. If so the generated momenta
   * should be stored in the meMomenta() vector.
   */
  virtual bool generateKinematics(const double * r) = 0;

  /**
   * Return the matrix element squared differential in the variables
   * given by the last call to generateKinematics().
   */
  virtual CrossSection dSigHatDR() const = 0;

  /**
   * Comlete a SubProcess object using the internal degrees of freedom
   * generated in the last generateKinematics() (and possible other
   * degrees of freedom which was intergated over in dSigHatDR(). This
   * default version does nothing. Will be made purely virtual in the
   * future.
   */
  virtual void generateSubCollision(SubProcess &);

  /**
   * Clear the information previously provided by a call to
   * setKinematics(...).
   */
  virtual void clearKinematics();

  /**
   * Add all possible diagrams with the add() function.
   */
  virtual void getDiagrams() const = 0;

  /**
   * Return all possible diagrams.
   */
  inline const DiagramVector & diagrams() const;

  /**
   * Return a Selector with possible colour geometries for the selected
   * diagram weighted by their relative probabilities.
   */
  virtual Selector<const ColourLines *>
  colourGeometries(tcDiagPtr diag) const = 0;

  /**
   * Select a ColpurLines geometry. The default version returns a
   * colour geometry selected among the ones returned from
   * colourGeometries(tcDiagPtr).
   */
  virtual const ColourLines &
  selectColourGeometry(tcDiagPtr diag) const;

  /**
   * With the information previously supplied with the
   * setKinematics(...) method, a derived class may optionally
   * override this method to weight the given diagrams with their
   * (although certainly not physical) relative probabilities.
   */
  inline virtual Selector<DiagramIndex> diagrams(const DiagramVector &) const;

  /**
   * Select a diagram. Default version uses diagrams(const
   * DiagramVector &) to select a diagram according to the
   * weights. This is the only method used that should be outside of
   * MEBase.
   */
  virtual DiagramIndex diagram(const DiagramVector &) const;

  /**
   * With the information previously supplied with the
   * setKinematics(...) methods, return the combined effects of the
   * reweighters.
   */
  double reWeight() const;

  /**
   * With the information previously supplied with the
   * setKinematics(...) methods, return the comined effects of the
   * peweighters.
   */
  double preWeight() const;

  /**
   * Add objects to the list of reweighters.
   */
  void addReweighter(tReweightPtr rw);

  /**
   * Add objects to the list of preweighters.
   */
  void addPreweighter(tReweightPtr rw);

  /**
   * Return the amplitude associated with this matrix element. This
   * function is allowed to return the null pointer if the amplitude
   * is not available.
   */
  inline Ptr<Amplitude>::pointer amplitude() const;
  //@}

public:

  /** @name Acces information about the last generated phase space point. */
  //@{
  /**
   * Return the last set invariant mass squared.
   */
  inline Energy2 sHat() const;

  /**
   * Return the factor with which this matrix element was last
   * pre-weighted.
   */
  inline double preweight() const;

  /**
   * Set the XComb object to be used in the next call to
   * generateKinematics() and dSigHatDR().
   */
  virtual void setXComb(tStdXCombPtr);

  /**
   * Retrieve information obtained in the calculation of the cross
   * section to be used later when selecting diagrams and colour flow.
   */
  const DVector & meInfo() const;

  /**
   * Save information obtained in the calculation of the cross
   * section to be used later when selecting diagrams and colour flow.
   */
  void meInfo(const DVector & info) const;

  /**
   * If this matrix element is to be used together with others for
   * CKKW reweighting and veto, this should give the multiplicity of
   * outgoing particles in the highest multiplicity matrix element in
   * the group.
   */
  inline int maxMultCKKW() const;

  /**
   * If this matrix element is to be used together with others for
   * CKKW reweighting and veto, this should give the multiplicity of
   * outgoing particles in the lowest multiplicity matrix element in
   * the group.
   */
  inline int minMultCKKW() const;
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
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();

protected:

  /**
   * To be used by sub classes in the getDiagrams() method to add
   * included diagrams.
   */
  inline void add(DiagPtr) const;

  /**
   * Access the momenta set by the last call to generateKinematics().
   */
  vector<Lorentz5Momentum> & meMomenta();
  using LastXCombInfo<StandardXComb>::meMomenta;

  /**
   * Get the last jacobian obtained when generating the kinematics
   * for the call to dSigHatDR.
   */
  inline double jacobian() const;

  /**
   * Set the last jacobian obtained when generating the kinematics for
   * the call to dSigHatDR.
   */
  inline void jacobian(double);

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
  virtual void rebind(const TranslationMap & trans)
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
   * The diagrams included for this matrix element.
   */
  mutable DiagramVector theDiagrams;

  /**
   * The last set invariant mass squared.
   */
  Energy2 theLastSHat;

  /**
   * The reweight objects modifying this matrix element.
   */
  ReweightVector reweights;

  /**
   * The preweight objects modifying this matrix element.
   */
  ReweightVector preweights;

  /**
   * The factor with which this matrix element was last pre-weighted.
   */
  mutable double lastPreweight;

  /**
   * The amplitude associated with this matrix element.
   */
  Ptr<Amplitude>::pointer theAmplitude;

  /**
   * Save the last jacobian obtained when generating the kinematics for
   * the call to dSigHatDR.
   */
  double theLastJacobian;

  /**
   * If this matrix element is to be used together with others for
   * CKKW reweighting and veto, this should give the multiplicity of
   * outgoing particles in the highest multiplicity matrix element in
   * the group.
   */
  int theMaxMultCKKW;

  /**
   * If this matrix element is to be used together with others for
   * CKKW reweighting and veto, this should give the multiplicity of
   * outgoing particles in the lowest multiplicity matrix element in
   * the group.
   */
  int theMinMultCKKW;

private:

  /**
   * Describe an abstract base class with persistent data.
   */
  static AbstractClassDescription<MEBase> initMEBase;

  /**
   *  Private and non-existent assignment operator.
   */
  MEBase & operator=(const MEBase &);

};

}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the base class of
 * MEBase.
 */
template <>
struct BaseClassTrait<MEBase,1>: public ClassTraitsType {
  /** Typedef of the base class of MEBase. */
  typedef HandlerBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * MEBase class.
 */
template <>
struct ClassTraits<MEBase>: public ClassTraitsBase<MEBase> {
  /** Return the class name. */
  static string className() { return "ThePEG::MEBase"; }
};

/** @endcond */

}

#include "MEBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEBase.tcc"
#endif

#endif /* ThePEG_MEBase_H */
