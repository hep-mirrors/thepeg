// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FlavourGenerator class.
//

#include "FlavourGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FlavourGenerator.tcc"
#endif

using namespace ThePEG;

FlavourGenerator::~FlavourGenerator() {}

void FlavourGenerator::splitHadron(tcPDPtr hadron, cPDPtr & quark,
				   cPDPtr & rest) const {}

AbstractNoPIOClassDescription<FlavourGenerator>
 FlavourGenerator::initFlavourGenerator;

void FlavourGenerator::Init() {}

