// -*- C++ -*-
#ifndef ThePEG_StandardModelBase_H
#define ThePEG_StandardModelBase_H
//
// This is the declaration of the <!id>StandardModelBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>StandardModelBase<!!id> is used to handle standard model
// parameters in an <!class>EventGenerator<!!class>. It uses
// <!class>AlphaEMBase<!!class>, <!class>AlphaSBase<!!class> and
// <!class>CKMBase<!!class> to help with the implementation of the
// electro-magnetic and QCD couplings and the flavour mixing matrix.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:EventGenerator.html">EventGenerator.h</a>,
// <a href="http:AlphaEMBase.html">AlphaEMBase.h</a>,
// <a href="http:AlphaSBase.html">AlphaSBase.h</a>,
// <a href="http:CKMBase.html">CKMBase.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "AlphaEMBase.h"
#include "CKMBase.h"
#include "AlphaSBase.h"
// #include "StandardModelBase.fh"
// #include "StandardModelBase.xh"

namespace ThePEG {

class StandardModelBase: public Interfaced {

  typedef Ptr<AlphaEMBase>::pointer AEMPtr;
  typedef Ptr<AlphaSBase>::pointer ASPtr;
  typedef Ptr<CKMBase>::pointer CKMPtr;
  typedef Ptr<AlphaEMBase>::transient_pointer tAEMPtr;
  typedef Ptr<AlphaSBase>::transient_pointer tASPtr;
  typedef Ptr<CKMBase>::transient_pointer tCKMPtr;

public:

  StandardModelBase();
  StandardModelBase(const StandardModelBase &);
  virtual ~StandardModelBase();
  // Standard ctors and dtor

  inline virtual void doupdate() throw(UpdateException);
  virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

public:
  // General parameters

  unsigned int families() const;
  // Return the number of families assumed in the standard model.

public:
  // Electro-Weak parameters

  inline double alphaEM() const;
  inline double alphaEM(Energy2 scale) const;
  // Constant and running \alpha_{EM}

  inline tAEMPtr alphaEMPtr() const;
  // Return a pointer to the object handling \alpha_{EM}

  inline double sin2ThetaW() const;
  // \sin^2\theta_W

  inline double enu() const;
  inline double ee() const;
  inline double eu() const;
  inline double ed() const;
  // The coupling between fundamental fermions and the photon.

  inline double vnu() const;
  inline double ve() const;
  inline double vu() const;
  inline double vd() const;
  inline double anu() const;
  inline double ae() const;
  inline double au() const;
  inline double ad() const;
  // The vector and axial couplings between fundamental fermions and Z^0.

  double CKM(unsigned int uFamily, unsigned int dFamily) const;
  double CKM(const ParticleData & uType,
		    const ParticleData & dType) const;
  // Return the square of the elements of the Cabibbo-Kobayashi-Maskawa
  // Matrix.

public:
  // QCD parameters:

  inline unsigned int Nc() const;
  // Return the number of colours.

  inline unsigned int Nf(Energy2 scale) const;
  // Return the number of avtive quark flavours.

  inline double alphaS() const;
  // Return the strong coupling constant.

  inline double alphaS(Energy2 scale) const;
  // Return the running strong coupling for a given scale

  inline tASPtr alphaSPtr() const;
  // Return a pointer to the object handling \alpha_S.

  inline Energy LambdaQCD(unsigned int nflav) const;
  inline Energy LambdaQCD(Energy2 scale) const;
  // Return the \Lambda_{QCD} for the number of active flavours
  // (corresponding to the given scale).

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual IBPtr clone() const;
  virtual IBPtr fullclone() const;
  // Standard clone methods

  inline virtual void
  rebind(const TranslationMap & trans) throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  unsigned int theFamilies;
  // The number of families.

  double theAlphaEM;
  // \alpha_{EM}

  AEMPtr theRunningAlphaEM;
  // Pointer to an object capable of calculating the running \alpha_{EM}.

  double theSin2ThetaW;
  // \sin^2\theta_W

  double theEnu, theEe, theEu, theEd;
  // The coupling between fundamental fermions and the photon.

  double theVnu, theVe, theVu, theVd;
  // The vector couplings between fundamental fermions and Z^0.

  double theAnu, theAe, theAu, theAd;
  // The axial couplings between fundamental fermions and Z^0.

  long recalculateEW;
  // If true the electro-weak couplings are derived from \theta_W in
  // the initialization.

  CKMPtr theCKM;
  // A pointer to an object representing the Cabibbo-Kobayashi-Maskawa
  // matrix.

  mutable vector< vector<double> > theCKM2Matrix;
  // The matrix of squared CKM elements set from theCKM at initialization.

  unsigned int theNc;
  // The number of colours;

  double theAlphaS;
  // The fixed strong coupling.

  ASPtr theRunningAlphaS;
  // Pointer to an object capable of calculating the running \alpha_{S}.


private:

  static ClassDescription<StandardModelBase> initStandardModelBase;

  StandardModelBase & operator=(const StandardModelBase &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<StandardModelBase,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<StandardModelBase>:
    public ClassTraitsBase<StandardModelBase> {
  static string className() { return "/ThePEG/StandardModelBase"; }
};

}

#include "StandardModelBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StandardModelBase.tcc"
#endif

#endif /* ThePEG_StandardModelBase_H */
