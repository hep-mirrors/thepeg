// -*- C++ -*-
#ifndef ThePEG_MultiEventGenerator_H
#define ThePEG_MultiEventGenerator_H
//
// This is the declaration of the <!id>MultiEventGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>MultiEventGenerator<!!id> class is derived from the
// <!class>FullEventGenerator<!!class> and is capable of making
// several runs with a pre-defined set of parameter and switch values.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:FullEventGenerator.html">FullEventGenerator.h</a>.
// 

#include "FullEventGenerator.h"
// #include "MultiEventGenerator.fh"
// #include "MultiEventGenerator.xh"

namespace ThePEG {

class MultiEventGenerator: public FullEventGenerator {

public:

  inline MultiEventGenerator();
  inline MultiEventGenerator(const MultiEventGenerator &);
  virtual ~MultiEventGenerator();
  // Standard ctors and dtor.

protected:

  virtual void doGo(long next, long maxevent);
  // Run this EventGenerator session.

  string addInterface(string);
  // Used to add an interface of an object which should be used with a
  // set of different values. The argument should be given as
  // "object:interface arg1, arg2, ..."

  string removeInterface(string);
  // Used to remove an interface of an object which should be used with a
  // set of different values. The argument should be given as
  // "object:interface arg1, arg2, ..."

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void doinitrun();
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  virtual void rebind(const TranslationMap & trans) throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  typedef vector<string> StringVector;

  IVector theObjects;
  StringVector theInterfaces;
  StringVector thePosArgs;
  vector<StringVector> theValues;

private:

  static ClassDescription<MultiEventGenerator> initMultiEventGenerator;
  // Describe a concrete class with persistent data.

  MultiEventGenerator & operator=(const MultiEventGenerator &);
  //  Private and non-existent assignment operator.

};

// CLASSDOC OFF

// The following template specialization informs ThePEG about the
// base class of MultiEventGenerator.
template <>
struct BaseClassTrait<MultiEventGenerator,1> {
  typedef FullEventGenerator NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<MultiEventGenerator>:
    public ClassTraitsBase<MultiEventGenerator> {
  static string className() { return "/ThePEG/MultiEventGenerator"; }
  // Return the class name.
  static string library() { return "MultiEventGenerator.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "MultiEventGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MultiEventGenerator.tcc"
#endif

#endif /* ThePEG_MultiEventGenerator_H */
