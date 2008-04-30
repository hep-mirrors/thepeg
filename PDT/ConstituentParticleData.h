// -*- C++ -*-
//
// ConstituentParticleData.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_ConstituentParticleData_H
#define ThePEG_ConstituentParticleData_H
// This is the declaration of the ConstituentParticleData class.

#include "ThePEG/PDT/ParticleData.h"

// #include "ConstituentParticleData.fh"
// #include "ConstituentParticleData.xh"

namespace ThePEG {

/**
 * ConstituentParticleData inherits from the ParticleData class and is
 * used for quarks, diquarks and gluons to store information about
 * their constituent mass.
 *
 * @see \ref ConstituentParticleDataInterfaces "The interfaces"
 * defined for ConstituentParticleData.
 */
class ConstituentParticleData: public virtual ParticleData {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline ConstituentParticleData();

  /**
   * Copy-constructor.
   */
  inline ConstituentParticleData(const ConstituentParticleData &);

  /**
   * Destructor.
   */
  virtual ~ConstituentParticleData();
  //@}

  /** @name The Create methods are special interfaces for ParticleData
      classes. */
  //@{
  /**
   * Create a Particle which is its own anti-particle.
   */
  static PDPtr Create(long newId, string newPDGName);

  /**
   * Create a particle - anti particle pair.
   */
  static PDPair Create(long newId, string newPDGName, string newAntiPDGName);
  //@}

public:

  /**
   * Return the constituent mass of this parton.
   */
  inline virtual Energy constituentMass() const;

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
  ConstituentParticleData(long newId, string newPDGName);

  /**
   * Read setup info from a standard stream. The information that must
   * be supplied is the same as for ParticleData::readSetup with an
   * additional constituent mass (in GeV) added in the end.
   */
  virtual void readSetup(istream & is) throw(SetupException);

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
   * Utility function for the interface.
   */
  void setConstituentMass(Energy m);

  /**
   * Utility function for the interface.
   */
  Energy defConstituentMass() const;

private:

  /**
   * The constituent mass of this parton.
   */
  Energy theConstituentMass;

  /**
   * The default constituent mass of this parton.
   */
  Energy theDefaultConstituentMass;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<ConstituentParticleData> initConstituentParticleData;

  /**
   *  Private and non-existent assignment operator.
   */
  ConstituentParticleData & operator=(const ConstituentParticleData &);

};

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of ConstituentParticleData. */
template <>
struct BaseClassTrait<ConstituentParticleData,1>: public ClassTraitsType {
  /** Typedef of the first base class of ConstituentParticleData. */
  typedef ParticleData NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  ConstituentParticleData class. */
template <>
struct ClassTraits<ConstituentParticleData>:
    public ClassTraitsBase<ConstituentParticleData> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::ConstituentParticleData"; }
};

/** @endcond */

}

#include "ConstituentParticleData.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ConstituentParticleData.tcc"
#endif

#endif /* ThePEG_ConstituentParticleData_H */
