// non-inlined functions of Lorentz Spinor class
#include "LorentzSpinor.h"
#include "LorentzSpinorBar.h"
#include <iostream>
using std::cout; using std::endl;
namespace ThePEG {
  namespace Helicity {
    // return the barred spinor
    LorentzSpinorBar LorentzSpinor::bar()
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
      return LorentzSpinorBar(output[0],output[1],output[2],output[3]);
    }
  }
}
