// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MEQQ2qq class.
//

#include "MEQQ2qq.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/EnumParticles.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEQQ2qq.tcc"
#endif

using namespace ThePEG;

MEQQ2qq::~MEQQ2qq() {}

void MEQQ2qq::getDiagrams() const {
  tcPDPtr g = getParticleData(ParticleID::g);
  for ( int i = 1; i <= maxFlavour(); ++i ) {
    tcPDPtr q = getParticleData(i);
    tcPDPtr qb = q->CC();
    for ( int j = 1; j <= maxFlavour(); ++j ) {
      if ( i == j ) continue;
      tcPDPtr qp = getParticleData(j);
      tcPDPtr qbp = qp->CC();
      add(new_ptr((Tree2toNDiagram(2), q, qb, 1, g, 3, qp, 3, qbp, -1)));
    }
  }
}

double MEQQ2qq::me2() const {
  return comfac()*colA()*KfacA()*2.0/9.0;
}

Selector<const ColourLines *>
MEQQ2qq::colourGeometries(tcDiagPtr diag) const {
  Selector<const ColourLines *> sel;

  static ColourLines csST("1 3 4, -5 -3 -2");

  sel.insert(1.0, &csST);
  return sel;
}

Selector<MEQQ2qq::DiagramIndex>
MEQQ2qq::diagrams(const DiagramVector & diags) const {
  Selector<DiagramIndex> sel;
  for ( DiagramIndex i = 0; i < diags.size(); ++i ) 
    if ( diags[i]->id() == -1 ) sel.insert(1.0, i);
  return sel;
}

NoPIOClassDescription<MEQQ2qq> MEQQ2qq::initMEQQ2qq;
// Definition of the static class description member.

void MEQQ2qq::Init() {

  static ClassDocumentation<MEQQ2qq> documentation
    ("The \\classname{MEQQ2qq} class describes the standard QCD "
     "$q + \\bar{q} \\rightarrow q' + \\bar{q}'$ matrix element.");
}

