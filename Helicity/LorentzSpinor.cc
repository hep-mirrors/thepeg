// non-inlined functions of Lorentz Spinor class
// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LorentzSpinor class.
//
// Author: Peter Richardson
//

#include "LorentzSpinor.h"
#include "LorentzSpinorBar.h"

using namespace ThePEG;
using namespace Helicity;

// return the barred spinor
LorentzSpinorBar LorentzSpinor::bar()
{
  complex<double> output[4];
  switch(_dirac)
    {
      // Haber lower energy
    case HaberDRep:
      output[0] = conj(_spin[0]);
      output[1] = conj(_spin[1]);
      output[2] =-conj(_spin[2]);
      output[3] =-conj(_spin[3]);
      break;
    case HELASDRep:
      // HELAS
      output[0] = conj(_spin[2]);
      output[1] = conj(_spin[3]);
      output[2] = conj(_spin[0]);
      output[3] = conj(_spin[1]);
      break;
    }
  return LorentzSpinorBar(output[0],output[1],output[2],output[3],_type,_dirac);
}

// boost the spinor
LorentzSpinor & LorentzSpinor::boost(double bx,double by,double bz)
{
  // work out beta and chi
  double beta=sqrt(bx*bx+by*by+bz*bz);
  double chi = atanh(beta);
  double sinhchi = sinh(0.5*chi)/beta, coshchi = cosh(0.5*chi);
  // calculate the new spinor
  Complex out[4],ii(0.,1.);
  Complex nxminy=bx-ii*by;
  Complex nxpiny=bx+ii*by;
  switch(_dirac)
    {
      // Haber lower energy
    case HaberDRep:
      out[0] = coshchi*_spin[0]+sinhchi*( bz*_spin[2]+nxminy*_spin[3]);
      out[1] = coshchi*_spin[1]+sinhchi*(-bz*_spin[3]+nxpiny*_spin[2]);
      out[2] = coshchi*_spin[2]+sinhchi*( bz*_spin[0]+nxminy*_spin[1]);
      out[3] = coshchi*_spin[3]+sinhchi*(-bz*_spin[1]+nxpiny*_spin[0]);
      break;
      // HELAS
    case HELASDRep:
      out[0] = coshchi*_spin[0]+sinhchi*(-bz*_spin[0]-nxminy*_spin[1]);
      out[1] = coshchi*_spin[1]+sinhchi*(+bz*_spin[1]-nxpiny*_spin[0]);
      out[2] = coshchi*_spin[2]+sinhchi*(+bz*_spin[2]+nxminy*_spin[3]);
      out[3] = coshchi*_spin[3]+sinhchi*(-bz*_spin[3]+nxpiny*_spin[2]);
      break;
    }
  for(unsigned int ix=0;ix<4;++ix){_spin[ix]=out[ix];}
  return *this;
}

// boost the spinor
LorentzSpinor & LorentzSpinor::boost(const Hep3Vector & boostv)
{
  double beta = boostv.mag();
  double bx=boostv.x(),by=boostv.y(),bz=boostv.z();
  double chi = atanh(beta);
  double sinhchi = sinh(0.5*chi)/beta, coshchi = cosh(0.5*chi);
  Complex out[4],ii(0.,1.);
  Complex nxminy=bx-ii*by;
  Complex nxpiny=bx+ii*by;
  switch(_dirac)
    {
      // Haber lower energy
    case HaberDRep:
      out[0] = coshchi*_spin[0]+sinhchi*(+bz*_spin[2]+nxminy*_spin[3]);
      out[1] = coshchi*_spin[1]+sinhchi*(-bz*_spin[3]+nxpiny*_spin[2]);
      out[2] = coshchi*_spin[2]+sinhchi*(+bz*_spin[0]+nxminy*_spin[1]);
      out[3] = coshchi*_spin[3]+sinhchi*(-bz*_spin[1]+nxpiny*_spin[0]);
      break;
      // HELAS
    case HELASDRep:
      out[0] = coshchi*_spin[0]+sinhchi*(-bz*_spin[0]-nxminy*_spin[1]);
      out[1] = coshchi*_spin[1]+sinhchi*(+bz*_spin[1]-nxpiny*_spin[0]);
      out[2] = coshchi*_spin[2]+sinhchi*(+bz*_spin[2]+nxminy*_spin[3]);
      out[3] = coshchi*_spin[3]+sinhchi*(-bz*_spin[3]+nxpiny*_spin[2]);
      break;
    }
  for(unsigned int ix=0;ix<4;++ix){_spin[ix]=out[ix];}
  return *this;
}

// general transform
LorentzSpinor & LorentzSpinor::transform(const SpinHalfLorentzRotation & r)
{
  unsigned int ix,iy;
  if(Rep()==defaultDRep)
    {
      Complex out[4];
      for(ix=0;ix<4;++ix)
	{
	  out[ix]=0.;
	  for(iy=0;iy<4;++iy){out[ix]+=r(ix,iy)*_spin[iy];}
	}
      for(ix=0;ix<4;++ix){_spin[ix]=out[ix];}
    }
  else
    {
      LorentzSpinor temp=(*this).transformRep(defaultDRep);
      LorentzSpinor output(defaultDRep);
      for(ix=0;ix<4;++ix)
	{
	  output[ix]=0.;
	  for(iy=0;iy<4;++iy){output[ix]+=r(ix,iy)*temp[iy];}
	}
      *this=output.transformRep(Rep());
    }
  return *this;
}
