// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LorentzSpinorBar class.
//
// Author: Peter Richardson
//

#include "LorentzSpinorBar.h"
#include "LorentzSpinor.h"
#include "HelicityDefinitions.h"

using namespace ThePEG;
using namespace Helicity;

// return the unbarred spinor
LorentzSpinor LorentzSpinorBar::bar()
{
  complex<double> output[4];
  switch(ThePEG::Helicity::HelicityDefinitions::getDirac())
    {
      // Haber lower energy
    case 1:
      output[0] = conj(_spin[0]);
      output[1] = conj(_spin[1]);
      output[2] =-conj(_spin[2]);
      output[3] =-conj(_spin[3]);
      break;
    case 2:
      // HELAS
      output[0] = conj(_spin[2]);
      output[1] = conj(_spin[3]);
      output[2] = conj(_spin[0]);
      output[3] = conj(_spin[1]);
      break;
    }
  return LorentzSpinor(output[0],output[1],output[2],output[3]);
}


