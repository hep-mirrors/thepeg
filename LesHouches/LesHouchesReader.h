// -*- C++ -*-
#ifndef THEPEG_LesHouchesReader_H
#define THEPEG_LesHouchesReader_H
//
// This is the declaration of the <!id>LesHouchesReader<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>LesHouchesReader<!!id> is an abstract base class to be used
// for objects which reads event files or streams from matrix element
// generators. Derived classes must at least implement the
// <!id>open<!!id> and <!id>readEvent<!!id> methods to read in
// information about the whole run and next event respectively and the
// close function to close the file or stream read. The derived class
// can fill the protected variables which corresponds very closely to
// the Les Houches protocol common block, this base class will then be
// responsible for transforming this data to the ThePEG
// <!class>Event<!!class> record in the <!id>getEvent<!!id>
// method. <!id>LesHouchesReader<!!id>s can only be used inside
// <!class>LesHouchesEventHandler<!!class> objects and not in the
// standard <!class>EventHandler<!!class> objects.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Event.html">Event.h</a>,
// <a href="http:LesHouchesEventHandler.html">LesHouchesEventHandler.h</a>.
// 

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Utilities/ObjectIndexer.h"
#include "ThePEG/Utilities/Exception.h"
#include "LesHouchesReader.fh"

namespace ThePEG {

class LesHouchesReader: public HandlerBase {

public:

  LesHouchesReader();
  LesHouchesReader(const LesHouchesReader &);
  virtual ~LesHouchesReader();
  // Standard ctors and dtor.

public:

  virtual void open() = 0;
  // Open a file or stream with events and read in the run information
  // into the corresponding protected variables.

  virtual void readEvent() = 0;
  // Read the next event form the file or stream into the
  // corresponding protected variables.

  virtual void close() = 0;
  // Close the file or stream from which events have been read.

  virtual EventPtr getEvent();
  // Takes the calls readEvent and translates the information into an
  // Event object which is returned.

protected:

  void createParticles();
  // Creates instances of all particles in the event and stores them
  // in particleIndex. If no beam particles are included in the event
  // they are also created.

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

protected:

  pair<long,long> IDBMUP;
  // PDG id's of beam particles. (first/second is in +/-z direction).

  pair<double,double> EBMUP;
  // Energy of beam particles given in GeV.

  pair<int,int> PDFGUP;
  // The author group for the PDF used for the beams according to the
  // PDFLib specification.

  pair<int,int> PDFSUP;
  // The id number the PDF used for the beams according to the
  // PDFLib specification.

  int IDWTUP;
  // Master switch indicating how the ME generator envisages the
  // events weights should be interpreted according to the Les Houches
  // accord.

  int NRUP;
  // The number of different subprocesses in this file (should
  // typically be just one)

  vector<double> XSECUP;
  // The cross sections for the different subprocesses in pb.

  vector<double> XERRUP;
  // The statistical error in the cross sections for the different
  // subprocesses in pb.

  vector<double> XMAXUP;
  // The maximum event weights (in XWGTUP) for different subprocesses.

  vector<int> LPRUP;
  // The subprocess code for the different subprocesses.

  int NUP;
  // The number of particle entries in the current event.

  int IDPRUP;
  // The subprocess code for this event (as given in LPRUP).

  double XWGTUP;
  // The weight for this event.

  double SCALUP;
  // The scale in GeV used in the calculation of the PDF's in this
  // event.

  double AQEDUP;
  // The value of the QED coupling used in this event.

  double AQCDUP;
  // The value of the QCD coupling used in this event.

  vector<long> IDUP;
  // The PDG id's for the particle entries in this event.

  vector<int> ISTUP;
  // The status codes for the particle entries in this event.

  vector< pair<int,int> > MOTHUP;
  // Indices for the first and last mother for the particle entries in
  // this event.

  vector< pair<int,int> > ICOLUP;
  // The colour-line indices (first(second) is (anti)colour) for the
  // particle entries in this event.

  vector< vector<double> > PUP;
  // Lab frame momentum (Px, Py, Pz, E and M in GeV) for the particle
  // entries in this event.

  vector<double> VTIMUP;
  // Invariant lifetime (c*tau, distance from production to decay im
  // mm) for the particle entries in this event.

  vector<double> SPINUP;
  // Spin info for the particle entries in this event given as the
  // cosine of the angle between the spin vector of a particle and the
  // 3-momentum of the decaying particle, specified in the lab frame.

private:

  ObjectIndexer<long,ColourLine> colourIndex;
  // Association between ColourLines and colour indices in the current
  // translation.

  ObjectIndexer<long,Particle> particleIndex;
  // Association between Particles and indices in the current
  // translation.

private:

  static AbstractClassDescription<LesHouchesReader> initLesHouchesReader;
  // Describe an abstract base class with persistent data.

  LesHouchesReader & operator=(const LesHouchesReader &);
  // Private and non-existent assignment operator.

public:

class LesHouchesInconsistencyError: public Exception {};


};

}

// CLASSDOC OFF

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of LesHouchesReader.
template <>
struct BaseClassTrait<LesHouchesReader,1> {
  typedef HandlerBase NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<LesHouchesReader>
  : public ClassTraitsBase<LesHouchesReader> {
  static string className() { return "ThePEG::LesHouchesReader"; }
  // Return the class name.
  static string library() { return "LesHouchesReader.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "LesHouchesReader.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LesHouchesReader.tcc"
#endif

#endif /* THEPEG_LesHouchesReader_H */
