// -*- C++ -*-
#ifndef ThePEG_HoldFlag_H
#define ThePEG_HoldFlag_H
// This is the declaration of the HoldFlag class.

// #include "ThePEG/Config/ThePEG.h"
// #include "HoldFlag.fh"
// #include "HoldFlag.xh"

namespace ThePEG {

template <typename T = bool>
/**
 * <code>HoldFlag</code> objects are used to temporarily change the value
 * of an object, restoring the original value when the
 * <code>HoldFlag</code> object is destructed.
 *
 * @see Level
 */
class HoldFlag {

public:

  /**
   * Constructor setting the a temporary value for the given object.
   * @param newFlag the object which value is temporarily changed.
   * @param holdFlag the temporary value for the newFlag object.
   */
  inline HoldFlag(T & newFlag, const T & holdFlag);

  /**
   * Constructor setting the a temporary value for the given object.
   * @param newFlag the object which value is temporarily changed.
   * @param holdFlag the temporary value for the newFlag object.
   * @param finalFlag the newFlag object will be given the value
   * finalFlag when the HoldFlag object is destroyed.
   */
  inline HoldFlag(T & newFlag, const T & holdFlag, const T & finalFlag);

  /**
   * Destructor. Restores the corresponding object to its original
   * value.
   */
  inline ~HoldFlag();

private:

  /**
   * The object to be changed.
   */
  T & theFlag;

  /**
   * The value which will be restored when this is destroyed.
   */
  T oldFlag;

  /**
   * Default constructor is private and not implemented.
   */
  inline HoldFlag();

  /**
   * Copy constructor is private and not implemented.
   */
  inline HoldFlag(const HoldFlag &);

  /**
   * Assignment is private and not implemented.
   */
  inline HoldFlag & operator=(const HoldFlag &);

};

/**
 * Specialization of HoldFlag for boolean variables.
 */
template <>
class HoldFlag<bool> {

public:

  /**
   * Constructor setting the a temporary value for the bool variable.
   * @param newFlag the boolean variable which value is temporarily changed.
   * @param holdFlag the temporary value for the newFlag variable.
   */
  inline HoldFlag(bool & newFlag, bool holdFlag = true);

  /**
   * Constructor setting the a temporary value for the bool variable.
   * @param newFlag the boolean variable which value is temporarily changed.
   * @param holdFlag the temporary value for the newFlag variable.
   * @param finalFlag the newFlag variable will be given the value
   * finalFlag when the HoldFlag object is destroyed.
   */
  inline HoldFlag(bool & newFlag, bool holdFlag, bool finalFlag);

  /**
   * Destructor. Restores the corresponding variable to its original
   * value.
   */
  inline ~HoldFlag();

private:

  /**
   * The variable to be changed.
   */
  bool & theFlag;

  /**
   * The value which will be restored when this is destroyed.
   */
  bool oldFlag;

  /**
   * Default constructor is private and not implemented.
   */
  inline HoldFlag();

  /**
   * Copy constructor is private and not implemented.
   */
  inline HoldFlag(const HoldFlag &);

  /**
   * Assignment is private and not implemented.
   */
  inline HoldFlag & operator=(const HoldFlag &);

};

}

#include "HoldFlag.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HoldFlag.tcc"
#endif

#endif /* ThePEG_HoldFlag_H */
