// -*- C++ -*-
#ifndef ThePEG_SpinInfo_H
#define ThePEG_SpinInfo_H
// This is the declaration of the SpinInfo class.

#include "ThePEG/EventRecord/SpinBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Helicity/HelicityVertex.h"
#include "SpinInfo.fh"
// #include "SpinInfo.xh"

namespace ThePEG {
namespace Helicity {

/**
 *   The SpinInfo is the base class for the spin information for the
 *   Herwig++ spin correlation algorithm. It inherits from ThePEG
 *   SpinBase class and in turn the implementations for different spin
 *   states inherit from this.
 *
 *   The class contains pointers to the vertex where the particle is
 *   produced and where it decays, together with methods to set/get
 *   these.
 *
 *   There are two flags decayed which store information on the state
 *   of the particle.
 *
 *   The decayed() members provides access to the _decay data member
 *   which is true if the spin density matrix required to perform the
 *   decay of a timelike particle has been calculated (this would be a
 *   decay matrix for a spacelike particle.) This is set by the
 *   decay() method which calls a method from the production vertex to
 *   calculate this matrix. The decay() method should be called by a
 *   decayer which uses spin correlation method before it uses the
 *   spin density matrix to calculate the matrix element for the
 *   decay.
 *
 *   The developed() member provides access to the _developed data
 *   member which is true if the decay matrix required to perform the
 *   decays of the siblings of a particle has been calculated (this
 *   would a spin density matrix for a spacelike particle.) This is
 *   set by the developed() method which calls a method from the decay
 *   vertex to calculate the matrix. The developed() method is called
 *   by a DecayHandler which is capable of performing spin
 *   correlations after all the unstable particles produced by a
 *   decaying particle are decayed.
 *
 *   Methods are also provided to access the spin density and decay
 *   matrices for a particle.
 *
 * @author Peter Richardson
 *
 */
class SpinInfo: public SpinBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline SpinInfo();

  /**
   * Standard Constructor.
   * @param p the production momentum.
   * @param time true if the particle is time-like.
   */
  inline SpinInfo(const Lorentz5Momentum & p, bool time);

  /**
   * Copy-constructor.
   */
  inline SpinInfo(const SpinInfo &);

  /**
   * Destructor.
   */
  virtual ~SpinInfo();
  //@}

public:

  /**
   * Standard Init function.
   */
  static void Init();

  /**
   * Rebind to cloned objects. If a FermionSpinInfo is cloned together
   * with a whole Event and this has pointers to other event record
   * objects, these should be rebound to their clones in this
   * function.
   */
  virtual void rebind(const EventTranslationMap & trans);

  /**
   * Standard clone method.
   */
  inline virtual EIPtr clone() const;

  /**
   * Method to handle the delelation
   */
  inline void update() const;

public:


  /** @name Access the vertices. */
  //@{
  /**
   * Set the vertex at which the particle was produced.
   */
  inline void setProductionVertex(VertexPtr) const;

  /**
   * Get the vertex at which the particle was produced.
   */
  inline tcVertexPtr getProductionVertex() const;

  /**
   * Set the vertex at which the particle decayed or branched.
   */
  inline void setDecayVertex(VertexPtr) const;

  /**
   * Get the vertex at which the particle decayed or branched.
   */
  inline tcVertexPtr getDecayVertex() const;
  //@}

  /** @name Access information about the associated particle. */
  //@{
  /**
   * Has the particle decayed?
   */
  inline bool decayed() const;

  /**
   * Set if the particle has decayed.
   */
  inline void decayed(bool) const;

  /**
   * Return true if the decay matrix required to perform the decays of
   * the siblings of a particle has been calculated.
   */
  inline  bool developed() const;

  /**
   * Calculate the rho matrix for the decay if not already done.
   */
  inline void decay() const;

  /**
   * Set the developed flag and calculate the D matrix for the decay.
   */
  inline void develop() const;

  /**
   * Set the developed variable for the particle.
   */
  inline void setDeveloped(bool) const;

  /**
   * Return 2s+1 for the particle
   */
  inline int Spin() const;

  /**
   * Return true if this is a particle (rather than an antiparticle).
   */
  inline bool Particle();

  /**
   * Return the momentum of the particle when it was produced.
   */
  inline const Lorentz5Momentum & productionMomentum() const;

  /**
   * Return true if particle is timelike (rather than spacelike).
   */
  inline bool timelike();
  //@}

public:

  /** @name Access the rho and D matrices. */
  //@{
  /**
   * Access the rho matrix.
   */
  inline RhoDMatrix rhoMatrix() const;

  /**
   * Access the rho matrix.
   */
  inline RhoDMatrix & rhoMatrix();

  /**
   * Access the D matrix.
   */
  inline RhoDMatrix DMatrix() const;

  /**
   * Access the D matrix.
   */
  inline RhoDMatrix & DMatrix();
  //@}

protected:

  /**
   * Set the spin of the particle.
   */
  inline void setSpin(int);

  /**
   * Set the production momentum  of the particle.
   */
  inline void setProductionMomentum(const Lorentz5Momentum & in);

  /**
   * Specify if the particle is timelike (rather than spacelike).
   */
  inline void setTimelike(bool);

private:

  /**
   * Describe a concrete class without persistent data.
   */
  static NoPIOClassDescription<SpinInfo> initSpinInfo;

  /**
   * Private and non-existent assignment operator.
   */
  SpinInfo & operator=(const SpinInfo &);

private:

  /**
   * pointers to the production and decay vertices for the particle
   */
  mutable VertexPtr _production,_decay;

  /**
   * Is this is timelike (true) or spacelike (false ) particle?  This
   * is used to decide if the particle is incoming or outgoing at the
   * production vertex
   */
  bool _timelike;

  /**
   * Location in the hard vertex array at production and decay
   */
  mutable int _prodloc,_decayloc;

  /**
   * Has the particle been decayed?  (I.e. has the rho matrix for the
   * decay been calculated.)
   */
  mutable bool _decayed;

  /**
   * Has the particle been developed?  (I.e. has the D matrix encoding
   * the info about the decay been calculated)
   */
  mutable bool _developed;

  /**
   * Storage of the rho matrix.
   */
  mutable RhoDMatrix _rhomatrix;

  /**
   * Storage of the decay matrix
   */
  mutable RhoDMatrix _Dmatrix;

  /**
   * The spin of the particle
   */
  int _ispin;

  /**
   * Momentum of the particle when it was produced
   */
  Lorentz5Momentum _productionmomentum;

};

}
}


namespace ThePEG {

/**
 * This template specialization informs ThePEG about the base class of
 * SpinInfo.
 */
template <>
struct BaseClassTrait<ThePEG::Helicity::SpinInfo,1>: public ClassTraitsType {
  /** Typedef of the base class of SpinInfo. */
  typedef SpinBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * SpinInfo class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ThePEG::Helicity::SpinInfo>
  : public ClassTraitsBase<ThePEG::Helicity::SpinInfo> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::Helicity::SpinInfo"; }
  /**
   * Return the name of the shared library to be loaded to get access
   * to the SpinInfo class and every other class it uses
   * (except the base class).
   */
  static string library() { return "libThePEGHelicity.so"; }

};

}

#include "SpinInfo.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SpinInfo.tcc"
#endif

#endif /* ThePEG_SpinInfo_H */
