// -*- C++ -*-
//
// This is the implementation of the non-inlined templated member
// functions of the Command class.
//

namespace ThePEG {

template <class T>
string Command<T>::cmd(InterfacedBase & i, string arg) const
  throw(InterfaceException) {
  T * t = dynamic_cast<T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  if ( theExeFn ) {
    try {
      string r = (t->*theExeFn)(arg);
      if ( r != "" ) i.touch();
      return r;
    }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw CmdExUnknown(*this, i, arg); }
  } else throw InterExSetup(*this, i);
}

}
