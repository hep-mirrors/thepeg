// -*- C++ -*-
//
// PDFCuts.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_PDFCuts_H
#define ThePEG_PDFCuts_H
// This is the declaration of the PDFCuts class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Interval.h"
#include "ThePEG/Cuts/Cuts.fh"

namespace ThePEG {

/**
 * The PDFCuts class is used to specify cuts on scale and momentum
 * fractions for which a PDFBase object is expected to give parton
 * densities. It is used to estimate upper limits on the parton
 * densities to be generated by a PDFBase object.
 *
 * @see PDFBase
 */
class PDFCuts {

public:

  /** @name Standard constructors, assignment and destructors. */
  //@{
  /**
   * Default constructor.
   */
  PDFCuts() : theSMax() {}

  /**
   * Construction from members.
   */
  PDFCuts(const Interval<double> & newL,
	  const SInterval & newScale, const Energy2 & newSMax) 
    : theL(newL), theScale(newScale), theSMax(newSMax) {}

  /**
   * Construction from a Cuts object, using the values for
   * the first incoming parton (or not).
   */
  PDFCuts(const Cuts &, bool first, const SInterval & S,
	  const SInterval & sHat);

  /**
   * Construction from a Cuts object, using the values for
   * the first incoming parton (or not).
   */
  PDFCuts(const Cuts &, bool first, Energy maxEnergy);
  //@}

public:

  /** @name Access the individual limits. */
  //@{
  /**
   * The minimum value of \f$\log(1/x)\f$.
   */
  double lMin() const { return theL.lower(); }


  /**
   * The maximum value of \f$\log(1/x)\f$.
   */
  double lMax() const { return theL.upper(); }

  /**
   * The minimum value of x.
   */
  double xMin() const { return exp(-lMax()); }


  /**
   * The maximum value of x.
   */
  double xMax() const { return exp(-lMin()); }


  /**
   * The lower limit on the scale to be used.
   */
  Energy2 scaleMin() const { return theScale.lower(); }


  /**
   * The upper limit on the scale to be used.
   */
  Energy2 scaleMax() const { return theScale.upper(); }


  /**
   * The maximum scale for a given momentum fraction.
   */
  Energy2 scaleMax(double x) const { return min(scaleMax(), sMax()*x); }


  /**
   * The maximum scale for a given logarithmic momentum fraction.
   */
  Energy2 scaleMaxL(double l) const { return scaleMax(exp(-l)); }


  /**
   * The maximum invariant mass squared of the colliding particles.
   */
  Energy2 sMax() const { return theSMax; }


  //@}

private:

  /**
   * The minimum and maximum values of \f$\log(1/x)\f$.
   */
  Interval<double> theL;

  /**
   * The limits on the scale to be used.
   */
  SInterval theScale;

  /**
   * The maximum invariant mass squared of the colliding particles.
   */
  Energy2 theSMax;

};

}

#endif /* ThePEG_PDFCuts_H */
