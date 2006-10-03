// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PDFBase class.
//

#include "PDFBase.h"
#include "ThePEG/PDF/RemnantHandler.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Repository/Repository.h"
#include "ThePEG/Utilities/EnumIO.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PDFBase.tcc"
#endif

using namespace ThePEG;

PDFBase::PDFBase()
  : rangeException(rangeZero) {}

PDFBase::PDFBase(const PDFBase & x)
  : HandlerBase(x), theRemnantHandler(x.theRemnantHandler),
    rangeException(x.rangeException) {}

PDFBase::~PDFBase() {}

bool PDFBase::canHandle(tcPDPtr particle) const {
  return canHandleParticle(particle) && remnantHandler() &&
    remnantHandler()->canHandle(particle, partons(particle));
}

double PDFBase::
xfx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale, double x,
    double eps, Energy2 particleScale) const {
  using Math::log1m;
  return xfl(particle, parton, partonScale,
	     (x < 0.5 || eps <= 0.0)? -log(x): -log1m(eps), particleScale);
}

double PDFBase::
xfl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale, double l,
    Energy2 particleScale) const {
  using Math::exp1m;
  return xfx(particle, parton, partonScale, exp(-l), exp1m(-l), particleScale);
}

double PDFBase::
xfvx(tcPDPtr, tcPDPtr, Energy2, double,
     double, Energy2) const {
  return 0.0;
}

double PDFBase::
xfvl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale, double l,
     Energy2 particleScale) const {
  using Math::exp1m;
  return xfvx(particle, parton, partonScale, exp(-l), exp1m(-l), particleScale);
}

double PDFBase::flattenL(tcPDPtr, tcPDPtr, const PDFCuts & c,
			 double z, double & jacobian) const {
  jacobian = c.lMax() - c.lMin();
  return c.lMin() + z*jacobian;
}

Energy2 PDFBase::
flattenScale(tcPDPtr, tcPDPtr, const PDFCuts & c,
	     double l, double z, Energy2 & jacobian) const {
  if ( c.scaleMin()  > 0.0*GeV ) {
    double r = c.scaleMaxL(l)/c.scaleMin();
    jacobian = c.scaleMin()*log(r)*pow(r, z);
    return c.scaleMin()*pow(r, z);
  } else {
    jacobian = c.scaleMaxL(l);
    return z*jacobian;
  }
}

void PDFBase::doinit() throw(InitException) {
  HandlerBase::doinit();
}

void PDFBase::persistentOutput(PersistentOStream & os) const {
  os << theRemnantHandler << oenum(rangeException);
}

void PDFBase::persistentInput(PersistentIStream & is, int) {
  is >> theRemnantHandler >> ienum(rangeException);
}

AbstractClassDescription<PDFBase> PDFBase::initPDFBase;

void PDFBase::Init() {

  static ClassDocumentation<PDFBase> documentation
    ("There is no documentation for the ThePEG::PDFBase class");

  static Reference<PDFBase,RemnantHandler> interfaceRemnantHandler
    ("RemnantHandler",
     "A remnant handler capable of generating remnants for the partons "
     "which can be extracted with this PDF.",
     &PDFBase::theRemnantHandler, false, false, true, false);

  static Switch<PDFBase,RangeException> interfaceRangeException
    ("RangeException",
     "How to handle cases when momentum fractions or scales are "
     "outside of limits. Note that this switch may be ignored in sub-classes.",
     &PDFBase::rangeException, rangeZero, true, false);
  static SwitchOption interfaceRangeExceptionFreeze
    (interfaceRangeException,
     "Freeze", "Values are frozen outside the given ranges.", rangeFreeze);
  static SwitchOption interfaceRangeExceptionZero
    (interfaceRangeException,
     "Zero", "Values are zero outside the given ranges.", rangeZero);
  static SwitchOption interfaceRangeExceptionThrow
    (interfaceRangeException,
     "Throw", "An exception is thrown outside the given ranges.", rangeThrow);

}

RemnantHandlerCantHandle::RemnantHandlerCantHandle(string pdf, string rh) {
  theMessage << "Cannot assign '" << rh << "' as remnant handler for the "
	     << "parton density object '" << pdf
	     << "' because the remnant handler does not feel up to the job.";
  severity(warning);
}

PDFWrongParticle::PDFWrongParticle(string p, string pdf, string mess) {
  theMessage << "Cannot assign particle '" << p << "' to be handled by the "
	     << "parton density object '" << pdf << "'. " << mess;
  severity(warning);
}

PDFRange::PDFRange(string pdf, string var, double val, double lim) {
  theMessage << "In parton density function '" << pdf << "': the value of "
	     << var << ", " << val << ", was out of range (" << lim
	     << ").";
  severity(eventerror);
}

 

