// -*- C++ -*-
#ifndef ThePEG_Transverse_H
#define ThePEG_Transverse_H
// This is the declaration of the Transverse class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/CLHEPWrap/Lorentz5Vector.h"
#include "Transverse.fh"
// #include "Transverse.xh"

namespace ThePEG {

/**
 * Transverse represents the transverse components of a
 * LorentzVector. It inherits from
 * <code>std::pair<FloatType,FloatType></code> and can be used
 * anywhere such a pair is called for. It can also be created directly
 * from a <code>Vector3</code>, <code>LorentzVector</code> and
 * <code>Lorentz5Momentum</code>.
 *
 * @see Lorentz5Vector,
 */
template <typename FloatType>
class Transverse: public pair<FloatType,FloatType> {

public:

  /** Template argument typedef. */
  typedef FloatType FloatType2;
  /** Template argument typedef. */
  typedef pair<FloatType,FloatType> BasePair;

public:

  /** @name Constructors. */
  //@{
  /**
   * Default constructor.
   */
  inline Transverse();

  /**
   * Copy constructor.
   */
  inline Transverse(const Transverse &);

  /**
   * Constructor from underlying representation.
   */
  inline Transverse(const BasePair &);

  /**
   * Constructor from x and y components.
   */
  inline Transverse(FloatType x, FloatType y);

  /**
   * Constructor taking the transverse parts of a Vector3.
   */
  inline Transverse(const Vector3 &);

  /**
   * Constructor taking the transverse parts of a LorentzVector.
   */
  inline Transverse(const LorentzVector &);

  /**
   * Constructor taking the transverse parts of a Lorentz5Vector.
   */
  inline Transverse(const Lorentz5Vector<FloatType> &);
  //@}

  /** @name Assignment operators. */
  //@{
  /**
   * Assignment.
   */
  inline const Transverse & operator=(const Transverse &);

  /**
   * Assignment from underlying representation.
   */
  inline const Transverse & operator=(const BasePair &);

  /**
   * Assignment taking the transverse parts of a Vector3.
   */
  inline const Transverse & operator=(const Vector3 &);

  /**
   * Assignment taking the transverse parts of a LorentzVector.
   */
  inline const Transverse & operator=(const LorentzVector &);

  /**
   * Assignment taking the transverse parts of a Lorentz5Vector.
   */
  inline const Transverse & operator=(const Lorentz5Vector<FloatType> &);
  //@}

  /** @name Arithmetric operations */
  //@{
  /**
   * Unary minus..
   */
  inline Transverse operator-() const;

  /**
   * Binary minus.
   */
  inline Transverse operator-(const Transverse &) const;

  /**
   * Assign-subtract.
   */
  inline Transverse & operator-=(const Transverse &);

  /**
   * Addition.
   */
  inline Transverse operator+(const Transverse &) const;

  /**
   * Assign-add.
   */
  inline Transverse & operator+=(const Transverse &);
  //@}

  /** @name Access coordinates. */
  //@{
  /**
   * The x-component.
   */
  inline FloatType x() const;

  /**
   * The y-component.
   */
  inline FloatType y() const;

  /**
   * The magnitude squared.
   */
  inline FloatType2 pt2() const;

  /**
   * The magnitude.
   */
  inline FloatType pt() const;

  /**
   * The azimuth angle..
   */
  inline double phi() const;
  //@}

};

/** Output a Transverse with units to a stream. */
template <typename OStream, typename T, typename UT>
void ounitstream(OStream & os, const Transverse<T> & p, UT & u) {
  os << ounit(p.x(), u) << ounit(p.y(), u);
}

/** Input a Transverse with units from a stream. */
template <typename IStream, typename T, typename UT>
void iunitstream(IStream & is, Transverse<T> & p, UT & u) {
  T x, y;
  is >> iunit(x, u) >> iunit(y, u);
  p = Transverse<T>(x, y);
}

}

#include "Transverse.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Transverse.tcc"
#endif

#endif /* ThePEG_Transverse_H */
