// -*- C++ -*-
#ifndef ThePEG_LorentzVector_H
#define ThePEG_LorentzVector_H

/** @file LorentzVector.h is a... */

#include "LorentzVector.fh"
#include "Transverse.h"
#include "ThePEG/Utilities/Direction.h"
#include "ThePEG/Utilities/UnitIO.h"
#include "LorentzRotation.h"
#include "ThreeVector.h"

namespace ThePEG {

template <typename Value> class LorentzVector; 

template <typename Value>
class LorentzVector 
{
typedef typename BinaryOpTraits<Value,Value>::MulT Value2;

public:
  LorentzVector() 
    : theX(), theY(), theZ(), theT() {}
  LorentzVector(Value x, Value y, Value z, Value t)
    : theX(x), theY(y), theZ(z), theT(t) {}
  LorentzVector(const Vector3<Value> & v, Value t)
    : theX(v.x()), theY(v.y()), theZ(v.z()), theT(t) {}

  template<typename U>
  LorentzVector(const LorentzVector<U> & v)
    : theX(v.x()), theY(v.y()), theZ(v.z()), theT(v.t()) {}

  template <typename ValueB>
  LorentzVector<Value> & operator=(const LorentzVector<ValueB> & b) {
    setX(b.x());
    setY(b.y());
    setZ(b.z());
    setT(b.t());
    return *this;
  }

public:
  Value x() const { return theX; }
  Value y() const { return theY; }
  Value z() const { return theZ; }
  Value t() const { return theT; }

  void setX(Value x)  {  theX = x; }
  void setY(Value y)  {  theY = y; }
  void setZ(Value z)  {  theZ = z; }
  void setT(Value t)  {  theT = t; }

  Value e() const     { return t(); }
  void setE(Value e)  {  setT(e);   }

public:
  Vector3<Value> vect() const {
    return Vector3<Value>(x(),y(),z());
  }

  operator Vector3<Value>() const { return vect(); }
  
  void setVect(const Vector3<Value> & p) {
    theX = p.x();
    theY = p.y();
    theZ = p.z();
  } 

public:

  LorentzVector<Value> conjugate() const {
    return LorentzVector<Value>(conj(x()),conj(y()),conj(z()),conj(t()));
  }

  Value2 mag2() const { return sqr(t()) - ( sqr(x()) + sqr(y()) + sqr(z()) ); }
  Value  mag() const {
    Value2 tmp = mag2();
    return tmp < Value2() ? -Value(sqrt(-tmp)) : Value(sqrt(tmp));
  }

  Value  m()     const { return mag(); }
  Value2 m2()    const { return mag2(); }
  
  Value2 mt2()   const { return sqr(t()) - sqr(z()); }
  Value  mt()  const { 
    Value2 tmp = mt2();
    return tmp < Value2() ? -Value(sqrt(-tmp)) : Value(sqrt(tmp));
  }

  Value2 perp2() const { return sqr(x()) + sqr(y()); }
  Value  perp()  const { return sqrt(perp2()); }

  template <typename U>
  Value2 perp2(const Vector3<U> & p) const {
    return vect().perp2(p);
  }

  template <typename U>
  Value perp(const Vector3<U> & p) const {
    return vect().perp(p);
  }


  Value2 et2() const {
    Value2 pt2 = vect().perp2();
    return pt2 == Value2() ? Value2() : e()*e() * pt2/(pt2+z()*z());
  }

  Value et() const {
    Value2 etet = et2();
    return e() < Value() ? -sqrt(etet) : sqrt(etet);
  }

  Value2 et2(const Vector3<double> & v) const {
    Value2 pt2 = vect().perp2(v);
    Value pv = vect().dot(v.unit());
    return pt2 == Value2() ? Value2() : e()*e() * pt2/(pt2+pv*pv);
  }

  Value et(const Vector3<double> & v) const {
    Value2 etet = et2(v);
    return e() < Value() ? -sqrt(etet) : sqrt(etet);
  }

  Value2 rho2()  const { return sqr(x()) + sqr(y()) + sqr(z()); }
  Value  rho()   const { return sqrt(rho2()); }

  double eta()   const { 
    Value m = rho();
    if ( m ==  Value() ) return  0.0;
    if ( m ==  z() ) return  1.0E72;
    if ( m == -z() ) return -1.0E72;
    return 0.5*log( (m+z())/(m-z()) );
  }

  double theta() const {
    return x() == Value() && y() == Value() 
      && z() == Value() ? 0.0 : atan2(perp(),z());
  }

  double cosTheta() const {
    Value ptot = rho();
    return ptot == Value() ? 1.0 : double(z()/ptot);
  }

  double phi()   const {
    return x() == Value() && y() == Value() ? 0.0 : atan2(y(),x()) ;
  }

  double angle(const LorentzVector<Value> & w) const {
    return vect().angle(w.vect());
  }

  double rapidity() const {
    if (abs(t()) == abs(z())) {
      throw Exception() << "rapidity for 4-vector with |E| = |Pz| -- infinite result" 
			<< Exception::eventerror;
    }
    if (abs(t()) < abs(z())) {
      throw Exception() << "rapidity for spacelike 4-vector with |E| < |Pz| -- undefined" 
			<< Exception::eventerror;
    }
    double q = (t() + z()) / (t() - z());
    return 0.5 * log(q);
  }

  double rapidity(const Axis & ref) const {
    double r = ref.mag2();
    if (r == 0) {
      throw Exception() << "A zero vector used as reference to LorentzVector rapidity"
			<< Exception::eventerror;
    }
    Value vdotu = vect().dot(ref)/sqrt(r);
    if (abs(t()) == abs(vdotu)) {
      throw Exception() <<  "rapidity for 4-vector with |E| = |Pu| -- infinite result" 
			<< Exception::eventerror;
    }
    if (abs(t()) < abs(vdotu)) {
      throw Exception() <<  "rapidity for spacelike 4-vector with |E|<|P*ref| undefined"
			<< Exception::eventerror;;
    }
    double q = (t() + vdotu) / (t() - vdotu);
    return 0.5 * log(q);
  }


  void setRho(Value newRho) { 
    Value oldRho = rho();
    if (oldRho == Value()) return;
    // LorentzVector::setMag : zero vector can't be stretched
    double factor = newRho / oldRho;
    setX(x()*factor);
    setY(y()*factor);
    setZ(z()*factor);
  }

  Boost boostVector() const {
    if (t() == Value()) {
      if (rho2() == Value2()) {
	return Boost();
      } else {
	throw Exception() << "boostVector computed for LorentzVector with t=0 -- infinite result" << Exception::eventerror;
	return vect() * (1./t());
      }
    }
    if (m2() <= Value2()) {
      throw Exception() << "boostVector computed for a non-timelike LorentzVector " << Exception::eventerror;
      // result will make analytic sense but is physically meaningless
    }
    return vect() * (1./t());
  }
  
  Boost findBoostToCM() const {
    return -boostVector();
  }

  Value plus()  const { return t() + z(); }
  Value minus() const { return t() - z(); }


  bool isNear(const LorentzVector<Value> & w, double epsilon) const {
    Value2 limit = abs(vect().dot(w.vect()));
    limit += 0.25 * sqr(t()+w.t());
    limit *= sqr(epsilon);
    Value2 delta = (vect() - w.vect()).mag2();
    delta +=  sqr(t()-w.t());
    return (delta <= limit );
  }
  
  LorentzVector<Value> & transform(const SpinOneLorentzRotation & m) {
    return *this = m.operator*(*this);
  }
  
  LorentzVector<Value> & operator*=(const SpinOneLorentzRotation & m) {
    return transform(m);
  }

  template <typename U>
  typename BinaryOpTraits<Value,U>::MulT
  dot(const LorentzVector<U> & a) const {
    return t() * a.t() - ( x() * a.x() + y() * a.y() + z() * a.z() );
  }


public:

  LorentzVector<Value> & 
  boost(double bx, double by, double bz) {
    double b2 = bx*bx + by*by + bz*bz;
    double gamma = 1.0 / sqrt(1.0 - b2);
    Value bp = bx*x() + by*y() + bz*z();
    double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;
    
    setX(x() + gamma2*bp*bx + gamma*bx*t());
    setY(y() + gamma2*bp*by + gamma*by*t());
    setZ(z() + gamma2*bp*bz + gamma*bz*t());
    setT(gamma*(t() + bp));
    return *this;
  }
  
  LorentzVector<Value> &  boost(Boost b) {
    return boost(b.x(), b.y(), b.z());
  }

  LorentzVector<Value> & rotateX (double phi) {
    double sinphi = sin(phi);
    double cosphi = cos(phi);
    Value  ty = y() * cosphi - z() * sinphi;
    theZ      = z() * cosphi + y() * sinphi;
    theY = ty;
    return *this;
  }
  
  LorentzVector<Value> & rotateY (double phi) {
    double sinphi = sin(phi);
    double cosphi = cos(phi);
    Value  tz = z() * cosphi - x() * sinphi;
    theX      = x() * cosphi + z() * sinphi;
    theZ = tz;
    return *this;
  }
  
  LorentzVector<Value> & rotateZ (double phi) {
    double sinphi = sin(phi);
    double cosphi = cos(phi);
    Value  tx = x() * cosphi - y() * sinphi;
    theY      = y() * cosphi + x() * sinphi;
    theX = tx;
    return *this;
  }
  
  LorentzVector<Value> & rotateUz (const Axis & axis) {
    // axis must be normalized !
    double u1 = axis.x();
    double u2 = axis.y();
    double u3 = axis.z();
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

private:
  Value theX;
  Value theY;
  Value theZ;
  Value theT;
};

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
inline typename BinaryOpTraits<ValueA,ValueB>::MulT 
operator*(const LorentzVector<ValueA> & a, const LorentzVector<ValueB> & b) {
  return a.dot(b);
}

template <typename Value>
inline typename BinaryOpTraits<Value,Value>::MulT 
operator*(const LorentzVector<Value> & a, const LorentzVector<Value> & b) {
  return a.dot(b);
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

template <typename Value>
inline bool
operator==(const LorentzVector<Value> & a, const LorentzVector<Value> & b) {
  return a.x() == b.x() && a.y() == b.y() && a.z() == b.z() && a.t() == b.t();
}

//template <typename Value>
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
  /** The type resulting from division of one template type with
      another. */
  //typedef LorentzVector<typename BinaryOpTraits<T,U>::DivT> DivT;
};


}


#endif /* ThePEG_LorentzVector_H */
