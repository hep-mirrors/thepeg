// -*- C++ -*-
#ifndef ThePEG_ME2to2Base_H
#define ThePEG_ME2to2Base_H
//
// This is the declaration of the <!id>ME2to2Base<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>ME2to2Base<!!id> class can be used for any matrix element
// class implementing <i>2->2</i> processes. It extends the
// <!class>MEBase<!!class> base class by implementing the virtual
// <!id>scale()<!!id> method to return the assumed scale of a given
// process according to several options. It also caches some useful
// characteristics of the chosen phase space point, such as
// <!id>tHat()<!!id>, <!id>uHat()<!!id> and the masses of the external
// partons.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:MEBase.html">MEBase.h</a>.
// 

#include "ThePEG/MatrixElement/MEBase.h"
#include "ThePEG/MatrixElement/Tree2toNDiagram.h"
#include "ThePEG/Interface/Switch.fh"
// #include "ME2to2Base.fh"
// #include "ME2to2Base.xh"

namespace ThePEG {

class ME2to2Base: public MEBase {

public:

  inline ME2to2Base();
  inline ME2to2Base(const ME2to2Base &);
  virtual ~ME2to2Base();
  // Standard ctors and dtor.

public:

  virtual int nDim() const;
  // The number of internal degreed of freedom used in the matrix
  // element.

  virtual bool generateKinematics(const double * r);
  // Generate internal degrees of freedom given 'nDim()' uniform
  // random numbers in the interval ]0,1[. To help the phase space
  // generator, the 'dSigHatDR()' should be a smooth function of these
  // numbers, although this is not strictly necessary. Return
  // false if the chosen points failed the kinematical cuts.

  virtual double getCosTheta(double cthmin, double cthmax, const double * r);
  // Used internally by generateKinematics, after calculating the
  // limits on cos(theta).

  virtual CrossSection dSigHatDR() const;
  // Return the matrix element for the kinematical configuation
  // previously provided by the last call to setKinematics(). Uses
  // me().

  virtual Energy2 scale() const;
  // Return the scale associated with the last set phase space point.

  inline int scaleChoice() const;
  // Give the option corresponding to the way the scale of an
  // interaction is calculated.

  virtual void setKinematics();
  // Set the typed and momenta of the incoming and outgoing partons to
  // be used in subsequent calls to me() and colourGeometries()
  // according to the associated XComb object.

public:

  inline Energy2 tHat() const;
  // Return the t-hat of the last set phase space point.

  inline Energy2 uHat() const;
  // Return the u-hat of the last set phase space point.

  inline double phi() const;
  // Peturn the azimuth angle of the last set phase space point.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

protected:

  static Switch<ME2to2Base,int> & interfaceScaleChoice();

private:

  int theScaleChoice;
  // The option indication how to calculate the scale of an interaction.

  Energy2 theLastTHat;
  // The t-hat of the last set phase space point.

  Energy2 theLastUHat;
  // The u-hat of the last set phase space point.

  double theLastPhi;
  // The azimuth angle of the last set phase space point.


private:

  static AbstractClassDescription<ME2to2Base> initME2to2Base;
  // Describe an abstract base class with persistent data.

  ME2to2Base & operator=(const ME2to2Base &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of ME2to2Base.
template <>
struct BaseClassTrait<ME2to2Base,1> {
  typedef MEBase NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ME2to2Base>: public ClassTraitsBase<ME2to2Base> {
  static string className() { return "/ThePEG/ME2to2Base"; }
  // Return the class name.
};

}

#include "ME2to2Base.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ME2to2Base.tcc"
#endif

#endif /* ThePEG_ME2to2Base_H */
