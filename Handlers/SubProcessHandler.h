// -*- C++ -*-
#ifndef ThePEG_SubProcessHandler_H
#define ThePEG_SubProcessHandler_H
//
// This is the declaration of the <!id>SubProcessHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>SubProcessHandler<!!id> class is used to handle a set of
// <!class>PartonXSecFn<!!class>s together with a
// <!class>PartonExtractor<!!class>. It is used by the
// <!class>CollisionHandler<!!class> to group together different ways
// of extracting partons from incoming particles with associated hard
// parton-parton processes.
//
// Just as the <!class>PartialCollisionHandler<!!class> class (the
// base class of <!class>CollisionHandler<!!class>), a
// <!id>SubProcessHandler<!!id> keeps a full set of
// <!class>HandlerGroup<!!class>s, which may be filled with defaults
// which overrides the ones specified in the
// <!class>PartialCollisionHandler<!!class> in each event that
// <!id>SubProcessHandler<!!id> is chosen.
//
// The <!id>SubProcessHandler<!!id> has also a
// <!id>KinematicalCuts<!!id> object which is responsible for
// restricting the kinematics of the sub-process and produced
// collision. This object takes precedence over the one in the
// <!class>CollisionHandler<!!class>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PartonXSecFn.html">PartonXSecFn.h</a>
// <a href="http:PartonExtractor.html">PartonExtractor.h</a>
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>
// <a href="http:PartialCollisionHandler.html">PartialCollisionHandler.h</a>
// <a href="http:HandlerGroup.html">HandlerGroup.h</a>
// <a href="http:KinematicalCuts.html">KinematicalCuts.h</a>
// 

#include "ThePEG/Utilities/Interval.h"
#include "ThePEG/Handlers/HandlerGroup.h"
#include "ThePEG/Handlers/HandlerBase.h"


namespace ThePEG {

class SubProcessHandler: public HandlerBase {

public:

  typedef vector<HandlerGroupBase *> GroupVector;
  typedef vector<ReweightPtr> ReweightVector;

public:

  SubProcessHandler();
  SubProcessHandler(const SubProcessHandler &);
  virtual ~SubProcessHandler();
  //Default ctor and dtor.

public:

  inline tPExtrPtr pExtractor() const;
  // Return a pointer to the parton extractor used.

  inline const MEVector & MEs() const;
  // Return a reference to the vector of parton matrix elements used.

  inline tKinCutPtr cuts() const;
  // Return a pointer to the kinematical cuts used.

  const HandlerGroupBase & handlerGroup(Group::Handler) const;
  inline const GroupVector & groups() const;
  // Access to the step handler groups

  inline MEVector & MEs();
  // Return a reference to the vector of parton matrix elements used.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual IBPtr clone() const;
  virtual IBPtr fullclone() const;
  // Standard clone method.

  inline virtual void doupdate() throw(UpdateException);
  virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

private:

  void setupGroups();
  // Setup the step handler groups.

private:

  PExtrPtr thePartonExtractor;
  // The pointer to the parton extractor used.

  MEVector theMEs;
  // The vector of partonic matrix elements to be used.

  KinCutPtr theCuts;
  // The pointer to the kinematical cuts used.

  HandlerGroup<SubProcessHandler> theSubprocessGroup;
  HandlerGroup<CascadeHandler> theCascadeGroup;
  HandlerGroup<MultipleInteractionHandler> theMultiGroup;
  HandlerGroup<HadronizationHandler> theHadronizationGroup;
  HandlerGroup<DecayHandler> theDecayGroup;
  GroupVector theGroups;
  // The step handler groups

  ReweightVector reweights;
  ReweightVector preweights;
  // The pre- and re-weight objects modifying all matrix element in
  // this sub-process hander.

private:

  ThePEG_DECLARE_PREPOST_GROUP(SubProcessHandler,Post);
  ThePEG_DECLARE_GROUPINTERFACE(CascadeHandler,CascHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(MultipleInteractionHandler,MIHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(HadronizationHandler,HadrHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(DecayHandler,DecayHdlPtr);
  // Utility functions for the interface.

  static ClassDescription<SubProcessHandler> initSubProcessHandler;
  // Standard Initialization object.

private:

  const SubProcessHandler & operator=(const SubProcessHandler &);
  // Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<SubProcessHandler,1> {
  typedef HandlerBase NthBase;
};

template <>
struct ClassTraits<SubProcessHandler>:
    public ClassTraitsBase<SubProcessHandler> {
  static string className() { return "/ThePEG/SubProcessHandler"; }
};

}

#include "SubProcessHandler.icc"

#endif /* ThePEG_SubProcessHandler_H */
