// -*- C++ -*-
//
#ifndef ThePEG_CombinedMatcher_H
#define ThePEG_CombinedMatcher_H
//
// This is the declaration of the <!id>AndMatcher<!!id>,
// <!id>OrMatcher<!!id> and <!id>NotMatcher<!!id> class which
// represent boolean operations on classes of type
// <!class>MatcherBase<!!class>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:MatcherBase.html">MatcherBase.h</a>.
// 

//

#include "Matcher.h"

namespace ThePEG {

template <class T1, class T2>
struct AndMatcher {
  // Matcher for all particles matched by both T1 and T2.
  typedef AndMatcher<typename T1::CC, typename T2::CC> CC;

  inline static bool Check(const ParticleData & pd) {
    return T1::Check(pd) && T2::Check(pd);
  }

};

template <class T1, class T2>
struct OrMatcher {
  // Matcher for all particles matched by either T1 or T2.
  typedef OrMatcher<typename T1::CC, typename T2::CC> CC;

  inline static bool Check(const ParticleData & pd) {
    return T1::Check(pd) || T2::Check(pd);
  }

};

template <class T>
struct NotMatcher {
  // Matcher for all particles not matched by T.
  typedef NotMatcher<typename T::CC> CC;

  inline static bool Check(const ParticleData & pd) {
    return !T::Check(pd);
  }

};

}

#endif /* ThePEG_CombinedMatcher_H */
