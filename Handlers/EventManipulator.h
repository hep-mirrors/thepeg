// -*- C++ -*-
#ifndef ThePEG_EventManipulator_H
#define ThePEG_EventManipulator_H
// This is the declaration of the EventManipulator class.

#include "ThePEG/Interface/Interfaced.h"
#include <stdexcept>
// #include "EventManipulator.fh"
// #include "EventManipulator.xh"

namespace ThePEG {

/**
 * An object of the EventManipulator class may be assigned to a
 * FullEventGenerator object. The manipulate() method is called for
 * each event generated, after the AnalysisHandlers have been called,
 * and may manipulate the event in any way needed. The manipulator may
 * alseo add StepHandlers to the EventHandler which produced the
 * event. The manipulate() method returns an integer which should be
 * zero if nothing was done to the event. If the EventHandler has
 * steps left to do, these are performed, after which the
 * <code>AnalysisHandler</code>s are called with the return value from
 * the previous manipulate() call. Then manipulate is called again and
 * the procedure is repeated until the EventHandler has no more steps
 * to do.
 *
 * @see FullEventGenerator
 * @see AnalysisHandler
 * @see EventHandler
 * @see StepHandler
 * 
 */
class EventManipulator: public Interfaced {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline EventManipulator();

  /**
   * Copy-constructor.
   */
  inline EventManipulator(const EventManipulator &);

  /**
   * Destructor.
   */
  virtual ~EventManipulator();
  //@}

public:

  /**
   * Manipulate an event and the event handler.

   * @param eh the EventHandler in charge of the generation.
   * @param event the Event to be manipulated.
   * @return zero if the event was not manipulated. Otherwise return
   * an integer which will be given to the
   * <code>AnalysisHandler</code>s of the current FullEventGenerator.
   */
  virtual int manipulate(tEHPtr eh, tEventPtr event) = 0;

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish();

  /**
   * Rebind pointer to other Interfaced objects. Called in the setup phase
   * after all objects used in an EventGenerator has been cloned so that
   * the pointers will refer to the cloned objects afterwards.
   * @param trans a TranslationMap relating the original objects to
   * their respective clones.
   * @throws RebindException if no cloned object was found for a given pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);


  /**
   * Return a vector of all pointers to Interfaced objects used in this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * Describe an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<EventManipulator> initEventManipulator;

  /**
   *  Private and non-existent assignment operator.
   */
  EventManipulator & operator=(const EventManipulator &);

};

/**
 * This template specialization informs ThePEG about the
 * base class of EventManipulator.
 */
template <>
struct BaseClassTrait<EventManipulator,1>: public ClassTraitsType {
  /** Typedef of the base class of EventManipulator. */
  typedef Interfaced NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * DecayHandler class and the shared object where it is defined.
 */
template <>
struct ClassTraits<EventManipulator>:
    public ClassTraitsBase<EventManipulator> {
  /** Return the class name. */
  static string className() {  return "ThePEG::EventManipulator"; }
};

}

#include "EventManipulator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "EventManipulator.tcc"
#endif

#endif /* ThePEG_EventManipulator_H */
