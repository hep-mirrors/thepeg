// -*- C++ -*-
#ifndef ThePEG_HelicityVertex_H
#define ThePEG_HelicityVertex_H
//
// This is the declaration of the <!id>HelicityVertex<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//  The HelicityVertex class is designed to store the helicity amplitude
//  expression for the matrix element for use by the spin correlation
//  algorithm. It implements the storage of the pointer to the incoming
//  and outgoing particles at the vertex and virtual methods for calculating
//  the rho and D matrices. The concrete implementations of the vertices
//  for specific processes, eg production or decay, inherit from this and
//  implement the storage of the matrix element together with the set and
//  get methods
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
//
// Author: Peter Reichardson
//

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

class HelicityVertex: public EventInfoBase {

public:

  typedef vector<tcSpinPtr> SpinVector;

public:

  inline HelicityVertex();
  inline HelicityVertex(const HelicityVertex &);
  virtual ~HelicityVertex();
  // Standard ctors and dtor.

public:

  static void Init();
  // Standard Init function used to initialize the interfaces.

  virtual void rebind(const EventTranslationMap & trans);
  // Translate all member variables which are pointers.

  inline virtual EIPtr clone() const;
  // Standard clone method.

public:

  // access methods for the incoming and outgoing particles

  inline SpinVector incoming() const;
  // access to the incoming particles

  inline SpinVector outgoing() const;
  // access to the outgoing particles

  inline void addIncoming(tcSpinPtr,int&);
  // add an incoming particle

  inline void addOutgoing(tcSpinPtr,int&);
  // add an outgoing particle

  inline void resetIncoming(tcSpinPtr,int);
  // ???

  inline void resetOutgoing(tcSpinPtr,int);
  // ???

  inline void output() const;
  // ???

public:

  // methods to calculate the rho and D matrices

  virtual RhoDMatrix getRhoMatrix(int);
  // method to get the rho matrix for a given outgoing particle

  virtual RhoDMatrix getDMatrix(int);
  // method to get the D matrix for an incoming particle

private:

  static AbstractNoPIOClassDescription<HelicityVertex> initHelicityVertex;
  // Describe an abstract base class without persistent data.

  HelicityVertex & operator=(const HelicityVertex &);
  // Private and non-existent assignment operator.

private:

  SpinVector _incoming;
  // pointers to the incoming particles at the vertex
  SpinVector _outgoing;
  // pointers to the outgoing particles at the vertex

};

}
}

// CLASSDOC OFF

namespace ThePEG {

  // The following template specialization informs ThePEG about the
  // base class of HelicityVertex.
  template <>
  struct BaseClassTrait<ThePEG::Helicity::HelicityVertex,1> {
    typedef EventInfoBase NthBase;
  };

  // The following template specialization informs ThePEG about the
  // name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ThePEG::Helicity::HelicityVertex>
  : public ClassTraitsBase<ThePEG::Helicity::HelicityVertex> {
  static string className() { return "ThePEG::Helicity::HelicityVertex"; }
  // Return the class name.
  static string library() { return "libThePEGHelicity.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "HelicityVertex.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HelicityVertex.tcc"
#endif

#endif /* ThePEG_HelicityVertex_H */
