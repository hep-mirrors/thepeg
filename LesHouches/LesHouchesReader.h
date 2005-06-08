// -*- C++ -*-
#ifndef THEPEG_LesHouchesReader_H
#define THEPEG_LesHouchesReader_H
// This is the declaration of the LesHouchesReader class.

#include "LesHouches.h"
#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Utilities/ObjectIndexer.h"
#include "ThePEG/Utilities/Exception.h"
#include "ThePEG/Utilities/XSecStat.h"
#include "ThePEG/PDF/PartonBinInstance.h"
#include "ThePEG/PDF/PartonBin.fh"
#include "ThePEG/MatrixElement/ReweightBase.h"
#include "LesHouchesEventHandler.fh"
#include "LesHouchesReader.fh"
#include <cstdio>

namespace ThePEG {

/**
 * LesHouchesReader is an abstract base class to be used for objects
 * which reads event files or streams from matrix element
 * generators. Derived classes must at least implement the open() and
 * doReadEvent() methods to read in information about the whole run into
 * the HEPRUP variable and next event into the HEPEUP variable
 * respectively. Also the close() function to close the file or stream
 * read must be implemented. Although these functions are named as if
 * we are reading from event files, they could just as well implement
 * the actual generation of events.
 *
 * After filling the HEPRUP and HEPEUP variables, which are protected
 * and easily accesible from the sub-class, this base class will then
 * be responsible for transforming this data to the ThePEG Event
 * record in the getEvent() method. <code>LesHouchesReader</code>s can
 * only be used inside LesHouchesEventHandler objects.
 *
 * In the initialization the virtual open() and scan() functions are
 * called. Here the derived class must provide the information about
 * the processes in the variables corresponding to the HEPRUP common
 * block. Note that the IDWTUP variable is not explicitly
 * used. Instead the derived class must specify whether the generated
 * events are weighted with or without negative weights using the
 * weighted(bool) and negativeWeights(bool) functions. If the events
 * are not weighted, the XSECUP vector should be filled with the
 * correct cross sections (in pb) for the corresponding subprocesses
 * and the getEvent() function should always return 1. Otherwise, the
 * XMAXUP vector should be filled with the overestimated cross
 * sections (in pb) for the corresponding subprocesses and the
 * getEvent() function should return a probability with which the
 * event should be accepted.
 *
 * Note that the information given per process in e.g. the XSECUP and
 * XMAXUP vectors is not used by the LesHouchesEventHandler and by
 * default the LesHouchesReader is not assumed to be able to actively
 * choose between the sub-processes. Instead, the
 * LesHouchesEventHandler can handle several LesHouchesReader objects
 * and choose between them. However, a sub-class of LesHouchesReader
 * may set the flag isActive, in which case it is assumed to be able
 * to select between its sub-processes itself.
 *
 * The LesHouchesReader may be assigned a number ReweightBase objects
 * which either completely reweights the events produced (in the
 * reweights vector), or only biases the selection without influencing
 * the cross section (in the preweights vector). Note that it is the
 * responsibility of a sub-class to call the reweight() function and
 * multiply the weight according to its return value (typically done
 * in the readEvent() function).
 *
 * @see \ref LesHouchesReaderInterfaces "The interfaces"
 * defined for LesHouchesReader.
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
   * Map for accumulating statistics of cross sections per process
   * number.
   */
  typedef map<int,XSecStat> StatMap;

  /**
   * Map of XComb objects describing the incoming partons indexed by
   * the corresponding PartonBin pair.
   */
  typedef map<tcPBPair,XCombPtr> XCombMap;

  /**
   * A vector of pointers to ReweightBase objects.
   */
  typedef vector<ReweightPtr> ReweightVector;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor. If the optional argument is true, the reader
   * is assumed to be able to produce events on demand for a given
   * process.
   */
  LesHouchesReader(bool active = false);

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

  /** @name Main virtual fuctions to be overridden in
   *  sub-classes. They are named as if we are reading from event
   *  files, but could equally well implement the actual generation of
   *  events. */
  //@{
  /**
   * Open a file or stream with events and read in the run information
   * into the heprup variable.
   */
  virtual void open() = 0;

  /**
   * Read the next event form the file or stream into the
   * corresponding protected variables. Return false if there is no
   * more events.
   */
  virtual bool doReadEvent() = 0;

  /**
   * Close the file or stream from which events have been read.
   */
  virtual void close() = 0;
  //@}

  /** @name Other important function which may be overridden in
   *  sub-classes which wants to bypass the basic HEPRUP or HEPEUP
   *  variables or otherwise facilitate the conversion to ThePEG
   *  objects.. */
  //@{
  /**
   * Initialize. This function is called by the LesHouchesEventHandler
   * to which this object is assigned.
   */
  virtual void initialize(LesHouchesEventHandler & eh);

  /**
   * Calls readEvent() or uncacheEvent() to read information into the
   * LesHouches common block variables. This function is called by the
   * LesHouchesEventHandler if this reader has been selectod to
   * produce an event.
   *
   * @return the weight asociated with this event. If negative weights
   * are allowed it should be between -1 and 1, otherwise between 0
   * and 1. If outside these limits the previously estimated maximum
   * is violated. Note that the estimated maximum then should be
   * updated from the outside.
   */
  virtual double getEvent();

  /**
   * Calls doReadEvent() and performs pre-defined reweightings. A
   * sub-class overrides this function it must make sure that the
   * corresponding reweightings are done.
   */
  virtual bool readEvent();

  /**
   * Skip \a n events. Used by LesHouchesEventHandler to make sure
   * that a file is scanned an even number of times in case the events
   * are not ramdomly distributed in the file.
   */
  virtual void skip(long n);

  /**
   * Get an XComb object. Converts the information in the Les Houches
   * common block variables to an XComb object describing the sub
   * process. This is the way information is conveyed from the reader
   * to the controlling LesHouchesEventHandler.
   */
  tXCombPtr getXComb();

  /**
   * Scan the file or stream to obtain information about cross section
   * weights and particles etc. This function should fill the
   * variables corresponding to the /HEPRUP/ common block. The
   * function returns the number of events scanned.
   */
  virtual long scan();

  /**
   * Take the information corresponding to the HEPRUP common block and
   * initialize the statistics for this reader.
   */
  virtual void initStat();

  /**
   * Reweights the current event using the reweights and preweights
   * vectors. It is the responsibility of the sub-class to call this
   * function after the HEPEUP information has been retrieved.
   */
  double reweight();

  /**
   * Converts the information in the Les Houches common block
   * variables into a Particle objects.
   */
  virtual void fillEvent();

  /**
   * Removes the particles created in the last generated event,
   * preparing to produce a new one.
   */
  void reset();

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
   * The number of events found in this reader. If less than zero the
   * number of events are unlimited.
   */
  inline long NEvents() const;

  /**
   * The number of events produced so far. Is reset to zero if an
   * event file is reopened.
   */
  inline long currentPosition() const;

  /**
   * The maximum number of events to scan to collect information about
   * processes and cross sections. If less than 0, all events will be
   * scanned.
   */
  inline long maxScan() const;

  /**
   * Return true if this reader is active.
   */
  inline bool active() const;

  /**
   * Return true if this reader produces weighted events.
   */
  inline bool weighted() const;

  /**
   * True if negative weights may be produced.
   */
  inline bool negativeWeights() const;

  /**
   * The collected cross section statistics for this reader.
   */
  inline const XSecStat & xSecStats() const;

  /**
   * Collected statistics about the individual processes.
   */
  inline const StatMap & processStats() const;

  /**
   * Select the current event. It will later be rejected with a
   * probability given by \a weight.
   */
  inline void select(double weight);

  /**
   * Accept the current event assuming it was previously selcted.
   */
  inline void accept();

  /**
   * Reject the current event assuming it was previously accepted.
   */
  inline void reject();

  /**
   * Increase the overestimated cross section for this reader.
   */
  inline void increaseMaxXSec(CrossSection maxxsec);

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
   * The map of XComb objects indexed by the corresponding PartonBin
   * pair.
   */
  inline const XCombMap & xCombs() const;

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
   * Reopen a reader. If we have reached the end of an event file,
   * reopen it and issue a warning if we have used up a large fraction
   * of it.
   */
  void reopen();

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
   * PartonBinInstance objects corresponding to the incoming
   * partons. Return the corresponding PartonBin objects.
   */
  virtual tcPBPair createPartonBinInstances();

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
   * Set true if this reader produces weighted events.
   */
  inline void weighted(bool);

  /**
   * The number of events in this reader. If less than zero the number
   * of events is unlimited.
   */
  inline void NEvents(long);

  /**
   * Set true if negative weights may be produced.
   */
  inline void negativeWeights(bool);

  /**
   * The map of XComb objects indexed by the corresponding PartonBin
   * pair.
   */
  inline XCombMap & xCombs();
  //@}

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit() throw(InitException);

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  virtual void doinitrun();

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
   * The HEPRUP common block.
   */
  HEPRUP heprup;

  /**
   * The HEPEUP common block.
   */
  HEPEUP hepeup;

  /**
   * The ParticleData objcest corresponding to the incoming particles.
   */
  tcPDPair inData;

  /**
   * The PDFBase object used for the first beam particle. Specified in
   * the interface or derived from PDFGUP and PDFSUP.
   */
  pair<PDFPtr,PDFPtr> inPDF;

  /**
   * The PDFBase object used for the second beam particle. Specified in
   * the interface or derived from PDFGUP and PDFSUP.
   */
  pair<cPDFPtr,cPDFPtr> outPDF;

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
   * The map of XComb objects indexed by the corresponding PartonBin
   * pair.
   */
  XCombMap theXCombs;

  /**
   * The KinematicalCuts object to be used for this reader.
   */
  KinCutPtr theCuts;

  /**
   * The number of events in this reader. If less than zero the number
   * of events is unlimited.
   */
  long theNEvents;

  /**
   * The number of events produced by this reader so far. Is reset
   * every time an event file is reopened.
   */
  long position;

  /**
   * The number of times this reader has been reopened.
   */
  int reopened;

  /**
   * The maximum number of events to scan to collect information about
   * processes and cross sections. If less than 0, all events will be
   * scanned.
   */
  long theMaxScan;

  /**
   * True if this is an active reader.
   */
  bool isActive;

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
   * Collect statistics for this reader.
   */
  XSecStat stats;

  /**
   * Collect statistics for each individual process.
   */
  StatMap statmap;

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

  /**
   * The reweight objects modifying the weights of this reader.
   */
  ReweightVector reweights;

  /**
   * The preweight objects modifying the weights of this reader.
   */
  ReweightVector preweights;

  /**
   * The factor with which this reader was last pre-weighted.
   */
  double preweight;

  /**
   * Should the event be reweighted by PDFs used by the PartonExtractor?
   */
  bool reweightPDF;

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
  /** Access function for the interface. */
  void setPDFA(PDFPtr);
  /** Access function for the interface. */
  PDFPtr getPDFA() const;
  /** Access function for the interface. */
  void setPDFB(PDFPtr);
  /** Access function for the interface. */
  PDFPtr getPDFB() const;

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
  static string library() { return "LesHouches.so"; }

};

}

// #include "LesHouchesReader.tcc"
#include "LesHouchesReader.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#endif

#endif /* THEPEG_LesHouchesReader_H */
