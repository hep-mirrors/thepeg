// -*- C++ -*-
#ifndef ThePEG_LorentzPolarizationVector_H
#define ThePEG_LorentzPolarizationVector_H
// This is the declaration of the LorentzPolarizationVector class.

#include "ThePEG/Config/Complex.h"
#include "ThePEG/CLHEPWrap/LorentzVector.h"
#include "ThePEG/CLHEPWrap/Lorentz5Vector.h"
#include "ThePEG/CLHEPWrap/ThreeVector.h"

namespace ThePEG {
namespace Helicity {

/**
 *  The LorentzPolarizationVector class is designed to store a
 *  polarization vector. It is based on the LorentzVector class of
 *  CLHEP and provides many of the same methods, the major difference
 *  is the data members are complex and the assoiciated methods have
 *  been change to accomodate this.
 *
 * @see CLHEP::LorentzVector
 *
 * @author Peter Richardson
 *
 */
class LorentzPolarizationVector {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Constructor giving the components \a x, \a y, \a z, \a t.
   */
  inline LorentzPolarizationVector(Complex x, Complex y,
				   Complex z, Complex t);

  /**
   * Constructor giving the components \a x, \a y, \a z, with the
   * t-component set to 0.
   */
  inline LorentzPolarizationVector(Complex x, Complex y, Complex z);

  /**
   * Constructor giving the \a t component with x, y, z set to 0.
   */
  inline LorentzPolarizationVector(Complex t);

  /**
   * Default Constructor zero everything
   */
  inline LorentzPolarizationVector();

  /**
   * Setup from a LorentzVector.
   */
  inline LorentzPolarizationVector(const LorentzVector &);

  /**
   * Copy constructor
   */
  inline LorentzPolarizationVector(const LorentzPolarizationVector &);

  /**
   * The destructor
   */
  inline ~LorentzPolarizationVector();
  //@}

  /** @name Access individual components. */
  //@{
  /**
   * Get x component.
   */
  inline Complex x() const;

  /**
   * Get y component.
   */
  inline Complex y() const;

  /**
   * Get z component.
   */
  inline Complex z() const;

  /**
   * Get time component.
   */
  inline Complex t() const;


  /**
   * Set x component.
   */
  inline void setX(Complex);

  /**
   * Set y component.
   */
  inline void setY(Complex);

  /**
   * Set z component.
   */
  inline void setZ(Complex);

  /**
   * Set time component.
   */
  inline void setT(Complex);

  /**
   * Get components by index.
   */
  inline Complex operator () (int) const;

  /**
   * Get components by index.
   */
  inline Complex operator [] (int) const;

  /**
   * Set components by index.
   */
  inline Complex & operator () (int);

  /**
   * Set components by index.
   */
  inline Complex & operator [] (int);
  //@}

  /** @name Assignment and arithmetic operators. */
  //@{
  /**
   * Assignment.
   */
  inline LorentzPolarizationVector &
  operator=(const LorentzPolarizationVector &);

  /**
   * Addition.
   */
  inline LorentzPolarizationVector
  operator+(const LorentzPolarizationVector &) const;

  /**
   * Add and assign.
   */
  inline LorentzPolarizationVector &
  operator+=(const LorentzPolarizationVector &);

  /**
   * Subtraction.
   */
  inline LorentzPolarizationVector
  operator-(const LorentzPolarizationVector &) const;

  /**
   * Subtract and assign.
   */
  inline LorentzPolarizationVector &
  operator-=(const LorentzPolarizationVector &);

  /**
   * Unary minus.
   */
  inline LorentzPolarizationVector operator-() const;

  /**
   * Scaling with complex numbers.
   */
  inline LorentzPolarizationVector & operator*=(Complex);

  /**
   * Dividing by a complex number
   */
  LorentzPolarizationVector & operator/=(Complex);

  /**
   * Scalar product with LorentzVector.
   */
  inline Complex dot(const LorentzVector &) const;

  /**
   * Scalar product with LorentzVector.
   * Same as dot(const LorentzVector &).
   */
  inline Complex operator*(const LorentzVector &) const;

  /**
   * Scalar product with other polarization.
   */
  inline Complex dot(const LorentzPolarizationVector &) const;

  /**
   * Scalar product with other polarization.
   * Same as dot(const LorentzPolarizationVector &).
   */
  inline Complex operator*(const LorentzPolarizationVector &) const;
  //@}

  /** @name Comparison operators. */
  //@{
  /**
   * Check for equality.
   */
  inline bool operator == (const LorentzPolarizationVector &) const;

  /**
   * Check for non-equality.
   */
  inline bool operator != (const LorentzPolarizationVector &) const;
  //@}



  /** @name Boosts and rotations. */
  //@{
  /**
   * Boost along x direction
   */
  LorentzPolarizationVector & boostX( double beta );

  /**
   * Boost along y direction
   */
  LorentzPolarizationVector & boostY( double beta );

  /**
   * Boost along z direction
   */
  LorentzPolarizationVector & boostZ( double beta );


  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzPolarizationVector & boost(double bx, double by, double bz);

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  inline LorentzPolarizationVector & boost(const Hep3Vector &);

  /**
   * Normalizes the Hep3Vector \a axis to define a direction, and uses
   * \a beta to define the magnitude of the boost.
   */
  inline LorentzPolarizationVector &
  boost(const Hep3Vector & axis,  double beta);

  /**
   * Rotate the spatial component around the x-axis.
   */
  LorentzPolarizationVector & rotateX(double);

  /**
   * Rotate the spatial component around the y-axis.
   */
  LorentzPolarizationVector & rotateY(double);

  /**
   * Rotate the spatial component around the z-axis.
   */
  LorentzPolarizationVector & rotateZ(double);

  /**
   * Rotates the reference frame from Uz to \a newUz (unit vector).
   */
  LorentzPolarizationVector &  rotateUz(const Hep3Vector & newUz);

  /**
   * Rotate the spatial component around specified \a axis.
   */
  LorentzPolarizationVector & rotate(double, const Hep3Vector & axis);

  /**
   * Return the conjugate LorentzPolarizationVector.
   */
  inline LorentzPolarizationVector conjugate();
  //@}

private:

  Complex _vec[4];

};


/**
 * Divide a LorentzPolarizationVector with a complex number.
 */
inline LorentzPolarizationVector
operator/(const LorentzPolarizationVector &, Complex a);

/**
 * Multiply a LorentzPolarizationVector with a complex number.
 */
inline LorentzPolarizationVector
operator*(Complex a,const LorentzPolarizationVector &);

/**
 * Multiply a Lorentz5Momentum with a complex number.
 */
inline LorentzPolarizationVector
operator*(Complex a,const Lorentz5Momentum &);

/**
 * Return the LorentzPolarizationVector \a vec boosted by \a beta in
 * the x-direction.
 */
inline LorentzPolarizationVector
boostXOf(const LorentzPolarizationVector & vec, double beta);

/**
 * Return the LorentzPolarizationVector \a vec boosted by \a beta in
 * the y-direction.
 */
inline LorentzPolarizationVector
boostYOf(const LorentzPolarizationVector & vec, double beta);

/**
 * Return the LorentzPolarizationVector \a vec boosted by \a beta in
 * the z-direction.
 */
inline LorentzPolarizationVector
boostZOf(const LorentzPolarizationVector & vec, double beta);

/**
 * Return the LorentzPolarizationVector \a vec boosted by \a beta.
 */
inline LorentzPolarizationVector
boostOf(const LorentzPolarizationVector & vec, const Hep3Vector & betaVector);

/**
 * Return the LorentzPolarizationVector \a vec boosted by \a beta in
 * the direction of \a axis.
 */
inline LorentzPolarizationVector
boostOf(const LorentzPolarizationVector & vec,
	const Hep3Vector & axis,  double beta);

}
}

#include "LorentzPolarizationVector.icc"

#endif
