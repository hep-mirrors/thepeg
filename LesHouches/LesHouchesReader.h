// -*- C++ -*-
#ifndef THEPEG_LesHouchesReader_H
#define THEPEG_LesHouchesReader_H
// This is the declaration of the LesHouchesReader class.

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Utilities/ObjectIndexer.h"
#include "ThePEG/Utilities/Exception.h"
#include "ThePEG/PDF/PartonBinInstance.h"
#include "LesHouchesReader.fh"
#include <cstdio>

namespace ThePEG {

/**
 * LesHouchesReader is an abstract base class to be used for objects
 * which reads event files or streams from matrix element
 * generators. Derived classes must at least implement the open() and
 * readEvent() methods to read in information about the whole run and
 * next event respectively and the close function to close the file or
 * stream read. The derived class can fill the protected variables
 * which corresponds very closely to the Les Houches protocol common
 * block, this base class will then be responsible for transforming
 * this data to the ThePEG Event record in the getEvent()
 * method. <code>LesHouchesReader</code>s can only be used inside
 * LesHouchesEventHandler objects and not in the standard EventHandler
 * objects.
 *
 * @see Event
 * @see LesHouchesEventHandler
 */
class LesHouchesReader: public HandlerBase {

  /**
   * LesHouchesEventHandler should have access to our private parts.
   */
  friend class LesHouchesEventHandler;

  /**
   * Alias for standard C file streams.
   */
  typedef FILE * CFile;

  /**
   * Alias for a pair of C file streams.
   */
  typedef pair<CFile, CFile> CFilePair;

  /**
   * Map for counting the numer of events per process number.
   */
  typedef map<int, long> CountMap;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  LesHouchesReader();

  /**
   * Copy-constructor.
   */
  LesHouchesReader(const LesHouchesReader &);

  /**
   * Destructor.
   */
  virtual ~LesHouchesReader();
  //@}

public:

  /** @name Main virtual fuctions to be overridden in sub-classes. */
  //@{
  /**
   * Open a file or stream with events and read in the run information
   * into the corresponding protected variables.
   */
  virtual void open() = 0;

  /**
   * Read the next event form the file or stream into the
   * corresponding protected variables. Return false if there is no
   * more events.
   */
  virtual bool readEvent() = 0;

  /**
   * Close the file or stream from which events have been read.
   */
  virtual void close() = 0;

  /**
   * Scan the file or stream to obtain information about cross section
   * weights and particles etc.
   */
  virtual void scan();

  /**
   * Calls readEvent() or uncacheEvent() to read information into the
   * LesHouches common block variables.
   *
   * @return the weight asociated with this event. If negative weights
   * are allowed it should be between -1 and 1, otherwise between 0
   * and 1. If outside these limits the previously estimated maximum
   * is violated. Note that the estimated maximum then should be
   * updated from the outside.
   */
  virtual double getEvent();

  /**
   * Converts the information in the Les Houches common block
   * variables into a Collision object and inserts it in the provided
   * \a event object.
   */
  virtual void fillEvent(tEventPtr event);
  //@}

  /** @name Access information about the current event. */
  //@{

  /**
   * Return the size of this event in bytes. To be used for the cache
   * file. \a npart is the number of particles. If \a npart is 0, the
   * number is taken from NUP.
   */
  inline static size_t eventSize(int N);

  /**
   * The pair of PartonBinInstance objects describing the current
   * incoming partons in the event.
   */
  inline const PBIPair & partonBinInstances() const;

  /**
   * Return the instances of the beam particles for the current event.
   */
  inline const PPair & beams() const;

  /**
   * Return the instances of the incoming particles to the sub process
   * for the current event.
   */
  inline const PPair & incoming() const;

  /**
   * Return the instances of the outgoing particles from the sub process
   * for the current event.
   */
  inline const PVector & outgoing() const;

  /**
   * Return the instances of the intermediate particles in the sub
   * process for the current event.
   */
  inline const PVector & intermediates() const;
  //@}

  /** @name Other inlined access functions. */
  //@{
  /**
   * The total cross section for the sub processes in this reader.
   */
  inline CrossSection xSec() const;

  /**
   * The overestimated cross section for the sub processes in this
   * reader.
   */
  inline CrossSection maxXSec() const;

  /**
   * The maximum weight to be expected.
   */
  inline double maxWeight() const;

  /**
   * The number of events found in this reader. If less than zero the
   * number of events are unlimited.
   */
  inline long NEvents() const;

  /**
   * The maximum number of events to scan to collect information about
   * processes and cross sections. If less than 0, all events will be
   * scanned.
   */
  inline long maxScan() const;

  /**
   * Return true if this reader produces weighted events.
   */
  inline bool weighted() const;

  /**
   * True if negative weights may be produced.
   */
  inline bool negativeWeights() const;

  /**
   * The total number of events requested so far.
   */
  inline long nAttempted() const;

  /**
   * Number of requested events per process number.
   */
  inline const CountMap & attemptMap() const;

  /**
   * The number of events accepted so far.
   */
  inline long nAccepted() const;

  /**
   * Accept the current event.
   */
  inline void accept();

  /**
   * Number of accepted events per process number.
   */
  inline const CountMap & acceptMap() const;

  /**
   * The PartonExtractor object used to construct remnants.
   */
  inline tPExtrPtr partonExtractor() const;

  /**
   * The pairs of PartonBin objects describing the partons which can
   * be extracted by the PartonExtractor object.
   */
  inline const PartonPairVec & partonBins() const;

  /**
   * The KinematicalCuts object to be used for this reader.
   */
  inline const KinematicalCuts & cuts() const;

  //@}

protected:

  /** @name Functions for manipulating cache files. */
  //@{

  /**
   * Name of file used to cache the events form the reader in a
   * fast-readable form. If empty, no cache file will be generated.
   */
  inline string cacheFileName() const;

  /**
   * Should the events from this Reader be randomized in order to
   * avoid problems if not all events are used.
   */
  inline bool randomize() const;

  /**
   * File stream for the cache.
   */
  inline CFile cacheFile() const;

  /**
   * Open the cache file for reading.
   */
  void openReadCacheFile();

  /**
   * Open the cache file for writing.
   */
  void openWriteCacheFile();

  /**
   * Close the cache file;
   */
  void closeCacheFile();

  /**
   * Returns true if the cache file is compressed.
   */
  inline bool compressedCache() const;

  /**
   * Write the current event to the cache file.
   */
  void cacheEvent() const;

  /**
   * Read an event from the cache file. Return false if something went wrong.
   */
  bool uncacheEvent();

  /**
   * Helper function to write a variable to a memory location
   */
  template <typename T>
  static char * mwrite(char * pos, const T & t, size_t n = 1);

  /**
   * Helper function to read a variable from a memory location
   */
  template <typename T>
  static const char * mread(const char * pos, T & t, size_t n = 1);

  //@}

  /** @name Auxilliary virtual methods which may be verridden by sub-classes. */
  //@{
  /**
   * Check the existence of a pair of PartonBin objects corresponding
   * to the current event.
   *
   * @return false if no pair of suitable PartonBin objects was found.
   */
  virtual bool checkPartonBin();

  /**
   * Create instances of all particles in the event and store them
   * in particleIndex.
   */
  virtual void createParticles();

  /**
   * Using the already created particles create a pair of
   * PartonBinInstance objects corresponding to the incoming partons.
   */
  virtual void createPartonBinInstances();

  /**
   * Create instances of the incoming beams in the event and store
   * them in particleIndex. If no beam particles are included in the
   * event they are created from the run info.
   */
  virtual void createBeams();

  /**
   * Go through the mother indices and connect up the Particles.
   */
  virtual void connectMothers();
  //@}

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
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();

protected:

  /** @name Set functions for some variables not in the Les Houches accord. */
  //@{
  /**
   * The cross section for the sub processes in this reader.
   */
  inline void xSec(CrossSection);

  /**
   * Set true if this reader produces weighted events.
   */
  inline void weighted(bool);

  /**
   * The overestimated cross section for the sub processes in this reader.
   */
  inline void maxXSec(CrossSection);

  /**
   * The number of events in this reader. If less than zero the number
   * of events is unlimited.
   */
  inline void NEvents(long);

  /**
   * The maximum weight to be expected.
   */
  inline void maxWeight(double);

  /**
   * Set true if negative weights may be produced.
   */
  inline void negativeWeights(bool);
  //@}

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit() throw(InitException);

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  inline virtual void doinitrun();

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish();

  /**
   * Rebind pointer to other Interfaced objects. Called in the setup phase
   * after all objects used in an EventGenerator has been cloned so that
   * the pointers will refer to the cloned objects afterwards.
   * @param trans a TranslationMap relating the original objects to
   * their respective clones.
   * @throws RebindException if no cloned object was found for a given pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in
   * this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

protected:

  /**
   * PDG id's of beam particles. (first/second is in +/-z direction).
   */
  pair<long,long> IDBMUP;

  /**
   * Energy of beam particles given in GeV.
   */
  pair<double,double> EBMUP;

  /**
   * The author group for the PDF used for the beams according to the
   * PDFLib specification.
   */
  pair<int,int> PDFGUP;

  /**
   * The id number the PDF used for the beams according to the
   * PDFLib specification.
   */
  pair<int,int> PDFSUP;

  /**
   * The PDFBase object used for the first beam particle. Specified in
   * the interface or derived from PDFGUP and PDFSUP.
   */
  PDFPtr thePDFA;

  /**
   * The PDFBase object used for the second beam particle. Specified in
   * the interface or derived from PDFGUP and PDFSUP.
   */
  PDFPtr thePDFB;

  /**
   * The PartonExtractor object used to construct remnants.
   */
  PExtrPtr thePartonExtractor;

  /**
   * The pairs of PartonBin objects describing the partons which can
   * be extracted by the PartonExtractor object.
   */
  PartonPairVec thePartonBins;

  /**
   * The KinematicalCuts object to be used for this reader.
   */
  KinCutPtr theCuts;

  /**
   * Master switch indicating how the ME generator envisages the
   * events weights should be interpreted according to the Les Houches
   * accord.
   */
  int IDWTUP;

  /**
   * The number of different subprocesses in this file (should
   * typically be just one)
   */
  int NRUP;

  /**
   * The cross sections for the different subprocesses in pb.
   */
  vector<double> XSECUP;

  /**
   * The statistical error in the cross sections for the different
   * subprocesses in pb.
   */
  vector<double> XERRUP;

  /**
   * The maximum event weights (in XWGTUP) for different subprocesses.
   */
  vector<double> XMAXUP;

  /**
   * The subprocess code for the different subprocesses.
   */
  vector<int> LPRUP;

  /**
   * The number of particle entries in the current event.
   */
  int NUP;

  /**
   * The subprocess code for this event (as given in LPRUP).
   */
  int IDPRUP;

  /**
   * The weight for this event.
   */
  double XWGTUP;

  /**
   * The PDF weights for the two incoming partons. Nota that this
   * variable is not present in the current LesHouches accord.
   */
  pair<double,double> XPDWUP;

  /**
   * The scale in GeV used in the calculation of the PDF's in this
   * event.
   */
  double SCALUP;

  /**
   * The value of the QED coupling used in this event.
   */
  double AQEDUP;

  /**
   * The value of the QCD coupling used in this event.
   */
  double AQCDUP;

  /**
   * The PDG id's for the particle entries in this event.
   */
  vector<long> IDUP;

  /**
   * The status codes for the particle entries in this event.
   */
  vector<int> ISTUP;

  /**
   * Indices for the first and last mother for the particle entries in
   * this event.
   */
  vector< pair<int,int> > MOTHUP;

  /**
   * The colour-line indices (first(second) is (anti)colour) for the
   * particle entries in this event.
   */
  vector< pair<int,int> > ICOLUP;

  /**
   * Lab frame momentum (Px, Py, Pz, E and M in GeV) for the particle
   * entries in this event.
   */
  vector< vector<double> > PUP;

  /**
   * Invariant lifetime (c*tau, distance from production to decay im
   * mm) for the particle entries in this event.
   */
  vector<double> VTIMUP;

  /**
   * Spin info for the particle entries in this event given as the
   * cosine of the angle between the spin vector of a particle and the
   * 3-momentum of the decaying particle, specified in the lab frame.
   */
  vector<double> SPINUP;

  /**
   * The total cross section for the sub processes in this reader.
   */
  CrossSection theXSec;

  /**
   * The overestimated cross section for the sub processes in this
   * reader.
   */
  CrossSection theMaxXSec;

  /**
   * The maximum weight found in this reader.
   */
  double theMaxWeight;

  /**
   * The number of events in this reader. If less than zero the number
   * of events is unlimited.
   */
  long theNEvents;

  /**
   * The maximum number of events to scan to collect information about
   * processes and cross sections. If less than 0, all events will be
   * scanned.
   */
  long theMaxScan;

  /**
   * True if this reader produces weighted events.
   */
  bool isWeighted;

  /**
   * True if negative weights may be produced.
   */
  bool hasNegativeWeights;

  /**
   * Name of file used to cache the events form the reader in a
   * fast-readable form. If empty, no cache file will be generated.
   */
  string theCacheFileName;

  /**
   * Should the events from this Reader be randomized in order to
   * avoid problems if not all events are used.
   */
  bool doRandomize;

  /**
   * The total number of events requested so far.
   */
  long theNAttempted;

  /**
   * Number of requested events per process number.
   */
  CountMap theAttemptMap;

  /**
   * The number of events accepted so far.
   */
  long theNAccepted;

  /**
   * Number of accepted events per process number.
   */
  CountMap theAcceptMap;

  /**
   * The pair of PartonBinInstance objects describing the current
   * incoming partons in the event.
   */
  PBIPair thePartonBinInstances;

  /**
   * Association between ColourLines and colour indices in the current
   * translation.
   */
  ObjectIndexer<long,ColourLine> colourIndex;

  /**
   * Association between Particles and indices in the current
   * translation.
   */
  ObjectIndexer<long,Particle> particleIndex;

  /**
   * The instances of the beam particles for the current event.
   */
  PPair theBeams;

  /**
   * The instances of the incoming particles to the sub process for
   * the current event.
   */
  PPair theIncoming;

  /**
   * The instances of the outgoing particles from the sub process for
   * the current event.
   */
  PVector theOutgoing;

  /**
   * The instances of the intermediate particles in the sub process for
   * the current event.
   */
  PVector theIntermediates;

  /**
   * File stream for the cache.
   */
  CFile theCacheFile;

private:

  /** Access function for the interface. */
  void setBeamA(long id);
  /** Access function for the interface. */
  long getBeamA() const;
  /** Access function for the interface. */
  void setBeamB(long id);
  /** Access function for the interface. */
  long getBeamB() const;
  /** Access function for the interface. */
  void setEBeamA(Energy e);
  /** Access function for the interface. */
  Energy getEBeamA() const;
  /** Access function for the interface. */
  void setEBeamB(Energy e);
  /** Access function for the interface. */
  Energy getEBeamB() const;

private:

  /**
   * Describe an abstract base class with persistent data.
   */
  static AbstractClassDescription<LesHouchesReader> initLesHouchesReader;

  /**
   * Private and non-existent assignment operator.
   */
  LesHouchesReader & operator=(const LesHouchesReader &);

public:

  /** Exception class used by LesHouchesReader in case inconsistencies
   *  are encountered. */
  class LesHouchesInconsistencyError: public Exception {};
  
  /** Exception class used by LesHouchesReader in case more events
      than available are requested. */
  class LesHouchesReopenWarning: public Exception {};

  /** Exception class used by LesHouchesReader in case reopening an
      event file fails. */
  class LesHouchesReopenError: public Exception {};

  /** Exception class used by LesHouchesReader in case there is
      information missing in the initialization phase. */
  class LesHouchesInitError: public InitException {};

};

}


#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/**
 * This template specialization informs ThePEG about the
 * base class of LesHouchesReader.
 */
template <>
struct BaseClassTrait<LesHouchesReader,1>: public ClassTraitsType {
  /** Typedef of the base class of LesHouchesReader. */
  typedef HandlerBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * LesHouchesReader class and the shared object where it is
 * defined.
 */
template <>
struct ClassTraits<LesHouchesReader>
  : public ClassTraitsBase<LesHouchesReader> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::LesHouchesReader"; }
  /**
   * Return the name of the shared library to be loaded to get access
   * to the LesHouchesReader class and every other class it uses
   * (except the base class).
   */
  static string library() { return "libThePEGLesHouches.so"; }

};

}

// #include "LesHouchesReader.tcc"
#include "LesHouchesReader.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#endif

#endif /* THEPEG_LesHouchesReader_H */
