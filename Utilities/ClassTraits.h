// -*- C++ -*-
#ifndef ThePEG_ClassTraits_H
#define ThePEG_ClassTraits_H
// This is the declaration of the ClassTraitsBase, ClassTraits and
// BaseClassTraits classes.


#include "ThePEG/Config/ThePEG.h"
// #include "ClassTraits.fh"
// #include "ClassTraits.xh"
#include "ThePEG/Persistency/PersistentOStream.fh"
#include "ThePEG/Persistency/PersistentIStream.fh"


namespace ThePEG {

/**
 * The templated ClassTraitsBase class defines a set of default
 * information about classes used by ThePEG. By default, the
 * ClassTraits simply inherits from ClassTraitsBase, but it can be
 * specialized to override the static member functions.
 *
 * The information that should be made available is:<BR>
 * <code>create()</code> creates an object of the described class,<BR>
 * <code>className()</code> returns the platform-independent name of
 * the class,<BR> <code>version()</code> return the version
 * number,<BR> <code>output()</code> output the members of the class
 * to a PersistentOStream,<BR> <code>input()</code> reads the members
 * of the class from a PersistentIStream and<BR> <code>cast()</code>
 * dynamically cast a pointer to a public base class to a pointer to
 * the class.
 *
 * @see PersistentOStream,
 * @see PersistentIStream.
 */
template <typename T>
struct ClassTraitsBase {

  ThePEG_DECLARE_TEMPLATE_POINTERS(T,TPtr);
  ThePEG_DECLARE_POINTERS(Base,BPtr);

  /**
   * Create a T object and return a smart pointer to it.
   */
  static TPtr create() { return TPtr::Create(); }

  /**
   * Return the name of class T.
   */
  static string className() { return T::className(); }

  /**
   * Return the version of class T
   */
  static int version() { return 0; }


  /**
   * The name of a file containing the dynamic
   * library where the class T is implemented.
   */
  static string library() { return ""; }

  /**
   * Write the T part of an object to a persistent stream.
   */
  static void output(tcTPtr t, PersistentOStream & os) {
    t->persistentOutput(os);
  }

  /**
   * Read the T part of an object from a persistent stream.
   */
  static void input(tTPtr t, PersistentIStream & is, int oldVersion) {
    t->persistentInput(is, oldVersion);
  }

  /**
   * Perform a dynamic cast from the given pointer to a pointer to T.
   */
  static TPtr cast(BPtr b) { return dynamic_ptr_cast<TPtr>(b); }  

  /**
   * Perform a dynamic cast from the given const pointer to a pointer
   * to const T.
   */
  static cTPtr cast(cBPtr b) { return dynamic_ptr_cast<cTPtr>(b); }

  /**
   * Perform a dynamic cast from the given transient pointer to a
   * transient pointer to T.
   */
  static tTPtr cast(tBPtr b) { return dynamic_ptr_cast<tTPtr>(b); }  

  /**
   * Perform a dynamic cast from the given transient const pointer to
   * a transient pointer to const T.
   */
  static tcTPtr cast(tcBPtr b) { return dynamic_ptr_cast<tcTPtr>(b); }

};

/**
 * The default concrete implementation of ClassTraitsBase. This
 * templated class may be specialized for any class if the default
 * implementation is not sufficient.
 */
template <typename T>
struct ClassTraits: public ClassTraitsBase<T> {};

/**
 * BaseClassTraits describes the base classes of the templated class.
 * BaseClassTraits should be specialized once for each
 * base class of a class to be described. The specializations should
 * contain a typedef so that
 * <code>BaseClassTraits<T>::NthBase</code> is made an alias for
 * the first base class of <code>T</code>,
 * <code>BaseClassTraits<T>::NthBase</code> the second base
 * class and so on. The typedef defaults to <code>int</code> which means
 * no base class.
 */
template <typename Derived, int BaseN> struct BaseClassTrait {
  /**
   * The type of the <code>BaseN</code>'th base class (int means there
   * are no further base classes).
   */
  typedef int NthBase;
};

}

// #include "ClassTraits.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ClassTraits.tcc"
#endif

#define ThePEG_DECLARE_BASE_CLASS_TRAITS_1(Class,Base)                     \
/** This template specialization informs ThePEG about the                  \
 *  base classes of Class. */                                              \
template <>                                                                \
struct BaseClassTrait<Class,1> {                                           \
  /** Typedef of the first base class of Class. */                         \
  typedef Base NthBase;                                                    \
};                                                                         \

#define ThePEG_DECLARE_BASE_CLASS_TRAITS_2(Class,Base1,Base2)              \
/** This template specialization informs ThePEG about the                  \
 *  base classes of Class. */                                              \
template <>                                                                \
struct BaseClassTrait<Class,1> {                                           \
  /** Typedef of the first base class of Class. */                         \
  typedef Base1 NthBase;                                                   \
};                                                                         \
/** This template specialization informs ThePEG about the                  \
 *  base classes of Class. */                                              \
template <>                                                                \
struct BaseClassTrait<Class,2> {                                           \
  /** Typedef of the second base class of Class. */                        \
  typedef Base2 NthBase;                                                   \
};                                                                         \

#define ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,Name,Lib)         \
/** This template specialization informs ThePEG about the name of          \
 *  the Class class and the shared object where it is defined. */          \
template <>                                                                \
struct ClassTraits<Class>:                                                 \
    public ClassTraitsBase<Class> {                                        \
  /** Return a platform-independent class name */                          \
  static string className() { return Name; }                               \
  /** Return the name of the shared library be loaded to get               \
   *  access to this class and every other class it uses                   \
   *  (except the base class). */                                          \
  static string library() { return Lib; }                                  \
}                                                                          \



#define ThePEG_DECLARE_CLASS_TRAITS(Class,Base)                           \
ThePEG_DECLARE_BASE_CLASS_TRAITS_1(Class,Base)                            \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,"ThePEG::" #Class,"")    \

#define ThePEG_DECLARE_DYNAMIC_CLASS_TRAITS(Class,Base,Lib)               \
ThePEG_DECLARE_BASE_CLASS_TRAITS_1(Class,Base)                            \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,"ThePEG::" #Class,Lib)   \

#define ThePEG_DECLARE_CLASS_TRAITS_2(Class,Base1,Base2)                  \
ThePEG_DECLARE_BASE_CLASS_TRAITS_2(Class,Base1,Base2)                     \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,"ThePEG/::" #Class,"")    \

#define ThePEG_DECLARE_DYNAMIC_CLASS_TRAITS_2(Class,Base1,Base2,Lib)      \
ThePEG_DECLARE_BASE_CLASS_TRAITS_2(Class,Base1,Base2)                     \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,"ThePEG::" #Class,Lib)   \

#define ThePEG_DECLARE_NAMED_CLASS_TRAITS(Class,Base,Name)                \
ThePEG_DECLARE_BASE_CLASS_TRAITS_1(Class,Base)                            \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,Name,"")                 \

#define ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS(Class,Base,Name,Lib)    \
ThePEG_DECLARE_BASE_CLASS_TRAITS_1(Class,Base)                            \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,Name,Lib)                \

#define ThePEG_DECLARE_NAMED_CLASS_TRAITS_2(Class,Base1,Base2,Name)       \
ThePEG_DECLARE_BASE_CLASS_TRAITS_2(Class,Base1,Base2)                     \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,Name,"")                 \

#endif /* ThePEG_ClassTraits_H */
