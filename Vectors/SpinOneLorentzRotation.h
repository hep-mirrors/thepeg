// -*- C++ -*-
#ifndef ThePEG_SpinOneLorentzRotation_H
#define ThePEG_SpinOneLorentzRotation_H

/** @file SpinOneLorentzRotation.h is... */
#include "ThePEG/Helicity/HelicityDefinitions.h"
#include "ThePEG/Helicity/LorentzTensor.fh"
#include "ThePEG/Helicity/LorentzRSSpinor.fh"
#include "ThePEG/Helicity/LorentzRSSpinorBar.fh"
#include "ThreeVector.h"
#include <valarray>

namespace ThePEG {

using ThePEG::Helicity::HELASDRep;
using ThePEG::Helicity::HaberDRep;
using ThePEG::Helicity::defaultDRep;

/**
 * The SpinOneLorentzRotation class is ... */

class SpinOneLorentzRotation {
public:

  /** @name Constructors and destructor. */
  //@{

  /**
   * Default constructor. Gives a unit matrix.
   */
  inline SpinOneLorentzRotation();

  /**
   * Constructor giving the components of a Lorentz boost.
   * @param bx The x-component of the boost
   * @param by The y-component of the boost
   * @param bz The z-component of the boost
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  inline SpinOneLorentzRotation (double bx, double by, double bz, double gamma=-1.);

  /**
   * Constructor giving the vector for a Lorentz boost.
   * @param b The boost vector
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  inline explicit SpinOneLorentzRotation (const Boost & b, double gamma=-1.);
  //@}

  /**
   * Returns true if the Identity matrix.
   */
  inline bool isIdentity() const;

  /**
   * Return the inverse.
   */
  inline SpinOneLorentzRotation inverse() const;

  /**
   * Inverts the SpinOneLorentzRotation matrix.
   */
  inline SpinOneLorentzRotation & invert();

  /**
   *  output operator
   */
  std::ostream & print( std::ostream & os ) const;

  /** @name Set methods for speical cases of simple rotations and boosts */
  //@{

  /**
   * Specify the components of a Lorentz Boost
   * @param bx The x-component of the boost
   * @param by The y-component of the boost
   * @param bz The z-component of the boost
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  SpinOneLorentzRotation & setBoost (double bx, double by, double bz, double gamma=-1.);

  /**
   * Specify a Lorentz Boost as a vector
   * @param b The boost vector
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  inline SpinOneLorentzRotation & setBoost (const Boost & b, double gamma=-1.);

  /**
   * Specify a rotation about a general axis by the angle given.
   * @param delta The angle
   * @param axis The axis
   */
  inline SpinOneLorentzRotation & setRotate(double delta, const Axis & axis);

  /**
   * Specify a rotation by the given angle about the x-axis
   * @param angle The rotation angle 
   */
  inline SpinOneLorentzRotation & setRotateX (double angle);

  /**
   * Specify a rotation by the given angle about the y-axis
   * @param angle The rotation angle 
   */
  inline SpinOneLorentzRotation & setRotateY (double angle);

  /**
   * Specify a rotation by the given angle about the z-axis
   * @param angle The rotation angle 
   */
  inline SpinOneLorentzRotation & setRotateZ (double angle);
  
  //@}

  /** @name Access methods for the components of the spin-1 rotation */
  //@{

  /**
   *   The xx component
   */
  inline double xx() const;

  /**
   *   The xy component
   */
  inline double xy() const;

  /**
   *   The xz component
   */
  inline double xz() const;

  /**
   *   The xt component
   */
  inline double xt() const;

  /**
   *   The yx component
   */
  inline double yx() const;

  /**
   *   The yy component
   */
  inline double yy() const;

  /**
   *   The yz component
   */
  inline double yz() const;

  /**
   *   The yt component
   */
  inline double yt() const;

  /**
   *   The zx component
   */
  inline double zx() const;

  /**
   *   The zy component
   */
  inline double zy() const;

  /**
   *   The zz component
   */
  inline double zz() const;

  /**
   *   The zt component
   */
  inline double zt() const;

  /**
   *   The tx component
   */
  inline double tx() const;

  /**
   *   The ty component
   */
  inline double ty() const;

  /**
   *   The tz component
   */
  inline double tz() const;

  /**
   *   The tt component
   */
  inline double tt() const;
  //@}

  /** @name Transformation and product members */
  //@{

  /**
   * Product with a LorentzVector simply returns the rotated vector.
   */
  template <typename Value>
  inline LorentzVector<Value>
  operator*(const LorentzVector<Value> & lv) const;

  /**
   * Product with a Lorentz5Vector simply returns the rotated vector.
   */
  template <typename Value>
  inline Lorentz5Vector<Value>
  operator*(const Lorentz5Vector<Value> & lv) const;

  /**
   * Product of two LorentzRotations (this) * lt - matrix multiplication  
   * @param lt The LorentzRotation we are multiplying
   */
  inline SpinOneLorentzRotation operator * (const SpinOneLorentzRotation & lt) const;

  /**
   * Multiply by and assign a*=b becomes a= a*b
   */
  inline  SpinOneLorentzRotation & operator *= (const SpinOneLorentzRotation & );

  /**
   *  Transform  (similar to *= but a.transform(b) becomes a = b*a
   */
  inline  SpinOneLorentzRotation & transform   (const SpinOneLorentzRotation & );

  /**
   * Rotation around the x-axis; equivalent to LT = RotationX(delta) * LT
   */
  inline SpinOneLorentzRotation & rotateX(double delta);

  /**
   * Rotation around the y-axis; equivalent to LT = RotationY(delta) * LT
   */
  inline SpinOneLorentzRotation & rotateY(double delta);

  /**
   * Rotation around the z-axis; equivalent to LT = RotationZ(delta) * LT
   */
  inline SpinOneLorentzRotation & rotateZ(double delta);
  
  /**
   *  Rotation around specified vector - LT = Rotation(delta,axis)*LT
   */
  inline SpinOneLorentzRotation & rotate(double delta, const Axis & axis);

  /**
   * Pure boost along the x-axis; equivalent to LT = BoostX(beta) * LT
   */
  inline SpinOneLorentzRotation & boostX(double beta);

  /**
   * Pure boost along the y-axis; equivalent to LT = BoostX(beta) * LT
   */
  inline SpinOneLorentzRotation & boostY(double beta);

  /**
   * Pure boost along the z-axis; equivalent to LT = BoostX(beta) * LT
   */
  inline SpinOneLorentzRotation & boostZ(double beta);

  /**
   *  boost equivalent to LT = Boost(bx,by,bz) * LT
   * @param bx The x-component of the boost
   * @param by The y-component of the boost
   * @param bz The z-component of the boost
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  inline SpinOneLorentzRotation & boost(double bx, double by, double bz,
					double gamma=-1.);

  /**
   *  boost equivalent to LT = Boost(bv) * LT
   * @param bv The boost vector
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  inline SpinOneLorentzRotation & boost(const Boost & bv, double gamma=-1.);
  //@}

private:

  template<typename Value> friend class Helicity::LorentzTensor;
  template<typename Value> friend class Helicity::LorentzRSSpinor;
  template<typename Value> friend class Helicity::LorentzRSSpinorBar;

  std::valarray<double> matrix_;

  inline SpinOneLorentzRotation (double xx, double xy, double xz, double xt,
				 double yx, double yy, double yz, double yt,
				 double zx, double zy, double zz, double zt,
				 double tx, double ty, double tz, double tt);

  inline double operator()(unsigned int i, unsigned int j) const {
    return matrix_[4*i + j];
  }

  inline double & xx_() { return matrix_[ 0]; }
  inline double & xy_() { return matrix_[ 1]; }
  inline double & xz_() { return matrix_[ 2]; }
  inline double & xt_() { return matrix_[ 3]; }

  inline double & yx_() { return matrix_[ 4]; }
  inline double & yy_() { return matrix_[ 5]; }
  inline double & yz_() { return matrix_[ 6]; }
  inline double & yt_() { return matrix_[ 7]; }

  inline double & zx_() { return matrix_[ 8]; }
  inline double & zy_() { return matrix_[ 9]; }
  inline double & zz_() { return matrix_[10]; }
  inline double & zt_() { return matrix_[11]; }

  inline double & tx_() { return matrix_[12]; }
  inline double & ty_() { return matrix_[13]; }
  inline double & tz_() { return matrix_[14]; }
  inline double & tt_() { return matrix_[15]; }
};


/**
 *  Global method to get the inverse
 */
inline SpinOneLorentzRotation inverseOf ( const SpinOneLorentzRotation & lt );

/**
 *  output operator
 */
inline std::ostream & operator<< ( std::ostream & os,
				   const  SpinOneLorentzRotation& lt ) {
  return lt.print(os);
}

}

#include "SpinOneLorentzRotation.icc"



#endif /* ThePEG_SpinOneLorentzRotation_H */
