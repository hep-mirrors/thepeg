// -*- C++ -*-
#ifndef ThePEG_KinematicalCuts_H
#define ThePEG_KinematicalCuts_H
//
// This is the declaration of the <!id>KinematicalCuts<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>KinematicalCuts<!!id> class is used to make cuts on
// generated events. A <!id>KinematicalCuts<!!id> object is selected
// for each generated collision. The <!class>CollisionHandler<!!class>
// has a default <!id>KinematicalCuts<!!id> object, which may be
// overridden by the selected <!class>SubProcessHandler<!!class>
// object, which in turn may be overridden by the selected
// <!class>PartonXSecFn<!!class> object.
//
// The <!id>KinematicalCuts<!!id> is used in two different
// ways. Individual handlers may use the specific member functions
// which specify cuts on individual variables. In addition the
// <!id>cut<!!id> member functions are always called by the
// <!class>CollisionHandler<!!class> to automatically check that all
// cuts are passed. It is possible to derive new classes from the
// <!id>KinematicalCuts<!!id> class, in which case the virtual
// <!id>newcut<!!id> methods may be overridden and will be called from
// the <!id>cut<!!id> methods.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>
// <a href="http:PartonXSecFn.html">PartonXSecFn.h</a>
// <a href="http:Collision.html">Collision.h</a>
// <a href="http:SubProcess.html">.h</a>
// 

#include "ThePEG/Interface/Interfaced.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.fh"
#include "ThePEG/Utilities/Triplet.h"
#include "ThePEG/PDT/StandardMatchers.h"
// #include "KinematicalCuts.fh"
// #include "KinematicalCuts.xh"

namespace ThePEG {

class KinematicalCuts: public Interfaced {

public:

  KinematicalCuts();
  KinematicalCuts(const KinematicalCuts &);
  virtual ~KinematicalCuts();
  // Standard ctors and dtor

public:

  void cut(const SubProcess &) const ThePEG_THROW_SPEC((Veto));
  // This method is called by the CollisionHandler with the primary
  // SubProcess provided in its cm frame.

  void cut(const Collision &, const LorentzRotation &) const
    ThePEG_THROW_SPEC((Veto));
  // This method is called by the CollisionHandler with the primary
  // collision after its first step provided in int cm frame. The
  // LorentzRotation provided should give the transformation to the
  // laboratory frame.

public:

  inline Energy mHatMin() const;
  inline Energy mHatMax() const;
  inline Energy sHatMin() const;
  inline Energy sHatMax() const;
  // The minimum and maximum values of the invariant mass (squared) of
  // the hard sub-process.

  inline bool mHat(Energy mhat) const;
  // Returns true if mHatMin() <= mhat < mHatMax().

  inline bool sHat(Energy2 shat) const;
  // Returns true if sHatMin() <= shat < sHatMax().

  inline Energy pTHatMin() const;
  inline Energy pTHatMax() const;
  // The minimum and maximum values of the transverse momentum of the
  // outgoing particles in the hard sub-process.

  inline bool pTHat(Energy pt) const;
  // Returns true if pTHatMin() <= pt < pTHatMax().

  inline Energy pTHatSingularMin() const;
  inline Energy singularMassMax() const;
  // Additional cut on the transverse momenta of the hard sub-process
  // for s-channel hard sub-processes for outgoing particles of mass
  // less than singularMassMax().

  inline double yStarMin() const;
  inline double yStarMax() const;
  // The minimum and maximum value of the rapidity of the hard
  // scattering sub-system.

  inline bool yStar(double y) const;
  // Returns true if yStarMin() <= y <= yStarMax().

  inline double maxYMin() const;
  inline double maxYMax() const;
  // The minimum and maximum value of the maximum rapidity of the
  // outgoing particles in the hard scattering.

  inline bool maxY(double y) const;
  // Returns true if maxYMin() <= y <= maxYMax().

  inline double minYMin() const;
  inline double minYMax() const;
  // The minimum and maximum value of the minimum rapidity of the
  // outgoing particles in the hard scattering.

  inline bool minY(double y) const;
  // Returns true if minYMin() <= y <= minYMax().

  inline double maxEtaMin() const;
  inline double maxEtaMax() const;
  // The minimum and maximum value of the maximum pseudo rapidity of
  // the outgoing particles in the hard scattering.

  inline bool maxEta(double eta) const;
  // Returns true if maxEtaMin() <= eta <= maxEtaMax().

  inline double minEtaMin() const;
  inline double minEtaMax() const;
  // The minimum and maximum value of the minimum pseudo rapidity of
  // the outgoing particles in the hard scattering.

  inline bool minEta(double eta) const;
  // Returns true if minEtaMin() <= eta <= minEtaMax().

  inline double maxCTMin() const;
  inline double maxCTMax() const;
  // The minimum and maximum value of the maximum cos(theta) of
  // the outgoing particles in the hard scattering.

  inline bool maxCT(double ct) const;
  // Returns true if maxCTMin() <= ct <= maxCTMax().

  inline double minCTMin() const;
  inline double minCTMax() const;
  // The minimum and maximum value of the minimum cos(theta) of
  // the outgoing particles in the hard scattering.

  inline bool minCT(double ct) const;
  // Returns true if minCTMin() <= ct <= minCTMax().

  inline double x1Min() const;
  inline double x1Max() const;
  // The minimum and maximum value of the Bjorken-x of the particle
  // comin into the hard scattering along the positive z-axis.

  inline bool x1(double x) const;
  // Returns true if x1Min() < x <= x1Max().

  inline double x2Min() const;
  inline double x2Max() const;
  // The minimum and maximum value of the Bjorken-x of the particle
  // comin into the hard scattering along the negative z-axis.

  inline bool x2(double x) const;
  // Returns true if x2Min() < x <= x2Max().

  inline double xFMin() const;
  inline double xFMax() const;
  // The minimum and maximum value of the Feynman-x of the hard
  // scattering.

  inline bool xF(double x) const;
  // Returns true if xFMin() <= x <= xFMax().

  inline double cTHMin() const;
  inline double cTHMax() const;
  // The minimum and maximum value of cosine of the scattering angle
  // in the restframe of a hard 2->2 scattering.

  inline bool cTH(double cth) const;
  // Returns true if cTHMin() <= cth <= cTHMax().

  inline Energy2 tHatMin() const;
  inline Energy2 tHatMax() const;
  // The minimum and maximum value of |that| of a hard 2->2 scattering.

  inline bool tHat(Energy2 that) const;
  // Returns true if tHatMin() <= th < tHatMax().

  inline Energy2 uHatMin() const;
  inline Energy2 uHatMax() const;
  // The minimum and maximum value of |uhat| of a hard 2->2 scattering.

  inline bool uHat(Energy2 uhat) const;
  // Returns true if uHatMin() <= uh < uHatMax().

  inline Energy2 scaleMin() const;
  inline Energy2 scaleMax() const;
  // The minimum and maximum value of the scale in a hard scattering
  // as defined by the Handlers which performed the hard scattering.

  inline bool scale(Energy2 sc) const;
  // Returns true if scaleMin() <= sc < scaleMax().

  inline Energy DISLepton1EnergyMin() const;
  inline Energy DISLepton1EnergyMax() const;
  // For lepton-particle scattering, the minimum and maximum
  // energy of the scattered lepton.

  inline double DISLepton1AngleMin() const;
  inline double DISLepton1AngleMax() const;
  // For lepton-particle scattering, the minimum and maximum
  // scattering angle of the lepton.

  inline Energy2 DISQ21Min() const;
  inline Energy2 DISQ21Max() const;
  // For lepton-particle scattering, the minimum and maximum
  // Q^2 as calculated from the scattered lepton.

  inline Energy DISLepton2EnergyMin() const;
  inline Energy DISLepton2EnergyMax() const;
  // For particle-lepton scattering, the minimum and maximum
  // energy of the scattered lepton.

  inline double DISLepton2AngleMin() const;
  inline double DISLepton2AngleMax() const;
  // For particle-lepton scattering, the minimum and maximum
  // scattering angle of the lepton.

  inline Energy2 DISQ22Min() const;
  inline Energy2 DISQ22Max() const;
  // For particle-lepton scattering, the minimum and maximum
  // Q^2 as calculated from the scattered lepton.

  inline Energy2 DISW2Min() const;
  inline Energy2 DISW2Max() const;
  // For lepton-particle, particle-lepton and lepton-lepton
  // scattering, the minimum and maximum value of the invariant mass
  // squared of the outgoing particles when removing the scattered
  // lepton(s).

  // These functions return true if the given variable passes the
  // cuts.

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

  virtual void newcut(const Collision &, const LorentzRotation &) const
    ThePEG_THROW_SPEC((Veto));
  // This method is called by the corresponding cut method with the
  // primary collision after its first step provided in int cm
  // frame. The LorentzRotation provided should give the
  // transformation to the laboratory frame. This bas-class method
  // does nothing.

protected:

  virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  virtual IBPtr clone() const;
  virtual IBPtr fullclone() const;
  // Standard clone method.

private:

  bool isLepton(const Particle & p) const;
  // Return true if p is a lepton.

  double maxYMinMax() const;
  double minYMaxMin() const;
  double maxEtaMinMax() const;
  double minEtaMaxMin() const;
  double maxCTMinMax() const;
  double minCTMaxMin() const;
  // Utility functions for the interface.

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

  double theYStarMin;
  double theYStarMax;
  // The minimum and maximum value of the rapidity of the hard
  // scattering sub-system.

  double theMaxYMin;
  double theMaxYMax;
  // The minimum and maximum value of the maximum rapidity of the
  // outgoing particles in the hard scattering.

  double theMinYMin;
  double theMinYMax;
  // The minimum and maximum value of the minimum rapidity of the
  // outgoing particles in the hard scattering.

  double theMaxEtaMin;
  double theMaxEtaMax;
  // The minimum and maximum value of the maximum pseudo rapidity of
  // the outgoing particles in the hard scattering.

  double theMinEtaMin;
  double theMinEtaMax;
  // The minimum and maximum value of the minimum pseudo rapidity of
  // the outgoing particles in the hard scattering.

  double theMaxCTMin;
  double theMaxCTMax;
  // The minimum and maximum value of the maximum cos(theta) of
  // the outgoing particles in the hard scattering.

  double theMinCTMin;
  double theMinCTMax;
  // The minimum and maximum value of the minimum cos(theta) of
  // the outgoing particles in the hard scattering.

  double theX1Min;
  double theX1Max;
  // The minimum and maximum value of the Bjorken-x of the particle
  // comin into the hard scattering along the positive z-axis.

  double theX2Min;
  double theX2Max;
  // The minimum and maximum value of the Bjorken-x of the particle
  // comin into the hard scattering along the negative z-axis.

  double theXFMin;
  double theXFMax;
  // The minimum and maximum value of the Feynman-x of the hard
  // scattering.

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

  bool useLeptoCuts;
  // Internal flag to indicate if we should use cuts on scattered leptons.

  Energy theDISLepton1EnergyMin;
  Energy theDISLepton1EnergyMax;
  // For lepton-particle scattering, the minimum and maximum
  // energy of the scattered lepton.

  double theDISLepton1AngleMin;
  double theDISLepton1AngleMax;
  // For lepton-particle scattering, the minimum and maximum
  // scattering angle of the lepton.

  Energy2 theDISQ21Min;
  Energy2 theDISQ21Max;
  // For lepton-particle scattering, the minimum and maximum
  // Q^2 as calculated from the scattered lepton.

  Energy theDISLepton2EnergyMin;
  Energy theDISLepton2EnergyMax;
  // For particle-lepton scattering, the minimum and maximum
  // energy of the scattered lepton.

  double theDISLepton2AngleMin;
  double theDISLepton2AngleMax;
  // For particle-lepton scattering, the minimum and maximum
  // scattering angle of the lepton.

  Energy2 theDISQ22Min;
  Energy2 theDISQ22Max;
  // For particle-lepton scattering, the minimum and maximum
  // Q^2 as calculated from the scattered lepton.

  Energy2 theDISW2Min;
  Energy2 theDISW2Max;
  // For lepton-particle, particle-lepton and lepton-lepton
  // scattering, the minimum and maximum value of the invariant mass
  // squared of the outgoing particles when removing the scattered
  // lepton(s).

  Ptr<MatchLepton>::pointer theLeptonMatcher;
  // A matcher object used to identify leptons.

private:

  static ClassDescription<KinematicalCuts> initKinematicalCuts;

  KinematicalCuts & operator=(const KinematicalCuts &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<KinematicalCuts,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<KinematicalCuts>:
    public ClassTraitsBase<KinematicalCuts> {
  static string className() {
    return "/ThePEG/KinematicalCuts";
  }
};

}

#include "KinematicalCuts.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "KinematicalCuts.tcc"
#endif

#endif /* ThePEG_KinematicalCuts_H */
