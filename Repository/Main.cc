// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Main class.
//

#include "Main.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Main.tcc"
#endif


using namespace ThePEG;

Main::~Main() {}

AbstractNoPIOClassDescription<Main> Main::initMain;
// Definition of the static class description member.

EGPtr Main::theEventGenerator;

long Main::theN = 0;

vector<string> Main::theArguments;

void Main::Init() {}

