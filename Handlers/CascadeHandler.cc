// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the CascadeHandler class.
//

#include "CascadeHandler.h"
#include "ThePEG/Handlers/PartialCollisionHandler.h"
#include "ThePEG/Handlers/Hint.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/PDF/PartonExtractor.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "CascadeHandler.tcc"
#endif

using namespace ThePEG;

CascadeHandler::~CascadeHandler() {}

void CascadeHandler::
handle(PartialCollisionHandler & ch, const tPVector & tagged,
       const Hint & hint) {
  static tPVector notags;
  theLastXComb = ch.lastXCombPtr();
  theHint = &hint;
  //  if ( hint.tagged() )
    theTagged = &tagged;
    //  else
    //    theTagged = &notags;
    //
  if ( !lastXComb().empty() )
    thePDFs = make_pair(pdf(lastPartons().first), pdf(lastPartons().second));

  theCollisionHandler = &ch;

  cascade();

}

AbstractNoPIOClassDescription<CascadeHandler>
CascadeHandler::initCascadeHandler;

void CascadeHandler::Init() {}

