// -*- C++ -*-
#ifndef ThePEG_Containers_H
#define ThePEG_Containers_H

// This file defines a number of containers. Some are just typedefs of
// <!id>std::<!!id> containers, while others are wrappers around
// <!id>std::<!!id> containers introduced in the hope of reducing the
// amount of debugging and code duplication.
//
// Do not make changes in this file. If you need to modify any of the
// standard containers used in ThePEG, edit a copy of this file and
// include it in an alternative config file which can be included in
// the main <a href="http:ThePEG.html">ThePEG.h</a> config file
// using the macro <!id>ThePEG_ALTERNATE_CONFIG<!!id>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ThePEG.html">ThePEG.h</a>
// <a href="http:std.html">std.h</a>
// 

#include "ThePEG/Utilities/FixedSizeAllocator.h"
#include "ThePEG/Utilities/UnitIO.h"

namespace ThePEG {

ThePEG_DECLARE_SET(PDPtr,ParticleDataSet);
typedef vector<PDPtr> PDVector;
typedef vector<cPDPtr> cPDVector;
typedef vector<tPDPtr> tPDVector;
typedef vector<tcPDPtr> tcPDVector;
ThePEG_DECLARE_SET(PMPtr,MatcherSet);
ThePEG_DECLARE_SET(DMPtr,DecayModeSet);
ThePEG_DECLARE_SET(IBPtr,ObjectSet);
ThePEG_DECLARE_SET(IBPtr,DependencySet);
ThePEG_DECLARE_MAP(long,PDPtr,ParticleMap);
ThePEG_DECLARE_MAP(string,IBPtr,ObjectMap);
ThePEG_DECLARE_MAP(IBPtr,DependencySet,DependencyMap);
typedef vector<IBPtr> IVector;
typedef vector<cIBPtr> CIVector;
typedef vector<PPtr> ParticleVector;
typedef vector<PPtr> PVector;
typedef vector<cPPtr> cPVector;
typedef vector<tPPtr> tPVector;
typedef vector<tcPPtr> tcPVector;
ThePEG_DECLARE_MAP(string,const InterfaceBase *,InterfaceMap);
typedef Rebinder<InterfacedBase> TranslationMap;
ThePEG_DECLARE_MAP(string,EGPtr,GeneratorMap);
typedef vector<AnaPtr> AnalysisVector;
typedef pair<PBPtr, PBPtr> PBPair;
typedef pair<PDPtr, PDPtr> PDPair;
typedef pair<cPDPtr, cPDPtr> cPDPair;
typedef pair<tPDPtr, tPDPtr> tPDPair;
typedef pair<tcPDPtr, tcPDPtr> tcPDPair;
typedef pair<PPtr, PPtr> PPair;
typedef pair<cPPtr, cPPtr> cPPair;
typedef pair<tPPtr, tPPtr> tPPair;
typedef pair<tcPPtr, tcPPtr> tcPPair;
typedef Interval<Energy2> SInterval;
typedef vector<Energy2> SVector;
typedef vector<SInterval> SIntervalVector;
typedef vector<PBPair> PartonPairVec;
typedef vector<tPDPair> tPartonPairVec;
typedef pair<tColinePtr,tColinePtr> tColinePair;
class SimpleDensityFunction;
typedef vector<SimpleDensityFunction> SimpleDensityVector;
typedef vector<PBPtr> PartonVector;
ThePEG_DECLARE_SET(tDMPtr,DecaySet);
ThePEG_DECLARE_SET(string,StringSet);
typedef vector<Energy> EnergyVector;
typedef vector<EIPtr> EIVector;
typedef vector<MEPtr> MEVector;
typedef vector<double> DVector;
typedef pair<double,double> DPair;

template <typename T, typename U>
vector<T> & operator<<(vector<T> & tv, const U & u) {
  tv.push_back(u);
  return tv;
}

template <typename T, typename U>
vector<T> & operator>>(vector<T> & tv, U & u) {
  u = tv.back();
  tv.pop_back();
  return tv;
}

template <typename T, typename U>
stack<T> & operator<<(stack<T> & ts, const U & u) {
  ts.push(u);
  return ts;
}

template <typename T, typename U>
stack<T> & operator>>(stack<T> & ts, U & u) {
  u = ts.top();
  ts.pop();
  return ts;
}

template <typename T, typename U>
deque<T> & operator<<(deque<T> & td, const U & u) {
  td.push_back(u);
  return td;
}

template <typename T, typename U>
deque<T> & operator>>(deque<T> & td, U & u) {
  u = td.front();
  td.pop_front();
  return td;
}

template <typename T, typename U>
set<T> & operator<<(set<T> & ts, const U & u) {
  ts.insert(u);
  return ts;
}

template <typename OStream, typename T, typename Alloc, typename UT>
void ounitstream(OStream & os, const vector<T,Alloc> & v, UT & u) {
  os << v.size();
  for ( typename vector<T,Alloc>::const_iterator i = v.begin();
	i != v.end(); ++i )
    os << ounit(*i, u);
}

template <typename IStream, typename T, typename Alloc, typename UT>
void iunitstream(IStream & is, vector<T,Alloc> & v, UT & u) {
  typename vector<T,Alloc>::size_type l;
  is >> l;
  v.resize(l);
  for ( typename vector<T,Alloc>::iterator i = v.begin(); i != v.end(); ++i )
    is >> iunit(*i, u);
}

template <typename OStream, typename T, typename CMP, typename A, typename UT>
void ounitstream(OStream & os, const set<T,CMP,A> & s, UT & u) {
  os << s.size();
  for ( typename set<T,CMP,A>::const_iterator i = s.begin(); i != s.end(); ++i )
    os << ounit(*i, u);
}

template <typename IStream, typename T, typename CMP, typename A, typename UT>
void iunitstream(IStream & is, set<T,CMP,A> & s, UT & u) {
  s.clear();
  typename set<T,CMP,A>::size_type l;
  is >> l;
  T t;
  while ( l-- ) {
    is >> iunit(t, u);
    s.insert(t);
  }
}

template <typename OStream, typename K, typename T,
          typename CMP, typename A, typename UT>
void ounitstream(OStream & os, const map<K,T,CMP,A> & m, UT & u) {
  os << m.size();
  for ( typename map<K,T,CMP,A>::const_iterator i = m.begin();
	i != m.end(); ++i )
    os << i->first, ounit(i->second, u);
}

template <typename IStream, typename K, typename T,
          typename CMP, typename A, typename UT>
void iunitstream(IStream & is, map<K,T,CMP,A> & m, UT & u) {
  m.clear();
  typename map<K,T,CMP,A>::size_type l;
  is >> l;
  T t;
  K k;
  while ( l-- ) {
    is >> k >> iunit(t, u);
    m[k] = t;
  }
}

}

#endif /* ThePEG_Containers_H */
