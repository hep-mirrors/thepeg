// -*- C++ -*-
#ifndef ThePEG_Amplitude_H
#define ThePEG_Amplitude_H
// This is the declaration of the Amplitude class.


#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Config/Complex.h"
// #include "Amplitude.fh"
// #include "Amplitude.xh"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/EventRecord/Particle.h"

namespace ThePEG {

/**
 * The Amplitude class is the abstract base class for all the classes
 * representing complex amplitudes associated with either a hard
 * 2\f$\rightarrow\f$N subprocess or a decay 1\f$\rightarrow\f$N
 * process.  The returned value should be dimensionless suitable
 * scaled by the total invariant mass squared (shat), which is always
 * computable from the specified momenta of the particles in the
 * vertex.  Notice that the amplitude for splitting
 * 1\f$\rightarrow\f$N processes is instead represented in other
 * classes (derived from the SplitFun class).
 *
 * @see \ref AmplitudeInterfaces "The interfaces"
 * defined for Amplitude.
 */
class Amplitude: public HandlerBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  Amplitude();

  /**
   * Copy-constructor.
   */
  Amplitude(const Amplitude &);

  /**
   * Destructor.
   */
  virtual ~Amplitude();
  //@}

  /** @name Main virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * Return the amplitude. Given the ParticleData objects in \a
   * particles, their \a momenta and \a helicities of all the
   * particles in the vertex, return the complex amplitude.  The
   * convention is the order of the vectors is that first there is the
   * incoming particle(s) and then the outgoing ones.  For the
   * helicities, the convention is to number them starting from 0 (no
   * negative values, because they are used as vector indeces), for
   * example, for a massive particle of spin S, 0 <= helicity <= 2*S.
   * The returned value should be dimensionless suitable scaled by the
   * total invariant mass squared (\f$\hat{s}\f$), which is always
   * computable from the specified \a momenta of the particles in the
   * vertex.
   */
  virtual Complex value(const tcPDVector & particles,
			const vector<Lorentz5Momentum> & momenta, 
			const vector<int> & helicities) = 0;

  /**
   * Return an overestimated amplitude. Same as value(const tcPDVector
   * &, const vector<Lorentz5Momentum> &, const vector<int> &), but it
   * provides an overestimate of the complex amplitude, that is:
   * <code>abs( overestimaValue() ) >= abs(value()) </code> The
   * default definition just returns value(), but it can be overriden
   * by derived classes.
   */
  virtual Complex overestimateValue(const tcPDVector & particles,
				    const vector<Lorentz5Momentum> & momenta, 
				    const vector<int> & helicities);
  //@}

  /** @name Alternative interface to main virtual functions. */
  //@{
  /**
   * Return the amplitude. Calls value(const tcPDVector &, const
   * vector<Lorentz5Momentum> &, const vector<int> &) and should not
   * be overridden.
   */

  Complex value(const PVector & particles, const vector<int> & helicities);

  /**
   * Return an overestimated amplitude. Calls overestimateValue(const
   * tcPDVector &, const vector<Lorentz5Momentum> &, const vector<int>
   * &)
   */
  Complex overestimateValue(const PVector & particles,
			    const vector<int> & helicities);
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
  virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in
   * this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

  /**
   * Describe an abstract base class with persistent data.
   */
  static AbstractClassDescription<Amplitude> initAmplitude;

  /**
   *  Private and non-existent assignment operator.
   */
  Amplitude & operator=(const Amplitude &);

};

}


namespace ThePEG {

/**
 * This template specialization informs ThePEG about the
 * base class of Amplitude.
 */
template <>
struct BaseClassTrait<Amplitude,1>: public ClassTraitsType {
  /** Typedef of the base class of Amplitude. */
  typedef HandlerBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * Amplitude class.
 */
template <>
struct ClassTraits<Amplitude>: public ClassTraitsBase<Amplitude> {
  /** Return the class name. */
  static string className() { return "ThePEG::Amplitude"; }
};

}

#include "Amplitude.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Amplitude.tcc"
#endif

#endif /* ThePEG_Amplitude_H */
