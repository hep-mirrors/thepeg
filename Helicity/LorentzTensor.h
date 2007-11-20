// -*- C++ -*-
//
// LorentzTensor.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_LorentzTensor_H
#define ThePEG_LorentzTensor_H
// This is the declaration of the LorentzTensor class.


#include "ThePEG/Config/ThePEG.h"
#include "LorentzPolarizationVector.h"

namespace ThePEG {
namespace Helicity {

// compiler magic needs these pre-declarations to make friend templates work
template<typename Value> class LorentzTensor;

/// Scalar product with another tensor
template <typename T, typename U>
complex<typename BinaryOpTraits<T,U>::MulT> 
operator*(const LorentzTensor<T> &, const LorentzTensor<U> &);


/**
 *  The LorentzTensor class is designed to implement the storage of a
 *  complex tensor to be used to representation the wavefunction of a
 *  spin-2 particle.
 *
 *  At the moment it only implements the storage of the tensor
 *  components but it is envisaged that it will be extended to include
 *  boost methods etc.
 *
 * @author Peter Richardson
 *
 */

template<typename Value> 
class LorentzTensor{

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default zero constructor.
   */
  inline LorentzTensor();

  /**
   * Constructor specifyign all components.
   */
  LorentzTensor(complex<Value>, complex<Value>, complex<Value>, complex<Value>,
		complex<Value>, complex<Value>, complex<Value>, complex<Value>,
		complex<Value>, complex<Value>, complex<Value>, complex<Value>,
		complex<Value>, complex<Value>, complex<Value>, complex<Value>);

  /**
   * Constructor in terms of two polarization vectors.
   */
  inline LorentzTensor(LorentzPolarizationVector, LorentzPolarizationVector);

//   /**
//    * Constructor in terms of two LorentzVectors
//    */
//   inline LorentzTensor(const LorentzVector<double> & p,
// 		       const LorentzVector<double> & q);

  //@}

  /** @name Access individual components. */
  //@{
  /**
   * Get x,x component.
   */
  inline complex<Value> xx() const;

  /**
   * Get y,x component.
   */
  inline complex<Value> yx() const;
  /**
   * Get z,x component.
   */
  inline complex<Value> zx() const;

  /**
   * Get t,x component.
   */
  inline complex<Value> tx() const;

  /**
   * Get x,y component.
   */
  inline complex<Value> xy() const;

  /**
   * Get y,y component.
   */
  inline complex<Value> yy() const;

  /**
   * Get z,y component.
   */
  inline complex<Value> zy() const;

  /**
   * Get t,y component.
   */
  inline complex<Value> ty() const;

  /**
   * Get x,z component.
   */
  inline complex<Value> xz() const;

  /**
   * Get y,z component.
   */
  inline complex<Value> yz() const;

  /**
   * Get z,z component.
   */
  inline complex<Value> zz() const;

  /**
   * Get t,z component.
   */
  inline complex<Value> tz() const;

  /**
   * Get x,t component.
   */
  inline complex<Value> xt() const;

  /**
   * Get y,t component.
   */
  inline complex<Value> yt() const;

  /**
   * Get z,t component.
   */
  inline complex<Value> zt() const;

  /**
   * Get t,t component.
   */
  inline complex<Value> tt() const;

  /**
   * Set x,x component.
   */
  inline void setXX(complex<Value>);

  /**
   * Set y,x component.
   */
  inline void setYX(complex<Value>);

  /**
   * Set z,x component.
   */
  inline void setZX(complex<Value>);

  /**
   * Set t,x component.
   */
  inline void setTX(complex<Value>);

  /**
   * Set x,y component.
   */
  inline void setXY(complex<Value>);

  /**
   * Set y,y component.
   */
  inline void setYY(complex<Value>);

  /**
   * Set z,y component.
   */
  inline void setZY(complex<Value>);

  /**
   * Set t,y component.
   */
  inline void setTY(complex<Value>);

  /**
   * Set x,z component.
   */
  inline void setXZ(complex<Value>);

  /**
   * Set y,z component.
   */
  inline void setYZ(complex<Value>);

  /**
   * Set z,z component.
   */
  inline void setZZ(complex<Value>);

  /**
   * Set t,z component.
   */
  inline void setTZ(complex<Value>);

  /**
   * Set x,t component.
   */
  inline void setXT(complex<Value>);

  /**
   * Set y,t component.
   */
  inline void setYT(complex<Value>);

  /**
   * Set z,t component.
   */
  inline void setZT(complex<Value>);

  /**
   * Set t,t component.
   */
  inline void setTT(complex<Value>);

  /**
   * Get components by indices.
   */
  inline complex<Value> operator () (int,int) const;

  /**
   * Set components by indices.
   */
  inline complex<Value> & operator () (int,int);
  //@}

  /** @name Transformations. */
  //@{
  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzTensor & boost(double,double,double);

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  inline LorentzTensor & boost(const Boost &);

  /**
   * General Lorentz transformation
   */
  inline LorentzTensor & transform(const SpinOneLorentzRotation &);

  /**
   * Return the complex conjugate.
   */
  inline LorentzTensor conjugate();
  //@}

  /** @name Arithmetic operators. */
  //@{
  /**
   * Scaling with a complex number
   */
  inline LorentzTensor operator*=(Complex);

  /**
   * Scalar product with other tensor
   */
  template <typename T, typename U>
  friend complex<typename BinaryOpTraits<T,U>::MulT> 
  operator*(const LorentzTensor<T> &, const LorentzTensor<U> &);

  /**
   * Addition.
   */
  inline LorentzTensor operator+(const LorentzTensor &) const;

  /**
   * Subtraction.
   */
  inline LorentzTensor operator-(const LorentzTensor &) const;

  /**
   * Trace
   */
  inline complex<Value> trace();
  //@}

private:

  /**
   * The components.
   */
  vector<vector<complex<Value> > > _tensor;

};

/**
 * Multiplication by a complex number.
 */
template<typename T, typename U> 
inline LorentzTensor<typename BinaryOpTraits<T,U>::MulT> 
operator*(complex<U>, const LorentzTensor<T> &);

/**
 * Multiply a LorentzVector by a LorentzTensor.
 */
template<typename T, typename U> 
inline LorentzVector<typename BinaryOpTraits<complex<T>,U>::MulT>
operator*(const LorentzVector<U> &, const LorentzTensor<T> &);

/**
 * Multiply a LorentzTensor by a LorentzVector.
 */
template<typename T, typename U> 
inline LorentzVector<typename BinaryOpTraits<complex<T>,U>::MulT>
operator*(const LorentzTensor<T> &, const LorentzVector<U> &);

}
}

#include "LorentzTensor.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "LorentzTensor.tcc"
#endif 

#endif
