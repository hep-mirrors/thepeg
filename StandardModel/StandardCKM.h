// -*- C++ -*-
#ifndef ThePEG_StandardCKM_H
#define ThePEG_StandardCKM_H
//
// This is the declaration of the <!id>StandardCKM<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>StandardCKM<!!id> inherits from <!class>CKMBase<!!class> and
// implements the standard parameterization of the CKM matrix in terms
// of three angles and a phase.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:CKMBase.html">CKMBase.h</a>.
// 

#include "CKMBase.h"
// #include "StandardCKM.fh"
// #include "StandardCKM.xh"

namespace ThePEG {

class StandardCKM: public CKMBase {

public:

  inline StandardCKM();
  inline StandardCKM(const StandardCKM &);
  virtual ~StandardCKM();
  // Standard ctors and dtor

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

public:

  virtual vector< vector<double> >  getMatrix(unsigned int nFamilies) const;
  // Return the matrix of squared matrix elements.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual IBPtr clone() const;
  virtual IBPtr fullclone() const;
  // Standard clone methods

  inline virtual void
  rebind(const TranslationMap & trans) throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  double theta12;
  double theta13;
  double theta23;
  double delta;

private:

  static ClassDescription<StandardCKM> initStandardCKM;

  StandardCKM & operator=(const StandardCKM &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<StandardCKM,1> {
  typedef CKMBase NthBase;
};

template <>
struct ClassTraits<StandardCKM>: public ClassTraitsBase<StandardCKM> {
  static string className() { return "/ThePEG/StandardCKM"; }
  static string library() { return "StandardCKM.so"; }
};

}

#include "StandardCKM.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StandardCKM.tcc"
#endif

#endif /* ThePEG_StandardCKM_H */
