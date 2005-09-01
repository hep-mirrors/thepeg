#ifndef ThePEG_Lorentz5Vector_H
#define ThePEG_Lorentz5Vector_H

// This is the declaration of the Lorentz5vector class.

#include "LorentzVector.h"
#include "Lorentz5Vector.fh"
#include "ThePEG/Utilities/Math.h"
#include "ThePEG/Utilities/Direction.h"
#include "ThePEG/Utilities/UnitIO.h"
#include "LorentzRotation.h"

namespace ThePEG {

template <typename FloatType>
/**
 * The Lorentz5Vector inherits from the
 * <code>LorentzVector</code> class of CLHEP. It is templated on the
 * type of the member variables, anticipating a similar strategy in
 * CLHEP in the future. The <code>Lorentz5Vector</code> class is a
 * <code>LorentzVector</code> with an extra member for the invariant
 * length/mass of the vector. Note that an object of the
 * <code>Lorentz5Vector</code> class may be internally inconsistent in
 * that the invariant length/mass of the <code>LorentzVector</code>
 * class need not be the same as the member variable representing the
 * invariant length/mass. The degree of inconsistency can be accessed
 * with the <code>massError()</code>, <code>energyError()</code> and
 * <code>rhoError()</code> methods and an object can be made consistent
 * using the <code>rescaleMass()</code>, <code>rescaleEnergy()</code> or
 * <code>rescaleRho()</code> methods.
 *
 * @see Math
 * 
 */
class Lorentz5Vector: public LorentzVector {

public:

  /** Template argument typedef. */
  typedef FloatType FloatType2;

public:

  /** @name Constructors and destructor. */
  //@{
  /**
   * Constructor giving the null vector.
   */
  inline Lorentz5Vector();

  /**
   * Constructor giving the invariant length.
   */
  inline Lorentz5Vector(FloatType m);

  /**
   * Constructor giving the components x, y, z, t. The invariant
   * length is set to LorentzVector::mag().
   */
  inline Lorentz5Vector(FloatType x, FloatType y,
			FloatType z, FloatType t = FloatType());

  /**
   * Constructor giving the components x, y, z, t and invariant length.
   * May result in an inconsistent Lorentz5Vector.
   */
  inline Lorentz5Vector(FloatType x, FloatType y, FloatType z,
			FloatType t, FloatType tau);

  /**
   * Constructor giving a 3-Vector and a time component. The invariant
   * length is set to LorentzVector::mag().
   */
  inline Lorentz5Vector(const Vector3 &, FloatType);

  /**
   * Constructor giving an invariant length and a 3-Vector
   * component. The time component is set to the corresponding value.
   */
  inline Lorentz5Vector(FloatType, const Vector3 &);

  /**
   * Constructor giving a 3-Vector, a time component and an invariant
   * length. May result in an inconsistent Lorentz5Vector.
   */
  inline Lorentz5Vector(const Vector3 &, FloatType t, FloatType tau);

  /**
   * Constructor giving a LorentzVector and an invariant length.
   * May result in an inconsistent Lorentz5Vector.
   */
  inline Lorentz5Vector(const LorentzVector &, FloatType);

  /**
   * Copy constructor.
   */
  inline Lorentz5Vector(const Lorentz5Vector &);

  /**
   * Copy from HepLorentzVector constructor. The invariant
   * length is set to LorentzVector::mag().
   */
  inline Lorentz5Vector(const LorentzVector &);

  /**
   * The destructor.
   */
  inline ~Lorentz5Vector();
  //@}

  /** @name Assignment and set functions. */
  //@{
  /**
   * Set invariant length/mass.
   */
  inline void setTau(FloatType);

  /**
   * Set invariant length/mass.
   */
  inline void setMass(FloatType);

  /**
   * Assignment. 
   */
  inline Lorentz5Vector & operator=(const Lorentz5Vector &);

  /**
   * Assignment. The invariant length is kept fixed. May result in an
   * inconsistent Lorentz5Vector.
   */
  inline Lorentz5Vector & operator=(const LorentzVector &);
  //@}

  /** @name Rescale functions to make consistent. */
  //@{
  /**
   * Rescale energy, so that the invariant length/mass of the
   * LorentzVector agrees with the current one.
   */
  inline void rescaleEnergy();

  /**
   * Rescale spatial component, so that the invariant length/mass of
   * the LorentzVector agrees with the current one.
   */
  inline void rescaleRho();

  /**
   * Set the invariant length/mass member, so that it agrees with the
   * invariant length/mass of the LorentzVector.
   */
  inline void rescaleMass();
  //@}

  /** @name Check consistency. */
  //@{
  /**
   * Return the relative inconsistency in the mass component.
   */
  inline FloatType massError() const;

  /**
   * Return the relative inconsistency in the energy component.
   */
  inline FloatType energyError() const;

  /**
   * Return the relative inconsistency in the spatial components.
   */
  inline FloatType rhoError() const;
  //@}

  /** @name Access components. */
  //@{
  /**
   * Get components by index. The invariant length/mass member is
   * accessed with index 5.
   */
  inline FloatType operator()(int) const;

  /**
   * Get components by index. The invariant length/mass member is
   * accessed with index 5.
   */
  inline FloatType operator[](int) const;

  /**
   * Mass/invariant length component squared. mag2() and m2() gives
   * the same calculated from the LorentzVector
   */
  inline FloatType2 mass2() const;

  /**
   * Mass/invariant length component squared. mag2() and m2() gives
   * the same calculated from the LorentzVector
   */
  inline FloatType2 tau2() const;

  /**
   * Mass/invariant length component. mag() and m() gives the same
   * calculated from the LorentzVector
   */
  inline FloatType mass() const;

  /**
   * Mass/invariant length component. mag() and m() gives the same
   * calculated from the LorentzVector
   */
  inline FloatType tau() const;

  /**
   * Return the positive negative light-cone components (depending on
   * the value of Direction<0>.
   */
  inline FloatType dirPlus() const;

  /**
   * Return the positive negative light-cone components (depending on
   * the value of Direction<0>.
   */
  inline FloatType dirMinus() const;
  //@}

  /**
   *  Perform a Lorentz transformation
   */
  inline Lorentz5Vector & transform(const LorentzRotation &);

private:

  /** The invariant mass/length member. */
  FloatType mm;

};

/** Output a Lorentz5Vector to a stream. */
template <typename OStream, typename T, typename UT>
void ounitstream(OStream & os, const Lorentz5Vector<T> & p, UT & u) {
  os << ounit(p.x(), u) << ounit(p.y(), u) << ounit(p.z(), u)
     << ounit(p.e(), u) << ounit(p.mass(), u);
}

/** Input a Lorentz5Vector from a stream. */
template <typename IStream, typename T, typename UT>
void iunitstream(IStream & is, Lorentz5Vector<T> & p, UT & u) {
  T x, y, z, e, mass;
  is >> iunit(x, u) >> iunit(y, u) >> iunit(z, u) >> iunit(e, u)
     >> iunit(mass, u);
  p = Lorentz5Vector<T>(x, y, z, e, mass);
}

}

#include "Lorentz5Vector.icc"

#endif /* ThePEG_Particle_H */
