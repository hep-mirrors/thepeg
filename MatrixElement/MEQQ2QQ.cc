// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MEQQ2QQ class.
//

#include "MEQQ2QQ.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/EnumParticles.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEQQ2QQ.tcc"
#endif

using namespace ThePEG;

MEQQ2QQ::~MEQQ2QQ() {}

void MEQQ2QQ::getDiagrams() const {
  tcPDPtr g = getParticleData(ParticleID::g);
  for ( int i = 1; i <= maxFlavour(); ++i ) {
    tcPDPtr q = getParticleData(i);
    tcPDPtr qb = q->CC();
    add(new_ptr((Tree2toNDiagram(3), q, g, q, 1, q, 2, q, -1)));
    add(new_ptr((Tree2toNDiagram(3), q, g, q, 2, q, 1, q, -2)));
    add(new_ptr((Tree2toNDiagram(3), qb, g, qb, 1, qb, 2, qb, -3)));
    add(new_ptr((Tree2toNDiagram(3), qb, g, qb, 2, qb, 1, qb, -4)));
  }
}

double MEQQ2QQ::me2() const {
  return comfac()*(colA() + colB())*KfacA()/9.0;
}

Selector<const ColourLines *>
MEQQ2QQ::colourGeometries(tcDiagPtr diag) const {

  static ColourLines ctTU("1 -2 5, 2 3 4");
  static ColourLines ctUT("-4 -3 -2, -5 2 -1");
  static ColourLines cuTU("1 -2 4, 2 3 5");
  static ColourLines cuUT("-5 -3 -2, -4 2 -1");

  Selector<const ColourLines *> sel;
  if ( diag->id() == -1 )
    sel.insert(1.0, &ctTU);
  else if ( diag->id() == -2)
    sel.insert(1.0, &cuTU);
  else if ( diag->id() == -3 )
    sel.insert(1.0, &ctUT);
  else if ( diag->id() == -4)
    sel.insert(1.0, &cuUT);
  return sel;
}

Selector<MEQQ2QQ::DiagramIndex>
MEQQ2QQ::diagrams(const DiagramVector & diags) const {
  Selector<DiagramIndex> sel;
  for ( DiagramIndex i = 0; i < diags.size(); ++i ) 
    if ( diags[i]->id() == -1 ||  diags[i]->id() == -3 )
      sel.insert(colA(), i);
    else if ( diags[i]->id() == -2 ||  diags[i]->id() == -4 )
      sel.insert(colB(), i);
  return sel;
}

NoPIOClassDescription<MEQQ2QQ> MEQQ2QQ::initMEQQ2QQ;
// Definition of the static class description member.

void MEQQ2QQ::Init() {

  static ClassDocumentation<MEQQ2QQ> documentation
    ("The \\classname{MEQQ2QQ} class describes the standard QCD "
     "$q + q \\rightarrow q + q$ matrix element.");
}

