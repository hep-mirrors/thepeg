// -*- C++ -*-
#ifndef ThePEG_HandlerGroup_H
#define ThePEG_HandlerGroup_H
//
// This is the declaration of the <!id>HandlerGroup<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>HandlerGroup<!!id> is a templated utility class to manage a
// group of <!class>StepHandler<!!class>s. All <!id>HandlerGroup<!!id>
// classes are derived from the <!id>HandlerGroupBase<!!id> class. As
// an example the specialization
// <!id>HandlerGroup&lt;CascadeHandler&gt;<!!id> keeps a
// <!class>CascadeHandler<!!class> object and associated pre- and
// post- <!class>StepHandler<!!class>s, defining shich steps should be
// performed before the perturbative cascade, which object should be
// used for the cascade and which steps should be performed after.
//
// The <!id>HandlerGroup<!!id> keesp both a default main handler and
// the corresponding default pre- and post- handlers as well as the
// main handler and pre/post hadlers chosen for the current event. The
// current handlers are accompanied by
// <!class>Hint<!!class>s. Handlers which are copied from the default
// ones are accompanied by the default <!class>Hint<!!class>, while
// handlers supplied from the outside may be accompanied by any kind
// of hint. The main handler can be supplied with several hints, the
// pre- and post- handlers may only have one hint each.
//
// The <!id>HandlerGroup<!!id> class is used in the
// PartialCollisionHandler and SubProcessHandler to manage the
// post-sub-process handler, the cascade, multiple interaction,
// hadronization and decay handler groups.
// 
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PartialCollisionHandler.html">PartialCollisionHandler.h</a>
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>
// <a href="http:StepHandler.html">StepHandler.h</a>
// <a href="http:CascadeHandler.html">CascadeHandler.h</a>
// <a href="http:MultipleInteractionHandler.html">MultipleInteractionHandler.h</a>
// <a href="http:HadronizationHandler.html">HadronizationHandler.h</a>
// <a href="http:DecayHandler.html">DecayHandler.h</a>
// 

#include "ThePEG/Config/ThePEG.h"
// #include "HandlerGroup.fh"
// #include "HandlerGroup.xh"

namespace ThePEG {

class HandlerGroupBase {

public:

  typedef pair<StepHdlPtr, HintPtr> StepWithHint;
  typedef vector<StepHdlPtr> StepVector;
  typedef vector<StepWithHint> StepHintVector;
  typedef deque<HintPtr> HintVector;

public:

  HandlerGroupBase();
  virtual ~HandlerGroupBase();
  // Standard ctor and dtor

  inline bool empty() const;
  // returns true if current selections in this group is empty.

  inline void init(const HandlerGroupBase &);
  // Initialize, taking the default StepHandlers as the current ones,
  // possibly overridden by the default ones in the auxilliary group
  // supplied in the argument.

  StepWithHint next();
  // Return the next step;

  void addPreHandler(tStepHdlPtr s, tHintPtr h,
		     const HandlerGroupBase &);
  // Add a step handler to the current list of pre- handlers.

  void addPostHandler(tStepHdlPtr s, tHintPtr h,
		      const HandlerGroupBase &);
  // Add a step handler to the current list of post- handlers.

  void addHint(tHintPtr h, const HandlerGroupBase &);
  // Add a hint to the currently selected main handler.

  inline StepVector & preHandlers();
  inline const StepVector & preHandlers() const;
  // Return a reference to the list of default pre- handlers.

  virtual tStepHdlPtr defaultHandler() const = 0;
  // Return a pointer to the default main handler.

  inline StepVector & postHandlers();
  inline const StepVector & postHandlers() const;
  // Return a reference to the list of default post- handlers.

  virtual tStepHdlPtr handler() const = 0;
  // Return a pointer to the current main handler.

  virtual void setHandler() = 0;
  // Unset the current main handler.

  virtual bool setHandler(tStepHdlPtr, const HandlerGroupBase &) = 0;
  // Set the current main handler, but also refill the current pre-
  // and post- handlers with the defaults.

  virtual void refillDefaultHandler(tStepHdlPtr) = 0;
  // Set the current main handler. If the null pointer use the default
  // main handler.

  void refillDefaults(const HandlerGroupBase &);
  // Fill main, pre- and post- handlers with the default ones. If the
  // default handlers in the argument takes precedence to this.

  virtual void clear();
  // Clear all current handlers, but don't touch the default ones.

  virtual string handlerClass() const = 0;
  // Return the base class name of the main handler type.

  void interfaceSetPrehandler(StepHdlPtr p, int i);
  void interfaceInsertPrehandler(StepHdlPtr p, int i);
  void interfaceErasePrehandler(int i);
  vector<StepHdlPtr> interfaceGetPrehandlers() const;
  void interfaceSetPosthandler(StepHdlPtr p, int i);
  void interfaceInsertPosthandler(StepHdlPtr p, int i);
  void interfaceErasePosthandler(int i);
  vector<StepHdlPtr> interfaceGetPosthandlers() const;
  // Utility functions used for the interface.

  virtual void write(PersistentOStream &) const;
  virtual void read(PersistentIStream &);
  // Read and write from/to persistent streams.

protected:

  HandlerGroupBase(const HandlerGroupBase &);

  bool isEmpty;

private:

  void checkInsert(StepHintVector & current, const StepVector & def);
  // Add handlers from the def vector to the current, supplying them
  // with default hints.

protected:

  StepVector theDefaultPreHandlers;
  StepVector theDefaultPostHandlers;
  StepHintVector thePreHandlers;
  HintVector theHints;
  StepHintVector thePostHandlers;
  // The default and current handlers with hints.

private:

  HandlerGroupBase & operator=(const HandlerGroupBase &);
  // Assignment is private.
  
};

template <typename HDLR>
class HandlerGroup: public HandlerGroupBase {

public:

  typedef typename Ptr<HDLR>::pointer HdlPtr;
  typedef typename Ptr<HDLR>::transient_pointer tHdlPtr;

public:

  HandlerGroup();
  HandlerGroup(const HandlerGroup<HDLR> &);
  ~HandlerGroup();
  // Standard ctors and dtor.

  virtual bool setHandler(tStepHdlPtr, const HandlerGroupBase &);
  // Set the current main handler, but also refill the current pre-
  // and post- handlers with the defaults.

  inline virtual void setHandler();
  // Unset the current main handler.

  inline virtual tStepHdlPtr handler() const;
  // Return a pointer to the current main handler.

  inline virtual tStepHdlPtr defaultHandler() const;
  // Return a pointer to the default main handler.

  virtual void refillDefaultHandler(tStepHdlPtr);
  // Set the current main handler. If the null pointer use the default
  // main handler.

  virtual void clear();
  // Clear all current handlers, but don't touch the default ones.

  virtual string handlerClass() const;
  // Return the base class name of the main handler type.

  void interfaceSetHandler(HdlPtr);
  HdlPtr interfaceGetHandler() const;
  // Utility functions used for the interface.

  inline virtual void write(PersistentOStream &) const;
  inline virtual void read(PersistentIStream &);
  // Read and write from/to persistent streams.

private:


  HdlPtr theDefaultHandler;
  HdlPtr theHandler;
  // The default and current main handler.

private:

  HandlerGroup<HDLR> & operator=(const HandlerGroup<HDLR> &);
  // Assignment is private.
  
};

namespace Group {
enum Handler { subproc, cascade, multi, hadron, decay };
enum Level { before, main, after };
// Enumerations for indexing of different HandlerGroup.
}

// CLASSDOC OFF

template <typename HDLR>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const HandlerGroup<HDLR> &);

template <typename HDLR>
inline PersistentIStream & operator>>(PersistentIStream &,
				      HandlerGroup<HDLR> &);

}

#define ThePEG_DECLARE_PREPOST_GROUP(HandlerClass,prepost)                    \
void interfaceSet##prepost##HandlerClass(StepHdlPtr, int);                   \
void interfaceInsert##prepost##HandlerClass(StepHdlPtr, int);               \
void interfaceErase##prepost##HandlerClass(int);                             \
vector<StepHdlPtr> interfaceGet##prepost##HandlerClass() const

#define ThePEG_DECLARE_GROUPINTERFACE(HandlerClass,ptr)                       \
ThePEG_DECLARE_PREPOST_GROUP(HandlerClass,Pre);                               \
void interfaceSet##HandlerClass(ptr);                                    \
ptr interfaceGet##HandlerClass() const;                                      \
ThePEG_DECLARE_PREPOST_GROUP(HandlerClass,Post)

#define ThePEG_IMPLEMENT_PREPOST_GROUP(ThisClass,HandlerClass,member,pp)      \
void ThisClass::interfaceSet##pp##HandlerClass(StepHdlPtr p , int i) {     \
  member.interfaceSet##pp##handler(p,i);                                     \
}                                                                              \
void ThisClass::interfaceInsert##pp##HandlerClass(StepHdlPtr p, int i) {   \
  member.interfaceInsert##pp##handler(p,i);                                  \
}                                                                              \
void ThisClass::interfaceErase##pp##HandlerClass(int i) {                  \
  member.interfaceErase##pp##handler(i);                                     \
}                                                                              \
vector<StepHdlPtr> ThisClass::interfaceGet##pp##HandlerClass() const {     \
  return member.interfaceGet##pp##handlers();                                  \
}

#define ThePEG_IMPLEMENT_GROUPINTERFACE(ThisClass,HandlerClass,member,ptr)    \
ThePEG_IMPLEMENT_PREPOST_GROUP(ThisClass,HandlerClass,member,Pre)             \
void ThisClass::interfaceSet##HandlerClass(ptr p) {                      \
  member.interfaceSetHandler(p);                                             \
}                                                                              \
ptr ThisClass::interfaceGet##HandlerClass() const {                        \
  return member.interfaceGetHandler();                                       \
}                                                                              \
ThePEG_IMPLEMENT_PREPOST_GROUP(ThisClass,HandlerClass,member,Post)            \

#define ThePEG_DECLARE_PREPOST_OBJECTS(ThisClass,HandlerClass,pp,ba)          \
static RefVector<ThisClass,StepHandler> interface##pp##HandlerClass            \
(#pp #HandlerClass "s",                                                        \
 "A list of handlers to be called " #ba " the " #HandlerClass ". "             \
 "If handler objects are specified in a CollisionHandler and "                 \
 "the SubProcessHandler chosen in a given collision also specifies some, "     \
 "the latter will caled first.",                                               \
 0, 0, false, false, true, false,                                             \
 &ThisClass::interfaceSet##pp##HandlerClass,                               \
 &ThisClass::interfaceInsert##pp##HandlerClass,                            \
 &ThisClass::interfaceErase##pp##HandlerClass,                             \
 &ThisClass::interfaceGet##pp##HandlerClass)

 
#define ThePEG_DECLARE_GROUPINTERFACE_OBJECTS(ThisClass,HandlerClass)         \
ThePEG_DECLARE_PREPOST_OBJECTS(ThisClass,HandlerClass,Pre, before);           \
static Reference<ThisClass,HandlerClass> interface ## HandlerClass             \
(#HandlerClass,                                                                \
 "The " #HandlerClass " object used in this " #ThisClass ". "                  \
 "If a " #HandlerClass " object is specified in a CollisionHandler and "       \
 "the SubProcessHandler chosen in a given collision also specifies one,"       \
 "the latter will be used.",                                                   \
 0, false, false, true, true,                                                 \
 &ThisClass::interfaceSet ## HandlerClass,                                     \
 &ThisClass::interfaceGet ## HandlerClass);                                    \
ThePEG_DECLARE_PREPOST_OBJECTS(ThisClass,HandlerClass,Post, after)

// CLASSDOC ON

#include "HandlerGroup.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "HandlerGroup.tcc"
#endif

#endif /* ThePEG_HandlerGroup_H */
