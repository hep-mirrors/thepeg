// non-inlined members of the LorentzTensor class
#include "LorentzTensor.h"

using namespace ThePEG;
using namespace Helicity;

// general boost
LorentzTensor & LorentzTensor::boost(double bx, double by, double bz)
{
  // basic definitions
  double boostm[4][4];
  double b2 = bx*bx+by*by+bz*bz;
  double gamma = 1.0/sqrt(1.0-b2);
  double gmmone = b2 >0 ? (gamma-1.)/b2 : 0.0;
  double vec[3]={bx,by,bz};
  // compute the lorentz boost matrix
  for(unsigned int ix=0;ix<3;++ix)
    {
      for(unsigned int iy=0;iy<3;++iy){boostm[ix][iy]=vec[ix]*vec[iy]*gmmone;}
      boostm[ix][ix]+=1;
      boostm[ix][3]=gamma*vec[ix];
      boostm[3][ix]=boostm[ix][3];
    }
  boostm[3][3]=gamma;
  // apply the boost
  LorentzTensor output;
  Complex temp;
  unsigned int ix,iy,ixa,iya;
  for(ix=0;ix<4;++ix)
    {for(iy=0;iy<4;++iy)
      {
	temp=0.;
	for(ixa=0;ixa<4;++ixa)
	  {for(iya=0;iya<4;++iya)
	      {temp+=boostm[ix][ixa]*boostm[iy][iya]*(*this)(ixa,iya);}
	  }
	output(ix,iy)=temp;
      }
    }
  *this=output;
  return *this;
}

