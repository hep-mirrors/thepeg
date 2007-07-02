// -*- C++ -*-
//
// This is the implementation of the non-inlined member
// functions of the LorentzSpinorBar class.
//
// Author: Peter Richardson
//

#include "LorentzSpinorBar.h"
#include "LorentzSpinor.h"

using namespace ThePEG;
using namespace ThePEG::Helicity;

// return the unbarred spinor
template <typename Value>
LorentzSpinor<Value> LorentzSpinorBar<Value>::bar() const
{
  complex<Value> output[4];
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
  return LorentzSpinor<Value>(output[0],output[1],output[2],output[3],_type,_dirac);
}

template <typename Value>
LorentzSpinorBar<Value> & LorentzSpinorBar<Value>::boost(double bx,double by,double bz)
{
  // work out beta and chi
  double beta=sqrt(bx*bx+by*by+bz*bz);
  double chi = atanh(beta);
  double sinhchi = sinh(0.5*chi)/beta, coshchi = cosh(0.5*chi);
  // calculate the new spinor
  complex<Value> out[4];
  Complex ii(0.,1.);
  Complex nxminy=bx-ii*by;
  Complex nxpiny=bx+ii*by;
  switch(_dirac)
    {
      // Haber lower energy
    case HaberDRep:
      out[0] = coshchi*_spin[0]+sinhchi*(+bz*_spin[2]+nxpiny*_spin[3]);
      out[1] = coshchi*_spin[1]+sinhchi*(-bz*_spin[3]+nxminy*_spin[2]);
      out[2] = coshchi*_spin[2]+sinhchi*(+bz*_spin[0]+nxpiny*_spin[1]);
      out[3] = coshchi*_spin[3]+sinhchi*(-bz*_spin[1]+nxminy*_spin[0]);
      break;
      // HELAS
    case HELASDRep:
      out[0] = coshchi*_spin[0]+sinhchi*(-bz*_spin[0]-nxpiny*_spin[1]);
      out[1] = coshchi*_spin[1]+sinhchi*(+bz*_spin[1]-nxminy*_spin[0]);
      out[2] = coshchi*_spin[2]+sinhchi*(+bz*_spin[2]+nxpiny*_spin[3]);
      out[3] = coshchi*_spin[3]+sinhchi*(-bz*_spin[3]+nxminy*_spin[2]);
      break;
    }
  for(unsigned int ix=0;ix<4;++ix){_spin[ix]=out[ix];}
  return *this;
}

template <typename Value>
LorentzSpinorBar<Value> & LorentzSpinorBar<Value>::boost(const Boost & boostv)
{
  double beta = boostv.mag();
  double bx=boostv.x(),by=boostv.y(),bz=boostv.z();
  double chi = atanh(beta);
  double sinhchi = sinh(0.5*chi)/beta, coshchi = cosh(0.5*chi);
  complex<Value> out[4];
  Complex ii(0.,1.);
  Complex nxminy=bx-ii*by;
  Complex nxpiny=bx+ii*by;
  switch(_dirac)
    {
      // Haber lower energy
    case HaberDRep:
      out[0] = coshchi*_spin[0]+sinhchi*(+bz*_spin[2]+nxpiny*_spin[3]);
      out[1] = coshchi*_spin[1]+sinhchi*(-bz*_spin[3]+nxminy*_spin[2]);
      out[2] = coshchi*_spin[2]+sinhchi*(+bz*_spin[0]+nxpiny*_spin[1]);
      out[3] = coshchi*_spin[3]+sinhchi*(-bz*_spin[1]+nxminy*_spin[0]);
      break;
      // HELAS
    case HELASDRep:
      out[0] = coshchi*_spin[0]+sinhchi*(-bz*_spin[0]-nxpiny*_spin[1]);
      out[1] = coshchi*_spin[1]+sinhchi*(+bz*_spin[1]-nxminy*_spin[0]);
      out[2] = coshchi*_spin[2]+sinhchi*(+bz*_spin[2]+nxpiny*_spin[3]);
      out[3] = coshchi*_spin[3]+sinhchi*(-bz*_spin[3]+nxminy*_spin[2]);
      break;
    }
  for(unsigned int ix=0;ix<4;++ix){_spin[ix]=out[ix];}
  return *this;
}

// general transform
template <typename Value>
LorentzSpinorBar<Value> & LorentzSpinorBar<Value>::transform(const SpinHalfLorentzRotation & r)
{
  unsigned int ix,iy;
  SpinHalfLorentzRotation t(r.inverse());
  if(Rep()==defaultDRep)
    {
      complex<Value> out[4];
      for(ix=0;ix<4;++ix)
	{
	  out[ix]=complex<Value>();
	  for(iy=0;iy<4;++iy){out[ix]+=_spin[iy]*t(iy,ix);}
	}
      for(ix=0;ix<4;++ix){_spin[ix]=out[ix];}
    }
  else
    {
      LorentzSpinorBar temp=(*this).transformRep(defaultDRep);
      LorentzSpinorBar output(defaultDRep);
      for(ix=0;ix<4;++ix)
	{
	  output[ix]=complex<Value>();
	  for(iy=0;iy<4;++iy){output[ix]+=temp[iy]*t(iy,ix);}
	}
      *this=output.transformRep(Rep());
    }
  return *this;
}


// conjugation
template <typename Value>
LorentzSpinorBar<Value> LorentzSpinorBar<Value>::conjugate() const {
  SpinorType new_type;
  switch(_type) {
  case u_spinortype:
    new_type=v_spinortype;
    break;
  case v_spinortype:
    new_type=u_spinortype;
    break;
  case unknown_spinortype:
  default:
    new_type=unknown_spinortype;
    break;
  }
  return LorentzSpinorBar<Value>(-conj(_spin[3]),+conj(_spin[2]),
                         +conj(_spin[1]),-conj(_spin[0]),new_type,_dirac);
}
