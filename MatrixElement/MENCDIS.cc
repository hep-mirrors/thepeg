// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MENCDIS class.
//

#include "MENCDIS.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/Utilities/Timer.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/StandardModel/StandardModelBase.h"
#include "ThePEG/Handlers/StandardXComb.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MENCDIS.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

MENCDIS::MENCDIS()
  : mZ2(0.0*GeV2) {}

MENCDIS::MENCDIS(const MENCDIS & x)
  : ME2to2QCD(x), mZ2(x.mZ2) {}

MENCDIS::~MENCDIS() {}

unsigned int MENCDIS::orderInAlphaS() const {
  return 0;
}

unsigned int MENCDIS::orderInAlphaEW() const {
  return 2;
}

void MENCDIS::getDiagrams() const {
  tcPDPtr gamma = getParticleData(ParticleID::gamma);
  tcPDPtr Z0 = getParticleData(ParticleID::Z0);
  tcPDPtr ep = getParticleData(ParticleID::eplus);
  tcPDPtr em = getParticleData(ParticleID::eminus);
  for ( int i = -maxFlavour(); i <= maxFlavour(); ++i ) {
    if ( !i ) continue;
    tcPDPtr q = getParticleData(i);
    add(new_ptr((Tree2toNDiagram(3), q, gamma, em, 1, q, 2, em, -1)));
    add(new_ptr((Tree2toNDiagram(3), q, Z0, em, 1, q, 2, em, -2)));
    add(new_ptr((Tree2toNDiagram(3), q, gamma, ep, 1, q, 2, ep, -1)));
    add(new_ptr((Tree2toNDiagram(3), q, Z0, ep, 1, q, 2, ep, -2)));
  }
}

Energy2 MENCDIS::scale() const {
  return -tHat();
}

double MENCDIS::me2() const {

  return 0.0;

}

Selector<MENCDIS::DiagramIndex>
MENCDIS::diagrams(const DiagramVector & diags) const {
  if ( lastXCombPtr() ) {
    lastG = meInfo()[0];
    lastZ = meInfo()[1];
  }
  Selector<DiagramIndex> sel;
  for ( DiagramIndex i = 0; i < diags.size(); ++i ) {
    if ( diags[i]->id() == -1 ) sel.insert(lastG, i);
    else if ( diags[i]->id() == -2 ) sel.insert(lastZ, i);
  }
  return sel;
}

Selector<const ColourLines *>
MENCDIS::colourGeometries(tcDiagPtr diag) const {

  static ColourLines c("1 4");
  static ColourLines cb("-1 -4");

  Selector<const ColourLines *> sel;
  if ( diag->partons()[0]->id() > 0 )
    sel.insert(1.0, &c);
  else
    sel.insert(1.0, &cb);
  return sel;
}

IBPtr MENCDIS::clone() const {
  return new_ptr(*this);
}

IBPtr MENCDIS::fullclone() const {
  return new_ptr(*this);
}

void MENCDIS::doinit() throw(InitException) {
  ME2to2QCD::doinit();
}

void MENCDIS::persistentOutput(PersistentOStream & os) const {
  os << ounit(mZ2, GeV2) << lastG << lastZ;
}

void MENCDIS::persistentInput(PersistentIStream & is, int) {
  is >> iunit(mZ2, GeV2) >> lastG >> lastZ;
}

ClassDescription<MENCDIS> MENCDIS::initMENCDIS;

void MENCDIS::Init() {

  static ClassDocumentation<MENCDIS> documentation
    ("The ThePEG::MENCDIS class implements the full"
     "\\f$e^\\pm q \\rightarrow e^\\pm q\\f$ "
     "matrix element including the interference terms.");

}
