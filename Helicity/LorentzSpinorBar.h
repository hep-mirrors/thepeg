// -*- C++ -*-
#ifndef ThePEG_LorentzSpinorBar_H
#define ThePEG_LorentzSpinorBar_H
//
// This is the declaration of the <!id>LorentzSpinorBar<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
//
// Author: Peter Richardson
//

#include "ThePEG/Config/Complex.h"
#include "ThePEG/CLHEPWrap/ThreeVector.h"
#include "LorentzSpinor.fh"
#include "LorentzSpinorBar.fh"

namespace ThePEG {
namespace Helicity {

class LorentzSpinorBar {

public:

  // default zero constructor
  LorentzSpinorBar();

  // constructor with complex numbers
  LorentzSpinorBar(Complex,Complex, Complex,Complex);

  // subscript operator to return spinor components
  inline Complex operator[](int) const;
  inline Complex operator()(int) const;

  // Set components by index.
  inline Complex & operator () (int);
  inline Complex & operator [] (int);

  // Get components
  inline Complex s1() const;
  inline Complex s2() const;
  inline Complex s3() const;
  inline Complex s4() const;

  // Set components
  inline void setS1(Complex);
  inline void setS2(Complex);
  inline void setS3(Complex);
  inline void setS4(Complex);

  // return the unbarred spinor
  LorentzSpinor bar();

  // Assignment.
  inline LorentzSpinorBar & operator = (const LorentzSpinorBar &);

  // boost
  inline LorentzSpinorBar boost(double,double,double) const;
  inline LorentzSpinorBar boost(const Hep3Vector &) const;

private:

  Complex _spin[4];

};

}
}

#include "LorentzSpinorBar.icc"

#endif
