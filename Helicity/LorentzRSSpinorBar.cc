
// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LorentzRSSpinorBar class.
//
// Author: Peter Richardson
//

#include "LorentzRSSpinorBar.h"
#include "LorentzRSSpinor.h"

using namespace ThePEG;
using namespace Helicity;

// return the unbarred spinor
LorentzRSSpinor LorentzRSSpinorBar::bar()
{
  Complex out[4][4]; unsigned int ix;
  switch(_dirac)
    {
      // Haber lower energy
    case HaberDRep:
      for(ix=0;ix<4;++ix)
	{
	  out[ix][0] = conj(_spin[ix][0]);
	  out[ix][1] = conj(_spin[ix][1]);
	  out[ix][2] =-conj(_spin[ix][2]);
	  out[ix][3] =-conj(_spin[ix][3]);
	}
      break;
    case HELASDRep:
      // HELAS
      for(ix=0;ix<4;++ix)
	{
	  out[ix][0] = conj(_spin[ix][2]);
	  out[ix][1] = conj(_spin[ix][3]);
	  out[ix][2] = conj(_spin[ix][0]);
	  out[ix][3] = conj(_spin[ix][1]);
	}
      break;
    }
  return LorentzRSSpinor(out[0][0],out[0][1],out[0][2],out[0][3],
			 out[1][0],out[1][1],out[1][2],out[1][3],
			 out[2][0],out[2][1],out[2][2],out[2][3],
			 out[3][0],out[3][1],out[3][2],out[3][3],_type,_dirac);
}
