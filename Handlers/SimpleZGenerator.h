// -*- C++ -*-
#ifndef THEPEG_SimpleZGenerator_H
#define THEPEG_SimpleZGenerator_H
//
// This is the declaration of the <!id>SimpleZGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Handlers/ZGenerator.h"

namespace ThePEG {

class SimpleZGenerator: public ZGenerator {

public:

  inline SimpleZGenerator();
  inline SimpleZGenerator(const SimpleZGenerator &);
  virtual ~SimpleZGenerator();
  // Standard ctors and dtor.

public:

  virtual double generate(cPDPtr q1, cPDPtr q2, Energy2 mT2 ) const;
  // Return the momentum fraction Z, of the fragmented hadron given
  // its two constituent flavours (quark, antiquark) or (quark, diquark)
  // and transverse mass squared.
 
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

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  static ClassDescription<SimpleZGenerator> initSimpleZGenerator;
  // Describe a concrete class with persistent data.

  SimpleZGenerator & operator=(const SimpleZGenerator &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of SimpleZGenerator.
template <>
struct BaseClassTrait<SimpleZGenerator,1> {
  typedef ZGenerator NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<SimpleZGenerator>
  : public ClassTraitsBase<SimpleZGenerator> {
  static string className() { return "ThePEG::SimpleZGenerator"; }
  // Return the class name.
  static string library() { return "SimpleZGenerator.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "SimpleZGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleZGenerator.tcc"
#endif

#endif /* THEPEG_SimpleZGenerator_H */
