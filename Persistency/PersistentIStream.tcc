// -*- C++ -*-
//
// This is the implementation of the non-inlined templated member
// functions of the PersistentIStream class.
//

namespace ThePEG {

template <typename Container>
void PersistentIStream::getContainer(Container & c) {
  long size;
  typename Container::value_type val;
  c.clear();
  *this >> size;
  while ( size-- && good() ) {
    *this >> val;
    c.insert(c.end(), val);
  }
}

}
