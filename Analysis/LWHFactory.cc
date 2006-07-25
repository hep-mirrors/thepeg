// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LWHFactory class.
//

#include "LWHFactory.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#ifndef LWH 
#define ThePEGLWH
#endif
#include "AnalysisFactory.h"


using namespace ThePEG;

LWHFactory::~LWHFactory() {}

void LWHFactory::doinitrun() {
  analysisFactory(new LWH::AnalysisFactory);
  FactoryBase::doinitrun();
}

void LWHFactory::persistentOutput(PersistentOStream & os) const {}

void LWHFactory::persistentInput(PersistentIStream & is, int) {}

ClassDescription<LWHFactory> LWHFactory::initLWHFactory;
// Definition of the static class description member.

void LWHFactory::Init() {

  static ClassDocumentation<LWHFactory> documentation
    ("This class represents the Light-Weight Histogram package which "
     "implements the most rudimentary histogramming facilities according "
     "to the <a href=\"http://aida.freehep.org\">AIDA</a> interface "
     "specifications. Currently the only thing that is supported is "
     "simple, equally binned, one dimensional histograms. If you are "
     "using AnalysisHandlers which accesses other features in the AIDA "
     "interface you may end up with an ungraceful crash.");

}
