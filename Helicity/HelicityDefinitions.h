// -*- C++ -*-
#ifndef THEPEG_HelicityDefinitions_H
#define THEPEG_HelicityDefinitions_H
// This is the declaration of the HelicityDefinitions class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Exception.h"

/** \file HelicityDefinitions.h
 *
 * This file contains enumerations used by LorentzSpinor and
 * LorentzSpinorBar classes.
 *
 * @see LorentzSpinor
 *
 * @author Peter Richardson
 */

namespace ThePEG {

/**
 * The Helicity namespace contains classes for spin representation
 * classes in ThePEG.
 */
namespace Helicity {

/**
 * Enumeration to choose between spinor representations.
 */
enum DiracRep {
  HELASDRep, /**< The representation used in HELAS. */
  HaberDRep, /**< The representation used by Haber. */
  defaultDRep = HELASDRep /**< THe default choice is HELAS. */
};

/**
 * Enumeration to specify spinor type.
 */
enum SpinorType {
  u_spinortype, /**< u spinor. */
  v_spinortype, /**< v spinor. */
  unknown_spinortype /**< Undefined spinor type. */
};

/** Exception class used by Helicity classes to signal a logical error. */
class HelicityLogicalError: public Exception {};

/** Exception class used by Helicity classes to signal a inconsistencies. */
class HelicityConsistencyError: public Exception {};

}
}

#endif /* THEPEG_HelicityDefinitions_H */
