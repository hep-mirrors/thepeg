// -*- C++ -*-
#ifndef ThePEG_MECuts_H
#define ThePEG_MECuts_H
//
// This is the declaration of the <!id>MECuts<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>MECuts<!!id> class is used to make cuts on generated phase
// space points for the hard interaction. A <!id>MECuts<!!id> object
// is selected for each matrix element. The
// <!class>CollisionHandler<!!class> has a default <!id>MECuts<!!id>
// object, which may be overridden by the selected
// <!class>SubProcessHandler<!!class> object, which in turn may be
// overridden by the selected <!class>MEBase<!!class> object.
//
// The <!id>MECuts<!!id> is used in two different
// ways. Individual handlers may use the specific member functions
// which specify cuts on individual variables. In addition the
// <!id>cut<!!id> member functions are always called by the
// <!class>CollisionHandler<!!class> to automatically check that all
// cuts are passed. It is possible to derive new classes from the
// <!id>MECuts<!!id> class, in which case the virtual
// <!id>newcut<!!id> methods may be overridden and will be called from
// the <!id>cut<!!id> methods.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>
// <a href="http:MEBase.html">MEBase.h</a>
// <a href="http:Collision.html">Collision.h</a>
// <a href="http:SubProcess.html">.h</a>
// 

#include "ThePEG/Interface/Interfaced.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.fh"
#include "ThePEG/Utilities/Triplet.h"
#include "ThePEG/PDT/StandardMatchers.h"
// #include "MECuts.fh"
// #include "MECuts.xh"

namespace ThePEG {

class MECuts: public Interfaced {

public:

  MECuts();
  MECuts(const MECuts &);
  virtual ~MECuts();
  // Standard ctors and dtor

public:

  void cut(const SubProcess &) const ThePEG_THROW_SPEC((Veto));
  // This method is called by the CollisionHandler with the primary
  // SubProcess provided in its cm frame.

public:

  inline Energy mHatMin() const;
  inline Energy mHatMax() const;
  inline Energy sHatMin() const;
  inline Energy sHatMax() const;
  // The minimum and maximum values of the invariant mass (squared) of
  // the hard sub-process.

  inline Energy pTHatMin() const;
  inline Energy pTHatMax() const;
  // The minimum and maximum values of the transverse momentum of the
  // outgoing particles in the hard sub-process.

  inline Energy pTHatSingularMin() const;
  inline Energy singularMassMax() const;
  // Additional cut on the transverse momenta of the hard sub-process
  // for s-channel hard sub-processes for outgoing particles of mass
  // less than singularMassMax().

  inline double cTHMin() const;
  inline double cTHMax() const;
  // The minimum and maximum value of cosine of the scattering angle
  // in the restframe of a hard 2->2 scattering.

  inline Energy2 tHatMin() const;
  inline Energy2 tHatMax() const;
  // The minimum and maximum value of that of a hard 2->2 scattering.

  inline Energy2 uHatMin() const;
  inline Energy2 uHatMax() const;
  // The minimum and maximum value of uhat of a hard 2->2 scattering.

  inline Energy2 scaleMin() const;
  inline Energy2 scaleMax() const;
  // The minimum and maximum value of the scale in a hard scattering
  // as defined by the Handlers which performed the hard scattering.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual void newcut(const SubProcess &) const ThePEG_THROW_SPEC((Veto));
  // This method is called by the corresponding cut method with the
  // primary SubProcess provided in its cm frame. This bas-class
  // method does nothing.

protected:

  virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  virtual IBPtr clone() const;
  // Standard clone method.

private:

  Energy theMHatMin;
  Energy theMHatMax;
  // The minimum and maximum values of the invariant mass of
  // the hard sub-process.

  Energy thePTHatMin;
  Energy thePTHatMax;
  // The minimum and maximum values of the transverse momentum of the
  // outgoing particles in the hard sub-process.

  Energy thePTHatSingularMin;
  Energy theSingularMassMax;
  // Additional cut on the transverse momenta of the hard sub-process
  // for s-channel hard sub-processes for outgoing particles of mass
  // less than theSingularMassMax.

  double theCTHMin;
  double theCTHMax;
  // The minimum and maximum value of cosine of the scattering angle
  // in the restframe of a hard 2->2 scattering.

  Energy2 theTHatMin;
  Energy2 theTHatMax;
  // The minimum and maximum value of that of a hard 2->2 scattering.

  Energy2 theUHatMin;
  Energy2 theUHatMax;
  // The minimum and maximum value of uhat of a hard 2->2 scattering.

  Energy2 theScaleMin;
  Energy2 theScaleMax;
  // The minimum and maximum value of the scale in a hard scattering
  // as defined by the Handlers which performed the hard scattering.

private:

  static ClassDescription<MECuts> initMECuts;

  MECuts & operator=(const MECuts &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<MECuts,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<MECuts>:
    public ClassTraitsBase<MECuts> {
  static string className() { return "ThePEG::MECuts"; }
};

}

#include "MECuts.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MECuts.tcc"
#endif

#endif /* ThePEG_MECuts_H */
