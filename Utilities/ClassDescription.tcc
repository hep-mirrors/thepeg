// -*- C++ -*-
//
// This is the implementation of the non-inlined templated member
// functions of the ClassDescriptionBase, ClassDescriptionTBase,
// ClassDescription, AbstractClassDescription, NoPIOClassDescription
// and AbstractNoPIOClassDescription, classes.
//

namespace ThePEG {

template <class T, int IBase, class B>
void ClassDescriptionHelper<T, IBase, B>::
addBases(vector<const ClassDescriptionBase *> & c) {
  const type_info & tid = typeid(B);
  const ClassDescriptionBase * b = DescriptionList::find(tid);
  if ( !b ) return;
  c.push_back(b);
  ClassDescriptionHelper<T,IBase+1>::addBases(c);
}

template <class T, int IBase>
void ClassDescriptionHelper<T, IBase, int>::
addBases(vector<const ClassDescriptionBase *> & c) {}

}
