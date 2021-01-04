// -*- C++ -*-
//
// HepMCReader.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2020 Julian Lukwata
//
// ThePEG is licenced under version 3 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef THEPEG_HepMCReader_H
#define THEPEG_HepMCReader_H
//
// This is the declaration of the HepMCInFile class.
//
#include <cstdio>
#include <cstring>
#include <config.h>
#include "HepMCEventHandler.h"


#ifdef HAVE_HEPMC3
#include "HepMC3/ReaderAscii.h"
#include "HepMC3/GenEvent.h"
#include "HepMC3/Units.h"
#else
#include "HepMC/IO_BaseClass.h"
#include "HepMC/GenEvent.h"
#endif

#include "ThePEG/Handlers/HandlerBase.h"

#include "ThePEG/Utilities/ObjectIndexer.h"
#include "ThePEG/Utilities/Exception.h"
/* #include "ThePEG/Config/Unitsystem.h" */
/* #include "ThePEG/Utilities/XSecStat.h" */
#include "ThePEG/PDF/PartonBinInstance.h"
#include "ThePEG/PDF/PartonBin.fh"
/* #include "ThePEG/MatrixElement/ReweightBase.h" */
#include "HepMCReader.fh"
#include "HepMCEventHandler.fh"



namespace ThePEG {

  /**
   * HepMCReader is a class to be used for objects
   * which reads event files .
   *
   * this base class will then be responsible for transforming this data to
   * the ThePEG Event record in the getEvent() method.
   * <code>HepMCReader</code>s can only be used inside HepMCEventHandler objects.
   *
   *
   * The HepMCReader may be assigned a number ReweightBase objects
   * which either completely reweights the events produced (in the
   * reweights vector), or only biases the selection without influencing
   * the cross section (in the preweights vector). Note that it is the
   * responsibility of a sub-class to call the reweight() function and
   * multiply the weight according to its return value (typically done
   * in the readEvent() function).
   *
   * @see Event
   * @see HepMCEventHandler
   */
  class HepMCReader: public HandlerBase, public LastXCombInfo<> {

    /**
     * HepMCEventHandler should have access to our private parts.
     */
    friend class HepMCEventHandler;

    /**
     * Map for accumulating statistics of cross sections per process
     * number.
     */
    /* typedef map<int,XSecStat> StatMap; */

    /**
     * Map of XComb objects describing the incoming partons indexed by
     * the corresponding PartonBin pair.
     */
    /* typedef map<tcPBPair,XCombPtr> XCombMap; */


    public:

    /** @name Standard constructors and destructors. */
    //@{
    /**
     * Default constructor.
     */
    HepMCReader();

    /**
     * Copy-constructor.
     */
    HepMCReader(const HepMCReader &);

    /**
     * Destructor.
     */
    virtual ~HepMCReader();
    //@}

    public:

    /** @name Main virtual fuctions to be overridden in
     *  sub-classes. They are named as if we are reading from event
     *  files, but could equally well implement the actual generation of
     *  events. */
    //@{

    /**
     * Read the next event from the file or stream into the
     * corresponding protected variables. Return false if there is no
     * more events.
     */
    virtual bool doReadEvent();


    /**
     * return the weight names
     */
    /* virtual vector<string> optWeightsNamesFunc(); */

    /**
     * vector with the optional weights names
     */

    /* vector<string> optionalWeightsNames; */

    //@}

    /** @name Other important function which may be overridden in
     *  sub-classes which wants to bypass the basic HEPRUP or HEPEUP
     *  variables or otherwise facilitate the conversion to ThePEG
     *  objects. */
    //@{
    /**
     * Initialize. This function is called by the HepMCEventHandler
     * to which this object is assigned.
     */
    virtual void initialize(HepMCEventHandler & eh);

    /**
     * Calls readEvent() to read information into the
     * variables. This function is called by the
     * HepMCEventHandler if this reader has been selectod to
     * produce an event.
     *
     * @return the weight asociated with this event. If negative weights
     * are allowed it should be between -1 and 1, otherwise between 0
     * and 1. If outside these limits the previously estimated maximum
     * is violated. Note that the estimated maximum then should be
     * updated from the outside.
     */
    /* virtual double getEvent(); */

    /**
     * Calls doReadEvent().
     */
    virtual bool readEvent();

    /**
     * Get an XComb object. Converts the information in the HepMC file
     * to an XComb object describing the sub process. This is the way
     * information is conveyed from the reader to the controlling HepMCEventHandler.
     */
    tXCombPtr getXComb();

    /**
     * Get a SubProcess object corresponding to the information in the
     */
    tSubProPtr getSubProcess();

    /**
     * Scan the file or stream to obtain information about cross section
     * weights and particles etc. This function should fill the
     * variables corresponding to the /HEPRUP/ common block. The
     * function returns the number of events scanned.
     */
    /* virtual long scan(); */

    /**
     * Take the information corresponding to the HEPRUP common block and
     * initialize the statistics for this reader.
     */
    /* virtual void initStat(); */

    /**
     * Reweights the current event using the reweights and preweights
     * vectors. It is the responsibility of the sub-class to call this
     * function after the HEPEUP information has been retrieved.
     */
    /* double reweight(); */

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
     * The current event weight given by XWGTUP times possible
     * reweighting. Note that this is not necessarily the same as what
     * is returned by getEvent(), which is scaled with the maximum
     * weight.
     */
    /* double eventWeight() const { return hepeup.XWGTUP*lastweight; } */

    /**
     * Return the optional named weights associated to the current event.
     */
    /* const map<string,double>& optionalEventWeights() const { return optionalWeights; } */

    /**
     * Return the optional npLO and npNLO
     */
    /* const int& optionalEventnpLO() const { return optionalnpLO; } */
    /* const int& optionalEventnpNLO() const { return optionalnpNLO; } */

    /**
     * The pair of PartonBinInstance objects describing the current
     * incoming partons in the event.
     */
    const PBIPair & partonBinInstances() const { return thePartonBinInstances; }
    /**
     * Return the instances of the beam particles for the current event.
     */
    const PPair & beams() const { return theBeams; }
    /* const PVector & beams() const { return theBeams; } */
    /**
     * Return the instances of the incoming particles to the sub process
     * for the current event.
     */
    const PPair & incoming() const { return theIncoming; }
    /* const PVector & incoming() const { return theIncoming; } */
    /**
     * Return the instances of the outgoing particles from the sub process
     * for the current event.
     */
    const PVector & outgoing() const { return theOutgoing; }
    /**
     * Return the instances of the intermediate particles in the sub
     * process for the current event.
     */
    const PVector & intermediates() const { return theIntermediates; }
    /**
     * If this reader is to be used (possibly together with others) for
     * CKKW reweighting and veto, this should give the multiplicity of
     * outgoing particles in the highest multiplicity matrix element in
     * the group.
     */
    /* int maxMultCKKW() const { return theMaxMultCKKW; } */
    /**
     * If this reader is to be used (possibly together with others) for
     * CKKW reweighting and veto, this should give the multiplicity of
     * outgoing particles in the lowest multiplicity matrix element in
     * the group.
     */
    /* int minMultCKKW() const { return theMinMultCKKW; } */
    //@}

    /** @name Other inlined access functions. */
    //@{
    /**
     * The number of events found in this reader. If less than zero the
     * number of events are unlimited.
     */
    /* long NEvents() const { return theNEvents; } */

    /**
     * The number of events produced so far. Is reset to zero if an
     * event file is reopened.
     */
    /* long currentPosition() const { return position; } */

    /**
     * The maximum number of events to scan to collect information about
     * processes and cross sections. If less than 0, all events will be
     * scanned.
     */
    /* long maxScan() const { return theMaxScan; } */

    /**
     * Return true if this reader is active.
     */
    /* bool active() const { return isActive; } */

    /**
     * The collected cross section statistics for this reader.
     */
    /* const XSecStat & xSecStats() const { return stats; } */

    /**
     * Collected statistics about the individual processes.
     */
    /* const StatMap & processStats() const { return statmap; } */

    /**
     * Increase the overestimated cross section for this reader.
     */
    /* virtual void increaseMaxXSec(CrossSection maxxsec); */

    /**
     * The PartonExtractor object used to construct remnants.
     */
    tPExtrPtr partonExtractor() const { return thePartonExtractor; }

    /**
     * Return a possibly null pointer to a CascadeHandler to be used for
     * CKKW-reweighting.
     */
    tCascHdlPtr CKKWHandler() const { return theCKKW; }

    /**
     * The pairs of PartonBin objects describing the partons which can
     * be extracted by the PartonExtractor object.
     */
    const PartonPairVec & partonBins() const { return thePartonBins; }

    /**
     * The map of XComb objects indexed by the corresponding PartonBin
     * pair.
     */
    /* const XCombMap & xComb() const { return theXComb; } */
    XCombPtr xComb() const { return theXComb; }

    /**
     * The Cuts object to be used for this reader.
     */
    /* CutsPtr cuts() const { return theCuts; } */
    const Cuts & cuts() const { return *theCuts; }

    /**
     *
     */
    const string filename() const { return _filename; }


#ifdef HAVE_HEPMC3
    std::shared_ptr<const HepMC3::GenEvent> event() { return std::const_pointer_cast<const HepMC3::GenEvent>(_event); }
#else
    const HepMC::GenEvent * event() const { return _event; }
#endif

    //@}

    protected:


    /** @name Auxilliary virtual methods which may be verridden by sub-classes. */
    //@{
    /**
     * Check the existence of a pair of PartonBin objects corresponding
     * to the current event.
     *
     * @return false if no pair of suitable PartonBin objects was found.
     */
    /* virtual bool checkPartonBin(); */

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
    /* virtual tcPBPair createPartonBinInstances(); */

    /**
     * Create instances of the incoming beams in the event and store
     * them in particleIndex. If no beam particles are included in the
     * event they are created from the run info.
     */
    /* virtual void createBeams(); */

    /**
     * Go through the mother indices and connect up the Particles.
     * TODO: Only needed if we consider intermediate steps :see_no_evil:
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

    /** @name Set functions for some variables not in the HepMC. */
    //@{
    /**
     * The number of events in this reader. If less than zero the number
     * of events is unlimited.
     */
    /* void NEvents(long x) { theNEvents = x; } */

    /**
     * The map of XComb objects indexed by the corresponding PartuonBin
     * pair.
     */
    /* XCombMap & xCombs() { return theXCombs; } */
    //@}

    /** @name Standard (and non-standard) Interfaced functions. */
    //@{
    /**
     * Initialize this object after the setup phase before saving an
     * EventGenerator to disk.
     * @throws InitException if object could not be initialized properly.
     */
    /* virtual void doinit(); */

    /**
     * Initialize this object. Called in the run phase just before
     * a run begins.
     */
    virtual void doinitrun();

    /**
     * Finalize this object. Called in the run phase just after a
     * run has ended. Used eg. to write out statistics.
     */
    virtual void dofinish();

    /**
     * Return true if this object needs to be initialized before all
     * other objects because it needs to extract PDFs from the event file.
     */
    /* virtual bool preInitialize() const; */

    /**
     * Called from doinit() to extract PDFs from the event file and add
     * the corresponding objects to the current EventGenerator.
     */
    /* virtual void initPDFs(); */
    //@}

    /** @name Clone Methods. */
    //@{
    /**
     * Make a simple clone of this object.
     * @return a pointer to the new object.
     */
    virtual IBPtr clone() const;

    /** Make a clone of this object, possibly modifying the cloned object
     * to make it sane.
     * @return a pointer to the new object.
     */
    virtual IBPtr fullclone() const;
    //@}

    protected:

    /**
     * number of event
     */
    int _eventNumber;

    /**
     *  The HepMC format
     */
    int _format;

    /**
     *  The HepMC filename
     */
    string _filename;

    /**
     *  The HepMC I/O handler
     */
#ifdef HAVE_HEPMC3
    HepMC3::Reader *_hepmcin;
#else
    /* HepMC::IO_AsciiParticles *_hepmcio; */
    HepMC::IO_BaseClass *_hepmcin;
#endif

    /**
     * Selector for the choice of units
     */
    int _unitchoice;

    /**
     * current HepMC event
     */
#ifdef HAVE_HEPMC3
    std::shared_ptr<HepMC3::GenEvent> _event; // HepMC3::Units::GEV, HepMC3::Units:MM);
#else
    HepMC::GenEvent *_event;
#endif
    /**
     * event scale
     */
    Energy2 _e_scale;

    /**
     * The ParticleData objects corresponding to the incoming particles.
     */
    tcPDPair inData;

    /**
     * The PDFBase objects which has been used for the beam particle
     * when generating the events being read. Specified in the interface
     * or derived from PDFGUP and PDFSUP.
     */
    pair<PDFPtr,PDFPtr> inPDF;

    /**
     * The PDFBase object to be used in the subsequent generation.
     */
    pair<cPDFPtr,cPDFPtr> outPDF;

    /**
     * The PartonExtractor object used to construct remnants.
     */
    tPExtrPtr thePartonExtractor;

    /**
     * A pointer to a CascadeHandler to be used for CKKW-reweighting.
     */
    tCascHdlPtr theCKKW;

    /**
     * The pairs of PartonBin objects describing the partons which can
     * be extracted by the PartonExtractor object.
     */
    PartonPairVec thePartonBins;

    /**
     * The map of XComb objects indexed by the corresponding PartonBin
     * pair.
     */
    /* XCombMap theXCombs; */
    XCombPtr theXComb;

    /**
     * The Cuts object to be used for this reader.
     */
    CutsPtr theCuts;

    /**
     * Determines whether to apply cuts to events before converting them
     * to ThePEG format.
     */
    bool doCutEarly;

    /**
     * Collect statistics for this reader.
     */
    /* XSecStat stats; */

    /**
     * Collect statistics for each individual process.
     */
    /* StatMap statmap; */

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
    /* PVector theBeams; */

    /**
     * The instances of the incoming particles to the sub process for
     * the current event.
     */
    PPair theIncoming;
    /* PVector theIncoming; */

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
     * Should PDFBase objects be constructed from the information in the
     * event file in the initialization?
     */
    bool doInitPDFs;

    /**
     * If the maximum cross section of this reader has been increased
     * with increaseMaxXSec(), this is the total factor with which it
     * has been increased.
     */
    /* double maxFactor; */

    /**
     * npLO for HepMC merging
     */
    /* int optionalnpLO; */

    /**
     * npNLO for HepMC merging
     */
    /* int optionalnpNLO; */

    /**
     * The (reweighted) XWGTUP value should be scaled with this cross
     * section when compared to the overestimated cross section.
     */
    /* CrossSection weightScale; */

    /**
     * Individual scales for different sub-processes if reweighted.
     */
    /* vector<double> xSecWeights; */

    /**
     * Individual maximum weights for individual (possibly reweighted)
     * processes.
     */
    /* map<int,double> maxWeights; */

    /**
     *  Option for the treatment of the momenta supplied
     */
    /* unsigned int theMomentumTreatment; */

    /**
     * just for me
     */

    /* Energy _emax; */
    double E_double;

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
    static ClassDescription<HepMCReader> initHepMCReader;

    /**
     * Private and non-existent assignment operator.
     */
    HepMCReader & operator=(const HepMCReader &) = delete;

    public:

    /** @cond EXCEPTIONCLASSES */
    /** Exception class used by HepMCReader in case inconsistencies
     *  are encountered. */
    class HepMCInconsistencyError: public Exception {};

    /** Exception class used by HepMCReader in case more events
      than available are requested. */
    class HepMCReopenWarning: public Exception {};

    /** Exception class used by HepMCReader in case there is
      information missing in the initialization phase. */
    class HepMCInitError: public InitException {};
    /** @endcond */

  };

  /// Stream output for HEPEUP
  /* ostream & operator<<(ostream & os, const HEPEUP & h); */

}


#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

  /** @cond TRAITSPECIALIZATIONS */

  /**
   * This template specialization informs ThePEG about the
   * base class of HepMCReader.
   */
  template <>
    struct BaseClassTrait<HepMCReader,1>: public ClassTraitsType {
      /** Typedef of the base class of HepMCReader. */
      typedef HandlerBase NthBase;
    };

  /**
   * This template specialization informs ThePEG about the name of the
   * HepMCReader class and the shared object where it is
   * defined.
   */
  template <>
    struct ClassTraits<HepMCReader>
    : public ClassTraitsBase<HepMCReader> {
      /**
       * Return the class name.
       */
      static string className() { return "ThePEG::HepMCReader"; }
      /**
       * Return the name of the shared library to be loaded to get access
       * to the HepMCReader class and every other class it uses
       * (except the base class).
       */
      static string library() { return "HepMCReader.so"; }

    };

  /** @endcond */

}


#endif /* THEPEG_HepMCReader_H */
