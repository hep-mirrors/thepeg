// -*- C++ -*-
#ifndef ThePEG_PDF_H
#define ThePEG_PDF_H
//
// This is the declaration of the <!id>PDF<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/PDF/PartonBin.h"
// #include "PDF.fh"
// #include "PDF.xh"

namespace ThePEG {

class PDF {

public:

  inline PDF();
  inline PDF(const PDF &);
  inline PDF(tcPBPtr);
  inline ~PDF();
  // Standard ctors and dtor.

  inline PDF & operator=(const PDF &);
  //  Assignment operator.

public:

  inline double xfl(tcPPtr parton, Energy2 partonScale, double l,
		    Energy2 particleScale = 0.0*GeV2) const;

  inline double xfx(tcPPtr parton, Energy2 partonScale, double x,
		    double eps = 0.0, Energy2 particleScale = 0.0*GeV2) const;

  inline double xfvl(tcPPtr parton, Energy2 partonScale, double l,
		     Energy2 particleScale = 0.0*GeV2) const;

  inline double xfvx(tcPPtr parton, Energy2 partonScale, double x,
		     double eps = 0.0, Energy2 particleScale = 0.0*GeV2) const;

  inline double xfl(tcPDPtr parton, Energy2 partonScale, double l,
		    Energy2 particleScale = 0.0*GeV2) const;

  inline double xfx(tcPDPtr parton, Energy2 partonScale, double x,
		    double eps = 0.0, Energy2 particleScale = 0.0*GeV2) const;

  inline double xfvl(tcPDPtr parton, Energy2 partonScale, double l,
		     Energy2 particleScale = 0.0*GeV2) const;

  inline double xfvx(tcPDPtr parton, Energy2 partonScale, double x,
		     double eps = 0.0, Energy2 particleScale = 0.0*GeV2) const;

private:

  tcPDFPtr thePDF;
  // The parton density object.

  tcPDPtr theParticle;
  // The particle for which the parton density is used.

};

}

#include "PDF.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PDF.tcc"
#endif

#endif /* ThePEG_PDF_H */
