// -*- C++ -*-
#ifndef ThePEG_ReweightMinPT_H
#define ThePEG_ReweightMinPT_H
//
// This is the declaration of the <!id>ReweightMinPT<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>ReweightMinPT<!!id> class matrix elements with the minimum of the transverse momenta of the outgoing partons to some power.
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ReweightBase.html">ReweightBase.h</a>.
// 

#include "ThePEG/MatrixElement/ReweightBase.h"
// #include "ReweightMinPT.fh"
// #include "ReweightMinPT.xh"

namespace ThePEG {

class ReweightMinPT: public ReweightBase {

public:

  inline ReweightMinPT();
  inline ReweightMinPT(const ReweightMinPT &);
  virtual ~ReweightMinPT();
  // Standard ctors and dtor.

public:

  virtual double weight() const;
  // Return the wieght for the kinematical configuation
  // previously provided by the last call to setKinematics().

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
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  double power;
  // The weight is the minimum pt^power.

private:

  static ClassDescription<ReweightMinPT> initReweightMinPT;
  // Describe an abstract base class with persistent data.

  ReweightMinPT & operator=(const ReweightMinPT &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of ReweightMinPT.
template <>
struct BaseClassTrait<ReweightMinPT,1> {
  typedef ReweightBase NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ReweightMinPT>: public ClassTraitsBase<ReweightMinPT> {
  static string className() { return "/ThePEG/ReweightMinPT"; }
  // Return the class name.
  static string library() { return "ReweightMinPT.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "ReweightMinPT.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ReweightMinPT.tcc"
#endif

#endif /* ThePEG_ReweightMinPT_H */
