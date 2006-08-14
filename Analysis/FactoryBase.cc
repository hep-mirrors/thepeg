// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FactoryBase class.
//

#include "FactoryBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Config/algorithm.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FactoryBase.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

FactoryBase::~FactoryBase() {}

void FactoryBase::clear() {
  //  if ( theHistogramFactory ) delete theHistogramFactory;
  //  if ( theTree ) delete theTree;
  if ( theAnalysisFactory ) delete theAnalysisFactory;
  theHistogramFactory = 0;
  theTree = 0;
  theAnalysisFactory = 0;
}

void FactoryBase::dofinish() {
  Interfaced::dofinish();
  for_each(clients, mem_fun(&InterfacedBase::finish));
  tree().commit();
  clear();
}

void FactoryBase::doinitrun() {
  Interfaced::doinitrun();
  string file = filename();
  if ( file == "" ) file = generator()->filename();
  file += "." + suffix();
  if ( file[0] != '/' ) file = generator()->path() + "/" + file;
  theTree = analysisFactory().createTreeFactory()->create
    (file, storeType(), false, true);
  theTree->setOverwrite(false);
  theHistogramFactory = analysisFactory().createHistogramFactory(tree());
}

void FactoryBase::persistentOutput(PersistentOStream & os) const {
  os << theFilename << theSuffix << theStoreType;
}

void FactoryBase::persistentInput(PersistentIStream & is, int) {
  clear();
  is >> theFilename >> theSuffix >> theStoreType;
}

AbstractClassDescription<FactoryBase>
FactoryBase::initFactoryBase;
// Definition of the static class description member.

void FactoryBase::Init() {

  static ClassDocumentation<FactoryBase> documentation
    ("There is no documentation for the FactoryBase class");


  static Parameter<FactoryBase,string> interfaceFilename
    ("Filename",
     "Together with <interface>Suffix</interface>, the name of the file "
     "where the resulting histograms will be stored. If empty, the run-name "
     "provided by the current EventGenerator will be used instead.",
     &FactoryBase::theFilename, "",
     true, false);

  static Parameter<FactoryBase,string> interfaceSuffix
    ("Suffix",
     "Together with <interface>Filename</interface>, the name of the file "
     "where the resulting histograms will be stored.",
     &FactoryBase::theSuffix, "aida",
     true, false);

  static Parameter<FactoryBase,string> interfaceStoreType
    ("StoreType",
     "The format in which the histograms are stored in the output file. "
     "The allowed values depend on the actual AIDA implementation used.",
     &FactoryBase::theStoreType, "xml",
     true, false);

}

