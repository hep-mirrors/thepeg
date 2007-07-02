// -*- C++ -*-
#ifndef Template_Tools_H
#define Template_Tools_H

namespace ThePEG {

template <int v>
struct Int2Type
{
  enum { value = v };
};


// useful for ambiguous function signatures
struct DummyType {};


template <typename T, typename U>
struct BinaryOpTraits;

/** @cond TRAITSPECIALIZATIONS */

template <>
struct BinaryOpTraits<double,double> {
  /** The type resulting from multiplication of the template types. */
  typedef double MulT;
  /** The type resulting from division of the first template type by
      the second. */
  typedef double DivT;
};

template <>
struct BinaryOpTraits<long double, long double> {
  /** The type resulting from multiplication of the template types. */
  typedef long double MulT;
  /** The type resulting from division of the first template type by
      the second. */
  typedef long double DivT;
};

template <>
struct BinaryOpTraits<int,int> {
  /** The type resulting from multiplication of the template types. */
  typedef int MulT;
  /** The type resulting from division of the first template type by
      the second. */
  typedef int DivT;
};

/** @endcond */

enum ImplSelector { Dimensioned, Standard };

typedef Int2Type<Dimensioned> DimensionT;
typedef Int2Type<Standard> StandardT;


template <typename T>
struct TypeTraits
{
  enum { hasDimension = false };
  typedef StandardT DimType;
  static const double baseunit;
};

template<typename T>
const double TypeTraits<T>::baseunit = T(1);

}

#endif
