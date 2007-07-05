// -*- C++ -*-
#ifndef ThePEG_LorentzPolarizationVector_H
#define ThePEG_LorentzPolarizationVector_H
// This is the declaration of the LorentzPolarizationVector class.

#include "ThePEG/Config/Unitsystem.h"
#include "ThePEG/Config/Complex.h"
#include "ThePEG/Vectors/LorentzVector.h"

namespace ThePEG {
  namespace Helicity {
    typedef LorentzVector<complex<double> > LorentzPolarizationVector;
    typedef LorentzVector<complex<Energy> > LorentzPolarizationVectorE;
  }
}
#endif
