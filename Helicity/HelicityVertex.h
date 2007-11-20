// -*- C++ -*-
//
// HelicityVertex.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_HelicityVertex_H
#define ThePEG_HelicityVertex_H
// This is the declaration of the HelicityVertex class.

#include "ThePEG/EventRecord/EventConfig.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "RhoDMatrix.h"
#include "ThePEG/EventRecord/EventInfoBase.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/EventRecord/SpinBase.h"
#include "HelicityVertex.fh"

// #include "HelicityVertex.xh"

namespace ThePEG {
namespace Helicity {

/**
 *  The HelicityVertex class is designed to store the helicity
 *  amplitude expression for the matrix element for use by the spin
 *  correlation algorithm. It implements the storage of the pointers
 *  to the incoming and outgoing particles at the vertex and virtual
 *  methods for calculating the rho and D matrices. The concrete
 *  implementations of the vertices for specific processes, eg
 *  production or decay, inherit from this and implement the storage
 *  of the matrix element together with the set and get methods.
 *
 *  These methods are then called by the SpinInfo class to perform the
 *  calculations.
 *
 *
 * @see SpinInfo
 *
 * @author Peter Richardson
 *
 */
class HelicityVertex: public EventInfoBase {

public:

  /** A vector of SpinInfo objects. */
  typedef vector<tcSpinPtr> SpinVector;

public:

  /**
   * Standard Init function.
   */
  static void Init();

  /**
   * Rebind to cloned objects. If a HelicityVertex is cloned together
   * with a whole Event and this has pointers to other event record
   * objects, these should be rebound to their clones in this
   * function.
   */
  virtual void rebind(const EventTranslationMap & trans);

public:

  /** @name Access the incoming and outgoing particles. */
  //@{
  /**
   * Access the spin of the incoming particles.
   */
  inline SpinVector incoming() const;

  /**
   * Access the spin of the outgoing particles.
   */
  inline SpinVector outgoing() const;

  /**
   * Add the spin of an incoming particle.
   * @param spin the spin of the particle.
   * @param loc is set to the position in the list of incoming spins.
   */
  inline void addIncoming(tcSpinPtr spin, int & loc);

  /**
   * Add the spin of an outgoing particle.
   * @param spin the spin of the particle.
   * @param loc is set to the position in the list of outgoing spins.
   */
  inline void addOutgoing(tcSpinPtr spin, int & loc);

  /**
   * Reset the \a spin of the incoming particle at position \a loc.
   */
  inline void resetIncoming(tcSpinPtr spin, int loc);

  /**
   * Reset the \a spin of the outgoing particle at position \a loc.
   */
  inline void resetOutgoing(tcSpinPtr spin, int loc);
  //@}

  /**
   * Print function used for debugging.
   */
  inline void output() const;

public:

  /** @name Mthods to calculate rho and D matrices. */
  //@{
  /**
   * Get the rho matrix for the outgoing particle at position \a loc.
   */
  virtual RhoDMatrix getRhoMatrix(int loc) = 0;

  /**
   * Get the D matrix for the incoming particle at position \a loc.
   */
  virtual RhoDMatrix getDMatrix(int loc) = 0;
  //@}

private:

  /**
   * Describe an abstract base class without persistent data.
   */
  static AbstractNoPIOClassDescription<HelicityVertex> initHelicityVertex;

  /**
   * Private and non-existent assignment operator.
   */
  HelicityVertex & operator=(const HelicityVertex &);

private:

  /**
   * Pointers to the incoming particle spins at the vertex.
   */
  SpinVector _incoming;

  /**
   * Pointers to the outgoing particle spins at the vertex.
   */
  SpinVector _outgoing;

};

}
}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

  /**
   * This template specialization informs ThePEG about the
   * base class of HelicityVertex.
   */
  template <>
  struct BaseClassTrait<ThePEG::Helicity::HelicityVertex,1>
    : public ClassTraitsType {
  /** Typedef of the base class of HelicityVertex. */
    typedef EventInfoBase NthBase;
  };

  /**
   * This template specialization informs ThePEG about the name of
   * the HelicityVertex class and the shared object where it is defined.
   */
template <>
struct ClassTraits<ThePEG::Helicity::HelicityVertex>
  : public ClassTraitsBase<ThePEG::Helicity::HelicityVertex> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::Helicity::HelicityVertex"; }
};

/** @endcond */

}

#include "HelicityVertex.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HelicityVertex.tcc"
#endif

#endif /* ThePEG_HelicityVertex_H */
