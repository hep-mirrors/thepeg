// -*- C++ -*-
#ifndef ThePEG_NucleonFormFactor_H
#define ThePEG_NucleonFormFactor_H
//
// This is the declaration of the NucleonFormFactor class.
//

#include "ThePEG/Interface/Interfaced.h"
#include "NucleonFormFactor.fh"

namespace ThePEG {

/**
 * The documentation of the NucleonFormFactor class provides a base class for the implementation of nucleon form factors,
 * for use in the calculation of exclusive processes
 *
 * @see \ref NucleonFormFactorInterfaces "The interfaces"
 * defined for NucleonFormFactor.
 */
class NucleonFormFactor: public Interfaced {

public :

  /**
   *  Return the form factor
   * @param q2 the scale
   * @param nucleon The nucleon
   */
  virtual Complex formFactor(tcPDPtr nucleon, Energy2 q2) const = 0;

public:

  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

private:

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  NucleonFormFactor & operator=(const NucleonFormFactor &) = delete;

};

}

#endif /* ThePEG_NucleonFormFactor_H */
