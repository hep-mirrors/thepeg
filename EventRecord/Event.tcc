// -*- C++ -*-
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
