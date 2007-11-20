// -*- C++ -*-
//
// PersistentIStream.tcc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
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
