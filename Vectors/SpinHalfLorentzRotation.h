// -*- C++ -*-
#ifndef THEPEG_SpinHalfLorentzRotation_H
#define THEPEG_SpinHalfLorentzRotation_H
//
// This is the declaration of the SpinHalfLorentzRotation class.
//
#include "ThePEG/Helicity/HelicityDefinitions.h"
#include "ThreeVector.h"

namespace ThePEG {

using ThePEG::Helicity::HELASDRep;
using ThePEG::Helicity::HaberDRep;
using ThePEG::Helicity::defaultDRep;

/**
 * The SpinHalfLorentzRotation class is designed to offer the same
 * features as the HepLorentzRotation class of CLHEP but for the spin-\f$\frac12\f$
 * Lorentz transformation. This is then combined into the general LorentzRotation
 * class of ThePEG to provide the Lorentz transformation for any object as the
 * transformations for higher spin objects can be built from the spin-\f$\frac12\f$
 * and spin-1 transformations.
 *
 * The boost matrix is calculated using the default Dirac matrix representation.
 * Any conversion to other Dirac matrix representations must be handled when the
 * transformation is used.
 */
class SpinHalfLorentzRotation {

  /**
   * The external inverseOf needs to be a friend
   */
  friend SpinHalfLorentzRotation inverseOf ( const SpinHalfLorentzRotation & lt );

public:

  /** @name Constructors and destructor. */
  //@{

  /**
   * Default constructor. Gives a unit matrix.
   */
  inline SpinHalfLorentzRotation();

  /**
   *  Copy constructor
   */
  inline SpinHalfLorentzRotation(const SpinHalfLorentzRotation &);

  /**
   * Constructor giving the components of a Lorentz boost.
   * @param bx The x-component of the boost
   * @param by The y-component of the boost
   * @param bz The z-component of the boost
   */
  inline SpinHalfLorentzRotation (double bx, double by, double bz);

  /**
   * Constructor giving the vector for a Lorentz boost.
   * @param b The boost vector
   */
  inline SpinHalfLorentzRotation (const Boost & b);

  /**
   * The destructor.
   */
  ~SpinHalfLorentzRotation();
  //@}

  /**
   *  Assignment operator
   */
  inline SpinHalfLorentzRotation & operator = (const SpinHalfLorentzRotation & );

  /**
   * Returns true if the Identity matrix.
   */
  inline bool isIdentity() const;

  /**
   * Return the inverse.
   */
  SpinHalfLorentzRotation inverse() const;

  /**
   * Inverts the SpinHalfLorentzRotation matrix.
   */
  inline SpinHalfLorentzRotation & invert();

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
  SpinHalfLorentzRotation & setBoost (double bx, double by, double bz);

  /**
   * Specify a Lorentz Boost as a vector
   * @param b The boost vector
   */
  SpinHalfLorentzRotation & setBoost (const Boost & b);

  /**
   * Specify a boost by the given factor along the x-axis
   * @param boost The Lorentz boost  
   */
  SpinHalfLorentzRotation & setBoostX (double & boost);

  /**
   * Specify a boost by the given factor along the y-axis
   * @param boost The Lorentz boost  
   */
  SpinHalfLorentzRotation & setBoostY (double & boost);

  /**
   * Specify a boost by the given factor along the z-axis
   * @param boost The Lorentz boost  
   */
  SpinHalfLorentzRotation & setBoostZ (double & boost);

  /**
   * Specify a rotation about a general axis by the angle given.
   * @param delta The angle
   * @param axis The axis
   */
  inline SpinHalfLorentzRotation & setRotate(double delta, const Axis & axis);

  /**
   * Specify a rotation by the given angle about the x-axis
   * @param angle The rotation angle 
   */
  inline SpinHalfLorentzRotation & setRotateX (double & angle);

  /**
   * Specify a rotation by the given angle about the y-axis
   * @param angle The rotation angle 
   */
  inline SpinHalfLorentzRotation & setRotateY (double & angle);

  /**
   * Specify a rotation by the given angle about the z-axis
   * @param angle The rotation angle 
   */
  inline SpinHalfLorentzRotation & setRotateZ (double & angle);
  
  //@}


  /** @name Access methods for the components */
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

  /**
   *  Fortran style subscript operator
   */
  inline Complex operator () (unsigned int,unsigned int) const;
  //@}


  /** @name Transformation and product members */
  //@{

  /**
   * Product of two SpinHalfLorentzRotations (this) * lt - matrix multiplication  
   * @param lt The SpinHalfLorentzRotation we are multiplying
   */
  inline SpinHalfLorentzRotation operator * (const SpinHalfLorentzRotation & lt) const;

  /**
   * Multiply by and assign a*=b becomes a= a*b
   */
  inline  SpinHalfLorentzRotation & operator *= (const SpinHalfLorentzRotation & );

  /**
   *  Transform  (similar to *= but a.transform(b) becomes a = b*a
   */
  inline  SpinHalfLorentzRotation & transform   (const SpinHalfLorentzRotation & );

  /**
   * Rotation around the x-axis; equivalent to LT = RotationX(delta) * LT
   */
  inline SpinHalfLorentzRotation & rotateX(double delta);

  /**
   * Rotation around the y-axis; equivalent to LT = RotationY(delta) * LT
   */
  inline SpinHalfLorentzRotation & rotateY(double delta);

  /**
   * Rotation around the z-axis; equivalent to LT = RotationZ(delta) * LT
   */
  inline SpinHalfLorentzRotation & rotateZ(double delta);
  
  /**
   *  Rotation around specified vector - LT = Rotation(delta,axis)*LT
   */
  inline SpinHalfLorentzRotation & rotate(double delta, const Axis & axis);

  /**
   * Pure boost along the x-axis; equivalent to LT = BoostX(beta) * LT
   */
  SpinHalfLorentzRotation & boostX(double beta);

  /**
   * Pure boost along the y-axis; equivalent to LT = BoostX(beta) * LT
   */
  SpinHalfLorentzRotation & boostY(double beta);

  /**
   * Pure boost along the z-axis; equivalent to LT = BoostX(beta) * LT
   */
  SpinHalfLorentzRotation & boostZ(double beta);

  /**
   * General boost equivalent to LT = Boost(bx,by,bz) * LT
   */
  SpinHalfLorentzRotation & boost(double bx, double by, double bz);

  /**
   * General boost equivalent to LT = Boost(bv) * LT
   */
  SpinHalfLorentzRotation & boost(const Boost & bv);
  //@}

protected:

  /**
   *  Protected constructor giving all the members, no check it is a valid
   *  transformation
   */
  inline SpinHalfLorentzRotation(Complex s1s1,Complex s1s2,Complex s1s3,Complex s1s4,
				 Complex s2s1,Complex s2s2,Complex s2s3,Complex s2s4,
				 Complex s3s1,Complex s3s2,Complex s3s3,Complex s3s4,
				 Complex s4s1,Complex s4s2,Complex s4s3,Complex s4s4);

private:


  /**
   * The members of the transformation matrix.
   */
  Complex _mx[4][4];
};

/**
 *  Global method to get the inverse
 */
inline SpinHalfLorentzRotation inverseOf ( const SpinHalfLorentzRotation & lt );

/**
 *  output operator
 */
inline std::ostream & operator<< ( std::ostream & os,
				   const  SpinHalfLorentzRotation& lt ) 
{return lt.print(os);}

}

#include "SpinHalfLorentzRotation.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SpinHalfLorentzRotation.tcc"
#endif

#endif /* THEPEG_SpinHalfLorentzRotation_H */
