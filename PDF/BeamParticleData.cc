// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the BeamParticleData class.
//

#include "BeamParticleData.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/Reference.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "BeamParticleData.tcc"
#endif

using namespace ThePEG;

BeamParticleData::BeamParticleData(long newId, string newPDGName)
  : ParticleData(newId, newPDGName) {}


PDPtr BeamParticleData::
Create(long newId, string newPDGName) {
  return new_ptr(BeamParticleData(newId, newPDGName));
}

PDPair BeamParticleData::
Create(long newId, string newPDGName, string newAntiPDGName) {
  PDPair pap;
  pap.first = new_ptr(BeamParticleData(newId, newPDGName));
  pap.second = new_ptr(BeamParticleData(-newId, newAntiPDGName));
  antiSetup(pap);
  return pap;
}

BeamParticleData::~BeamParticleData() {}

PDPtr BeamParticleData::pdclone() const {
  return new_ptr(*this);
}

void BeamParticleData::persistentOutput(PersistentOStream & os) const {
  os << thePDF;
}

void BeamParticleData::persistentInput(PersistentIStream & is, int) {
  is >> thePDF;
}

ClassDescription<BeamParticleData> BeamParticleData::initBeamParticleData;

void BeamParticleData::setPDF(PDFPtr pdf) {
  if ( pdf && !pdf->canHandle(tcPDPtr((const ParticleData *)this)) )
    throw BeamParticleWrongPDF(name(), pdf? pdf->name(): string("<NULL>"));
  thePDF = pdf;
}

void BeamParticleData::Init() {

  static Reference<BeamParticleData,PDFBase> interfacePDF
    ("PDF",
     "The parton densities for this beam particle.",
     &BeamParticleData::thePDF, false, false, true, true,
     &BeamParticleData::setPDF, 0, 0);

}

BeamParticleWrongPDF::BeamParticleWrongPDF(string p, string pdf) {
  theMessage << "The parton density object '" << pdf << "' cannot be used to "
	     << "handle densities of particle '" << p << "'. (Possibly due to "
	     << "the remnant handler assigned to the parton density.)";
  severity(warning);
}
