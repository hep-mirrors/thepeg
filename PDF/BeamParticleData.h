// -*- C++ -*-
#ifndef ThePEG_BeamParticleData_H
#define ThePEG_BeamParticleData_H
//
// This is the declaration of the <!id>BeamParticleData<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>BeamParticleData<!!id> inherits from the
// <!class>ParticleData<!!class> class and is used for particles which
// have information about their sub-structure implemented as a pointer
// to a <!class>PDFBase<!!class> object.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ParticleData.html">ParticleData.h</a>,
// <a href="http:PDFBase.html">PDFBase.h</a>.
// 

#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDF/PDFBase.h"

// #include "BeamParticleData.fh"
#include "BeamParticleData.xh"

namespace ThePEG {

class BeamParticleData: public virtual ParticleData {

public:

  inline BeamParticleData();
  inline BeamParticleData(const BeamParticleData &);
  virtual ~BeamParticleData();
  // Standard ctors and dtor

  static PDPtr Create(long newId, string newPDGName);
  // Create a Particle which is its own anti-particle.

  static PDPair Create(long newId, string newPDGName, string newAntiPDGName);
  // Create a particle - anti particle pair. Note that setting the
  // parton density object on this particle does not change the parton
  // density of the anti particle iven if synchronized() is true.

public:

  inline tcPDFPtr pdf() const;
  // Return a pointer to the parton density object describing the
  // sub-structure of this particle type.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  BeamParticleData(long newId, string newPDGName);
  // Protected constructor only to be used by subclasses or by the
  // Create method.

  virtual PDPtr pdclone() const;
  // ParticleData clone method

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  void setPDF(PDFPtr);
  // Set the parton density object.

private:

  PDFPtr thePDF;
  // The pointer to the parton density object.

private:

  static ClassDescription<BeamParticleData> initBeamParticleData;

  BeamParticleData & operator=(const BeamParticleData &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<BeamParticleData,1> {
  typedef ParticleData NthBase;
};

template <>
struct ClassTraits<BeamParticleData>: public ClassTraitsBase<BeamParticleData> {
  static string className() { return "/ThePEG/BeamParticleData"; }
};

}

#include "BeamParticleData.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "BeamParticleData.tcc"
#endif

#endif /* ThePEG_BeamParticleData_H */
