// -*- C++ -*-
#ifndef Physical_Qty_H
#define Physical_Qty_H
#include "TemplateTools.h"

namespace ThePEG {

template <int M, int II>
struct QtyHelper {
  static const int I = -999999;
};

template <int II>
struct QtyHelper<0,II> {
  static const int I = II;
};

template <int II, int DI, int DI2>
struct QtyInt {
  static const int I = QtyHelper<(DI2*II)%DI,(DI2*II)/DI>::I;
};


template<int L, int E, int Q, int DL = 1, int DE = 1, int DQ = 1>
class Qty
{
private:

  Qty(double val) : rawValue_(val) {}

public:

  typedef Qty<2*L,2*E,2*Q,DL,DE,DQ> Squared;

  static Qty<L,E,Q,DL,DE,DQ> baseunit() {
    return Qty<L,E,Q,DL,DE,DQ>(1.0);
  }

  // default constructor to 0
  Qty() : rawValue_(0.0) {}

  template <int DL2, int DE2, int DQ2>
  Qty(const Qty<QtyInt<L,DL,DL2>::I,QtyInt<E,DE,DE2>::I,QtyInt<Q,DQ,DQ2>::I,
                DL2,DE2,DQ2> & q)
    : rawValue_(q.rawValue()) {}

  double rawValue() const { return rawValue_; }

  Qty<L,E,Q,DL,DE,DQ> & operator*=(double x) { rawValue_ *= x; return *this; }
  Qty<L,E,Q,DL,DE,DQ> & operator/=(double x) { rawValue_ /= x; return *this; }

  template <int DL2, int DE2, int DQ2>
  Qty<L,E,Q,DL,DE,DQ> & 
  operator+=(const Qty<QtyInt<L,DL,DL2>::I,
	               QtyInt<E,DE,DE2>::I,
	               QtyInt<Q,DQ,DQ2>::I,
	     DL2,DE2,DQ2> x) { 
    rawValue_ += x.rawValue(); 
    return *this; 
  }

  template <int DL2, int DE2, int DQ2>
  Qty<L,E,Q,DL,DE,DQ> & 
  operator-=(const Qty<QtyInt<L,DL,DL2>::I,
	               QtyInt<E,DE,DE2>::I,
	               QtyInt<Q,DQ,DQ2>::I,
	     DL2,DE2,DQ2> x) { 
    rawValue_ -= x.rawValue(); 
    return *this; 
  }

private:
  double rawValue_;
};

// specialization for <0,0,0> with conversions to double
template<int DL, int DE, int DQ>
class Qty<0,0,0,DL,DE,DQ>
{
public:
  typedef Qty<0,0,0,DL,DE,DQ> Squared;

  static Qty<0,0,0,DL,DE,DQ> baseunit() {
    return Qty<0,0,0,DL,DE,DQ>(1.0);
  }

  // default constructor to 0, can take doubles, too
  Qty(double x = 0.0) : rawValue_(x) {}

  template <int DL2, int DE2, int DQ2>
  Qty(const Qty<0,0,0,DL2,DE2,DQ2> & q) : rawValue_(q.rawValue()) {}

  double rawValue() const { return rawValue_; }
  operator double() const { return rawValue_; }

  Qty<0,0,0,DL,DE,DQ> & operator*=(double x) { rawValue_ *= x; return *this; }
  Qty<0,0,0,DL,DE,DQ> & operator/=(double x) { rawValue_ /= x; return *this; }

  Qty<0,0,0,DL,DE,DQ> & operator+=(const Qty<0,0,0,DL,DE,DQ> x) { 
    rawValue_ += x.rawValue(); 
    return *this; 
  }
  Qty<0,0,0,DL,DE,DQ> & operator-=(const Qty<0,0,0,DL,DE,DQ> x) { 
    rawValue_ -= x.rawValue(); 
    return *this; 
  }

private:
  double rawValue_;
};

template <typename T, typename U> 
struct BinaryOpTraits;

template<int L1, int L2, int E1, int E2, int Q1, int Q2,
	 int DL1, int DL2, int DE1, int DE2, int DQ1, int DQ2>
struct BinaryOpTraits<Qty<L1,E1,Q1,DL1,DE1,DQ1>,
		      Qty<L2,E2,Q2,DL2,DE2,DQ2> > {
  /** The type resulting from multiplication of the template type with
      itself. */
  typedef Qty<L1*DL2+L2*DL1,E1*DE2+E2*DE1,Q1*DQ2+Q2*DQ1,
              DL1*DL2,DE1*DE2,DQ1*DQ2> MulT;
  /** The type resulting from division of one template type with
      another. */
  typedef Qty<L1*DL2-L2*DL1,E1*DE2-E2*DE1,Q1*DQ2-Q2*DQ1,
              DL1*DL2,DE1*DE2,DQ1*DQ2> DivT;
};


template<int L1, int E1, int Q1, int DL1, int DE1, int DQ1>
struct BinaryOpTraits<Qty<L1,E1,Q1,DL1,DE1,DQ1>,
		      Qty<L1,E1,Q1,DL1,DE1,DQ1> > {
  /** The type resulting from multiplication of the template type with
      itself. */
  typedef Qty<2*L1,2*E1,2*Q1,
              DL1,DE1,DQ1> MulT;
  /** The type resulting from division of one template type with
      another. */
  typedef double DivT;
};

template<int L1, int E1, int Q1, int DL1, int DE1, int DQ1>
struct BinaryOpTraits<double,
		      Qty<L1,E1,Q1,DL1,DE1,DQ1> > {
  /** The type resulting from multiplication of the template type with
      itself. */
  typedef Qty<L1,E1,Q1,
              DL1,DE1,DQ1> MulT;
  /** The type resulting from division of one template type with
      another. */
  typedef Qty<-L1,-E1,-Q1,
              DL1,DE1,DQ1> DivT;
};

template<int L1, int E1, int Q1, int DL1, int DE1, int DQ1>
struct BinaryOpTraits<Qty<L1,E1,Q1,DL1,DE1,DQ1>,
		      double> {
  /** The type resulting from multiplication of the template type with
      itself. */
  typedef Qty<L1,E1,Q1,
              DL1,DE1,DQ1> MulT;
  /** The type resulting from division of one template type with
      another. */
  typedef Qty<L1,E1,Q1,
              DL1,DE1,DQ1> DivT;
};

// template <typename T>
// class TypeTraits
// {
// private:
//   template <typename U> 
//   struct DimensionTraits 
//   {
//     enum { result = false };
//     typedef StandardT Type;
//     static const U baseunit() {
//       return 1;
//     }
//   };
  
//   template <int L, int E, int Q, int DL, int DE, int DQ> 
//   struct DimensionTraits<Qty<L,E,Q,DL,DE,DQ> > 
//   {
//     enum { result = true };
//     typedef DimensionT Type;
//     static const Qty<L,E,Q,DL,DE,DQ> baseunit() {
//       return Qty<L,E,Q,DL,DE,DQ>::baseunit();
//     }
//   };

//   template <int DL, int DE, int DQ> 
//   struct DimensionTraits<Qty<0,0,0,DL,DE,DQ> > 
//   {
//     enum { result = false };
//     typedef StandardT Type;
//     static const Qty<0,0,0,DL,DE,DQ> baseunit() {
//       return 1.0;
//     }
//   };
  
// public:
//   enum { hasDimension = DimensionTraits<T>::result };
//   typedef typename DimensionTraits<T>::Type DimType;
//   static const T baseunit;
// };

// template<typename T>
// const T TypeTraits<T>::baseunit = DimensionTraits<T>::baseunit();

template <int L, int E, int Q, int DL, int DE, int DQ> 
struct TypeTraits<Qty<L,E,Q,DL,DE,DQ> >
{
  enum { hasDimension = true };
  typedef DimensionT DimType;
  static const Qty<L,E,Q,DL,DE,DQ> baseunit;
};

template <int L, int E, int Q, int DL, int DE, int DQ> 
const Qty<L,E,Q,DL,DE,DQ> 
TypeTraits<Qty<L,E,Q,DL,DE,DQ> >::baseunit = Qty<L,E,Q,DL,DE,DQ>::baseunit();


template <int DL, int DE, int DQ> 
struct TypeTraits<Qty<0,0,0,DL,DE,DQ> >
{
  enum { hasDimension = false };
  typedef StandardT DimType;
  static const double baseunit;
};

template <int DL, int DE, int DQ> 
const double 
TypeTraits<Qty<0,0,0,DL,DE,DQ> >::baseunit = 1.0;


}

#endif
