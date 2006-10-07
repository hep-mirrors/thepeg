// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RemnantData class.
//

#include "RemnantData.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantData.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

RemnantData::
RemnantData(tcPDPtr particle, RemDecPtr)
  : ParticleData(*particle), parentPD(particle) {}

RemnantData::~RemnantData() {}

bool RemnantData::extract(tcPDPtr parton) {
  if ( !parton ) return false;
  extracted.insert(parton);
  iCharge(PDT::Charge(iCharge() - parton->iCharge()));
  return fixColour();
}

bool RemnantData::
reextract(tcPDPtr oldp, tcPDPtr newp) {
  multiset<tcPDPtr>::iterator it = extracted.find(oldp);
  if ( it == extracted.end() ) return false;
  extracted.erase(it);
  extracted.insert(newp);
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
  os << parentPD << extracted;
}

void RemnantData::persistentInput(PersistentIStream & is, int) {
  is >> parentPD >> extracted;
}

ClassDescription<RemnantData> RemnantData::initRemnantData;
// Definition of the static class description member.

void RemnantData::Init() {

  static ClassDocumentation<RemnantData> documentation
    ("There is no documentation for the RemnantData class");

}

