// -*- C++ -*-
#ifndef ThePEG_DipoleFormFactor_H
#define ThePEG_DipoleFormFactor_H
//
// This is the declaration of the DipoleFormFactor class.
//

#include "NucleonFormFactor.h"
#include "ThePEG/Utilities/Maths.h"

namespace ThePEG {

/**
 * Here is the documentation of the DipoleFormFactor class.
 *
 * @see \ref DipoleFormFactorInterfaces "The interfaces"
 * defined for DipoleFormFactor.
 */
class DipoleFormFactor: public NucleonFormFactor {

public:

  /**
   * The default constructor.
   */
  DipoleFormFactor() : q02_(0.71*GeV2)
  {}

  /**
   *  Return the form factor
   * @param q2 the scale
   */
  Complex formFactor(tcPDPtr , Energy2 q2) const {
    return Math::powi((1 + q2/q02_),-2);
  }

public:

  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(PersistentOStream & os) const;

  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(PersistentIStream & is, int version);
  //@}

  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const;
  //@}

private:

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  DipoleFormFactor & operator=(const DipoleFormFactor &) = delete;

private:

  /**
   *  Fitted scale \f$Q{_0}{^2}=0.71GeV^2\f$ for the dipole form factor
   */
  Energy2 q02_;
  
};

}

#endif /* ThePEG_DipoleFormFactor_H */
