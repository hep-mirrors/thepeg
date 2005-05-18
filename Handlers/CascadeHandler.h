// -*- C++ -*-
#ifndef ThePEG_CascadeHandler_H
#define ThePEG_CascadeHandler_H
// This is the declaration of the CascadeHandler class.

#include "StepHandler.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
#include "ThePEG/PDF/PDF.h"
// #include "CascadeHandler.fh"
// #include "CascadeHandler.xh"

namespace ThePEG {


/**
 * The CascadeHandler is the base class of all handlers implementing
 * perturbative partonic cascade models. It is derived from the more
 * general StepHandler class, and implements the handle() function to
 * do some standard initialization before calling the main cascade()
 * function.
 *
 * @see \ref CascadeHandlerInterfaces "The interfaces"
 * defined for CascadeHandler.
 * @see StepHandler
 * @see EventHandler
 * @see SubProcessHandler
 */
class CascadeHandler: public StepHandler, public LastXCombInfo<> {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  CascadeHandler();

  /**
   * The copy constructor.
   */
  CascadeHandler(const CascadeHandler &);

  /**
   * The destructor.
   */
  virtual ~CascadeHandler();
  //@}

public:

  /** @name Virtual functions required by the StepHandler class. */
  //@{
  /**
    * The main function called by the EventHandler class to
    * perform a step.
    * @param eh the EventHandler in charge of the Event generation.
    * @param tagged if not empty these are the only particles which should
    * be considered by the StepHandler.
    * @param hint a Hint object with possible information from previously
    * performed steps.
    * @throws Veto if the StepHandler requires the current step to be
    * discarded.
    * @throws Stop if the generation of the current Event should be stopped
    * after this call.
    * @throws Exception if something goes wrong.
    */
  virtual void handle(EventHandler & eh, const tPVector & tagged,
		      const Hint & hint)
    ThePEG_THROW_SPEC((Veto, Stop, Exception));
  //@}

  /**
   * The main function to be overwritten by sub-classes. It is called
   * by handle() after storing some information which is then
   * available through simple access functions.
   */
  virtual void cascade() = 0;

public:

  /** @name Access information stored by the handle() function. */
  //@{
  /**
   * Return the vector of tagged particles which should be
   * showered. It the vector is empty, the patons from the current
   * sub-process is supposed to be showered.
   */
  inline const tPVector & tagged() const;

  /**
   * Return the int provided in the current call to handle().
   */
  inline const Hint & hint() const;

  /**
   * Return references to the PDF used by the first incoming particle.
   */
  inline const PDF & firstPDF() const;

  /**
   * Return references to the PDF used by the first incoming particle.
   */
  inline const PDF & secondPDF() const;

  /**
   * Return references to the currently used PDF's.
   */
  inline const pair<PDF,PDF> & pdfs() const;

  /**
   * Return a pointer to the current collision handler.
   */
  inline tEHPtr eventHandler() const;
  //@}

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
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  inline virtual void doinitrun();

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
   * Store the tagged argument given to handle().
   */
  const tPVector * theTagged;

  /**
   * Store the Hint arguments given to handle().
   */
  const Hint * theHint;

  /**
   * The pdfs used to extract the incoming partons.
   */
  pair<PDF,PDF> thePDFs;

  /**
   * The current collision handler.
   */
  tEHPtr theEventHandler;

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<CascadeHandler> initCascadeHandler;

  /**
   *  Private and non-existent assignment operator.
   */
  CascadeHandler & operator=(const CascadeHandler &);

};

/** This template specialization informs ThePEG about the
 *  base classes of CascadeHandler. */
template <>
struct BaseClassTrait<CascadeHandler,1>: public ClassTraitsType {
  /** Typedef of the first base class of CascadeHandler. */
  typedef StepHandler NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the CascadeHandler class and the shared object where it is defined. */
template <>
struct ClassTraits<CascadeHandler>: public ClassTraitsBase<CascadeHandler> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::CascadeHandler"; }
};

}

#include "CascadeHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "CascadeHandler.tcc"
#endif

#endif /* ThePEG_CascadeHandler_H */
