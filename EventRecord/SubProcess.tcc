// -*- C++ -*-
//
// This is the implementation of the non-inlined templated member
// functions of the SubProcess class.
//

namespace ThePEG {

template <class InputIterator>
void SubProcess::setIntermediates(InputIterator first, InputIterator last) {
  theIntermediates = ParticleVector(first, last);
}

template <class InputIterator>
void SubProcess::setOutgoing(InputIterator first, InputIterator last) {
  theOutgoing = ParticleVector(first, last);
}

}
