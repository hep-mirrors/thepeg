// -*- C++ -*-
//
// ClassDescription.tcc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined templated member
// functions of the ClassDescriptionBase, ClassDescriptionTBase,
// ClassDescription, AbstractClassDescription, NoPIOClassDescription
// and AbstractNoPIOClassDescription, classes.
//

namespace ThePEG {

template <typename T, int IBase, typename B>
void ClassDescriptionHelper<T, IBase, B>::
addBases(vector<const ClassDescriptionBase *> & c) {
  //  const type_info & tid = typeid(B);
  const ClassDescriptionBase * b = DescriptionList::find(typeid(B));
  if ( !b ) return;
  c.push_back(b);
  ClassDescriptionHelper<T,IBase+1>::addBases(c);
}

template <typename T, int IBase>
void ClassDescriptionHelper<T, IBase, int>::
addBases(vector<const ClassDescriptionBase *> & ) {}

}
