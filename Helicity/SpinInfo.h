// -*- C++ -*-
#ifndef ThePEG_SpinInfo_H
#define ThePEG_SpinInfo_H
//
// This is the declaration of the <!id>SpinInfo<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//   This is the base class for the spin information for the Herwig++ spin
//   correlation algorithm. It inherits from ThePEG SpinBase class and in turn
//   the implementations for different spin states inherit from this
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
//
// Author: Peter Richardson
//

#include "ThePEG/EventRecord/SpinBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Helicity/HelicityVertex.h"
#include "SpinInfo.fh"
// #include "SpinInfo.xh"

namespace ThePEG {
namespace Helicity {

class SpinInfo: public SpinBase {

public:

  inline SpinInfo();
  inline SpinInfo(const Lorentz5Momentum &,bool);
  inline SpinInfo(const SpinInfo &);
  virtual ~SpinInfo();
  // Standard ctors and dtor.

public:

  static void Init();
  // Standard Init function used to initialize the interface.

  virtual void rebind(const EventTranslationMap & trans);

  inline virtual EIPtr clone() const;
  // Standard clone method.

  inline void update() const;
  // method to handle the delelation

public:
  // set and get methods for the vertex

  inline void setProductionVertex(VertexPtr) const;
  // set the vertex at which the particle was produced

  inline tcVertexPtr getProductionVertex() const;
  // get the vertex at which the particle was produced

  inline void setDecayVertex(VertexPtr) const;
  // set the vertex at which the particle decayed or branched

  inline tcVertexPtr getDecayVertex() const;
  // set and get methods for the stage variables

  inline bool decayed() const;
  // get decay for particle

  inline void decayed(bool) const;
  /// set decay for the particle

  inline  bool developed() const;
  // get developed for the particle

  inline void decay() const;
  // calculate the rho matrix for the decay if not already done

  inline void develop() const;
  // set the developed flag and calculate the D matrix for the decay

  inline void setDeveloped(bool) const;
  // get the developed variable for the particle

  inline int Spin() const;
  // return 2s+1 for the particle

  inline bool Particle();
  // is this a particle or antiparticle

  inline const Lorentz5Momentum & productionMomentum() const;
  // return the momentum of the particle when in was produced

  inline bool timelike();
  // ???

public:

  // access to the rho matrix
  inline RhoDMatrix rhoMatrix() const;
  inline RhoDMatrix & rhoMatrix();

  // access to the D matrix
  inline RhoDMatrix DMatrix() const;
  inline RhoDMatrix & DMatrix();

protected:

  inline void setSpin(int);
  // set the spin of the particle
  inline void setProductionMomentum(const Lorentz5Momentum & in);
  inline void setTimelike(bool);

private:

  static NoPIOClassDescription<SpinInfo> initSpinInfo;
  // Describe a concrete class without persistent data.

  SpinInfo & operator=(const SpinInfo &);
  // Private and non-existent assignment operator.

private:

  mutable VertexPtr _production,_decay;
  // pointers to the production and decay vertices for the particle

  bool _timelike;
  // is this is timelike (true) or spacelike (false ) particle
  // this is used to decide if the particle is incoming or outgoing at
  // the production vertex

  mutable int _prodloc,_decayloc;
  // location in the hard vertex array at production and decay

  mutable bool _decayed;
  // has the particle been decayed
  // (i.e. has the rho matrix for the decay been calculated)

  mutable bool _developed;
  // has the particle been developed
  // (i.e. has the D matrix encoding the info about the decay been calculated)

  mutable RhoDMatrix _rhomatrix;
  // storage of the rho matrix

  mutable RhoDMatrix _Dmatrix;
  // storage of the decat matrix

  int _ispin;
  // spin of the particle

  Lorentz5Momentum _productionmomentum;
  // momentum of the particle when it was produced

};

ThePEG_DECLARE_CLASS_POINTERS(SpinInfo,HwSpinPtr);

}
}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of SpinInfo.
template <>
struct BaseClassTrait<ThePEG::Helicity::SpinInfo,1> {
  typedef SpinBase NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ThePEG::Helicity::SpinInfo>
  : public ClassTraitsBase<ThePEG::Helicity::SpinInfo> {
  static string className() { return "ThePEG::Helicity::SpinInfo"; }
  // Return the class name.
  static string library() { return "libThePEGHelicity.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "SpinInfo.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SpinInfo.tcc"
#endif

#endif /* ThePEG_SpinInfo_H */
