// -*- C++ -*-
#ifndef THEPEG_TmpTransform_H
#define THEPEG_TmpTransform_H
//
// This is the declaration of the TmpTransform class.
//

#include "ThePEG/Config/ThePEG.h"

namespace ThePEG {

/**
 * This is a wrapper class to be used to temporarily make a Lorentz
 * transform of an object. When created a pointer to an object and a
 * LorentzRotation is provided, and the objects transform(const
 * LorentzRotation &) function is called. When the destructed the
 * inverse tansformation is performed. In this way one can make sure
 * that the inverse transformation is performed even if the function
 * where the TmpTransform is created returns or throws an exception.
 */
template <typename Ptr>
class TmpTransform {

public:


  /**
   * The contructor will call the transform(const LorentzRotation &)
   * of an object pointed to by \a p with \a r as argument.
   */
  inline TmpTransform(Ptr p, const LorentzRotation & r);

  /**
   * The destructor performs the inverse of the transformation done in
   * the constructor.
   */
  inline ~TmpTransform();

private:

  /**
   * A pointer to the object being transformed.
   */
  Ptr ptr;

  /**
   * The rotation performed in the constructor.
   */
  LorentzRotation rot;

private:

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  TmpTransform & operator=(const TmpTransform &);

  /**
   * The default constructor is private and must never be called.
   * In fact, it should not even be implemented.
   */
  TmpTransform();

  /**
   * The copy constructor is private and must never be called.
   * In fact, it should not even be implemented.
   */
  TmpTransform(const TmpTransform &);

};

}

#include "TmpTransform.icc"

#endif /* THEPEG_TmpTransform_H */
