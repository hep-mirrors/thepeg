// -*- C++ -*-
#ifndef ThePEG_AnalysisHandler_H
#define ThePEG_AnalysisHandler_H
// This is the declaration of the AnalysisHandler class.

#include "HandlerBase.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include <stdexcept>

namespace ThePEG {

/**
 * The AnalysisHandler is the base class of all analysis objects which
 * may be handled by the FullEventGenerator. The main function is the
 * virtual <code>analyze()</code> method which which is called for
 * each analysis handler after each event. The method may be called
 * several times for each event - this may be checked by the analysis
 * handler by looking at the <code>ieve</code>, <code>loop</code> and
 * <code>state</code> arguments to the <code>analyze</code> method.
 *
 * Initialization of histograms etc. should be made in the
 * <code>doinitrun()</code> function, while writing out of histograms
 * and analysis results should be performed in the
 * <code>dofinish()</code> function.
 *
 * @see \ref AnalysisHandlerInterfaces "The interfaces"
 * defined for AnalysisHandler.
 * @see FullEventGenerator
 * @see Event
 */
class AnalysisHandler: public HandlerBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline AnalysisHandler();

  /**
   * The copy constructor.
   */
  inline AnalysisHandler(const AnalysisHandler &);

  /**
   * The destructor.
   */
  virtual ~AnalysisHandler();
  //@}

public:

  /** @name Virtual functions required by the AnalysisHandler class. */
  //@{
  /**
   * Analyze a given Event. Note that a fully generated event
   * may be presented several times, if it has been manipulated in
   * between. The default version of this function will call transform
   * to make a lorentz transformation of the whole event, then extract
   * all final state particles and call analyze(tPVector) of this
   * analysis object and those of all associated analysis objects. The
   * default version will not, however, do anything on events which
   * have not been fully generated, or have been manipulated in any
   * way.
   * @param event pointer to the Event to be analyzed.
   * @param ieve the event number.
   * @param loop the number of times this event has been presented.
   * If negative the event is now fully generated.
   * @param state a number different from zero if the event has been
   * manipulated in some way since it was last presented.
   */
  virtual void analyze(tEventPtr event, long ieve, int loop, int state);

  /**
   * Transform the event to the desired Lorentz frame and return the
   * corresponding LorentzRotation.
   * @param event a pointer to the Event to be transformed.
   * @return the LorentzRotation used in the transformation.
   */
  virtual LorentzRotation transform(tEventPtr event) const;

  /**
   * Analyze the given vector of particles. The default version calls
   * analyze(tPPtr) for each of the particles.
   * @param particles the vector of pointers to particles to be analyzed
   */
  virtual void analyze(const tPVector & particles);

  /**
   * Analyze the given particle.
   * @param particle pointer to the particle to be analyzed.
   */
  virtual void analyze(tPPtr particle);

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
  virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const;

  //@}

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

private:

  /**
   * A list of slave analysis objects which are called for the same
   * extracted particles and in the same Lorentz frame as this one.
   */
  AnalysisVector theSlaves;
  //@}

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<AnalysisHandler> initAnalysisHandler;

};

/** This template specialization informs ThePEG about the
 *  base classes of AnalysisHandler. */
template <>
struct BaseClassTrait<AnalysisHandler,1>: public ClassTraitsType {
  /** Typedef of the first base class of AnalysisHandler. */
  typedef HandlerBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the AnalysisHandler class and the shared object where it is defined. */
template <>
struct ClassTraits<AnalysisHandler>: public ClassTraitsBase<AnalysisHandler> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::AnalysisHandler"; }
};

}

#include "AnalysisHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "AnalysisHandler.tcc"
#endif

#endif /* ThePEG_AnalysisHandler_H */
