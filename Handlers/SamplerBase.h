// -*- C++ -*-
#ifndef ThePEG_SamplerBase_H
#define ThePEG_SamplerBase_H
// This is the declaration of the SamplerBase class.

#include "ThePEG/Interface/Interfaced.h"
#include "SamplerBase.fh"
#include "ThePEG/Handlers/StandardEventHandler.fh"
// #include "SamplerBase.xh"

namespace ThePEG {

/**
 * This is the base class for all phase space sampler classes to be
 * used by the EventHandler class to sample the phase space according
 * to the cross sections for the processes in the EventHandler. The
 * class should be able to sample a unit hyper-cube in arbitrary
 * dimensions. The points need not necessarily be sampled with unit
 * weight.
 *
 * The virtual methods to be implemented by concrete sub-classes are
 * initialize(), generate() and rejectLast().
 *
 * @see \ref SamplerBaseInterfaces "The interfaces"
 * defined for SamplerBase.
 * @see EventHandler
 */
class SamplerBase: public Interfaced {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */

  inline SamplerBase();

  /**
   * Copy-constructor.
   */
  inline SamplerBase(const SamplerBase &);

  /**
   * Destructor.
   */
  virtual ~SamplerBase();
  //@}

public:

  /**
   * Set the event handler for which the function
   * StandardEventHandler::dSigDR(const vector<double> &) function
   * returns the cross section for the chosen phase space point.
   */
  inline void setEventHandler(tStdEHPtr eh);

  /** @name Virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * Initialize the the sampler, possibly doing presampling of the
   * phase space.
   */
  virtual void initialize() = 0;

  /**
   * Generarate a new phase space point and return a weight associated
   * with it. This weight should preferably be 1.
   */
  virtual double generate() = 0;

  /**
   * Reject the last chosen phase space point.
   */
  virtual void rejectLast() = 0;

  /**
   * Return the last generated phase space point.
   */
  inline const vector<double> & lastPoint() const;

  /**
   * If the sampler is able to sample several different functions
   * separately, this function should return the last chosen
   * function. This default version always returns 0.
   */
  virtual int lastBin() const;

  /**
   * Return the total integrated cross section determined from the
   * Monte Carlo sampling so far.
   */
  virtual CrossSection integratedXSec() const = 0;

  /**
   * Return the sum of the weights returned by generate() so far (of
   * the events that were not rejeted).
   */
  virtual double sumWeights() const = 0;
  //@}

protected:

  /**
   * Return the last generated phase space point.
   */
  inline vector<double> & lastPoint();

  /**
   * Return the associated event handler.
   */
  inline tStdEHPtr eventHandler() const;

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
   * Standard Init function used to initialize the interfaces.
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
   * Return a vector of all pointers to Interfaced objects used in
   * this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * The associated event handler.
   */
  tStdEHPtr theEventHandler;

  /**
   * The last generated phase space point.
   */
  vector<double> theLastPoint;

private:

  /**
   * Describe an abstract base class with persistent data.
   */
  static AbstractClassDescription<SamplerBase> initSamplerBase;

  /**
   *  Private and non-existent assignment operator.
   */
  SamplerBase & operator=(const SamplerBase &);

};

}


namespace ThePEG {

template <>
/**
 * This template specialization informs ThePEG about the base class of
 * SamplerBase.
 */
struct BaseClassTrait<SamplerBase,1>: public ClassTraitsType {
  /** Typedef of the base class of SamplerBase. */
  typedef Interfaced NthBase;
};

template <>
/**
 * This template specialization informs ThePEG about the name of the
 * SamplerBase class.
 */
struct ClassTraits<SamplerBase>: public ClassTraitsBase<SamplerBase> {
  /** Return the class name. */
  static string className() { return "ThePEG::SamplerBase"; }

};

}

#include "SamplerBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SamplerBase.tcc"
#endif

#endif /* ThePEG_SamplerBase_H */
