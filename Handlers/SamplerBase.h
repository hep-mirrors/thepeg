// -*- C++ -*-
#ifndef ThePEG_SamplerBase_H
#define ThePEG_SamplerBase_H
//
// This is the declaration of the <!id>SamplerBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This is the base class for all phase space sampler classes to be
// used by the <!class>EventHandler<!!class> class to sample the phase
// space according to the cross sections for the proceses in the
// <!class>EventHandler<!!class>. The class should be able to sample a
// unit hyper-cube in a phase space in arbitrary dimensions. The
// points need not necessarily be sampled with unit weight.
//
// The virtual methods to be implemented by concrete sub-classes are
// <!id>initialize()<!!id>, <!id>generate()<!!id> and
// <!id>rejectLast()<!!id>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:EventHandler.html">.h</a>,
// <a href="http:.html">Interfaced.h</a>.
// 

#include "ThePEG/Interface/Interfaced.h"
#include "SamplerBase.fh"
// #include "SamplerBase.xh"

namespace ThePEG {

class SamplerBase: public Interfaced {

public:

  inline SamplerBase();
  inline SamplerBase(const SamplerBase &);
  virtual ~SamplerBase();
  // Standard ctors and dtor.

public:

  inline void setEventHandler(tEHPtr eh);
  // Set the event handler for which the function dSigDR(const
  // vector<double> &) function returns the cross section for the
  // chosen phase space point.

  virtual void initialize() = 0;
  // Initialize the the sampler, possibly doing presampling of the
  // phase space.

  virtual double generate() = 0;
  // Generarate a new phase space point and return a weight associated
  // with it. This weight should preferably be 1.

  virtual void rejectLast() = 0;
  // Reject the last chosen phase space point.

  inline const vector<double> & lastPoint() const;
  // Return the last generated phase space point.

  virtual int lastBin() const;
  // If the sampler is able to sample several different functions
  // separately, this function should return the last chosen
  // function. This default version always returns 0.

  virtual CrossSection integratedXSec() const = 0;
  // Return the total integrated cross section determined from the
  // Monte Carlo sampling so far.

  virtual double sumWeights() const = 0;
  // Return the sum of the weights returned by generate() so far (of
  // the events that were not rejeted).

protected:

  inline vector<double> & lastPoint();
  // Return the last generated phase space point.

  inline tEHPtr eventHandler() const;
  // Return the associated event handler.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void doinitrun();
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  tEHPtr theEventHandler;
  // The associated event handler.

  vector<double> theLastPoint;
  // The last generated phase space point.

private:

  static AbstractClassDescription<SamplerBase> initSamplerBase;
  // Describe an abstract base class with persistent data.

  SamplerBase & operator=(const SamplerBase &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of SamplerBase.
template <>
struct BaseClassTrait<SamplerBase,1> {
  typedef Interfaced NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<SamplerBase>: public ClassTraitsBase<SamplerBase> {
  static string className() { return "/ThePEG/SamplerBase"; }
  // Return the class name.
};

}

#include "SamplerBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SamplerBase.tcc"
#endif

#endif /* ThePEG_SamplerBase_H */
