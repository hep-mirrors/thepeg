// -*- C++ -*-
//
// Transverse.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_Transverse_H
#define ThePEG_Transverse_H
// This is the declaration of the Transverse class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Vectors/Lorentz5Vector.h"
#include "Transverse.fh"
// #include "Transverse.xh"

namespace ThePEG {

/**
 * Transverse represents the transverse components of a
 * LorentzVector. It inherits from
 * <code>std::pair<Value,Value></code> and can be used
 * anywhere such a pair is called for. It can also be created directly
 * from a <code>Vector3</code>, <code>LorentzVector</code> and
 * <code>Lorentz5Momentum</code>.
 *
 * @see Lorentz5Vector
 */
template <typename Value>
class Transverse: public pair<Value,Value> {

public:

  /** Template argument typedef. */
  typedef typename BinaryOpTraits<Value,Value>::MulT Value2;
  /** Template argument typedef. */
  typedef pair<Value,Value> BasePair;

public:

  /** @name Constructors. */
  //@{
  /**
   * Default constructor.
   */
  inline Transverse();

  /**
   * Constructor from underlying representation.
   */
  inline Transverse(const BasePair &);

  /**
   * Constructor from x and y components.
   */
  inline Transverse(Value x, Value y);

  /**
   * Constructor taking the transverse parts of a Vector3.
   */
  inline Transverse(const Vector3<Value> &);

  /**
   * Constructor taking the transverse parts of a LorentzVector.
   */
  inline Transverse(const LorentzVector<Value> &);

  /**
   * Constructor taking the transverse parts of a Lorentz5Vector.
   */
  inline Transverse(const Lorentz5Vector<Value> &);
  //@}

  /** @name Assignment operators. */
  //@{
  /**
   * Assignment from underlying representation.
   */
  inline const Transverse & operator=(const BasePair &);

  /**
   * Assignment taking the transverse parts of a Vector3.
   */
  inline const Transverse & operator=(const Vector3<Value> &);

  /**
   * Assignment taking the transverse parts of a LorentzVector.
   */
  inline const Transverse & operator=(const LorentzVector<Value> &);

  /**
   * Assignment taking the transverse parts of a Lorentz5Vector.
   */
  inline const Transverse & operator=(const Lorentz5Vector<Value> &);
  //@}

  /** @name Arithmetric operations */
  //@{
  /**
   * Unary minus.
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
  inline Value x() const;

  /**
   * The y-component.
   */
  inline Value y() const;

  /**
   * The magnitude squared.
   */
  inline Value2 pt2() const;

  /**
   * The magnitude.
   */
  inline Value pt() const;

  /**
   * The azimuth angle.
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
