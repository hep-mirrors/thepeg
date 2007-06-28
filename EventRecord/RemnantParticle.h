// -*- C++ -*-
#ifndef THEPEG_RemnantParticle_H
#define THEPEG_RemnantParticle_H
//
// This is the declaration of the RemnantParticle class.
//

#include "ThePEG/EventRecord/Particle.h"
#include "RemnantParticle.fh"
#include "ThePEG/PDT/RemnantData.fh"
#include "ThePEG/PDT/RemnantDecayer.fh"

namespace ThePEG {

/**
 * Here is the documentation of the RemnantParticle class.
 */
class RemnantParticle: public Particle {

public:

  /**
   * RemnantDecayer is a friend.
   */
  friend class RemnantDecayer;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The standard constructor takes as argument the \a particle
   * for which this is the remnant and a \a decayer capable of
   * performing the decay. Optionally a \a parton that has been
   * extracted.
   */
  RemnantParticle(const Particle & particle, RemDecPtr decayer,
		  tPPtr parton = tPPtr());

  /**
   * The copy constructor.
   */
  inline RemnantParticle(const RemnantParticle &);

  /**
   * The destructor.
   */
  virtual ~RemnantParticle();

  /**
   * Particle uses the FixedSizeAllocator for (de)allocation.
   */
  inline void * operator new(size_t);
  
  /**
   * Particle uses the FixedSizeAllocator for (de)allocation.
   */
  inline void operator delete(void *, size_t);
  //@}

public:

  /**
   * Modify the properties to reflect that the given \a parton was
   * extracted. If \a fixcolour is true a colour line is drawn from
   * the remnant to the extracted parton.
   */
  bool extract(tPPtr parton, bool fixcolour = false);

  /**
   * Modify the properties to reflect that the previously extracted
   * parton, \a oldp, was evolved backwards to the the parton \a
   * newp. If \a fixcolour is true a colour line is drawn from the
   * remnant to the extracted parton.
   */
  bool reextract(tPPtr oldp, tPPtr newp, bool fixcolour = false);

  /**
   * Modify the properties to reflect that the given \a parton which
   * was previously extracted is removed.
   */
  bool remove(tPPtr parton);

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
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

protected:

  /**
   * If necessary, colour-connect this remnant to the given \a parton.
   */
  void fixColourLines(tPPtr parton);

private:

  /**
   * The RemnantData object associated to this remnant.
   */
  RemPDPtr remData;

  /**
   * The parent from which this remnant resulted.
   */
  tcPPtr parent;

  /**
   * The set of extracted partons.
   */
  PVector extracted;

protected:

  /**
   * Private default constructor must only be used by the
   * PersistentIStream class via the ClassTraits<RemnantParticle> class.
   */
  inline RemnantParticle();

  /**
   * The ClassTraits<RemnantParticle> class must be a friend to be able to
   * use the private default constructor.
   */
  friend class ClassTraits<RemnantParticle>;

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<RemnantParticle> initRemnantParticle;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  RemnantParticle & operator=(const RemnantParticle &);

};

}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of RemnantParticle. */
template <>
struct BaseClassTrait<RemnantParticle,1> {
  /** Typedef of the first base class of RemnantParticle. */
  typedef Particle NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the RemnantParticle class and the shared object where it is defined. */
template <>
struct ClassTraits<RemnantParticle>
  : public ClassTraitsBase<RemnantParticle> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::RemnantParticle"; }
  /** Create a Particle object. */
  static TPtr create() { return TPtr::Create(RemnantParticle()); }
};

/** @endcond */

}

#include "RemnantParticle.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantParticle.tcc"
#endif

#endif /* THEPEG_RemnantParticle_H */
