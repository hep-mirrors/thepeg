// -*- C++ -*-
//
// LorentzVector.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2006-2007 David Grellscheid, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_LorentzVector_H
#define ThePEG_LorentzVector_H

/** 
 * @file LorentzVector.h contains the LorentzVector class.  Lorentz
 * vectors can be created with any unit type as template parameter.
 * All basic mathematical operations are supported, as well as a
 * subset of the CLHEP LorentzVector functionality.
 */

#include "LorentzVector.fh"
#include "Transverse.h"
#include "ThePEG/Utilities/Direction.h"
#include "ThePEG/Utilities/UnitIO.h"
#include "LorentzRotation.h"
#include "ThreeVector.h"

namespace {
  /// Debug helper function
#ifdef NDEBUG
  inline void errorIf(bool, std::string) {}
#else
  inline void errorIf(bool condition, std::string message) {
    if ( condition )
      throw ThePEG::Exception(message, ThePEG::Exception::eventerror);
  }
#endif
}

namespace ThePEG {

template <typename Value> class LorentzVector; 

/** 
 * A 4-component Lorentz vector. It can be created with any unit type
 * as template parameter.  All basic mathematical operations are
 * supported, as well as a subset of the CLHEP LorentzVector
 * functionality.
 */
template <typename Value> class LorentzVector 
{
private:
  /// Value squared
  typedef typename BinaryOpTraits<Value,Value>::MulT Value2;

public:
  /** @name Constructors. */
  //@{
  LorentzVector() 
    : theX(), theY(), theZ(), theT() {}

  LorentzVector(Value x, Value y, Value z, Value t)
    : theX(x), theY(y), theZ(z), theT(t) {}

  LorentzVector(const Vector3<Value> & v, Value t)
    : theX(v.x()), theY(v.y()), theZ(v.z()), theT(t) {}

  template<typename U>
  LorentzVector(const LorentzVector<U> & v)
    : theX(v.x()), theY(v.y()), theZ(v.z()), theT(v.t()) {}
  //@}

  /// Assignment operator
  template <typename ValueB>
  LorentzVector<Value> & operator=(const LorentzVector<ValueB> & b) {
    setX(b.x());
    setY(b.y());
    setZ(b.z());
    setT(b.t());
    return *this;
  }

public:
  /// @name Component access methods.
  //@{
  Value x() const { return theX; }
  Value y() const { return theY; }
  Value z() const { return theZ; }
  Value t() const { return theT; }
  Value e() const { return t();  }
  //@}

  /// @name Component set methods.
  //@{
  void setX(Value x)  {  theX = x; }
  void setY(Value y)  {  theY = y; }
  void setZ(Value z)  {  theZ = z; }
  void setT(Value t)  {  theT = t; }
  void setE(Value e)  {  setT(e);  }
  //@}

public:
  /// Access to the 3-component part.
  Vector3<Value> vect() const {
    return Vector3<Value>(x(),y(),z());
  }

  /// Cast to the 3-component part.
  operator Vector3<Value>() const { return vect(); }
  
  /// Set the 3-component part.
  void setVect(const Vector3<Value> & p) {
    theX = p.x();
    theY = p.y();
    theZ = p.z();
  } 

public:
  /// The complex conjugate vector.
  LorentzVector<Value> conjugate() const 
  {
    return LorentzVector<Value>(conj(x()),conj(y()),conj(z()),conj(t()));
  }

  /// Squared magnitude \f$x^\mu\,x_\mu=t^2 - \vec{x}^2\f$.
  Value2 mag2() const 
  { 
    return (t()-z())*(t()+z()) - sqr(x()) - sqr(y()); 
  }

  /// Squared magnitude \f$x^\mu\,x_\mu=t^2 - \vec{x}^2\f$.
  Value2 m2() const { return mag2(); }

  /// Magnitude (signed) \f$\pm\sqrt{|t^2 - \vec{x}^2|}\f$.
  Value  mag() const 
  {
    Value2 tmp = mag2();
    return tmp < Value2() ? -Value(sqrt(-tmp)) : Value(sqrt(tmp));
  }

  /// Magnitude (signed) \f$\pm\sqrt{|t^2 - \vec{x}^2|}\f$.
  Value m() const { return mag(); }

  /// Transverse mass squared \f$t^2-z^2\f$.
  Value2 mt2()  const { return (t()-z())*(t()+z()); }

  /// Transverse mass (signed) \f$\pm\sqrt{|t^2 - z^2|}\f$.
  Value  mt()  const 
  { 
    Value2 tmp = mt2();
    return tmp < Value2() ? -Value(sqrt(-tmp)) : Value(sqrt(tmp));
  }

  /// Squared transverse component of the spatial vector \f$x^2+y^2\f$.
  Value2 perp2() const { return sqr(x()) + sqr(y()); }

  /// Transverse component of the spatial vector \f$\pm\sqrt{x^2 + y^2}\f$.
  Value  perp()  const { return sqrt(perp2()); }

  /**
   * Squared transverse component of the spatial vector with respect to the
   * given axis.
   */
  template <typename U>
  Value2 perp2(const Vector3<U> & p) const 
  {
    return vect().perp2(p);
  }

  /**
   * Transverse component of the spatial vector with respect to the
   * given axis.
   */
  template <typename U>
  Value perp(const Vector3<U> & p) const 
  {
    return vect().perp(p);
  }

  /// Transverse energy squared.
  Value2 et2() const 
  {
    Value2 pt2 = vect().perp2();
    return pt2 == Value2() ? Value2() : e()*e() * pt2/(pt2+z()*z());
  }

  /// Transverse energy (signed).
  Value et() const 
  {
    Value2 etet = et2();
    return e() < Value() ? -sqrt(etet) : sqrt(etet);
  }

  /// Transverse energy squared with respect to the given axis.
  Value2 et2(const Vector3<double> & v) const 
  {
    Value2 pt2 = vect().perp2(v);
    Value pv = vect().dot(v.unit());
    return pt2 == Value2() ? Value2() : e()*e() * pt2/(pt2+pv*pv);
  }

  /// Transverse energy with respect to the given axis (signed).
  Value et(const Vector3<double> & v) const 
  {
    Value2 etet = et2(v);
    return e() < Value() ? -sqrt(etet) : sqrt(etet);
  }

  /// @name Spherical coordinates for the spatial part.
  //@{
  /// Radius squared.
  Value2 rho2()  const { return sqr(x()) + sqr(y()) + sqr(z()); }

  /// Radius.
  Value  rho()   const { return sqrt(rho2()); }

  /// Set new radius.
  void setRho(Value newRho) 
  { 
    Value oldRho = rho();
    if (oldRho == Value()) 
      return;
    double factor = newRho / oldRho;
    setX(x()*factor);
    setY(y()*factor);
    setZ(z()*factor);
  }

  /// Polar angle.
  double theta() const 
  {
    return x() == Value() && y() == Value() 
      && z() == Value() ? 0.0 : atan2(perp(),z());
  }

  /// Cosine of the polar angle.
  double cosTheta() const 
  {
    Value ptot = rho();
    return ptot == Value() ? 1.0 : double(z()/ptot);
  }

  /// Azimuthal angle.
  double phi()   const 
  {
    return x() == Value() && y() == Value() ? 0.0 : atan2(y(),x()) ;
  }
  //@}

  /// Pseudorapidity of spatial part.
  double eta() const 
  { 
    Value m = rho();
    if ( m ==  Value() ) return  0.0;
    errorIf(m == z() || m == -z(),
	    "Pseudorapidity for 3-vector along z-axis undefined.");
    return 0.5 * log( (m+z()) / (m-z()) );
  }

  /// Spatial angle with another vector.
  double angle(const LorentzVector<Value> & w) const 
  {
    return vect().angle(w.vect());
  }

  /// Rapidity \f$\frac{1}{2}\ln\frac{t+z}{t-z} \f$
  double rapidity() const 
  {
    errorIf(abs(t()) == abs(z()),
	    "rapidity for 4-vector with |E| = |Pz| -- infinite result");
    errorIf(abs(t()) < abs(z()),
	    "rapidity for spacelike 4-vector with |E| < |Pz| -- undefined");
    double q = (t() + z()) / (t() - z());
    return 0.5 * log(q);
  }

  /// Rapidity with respect to another vector
  double rapidity(const Axis & ref) const 
  {
    double r = ref.mag2();
    errorIf(r == 0,
	    "A zero vector used as reference to LorentzVector rapidity");
    Value vdotu = vect().dot(ref)/sqrt(r);
    errorIf(abs(t()) == abs(vdotu),
	    "rapidity for 4-vector with |E| = |Pu| -- infinite result");
    errorIf(abs(t()) < abs(vdotu),
	    "rapidity for spacelike 4-vector with |E|<|P*ref| undefined");
    double q = (t() + vdotu) / (t() - vdotu);
    return 0.5 * log(q);
  }

  /**
   * Boost from reference frame into this vector's rest
   * frame: \f$\frac{\vec{x}}{t}\f$.
   */
  Boost boostVector() const 
  {
    if (t() == Value()) {
      if (rho2() == Value2()) 
	return Boost();
      else 
	errorIf(true,
		"boostVector computed for LorentzVector with t=0"
		" -- infinite result");
    }
    // result will make analytic sense but is physically meaningless
    errorIf(m2() <= Value2(),
	  "boostVector computed for a non-timelike LorentzVector");
    return vect() * (1./t());
  }
  
  /**
   * Boost from reference frame into this vector's rest
   * frame: \f$-\frac{\vec{x}}{t}\f$.
   */
  Boost findBoostToCM() const 
  {
    return -boostVector();
  }

  /// Returns the positive light-cone component \f$t + z\f$.
  Value plus()  const { return t() + z(); }
  /// Returns the negative light-cone component \f$t - z\f$.
  Value minus() const { return t() - z(); }

  /// Are two vectors nearby, using Euclidean measure \f$t^2 + |\vec{x}|^2\f$?
  bool isNear(const LorentzVector<Value> & w, double epsilon) const 
  {
    Value2 limit = abs(vect().dot(w.vect()));
    limit += 0.25 * sqr( t() + w.t() );
    limit *= sqr(epsilon);
    Value2 delta = (vect() - w.vect()).mag2();
    delta +=  sqr( t() - w.t() );
    return (delta <= limit);
  }
  
  /// Rotate the vector. Resets \f$x^\mu\rightarrow\mathsf{M}^\mu_\nu x^\nu\f$.
  LorentzVector<Value> & transform(const SpinOneLorentzRotation & m) 
  {
    return *this = m.operator*(*this);
  }

  /// Rotate the vector. Resets \f$x^\mu\rightarrow\mathsf{M}^\mu_\nu x^\nu\f$.
  LorentzVector<Value> & operator*=(const SpinOneLorentzRotation & m) 
  {
    return transform(m);
  }

  /// Dot product with metric \f$(+,-,-,-)\f$
  template <typename U>
  typename BinaryOpTraits<Value,U>::MulT
  dot(const LorentzVector<U> & a) const 
  {
    return t() * a.t() - ( x() * a.x() + y() * a.y() + z() * a.z() );
  }


public:

  /**
   * Apply boost.  
   *
   * @param bx Component x of the boost.
   * @param by Component y of the boost.
   * @param bz Component z of the boost.
   * @param gamma Optional gamma parameter for higher numerical
   * accuracy. The user has to ensure consistency. If not given, it
   * will be calculated as \f$\gamma=1/\sqrt{1-\beta^2}\f$.
   *
   */
  LorentzVector<Value> & 
  boost(double bx, double by, double bz, double gamma=-1.) 
  {
    double b2 = bx*bx + by*by + bz*bz;
    if(gamma < 0.) 
      gamma = 1.0 / sqrt(1.0 - b2);
    Value bp = bx*x() + by*y() + bz*z();
    double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;
    
    setX(x() + gamma2*bp*bx + gamma*bx*t());
    setY(y() + gamma2*bp*by + gamma*by*t());
    setZ(z() + gamma2*bp*bz + gamma*bz*t());
    setT(gamma*(t() + bp));
    return *this;
  }
  
  /**
   * Apply boost.  
   *
   * @param b Three-vector giving the boost.
   *
   * @param gamma Optional gamma parameter for higher numerical
   * accuracy. The user has to ensure consistency. If not given, it
   * will be calculated as \f$\gamma=1/\sqrt{1-\beta^2}\f$.
   *
   */
  LorentzVector<Value> &  boost(Boost b, double gamma=-1.) {
    return boost(b.x(), b.y(), b.z(),gamma);
  }

  /**
   * Apply rotation around the x-axis.
   *
   * @param phi Angle in radians.
   */
  LorentzVector<Value> & rotateX (double phi) {
    double sinphi = sin(phi);
    double cosphi = cos(phi);
    Value  ty = y() * cosphi - z() * sinphi;
    theZ      = z() * cosphi + y() * sinphi;
    theY = ty;
    return *this;
  }
  
  /**
   * Apply rotation around the y-axis.
   *
   * @param phi Angle in radians.
   */
  LorentzVector<Value> & rotateY (double phi) {
    double sinphi = sin(phi);
    double cosphi = cos(phi);
    Value  tz = z() * cosphi - x() * sinphi;
    theX      = x() * cosphi + z() * sinphi;
    theZ = tz;
    return *this;
  }
  
  /**
   * Apply rotation around the z-axis.
   *
   * @param phi Angle in radians.
   */
  LorentzVector<Value> & rotateZ (double phi) {
    double sinphi = sin(phi);
    double cosphi = cos(phi);
    Value  tx = x() * cosphi - y() * sinphi;
    theY      = y() * cosphi + x() * sinphi;
    theX = tx;
    return *this;
  }
  
  /**
   * Rotate the reference frame to a new z-axis.
   */
  LorentzVector<Value> & rotateUz (const Axis & axis) {
    Axis ax = axis.unit();
    double u1 = ax.x();
    double u2 = ax.y();
    double u3 = ax.z();
    double up = u1*u1 + u2*u2;
    if (up>0) {
      up = sqrt(up);
      Value px = x(),  py = y(),  pz = z();
      setX( (u1*u3*px - u2*py)/up + u1*pz );
      setY( (u2*u3*px + u1*py)/up + u2*pz );
      setZ(    -up*px +             u3*pz );
    }
    else if (u3 < 0.) {
      setX(-x());
      setZ(-z()); 
    }
    else {}
    return *this;
  }
  
public:
  /// @name Mathematical assignment operators.
  //@{
  template <typename ValueB>
  LorentzVector<Value> & operator+=(const LorentzVector<ValueB> & a) {
    theX += a.x();
    theY += a.y();
    theZ += a.z();
    theT += a.t();
    return *this;
  }
  
  template <typename ValueB>
  LorentzVector<Value> & operator-=(const LorentzVector<ValueB> & a) {
    theX -= a.x();
    theY -= a.y();
    theZ -= a.z();
    theT -= a.t();
    return *this;
  }

  LorentzVector<Value> & operator*=(double a) {
    theX *= a;
    theY *= a;
    theZ *= a;
    theT *= a;
    return *this;
  }

  LorentzVector<Value> & operator/=(double a) {
    theX /= a;
    theY /= a;
    theZ /= a;
    theT /= a;
    return *this;
  }
  //@}

private:
  /// @name Vector components
  //@{
  Value theX;
  Value theY;
  Value theZ;
  Value theT;
  //@}
};

/// @name Basic mathematical operations
//@{
template <typename Value>
inline LorentzVector<double>
operator/(const LorentzVector<Value> & v, Value a) {
  return LorentzVector<double>(v.x()/a, v.y()/a, v.z()/a, v.t()/a);
}

template <typename Value>
inline LorentzVector<Value> operator-(const LorentzVector<Value> & v) {
  return LorentzVector<Value>(-v.x(),-v.y(),-v.z(),-v.t());
}

template <typename ValueA, typename ValueB>
inline LorentzVector<ValueA>
operator+(LorentzVector<ValueA> a, const LorentzVector<ValueB> & b) {
  return a += b;
}

template <typename ValueA, typename ValueB>
inline LorentzVector<ValueA>
operator-(LorentzVector<ValueA> a, const LorentzVector<ValueB> & b) {
  return a -= b;
}

template <typename Value>
inline LorentzVector<Value>
operator*(LorentzVector<Value> a, double b) {
  return a *= b;
}

template <typename Value>
inline LorentzVector<Value>
operator*(double b, LorentzVector<Value> a) {
  return a *= b;
}

template <typename ValueA, typename ValueB>
inline
LorentzVector<typename BinaryOpTraits<ValueA,ValueB>::MulT> 
operator*(ValueB a, const LorentzVector<ValueA> & v) {
  typedef typename BinaryOpTraits<ValueB,ValueA>::MulT ResultT;
  return LorentzVector<ResultT>(a*v.x(), a*v.y(), a*v.z(), a*v.t());
}

template <typename ValueA, typename ValueB>
inline
LorentzVector<typename BinaryOpTraits<ValueA,ValueB>::MulT> 
operator*(const LorentzVector<ValueA> & v, ValueB b) {
  return b*v;
}

template <typename ValueA, typename ValueB>
inline
LorentzVector<typename BinaryOpTraits<ValueA,ValueB>::DivT> 
operator/(const LorentzVector<ValueA> & v, ValueB b) {
  typedef typename BinaryOpTraits<ValueA,ValueB>::DivT ResultT;
  return LorentzVector<ResultT>(v.x()/b, v.y()/b, v.z()/b, v.t()/b);
}
//@}

/// @name Scalar product with metric \f$(+,-,-,-)\f$
//@{
template <typename ValueA, typename ValueB>
inline typename BinaryOpTraits<ValueA,ValueB>::MulT 
operator*(const LorentzVector<ValueA> & a, const LorentzVector<ValueB> & b) {
  return a.dot(b);
}

template <typename Value>
inline typename BinaryOpTraits<Value,Value>::MulT 
operator*(const LorentzVector<Value> & a, const LorentzVector<Value> & b) {
  return a.dot(b);
}
//@}

/// Equality
template <typename Value>
inline bool
operator==(const LorentzVector<Value> & a, const LorentzVector<Value> & b) {
  return a.x() == b.x() && a.y() == b.y() && a.z() == b.z() && a.t() == b.t();
}

/// Stream output. Format \f$(x,y,z;t)\f$.
inline ostream & operator<< (ostream & os, const LorentzVector<double> & v) {
  return os << "(" << v.x() << "," << v.y() << "," << v.z()
	    << ";" << v.t() << ")";
}

/** Return the positive light-cone component. Or negative if the
 *  current Direction<0> is reversed. */
template <typename Value>
inline double dirPlus(const LorentzVector<Value> & p) {
  return Direction<0>::pos()? p.plus(): p.minus();
}

/** Return the negative light-cone component. Or positive if the
 *  current Direction<0> is reversed. */
template <typename Value>
inline double dirMinus(const LorentzVector<Value> & p) {
  return Direction<0>::neg()? p.plus(): p.minus();
}

/** Return the component along the positive z-axis. Or the negative
 *  z-axis if the current Direction<0> is reversed. */
template <typename Value>
inline double dirZ(const LorentzVector<Value> & p) {
  return Direction<0>::dir()*p.z();
}

/** Return the polar angle wrt. the positive z-axis. Or the negative
 *  z-axis if the current Direction<0> is reversed. */
template <typename Value>
inline double dirTheta(const LorentzVector<Value> & p) {
  return Direction<0>::pos()? p.theta(): Constants::pi - p.theta();
}

/** Return the cosine of the polar angle wrt. the positive z-axis. Or
 *  the negative z-axis if the current Direction<0> is reversed. */
template <typename Value>
inline double dirCosTheta(const LorentzVector<Value> & p) {
  return Direction<0>::pos()? p.cosTheta():  -p.cosTheta();
}

/** Get the boost vector for the LorentzVector. If the current
 *  Direction<0> is reversed, so is the z-component. */
template <typename Value>
inline Vector3<Value> dirBoostVector(const LorentzVector<Value> & p) {
  Vector3<Value> b(p.boostVector());
  if ( Direction<0>::neg() ) b.setZ(-b.z());
  return b;
}

/** Create a LorentzVector giving its light-cone and transverse
 *  components. */
template <typename Value>
inline LorentzVector<Value>
lightCone(Value plus, Value minus, Value x, Value y) {
  LorentzVector<Value> r(x, y, 0.5*(plus-minus), 0.5*(plus+minus));
  return r;
}

/** Create a LorentzVector giving its light-cone components. */
template <typename Value>
inline LorentzVector<Value>
lightCone(Value plus, Value minus) {
  // g++-3.3 has a problem with using Value() directly
  // gcc-bug c++/3650, fixed in 3.4
  static const Value zero = Value();
  LorentzVector<Value> r(zero, zero,
			 0.5*(plus-minus), 0.5*(plus+minus));
  return r;
}

/** Create a LorentzVector giving its light-cone and transverse
 *  components. */
template <typename Value>
inline LorentzVector<Value>
lightCone(Value plus, Value minus, Transverse<Value> pt) {
  LorentzVector<Value> r(pt.x(), pt.y(), 0.5*(plus-minus), 0.5*(plus+minus));
  return r;
}

/** Create a LorentzVector giving its light-cone and transverse
 *  components. If the current Direction<0> is reversed, so is the
 *  z-component. */
template <typename Value>
inline LorentzVector<Value>
lightConeDir(Value plus, Value minus,
	     Value x = Value(), Value y = Value()) {
  LorentzVector<Value> r(x, y, Direction<0>::dir()*0.5*(plus - minus),
		  0.5*(plus + minus));
  return r;
}

/** Create a LorentzVector giving its light-cone and transverse
 *  components. If the current Direction<0> is reversed, so is the
 *  z-component. */
template <typename Value>
inline LorentzVector<Value>
lightConeDir(Value plus, Value minus, Transverse<Value> pt) {
  LorentzVector<Value> r(pt.x(), pt.y(), Direction<0>::dir()*0.5*(plus - minus),
		  0.5*(plus + minus));
  return r;

}

/** Output a LorentzVector with units to a stream. */
template <typename OStream, typename UnitT, typename Value>
void ounitstream(OStream & os, const LorentzVector<Value> & p, UnitT & u) {
  os << ounit(p.x(), u) << ounit(p.y(), u) << ounit(p.z(), u)
     << ounit(p.e(), u);
}

/** Input a LorentzVector with units from a stream. */
template <typename IStream, typename UnitT, typename Value>
void iunitstream(IStream & is, LorentzVector<Value> & p, UnitT & u) {
  Value x, y, z, e;
  is >> iunit(x, u) >> iunit(y, u) >> iunit(z, u) >> iunit(e, u);
  p = LorentzVector<Value>(x, y, z, e);
}


/// @name Traits for binary operations
//@{
template <typename T, typename U>
struct BinaryOpTraits;

template <typename T, typename U>
struct BinaryOpTraits<LorentzVector<T>, U> {
  /** The type resulting from multiplication of the template type with
      itself. */
  typedef LorentzVector<typename BinaryOpTraits<T,U>::MulT> MulT;
  /** The type resulting from division of one template type with
      another. */
  typedef LorentzVector<typename BinaryOpTraits<T,U>::DivT> DivT;
};

template <typename T, typename U>
struct BinaryOpTraits<T, LorentzVector<U> > {
  /** The type resulting from multiplication of the template type with
      itself. */
  typedef LorentzVector<typename BinaryOpTraits<T,U>::MulT> MulT;
};
//@}

}


#endif /* ThePEG_LorentzVector_H */
