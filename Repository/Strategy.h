// -*- C++ -*-
#ifndef ThePEG_Strategy_H
#define ThePEG_Strategy_H
// This is the declaration of the Strategy class.

#include "ThePEG/Config/ThePEG.h"
#include "Strategy.fh"
// #include "Strategy.xh"
#include "ThePEG/Interface/Interfaced.h"

namespace ThePEG {

/**
 * The Strategy class represents a general strategy to be assigned to
 * an EventGenerator. It contains a set of default ParticleData
 * objects which takes presedence over the ones in the Repository
 * (although not over the ones in the EventGenerator). It also
 * contains a set of other default objects which are automatically
 * assigned to all Reference and RefVector interfaces which have the
 * InterfaceBase::defaultIfNull() flag set. In this case each of the
 * objects in defaultObjects() are tested in turn, and the first
 * object which has the correct class and can be set will be used.
 *
 * Sub-classes may implement other behaviors by overriding the
 * doinit() function.
 *
 * @see EventGenerator,
 * @see ParticleData,
 * @see Repository,
 * @see Reference.
 * 
 */
class Strategy: public Interfaced {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  Strategy();

  /**
   * Copy-constructor.
   */
  Strategy(const Strategy &);

  /**
   * Destructor.
   */
  virtual ~Strategy();
  //@}

public:

  /** @name Access the special objects in this Strategy. */
  //@{
  /**
   * Return the map of local particles indexed by their PDG id number.
   */
  inline const ParticleMap & particles() const;

  /**
   * Return the vector of default objects.
   */
  inline const vector<IPtr> & defaultObjects() const;
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
  inline virtual IBPtr fullclone() const;
  //@}


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
  //@}

private:

  /**
   * Return the map of local particles.
   */
  inline ParticleMap & particles();

private:

  /**
   * the map of default particles.
   */
  ParticleMap theParticles;

  /**
   * A vector of default objects.
   */
  vector<IPtr> theDefaultObjects;

private:

  /**
   * Utility function used by the interface.
   */
  void setLocalParticles(PDPtr pd, int);

  /**
   * Utility function used by the interface.
   */
  void insLocalParticles(PDPtr pd, int);

  /**
   * Utility function used by the interface.
   */
  void delLocalParticles(int place);

  /**
   * Utility function used by the interface.
   */
  vector<PDPtr> getLocalParticles() const;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<Strategy> initStrategy;

  /**
   *  Private and non-existent assignment operator.
   */
  Strategy & operator=(const Strategy &);

};

/** This template specialization informs ThePEG about the base classes
 *  of Strategy. */
template <>
struct BaseClassTrait<Strategy,1> {
  /** Typedef of the first base class of Strategy. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  Strategy class. */
template <>
struct ClassTraits<Strategy>: public ClassTraitsBase<Strategy> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::Strategy"; }
};

}

#include "Strategy.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Strategy.tcc"
#endif

#endif /* ThePEG_Strategy_H */
