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
  Transverse() : BasePair(Value(), Value()) {}

  /**
   * Constructor from underlying representation.
   */
  Transverse(const BasePair & p) : BasePair(p) {}

  /**
   * Constructor from x and y components.
   */
  Transverse(Value x, Value y) : BasePair(x, y) {}

  /**
   * Constructor taking the transverse parts of a Vector3.
   */
  Transverse(const Vector3<Value> & p) : BasePair(p.x(), p.y()) {}

  /**
   * Constructor taking the transverse parts of a LorentzVector.
   */
  Transverse(const LorentzVector<Value> & p) : BasePair(p.x(), p.y()) {}

  /**
   * Constructor taking the transverse parts of a Lorentz5Vector.
   */
  Transverse(const Lorentz5Vector<Value> & p) : BasePair(p.x(), p.y()) {}
  //@}

  /** @name Assignment operators. */
  //@{
  /**
   * Assignment from underlying representation.
   */
  const Transverse & operator=(const BasePair & p) {
    BasePair::operator=(p);
    return *this;
  }

  /**
   * Assignment taking the transverse parts of a Vector3.
   */
  const Transverse & operator=(const Vector3<Value> & p) {
    BasePair::operator=(BasePair(p.x(), p.y()));
    return *this;
  }

  /**
   * Assignment taking the transverse parts of a LorentzVector.
   */
  const Transverse & operator=(const LorentzVector<Value> & p) {
    BasePair::operator=(BasePair(p.x(), p.y()));
    return *this;
  }

  /**
   * Assignment taking the transverse parts of a Lorentz5Vector.
   */
  const Transverse & operator=(const Lorentz5Vector<Value> & p) { 
    BasePair::operator=(BasePair(p.x(), p.y()));
    return *this;
  }

  //@}

  /** @name Arithmetric operations */
  //@{
  /**
   * Unary minus.
   */
  Transverse operator-() const { return Transverse(-x(), -y()); }

  /**
   * Binary minus.
   */
  Transverse operator-(const Transverse & pt) const { 
    return Transverse(x() - pt.x(), y() - pt.y()); 
  }

  /**
   * Assign-subtract.
   */
  Transverse & operator-=(const Transverse & pt) {
    BasePair::first -= pt.x();
    BasePair::second -= pt.y();
    return *this;
  }

  /**
   * Addition.
   */
  Transverse operator+(const Transverse &) const {
    return Transverse(x() + pt.x(), y() + pt.y());
  }

  /**
   * Assign-add.
   */
  Transverse & operator+=(const Transverse &) {
    BasePair::first += pt.x();
    BasePair::second += pt.y();
    return *this;
  }
  //@}

  /** @name Access coordinates. */
  //@{
  /**
   * The x-component.
   */
  Value x() const { return BasePair::first; }

  /**
   * The y-component.
   */
  Value y() const { return BasePair::second; }

  /**
   * The magnitude squared.
   */
  Value2 pt2() const { return sqr(x()) + sqr(y()); }

  /**
   * The magnitude.
   */
  Value pt() const { return sqrt(pt2()); }

  /**
   * The azimuth angle.
   */
  double phi() const { return atan2(y(), x()); }
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

#endif /* ThePEG_Transverse_H */
