// -*- C++ -*-
//
// This is the implementation of the non-inlined templated member
// functions of the Reference class.
//

namespace ThePEG {

template <class T, class R>
void Reference<T,R>::set(InterfacedBase & i, IBPtr newRef, bool chk) const
  throw(InterfaceException) {
  if ( readOnly() ) throw InterExReadOnly(*this, i);
  T * t = dynamic_cast<T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  if ( noNull() && !newRef ) throw InterExNoNull(*this, i);
  RefPtr r = dynamic_ptr_cast<RefPtr>(newRef);
  if ( !r && newRef) throw RefExSetRefClass(*this, i, newRef);
  RefPtr oldRef = dynamic_ptr_cast<RefPtr>(get(i));
  if ( theSetFn && ( chk || !theMember ) ) {
    try { (t->*theSetFn)(r); }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw RefExSetUnknown(*this, i, r); }
  } else {
    if ( theMember ) t->*theMember = r;
    else throw InterExSetup(*this, i);
  }
  if ( !InterfaceBase::dependencySafe() && oldRef != get(i) ) i.touch();  
}

template <class T, class R>
IBPtr Reference<T,R>::get(const InterfacedBase & i) const
  throw(InterfaceException) {
  const T * t = dynamic_cast<const T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  if ( theGetFn ) {
    try { return (t->*theGetFn)(); }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw RefExGetUnknown(*this, i); }
  }
  if ( theMember ) return t->*theMember;
  throw InterExSetup(*this, i);
}

template <class T, class R>
bool Reference<T,R>::check(const InterfacedBase & i, cIBPtr ir) const
  throw(InterfaceException) {
  const T * t = dynamic_cast<const T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  if ( noNull() && !ir ) return false;
  cRefPtr r = dynamic_ptr_cast<cRefPtr>(ir);
  if ( !r && ir ) return false;
  if ( !theCheckFn ) return true;
  return (t->*theCheckFn)(r);
}

}

