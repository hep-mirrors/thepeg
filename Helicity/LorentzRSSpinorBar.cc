
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

LorentzRSSpinorBar & LorentzRSSpinorBar::boost(double bx,double by,double bz)
{
  // work out beta and chi
  double b2(bx*bx+by*by+bz*bz),beta(sqrt(b2)),chi(atanh(beta));
  double sinhchi(sinh(0.5*chi)/beta),coshchi(cosh(0.5*chi));
  // calculate the new spinor
  Complex out[4][4],ii(0.,1.),boosts[4][4];
  Complex nxminy(bx-ii*by),nxpiny(bx+ii*by);
  double gamma(1.0/sqrt(1.0-b2)),gmmone(b2 >0 ? (gamma-1.)/b2 : 0.0);
  double bvec[3]={bx,by,bz},boostv[4][4];
  unsigned int ix,iy,ixa,iya;
  // spin matrix
  switch(_dirac)
    {
      // Haber lower energy
    case HaberDRep:
      boosts[0][0] = coshchi;
      boosts[0][1] = 0.;
      boosts[0][2] =-sinhchi*bz;
      boosts[0][3] =-sinhchi*nxminy;
      boosts[1][0] = 0.;
      boosts[1][1] = coshchi;
      boosts[1][2] =-sinhchi*nxpiny;
      boosts[1][3] = sinhchi*bz;
      boosts[2][0] =-sinhchi*bz;
      boosts[2][1] =-sinhchi*nxminy;
      boosts[2][2] = coshchi;
      boosts[2][3] = 0.;
      boosts[3][0] =-sinhchi*nxpiny;
      boosts[3][1] = sinhchi*bz;
      boosts[3][2] = 0.;
      boosts[3][3] = coshchi;
      break;
      // HELAS
    case HELASDRep:
      boosts[0][0] = coshchi+sinhchi*bz;
      boosts[0][1] = sinhchi*nxminy;
      boosts[0][2] = 0.;
      boosts[0][3] = 0.;
      boosts[1][0] = sinhchi*nxpiny;
      boosts[1][1] = coshchi-sinhchi*bz;
      boosts[1][2] = 0.;
      boosts[1][3] = 0.;
      boosts[2][0] = 0.;
      boosts[2][1] = 0.;
      boosts[2][2] = coshchi-sinhchi*bz;
      boosts[2][3] =-sinhchi*nxminy;
      boosts[3][0] = 0.;
      boosts[3][1] = 0.;
      boosts[3][2] =-sinhchi*nxpiny;
      boosts[3][3] = coshchi+sinhchi*bz;
      break;
    }
  // vector matrix
  for(ix=0;ix<3;++ix)
    {
      for(iy=0;iy<3;++iy){boostv[ix][iy]=bvec[ix]*bvec[iy]*gmmone;}
      boostv[ix][ix]+=1;
      boostv[ix][3]=gamma*bvec[ix];
      boostv[3][ix]=boostv[ix][3];
    }
  boostv[3][3]=gamma;
  // apply the boost
  for(ix=0;ix<4;++ix)
    {
      for(iy=0;iy<4;++iy)
	{
	  out[ix][iy]=0.;
	  for(ixa=0;ixa<4;++ixa)
	    {
	      for(iya=0;iya<4;++iya)
		{out[ix][iy]+=boostv[ix][ixa]*boosts[iya][iy]*_spin[ixa][iya];}
	    }
	}
    }
  *this= LorentzRSSpinorBar(out[0][0],out[0][1],out[0][2],out[0][3],
			    out[1][0],out[1][1],out[1][2],out[1][3],
			    out[2][0],out[2][1],out[2][2],out[2][3],
			    out[3][0],out[3][1],out[3][2],out[3][3],_type,_dirac);
  return *this;
}

LorentzRSSpinorBar & LorentzRSSpinorBar::boost(const Hep3Vector & boostvec)
{
  double beta = boostvec.mag(),b2(beta*beta);
  double bx(boostvec.x()),by(boostvec.y()),bz(boostvec.z());
  double chi(atanh(beta)),sinhchi(sinh(0.5*chi)/beta),coshchi(cosh(0.5*chi));
  Complex out[4][4],ii(0.,1.);
  Complex nxminy(bx-ii*by),nxpiny(bx+ii*by),boosts[4][4];
  double gamma(1.0/sqrt(1.0-b2)),gmmone(b2 >0 ? (gamma-1.)/b2 : 0.0),boostv[4][4];
  unsigned int ix,iy,ixa,iya;
  // spin matrix
  switch(_dirac)
    {
      // Haber lower energy
    case HaberDRep:
      boosts[0][0] = coshchi;
      boosts[0][1] = 0.;
      boosts[0][2] =-sinhchi*bz;
      boosts[0][3] =-sinhchi*nxminy;
      boosts[1][0] = 0.;
      boosts[1][1] = coshchi;
      boosts[1][2] =-sinhchi*nxpiny;
      boosts[1][3] = sinhchi*bz;
      boosts[2][0] =-sinhchi*bz;
      boosts[2][1] =-sinhchi*nxminy;
      boosts[2][2] = coshchi;
      boosts[2][3] = 0.;
      boosts[3][0] =-sinhchi*nxpiny;
      boosts[3][1] = sinhchi*bz;
      boosts[3][2] = 0.;
      boosts[3][3] = coshchi;
      break;
      // HELAS
    case HELASDRep:
      boosts[0][0] = coshchi+sinhchi*bz;
      boosts[0][1] = sinhchi*nxminy;
      boosts[0][2] = 0.;
      boosts[0][3] = 0.;
      boosts[1][0] = sinhchi*nxpiny;
      boosts[1][1] = coshchi-sinhchi*bz;
      boosts[1][2] = 0.;
      boosts[1][3] = 0.;
      boosts[2][0] = 0.;
      boosts[2][1] = 0.;
      boosts[2][2] = coshchi-sinhchi*bz;
      boosts[2][3] =-sinhchi*nxminy;
      boosts[3][0] = 0.;
      boosts[3][1] = 0.;
      boosts[3][2] =-sinhchi*nxpiny;
      boosts[3][3] = coshchi+sinhchi*bz;
      break;
    }
  // vector matrix
  for(ix=0;ix<3;++ix)
    {
      for(iy=0;iy<3;++iy){boostv[ix][iy]=boostvec[ix]*boostvec[iy]*gmmone;}
      boostv[ix][ix]+=1;
      boostv[ix][3]=gamma*boostvec[ix];
      boostv[3][ix]=boostv[ix][3];
    }
  // apply the boost
  for(ix=0;ix<4;++ix)
    {
      for(iy=0;iy<4;++iy)
	{
	  out[ix][iy]=0.;
	  for(ixa=0;ixa<4;++ixa)
	    {
	      for(iya=0;iya<4;++iya)
		{out[ix][iy]+=boostv[ix][ixa]*boosts[iya][iy]*_spin[ixa][iya];}
	    }
	}
    }
  *this= LorentzRSSpinorBar(out[0][0],out[0][1],out[0][2],out[0][3],
			    out[1][0],out[1][1],out[1][2],out[1][3],
			    out[2][0],out[2][1],out[2][2],out[2][3],
			    out[3][0],out[3][1],out[3][2],out[3][3],_type,_dirac);
  return *this;
}

LorentzRSSpinorBar & LorentzRSSpinorBar::transform(const LorentzRotation & r)
{
  SpinHalfLorentzRotation t(r.half().inverse());
  unsigned int ix,iy,ixa,iya;
  LorentzRSSpinorBar out;
  if(Rep()==defaultDRep)
    {
      for(ix=0;ix<4;++ix)
	{
	  for(iy=0;iy<4;++iy)
	    {
	      out(ix,iy)=0.;
	      for(ixa=0;ixa<4;++ixa)
		{
		  for(iya=0;iya<4;++iya)
		    {out(ix,iy)+=r.one()(ix,ixa)*t(iya,iy)*_spin[ixa][iya];}
		}
	    }
	}
    }
  else
    {
      LorentzRSSpinorBar temp((*this).transformRep(defaultDRep));
      for(ix=0;ix<4;++ix)
	{
	  for(iy=0;iy<4;++iy)
	    {
	      out(ix,iy)=0.;
	      for(ixa=0;ixa<4;++ixa)
		{
		  for(iya=0;iya<4;++iya)
		    {out(ix,iy)+=r.one()(ix,ixa)*t(iya,iy)*temp(ixa,iya);}
		}
	    }
	}
      out.changeRep(Rep());
    }
  *this=out;
  return *this;
}
