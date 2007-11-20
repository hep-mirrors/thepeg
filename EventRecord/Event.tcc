// -*- C++ -*-
//
// Event.tcc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the templated member functions of
// the Event class.
//

namespace ThePEG {

template <class OutputIterator>
void Event::select(OutputIterator r, const SelectorBase & s) const {
  if ( s.allCollisions() ) {
    for ( CollisionVector::const_iterator it = theCollisions.begin();
	  it != theCollisions.end(); ++it ) (**it).select(r, s);
  } else {
    primaryCollision()->select(r, s);
  }
}

}
