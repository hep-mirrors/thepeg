// -*- C++ -*-
#ifndef ThePEG_Matcher_H
#define ThePEG_Matcher_H
//
// This is the declaration of the <!id>Matcher<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>Matcher<!!id> is a templated class inheriting from
// <!class>MatcherBase<!!class>. It is used to conveniently create
// interfaced classes inheriting from <!class>MatcherBase<!!class>
// giving a class with a static 'Check' method as template argument.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:MatcherBase.html">MatcherBase.h</a>.
// 

#include "MatcherBase.h"

namespace ThePEG {

template <class T>
class Matcher: public MatcherBase {

public:

  inline Matcher();
  inline Matcher(const Matcher<T> &);
  virtual ~Matcher();
  // Standard ctors and dtor.

  static PMPtr Create(const string & newName, string antiName);
  virtual PMPtr pmclone() const;
  virtual IBPtr fullclone() const;
  virtual IBPtr clone() const;
  // Create and clone Matcher objects.


  inline virtual bool check(const ParticleData & pd) const;
  inline static bool Check(const ParticleData & pd);
  // Virtual and static mathods, both calling T::Check(pd) to return
  // tru if the given particle type is matched by this Matcher.

protected:

  inline void setCC(tPMPtr, tPMPtr) const;
  // Set antipartner.

private:

  static NoPIOClassDescription< Matcher<T> > initMatcher;

};

template <typename T>
struct BaseClassTrait<Matcher<T>,1> {
  typedef MatcherBase NthBase;
};

template <typename T>
struct ClassTraits< Matcher<T> >:
    public ClassTraitsBase< Matcher<T> > {
  static string className() {
    return "/ThePEG/Matcher<" + ClassTraits<T>::className() + ">";
  }
};

}

#include "Matcher.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Matcher.tcc"
#endif

#endif /* ThePEG_Matcher_H */
