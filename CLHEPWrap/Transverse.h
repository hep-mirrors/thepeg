// -*- C++ -*-
#ifndef ThePEG_Transverse_H
#define ThePEG_Transverse_H
//
// This is the declaration of the <!id>Transverse<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>Transverse<!!id> represents the transverse components of a
// LorentzVector. It inherits from
// <!id>std::pair&lt;FloatType,FloatType&gt;<!!id> and can be used
// anywhere such a pair is called for. It can also be created directly
// from a <!id>Vector3<!!id>, <!id>LorentzVector<!!id> and
// <!id>Lorentz5Momentum<!!id>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Lorentz5Vector.html">Lorentz5Vector.h</a>,
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/CLHEPWrap/Lorentz5Vector.h"
#include "Transverse.fh"
// #include "Transverse.xh"

namespace ThePEG {

template <typename FloatType>
class Transverse: public pair<FloatType,FloatType> {

public:

  typedef FloatType FloatType2;
  typedef pair<FloatType,FloatType> BasePair;

public:

  inline Transverse();
  inline Transverse(const Transverse &);
  inline Transverse(const BasePair &);
  inline Transverse(FloatType, FloatType);
  inline Transverse(const Vector3 &);
  inline Transverse(const LorentzVector &);
  inline Transverse(const Lorentz5Vector<FloatType> &);
  // Constructors.

  inline const Transverse & operator=(const Transverse &);
  inline const Transverse & operator=(const BasePair &);
  inline const Transverse & operator=(const Vector3 &);
  inline const Transverse & operator=(const LorentzVector &);
  inline const Transverse & operator=(const Lorentz5Vector<FloatType> &);
  // Assignment.

  inline FloatType x() const;
  inline FloatType y() const;
  // Element access.

  inline Transverse operator-() const;
  inline Transverse operator-(const Transverse &) const;
  inline Transverse & operator-=(const Transverse &);
  inline Transverse operator+(const Transverse &) const;
  inline Transverse & operator+=(const Transverse &);
  // Arithmetric operations.

  inline FloatType2 pt2() const;
  inline FloatType pt() const;
  inline double phi() const;
  // Polar coordinates.

};

template <typename OStream, typename T, typename UT>
void ounitstream(OStream & os, const Transverse<T> & p, UT & u) {
  os << ounit(p.x(), u) << ounit(p.y(), u);
}

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
