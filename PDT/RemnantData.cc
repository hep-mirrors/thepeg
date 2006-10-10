// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RemnantData class.
//

#include "RemnantData.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/RemnantDecayer.h"
#include "ThePEG/PDT/DecayMode.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantData.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

RemnantData::
RemnantData(tcPDPtr particle, RemDecPtr dec)
  : ParticleData(particle->id(), "Remnant (" + particle->PDGName() + ")"),
    parentPD(particle), decayer(dec) {
  synchronized(false);
  width(0.0*GeV);
  widthCut(0.0*GeV);
  iCharge(particle->iCharge());
  iSpin(particle->iSpin());
  iColour(particle->iColour());
  stable(false);
  DMPtr dm = new_ptr(DecayMode());
  dm->parent(const_ptr_cast<tPDPtr>(particle));
  dm->brat();
  dm->decayer(dec);
  dm->switchOn();
  addDecayMode(dm);
  fixColour();
}

RemnantData::~RemnantData() {}

bool RemnantData::extract(tcPDPtr parton) {
  if ( !parton ) return false;
  multiset<tcPDPtr> newextr = extracted;
  newextr.insert(parton);
  if ( !decayer->canHandle(parentPD, extracted) ) return false;
  extracted.swap(newextr);
  iCharge(PDT::Charge(iCharge() - parton->iCharge()));
  return fixColour();
}

bool RemnantData::
reextract(tcPDPtr oldp, tcPDPtr newp) {
  multiset<tcPDPtr> newextr = extracted;
  multiset<tcPDPtr>::iterator it = newextr.find(oldp);
  if ( it == newextr.end() ) return false;
  newextr.erase(it);
  newextr.insert(newp);
  if ( !decayer->canHandle(parentPD, extracted) ) return false;
  extracted.swap(newextr);
  iCharge(PDT::Charge(iCharge() + oldp->iCharge() - newp->iCharge()));
  return fixColour();
}

bool RemnantData::fixColour() {
  bool col = parentPD->hasAntiColour();
  bool acol = parentPD->hasColour();
  for ( multiset<tcPDPtr>::const_iterator it = extracted.begin();
	it != extracted.end(); ++it ) {
    if ( (**it).hasColour() ) col = true;
    if ( (**it).hasAntiColour() ) acol = true;
  }
  if ( col )
    iColour(acol? PDT::Colour8: PDT::Colour3bar);
  else
    iColour(acol? PDT::Colour3: PDT::Colour0);

  return true;
}

void RemnantData::persistentOutput(PersistentOStream & os) const {
  os << parentPD << decayer << extracted;
}

void RemnantData::persistentInput(PersistentIStream & is, int) {
  is >> parentPD >> decayer >> extracted;
}

ClassDescription<RemnantData> RemnantData::initRemnantData;
// Definition of the static class description member.

void RemnantData::Init() {

  static ClassDocumentation<RemnantData> documentation
    ("There is no documentation for the RemnantData class");

}

