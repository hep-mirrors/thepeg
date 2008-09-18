// -*- C++ -*-
//
// LorentzRSSpinorBar.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_LorentzRSSpinorBar_H
#define ThePEG_LorentzRSSpinorBar_H
// This is the declaration of the LorentzRSSpinorBar class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Vectors/ThreeVector.h"
#include "HelicityDefinitions.h"
#include "LorentzRSSpinor.fh"
#include "LorentzRSSpinorBar.fh"
#include "LorentzSpinorBar.h"
#include "LorentzSpinor.h"
#include "LorentzPolarizationVector.h"

namespace ThePEG {
namespace Helicity {

/**
 *  The <code>LorentzRSSpinorBar</code> class implements the storage of a
 *  barred Lorentz Rarita-Schwinger Spinor for a spin-3/2 particle.
 *  The design is based on that of the
 *  <code>LorentzRSSpinor</code> class and the details of the implemented
 *  are discussed in more detail in the header file for that class.
 *
 * @see LorentzRSSpinor
 *
 * \author Peter Richardson
 *
 */
template <typename Value>
class LorentzRSSpinorBar {

public:

  /** @name Standard constructors. */
  //@{
  /**
   * Default zero constructor, optionally specifying \a t, the type
   * and \a r, the choice of dirac matrix.
   */
  LorentzRSSpinorBar(SpinorType t = unknown_spinortype,
		     DiracRep r = defaultDRep)  
    : _dirac(r), _type(t) {
    for(unsigned int ix=0;ix<4;++ix)
      for(unsigned int iy=0;iy<4;++iy) _spin[ix][iy]=Value();
  }
  
  /**
   * Default zero constructor, optionally specifying the choice of
   * dirac matrix.
   */
  LorentzRSSpinorBar(DiracRep dirac)
    : _dirac(dirac), _type(unknown_spinortype) {
    for(unsigned int ix=0;ix<4;++ix)
      for(unsigned int iy=0;iy<4;++iy) _spin[ix][iy]=Value();
  }

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying \a t, the type and \a r, the choice of
   * dirac matrix.
   */
  LorentzRSSpinorBar(complex<Value> a1,complex<Value> b1,
		     complex<Value> c1,complex<Value> d1,
		     complex<Value> a2,complex<Value> b2,
		     complex<Value> c2,complex<Value> d2,
		     complex<Value> a3,complex<Value> b3,
		     complex<Value> c3,complex<Value> d3,
		     complex<Value> a4,complex<Value> b4,
		     complex<Value> c4,complex<Value> d4,
		     SpinorType t=unknown_spinortype, DiracRep r=defaultDRep)
    : _dirac(r), _type(t) {
    _spin[0][0]=a1;_spin[1][0]=a2;_spin[2][0]=a3;_spin[3][0]=a4;
    _spin[0][1]=b1;_spin[1][1]=b2;_spin[2][1]=b3;_spin[3][1]=b4;
    _spin[0][2]=c1;_spin[1][2]=c2;_spin[2][2]=c3;_spin[3][2]=c4;
    _spin[0][3]=d1;_spin[1][3]=d2;_spin[2][3]=d3;_spin[3][3]=d4;
  }
  
  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying the choice of dirac matrix
   */
  LorentzRSSpinorBar(complex<Value> a1,complex<Value> b1,
		     complex<Value> c1,complex<Value> d1,
		     complex<Value> a2,complex<Value> b2,
		     complex<Value> c2,complex<Value> d2,
		     complex<Value> a3,complex<Value> b3,
		     complex<Value> c3,complex<Value> d3,
		     complex<Value> a4,complex<Value> b4,
		     complex<Value> c4,complex<Value> d4,DiracRep dirac)
    : _dirac(dirac), _type(unknown_spinortype) {
    _spin[0][0]=a1;_spin[1][0]=a2;_spin[2][0]=a3;_spin[3][0]=a4;
    _spin[0][1]=b1;_spin[1][1]=b2;_spin[2][1]=b3;_spin[3][1]=b4;
    _spin[0][2]=c1;_spin[1][2]=c2;_spin[2][2]=c3;_spin[3][2]=c4;
    _spin[0][3]=d1;_spin[1][3]=d2;_spin[2][3]=d3;_spin[3][3]=d4;
  }
  //@}

  /** @name Access the components. */
  //@{
  /**
   * Subscript operator to return spinor components
   */
  complex<Value> operator()(int i, int j) const {
    assert( i >= 0 && i <= 3 && j>=0 && j<=3 );
    return _spin[i][j];
  }

  /**
   * Set components by index
   */
  complex<Value> & operator () (int i, int j) {
    assert( i >= 0 && i <= 3 && j>=0 && j<=3 );
    return _spin[i][j];
  }
  
  /**
   * Get first spinor component for the x vector
   */
  complex<Value> xs1() const {return _spin[0][0];}

  /**
   * Get second spinor component for the x vector
   */
  complex<Value> xs2() const {return _spin[0][1];}

  /**
   * Get third  spinor component for the x vector
   */
  complex<Value> xs3() const {return _spin[0][2];}

  /**
   * Get fourth  spinor component for the x vector
   */
  complex<Value> xs4() const {return _spin[0][3];}

  /**
   * Get first spinor component for the y vector
   */
  complex<Value> ys1() const {return _spin[1][0];}

  /**
   * Get second spinor component for the y vector
   */
  complex<Value> ys2() const {return _spin[1][1];}
  
  /**
   * Get third spinor component for the y vector
   */
  complex<Value> ys3() const {return _spin[1][2];}
  
  /**
   * Get fourth spinor component for the y vector
   */
  complex<Value> ys4() const {return _spin[1][3];}
  
  /**
   * Get first spinor component for the z vector
   */
  complex<Value> zs1() const {return _spin[2][0];}
  
  /**
   * Get second spinor component for the z vector
   */
  complex<Value> zs2() const {return _spin[2][1];}
  
  /**
   * Get third spinor component for the z vector
   */
  complex<Value> zs3() const {return _spin[2][2];}
  
  /**
   * Get fourth spinor component for the z vector
   */
  complex<Value> zs4() const {return _spin[2][3];}
  
  /**
   * Get first spinor component for the t vector
   */
  complex<Value> ts1() const {return _spin[3][0];}
  
  /**
   * Get second spinor component for the t vector
   */
  complex<Value> ts2() const {return _spin[3][1];}
  
  /**
   * Get third spinor component for the t vector
   */
  complex<Value> ts3() const {return _spin[3][2];}
  
  /**
   * Get fourth spinor component for the t vector
   */
  complex<Value> ts4() const {return _spin[3][3];}
  
  /**
   * Set first spinor component for the x vector
   */
  void setXS1(complex<Value> in) {_spin[0][0]=in;}
  
  /**
   * Set second spinor component for the x vector
   */
  void setXS2(complex<Value> in) {_spin[0][1]=in;}
  
  /**
   * Set third spinor component for the x vector
   */
  void setXS3(complex<Value> in) {_spin[0][2]=in;}
  
  /**
   * Set fourth spinor component for the x vector
   */
  void setXS4(complex<Value> in) {_spin[0][3]=in;}
  
  /**
   * Set first spinor component for the y vector
   */
  void setYS1(complex<Value> in) {_spin[1][0]=in;}
  
  /**
   * Set second spinor component for the y vector
   */
  void setYS2(complex<Value> in) {_spin[1][1]=in;}
  
  /**
   * Set third spinor component for the y vector
   */
  void setYS3(complex<Value> in) {_spin[1][2]=in;}
  
  /**
   * Set fourth spinor component for the y vector
   */
  void setYS4(complex<Value> in) {_spin[1][3]=in;}
  
  /**
   * Set first spinor component for the z vector
   */
  void setZS1(complex<Value> in) {_spin[2][0]=in;}
  
  /**
   * Set second spinor component for the z vector
   */
  void setZS2(complex<Value> in) {_spin[2][1]=in;}
  
  /**
   * Set third spinor component for the z vector
   */
  void setZS3(complex<Value> in) {_spin[2][2]=in;}
  
  /**
   * Set fourth spinor component for the z vector
   */
  void setZS4(complex<Value> in) {_spin[2][3]=in;}
  
  /**
   * Set first spinor component for the t vector
   */
  void setTS1(complex<Value> in) {_spin[3][0]=in;}
  
  /**
   * Set second spinor component for the t vector
   */
  void setTS2(complex<Value> in) {_spin[3][1]=in;}
  
  /**
   * Set third spinor component for the t vector
   */
  void setTS3(complex<Value> in) {_spin[3][2]=in;}
  
  /**
   * Set fourth spinor component for the t vector
   */
  void setTS4(complex<Value> in ) {_spin[3][3]=in;}
  //@}

  /** @name Arithmetic operators. */
  //@{
  /**
   * dot product with a polarization vector
   */
  LorentzSpinorBar<Value> dot(const LorentzPolarizationVector & vec) const {
    LorentzSpinorBar<Value> output(_type,_dirac);
    for(unsigned int ix=0;ix<4;++ix) {
      output[ix]=_spin[3][ix]*vec.t()-_spin[0][ix]*vec.x()
	-_spin[1][ix]*vec.y()-_spin[2][ix]*vec.z();
    }
    return output;
  }

  /**
   * dot product with a 4-momentum
   */
  LorentzSpinorBar<Value> dot(const LorentzMomentum & invec) const {
    LorentzSpinorBar<Value> output(_type,_dirac);
    LorentzVector<double> vec = UnitRemoval::InvE * invec;
    unsigned int ix;
    for(ix=0;ix<4;++ix) {
      output[ix]=_spin[3][ix]*vec.t()-_spin[0][ix]*vec.x()
	-_spin[1][ix]*vec.y()-_spin[2][ix]*vec.z();
    }
    return output;
  }
  //@}
  
  /** @name Transformations. */
  //@{
  /**
   * return the barred spinor
   */
  LorentzRSSpinor<Value> bar() const;

  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzRSSpinorBar & boost(double,double,double);

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  LorentzRSSpinorBar & boost(const Boost &);

  /**
   * General transform
   */
  LorentzRSSpinorBar & transform(const LorentzRotation &);
  //@}

  /** @name Functions related to type and representation. */
  //@{
  /**
   * Change the dirac matrix representation.
   */
  void changeRep(DiracRep newdirac) {
    if(newdirac!=_dirac) *this = transformRep(newdirac);
  }

  /**
   * Return the spinor in a different representation.
   */
  LorentzRSSpinorBar transformRep(DiracRep newdirac) {
    // do nothing if all ready in the correct representation
    if(newdirac==_dirac) return *this;
    double fact(sqrt(0.5));
    // transform from HELAS representation to Haber one
    complex<Value> out[4][4];
    unsigned int ix;
    if(newdirac==HELASDRep && _dirac==HaberDRep) {
      for(ix=0;ix<4;++ix) {
	out[ix][0] = fact*( _spin[ix][0]-_spin[ix][2]);
	out[ix][1] = fact*( _spin[ix][1]-_spin[ix][3]);
	out[ix][2] = fact*( _spin[ix][0]+_spin[ix][2]);
	out[ix][3] = fact*( _spin[ix][1]+_spin[ix][3]);
      }
    }
    // transform from Haber representation to HELAS one
    else if(newdirac==HaberDRep && _dirac==HELASDRep) {
      for(ix=0;ix<4;++ix) {
	out[ix][0] = fact*( _spin[ix][0]+_spin[ix][2]);
	out[ix][1] = fact*( _spin[ix][1]+_spin[ix][3]);
	out[ix][2] = fact*(-_spin[ix][0]+_spin[ix][2]);
	out[ix][3] = fact*(-_spin[ix][1]+_spin[ix][3]);
      }
    }
    return LorentzRSSpinorBar
      (out[0][0],out[0][1],out[0][2],out[0][3],
       out[1][0],out[1][1],out[1][2],out[1][3],
       out[2][0],out[2][1],out[2][2],out[2][3],
       out[3][0],out[3][1],out[3][2],out[3][3],_type,_dirac);
  }
  
  /**
   * Return the representation of the spinor.
   */
  DiracRep Rep() const {return _dirac;}

  /**
   * Return the type of the spinor.
   */
  SpinorType Type() const {return _type;}
  //@}

  /**
   * Current \f$\bar{f}^\alpha(c_LP_L+c_RP_R)f\f$ for general couplings.
   * @param f The unbarred spinor
   * @param left The left-handed coupling, \f$c_L\f$.
   * @param right The right-handed coupling, \f$c_R\f$.
   */
  template <typename ValueB>
  LorentzVector<complex<
    typename BinaryOpTraits<Value,ValueB>::MulT> >
    generalCurrent(LorentzSpinor<ValueB>& f, Complex left, Complex right) {
      typedef complex<typename BinaryOpTraits<Value,ValueB>::MulT> ResultT;
      ResultT output[4];
      // ensure both spinors are in the same representation,
      // otherwise change to default
      if(Rep()!=f.Rep()) {
	f.changeRep(defaultDRep);
	changeRep(defaultDRep);
      }
      unsigned int iz;
      // low energy
      if(Rep()==HaberDRep) {
	for(iz=0;iz<4;++iz) {
	  output[iz] = 
	    0.5*left*( (_spin[iz][0]-_spin[iz][2])*(f.s1()-f.s3())
		       +(_spin[iz][1]-_spin[iz][3])*(f.s2()-f.s4()))
	    +0.5*right*( (_spin[iz][0]+_spin[iz][2])*(f.s1()+f.s3())
			 +(_spin[iz][1]+_spin[iz][3])*(f.s2()+f.s4()));}
      }
      else {
	for(iz=0;iz<4;++iz){
	  output[iz]=  left*(_spin[iz][0]*f.s1()+_spin[iz][1]*f.s2())
	    +right*(_spin[iz][2]*f.s3()+_spin[iz][3]*f.s4());
	}
      }
      return LorentzVector<ResultT>(output[0],output[1],
				    output[2],output[3]);
    }
  
private:
  /**
   * Definition of the Dirac matrices used.
   */
  DiracRep _dirac;

  /**
   * Type of spinor.
   */
  SpinorType _type;

  /**
   * Storage of the components.
   */
  complex<Value> _spin[4][4];
};
}
}
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "LorentzRSSpinorBar.tcc"
#endif 

#endif
