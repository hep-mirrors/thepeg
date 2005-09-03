// -*- C++ -*-
#ifndef ThePEG_Matcher_H
#define ThePEG_Matcher_H
// This is the declaration of the Matcher class.

#include "MatcherBase.h"

namespace ThePEG {

/**
 * Matcher is a templated class inheriting from MatcherBase. It is
 * used to conveniently create interfaced classes inheriting from
 * MatcherBase giving a class with a static T::Check() method as
 * template argument.
 *
 * @see MatcherBase
 * 
 */
template <class T>
class Matcher: public MatcherBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline Matcher();

  /**
   * Copy-constructor.
   */
  inline Matcher(const Matcher<T> &);

  /**
   * Destructor.
   */
  virtual ~Matcher();
  //@}

  /** @name Special clone and create functions used by the Repository. */
  //@{
  /**
   * Create and clone Matcher objects.
   */
  static PMPtr Create(const string & newName, string antiName);
  /**
   * Create and clone Matcher objects.
   */
  virtual PMPtr pmclone() const;
  //@}


protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const;
  //@}


  /** @name Virtual and static versions of the check functions. */
  //@{
  /**
   * Virtual function overriding the one in MatcherBase. Simply calls
   * Check().
   */
  inline virtual bool check(const ParticleData & pd) const;

  /**
   * Static check function. Return true if a given particle type, \a
   * pd, is matched by this Matcher, ie. if the T::Check() function of
   * the template argument returns true.
   */
  inline static bool Check(const ParticleData & pd);
  //@}

protected:

  /**
   * Set antipartner.
   */
  inline void setCC(tPMPtr, tPMPtr) const;

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class without persistent data.
   */
  static NoPIOClassDescription< Matcher<T> > initMatcher;

};

/**
 * MatcherType is an empty non-polymorphic base class for all matcher
 * classes to be used as template argument to Matcher.
 */
struct MatcherType {};

/** @cond TRAITSPECIALIZATIONS */

/** This partial template specialization informs ThePEG about the base
 *  classes of Matcher<T>. */
template <typename T>
struct BaseClassTrait<Matcher<T>,1>: public ClassTraitsType {
  /** Typedef of the first base class of Matcher<T>. */
  typedef MatcherBase NthBase;
};

/** This partial template specialization informs ThePEG about the name
 *  of the Matcher<T> class. Note that the template argument class is
 *  assumed to have a specialization of ClassTraits of its own.*/
template <typename T>
struct ClassTraits< Matcher<T> >: public ClassTraitsBase< Matcher<T> > {
  /** Return a platform-independent class name */
  static string className() {
    return "ThePEG::Matcher<" + ClassTraits<T>::className() + ">";
  }
};

/** @endcond */

}

#include "Matcher.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Matcher.tcc"
#endif

#endif /* ThePEG_Matcher_H */
