// -*- C++ -*-
#ifndef ThePEG_ClassTraits_H
#define ThePEG_ClassTraits_H
//
// This is the declaration of the <!id>ClassTraitsBase<!!id>,
// <!id>ClassTraits<!!id> and <!id>BaseClassTraits<!!id> classes.
//
// CLASSDOC SUBSECTION Description:
//
// The templated <!id>ClassTraitsBase<!!id> class defines a set of
// default information about classes used by ThePEG. By default, the
// <!id>ClassTraits<!!id> simply inherits from
// <!id>ClassTraitsBase<!!id>, but it can be specialized to override
// the static member functions.
//
// The information that should be made available is:<BR>
// <!id>create()<!!id> creates an object of the described class,<BR>
// <!id>className()<!!id> returns the name of the class,<BR>
// <!id>version()<!!id> return the version number,<BR>
// <!id>output()<!!id> output the members of the class to a
// <!class>PersistentOStream<!!class>,<BR> <!id>output()<!!id> reads
// the members of the class from a <!class>PersistentIStream<!!class>
// and<BR> <!id>cast()<!!id> dynamically cast a pointer to
// <!id>Base<!!id> to a pointer to the class.
//
// The <!id>BaseClassTraits<!!id> should be specialized once for each
// base class of a class to be described. The specializations should
// contain a typedef so that
// <!id>BaseClassTraits&lt;T,1&gt;::NthBase<!!id> is made an alias for
// the first base class of <!id>T<!!id>,
// <!id>BaseClassTraits&lt;T,2&gt;::NthBase<!!id> the second base
// class and so on. The typedef defaults to <!id>int<!!id> which means
// no base class.
//
// This header file also defines a couple of macros for easy
// specialization of <!id>ClassTraits<!!id> and
// <!id>BaseClassTraits<!!id>:<BR>
// <!id>ThePEG_DECLARE_CLASS_TRAITS(Class,Base)<!!id> defines traits
// classes for <!id>Class<!!id> with base class <!id>Base<!!id> giving
// it the class name /ThePEG/Class<BR>
// <!id>ThePEG_DECLARE_CLASS_TRAITS2(Class,Base1,Base2)<!!id> defines
// traits classes for <!id>Class<!!id> with base classes
// <!id>Base1<!!id> and <!id>Base2 and <!!id> giving it the class name
// /Pyythia7/Class and<BR>
// <!id>ThePEG_DECLARE_NAMED_CLASS_TRAITS(Class,Base,Name)<!!id>
// defines traits classes for <!id>Class<!!id> with base class
// <!id>Base<!!id> giving it the class name <!id>Name<!!id>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PersistentOStream.html">PersistentOStream.h</a>,
// <a href="http:PersistentIStream.html">PersistentIStream.h</a>.
// 


#include "ThePEG/Config/ThePEG.h"
// #include "ClassTraits.fh"
// #include "ClassTraits.xh"
#include "ThePEG/Persistency/PersistentOStream.fh"
#include "ThePEG/Persistency/PersistentIStream.fh"


namespace ThePEG {

template <class T>
struct ClassTraitsBase {

  ThePEG_DECLARE_TEMPLATE_POINTERS(T,TPtr);
  ThePEG_DECLARE_POINTERS(Base,BPtr);

  static TPtr create() { return TPtr::Create(); }
  // Create a T object and return a smart pointer to it.

  static string className() { return T::className(); }
  // Return the name of class T.

  static int version() { return 0; }
  // Return the version of class T

  static string library() { return ""; }

  static void output(tcTPtr t, PersistentOStream & os) {
    t->persistentOutput(os);
  }
  // Write the T part of an object to a persistent stream.

  static void input(tTPtr t, PersistentIStream & is, int oldVersion) {
    t->persistentInput(is, oldVersion);
  }
  // Read the T part of an object from a persistent stream.

  static TPtr cast(BPtr b) { return dynamic_ptr_cast<TPtr>(b); }  
  static cTPtr cast(cBPtr b) { return dynamic_ptr_cast<cTPtr>(b); }
  static tTPtr cast(tBPtr b) { return dynamic_ptr_cast<tTPtr>(b); }  
  static tcTPtr cast(tcBPtr b) { return dynamic_ptr_cast<tcTPtr>(b); }
  // Perform a dynamic cast.

};

template <class T>
struct ClassTraits: public ClassTraitsBase<T> {};

template <class Derived, int BaseN> struct BaseClassTrait {
  typedef int NthBase;
};

}

// #include "ClassTraits.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ClassTraits.tcc"
#endif

#define ThePEG_DECLARE_BASE_CLASS_TRAITS_1(Class,Base)                    \
template <>                                                                \
struct BaseClassTrait<Class,1> {                                           \
  typedef Base NthBase;                                                    \
};                                                                         \

#define ThePEG_DECLARE_BASE_CLASS_TRAITS_2(Class,Base1,Base2)             \
template <>                                                                \
struct BaseClassTrait<Class,1> {                                           \
  typedef Base1 NthBase;                                                   \
};                                                                         \
template <>                                                                \
struct BaseClassTrait<Class,2> {                                           \
  typedef Base2 NthBase;                                                   \
};                                                                         \

#define ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,Name,Lib)        \
template <>                                                                \
struct ClassTraits<Class>:                                                 \
    public ClassTraitsBase<Class> {                                        \
  static string className() { return Name; }                               \
  static string library() { return Lib; }                                  \
}                                                                          \



#define ThePEG_DECLARE_CLASS_TRAITS(Class,Base)                           \
ThePEG_DECLARE_BASE_CLASS_TRAITS_1(Class,Base)                            \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,"/ThePEG/" #Class,"")   \

#define ThePEG_DECLARE_DYNAMIC_CLASS_TRAITS(Class,Base,Lib)               \
ThePEG_DECLARE_BASE_CLASS_TRAITS_1(Class,Base)                            \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,"/ThePEG/" #Class,Lib)  \

#define ThePEG_DECLARE_CLASS_TRAITS_2(Class,Base1,Base2)                  \
ThePEG_DECLARE_BASE_CLASS_TRAITS_2(Class,Base1,Base2)                     \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,"/ThePEG/" #Class,"")   \

#define ThePEG_DECLARE_DYNAMIC_CLASS_TRAITS_2(Class,Base1,Base2,Lib)      \
ThePEG_DECLARE_BASE_CLASS_TRAITS_2(Class,Base1,Base2)                     \
ThePEG_DECLARE_NAMED_DYNAMIC_CLASS_TRAITS_(Class,"/ThePEG/" #Class,Lib)  \

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
