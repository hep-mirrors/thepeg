// -*- C++ -*-
//
// LorentzSpinorBar.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_LorentzSpinorBar_H
#define ThePEG_LorentzSpinorBar_H
// This is the declaration of the LorentzSpinorBar class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Vectors/LorentzRotation.h"
#include "ThePEG/Vectors/ThreeVector.h"
#include "HelicityDefinitions.h"
#include "LorentzSpinor.fh"
#include "LorentzSpinorBar.fh"

namespace ThePEG {
namespace Helicity {

/**
 *  The LorentzSpinorBar class implements the storage of a barred
 *  LorentzSpinor. The design is based on that of the LorentzSpinor
 *  class where the details of the implemented are discussed in more
 *  detail.
 *
 * @see LorentzSpinor
 *
 * @author Peter Richardson
 */

template<typename Value>
class LorentzSpinorBar {
public:

  /** @name Standard constructors. */
  //@{
  /**
   * Default zero constructor, optionally specifying \a t, the type
   * and \a rep, the choice of dirac matrix.
   */
  LorentzSpinorBar(SpinorType t = unknown_spinortype,
		   DiracRep r = defaultDRep): _dirac(r), _type(t) {
    for(unsigned int ix=0;ix<4;++ix) _spin[ix]=Value();
  }

  /**
   * Default zero constructor, optionally specifying the choice of
   * dirac matrix.
   */
  LorentzSpinorBar(DiracRep dirac) 
    : _dirac(dirac), _type(unknown_spinortype) {
    for(unsigned int ix=0;ix<4;++ix) _spin[ix]=Value();
  }

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying \a t, the type and \a r, the choice of
   * dirac matrix.
   */
  LorentzSpinorBar(complex<Value> a, complex<Value> b,
		   complex<Value> c, complex<Value> d,
		   SpinorType t = unknown_spinortype,
		   DiracRep r = defaultDRep) 
    : _dirac(r), _type(t) {
    _spin[0]=a;
    _spin[1]=b;
    _spin[2]=c;
    _spin[3]=d;
  }

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying the choice of dirac matrix
   */
  LorentzSpinorBar(complex<Value> a, complex<Value> b,
		   complex<Value> c, complex<Value> d, DiracRep r)  
    : _dirac(r), _type(unknown_spinortype){
    _spin[0]=a;
    _spin[1]=b;
    _spin[2]=c;
    _spin[3]=d;
  }
  //@}

  /** @name Access the components. */
  //@{
  /**
   * Subscript operator to return spinor components
   */
  complex<Value> operator[](int i) const {
    assert( i>= 0 && i <= 3 );
    return _spin[i];
  }

  /**
   * Subscript operator to return spinor components
   */
  complex<Value> operator()(int i) const {
    assert( i>= 0 && i <= 3 );
    return _spin[i];
  }

  /**
   * Set components by index.
   */
  complex<Value> & operator()(int i) {
    assert( i>= 0 && i <= 3 );
    return _spin[i];
  }

  /**
   * Set components by index.
   */
  complex<Value> & operator[](int i) {
    assert( i>= 0 && i <= 3 );
    return _spin[i];
  }

  /**
   * Get first component.
   */
  complex<Value> s1() const {return _spin[0];}

  /**
   * Get second component.
   */
  complex<Value> s2() const {return _spin[1];}

  /**
   * Get third component.
   */
  complex<Value> s3() const {return _spin[2];}

  /**
   * Get fourth component.
   */
  complex<Value> s4() const {return _spin[3];}

  /**
   * Set first component.
   */
  void setS1(complex<Value> in) {_spin[0]=in;}

  /**
   * Set second component.
   */
  void setS2(complex<Value> in) {_spin[1]=in;}

  /**
   * Set third component.
   */
  void setS3(complex<Value> in) {_spin[2]=in;}

  /**
   * Set fourth component.
   */
  void setS4(complex<Value> in) {_spin[3]=in;}
  //@}

  /** @name Transformations. */
  //@{
  /**
   * Return the barred spinor
   */
  LorentzSpinor<Value> bar() const;

  /**
   * Return the conjugated spinor \f$u_c=C\bar{u}^T\f$. This operation
   * transforms u-spinors to v-spinors and vice-versa and is required when
   * dealing with majorana particles.
   */
  LorentzSpinorBar conjugate() const;

  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzSpinorBar & boost(double,double,double);

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  LorentzSpinorBar & boost(const Boost &);

  /**
   * General Lorentz transformation
   */
  LorentzSpinorBar & transform(const SpinHalfLorentzRotation &) ;
  
  /**
   * General Lorentz transformation
   */
  LorentzSpinorBar & transform(const LorentzRotation & r) {
    transform(r.half());
    return *this;
  }
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
  LorentzSpinorBar transformRep(DiracRep newdirac) const {
    if(newdirac==_dirac){return *this;}
    double fact=sqrt(0.5);
    // transform from HELAS representation to Haber one
    complex<Value> output[4];
    if(newdirac==HELASDRep && _dirac==HaberDRep) {
      output[0] = fact*( _spin[0]-_spin[2]);
      output[1] = fact*( _spin[1]-_spin[3]);
      output[2] = fact*( _spin[0]+_spin[2]);
      output[3] = fact*( _spin[1]+_spin[3]);
  }
    // transform from Haber representation to HELAS one
    else if(newdirac==HaberDRep && _dirac==HELASDRep) {
      output[0] = fact*( _spin[0]+_spin[2]);
      output[1] = fact*( _spin[1]+_spin[3]);
      output[2] = fact*(-_spin[0]+_spin[2]);
      output[3] = fact*(-_spin[1]+_spin[3]);
    }
    // return the answer
    return LorentzSpinorBar(output[0],output[1],
			    output[2],output[3],_type,newdirac);
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

private:
  /**
   * Definition of the Dirac matrices used.
   */
  DiracRep _dirac;

  /**
   * Type of spinor
   */
  SpinorType _type;

  /**
   * Storage of the components.
   */
  complex<Value> _spin[4];
};

}
}

#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "LorentzSpinorBar.tcc"
#endif 

#endif
