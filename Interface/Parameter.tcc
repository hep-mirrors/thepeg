// -*- C++ -*-
//
// This is the implementation of the non-inlined templated member
// functions of the Parameter and ParameterTBase classes.
//

namespace ThePEG {

template <typename Type>
string ParameterTBase<Type>::type() const {
  if ( std::numeric_limits<Type>::is_integer ) return "Pi";
  if ( typeid(Type) == typeid(string) ) return "Ps";
  return "Pf";
}

template <typename Type>
void ParameterTBase<Type>::
set(InterfacedBase & i, string newValue) const throw(InterfaceException) {
  istringstream is(newValue);
  if ( unit() > Type() ) {
    double t;
    is >> t;
    tset(i, Type(t*unit()));
  } else {
    Type t;
    is >> t;
    tset(i, t);
  }
}

template <typename Type>
string ParameterTBase<Type>::
get(const InterfacedBase & i) const throw(InterfaceException) {
  ostringstream os;
  putUnit(os, tget(i));
  return os.str();
}

template <typename Type>
string ParameterTBase<Type>::
minimum(const InterfacedBase & i) const throw(InterfaceException) {
  ostringstream os;
  putUnit(os, tminimum(i));
  return os.str();
}

template <typename Type>
string ParameterTBase<Type>::
maximum(const InterfacedBase & i) const throw(InterfaceException) {
  ostringstream os;
  putUnit(os, tmaximum(i));
  return os.str();
}
    
template <typename Type>
string ParameterTBase<Type>::
def(const InterfacedBase & i) const throw(InterfaceException) {
  ostringstream os;
  putUnit(os, tdef(i));
  return os.str();
}

template <typename T, typename Type>
void Parameter<T,Type>::tset(InterfacedBase & i, Type newValue) const
  throw(InterfaceException) {
  if ( readOnly() ) throw InterExReadOnly(*this, i);
  T * t = dynamic_cast<T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  if ( limited() && ( newValue < tminimum(i) || newValue > tmaximum(i) ) )
    throw ParExSetLimit(*this, i, newValue);
  Type oldValue = tget(i);
  if ( theSetFn ) {
    try { (t->*theSetFn)(newValue); }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw ParExSetUnknown(*this, i, newValue); }
  } else {
    if ( theMember ) t->*theMember = newValue;
    else throw InterExSetup(*this, i);
  }
  if ( !dependencySafe() && oldValue != tget(i)) i.touch();
}

template <typename T, typename Type>
Type Parameter<T,Type>::tget(const InterfacedBase & i) const throw(InterfaceException) {
  const T * t = dynamic_cast<const T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  if ( theGetFn ) {
    try { return (t->*theGetFn)(); }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw ParExGetUnknown(*this, i, "current"); }
  }
  if ( theMember ) return t->*theMember;
  else throw InterExSetup(*this, i);
}

template <typename T, typename Type>
Type Parameter<T,Type>::tminimum(const InterfacedBase & i) const
  throw(InterfaceException) {
  if ( theMinFn ) {
    const T * t = dynamic_cast<const T *>(&i);
    if ( !t ) throw InterExClass(*this, i);
    try { return max(theMin, (t->*theMinFn)()); }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw ParExGetUnknown(*this, i, "minimum"); }
  }
  return theMin;
}

template <typename T, typename Type>
Type Parameter<T,Type>::tmaximum(const InterfacedBase & i) const
  throw(InterfaceException) {
  if ( theMaxFn ) {
    const T * t = dynamic_cast<const T *>(&i);
    if ( !t ) throw InterExClass(*this, i);
    try { return min(theMax, (t->*theMaxFn)()); }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw ParExGetUnknown(*this, i, "maximum"); }
  }
  return theMax;
}

template <typename T, typename Type>
Type Parameter<T,Type>::tdef(const InterfacedBase & i) const
  throw(InterfaceException) {
  if ( theDefFn ) {
    const T * t = dynamic_cast<const T *>(&i);
    if ( !t ) throw InterExClass(*this, i);
    try { return (t->*theDefFn)(); }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw ParExGetUnknown(*this, i, "default"); }
  }
  return theDef;
}

template <typename T>
ParExSetLimit::ParExSetLimit(const InterfaceBase & i,
			     const InterfacedBase & o, T v) {
  theMessage << "Could not set the parameter \"" << i.name()
	     << "\" for the object \"" << o.name() << "\" to " << v
	     << " because the value is outside the specified limits.";
  severity(warning);
}

template <typename T>
ParExSetUnknown::ParExSetUnknown(const InterfaceBase & i,
				 const InterfacedBase & o, T v) {
  theMessage << "Could not set the parameter \"" << i.name()
	     << "\" for the object \"" << o.name() << "\" to " << v
	     << " because the set function threw an unknown exception.";
  severity(maybeabort);
}

}

