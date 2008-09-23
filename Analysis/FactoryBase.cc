// -*- C++ -*-
//
// FactoryBase.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FactoryBase class.
//

#include "FactoryBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Config/algorithm.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

FactoryBase::FactoryBase()
  : theFilename(""), theSuffix("aida"), theStoreType("xml"),
    theAnalysisFactory(0), theTree(0), theHistogramFactory(0),
    theDataSetFactory(0) {}

FactoryBase::FactoryBase(const FactoryBase & x)
  : Interfaced(x), theFilename(x.theFilename), theSuffix(x.theSuffix),
    theStoreType(x.theStoreType), theAnalysisFactory(0), theTree(0),
    theHistogramFactory(0), theDataSetFactory(0) {}

FactoryBase::~FactoryBase() {}

FactoryBase::DataFiller::~DataFiller() {
  int N = v.size()/(3*dset->dimension());
  for ( int i = 0; i < N; ++i ) {
    AIDA::IDataPoint * p = dset->addPoint();
    for ( int j = 0; j < p->dimension(); ++j ) {
      p->coordinate(j)->setValue(v.front());
      v.pop_front();
      p->coordinate(j)->setErrorPlus(v.front());
      v.pop_front();
      p->coordinate(j)->setErrorMinus(v.front());
      v.pop_front();
    }
  }
}


void FactoryBase::clear() {
  if ( theTree ) delete theTree;
  if ( theAnalysisFactory ) delete theAnalysisFactory;
  theHistogramFactory = 0;
  theDataSetFactory = 0;
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
  theDataSetFactory = analysisFactory().createDataPointSetFactory(tree());
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

