// -*- C++ -*-
#ifndef ThePEG_LorentzSpinorBar_H
#define ThePEG_LorentzSpinorBar_H
//
// This is the declaration of the <!id>LorentzSpinorBar<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//  The <!id>LorentzSpinorBar<!!id> class implements the storage of a
//  barred Lorentz Spinor. The design is based on that of the
//  <!id>LorentzSpinor<!!id> class and the details of the implemented
//  are discussed in more detail in the header file for that class.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="LorentzSpinor.html">LorentzSpinor.h</a>>.
//
// Author: Peter Richardson
//

#include "ThePEG/Config/Complex.h"
#include "ThePEG/CLHEPWrap/ThreeVector.h"
#include "HelicityDefinitions.h"
#include "LorentzSpinor.fh"
#include "LorentzSpinorBar.fh"

namespace ThePEG {
namespace Helicity {

class LorentzSpinorBar {

public:

  // default zero constructor
  LorentzSpinorBar();

  // constructor with types
  LorentzSpinorBar(int type);
  LorentzSpinorBar(int dirac, int type);

  // constructor with complex numbers
  LorentzSpinorBar(int type,Complex,Complex, Complex,Complex);
  LorentzSpinorBar(int dirac, int type,Complex,Complex, Complex,Complex);

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

  // change the dirac matrix representation
  inline void changeRep(int);

  // return the spinor in a different representation
  inline LorentzSpinorBar transformRep(int);

  // return the representation of the spinor
  inline int Rep();

private:

  Complex _spin[4];
  // storage of the components
  int _idirac;
  // definition of the Dirac matrices used
  int _itype;
  // type of spinor


};

}
}

#include "LorentzSpinorBar.icc"

#endif
