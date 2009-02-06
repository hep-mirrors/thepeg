// -*- C++ -*-
//
// PhysicalQtyOps.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2006-2007 David Grellscheid, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef Physical_Qty_Ops_H
#define Physical_Qty_Ops_H
#include <cmath>

/** @file PhysicalQtyOps.h 
 * Overloads for mathematical operations on physical quantities.
 */

namespace ThePEG {
/// @name Overloads for mathematical operations on physical quantities.
//@{
// qty = qty * qty
template<int L1, int L2, int E1, int E2, int Q1, int Q2,
  int DL1, int DL2, int DE1, int DE2, int DQ1, int DQ2>
inline Qty<L1*DL2+L2*DL1,E1*DE2+E2*DE1,Q1*DQ2+Q2*DQ1,DL1*DL2,DE1*DE2,DQ1*DQ2> 
operator*(Qty<L1,E1,Q1,DL1,DE1,DQ1> q1, Qty<L2,E2,Q2,DL2,DE2,DQ2> q2) {
  typedef
    Qty<L1*DL2+L2*DL1,E1*DE2+E2*DE1,Q1*DQ2+Q2*DQ1,DL1*DL2,DE1*DE2,DQ1*DQ2> RetT;
  return RetT(q1.rawValue()*q2.rawValue()*RetT::baseunit());
}


// qty = qty / qty
template<int L1, int L2, int E1, int E2, int Q1, int Q2,
  int DL1, int DL2, int DE1, int DE2, int DQ1, int DQ2>
inline Qty<L1*DL2-L2*DL1,E1*DE2-E2*DE1,Q1*DQ2-Q2*DQ1,DL1*DL2,DE1*DE2,DQ1*DQ2> 
operator/(Qty<L1,E1,Q1,DL1,DE1,DQ1> q1, Qty<L2,E2,Q2,DL2,DE2,DQ2> q2) {
  typedef
    Qty<L1*DL2-L2*DL1,E1*DE2-E2*DE1,Q1*DQ2-Q2*DQ1,DL1*DL2,DE1*DE2,DQ1*DQ2> RetT;
  return RetT((q1.rawValue()/q2.rawValue())*RetT::baseunit());
}

// qty = qty + qty
template<int L, int E, int Q, int DL, int DE, int DQ, int DL2, int DE2, int DQ2>
inline Qty<L,E,Q,DL,DE,DQ> 
operator+(Qty<L,E,Q,DL,DE,DQ> q1, 
	  Qty<QtyInt<L,DL,DL2>::I,
	      QtyInt<E,DE,DE2>::I,
	      QtyInt<Q,DQ,DQ2>::I, 
	  DL2,DE2,DQ2> q2) {
  Qty<L,E,Q,DL,DE,DQ> q = q1;
  q += q2;
  return q;
}

// qty = qty - qty
template<int L, int E, int Q, int DL, int DE, int DQ, int DL2, int DE2, int DQ2>
inline Qty<L,E,Q,DL,DE,DQ> 
operator-(Qty<L,E,Q,DL,DE,DQ> q1, 
	  Qty<QtyInt<L,DL,DL2>::I,
	      QtyInt<E,DE,DE2>::I,
	      QtyInt<Q,DQ,DQ2>::I, 
	  DL2,DE2,DQ2> q2) {
  Qty<L,E,Q,DL,DE,DQ> q = q1;
  q -= q2;
  return q;
}

// qty == qty
template<int L, int E, int Q, int DL, int DE, int DQ, int DL2, int DE2, int DQ2>
inline bool
operator==(Qty<L,E,Q,DL,DE,DQ> q1,
	   Qty<QtyInt<L,DL,DL2>::I,
	       QtyInt<E,DE,DE2>::I,
	       QtyInt<Q,DQ,DQ2>::I, 
	       DL2,DE2,DQ2> q2) {
  return q1.rawValue()==q2.rawValue();
}

// qty != qty
template<int L, int E, int Q, int DL, int DE, int DQ, int DL2, int DE2, int DQ2>
inline bool
operator!=(Qty<L,E,Q,DL,DE,DQ> q1,
	   Qty<QtyInt<L,DL,DL2>::I,
	       QtyInt<E,DE,DE2>::I,
	       QtyInt<Q,DQ,DQ2>::I, 
	       DL2,DE2,DQ2> q2) {
  return q1.rawValue()!=q2.rawValue();
}

// qty < qty
template<int L, int E, int Q, int DL, int DE, int DQ, int DL2, int DE2, int DQ2>
inline bool
operator<(Qty<L,E,Q,DL,DE,DQ> q1,
          Qty<QtyInt<L,DL,DL2>::I,
              QtyInt<E,DE,DE2>::I,
              QtyInt<Q,DQ,DQ2>::I, 
              DL2,DE2,DQ2> q2) {
  return q1.rawValue()<q2.rawValue();
}

// qty <= qty
template<int L, int E, int Q, int DL, int DE, int DQ, int DL2, int DE2, int DQ2>
inline bool
operator<=(Qty<L,E,Q,DL,DE,DQ> q1,
	   Qty<QtyInt<L,DL,DL2>::I,
	       QtyInt<E,DE,DE2>::I,
	       QtyInt<Q,DQ,DQ2>::I, 
	       DL2,DE2,DQ2> q2) {
  return q1.rawValue()<=q2.rawValue();
}

// qty > qty
template<int L, int E, int Q, int DL, int DE, int DQ, int DL2, int DE2, int DQ2>
inline bool
operator>(Qty<L,E,Q,DL,DE,DQ> q1,
	  Qty<QtyInt<L,DL,DL2>::I,
	      QtyInt<E,DE,DE2>::I,
              QtyInt<Q,DQ,DQ2>::I, 
              DL2,DE2,DQ2> q2) {
  return q1.rawValue()>q2.rawValue();
}

// qty >= qty
template<int L, int E, int Q, int DL, int DE, int DQ, int DL2, int DE2, int DQ2>
inline bool
operator>=(Qty<L,E,Q,DL,DE,DQ> q1,
	   Qty<QtyInt<L,DL,DL2>::I,
	       QtyInt<E,DE,DE2>::I,
               QtyInt<Q,DQ,DQ2>::I, 
               DL2,DE2,DQ2> q2) {
  return q1.rawValue()>=q2.rawValue();
}

// comparisons with ZERO
template<int L, int E, int Q, int DL, int DE, int DQ>
inline bool
operator==(Qty<L,E,Q,DL,DE,DQ> q1, ZeroUnit) {
  return q1.rawValue() == 0.0;
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline bool
operator!=(Qty<L,E,Q,DL,DE,DQ> q1, ZeroUnit) {
  return q1.rawValue() != 0.0;
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline bool
operator<(Qty<L,E,Q,DL,DE,DQ> q1, ZeroUnit) {
  return q1.rawValue() < 0.0;
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline bool
operator>(Qty<L,E,Q,DL,DE,DQ> q1, ZeroUnit) {
  return q1.rawValue() > 0.0;
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline bool
operator<=(Qty<L,E,Q,DL,DE,DQ> q1, ZeroUnit) {
  return q1.rawValue() <= 0.0;
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline bool
operator>=(Qty<L,E,Q,DL,DE,DQ> q1, ZeroUnit) {
  return q1.rawValue() >= 0.0;
}

// qty = qty * double
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ>
operator*(Qty<L,E,Q,DL,DE,DQ> q,double x) {
  return q*=x;
}

// qty = double * qty
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ>
operator*(double x,Qty<L,E,Q,DL,DE,DQ> q) {
  return q*=x;
}

// qty = qty / double
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ>
operator/(Qty<L,E,Q,DL,DE,DQ> q,double x) {
  return q/=x;
}

// qty = double / qty
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<-L,-E,-Q,DL,DE,DQ>
operator/(double x, Qty<L,E,Q,DL,DE,DQ> q) {
  typedef Qty<-L,-E,-Q,DL,DE,DQ> RetT;
  return RetT((x/q.rawValue())*RetT::baseunit());
}

// qty = -qty
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ>
operator-(Qty<L,E,Q,DL,DE,DQ> q) {
  return Qty<L,E,Q,DL,DE,DQ>(-q.rawValue()*Qty<L,E,Q,DL,DE,DQ>::baseunit());
}

// qty = sqr(qty)
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<2*L,2*E,2*Q,DL,DE,DQ>
sqr(Qty<L,E,Q,DL,DE,DQ> q) {
  return q*q;
}

// qty = sqrt(qty)
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL*2,DE*2,DQ*2>
sqrt(Qty<L,E,Q,DL,DE,DQ> q) {
  typedef Qty<L,E,Q,DL*2,DE*2,DQ*2> RetT;
  return RetT(std::sqrt(q.rawValue())*RetT::baseunit());
}

// double = atan2(y,x)
template<int L, int E, int Q, int DL, int DE, int DQ>
inline double
atan2(Qty<L,E,Q,DL,DE,DQ> y, Qty<L,E,Q,DL,DE,DQ> x) {
  return std::atan2(y.rawValue(), x.rawValue());
}

// qty = abs(qty)
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ>
abs(Qty<L,E,Q,DL,DE,DQ> q) {
  typedef Qty<L,E,Q,DL,DE,DQ> RetT;
  return RetT(std::abs(q.rawValue())*RetT::baseunit());
}

// qty = pow<P,R>(qty)
template<int P, int R, int L, int E, int Q, int DL, int DE, int DQ>
Qty<P*L,P*E,P*Q,R*DL,R*DE,R*DQ> pow(Qty<L,E,Q,DL,DE,DQ> q) {
  typedef Qty<P*L,P*E,P*Q,R*DL,R*DE,R*DQ> RetT;
  return RetT(std::pow(q.rawValue(),double(P)/double(R))*RetT::baseunit());
}
  

// max(qty,qty)
template<int L, int E, int Q, int DL, int DE, int DQ, int DL2, int DE2, int DQ2>
inline Qty<L,E,Q,DL,DE,DQ> 
max(Qty<L,E,Q,DL,DE,DQ> q1, 
    Qty<QtyInt<L,DL,DL2>::I,
    QtyInt<E,DE,DE2>::I,
    QtyInt<Q,DQ,DQ2>::I, 
    DL2,DE2,DQ2> q2) {
  return q1.rawValue() < q2.rawValue() ? Qty<L,E,Q,DL,DE,DQ>(q2) : q1;
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ> 
max(Qty<L,E,Q,DL,DE,DQ> q1, 
    Qty<L,E,Q,DL,DE,DQ> q2) { 
  return q1.rawValue() < q2.rawValue() ? q2 : q1;
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ> 
max(Qty<L,E,Q,DL,DE,DQ> q1, ZeroUnit) {
  return q1.rawValue() < 0.0 ? ZERO : q1;
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ> 
max(ZeroUnit, Qty<L,E,Q,DL,DE,DQ> q1) {
  return q1.rawValue() < 0.0 ? ZERO : q1;
}
template<int DL, int DE, int DQ>
inline double
max(double q1, 
    Qty<0,0,0,DL,DE,DQ> q2) { 
  return q1 < q2.rawValue() ? double(q2) : q1;
}
template<int DL, int DE, int DQ>
inline double
max(Qty<0,0,0,DL,DE,DQ> q1, 
    double q2) { 
  return q1.rawValue() < q2 ? q2 : double(q1);
}

// min(qty,qty)
template<int L, int E, int Q, int DL, int DE, int DQ, int DL2, int DE2, int DQ2>
inline Qty<L,E,Q,DL,DE,DQ> 
min(Qty<L,E,Q,DL,DE,DQ> q1, 
    Qty<QtyInt<L,DL,DL2>::I,
    QtyInt<E,DE,DE2>::I,
    QtyInt<Q,DQ,DQ2>::I, 
    DL2,DE2,DQ2> q2) {
  return q1.rawValue() < q2.rawValue() ? q1 : Qty<L,E,Q,DL,DE,DQ>(q2);
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ> 
min(Qty<L,E,Q,DL,DE,DQ> q1, 
    Qty<L,E,Q,DL,DE,DQ> q2) { 
  return q1.rawValue() < q2.rawValue() ? q1 : q2;
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ> 
min(Qty<L,E,Q,DL,DE,DQ> q1, ZeroUnit) {
  return q1.rawValue() > 0.0 ? ZERO : q1;
}
template<int L, int E, int Q, int DL, int DE, int DQ>
inline Qty<L,E,Q,DL,DE,DQ> 
min(ZeroUnit, Qty<L,E,Q,DL,DE,DQ> q1) {
  return q1.rawValue() > 0.0 ? ZERO : q1;
}
template<int DL, int DE, int DQ>
inline double
min(double q1, 
    Qty<0,0,0,DL,DE,DQ> q2) { 
  return q1 < q2.rawValue() ? q1 : double(q2);
}
template<int DL, int DE, int DQ>
inline double
min(Qty<0,0,0,DL,DE,DQ> q1, 
    double q2) { 
  return q1.rawValue() < q2 ? double(q1) : q2;
}
//@}
}

#endif
