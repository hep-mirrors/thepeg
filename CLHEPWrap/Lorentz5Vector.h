#ifndef ThePEG_Lorentz5Vector_H
#define ThePEG_Lorentz5Vector_H

// This is the declaration of the Lorentz5vector class.
//
// The <!id>Lorentz5Vector<!!id> inherits from the
// <!id>LorentzVector<!!id> class of CLHEP. It is templated on the
// type of the member variables, anticipating a similar strategy in
// CLHEP in the future. The <!id>Lorentz5Vector<!!id> class is a
// <!id>LorentzVector<!!id> with an extra member for the invariant
// length/mass of the vector. Note that an object of the
// <!id>Lorentz5Vector<!!id> class may be internally inconsistent in
// that the invariant length/mass of the <!id>LorentzVector<!!id>
// class need not be the same as the member variable representing the
// invariant length/mass. The degree of inconsistency can be accessed
// with the <!id>massError()<!!id>, <!id>energyError()<!!id> and
// <!id>rhoError()<!!id> methods and an object can be made consistent
// using the <!id>rescaleMass()<!!id>, <!id>rescaleEnergy()<!!id> or
// <!id>rescaleRho()<!!id> methods.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Math.html">Math.h</a>
// 

#include "LorentzVector.h"
#include "Lorentz5Vector.fh"
#include "ThePEG/Utilities/Math.h"
#include "ThePEG/Utilities/Direction.h"
#include "ThePEG/Utilities/UnitIO.h"

namespace ThePEG {

template <typename FloatType>
class Lorentz5Vector: public LorentzVector {

public:

  typedef FloatType FloatType2;

public:

  inline Lorentz5Vector();
  // Constructor giving the null vector.

  inline Lorentz5Vector(FloatType m);
  // Constructor giving the invariant length.

  inline Lorentz5Vector(FloatType x, FloatType y,
			FloatType z, FloatType t = FloatType());
  // Constructor giving the components x, y, z, t. The invariant
  // length is set to LorentzVector::mag().

  inline Lorentz5Vector(FloatType x, FloatType y, FloatType z,
			FloatType t, FloatType tau);
  // Constructor giving the components x, y, z, t and invariant length.
  // May result in an inconsistent Lorentz5Vector.

  inline Lorentz5Vector(const Vector3 &, FloatType);
  // Constructor giving a 3-Vector and a time component. The invariant
  // length is set to LorentzVector::mag().

  inline Lorentz5Vector(FloatType, const Vector3 &);
  // Constructor giving an invariant length and a 3-Vector
  // component. The time component is set to the corresponding value.

  inline Lorentz5Vector(const Vector3 &, FloatType t, FloatType tau);
  // Constructor giving a 3-Vector, a time component and an invariant
  // length. May result in an inconsistent Lorentz5Vector.

  inline Lorentz5Vector(const LorentzVector &, FloatType);
  // Constructor giving a LorentzVector and an invariant length.
  // May result in an inconsistent Lorentz5Vector.

  inline Lorentz5Vector(const Lorentz5Vector &);
  // Copy constructor.

  inline Lorentz5Vector(const LorentzVector &);
  // Copy from HepLorentzVector constructor. The invariant
  // length is set to LorentzVector::mag().

  inline ~Lorentz5Vector();
  // The destructor.

  inline void setTau(FloatType);
  inline void setMass(FloatType);
  // Set invariant length/mass.

  inline void rescaleEnergy();
  // Rescale energy, so that the invariant length/mass of the
  // LorentzVector agrees with the current one.

  inline void rescaleRho();
  // Rescale spatial component, so that the invariant length/mass of
  // the LorentzVector agrees with the current one.

  inline void rescaleMass();
  // Set the invariant length/mass member, so that it agrees with the
  // invariant length/mass of the LorentzVector.

  inline FloatType massError() const;
  inline FloatType energyError() const;
  inline FloatType rhoError() const;
  // Return the relative inconsistency in the mass, energy or spatial
  // components.

  inline FloatType operator()(int) const;
  inline FloatType operator[](int) const;
  // Get components by index. The invariant length/mass member is
  // accessed with index 5.

  inline Lorentz5Vector & operator=(const Lorentz5Vector &);
  // Assignment. 

  inline Lorentz5Vector & operator=(const LorentzVector &);
  // Assignment. The invariant length is kept fixed. May result in an
  // inconsistent Lorentz5Vector.

  inline FloatType2 mass2() const;
  inline FloatType2 tau2() const;
  // Mass/invariant length component squared. mag2() and m2() gives
  // the same calculated from the LorentzVector

  inline FloatType mass() const;
  inline FloatType tau() const;
  // Mass/invariant length component. mag() and m() gives the same
  // calculated from the LorentzVector

  inline FloatType dirPlus() const;
  inline FloatType dirMinus() const;
  // Return the positive negative light-cone components (depending on
  // the value of Direction<0>.

private:

  FloatType mm;

};

template <typename OStream, typename T, typename UT>
void ounitstream(OStream & os, const Lorentz5Vector<T> & p, UT & u) {
  os << ounit(p.x(), u) << ounit(p.y(), u) << ounit(p.z(), u)
     << ounit(p.e(), u) << ounit(p.mass(), u);
}

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
