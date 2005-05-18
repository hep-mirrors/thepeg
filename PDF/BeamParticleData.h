// -*- C++ -*-
#ifndef ThePEG_BeamParticleData_H
#define ThePEG_BeamParticleData_H
// This is the declaration of the BeamParticleData class.

#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDF/PDFBase.h"

// #include "BeamParticleData.fh"
#include "BeamParticleData.xh"

namespace ThePEG {

/**
 * BeamParticleData inherits from the ParticleData class and is used
 * for particles which have information about their sub-structure
 * implemented as a pointer to a PDFBase object.
 *
 * @see \ref BeamParticleDataInterfaces "The interfaces"
 * defined for BeamParticleData.
 * @see ParticleData
 * @see PDFBase
 */
class BeamParticleData: public virtual ParticleData {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline BeamParticleData();

  /**
   * Copy-constructor.
   */
  inline BeamParticleData(const BeamParticleData &);

  /**
   * Destructor.
   */
  virtual ~BeamParticleData();
  //@}

  /** @name The Create methods are special interfaces for ParticleData
      classes. */
  //@{
  /**
   * Create a Particle which is its own anti-particle.
   */
  static PDPtr Create(long newId, string newPDGName);

  /**
   * Create a particle - anti particle pair. Note that setting the
   * parton density object on this particle does not change the parton
   * density of the anti particle iven if synchronized() is true.
   */
  static PDPair Create(long newId, string newPDGName, string newAntiPDGName);
  //@}

public:

  /**
   * Return a pointer to the parton density object describing the
   * sub-structure of this particle type.
   */
  inline tcPDFPtr pdf() const;

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

  /**
   * Protected constructor only to be used by subclasses or by the
   * Create method.
   */
  BeamParticleData(long newId, string newPDGName);

  /**
   * ParticleData clone method
   */
  virtual PDPtr pdclone() const;

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
   * @throws RebindException if no cloned object was found for a given
   * pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this
   * object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * Set the parton density object.
   */
  void setPDF(PDFPtr);

private:

  /**
   * The pointer to the parton density object.
   */
  PDFPtr thePDF;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<BeamParticleData> initBeamParticleData;

  /**
   *  Private and non-existent assignment operator.
   */
  BeamParticleData & operator=(const BeamParticleData &);

};

/** This template specialization informs ThePEG about the
 *  base classes of BeamParticleData. */
template <>
struct BaseClassTrait<BeamParticleData,1>: public ClassTraitsType {
  /** Typedef of the first base class of BeamParticleData. */
  typedef ParticleData NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  BeamParticleData class. */
template <>
struct ClassTraits<BeamParticleData>:
    public ClassTraitsBase<BeamParticleData> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::BeamParticleData"; }
};

}

#include "BeamParticleData.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "BeamParticleData.tcc"
#endif

#endif /* ThePEG_BeamParticleData_H */
