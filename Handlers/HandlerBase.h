// -*- C++ -*-
#ifndef ThePEG_HandlerBase_H
#define ThePEG_HandlerBase_H
//
// This is the declaration of the <!id>HandlerBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>HandlerBase<!!id> is an abstract base class derived from the
// <!class>Interfaced<!!class> class adding some functionality such as
// easy acces to the <!class>RandomGenerator<!!class> and the
// <!class>StandardModel<!!class> object of the controlling
// <!class>EventGenerator<!!class> object. This is in fact two
// classes. <!id>HandlerBase<!!id> inherits from the templated
// <!id>HandlerBaseT<!!id> class which includes the inlined accessor
// functions. This is a trick so that classes inheriting from
// <!id>HandlerBase<!!id> need not depend on the
// <!class>EventGenerator<!!class> if the inlined accessor funtions
// are not actually used.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Interfaced.html">Interfaced.h</a>
// <a href="http:RandomGenerator.html">RandomGenerator.h</a>
// <a href="http:StandardModel.html">StandardModel.h</a>
// <a href="http:EventGenerator.html">EventGenerator.h</a>
// 

#include "ThePEG/Interface/Interfaced.h"
#include <stdexcept>

namespace ThePEG {

template <int I = 0>
class HandlerBaseT: public Interfaced {


public:

  friend class HandlerBase;

private:

  inline HandlerBaseT();
  inline HandlerBaseT(const HandlerBaseT &);
  virtual ~HandlerBaseT();
  // Standard ctors and dtor are private and can only be accessed
  // through the HandlerBase class.

public:

  inline double rnd() const;
  inline double rnd(double xu) const;
  inline double rnd(double xl, double xu) const;
  // Return a simple flat random number in the range ]0,1[, ]0,xu[ and
  // ]xl,xu[ respectively.

  inline bool rndbool() const;
  // Return 50/50.

  inline bool rndbool(double p) const;
  // Return a true with probability p.

  inline bool rndbool(double p1, double p2) const;
  // Return a true with probability p1/(p1+p2).

  inline int rndsign(double p1, double p2, double p3) const;
  // Return -1, 0, or 1 with relative probabilities p1, p2, p3.

  inline int rnd2(double p0, double p1) const;
  inline int rnd3(double p0, double p1, double p2) const;
  inline int rnd4(double p0, double p1, double p2, double p3) const;
  // Return a i with probability p_i/sum(p_i).

  inline long irnd(long xu = 2) const;
  inline long irnd(long xl, long xu) const;
  // Return a simple flat random integrer number in the range [0,xu[ and
  // [xl,xu[ respectively.

  inline const StandardModelBase & SM() const;
  inline tSMPtr standardModel() const;
  // Return a reference/pointer to the object containing the standard
  // model parameters for this run.

};

class HandlerBase: public HandlerBaseT<0> {

public:

  inline HandlerBase();
  inline HandlerBase(const HandlerBase &);
  virtual ~HandlerBase();
  // Standard ctors and dtor

public:

  static void Init();
  // Standard Init function used to initialize the interface.

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

  static AbstractNoPIOClassDescription<HandlerBase> initHandlerBase;

  HandlerBase & operator=(const HandlerBase &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<HandlerBase,1> {
  typedef Interfaced NthBase;
};
// We ignore the fact that HandlerBaseT<0> is the actual base class.

template <>
struct ClassTraits<HandlerBase>: public ClassTraitsBase<HandlerBase> {
  static string className() { return "/ThePEG/HandlerBase"; }
};

}

#include "HandlerBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HandlerBase.tcc"
#endif

#endif /* ThePEG_HandlerBase_H */
