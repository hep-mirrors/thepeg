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

string BlobMEBase::ColourConnection::write(size_t& sourceCount) const {
  assert(members.size() >= 2);
  string res;
  for ( auto it = members.begin(); it != members.end(); ++it )
    res += std::to_string(*it) + " ";
  if ( members.size() > 2 || 
       ( members.size() == 2 && members[0]*members[1] > 0 ) ) {
    res += ": " + std::to_string(sourceCount);
    ++sourceCount;
  }
  return res;
}

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
BlobMEBase::colourGeometries(tcDiagPtr diag) const {
  auto connections = colourConnections();
  ostringstream clines;
  size_t sourceCount = diag->partons().size();
  for ( auto it = connections.begin(); it != connections.end(); ++it ) {
    clines << it->write(sourceCount);
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

