// -*- C++ -*-
#ifndef ThePEG_PartialEventGenerator_H
#define ThePEG_PartialEventGenerator_H
//
// This is the declaration of the <!id>PartialEventGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>PartialEventGenerator<!!id> inherits from the
// <!class>EventGenerator<!!class> class and has a pointer to an
// <!class>PartialCollisionHandler<!!class> which is not able to
// generate full event, hence the <!id>go()<!!id> and
// <!id>shoot()<!!id> methods are inactive.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:EventGenerator.html">EventGenerator.h</a>,
// <a href="http:PartialCollisionHandler.html">PartialCollisionHandler.h</a>.
// 

#include "ThePEG/Repository/EventGenerator.h"
// #include "PartialEventGenerator.fh"
// #include "PartialEventGenerator.xh"

namespace ThePEG {

class PartialEventGenerator: public EventGenerator {

public:

  PartialEventGenerator();
  PartialEventGenerator(const PartialEventGenerator &);
  virtual ~PartialEventGenerator();
  // Standard ctors and dtor

public:

  inline tPartCollHdlPtr handler() const;
  // Return a pointer to the PatrialCollisionHandler.
  
  virtual tcEventPtr currentEvent() const;
  // Return the event being generated.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual EventPtr doShoot();
  // Generate one event. 

  virtual EventPtr doPartialEvent(tEventPtr);
  // Finish generating an event constructed from the outside. 

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

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

  PartCollHdlPtr theHandler;
  // Pointer to the PatrialCollisionHandler.

private:

  static ClassDescription<PartialEventGenerator> initPartialEventGenerator;

  PartialEventGenerator & operator=(const PartialEventGenerator &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<PartialEventGenerator,1> {
  typedef EventGenerator NthBase;
};

template <>
struct ClassTraits<PartialEventGenerator>:
    public ClassTraitsBase<PartialEventGenerator> {
  static string className() { return "/ThePEG/PartialEventGenerator"; }
};

}

#include "PartialEventGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartialEventGenerator.tcc"
#endif

#endif /* ThePEG_PartialEventGenerator_H */
