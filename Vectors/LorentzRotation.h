// -*- C++ -*-
#ifndef THEPEG_LorentzRotation_H
#define THEPEG_LorentzRotation_H
//
// This is the declaration of the LorentzRotation class.
//
#include "SpinOneLorentzRotation.h"
#include "SpinHalfLorentzRotation.h"
#include "LorentzRotation.fh"

namespace ThePEG {

/**
 * The LorentzRotation class combine a SpinOneLorentzRotation and a 
 * spin SpinHalfLorentzRotation to provide members which can perform the
 * Lorentz transformation of any object. The class ensures that the 
 * two transformations are consistent by only allowing transformations
 * to be made to both the spin-1 and spin-\f$\frac12\f$ members. 
 */
class LorentzRotation {

  /**
   * The external inverseOf needs to be a friend
   */
  friend LorentzRotation inverseOf ( const LorentzRotation & lt );

public:

  /** @name Constructors and destructor. */
  //@{

  /**
   * Default constructor. Gives a unit matrix.
   */
  inline LorentzRotation();

  /**
   *  Copy constructor
   */
  inline LorentzRotation(const LorentzRotation &);

  /**
   * Constructor giving the components of a Lorentz boost.
   * @param bx The x-component of the boost
   * @param by The y-component of the boost
   * @param bz The z-component of the boost
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  inline LorentzRotation (double bx, double by, double bz, double gamma=-1.);

  /**
   * Constructor giving the vector for a Lorentz boost.
   * @param b The boost vector 
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  inline LorentzRotation (const Boost & b, double gamma=-1.);

  /**
   * The destructor.
   */
  ~LorentzRotation();
  //@}

  /**
   *  Assignment operator
   */
  inline LorentzRotation & operator = (const LorentzRotation & );

  /**
   * Returns true if the Identity matrix.
   */
  inline bool isIdentity() const;

  /**
   * Return the inverse.
   */
  LorentzRotation inverse() const;

  /**
   * Inverts the LorentzRotation matrix.
   */
  inline LorentzRotation & invert();

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
   */
  LorentzRotation & setBoost (double bx, double by, double bz, double gamma=-1.);

  /**
   * Specify a Lorentz Boost as a vector
   * @param b The boost vector
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  LorentzRotation & setBoost (const Boost & b, double gamma=-1.);

  /**
   * Specify a boost by the given factor along the x-axis
   * @param boost The Lorentz boost  
   */
  inline LorentzRotation & setBoostX (double boost);

  /**
   * Specify a boost by the given factor along the y-axis
   * @param boost The Lorentz boost  
   */
  inline LorentzRotation & setBoostY (double boost);

  /**
   * Specify a boost by the given factor along the z-axis
   * @param boost The Lorentz boost  
   */
  inline LorentzRotation & setBoostZ (double boost);

  /**
   * Specify a rotation about a general axis by the angle given.
   * @param delta The angle
   * @param axis The axis
   */
  inline LorentzRotation & setRotate(double delta, const Axis & axis);

  /**
   * Specify a rotation by the given angle about the x-axis
   * @param angle The rotation angle 
   */
  inline LorentzRotation & setRotateX (double angle);

  /**
   * Specify a rotation by the given angle about the y-axis
   * @param angle The rotation angle 
   */
  inline LorentzRotation & setRotateY (double angle);

  /**
   * Specify a rotation by the given angle about the z-axis
   * @param angle The rotation angle 
   */
  inline LorentzRotation & setRotateZ (double angle);
  
  //@}

  /** @name Methods to return the spin-\f$\frac12\f$ and spin-1 transformations */
  //@{

  /**
   * The spin-\f$\frac12\f$ transformation
   */
  inline const SpinHalfLorentzRotation & half() const;

  /**
   * The spin-1 transformation
   */
  inline const SpinOneLorentzRotation & one() const;

  /**
   * Automatically cast to the spin-1 transformation
   */
  inline operator const SpinOneLorentzRotation & () const;
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

  /** @name Access methods for the components of the spin-\f$\frac12\f$ rotation */
  //@{
  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s1s1() const;

  /**
   *   The \f$(1,2)\f$ component
   */
  inline Complex s1s2() const;

  /**
   *   The \f$(1,3)\f$ component
   */
  inline Complex s1s3() const;

  /**
   *   The \f$(1,4)\f$ component
   */
  inline Complex s1s4() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s2s1() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s2s2() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s2s3() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s2s4() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s3s1() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s3s2() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s3s3() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s3s4() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s4s1() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s4s2() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s4s3() const;

  /**
   *   The \f$(1,1)\f$ component
   */
  inline Complex s4s4() const;
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
  inline LorentzRotation operator * (const LorentzRotation & lt) const;

  /**
   * Multiply by and assign a*=b becomes a= a*b
   */
  inline  LorentzRotation & operator *= (const LorentzRotation & );

  /**
   *  Transform  (similar to *= but a.transform(b) becomes a = b*a
   */
  inline  LorentzRotation & transform   (const LorentzRotation & );

  /**
   * Rotation around the x-axis; equivalent to LT = RotationX(delta) * LT
   */
  inline LorentzRotation & rotateX(double delta);

  /**
   * Rotation around the y-axis; equivalent to LT = RotationY(delta) * LT
   */
  inline LorentzRotation & rotateY(double delta);

  /**
   * Rotation around the z-axis; equivalent to LT = RotationZ(delta) * LT
   */
  inline LorentzRotation & rotateZ(double delta);
  
  /**
   *  Rotation around specified vector - LT = Rotation(delta,axis)*LT
   */
  inline LorentzRotation & rotate(double delta, const Axis & axis);

  /**
   * Pure boost along the x-axis; equivalent to LT = BoostX(beta) * LT
   */
  LorentzRotation & boostX(double beta);

  /**
   * Pure boost along the y-axis; equivalent to LT = BoostX(beta) * LT
   */
  LorentzRotation & boostY(double beta);

  /**
   * Pure boost along the z-axis; equivalent to LT = BoostX(beta) * LT
   */
  LorentzRotation & boostZ(double beta);

  /**
   *  boost equivalent to LT = Boost(bx,by,bz) * LT
   * @param bx The x-component of the boost
   * @param by The y-component of the boost
   * @param bz The z-component of the boost
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  LorentzRotation & boost(double bx, double by, double bz, double gamma=-1.);

  /**
   *  boost equivalent to LT = Boost(bv) * LT
   * @param bv The boost
   * @param gamma The \f$\gamma\f$ factor (optional)
   */
  LorentzRotation & boost(const Boost & bv, double gamma=-1.);
  //@}

private:

  /**
   *  The spin-\f$\frac12\f$ rotation
   */
  SpinHalfLorentzRotation _half;

  /**
   *  The spin-1 rotation
   */
  SpinOneLorentzRotation _one;

};

/**
 *  Global method to get the inverse
 */
inline LorentzRotation inverseOf ( const LorentzRotation & lt );

/**
 *  output operator
 */
inline std::ostream & operator<< ( std::ostream & os,
				   const  LorentzRotation& lt ) 
{return lt.print(os);}

}

#include "LorentzRotation.icc"

#endif /* THEPEG_LorentzRotation_H */

