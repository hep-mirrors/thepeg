// -*- C++ -*-
//
// This is the implementation of the non-inlined templated member
// functions of the BaseRepository class.
//

namespace ThePEG {

template <typename T>
typename Ptr<T>::pointer BaseRepository::GetPtr(const T & t) {
  typedef typename Ptr<T>::pointer ptr;
  ObjectSet::iterator it = allObjects().find
    (IBPtr(const_cast<InterfacedBase *>((const InterfacedBase*)&t)));
  return it == allObjects().end()? ptr():
    dynamic_ptr_cast<ptr>(*it);
}

template <typename PtrType>
PtrType BaseRepository::GetPtr(string name) {
  return dynamic_ptr_cast<PtrType>(GetPointer(name));
}

template <typename PtrType>
PtrType BaseRepository::GetObject(string name) {
  typedef ClassTraits<typename PtrTraits<PtrType>::value_type> Traits;
  IBPtr ip = GetPointer(name);
  if ( !ip ) throw RepositoryNotFound(name);
  PtrType p = dynamic_ptr_cast<PtrType>(ip);
  if ( !p ) throw RepositoryClassMisMatch(*ip, Traits::className());
  return p;
}

template <typename T>
typename Ptr<T>::pointer BaseRepository::clone(const T & t) {
  typedef typename Ptr<T>::pointer ptr;
  const InterfacedBase & ib = t;
  ptr ret;
  try {
    ret = dynamic_ptr_cast<ptr>(ib.clone());
  }
  catch ( ... ) {
    throw BadClone(t);
  }
  if ( !ret ) throw BadClassClone(t);
  return ret;
}

template <typename T>
typename Ptr<T>::pointer BaseRepository::fullclone(const T & t) {
  typedef typename Ptr<T>::pointer ptr;
  ptr ret;
  try {
    ret = dynamic_ptr_cast<ptr>(t.fullclone());
  }
  catch ( ... ) {
    throw BadClone(t);
  }
  if ( !ret ) throw BadClassClone(t);
  return ret;
}

}
