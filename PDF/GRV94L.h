// -*- C++ -*-
#ifndef ThePEG_GRV94L_H
#define ThePEG_GRV94L_H
//
// This is the declaration of the <!id>GRV94L<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>GRV94L<!!id> iherits from PDFBase via the GRVBase class and
// implements the GRV94L parton densities for (anti) protons.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PDFBase.html">PDFBase.h</a>,
// <a href="http:GRVBase.html">GRVBase.h</a>.
// 

#include "ThePEG/PDF/GRVBase.h"
// #include "GRV94L.fh"
// #include "GRV94L.xh"

namespace ThePEG {

class GRV94L: public GRVBase {

public:

  inline GRV94L();
  inline GRV94L(const GRV94L &);
  virtual ~GRV94L();
  // Standard ctors and dtor

  inline Energy2 mu2() const;
  inline Energy2 lam2() const;
  // Return the cutoff scale and the square of Lambda_QCD used.

protected:

  virtual void setup(double l, Energy2 scale) const;
  // Setup the log(1/x) and scale Q2 to be used in the following call
  // to uv, dv, ...

  virtual double uv() const;
  virtual double dv() const;
  virtual double del() const;
  virtual double udb() const;
  virtual double sb() const;
  virtual double cb() const;
  virtual double bb() const;
  virtual double gl() const;
  // Return the value of the u-valens, d-valens, difference between
  // the u and d sea, the average u and d sea, s, c and b sea and
  // gluon densities respectively for the values previously given by
  // setup().

public:

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  static NoPIOClassDescription<GRV94L> initGRV94L;

  GRV94L & operator=(const GRV94L &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<GRV94L,1> {
  typedef GRVBase NthBase;
};

template <>
struct ClassTraits<GRV94L>: public ClassTraitsBase<GRV94L> {
  static string className() { return "/ThePEG/GRV94L"; }
  static string library() { return "GRV94L.so"; }
};

}

#include "GRV94L.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "GRV94L.tcc"
#endif

#endif /* ThePEG_GRV94L_H */
