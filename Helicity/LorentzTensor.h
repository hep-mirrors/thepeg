// -*- C++ -*-
#ifndef ThePEG_LorentzTensor_H
#define ThePEG_LorentzTensor_H
//
// This is the declaration of the <!id>LorentzTensor<!!id> class.
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
#include "LorentzPolarizationVector.h"

namespace ThePEG {
namespace Helicity {

class LorentzTensor{

    public:

  // constructors
  inline LorentzTensor();
  // default zero constructor

  LorentzTensor(Complex, Complex, Complex, Complex,
		Complex, Complex, Complex, Complex,
		Complex, Complex, Complex, Complex,
		Complex, Complex, Complex, Complex);
  // constructor specifyign all components

  inline LorentzTensor(LorentzPolarizationVector, LorentzPolarizationVector);
  // constructor in terms of two polarization vectors

  inline Complex xx() const;
  inline Complex yx() const;
  inline Complex zx() const;
  inline Complex tx() const;
  inline Complex xy() const;
  inline Complex yy() const;
  inline Complex zy() const;
  inline Complex ty() const;
  inline Complex xz() const;
  inline Complex yz() const;
  inline Complex zz() const;
  inline Complex tz() const;
  inline Complex xt() const;
  inline Complex yt() const;
  inline Complex zt() const;
  inline Complex tt() const;
  // Get components

  inline void setXX(Complex);
  inline void setYX(Complex);
  inline void setZX(Complex);
  inline void setTX(Complex);
  inline void setXY(Complex);
  inline void setYY(Complex);
  inline void setZY(Complex);
  inline void setTY(Complex);
  inline void setXZ(Complex);
  inline void setYZ(Complex);
  inline void setZZ(Complex);
  inline void setTZ(Complex);
  inline void setXT(Complex);
  inline void setYT(Complex);
  inline void setZT(Complex);
  inline void setTT(Complex);
  // Set components.

  inline Complex operator () (int,int) const;
  // Get components by index.

  inline Complex & operator () (int,int);
  // Set components by index.

  inline LorentzTensor & operator = (const LorentzTensor &);
  // Assignment.

private:

  Complex _tensor[4][4];

};

}
}

#include "LorentzTensor.icc"

#endif
