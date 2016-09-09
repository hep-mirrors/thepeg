// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the BlobMEBase class.
//

#include "BlobMEBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"

using namespace ThePEG;

BlobMEBase::BlobMEBase() {}

BlobMEBase::~BlobMEBase() {}


#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/MatrixElement/BlobDiagram.h"

void BlobMEBase::getDiagrams() const {
  map<tcPDPair,tcPDVector> proc = processes();
  int id = 1;
  for ( auto it = proc.begin(); it != proc.end(); ++it, ++id ) {
    BlobDiagram diag(id,it->first.first,it->first.second);
    for ( auto pit = it->second.begin(); pit != it->second.end(); ++pit )
      diag.operator,(*pit);
    add(new_ptr(diag));
  }
}

Selector<MEBase::DiagramIndex>
BlobMEBase::diagrams(const DiagramVector & diags) const {
  assert(diags.size()==1);
  Selector<DiagramIndex> sel;
  sel.insert(1.0, 0);
  return sel;
}

Selector<const ColourLines *>
BlobMEBase::colourGeometries(tcDiagPtr) const {
  map<size_t,size_t> connections =
    colourConnections();
  ostringstream clines;
  for ( auto it = connections.begin(); it != connections.end(); ++it ) {
    int cid = it->first+1; int acid = -(it->second+1);
    if ( it->first < 2 ) cid = -cid;
    if ( it->second < 2 ) acid = -acid;
    clines << cid << " " << acid;
    auto nit = it; ++nit;
    if ( nit != connections.end() )
      clines << ",";
  }
  theColourLines.reset(clines.str());
  Selector<const ColourLines *> sel;
  sel.insert(1.0,&theColourLines);
  return sel;
}

CrossSection BlobMEBase::dSigHatDR() const {
  if ( !lastXCombPtr()->willPassCuts() )
    return ZERO;
  return
    (sqr(hbarc)/(2.*lastSHat())) *
    jacobian() * me2();
}

AbstractNoPIOClassDescription<BlobMEBase> BlobMEBase::initBlobMEBase;

void BlobMEBase::Init() {

  static ClassDocumentation<BlobMEBase> documentation
    ("BlobMEBase is the base class for matrix elements producing blobs.");

}

