// -*- C++ -*-
#ifndef ThePEG_SubProcessHandler_H
#define ThePEG_SubProcessHandler_H
// This is the declaration of the SubProcessHandler class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Interval.h"
#include "ThePEG/Handlers/HandlerGroup.h"
#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/MatrixElement/MEBase.fh"
#include "SubProcessHandler.fh"


namespace ThePEG {

/**
 * The SubProcessHandler class is used to handle a set of MEBase
 * objects together with a PartonExtractor. It is used by the
 * StandardEventHandler to group together different ways of extracting
 * partons from incoming particles with associated hard parton-parton
 * matrix elements.
 *
 * Just as the EventHandler class, a SubProcessHandler keeps a full
 * set of <code>HandlerGroup</code>s, which may be filled with
 * defaults which overrides the ones specified in the EventHandler in
 * each event the SubProcessHandler is chosen.
 *
 * The SubProcessHandler has also a KinematicalCuts object which is
 * responsible for restricting the kinematics of the sub-process and
 * produced collision. This object takes precedence over the one in
 * the EventHandler in each event the SubProcessHandler is chosen.
 *
 * @see \ref SubProcessHandlerInterfaces "The interfaces"
 * defined for SubProcessHandler.
 * @see MEBase
 * @see PartonExtractor
 * @see EventHandler
 * @see StandardEventHandler
 * @see HandlerGroup
 * @see KinematicalCuts
 */
class SubProcessHandler: public HandlerBase {

public:

  /** A vector of HandlerGroup pointers. */
  typedef vector<HandlerGroupBase *> GroupVector;

  /** A vector of ReweightBase pointers. */
  typedef vector<ReweightPtr> ReweightVector;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  SubProcessHandler();

  /**
   * Copy-constructor.
   */
  SubProcessHandler(const SubProcessHandler &);

  /**
   * Destructor.
   */
  virtual ~SubProcessHandler();
  //@}

public:

  /** @name Access objects assigned to the SubProcessHandler. */
  //@{
  /**
   * Return a pointer to the parton extractor used.
   */
  inline tPExtrPtr pExtractor() const;

  /**
   * Return a reference to the vector of parton matrix elements used.
   */
  inline const MEVector & MEs() const;

  /**
   * Return a pointer to the kinematical cuts used.
   */
  inline tKinCutPtr cuts() const;

  /**
   * Access a step handler group.
   */
  const HandlerGroupBase & handlerGroup(Group::Handler) const;

  /**
   * Access the step handler groups.
   */
  inline const GroupVector & groups() const;

  /**
   * Return a reference to the vector of parton matrix elements used.
   */
  inline MEVector & MEs();
  //@}

public:

  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(PersistentOStream & os) const;

  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(PersistentIStream & is, int version);
  //@}

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr fullclone() const;
  //@}

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit() throw(InitException);

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish();
  //@}

private:

  /**
   * Setup the step handler groups.
   */
  void setupGroups();

private:

  /**
   * The pointer to the parton extractor used.
   */
  PExtrPtr thePartonExtractor;

  /**
   * The vector of partonic matrix elements to be used.
   */
  MEVector theMEs;

  /**
   * The pointer to the kinematical cuts used.
   */
  KinCutPtr theCuts;

  /**
   * The SubProcessHandler group.
   */
  HandlerGroup<SubProcessHandler> theSubprocessGroup;

  /**
   * The CascadeHandler group.
   */
  HandlerGroup<CascadeHandler> theCascadeGroup;

  /**
   * The MultipleInteractionHandler group.
   */
  HandlerGroup<MultipleInteractionHandler> theMultiGroup;

  /**
   * The HadronizationHandler group.
   */
  HandlerGroup<HadronizationHandler> theHadronizationGroup;

  /**
   * The DecayHandler group.
   */
  HandlerGroup<DecayHandler> theDecayGroup;

  /**
   * The step handler groups.
   */
  GroupVector theGroups;

  /**
   * The pre- and re-weight objects modifying all matrix element in
   * this sub-process hander.
   */
  ReweightVector reweights;
  /**
   * The pre- and re-weight objects modifying all matrix element in
   * this sub-process hander.
   */
  ReweightVector preweights;

private:

  ThePEG_DECLARE_PREPOST_GROUP(SubProcessHandler,Post);
  ThePEG_DECLARE_GROUPINTERFACE(CascadeHandler,CascHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(MultipleInteractionHandler,MIHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(HadronizationHandler,HadrHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(DecayHandler,DecayHdlPtr);

  /**
   * Describe a concreta class with persistent data.
   */
  static ClassDescription<SubProcessHandler> initSubProcessHandler;

private:

  /**
   * Private and non-existent assignment operator.
   */
  const SubProcessHandler & operator=(const SubProcessHandler &);

};

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of SubProcessHandler. */
template <>
struct BaseClassTrait<SubProcessHandler,1>: public ClassTraitsType {
  /** Typedef of the first base class of SubProcessHandler. */
  typedef HandlerBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the SubProcessHandler class and the shared object where it is defined. */
template <>
struct ClassTraits<SubProcessHandler>:
    public ClassTraitsBase<SubProcessHandler> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::SubProcessHandler"; }
};

/** @endcond */

}

#include "SubProcessHandler.icc"

#endif /* ThePEG_SubProcessHandler_H */
