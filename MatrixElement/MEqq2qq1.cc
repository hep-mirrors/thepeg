// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MEqq2qq class.
//

#include "MEqq2qq1.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/EnumParticles.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEqq2qq.tcc"
#endif

using namespace ThePEG;

MEqq2qq::~MEqq2qq() {}

void MEqq2qq::getDiagrams() const {
  tcPDPtr g = getParticleData(ParticleID::g);
  for ( int i = 1; i <= maxFlavour(); ++i ) {
    tcPDPtr q = getParticleData(i);
    tcPDPtr qb = q->CC();
    add(new_ptr((Tree2toNDiagram(3), q, g, qb, 1, q, 2, qb, -1)));
    add(new_ptr((Tree2toNDiagram(2), q, qb, 1, g, 3, q, 3, qb, -2)));
  }
}

double MEqq2qq::me2() const {
  return comfac()*(colA()*Kfac() + colB()*KfacA())*2.0/9.0;
}

Selector<const ColourLines *>
MEqq2qq::colourGeometries(tcDiagPtr diag) const {

  static ColourLines ctST("1 -2 -3, -5 2 4");
  static ColourLines csST("1 3 4, -5 -3 -2");

  Selector<const ColourLines *> sel;
  if ( diag->id() == -1 )
    sel.insert(1.0, &ctST);
  else
    sel.insert(1.0, &csST);
  return sel;
}

Selector<MEqq2qq::DiagramIndex>
MEqq2qq::diagrams(const DiagramVector & diags) const {
  Selector<DiagramIndex> sel;
  for ( DiagramIndex i = 0; i < diags.size(); ++i ) 
    if ( diags[i]->id() == -1 )
      sel.insert(colB(), i);
    else if ( diags[i]->id() == -2 )
      sel.insert(colA(), i);
  return sel;
}

NoPIOClassDescription<MEqq2qq> MEqq2qq::initMEqq2qq;
// Definition of the static class description member.

void MEqq2qq::Init() {

  static ClassDocumentation<MEqq2qq> documentation
    ("The ThePEG::MEqq2qq class describes the standard QCD "
     "\\f$q\\bar{q} \\rightarrow q\\bar{q}\\f$ matrix element.");
}
