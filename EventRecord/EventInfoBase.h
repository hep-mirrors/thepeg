// -*- C++ -*-
#ifndef ThePEG_EventInfoBase_H
#define ThePEG_EventInfoBase_H
//
// This is the declaration of the <!id>EventInfoBase<!!id> class.
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

#include "ThePEG/EventRecord/EventConfig.h"
#include "ThePEG/Utilities/ClassDescription.h"
// #include "EventInfoBase.fh"
// #include "EventInfoBase.xh"

namespace ThePEG {

class EventInfoBase: public EventRecordBase {

public:

  inline EventInfoBase();
  inline EventInfoBase(const EventInfoBase &);
  virtual ~EventInfoBase();
  // Standard ctors and dtor.

public:

  virtual void rebind(const EventTranslationMap & trans);

  static void Init();
  // Standard Init function used to initialize the interface.

  inline virtual EIPtr clone() const;
  // Standard clone method.

private:

  static NoPIOClassDescription<EventInfoBase> initEventInfoBase;
  // Describe concrete class without persistent data.

  EventInfoBase & operator=(const EventInfoBase &);
  //  Private and non-existent assignment operator.

};

// CLASSDOC OFF

ThePEG_DECLARE_CLASS_TRAITS(EventInfoBase,EventRecordBase);

}

#include "EventInfoBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "EventInfoBase.tcc"
#endif

#endif /* ThePEG_EventInfoBase_H */
