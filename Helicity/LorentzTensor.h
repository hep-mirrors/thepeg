// -*- C++ -*-
#ifndef ThePEG_LorentzTensor_H
#define ThePEG_LorentzTensor_H
// This is the declaration of the LorentzTensor class.


#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Config/Complex.h"
#include "LorentzPolarizationVector.h"

namespace ThePEG {
namespace Helicity {

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
  LorentzTensor(Complex, Complex, Complex, Complex,
		Complex, Complex, Complex, Complex,
		Complex, Complex, Complex, Complex,
		Complex, Complex, Complex, Complex);

  /**
   * Constructor in terms of two polarization vectors.
   */
  inline LorentzTensor(LorentzPolarizationVector, LorentzPolarizationVector);

  /**
   * Constructor in terms of two LorentzVectors
   */
  inline LorentzTensor(LorentzVector p, LorentzVector q);

  /**
   * The destructor
   */
  inline ~LorentzTensor();
  //@}

  /** @name Access individual components. */
  //@{
  /**
   * Get x,x component.
   */
  inline Complex xx() const;

  /**
   * Get y,x component.
   */
  inline Complex yx() const;
  /**
   * Get z,x component.
   */
  inline Complex zx() const;

  /**
   * Get t,x component.
   */
  inline Complex tx() const;

  /**
   * Get x,y component.
   */
  inline Complex xy() const;

  /**
   * Get y,y component.
   */
  inline Complex yy() const;

  /**
   * Get z,y component.
   */
  inline Complex zy() const;

  /**
   * Get t,y component.
   */
  inline Complex ty() const;

  /**
   * Get x,z component.
   */
  inline Complex xz() const;

  /**
   * Get y,z component.
   */
  inline Complex yz() const;

  /**
   * Get z,z component.
   */
  inline Complex zz() const;

  /**
   * Get t,z component.
   */
  inline Complex tz() const;

  /**
   * Get x,t component.
   */
  inline Complex xt() const;

  /**
   * Get y,t component.
   */
  inline Complex yt() const;

  /**
   * Get z,t component.
   */
  inline Complex zt() const;

  /**
   * Get t,t component.
   */
  inline Complex tt() const;

  /**
   * Set x,x component.
   */
  inline void setXX(Complex);

  /**
   * Set y,x component.
   */
  inline void setYX(Complex);

  /**
   * Set z,x component.
   */
  inline void setZX(Complex);

  /**
   * Set t,x component.
   */
  inline void setTX(Complex);

  /**
   * Set x,y component.
   */
  inline void setXY(Complex);

  /**
   * Set y,y component.
   */
  inline void setYY(Complex);

  /**
   * Set z,y component.
   */
  inline void setZY(Complex);

  /**
   * Set t,y component.
   */
  inline void setTY(Complex);

  /**
   * Set x,z component.
   */
  inline void setXZ(Complex);

  /**
   * Set y,z component.
   */
  inline void setYZ(Complex);

  /**
   * Set z,z component.
   */
  inline void setZZ(Complex);

  /**
   * Set t,z component.
   */
  inline void setTZ(Complex);

  /**
   * Set x,t component.
   */
  inline void setXT(Complex);

  /**
   * Set y,t component.
   */
  inline void setYT(Complex);

  /**
   * Set z,t component.
   */
  inline void setZT(Complex);

  /**
   * Set t,t component.
   */
  inline void setTT(Complex);

  /**
   * Get components by indices.
   */
  inline Complex operator () (int,int) const;

  /**
   * Set components by indices.
   */
  inline Complex & operator () (int,int);
  //@}

  /** @name Transformations. */
  //@{
  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzTensor boost(double,double,double) const;

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  inline LorentzTensor boost(const Hep3Vector &) const;

  /**
   * Return the complex conjugate.
   */
  inline LorentzTensor conjugate();
  //@}

  /** @name Assignment and arithmetic operators. */
  //@{
  /**
   * Assignment operator.
   */
  inline LorentzTensor & operator=(const LorentzTensor &);

  /**
   * Scalar product with other tensor
   */
  inline Complex operator*(const LorentzTensor &) const;

  /**
   * Scaling with a complex number
   */
  inline LorentzTensor operator*=(Complex);

  /**
   * Addition.
   */
  inline LorentzTensor operator+(const LorentzTensor &) const;

  /**
   * Subtraction.
   */
  inline LorentzTensor operator-(const LorentzTensor &) const;
  //@}

private:

  /**
   * The components.
   */
  Complex _tensor[4][4];

};

/**
 * Multiplication by a complex number.
 */
inline LorentzTensor operator*(Complex a,const LorentzTensor &);

/**
 * Multiply a LorentzPolarizationVector by a LorentzTensor.
 */
inline LorentzPolarizationVector
operator*(const LorentzPolarizationVector &, const LorentzTensor &);

/**
 * Multiply a LorentzTensor by a LorentzPolarizationVector.
 */
inline LorentzPolarizationVector
operator*(const LorentzTensor &,const LorentzPolarizationVector &);

}
}

#include "LorentzTensor.icc"

#endif
