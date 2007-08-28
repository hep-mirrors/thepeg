// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Main class.
//

#include "Main.h"

using namespace ThePEG;

AbstractNoPIOClassDescription<Main> Main::initMain;
// Definition of the static class description member.

EGPtr Main::theEventGenerator;

long Main::theN = 0;

vector<string> Main::theArguments;

