// -*- C++ -*-
#ifndef ThePEG_PDF_H
#define ThePEG_PDF_H
// This is the declaration of the PDF class.

#include "ThePEG/PDF/PartonBinInstance.h"
// #include "PDF.fh"
// #include "PDF.xh"

namespace ThePEG {

/**
 * PDF is a simple wrapper class with normal copy-semantics which
 * holds a PDFBase object and a ParticleData object for which to
 * determine parton densities.
 */
class PDF {

public:

  /** @name Standard constructors, assignment and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline PDF();

  /**
   * Copy-constructor.
   */
  inline PDF(const PDF &);

  /**
   * Constructor from a given PartonBinInstance.
   */
  inline PDF(tcPBIPtr);

  /**
   * Destructor.
   */
  inline ~PDF();

  /**
   * Assignment operator.
   */
  inline PDF & operator=(const PDF &);
  //@}

public:

  /** @name Access the parton densities. */
  //@{
  /**
   * Return the density for the given \a parton, for a given \a
   * partonScale and logarithmic momentum fraction \a l assuming the
   * particle has a virtuality \a particleScale.
   */
  inline double xfl(tcPPtr parton, Energy2 partonScale, double l,
		    Energy2 particleScale = 0.0*GeV2) const;

  /**
   * Return the density for the given \a parton, for a given \a
   * partonScale and momentum fraction \a x assuming the
   * particle has a virtuality \a particleScale.
   */
  inline double xfx(tcPPtr parton, Energy2 partonScale, double x,
		    double eps = 0.0, Energy2 particleScale = 0.0*GeV2) const;

  /**
   * Return the valence density for the given \a parton, for a given
   * \a partonScale and logarithmic momentum fraction \a l assuming
   * the particle has a virtuality \a particleScale.
   */
  inline double xfvl(tcPPtr parton, Energy2 partonScale, double l,
		     Energy2 particleScale = 0.0*GeV2) const;

  /**
   * Return the valence density for the given \a parton, for a given
   * \a partonScale and momentum fraction \a x assuming the particle
   * has a virtuality \a particleScale.
   */
  inline double xfvx(tcPPtr parton, Energy2 partonScale, double x,
		     double eps = 0.0, Energy2 particleScale = 0.0*GeV2) const;

  /**
   * Return the density for the given \a parton, for a given \a
   * partonScale and logarithmic momentum fraction \a l assuming the
   * particle has a virtuality \a particleScale.
   */
  inline double xfl(tcPDPtr parton, Energy2 partonScale, double l,
		    Energy2 particleScale = 0.0*GeV2) const;

  /**
   * Return the density for the given \a parton, for a given \a
   * partonScale and momentum fraction \a x assuming the
   * particle has a virtuality \a particleScale.
   */
  inline double xfx(tcPDPtr parton, Energy2 partonScale, double x,
		    double eps = 0.0, Energy2 particleScale = 0.0*GeV2) const;

  /**
   * Return the valence density for the given \a parton, for a given
   * \a partonScale and logarithmic momentum fraction \a l assuming
   * the particle has a virtuality \a particleScale.
   */
  inline double xfvl(tcPDPtr parton, Energy2 partonScale, double l,
		     Energy2 particleScale = 0.0*GeV2) const;

  /**
   * Return the valence density for the given \a parton, for a given
   * \a partonScale and momentum fraction \a x assuming the particle
   * has a virtuality \a particleScale.
   */
  inline double xfvx(tcPDPtr parton, Energy2 partonScale, double x,
		     double eps = 0.0, Energy2 particleScale = 0.0*GeV2) const;
  //@}

private:

  /**
   * The parton density object.
   */
  tcPDFPtr thePDF;

  /**
   * The particle for which the parton density is used.
   */
  tcPDPtr theParticle;

};

}

#include "PDF.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PDF.tcc"
#endif

#endif /* ThePEG_PDF_H */
