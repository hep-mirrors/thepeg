// -*- C++ -*-
#ifndef ThePEG_Rebinder_H
#define ThePEG_Rebinder_H

#include "ThePEG/Config/ThePEG.h"
#include "Rebinder.fh"
#include <stdexcept>
// #include "Rebinder.xh"

namespace ThePEG {

template <class T>
class Rebinder {

public:

  ThePEG_DECLARE_TEMPLATE_POINTERS(T,TPtr);
  typedef map<cTPtr,TPtr> MapType;
  typedef typename MapType::const_iterator const_iterator;

public:

  inline Rebinder();

public:

  inline TPtr & operator[](tcTPtr);

  template <typename R>
  inline R translate(const R &) const;

  template <typename OutputIterator, typename InputIterator>
  inline void translate(OutputIterator, InputIterator, InputIterator) const;

  template <typename R>
  inline R alwaysTranslate(const R &) const throw(std::runtime_error);

  template <typename OutputIterator, typename InputIterator>
  inline void alwaysTranslate(OutputIterator, InputIterator, InputIterator)
    const throw(std::runtime_error);

  inline const MapType & map() const;

private:

  MapType theMap;

private:

  inline Rebinder(const Rebinder &);

  inline Rebinder & operator=(const Rebinder &);

};


}

#include "Rebinder.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Rebinder.tcc"
#endif

#endif /* ThePEG_Rebinder_H */
