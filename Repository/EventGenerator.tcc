// -*- C++ -*-
//
// This is the implementation of the non-inlined templated member
// functions of the EventGenerator class.
//

namespace ThePEG {

template <typename T>
typename Ptr<T>::pointer EventGenerator::getPtr(const T & t) const {
  typedef typename Ptr<T>::pointer ptr;
  ObjectSet::const_iterator it = objects().find(ptr_cast_const<IBPtr>(&t));
  return it == objects().end()? ptr(): dynamic_ptr_cast<ptr>(*it);
}

template <typename T>
typename Ptr<T>::pointer EventGenerator::getDefault() const {
  typedef typename Ptr<T>::pointer ptr;
  ptr ret;
  for ( vector<IPtr>::const_iterator it = defaultObjects().begin();
	it != defaultObjects().end(); ++it ) {
    ret = dynamic_ptr_cast<ptr>(*it);
    if ( ret ) return ret;
  }
  if ( strategy() ) {
    for ( vector<IPtr>::const_iterator it =
	    strategy()->defaultObjects().begin();
	  it != strategy()->defaultObjects().end(); ++it ) {
      ret = dynamic_ptr_cast<ptr>(*it);
      if ( ret ) return ret;
    }
  } 
  return ret;
}

}
