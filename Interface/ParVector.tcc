// -*- C++ -*-
//
// This is the implementation of the non-inlined templated member
// functions of the ParVector and ParVectorTBase classes.
//

#include "ParVector.xh"

namespace ThePEG {

template <typename Type>
string ParVectorTBase<Type>::type() const {
  if ( std::numeric_limits<Type>::is_integer ) return "Vi";
  if ( typeid(Type) == typeid(string) ) return "Vs";
  return "Vf";
}

template <typename Type>
string ParVectorTBase<Type>::doxygenType() const {
  ostringstream os;
  if ( size() <= 0 ) os << "Varying size ";
  else os << "Fixed size (" << size() << ") ";
  os << "vector of ";
  string lim = "";
  if ( !limited() ) lim = " unlimited";
  if ( std::numeric_limits<Type>::is_integer ) os << lim << "integer ";
  else if ( typeid(Type) == typeid(string) ) os << "string ";
  else os << lim;
  os << "parameters";
  return os.str();
}

template <typename Type>
void ParVectorTBase<Type>::setDef(InterfacedBase & i, int place) const
  throw(InterfaceException) {
  if ( place >= 0 ) tset(i, tdef(i, place), place);
  int sz = get(i).size();
  for ( int j = 0; j < sz; ++j ) tset(i, tdef(i, j), j);
}

template <typename Type>
void ParVectorTBase<Type>::
set(InterfacedBase & i, string newValue, int place) const
  throw(InterfaceException) {
  istringstream is(newValue);
  if ( unit() > Type() ) {
    double t;
    is >> t;
    tset(i, Type(t*unit()), place);
  } else {
    Type t;
    is >> t;
    tset(i, t, place);
  }
}

template <typename Type>
void ParVectorTBase<Type>::
insert(InterfacedBase & i, string newValue, int place) const
  throw(InterfaceException) {
  istringstream is(newValue);
  if ( unit() > Type() ) {
    double t;
    is >> t;
    tinsert(i, Type(t*unit()), place);
  } else {
    Type t;
    is >> t;
    tinsert(i, t, place);
  }
}

template <typename Type>
typename ParVectorTBase<Type>::StringVector ParVectorTBase<Type>::
get(const InterfacedBase & i) const throw(InterfaceException) {
  TypeVector tres = tget(i);
  StringVector res;
  for ( typename TypeVector::iterator it = tres.begin();
	it != tres.end(); ++it ) {
    ostringstream os;
    if ( unit() > Type() )
      os << *it/unit();
    else
      os << *it;
    res.push_back(os.str());
  }
  return res;
}

template <typename Type>
string ParVectorTBase<Type>::
minimum(const InterfacedBase & i, int place) const throw(InterfaceException) {
  ostringstream os;
  if ( unit() > Type() )
    os << tminimum(i, place)/unit();
  else
    os << tminimum(i, place);
  return os.str();
}

template <typename Type>
string ParVectorTBase<Type>::
maximum(const InterfacedBase & i, int place) const throw(InterfaceException) {
  ostringstream os;
  if ( unit() > Type() )
    os << tmaximum(i, place)/unit();
  else
    os << tmaximum(i, place);
  return os.str();
}


template <typename Type>
string ParVectorTBase<Type>::
def(const InterfacedBase & i, int place) const throw(InterfaceException) {
  ostringstream os;
  if ( unit() > Type() )
    os << tdef(i, place)/unit();
  else
    os << tdef(i, place);
  return os.str();
}


template <typename T, typename Type>
void ParVector<T,Type>::tset(InterfacedBase & i, Type newValue, int place) const
  throw(InterfaceException) {
  if ( InterfaceBase::readOnly() ) throw InterExReadOnly(*this, i);
  T * t = dynamic_cast<T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  if ( ( ParVectorBase::lowerLimit() && newValue < tminimum(*t, place) ) ||
       ( ParVectorBase::upperLimit() && newValue > tmaximum(*t, place) ) )
    throw ParVExLimit(*this, i, newValue);
  TypeVector oldVector = tget(i);
  if ( theSetFn ) {
    try { (t->*theSetFn)(newValue, place); }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw ParVExUnknown(*this, i, newValue, place, "set"); }
  } else {
    if ( !theMember ) throw InterExSetup(*this, i);
    if ( place < 0 || unsigned(place) >= (t->*theMember).size() )
      throw ParVExIndex(*this, i, place);
    (t->*theMember)[place] = newValue;
  }
  if ( !InterfaceBase::dependencySafe() && oldVector != tget(i) ) i.touch();
}

template <typename T, typename Type>
void ParVector<T,Type>::
tinsert(InterfacedBase & i, Type newValue, int place) const
  throw(InterfaceException) {
  if ( InterfaceBase::readOnly() ) throw InterExReadOnly(*this, i);
  if ( ParVectorBase::size() > 0 ) throw ParVExFixed(*this, i);
  T * t = dynamic_cast<T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  if ( ( ParVectorBase::lowerLimit() && newValue < tminimum(*t, place) ) ||
       ( ParVectorBase::upperLimit() && newValue > tmaximum(*t, place) ) )
    throw ParVExLimit(*this, i, newValue);
  TypeVector oldVector = tget(i);
  if ( theInsFn ) {
    try { (t->*theInsFn)(newValue, place); }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw ParVExUnknown(*this, i, newValue, place, "insert"); }
  } else {
    if ( !theMember ) throw InterExSetup(*this, i);
    if ( place < 0 || unsigned(place) > (t->*theMember).size() )
      throw ParVExIndex(*this, i, place);
    (t->*theMember).insert((t->*theMember).begin()+place, newValue);
  }
  if ( !InterfaceBase::dependencySafe() && oldVector != tget(i) ) i.touch();
}

template <typename T, typename Type>
void ParVector<T,Type>::
erase(InterfacedBase & i, int place) const throw(InterfaceException) {
  if ( InterfaceBase::readOnly() ) throw InterExReadOnly(*this, i);
  if ( ParVectorBase::size() > 0 ) throw ParVExFixed(*this, i);
  T * t = dynamic_cast<T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  TypeVector oldVector = tget(i);
  if ( theDelFn ) {
    try { (t->*theDelFn)(place); }
    catch (InterfaceException) { throw; }
    catch ( ... ) {  throw ParVExDelUnknown(*this, i, place); }
  } else {
    if ( !theMember ) throw InterExSetup(*this, i);
    if ( place < 0 || unsigned(place) >= (t->*theMember).size() )
      throw ParVExIndex(*this, i, place);
    (t->*theMember).erase((t->*theMember).begin()+place);
  }
  if ( !InterfaceBase::dependencySafe() && oldVector != tget(i) ) i.touch();
}

template <typename T, typename Type>
typename ParVector<T,Type>::TypeVector ParVector<T,Type>::
tget(const InterfacedBase & i) const throw(InterfaceException) {
  const T * t = dynamic_cast<const T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  if ( theGetFn ) {
    try { return (t->*theGetFn)(); }
    catch (InterfaceException) { throw; }
    catch ( ... ) { throw ParVExGetUnknown(*this, i, "current"); }
  }
  if ( theMember ) return t->*theMember;
  throw InterExSetup(*this, i);
}

template <typename T, typename Type>
typename ParVector<T,Type>::StringVector ParVector<T,Type>::
get(const InterfacedBase & i) const throw(InterfaceException) {
  if ( !theStringGetFn ) return ParVectorTBase<Type>::get(i);
  const T * t = dynamic_cast<const T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  try { return (t->*theStringGetFn)(); }
  catch (InterfaceException) { throw; }
  catch ( ... ) { throw ParVExGetUnknown(*this, i, "current"); }
}


template <typename T, typename Type>
Type ParVector<T,Type>::tdef(const InterfacedBase & i, int place) const
  throw(InterfaceException) {
  if ( place < 0 || !theDefFn ) return theMin;
  const T * t = dynamic_cast<const T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  try { return (t->*theDefFn)(place); }
  catch (InterfaceException) { throw; }
  catch ( ... ) { throw ParVExGetUnknown(*this, i, "default"); }
}

template <typename T, typename Type>
Type ParVector<T,Type>::tminimum(const InterfacedBase & i, int place) const
  throw(InterfaceException) {
  if ( place < 0 || !theMinFn ) return theMin;
  const T * t = dynamic_cast<const T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  try { return (t->*theMinFn)(place); }
  catch (InterfaceException) { throw; }
  catch ( ... ) { throw ParVExGetUnknown(*this, i, "minimum"); }
}

template <typename T, typename Type>
Type ParVector<T,Type>::tmaximum(const InterfacedBase & i, int place) const
  throw(InterfaceException) {
  if ( place < 0 || !theMaxFn ) return theMax;
  const T * t = dynamic_cast<const T *>(&i);
  if ( !t ) throw InterExClass(*this, i);
  try { return (t->*theMaxFn)(place); }
  catch (InterfaceException) { throw; }
  catch ( ... ) { throw ParVExGetUnknown(*this, i, "maximum"); }
}

template <typename T, typename Type>
void ParVector<T,Type>::doxygenDescription(ostream & os) const {
  ParVectorTBase<Type>::doxygenDescription(os);
  os << "<b>Default value:</b> ";
  putUnit(os, theDef);
  if ( theDefFn ) os << " (May be changed by member function.)";
  if ( ParVectorBase::lowerLimit() ) {
    os << "<br>\n<b>Minimum value:</b> ";
    putUnit(os, theMin);
    if ( theMinFn ) os << " (May be changed by member function.)";
  }
  if ( ParVectorBase::upperLimit() ) {
    os << "<br>\n<b>Maximum value:</b> ";
    putUnit(os, theMax);
    if ( theMaxFn ) os << " (May be changed by member function.)";
  }
  os << "<br>\n";
}

template <typename T>
ParVExLimit::ParVExLimit(const InterfaceBase & i,
			 const InterfacedBase & o, T v) {
  theMessage << "Could not set/insert " << v << " in the parameter vector \""
	     << i.name() << "\" for the object \"" << o.name()
	     << "\" because the value is outside the specified limits.";
  severity(warning);
}

template <typename T>
ParVExUnknown::ParVExUnknown(const InterfaceBase & i, const InterfacedBase & o,
			     T v, int j, const char * s) {
  theMessage << "Could not " << s << " the value " << v << " at position "
	     << j << " in the parameter vector \"" << i.name()
	     << "\" for the object \"" << o.name() << "\" because the "
	     << s << " function threw an unknown exception.";
  severity(maybeabort);
}

}
