// -*- C++ -*-
#ifndef ThePEG_Amplitude_H
#define ThePEG_Amplitude_H
//
// This is the declaration of the <!id>Amplitude<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Amplitude<!!id> class is the abstract base class for all 
// the classes representing complex amplitudes associated with either 
// a hard <I>2-&GT;N</I> subprocess or a decay <I>1-&GT;N</I> process.  
// The returned value should be dimensionless suitable scaled by the 
// total invariant mass squared (shat), which is always computable
// from the specified momenta of the particles in the vertex.
// Notice that the amplitude for splitting <I>1-&GT;N</I> processes is instead 
// represented in other classes (derived from the <!id>SplitFun<!!id> class).


#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Config/Complex.h"
// #include "Amplitude.fh"
// #include "Amplitude.xh"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/EventRecord/Particle.h"

namespace ThePEG {

class Amplitude: public HandlerBase {

public:
 
  Amplitude();
  Amplitude(const Amplitude &);
  virtual ~Amplitude();
  // Standard ctors and dtor.

  virtual Complex value( const tcPDVector & particles,
			 const vector<Lorentz5Momentum> & momenta, 
			 const vector<int> & helicities ) = 0;
  // Given the particle data, momenta and helicities of all the particles 
  // in the "vertex", the method return the complex amplitude.
  // The convention is the order of the vectors is that first 
  // there is the incoming particle(s) and then the outgoing ones. 
  // For the helicities, the convention is to number them starting 
  // from 0 (no negative values, because they are used as vector indeces), 
  // for example, for a massive particle of spin S,  0 &LT;= helicity &LT;= 2*S.
  // The returned value should be dimensionless suitable scaled by the 
  // total invariant mass squared (shat), which is always computable
  // from the specified <!id>momenta<!!id> of the particles in the vertex.

  virtual Complex overestimateValue( const tcPDVector & particles,
				     const vector<Lorentz5Momentum> & momenta, 
				     const vector<int> & helicities );
  // As above, but it provides an overestimate of the complex
  // amplitude, that is: <BR> 
  //  <I> abs( overestimaValue(...) ) &GT;= abs( value(...) ) </I><BR>
  // The default definition just returns value(...), 
  // but it can be overriden by derived classes.  

  Complex value( const PVector & particles, const vector<int> & helicities );
  Complex overestimateValue( const PVector & particles, const vector<int> & helicities );
  // These methods simply forward a call to the previous ones,
  // and should not be overriden.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

  static AbstractClassDescription<Amplitude> initAmplitude;
  // Describe an abstract base class with persistent data.

  Amplitude & operator=(const Amplitude &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of Amplitude.
template <>
struct BaseClassTrait<Amplitude,1> {
  typedef HandlerBase NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<Amplitude>: public ClassTraitsBase<Amplitude> {
  static string className() { return "/ThePEG/Amplitude"; }
  // Return the class name.
};

}

#include "Amplitude.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Amplitude.tcc"
#endif

#endif /* ThePEG_Amplitude_H */
