// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PartonBin class.
//

#include "PartonBin.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDF/PDFBase.h"
#include "ThePEG/PDF/NoPDF.h"
#include "ThePEG/PDF/RemnantHandler.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Utilities/UtilityBase.h"
#include "ThePEG/Utilities/Math.h"
#include "ThePEG/Utilities/Timer.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartonBin.tcc"
#endif

using namespace ThePEG;

PartonBin::PartonBin() {
  reset();
}

PartonBin::
PartonBin(tcPDPtr p, tPBPtr inc, tcPDPtr pi,
	  tcPDFPtr pdf, const PDFCuts & newCuts)
  : theParticle(p), theIncomingBin(inc), theParton(pi), thePDF(pdf),
    theLastPartialL(0.0), theLastPartialX(-1.0), theLastPartialEps(-1.0),
    theLastL(0.0), thePDFDim(0), theRemDim(0), theLastJacobian(1.0),
    theRemnantInfo(0), info(0), theCuts(newCuts) {
  if ( pdf ) theRemnantHandler = pdf->remnantHandler();
  reset();
}

PartonBin::PartonBin(const PartonBin & x)
  : Base(x), theParticle(x.theParticle), theIncomingBin(x.theIncomingBin),
    theParton(x.theParton), thePDF(x.thePDF),
    theRemnantHandler(x.theRemnantHandler),
    theLastPartialL(x.theLastPartialL), theLastPartialX(x.theLastPartialX),
    theLastPartialEps(x.theLastPartialEps), theLastL(x.theLastL),
    thePDFDim(x.thePDFDim), theRemDim(x.theRemDim),
    theLastJacobian(x.theLastJacobian), theRemnantInfo(0),
    info(0), theCuts(x.theCuts) {}

PartonBin::~PartonBin() {
  if ( theRemnantInfo ) delete theRemnantInfo;
}

void PartonBin::reset(double l, Energy2 Q2) {
  theLastPartialL = theLastL = l;
  theLastPartialX = theLastPartialEps = -1.0;
  if ( info ) {
    info->lastParticle = PPtr();
    info->lastParton = PPtr();
    info->lastRemnants.clear();
    info->lastPartons.clear();
    info->lastScale = Q2;
    info->remnantWeight = 1.0;
  }
}

void PartonBin::resetRemnantMomenta(const LorentzMomentum & Pr) {
  Utilities::setMomentum(lastRemnants().begin(), lastRemnants().end(), Pr);
}

int PartonBin::nDim(bool doscale) {
  if ( !incoming() ) return 0;
  if ( dynamic_ptr_cast<Ptr<NoPDF>::tcp>(pdf()) ) thePDFDim = 0;
  else if ( doscale ) thePDFDim = 2;
  else thePDFDim = 1;
  theRemDim = remnantHandler()->nDim(*this, !doscale);
  return pdfDim() + remDim() + incoming()->nDim(true);
}

tPBPtr PartonBin::getFirst() {
  return incoming()? incoming()->getFirst(): tPBPtr(this);
}

void PartonBin::prepare() {
  lastPartialL(-1.0);
  theLastL = 0.0;
  if ( !incoming() ) return;
  theLastPartialL = -1.0;
  theLastL = -1.0;
  incoming()->prepare();
}

void PartonBin::generate(const double * r) {
  lastScale(0.0*GeV2);
  if ( !incoming() ) return;
  if ( lastPartialL() >= 0 ) return;
  lastPartialL(0.0);
  lastJacobian(1.0);
  remnantWeight(1.0);
  if ( pdfDim() )
    lastPartialL(pdf()->flattenL(particle(), parton(), cuts(),
				 *r++, theLastJacobian));
  if ( pdfDim() > 1 )
    lastScale(pdf()->flattenScale(particle(), parton(), cuts(), lastPartialL(),
				  *r++, theLastJacobian));
  incoming()->generate(r);
  lastL(lastPartialL() + incoming()->lastL());
}

double PartonBin::fullFn(Energy2 newScale) {
  if ( !incoming() ) return 1.0;
  if ( newScale > 0.0*GeV2 ) lastScale(newScale);
  return incoming()->fullFn() * theLastJacobian *
    pdf()->xfl(particle(), parton(), lastScale(), lastPartialL(),
	       incoming()->lastScale());
}
  
PartonBinInfo * PartonBin::createInfo() const {
  PartonBinInfo * i = new PartonBinInfo;
  if ( incoming() ) i->incoming = incoming()->createInfo();
  return i;
}

void PartonBin::setInfo(PartonBinInfo * i, tPPtr inc) {
  info = i;
  if ( incoming() ) incoming()->setInfo(i->incoming, inc);
  else lastParton(inc);
}

void PartonBin::persistentOutput(PersistentOStream & os) const {
  os << theParticle << theIncomingBin << theParton << thePDF
     << theRemnantHandler << theLastL << theLastPartialL << theLastPartialX
     << theLastPartialEps << thePDFDim << theRemDim << theLastJacobian
     << cuts().lMin() << cuts().lMax() << ounit(cuts().scaleMin(), GeV2)
     << ounit(cuts().scaleMax(), GeV2) << ounit(cuts().sMax(), GeV2);
}

void PartonBin::persistentInput(PersistentIStream & is, int) {
  double lmin = 0.0;
  double lmax = 0.0;
  Energy2 scmin = 0.0*GeV2;
  Energy2 scmax = 0.0*GeV2;
  Energy2 smax = 0.0*GeV2;
  is >> theParticle >> theIncomingBin >> theParton >> thePDF
     >> theRemnantHandler >> theLastL >> theLastPartialL >> theLastPartialX
     >> theLastPartialEps >> thePDFDim >> theRemDim >> theLastJacobian
     >> lmin >> lmax >> iunit(scmin, GeV2) >> iunit(scmax, GeV)
     >> iunit(smax, GeV2);
  theCuts = PDFCuts(Interval<double>(lmin, lmax),
		    SInterval(scmin, scmax), smax);

  info = 0;
  if ( theRemnantInfo ) delete theRemnantInfo;
  theRemnantInfo = 0;
}

ClassDescription<PartonBin> PartonBin::initPartonBin;

void PartonBin::Init() {}
