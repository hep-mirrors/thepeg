// -*- C++ -*-
#ifndef ThePEG_GRVBase_H
#define ThePEG_GRVBase_H
//
// This is the declaration of the <!id>GRVBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>GRVBase<!!id> inherits from PDFBase and is used as a base
// class for all GRV parton densities.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">PDFBase.h</a>.
// 

#include "ThePEG/PDF/PDFBase.h"
// #include "GRVBase.fh"
// #include "GRVBase.xh"

namespace ThePEG {

class GRVBase: public PDFBase {

public:

  GRVBase();
  GRVBase(const GRVBase &);
  virtual ~GRVBase();
  // Standard ctors and dtor

public:

  virtual bool canHandleParticle(tcPDPtr particle) const;
  // Return true if this PDF can handle the extraction of parton from the
  // given particle ie. if the particle is a proton or neutron.

  virtual cPDVector partons(tcPDPtr p) const;
  // Return the parton types which are described by these parton
  // densities.

  virtual double xfl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale) const;
  // Return the value of the density of parton at the given a scale
  // and log fractional momentum l (the optional virtuality of the
  // incoming particle is not used).

  virtual double xfvl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale) const;
  // Return the valaens partof the density of parton at the given a
  // scale and log fractional momentum l (the optional virtuality of
  // the incoming particle is not used).

public:

  inline double S() const;
  inline double S2() const;
  inline double S3() const;
  inline double rootS() const;
  inline double x() const;
  inline double lx() const;
  inline double eps() const;
  inline double rootx() const;
  // Return the S, S^2, S^2, sqrt(S), x, log(1/x), 1-x, sqrt(x) of the
  // last selected momentum fraction x and
  // S=log(log(Q2/mu2)/log(Q2/lambda2)).

protected:

  virtual void setup(double l, Energy2 scale) const = 0;
  void setup(double l, Energy2 scale, Energy mu2, Energy2 lam2) const;
  // Set the l=log(1/x) and S=log(log(Q2/mu2)/log(Q2/lam2)) to be
  // used in the current evaluation of the parton density.

  double valens(double N, double ak, double bk,
		double a, double b, double c, double d) const;
  // The form of the valens density functions.

  double lightsea(double al, double be, double ak, double bk, double a,
		  double b, double c, double d, double e, double es) const;
  // The form of the light sea and gluon density
  // functions.

  double heavysea(double sth, double al, double be, double ak, double ag,
		  double b, double d, double e, double es) const;
  // The form of the heavy sea density functions.

  virtual double uv() const = 0;
  virtual double dv() const = 0;
  virtual double del() const = 0;
  virtual double udb() const = 0;
  virtual double sb() const = 0;
  virtual double cb() const = 0;
  virtual double bb() const = 0;
  virtual double gl() const = 0;
  // Return the value of the u-valens, d-valens, difference between
  // the u and d sea, the average u and d sea, s, c and b sea and
  // gluon densities respectively for the values previously given by
  // setup().

  inline double fuv() const;
  inline double fdv() const;
  inline double fdel() const;
  inline double fudb() const;
  inline double fsb() const;
  inline double fcb() const;
  inline double fbb() const;
  inline double fgl() const;
  // fq() returns the saved values from the q() functions if
  // present. Otherwise q() is called, saved and returned.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  virtual void rebind(const TranslationMap & trans) throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  mutable double theLx;
  mutable double thex;
  mutable double theEps;
  mutable double theRootx;
  mutable Energy2 Q2;
  mutable Energy2 theLam2;
  mutable Energy2 theMu2;
  mutable double theS;
  mutable double theS2;
  mutable double theS3;
  mutable double theRootS;
  // The S, S^2, S^2, sqrt(S), x, log(1/x), 1-x, sqrt(x) of the
  // last selected ,omentum fraction x and
  // S=log(log(Q2/mu2)/log(Q2/lambda2)).

  mutable double uvSave;
  mutable double dvSave;
  mutable double delSave;
  mutable double udbSave;
  mutable double sbSave;
  mutable double cbSave;
  mutable double bbSave;
  mutable double glSave;
  // Saved values from the different functions.

private:

  static AbstractNoPIOClassDescription<GRVBase> initGRVBase;

  GRVBase & operator=(const GRVBase &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<GRVBase,1> {
  typedef PDFBase NthBase;
};

template <>
struct ClassTraits<GRVBase>: public ClassTraitsBase<GRVBase> {
  static string className() { return "/ThePEG/GRVBase"; }
  static string library() { return "GRVBase.so"; }
};

}

#include "GRVBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "GRVBase.tcc"
#endif

#endif /* ThePEG_GRVBase_H */
