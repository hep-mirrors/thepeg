// -*- C++ -*-
#ifndef ThePEG_StandardXComb_H
#define ThePEG_StandardXComb_H
// This is the declaration of the StandardXComb class.

#include "ThePEG/Config/ThePEG.h"
#include "SubProcessHandler.fh"
#include "ThePEG/PDF/PartonExtractor.fh"
#include "ThePEG/PDF/PartonBin.h"
#include "ThePEG/PDF/PartonBinInstance.h"
#include "ThePEG/Utilities/VSelector.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/Math.h"
#include "ThePEG/Utilities/XSecStat.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/MatrixElement/MEBase.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Handlers/StandardEventHandler.h"
#include "ThePEG/MatrixElement/MEBase.h"
#include "ThePEG/Handlers/SubProcessHandler.fh"
#include "StandardXComb.fh"

namespace ThePEG {

/**
 * The StandardXComb class inherits from the more general XComb class
 * which stores all information about the generation of a hard
 * sub-proces for a given pair of incoming particles, a pair of
 * extracted partons, etc. This class stores more information related
 * to thestandard process generation scheme in ThePEG, such as the
 * PartonExtractor and MEBase object used. It also does some of the
 * administration of the process generation.
 *
 * The main function is dSigDR() which returns the differential cross
 * section w.r.t. a given vector of random numbers in the interval
 * ]0,1[. In the initialization this is used to pre-sample the phase
 * space. In the generation phase it is used to give the cross section
 * for a phase space point, and if this StandardXComb is chosen the
 * construct() function is called to generate the actual sub-process.
 *
 * @see ParonExtractor
 * @see MEBase
 * @see Cuts
 */
class StandardXComb: public XComb {

public:

  /** A vector of DiagramBase objects. */
  typedef MEBase::DiagramVector DiagramVector;

  /** A vector of indices. */
  typedef MEBase::DiagramIndex DiagramIndex;

  /** MEBase needs to be a friend. */
  friend class MEBase;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Standard constructor.
   */
  StandardXComb(Energy newMaxEnergy, const cPDPair & inc,
		tStdEHPtr newEventHandler,tSubHdlPtr newSubProcessHandler,
		tPExtrPtr newExtractor,	tCascHdlPtr newCKKW,
		const PBPair & newPartonBins, tCutsPtr newCuts, tMEPtr newME,
		const DiagramVector & newDiagrams, bool mir);

  /**
   * Copy-constructor.
   */
  StandardXComb(const StandardXComb &);

  /**
   * Default constructor.
   */
  StandardXComb();

  /**
   * Destructor.
   */
  ~StandardXComb();

  /**
   * Constructor used by MEBase to create a temporary object to store info.
   */
  StandardXComb(tMEPtr me, const tPVector & parts, DiagramIndex i);

  //@}

  /** @name Access the assigned objects used in the generation. */
  //@{
  /**
   * Return a pointer to the corresponding sub-process handler. May be
   * null if the standard process generation in ThePEG was not used.
   */
  inline tcSubHdlPtr subProcessHandler() const;

  /**
   * The matrix element to be used.
   */
  inline tMEPtr matrixElement() const;
  //@}

  /** @name Main functions used for the generation. */
  //@{
  /**
   * Try to determine if this subprocess is at all possible.
   */
  virtual bool checkInit();

  /**
   * The number of dimensions of the phase space used to generate this
   * process.
   */
  inline int nDim() const;

  /**
   * Generate a phase space point from a vector \a r of \a nr numbers
   * in the interval ]0,1[ and return the corresponding differential
   * cross section.
   */
  CrossSection dSigDR(const pair<double,double> ll, int nr, const double * r);

  /**
   * Construct a sub-process object from the information available.
   */
  tSubProPtr construct();
  //@}

  /** @name Functions used for collecting statistics. */
  //@{
  /**
   * The statistics object for this XComb.
   */
  inline const XSecStat & stats() const;

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
   * Reset statistics.
   */
  inline void reset();
  //@}

  /** @name Access information used by the MEBase object. */
  //@{
  /**
   * The diagrams used by the matrix element.
   */
  inline const DiagramVector & diagrams() const;

  /**
   * True if the TreeDiagram's for this matrix element should in fact
   * be mirrored before used to create an actual sub-rocess.
   */
  inline bool mirror() const;

  /**
   * Return the momenta of the partons to be used by the matrix
   * element object, in the order specified by the TreeDiagram objects
   * given by the matrix element.
   */
  inline const vector<Lorentz5Momentum> & meMomenta() const;

  /**
   * Return the last selected diagram.
   */
  inline tcDiagPtr lastDiagram() const;

  /**
   * Return the parton types to be used by the matrix element object,
   * in the order specified by the TreeDiagram objects given by the
   * matrix element.
   */
  inline const cPDVector & mePartonData() const;

  /**
   * Return the index of the last selected diagram.
   */
  inline DiagramIndex lastDiagramIndex() const;

  /**
   * Get information saved by the matrix element in the calculation of
   * the cross section to be used later when selecting diagrams and
   * colour flow.
   */
  inline const DVector & meInfo() const;

  /**
   * Set information saved by the matrix element in the calculation of
   * the cross section to be used later when selecting diagrams and
   * colour flow.
   */
  inline void meInfo(const DVector & info);
  //@}

protected:

  /**
   * Construct the corresponding SubProcess object if it hasn't been
   * done before.
   */
  void newSubProcess();

  /**
   * Return the momenta of the partons to be used by the matrix
   * element object, in the order specified by the TreeDiagram objects
   * given by the matrix element.
   */
  inline vector<Lorentz5Momentum> & meMomenta();

  /**
   * Return the parton types to be used by the matrix element object,
   * in the order specified by the TreeDiagram objects given by the
   * matrix element.
   */
  inline cPDVector & mePartonData();

  /**
   * Set the last selected diagram.
   */
  inline void lastDiagramIndex(DiagramIndex);

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
   * Standard Init function used to initialize the interface.
   */
  static void Init();

private:

  /**
   * The corresponding sub-process handler
   */
  SubHdlPtr theSubProcessHandler;

  /**
   * The matrix element to be used.
   */
  tMEPtr theME;

  /**
   * Statistics gathering for this XComb.
   */
  XSecStat theStats;

  /**
   * The diagrams used by the matrix element.
   */
  DiagramVector theDiagrams;

  /**
   * True if the TreeDiagram's for this matrix element should in fact
   * be mirrored before used to create an actual sub-rocess.
   */
  bool isMirror;

  /**
   * The number of dimensions of the phase space used to generate this
   * process.
   */
  int theNDim;

  /**
   * The number of dimensions of the phase space used for each of the
   * incoming partons.
   */
  pair<int,int> partonDims;

  /**
   * The momenta of the partons to be used by the matrix element
   * object, in the order specified by the TreeDiagram objects given
   * by the matrix element.
   */
  vector<Lorentz5Momentum> theMEMomenta;

  /**
   * The parton types to be used by the matrix element object, in the
   * order specified by the TreeDiagram objects given by the matrix
   * element.
   */
  cPDVector theMEPartonData;

  /**
   * The last selected tree diagram.
   */
  DiagramIndex theLastDiagramIndex;

  /**
   * Information saved by the matrix element in the calculation of the
   * cross section to be used later when selecting diagrams and colour
   * flow.
   */
  DVector theMEInfo;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<StandardXComb> initStandardXComb;
 
  /**
   * Private and non-existent assignment operator.
   */
  StandardXComb & operator=(const StandardXComb &);

};

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the base class of
 * StandardXComb.
 */
template <>
struct BaseClassTrait<StandardXComb,1>: public ClassTraitsType {
  /** Typedef of the base class of StandardXComb. */
  typedef XComb NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * StandardXComb class.
 */
template <>
struct ClassTraits<StandardXComb>:
    public ClassTraitsBase<StandardXComb> {
  /** Return the class name. */
  static string className() { return "ThePEG::StandardXComb"; }
};

/** @endcond */

}

#include "StandardXComb.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StandardXComb.tcc"
#endif

#endif /* ThePEG_StandardXComb_H */
