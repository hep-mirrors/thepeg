// -*- C++ -*-
#ifndef ThePEG_LorentzSpinor_H
#define ThePEG_LorentzSpinor_H
//
// This is the declaration of the <!id>LorentzSpinor<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//  The <!id>LorentzSpinor<!!id> class is designed to store a
//  spinor. In addition to storing the components of the spinor
//  information is stored on the representation of the Dirac matrices
//  used in calculating the spinor and the type of spinor, for example
//  u or v type.
//
//  At the moment only two choices of the Dirac matrix representation
//  are supported.  The first _idirac=1 is a low energy representation
//  in which
//
//  gamma_{i=1,2,3} = (    0      sigma_i ) gamma_0 = ( 1  0 ) gamma_5 = ( 0 1 )
//                    ( -sigma_i     0    )           ( 0 -1 )           ( 1 0 )
//
//  this choice is perhaps more familiar from undergraduate courses
//  and is most appropriate for low-energy calculations. However for
//  high-energy calculations the choice made by the HELAS
//  collaboration is more efficient for numerical calculations. This
//  choice is supported as _idirac = 2 and is recommend for most
//  calculations. In this representation
//
//  gamma_{i=1,2,3} = (    0      sigma_i ) gamma_0 = ( 0 1 ) gamma_5 = ( -1 0 )
//                    ( -sigma_i     0    )           ( 1 0 )           (  0 1 )
//
//  These two representations are related by the transformation
//
//  psi_2 = S psi_1   where    S = 1/sqrt(2) (  1 -1 )
//                                           (  1  1 )
//
//  and this transformation is used in the transformRep(int) member to
//  return the spinor in whichever of the supported representations is
//  required or the changeRep(int) member to change the representation
//  of this spinor.
//
//  The <!id>HelicityDefinitions<!!id> class contains a default choice
//  for the representation which should be used if possible.
//
//   The type of the spinor is also stored as _itype = 0   unknown
//                                                   = 1   u-type 
//                                                   = 2   v-type
//
//  This information is intended mainly for use in the case of
//  Majorana particles where matrix elements can be calculated with
//  either u or v type spinors and knowledge of which was used will be
//  needed in order to give the correct correlations. The unknown type
//  is intended for cases where either the spinor for an off-shell
//  line in a matrix element calculation or the information is
//  genuinely unknown.
//
//  The LorentzSpinorBar class is also provided to store the barred spinor.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="HelicityDefinitions.html">HelicityDefinitions.h</a>.
// <a href="LorentzSpinorBar.html">LorentzSpinorBar.h</a>.
//
// Author: Peter Richardson
//
#include "ThePEG/Config/Complex.h"
#include "ThePEG/CLHEPWrap/ThreeVector.h"
#include "HelicityDefinitions.h"
#include "LorentzSpinor.fh"
#include "LorentzSpinorBar.fh"

namespace ThePEG{
namespace Helicity{

class LorentzSpinor {

public:

  // default zero constructor
  LorentzSpinor();

  // specific the type and choice of dirac matrix
  LorentzSpinor(int type);
  LorentzSpinor(int dirac, int type);

  // constructor with complex numbers
  LorentzSpinor(int type, Complex,Complex,Complex,Complex);
  LorentzSpinor(int dirac, int type, Complex,Complex,Complex,Complex);

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

  // change the dirac matrix representation
  inline void changeRep(int);

  // return the spinor in a different representation
  inline LorentzSpinor transformRep(int);

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

#include "LorentzSpinor.icc"

#endif

