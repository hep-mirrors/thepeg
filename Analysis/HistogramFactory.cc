// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the HistogramFactory class.
//

#include "HistogramFactory.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Repository/EventGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HistogramFactory.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

HistogramFactory::~HistogramFactory() {}

void HistogramFactory::clear() {
  if ( theHistogramFactory ) delete theHistogramFactory;
  if ( theTree ) delete theTree;
  if ( theAnalysisFactory ) delete theAnalysisFactory;
  theHistogramFactory = 0;
  theTree = 0;
  theAnalysisFactory = 0;
}

void HistogramFactory::dofinish() {
  Interfaced::dofinish();
  tree->commit();
  clear();
}

void HistogramFactory::doinitrun() {
  Interfaced::doinitrun();
  string file = filename();
  if ( file == "" ) file = generator()->filename();
  file += "." + suffix();
  if ( file[0] != "/" ) file = generator()->path() + "/" + file;
  theTree = analysisFactory().createTreeFactory()->create
    (file, storeType(), false, true);
  theHistogramFactory = analysisFactory().createHistogramFactory(tree());
}

void HistogramFactory::persistentOutput(PersistentOStream & os) const {
  os << theFilename << theSuffix << theStoreType;
}

void HistogramFactory::persistentInput(PersistentIStream & is, int) {
  clear();
  is >> theFilename >> theSuffix >> theStoreType;
}

AbstractClassDescription<HistogramFactory>
HistogramFactory::initHistogramFactory;
// Definition of the static class description member.

void HistogramFactory::Init() {

  static ClassDocumentation<HistogramFactory> documentation
    ("There is no documentation for the HistogramFactory class");


  static Parameter<HistogramFactory,string> interfaceFilename
    ("Filename",
     "Together with <interface>Suffix</interface>, the name of the file "
     "where the resulting histograms will be stored. If empty, the run-name "
     "provided by the current EventGenerator will be used instead.",
     &HistogramFactory::theFilename, "",
     true, false);

  static Parameter<HistogramFactory,string> interfaceSuffix
    ("Suffix",
     "Together with <interface>Filename</interface>, the name of the file "
     "where the resulting histograms will be stored.",
     &HistogramFactory::theSuffix, "aida",
     true, false);

  static Parameter<HistogramFactory,string> interfaceStoreType
    ("StoreType",
     "The format in which the histograms are stored in the output file. "
     "The allowed values depend on the actual AIDA implementation used.",
     &HistogramFactory::theStoreType, "xml",
     true, false);

}

