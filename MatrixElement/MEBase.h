// -*- C++ -*-
#ifndef ThePEG_MEBase_H
#define ThePEG_MEBase_H
//
// This is the declaration of the <!id>MEBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>MEBase<!!id> class is the base class of all objects
// representing hard matrix elements in ThePEG. There are three
// methods which must be overridden by a concrete subclass:<BR>
//
// <!id>includedDiagrams(tcPDPair)<!!id> should return a vector of
// <!class>DiagramBase<!!class>s describing the diagrams used for this
// matrix element for the given pair of incoming parton types. These
// <!class>DiagramBase<!!class>s are used to identify the incoming and
// outgoing partons which can be handled to the process generation
// scheme, and is also used to cnstruct a corresponding
// <!class>SubProcess<!!class> object.
//
// <!id>scale()<!!id> should return the scale associated with the
// phase space point set with the last call to
// <!id>setKinematics(...)<!!id> or
// <!id>generateKinematics(...)<!!id>.
//
// <!id>double me() const<!!id> should return the the matrix element
// squared using the the type and momentum of the incoming and
// outgoing partons, previously set by the
// <!id>setKinematics(...)<!!id> or
// <!id>generateKinematics(...)<!!id> member functions, accessible through
// the methods <!id>meMomenta()<!!id> and <!id>mePartonData()<!!id>
// inherited from <!class>LastXCombInfo<!!class>, and/or from
// information stored by sub classes. The returned value should be
// dimensionless suitable scaled by the total invariant mass squared
// (accessible through the <!id>sHat()<!!id> member function). Any
// user of this method must make sure that the
// <!id>setKinematics(...)<!!id> member function has been
// appropriately called before.
//
// <!id>colourGeometries()<!!id> should return a <!id>Selector<!!id>
// with the possible <!class>ColourLines<!!class>' weighted by
// their relative probabilities given the information given by the
// last call to <!id>setKinematics(...)<!!id> or
// <!id>generateKinematics(...)<!!id>.
//
// There are other virtula functions which may be overridden as listed
// below.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:DiagramBase.html">DiagramBase.h</a>,
// <a href="http:ColourLines.html">ColourLines.h</a>.
// 

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/MatrixElement/DiagramBase.h"
#include "ThePEG/MatrixElement/ColourLines.h"
#include "ThePEG/MatrixElement/Amplitude.h"
#include "ThePEG/Handlers/LastXCombInfo.h"

// #include "MEBase.fh"
// #include "MEBase.xh"

namespace ThePEG {

class MEBase: public HandlerBase, public LastXCombInfo<> {

public:

  typedef vector<DiagPtr> DiagramVector;
  typedef DiagramVector::size_type DiagramIndex;
  typedef vector<ReweightPtr> ReweightVector;

public:

  MEBase();
  MEBase(const MEBase &);
  virtual ~MEBase();
  // Standard ctors and dtor.

public:

  virtual unsigned int orderInAlphaS() const = 0;
  virtual unsigned int orderInAlphaEW() const = 0;
  // Return the order in respective couplings in which this matrix
  // element is given.

  virtual double me2() const = 0;
  // Return the matrix element for the kinematical configuation
  // previously provided by the last call to setKinematics(), suitably
  // scaled by sHat() to give a dimension-less number.

  virtual Energy2 scale() const = 0;
  // Return the scale associated with the last set phase space point.

  void setKinematics(tPPair in, const PVector & out);
  // Set the typed and momenta of the incoming and outgoing partons to
  // be used in subsequent calls to me() and colourGeometries().

  virtual void setKinematics();
  // Set the typed and momenta of the incoming and outgoing partons to
  // be used in subsequent calls to me() and colourGeometries()
  // according to the associated XComb object. If the fun ction is
  // overridden in a sub class the new function must call the base
  // class one first.

  virtual int nDim() const;
  // The number of internal degreed of freedom used in the matrix
  // element. This default version returns 0;

  virtual bool generateKinematics(const double * r) = 0;
  // Generate internal degrees of freedom given 'nDim()' uniform
  // random numbers in the interval ]0,1[. To help the phase space
  // generator, the 'dSigHatDR' should be a smooth function of these
  // numbers, although this is not strictly necessary. THe return
  // value should be true of the generation succeeded.

  virtual CrossSection dSigHatDR() const = 0;
  // Return the matrix element squared differential in the variables
  // given by the last call to 'generateKinematics()'.

  virtual void generateSubCollision(SubProcess &);
  // Comlete a SubProcess object using the internal degrees of freedom
  // generated in the last 'generateKinematics()' (and possible other
  // degrees of freedom which was intergated over in 'dSigHatDR()'. This
  // default version does nothing. Will be made purely virtual in the
  // future.

  virtual void clearKinematics();
  // Clear the information previously provided by a call to
  // setKinematics(...).

  virtual void getDiagrams() const = 0;
  // Add all possible diagrams with the add() function.

  inline const DiagramVector & diagrams() const;
  // Return all possible diagrams.

  virtual Selector<const ColourLines *>
  colourGeometries(tcDiagPtr diag) const = 0;
  // Return a Selector with possible colour geometries for the selected
  // diagram weighted by their relative probabilities.

  virtual const ColourLines &
  selectColourGeometry(tcDiagPtr diag) const;
  // The default version returns a colour geometry selected among the
  // ones returned from colourGeometries().

  inline virtual Selector<DiagramIndex> diagrams(const DiagramVector &) const;
  // With the information previously supplied with the
  // setKinematics(...) method, a derived class may optionally
  // override this method to weight the given diagrams with their
  // (although certainly not physical) relative probabilities.

  virtual DiagramIndex diagram(const DiagramVector &) const;
  // Default version uses diagrams(...) to select a diagram
  // according to the weights. This is the only method used that
  // should be outside of MEBase.

  double reWeight() const;
  double preWeight() const;
  // With the information previously supplied with the
  // setKinematics(...) methods, return the comined effects of the
  // (p)reweighters.

  void addReweighter(tReweightPtr rw);
  void addPreweighter(tReweightPtr rw);
  // Add objects to the list of re- and pre-weighters.

  inline Ptr<Amplitude>::pointer amplitude() const;
  // Return the eventual amplitude associated with this matrix element.

public:

  inline Energy2 sHat() const;
  // Return the last set invariant mass squared.

  inline double preweight() const;
  // Return the factor with which this matrix element was last
  // pre-weighted.

  virtual void setXComb(tXCombPtr);
  // Set the XComb object to be used in the next call to
  // generateKinematics() and dSigHatDR().

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline void add(DiagPtr) const;
  // To be used by sub classes in the getDiagrams() method to add
  // included diagrams.

  vector<Lorentz5Momentum> & meMomenta();
  using LastXCombInfo<>::meMomenta;

  inline double jacobian() const;
  inline void jacobian(double);
  // Get/set the last jacobian obtained when generating the kinematics
  // for the call to dSigHatDR.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  mutable DiagramVector theDiagrams;
  // The diagrams included for this matrix element.

  Energy2 theLastSHat;
  // The last set invariant mass squared.

  ReweightVector reweights;
  ReweightVector preweights;
  // The pre- and re-weight objects modifying this matrix element.

  mutable double lastPreweight;
  // The factor with which this matrix element was last pre-weighted.

  Ptr<Amplitude>::pointer theAmplitude;
  // The eventual amplitude associated with this matrix element.

  double theLastJacobian;
  // Save the last jacobian obtained when generating the kinematics for
  // the call to dSigHatDR.

private:

  static AbstractClassDescription<MEBase> initMEBase;
  // Describe an abstract base class with persistent data.

  MEBase & operator=(const MEBase &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of MEBase.
template <>
struct BaseClassTrait<MEBase,1> {
  typedef HandlerBase NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<MEBase>: public ClassTraitsBase<MEBase> {
  static string className() { return "/ThePEG/MEBase"; }
  // Return the class name.
};

}

#include "MEBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEBase.tcc"
#endif

#endif /* ThePEG_MEBase_H */
