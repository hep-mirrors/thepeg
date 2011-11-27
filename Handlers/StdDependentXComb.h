// -*- C++ -*-
//
// StdDependentXComb.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
// Copyright (C) 2009-2010 Simon Platzer
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_StdDependentXComb_H
#define ThePEG_StdDependentXComb_H
// This is the declaration of the StdDependentXComb class.

#include "StandardXComb.h"
#include "StdDependentXComb.fh"

namespace ThePEG {

/**
 * The StdDependentXComb class inherits from the StandardXComb
 * class and represents information on a hard subprocess in dependence
 * of another hard subprocess referred to by the head XComb object.
 * Such associations are commonly encountered in higher order corrections
 * carried ouut within the subtraction method. This is indeed the main
 * application of the StdXCombGroup and StdDependentXComb classes.
 *
 * @see StdXCombGroup
 * @see MEGroup
 */
class StdDependentXComb: public StandardXComb {

  /** MEBase needs to be a friend. */
  friend class MEBase;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Standard constructor.
   */
  StdDependentXComb(tStdXCombPtr newHead,
		    const PBPair & newPartonBins, tMEPtr newME,
		    const DiagramVector & newDiagrams);

  /**
   * Default constructor.
   */
  StdDependentXComb();

  /**
   * Destructor.
   */
  virtual ~StdDependentXComb();

public:

  /**
   * Return the cross section differential in the variables
   * previously supplied. The PDF weight is taken from the
   * lastPDFWeight supplied by the head XComb object.
   */
  CrossSection dSigDR();

  /**
   * Setup information on incoming partons depending
   * on the information previously supplied through the
   * choice of diagram and incoming momenta in the first
   * two entries of meMomenta(). Partons are not actually
   * extracted from the incoming particles, though a subprocess
   * detached from the current Event may be created.
   */
  void setIncomingPartons();

  /**
   * Indicate that information on incoming partons
   * has to be collected.
   */
  void remakeIncoming() { resetIncoming = true; }

  /**
   * Set the process as selected by the dependent matrix element.
   */
  void setProcess();

  /**
   * Construct a sub-process object from the information available.
   */
  virtual tSubProPtr construct();

  /**
   * Properly setup the PartonBinInstance objects
   * provided a sub process has been constructed
   * using this XComb.
   */
  void setPartonBinInstances(Energy2 scale = ZERO);

  /** @name Functions used for collecting statistics. */
  //@{
  /**
   * The statistics object for this XComb.
   */
  virtual const XSecStat & stats() const { return head()->stats(); }

  /**
   * Select the current event. It will later be rejected with a
   * probability given by \a weight.
   */
  virtual void select(double weight) { head()->select(weight); }

  /**
   * Accept the current event assuming it was previously selcted.
   */
  virtual void accept() { head()->accept(); }

  /**
   * Reject the current event assuming it was previously accepted. If
   * weighted events are produced, the \a weight should be the same as
   * the previous call to select(double).
   */
  virtual void reject(double weight = 1.0) { head()->reject(weight); }

  /**
   * Reset statistics.
   */
  virtual void reset() { head()->reset(); }
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
   * Standard Init function used to initialize the interface.
   */
  static void Init();

private:

  /**
   * Wether or not we have to reset the incoming partons
   */
  bool resetIncoming;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<StdDependentXComb> initStdDependentXComb;
 
  /**
   * Private and non-existent assignment operator.
   */
  StdDependentXComb & operator=(const StdDependentXComb &);

};

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the base class of
 * StdDependentXComb.
 */
template <>
struct BaseClassTrait<StdDependentXComb,1> {
  /** Typedef of the base class of StdDependentXComb. */
  typedef StandardXComb NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * StdDependentXComb class.
 */
template <>
struct ClassTraits<StdDependentXComb>:
    public ClassTraitsBase<StdDependentXComb> {
  /** Return the class name. */
  static string className() { return "ThePEG::StdDependentXComb"; }
};

/** @endcond */

}

#endif /* ThePEG_StdDependentXComb_H */
