// -*- C++ -*-
//
// This is the implementation of the templated member functions of
// the Collision class.
//

namespace ThePEG {

template <class OutputIterator>
void Collision::select(OutputIterator r, const SelectorBase & s) const {
  if ( s.allSteps() ) {
    if ( incoming().first && s.intermediate() && s.check(*incoming().first) )
      *r++ = incoming().first;
    if ( incoming().first && s.intermediate() && s.check(*incoming().second) )
      *r++ = incoming().second;
    for ( StepVector::const_iterator it = theSteps.begin();
	  it != theSteps.end(); ++it ) (**it).select(r, s);
  } else {
    if ( incoming().first && s.intermediate() &&
	 s.check(*incoming().first) && steps().size() < 2 )
      *r++ = incoming().first;
    if (incoming().first && s.intermediate() &&
	s.check(*incoming().second) && steps().size() < 2 )
      *r++ = incoming().second;
    finalStep()->select(r, s);
  }
}

template <class Iterator>
void Collision::addParticles(Iterator first, Iterator last) {
  allParticles.insert(first, last);
  if ( event() ) event()->addParticles(first, last);
}

}
