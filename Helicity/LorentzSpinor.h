// -*- C++ -*-
#ifndef ThePEG_LorentzSpinor_H
#define ThePEG_LorentzSpinor_H
//
// This is the declaration of the <!id>LorentzSpinor<!!id> class.
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

namespace ThePEG{
namespace Helicity{

class LorentzSpinor {

public:

  // default zero constructor
  LorentzSpinor();

  // constructor with complex numbers
  LorentzSpinor(Complex,Complex,
		Complex,Complex);

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
	
  // return the barred spinor
  LorentzSpinorBar bar();	
	
  // the equals operator
  inline LorentzSpinor & operator = (const LorentzSpinor &);
	
  // boost 
  inline LorentzSpinor  boost(double,double,double) const;
  inline LorentzSpinor  boost(const Hep3Vector &) const;

private:

  Complex _spin[4];

};
}
}

#include "LorentzSpinor.icc"

#endif

