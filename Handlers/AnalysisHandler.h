// -*- C++ -*-
#ifndef ThePEG_AnalysisHandler_H
#define ThePEG_AnalysisHandler_H
//
// This is the declaration of the <!id>AnalysisHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>AnalysisHandler<!!id> is the base class of all analysis
// objects which may be handled by the
// <!class>FullEventGenerator<!!class>. The main function is the
// virtual <!id>analyze<!!id> method which which is called for each
// analysis handler after each event. The method may be called several
// times for each event - this may be checked by the analysis handler
// by looking at the <!id>ieve<!!id>, <!id>loop<!!id> and
// <!id>state<!!id> arguments to the <!id>analyze<!!id> method.
//
// Initialization of histograms etc. should be made in the <!id>doinit<!!id>
// method, while writing out of histograms and analysis results should
// be performed in the <!id>dofinish<!!id> method.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:FullEventGenerator.html">FullEventGenerator.h</a>
// <a href="http:Event.html">Event.h</a>
// 

#include "HandlerBase.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include <stdexcept>

namespace ThePEG {

class AnalysisHandler: public HandlerBase {

public:

  inline AnalysisHandler();
  inline AnalysisHandler(const AnalysisHandler &);
  virtual ~AnalysisHandler();
  // Standard ctors and dtor

public:

  virtual void analyze(tEventPtr event, long ieve, int loop, int state);
  // Analyse a given 'event'. 'ieve' is the event number, 'loop' is
  // the number of times this event has been presented. If loop is
  // negative, the event is now fully generated.  'state' is a number
  // different from zero if the event has been manipulated in some way
  // since it was last presented. Note that a fully generated event
  // may be presented several times, if it has been manipulated in
  // between. The default version of this function will call transform
  // to make a lorentz transformation of the whole event, then extract
  // all final state particles and call analyze(tPVector) of this
  // analysis object and those of all associated analysis objects. The
  // default version will not, however, do anything on events which
  // have not been fully generated, or have been manipulated in any
  // way.

  virtual LorentzRotation transform(tEventPtr) const;
  // transform the event to the desired Lorentz frame and return the
  // used LorentzRotation. The default version does nothing and
  // returns the identity rotation.

  virtual void analyze(const tPVector & particles);
  // Analyze the given vector of particles. The default version calls
  // analyze(tPPtr) for each of the particles.

  virtual void analyze(tPPtr particle);
  // Analyze the given particle. The default version does nothing

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual IBPtr clone() const;
  // Return a simple clone of this object. Should be implemented as
  // <!id>return new_ptr(*this);<!!id> by a derived class.

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

  AnalysisVector theSlaves;
  // A list of slave analysis objects which are called for the same
  // extracted particles as this one.

private:

  static ClassDescription<AnalysisHandler> initAnalysisHandler;

};

template <>
struct BaseClassTrait<AnalysisHandler,1> {
  typedef HandlerBase NthBase;
};

template <>
struct ClassTraits<AnalysisHandler>: public ClassTraitsBase<AnalysisHandler> {
  static string className() { return "/ThePEG/AnalysisHandler"; }
};

}

#include "AnalysisHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "AnalysisHandler.tcc"
#endif

#endif /* ThePEG_AnalysisHandler_H */
