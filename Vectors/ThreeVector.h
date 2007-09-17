// -*- C++ -*-
#ifndef ThePEG_ThreeVector_H
#define ThePEG_ThreeVector_H

/** @file ThreeVector.h is... */

#include "ThreeVector.fh"
#include "ThePEG/Utilities/UnitIO.h"
#include <cassert>

namespace ThePEG {

template <typename Value>
class Vector3 
{
  typedef typename BinaryOpTraits<Value,Value>::MulT Value2;
  typedef typename BinaryOpTraits<Value2,Value2>::MulT Value4;
public:
  Vector3() 
    : theX(), theY(), theZ() {}
  Vector3(Value x, Value y, Value z)
    : theX(x), theY(y), theZ(z) {}

  template<typename ValueB>
  Vector3(const Vector3<ValueB> & v)
    : theX(v.x()), theY(v.y()), theZ(v.z()) {}

public:
  Value x() const { return theX; }
  Value y() const { return theY; }
  Value z() const { return theZ; }

  void setX(Value x)  {  theX = x; }
  void setY(Value y)  {  theY = y; }
  void setZ(Value z)  {  theZ = z; }

public:
  Value2 mag2() const { return sqr(x()) + sqr(y()) + sqr(z()); }
  Value  mag() const { return sqrt(mag2()); }

  Value2 perp2() const { return sqr(x()) + sqr(y()); }
  Value  perp()  const { return sqrt(perp2()); }

  template <typename U>
  typename BinaryOpTraits<Value,U>::MulT
  dot(const Vector3<U> & a) const {
    return x()*a.x() + y()*a.y() + z()*a.z();
  }

  template <typename U>
  Value2 perp2(const Vector3<U> & p) const {
    typedef typename BinaryOpTraits<U,U>::MulT pSqType;
    pSqType tot = p.mag2();
    typename BinaryOpTraits<Value,U>::MulT
      ss = this->dot(p);
    return tot > pSqType() ? mag2()-sqr(ss)/tot : mag2();
  }

  template <typename U>
  Value perp(const Vector3<U> & p) const {
    return sqrt(perp2(p));
  }

  double theta() const {
    return x() == Value() && y() == Value() 
      && z() == Value() ? 0.0 : atan2(perp(),z());
  }

  double phi()   const {
    return x() == Value() && y() == Value()? 0.0: atan2(y(),x());
  }

  void setTheta(double th) {
    double ma  = mag();
    double ph  = phi();
    setX(ma*sin(th)*cos(ph));
    setY(ma*sin(th)*sin(ph));
    setZ(ma*cos(th));
  }

  void setPhi(double ph) {
    double xy = perp();
    setX(xy*cos(ph));
    setY(xy*sin(ph));
  }
  
  Vector3<double> unit() const {
    Value2 mg2 = mag2();
    assert(mg2 > Value2());
    Value mg = sqrt(mg2);
    return Vector3<double>(x()/mg, y()/mg, z()/mg);
  }
  
  Vector3<Value> orthogonal() const {
    Value xx = x() < Value() ? -x() : x();
    Value yy = y() < Value() ? -y() : y();
    Value zz = z() < Value() ? -z() : z();
    if (xx < yy) {
      return xx < zz ? Vector3<Value>(Value(),z(),-y()) 
	: Vector3<Value>(y(),-x(),Value());
    } else {
      return yy < zz ? Vector3<Value>(-z(),Value(),x()) 
	: Vector3<Value>(y(),-x(),Value());
    }
  }

  template <typename U>
  double deltaPhi  (const Vector3<U> & v2) const {
    double dphi = v2.phi() - phi();
    if ( dphi > Constants::pi ) {
      dphi -= Constants::twopi;
    } else if ( dphi <= -Constants::pi ) {
      dphi += Constants::twopi;
    }
    return dphi;
  } 

  Vector3<Value> & rotate(double angle, const Vector3<double> & axis) {
    if (angle == 0.0) 
      return *this;
    const double ll = axis.mag();
    assert(ll > 0.0);

    const double sa = sin(angle), ca = cos(angle);
    const double dx = axis.x()/ll, dy = axis.y()/ll, dz = axis.z()/ll;
    const double xx  = x(), yy = y(), zz = z(); 

    setX((ca+(1-ca)*dx*dx)     * xx
	 +((1-ca)*dx*dy-sa*dz) * yy
	 +((1-ca)*dx*dz+sa*dy) * zz
	 );
    setY(((1-ca)*dy*dx+sa*dz)  * xx
	 +(ca+(1-ca)*dy*dy)    * yy
	 +((1-ca)*dy*dz-sa*dx) * zz
	 );
    setZ(((1-ca)*dz*dx-sa*dy)  * xx
	 +((1-ca)*dz*dy+sa*dx) * yy
	 +(ca+(1-ca)*dz*dz)    * zz
	 );
    return *this;
  }

  Vector3<Value> & rotateUz (const Axis & axis) {
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

  template <typename U>
  Vector3<typename BinaryOpTraits<Value,U>::MulT>
  cross(const Vector3<U> & a) const {
    typedef Vector3<typename BinaryOpTraits<Value,U>::MulT> ResultT;
    return ResultT( y()*a.z()-z()*a.y(),
		   -x()*a.z()+z()*a.x(),
		    x()*a.y()-y()*a.x());
  }
  
public:  

  Vector3<Value> & operator+=(const Vector3<Value> & a) {
    theX += a.x();
    theY += a.y();
    theZ += a.z();
    return *this;
  }

  Vector3<Value> & operator-=(const Vector3<Value> & a) {
    theX -= a.x();
    theY -= a.y();
    theZ -= a.z();
    return *this;
  }

  Vector3<Value> & operator*=(double a) {
    theX *= a;
    theY *= a;
    theZ *= a;
    return *this;
  }

  Vector3<Value> & operator/=(double a) {
    theX /= a;
    theY /= a;
    theZ /= a;
    return *this;
  }
  
  template <typename U>
  double cosTheta(const Vector3<U> & q) const {
    typedef typename BinaryOpTraits<Value,U>::MulT
      ProdType;
    double arg;
    ProdType ptot = mag()*q.mag();
    if(ptot <= ProdType()) {
      arg = 0.0;
    } else {
      arg = dot(q)/ptot;
      if(arg >  1.0) arg =  1.0;
      if(arg < -1.0) arg = -1.0;
    }
    return arg;
  }
  
  template <typename U>
  double angle(const Vector3<U> & v) const {
    return acos(cosTheta(v));
  }

private:
  Value theX;
  Value theY;
  Value theZ;
};

inline ostream & 
operator<< (ostream & os, const Vector3<double> & v)
{
  return os << '(' << v.x() << ',' << v.y() << ',' << v.z() << ')';
}

template <typename Value>
inline Vector3<Value>
operator+(Vector3<Value> a, 
	  const Vector3<Value> & b)
{
  return a += b;
}

template <typename Value>
inline Vector3<Value>
operator-(Vector3<Value> a, 
	  const Vector3<Value> & b)
{
  return a -= b;
}

template <typename Value>
inline Vector3<Value> operator-(const Vector3<Value> & v) {
  return Vector3<Value>(-v.x(),-v.y(),-v.z());
}

template <typename Value>
inline Vector3<Value> operator*(Vector3<Value> v, double a) {
  return v *= a;
}

template <typename Value>
inline Vector3<Value> operator*(double a, Vector3<Value> v) {
  return v *= a;
}

template <typename ValueA, typename ValueB>
inline Vector3<typename BinaryOpTraits<ValueA,ValueB>::MulT> 
operator*(ValueB a, Vector3<ValueA> v) {
  typedef typename BinaryOpTraits<ValueA,ValueB>::MulT ResultT;
  return Vector3<ResultT>(a*v.x(), a*v.y(), a*v.z());
}

template <typename ValueA, typename ValueB>
inline Vector3<typename BinaryOpTraits<ValueA,ValueB>::MulT> 
operator*(Vector3<ValueA> v, ValueB a) {
  return a*v;
}

template <typename ValueA, typename ValueB>
inline typename BinaryOpTraits<ValueA,ValueB>::MulT 
operator*(const Vector3<ValueA> & a, 
	  const Vector3<ValueB> & b)
{
  return a.dot(b);
}

template <typename Value>
Vector3<double> unitVector(const Vector3<Value> & v) {
  return v.unit();
}



/** Output a Vector3 with units to a stream. */
template <typename OStream, typename UT, typename Value>
void ounitstream(OStream & os, const Vector3<Value> & p, UT & u) {
  os << ounit(p.x(), u) << ounit(p.y(), u) << ounit(p.z(), u);
}

/** Input a Vector3 with units from a stream. */
template <typename IStream, typename UT, typename Value>
void iunitstream(IStream & is, Vector3<Value> & p, UT & u) {
  Value x, y, z;
  is >> iunit(x, u) >> iunit(y, u) >> iunit(z, u);
  p = Vector3<Value>(x, y, z);
}

}

#endif /* ThePEG_ThreeVector_H */
