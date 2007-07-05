// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RSSpinorWaveFunction class.
//

#include "RSSpinorWaveFunction.h"

namespace ThePEG {
namespace Helicity {

// calculate the Wavefunction
void RSSpinorWaveFunction::calculateWaveFunction(unsigned int ihel,DiracRep dirac)
{
  // check ihelicity is O.K.
  Direction dir = direction();
  LorentzRSSpinor<double> news;
  if(dir==incoming){news=LorentzRSSpinor<double>(u_spinortype,dirac);}
  else{news=LorentzRSSpinor<double>(v_spinortype,dirac);}
  unsigned int ix,iy;
  static double eps=1E-5;
  if(dir==intermediate)
    {throw HelicityConsistencyError()
	<< "In RSSpinorWaveFunction::calcluateWaveFunction "
	<< "particle must be incoming or outgoing not intermediate" 
	<< Exception::abortnow;}
  if(ihel>3)
    {
      throw HelicityConsistencyError() 
	<< "Invalid Helicity = " << ihel 
	<< " requested for RSSpinor" << Exception::abortnow;
      for(iy=0;iy<4;++iy){for(ix=0;ix<4;++ix){_wf(ix,iy)=complex<double>();}}
    }
  else
    {
      if(mass()>Energy())
	{
	  // extract the momentum components
	  // compute the normal spinors to construct the RS spinor
	  Complex hel_wf[2][2];
	  if(dir==incoming)
	    {
	      // the + spinor
	      hel_wf[0][0] = 1.;
	      hel_wf[1][0] = 0.;
	      // the - spinor
	      hel_wf[0][1] = 0.;
	      hel_wf[1][1] = 1.;
	    }
	  else
	    {
	      // the + spinor
	      hel_wf[0][0] = 0.;
	      hel_wf[1][0] = 1.;
	      // the - spinor
	      hel_wf[0][1] = 1.;
	      hel_wf[1][1] = 0.;
	    }
	  // decide which definition of the spinors we are using
	  SqrtEnergy eplusm,eplusp,upper[2],lower[2];
	  switch(dirac)
	    {
	      // Haber lower energy
	    case HaberDRep:
	      eplusm = sqrt(2.*mass());
	      if(dir==incoming)
		{
		  upper[0] = eplusm;
		  upper[1] = eplusm;
		  lower[0] = SqrtEnergy();
		  lower[1] = SqrtEnergy();
		}
	      else
		{
		  upper[0] = SqrtEnergy();
		  upper[1] = SqrtEnergy();
		  lower[0] =-eplusm;
		  lower[1] = eplusm;
		}
	      break;
	    case HELASDRep:
	      // HELAS
	      eplusp = sqrt(mass());
	      if(dir==incoming)
		{
		  upper[0] = eplusp;
		  lower[0] = eplusp;
		  upper[1] = eplusp;
		  lower[1] = eplusp;
		}
	      else
		{
		  upper[0] =-eplusp;
		  lower[0] = eplusp;
		  upper[1] = eplusp;
		  lower[1] =-eplusp;
		}
	      break;
	      // invalid choice
	    default:
	      throw HelicityLogicalError() 
		<< "Invalid choice of Dirac representation in "
		<< "RSSpinorWaveFunction::calculateWaveFunction() " 
		<< Exception::abortnow; 
	      break;
	    }
	  // now construct the spinors
	  complex<SqrtEnergy> spinor[4][2];
	  for(ix=0;ix<2;++ix)
	    {
	      spinor[0][ix] = upper[ix]*hel_wf[0][ix];
	      spinor[1][ix] = upper[ix]*hel_wf[1][ix];
	      spinor[2][ix] = lower[ix]*hel_wf[0][ix];
	      spinor[3][ix] = lower[ix]*hel_wf[1][ix];
	    } 
	  // compute the polarization vectors to construct the RS spinor
	  Complex vec[4][3],ii(0.,1.);
	  double ort=1./sqrt(2.);
	  if(dir==incoming)
	    {
	      vec[0][0] =-ort;
	      vec[1][0] =-ort*ii;
	      vec[2][0] = 0.;
	      vec[3][0] = 0.;
	      vec[0][1] = 0.;
	      vec[1][1] = 0.;
	      vec[2][1] = 1.;
	      vec[3][1] = 0.;
	      vec[0][2] = ort;
	      vec[1][2] =-ort*ii;
	      vec[2][2] = 0.;
	      vec[3][2] = 0.;
	    }
	  else
	    {
	      vec[0][0] = ort;
	      vec[1][0] =-ort*ii;
	      vec[2][0] = 0.;
	      vec[3][0] = 0.;
	      vec[0][1] = 0.;
	      vec[1][1] = 0.;
	      vec[2][1] =-1.;
	      vec[3][1] = 0.;
	      vec[0][2] =-ort;
	      vec[1][2] =-ort*ii;
	      vec[2][2] = 0.;
	      vec[3][2] = 0.;
	    }
	  // now we can put the bits together to compute the RS spinor
	  double or3(sqrt(1./3.)),tor3(sqrt(2./3.));
	  if(ihel==0)
	    {for(ix=0;ix<4;++ix){for(iy=0;iy<4;++iy)
		  {news(ix,iy)=UnitRemoval::InvSqrtE*
		      vec[ix][0]*spinor[iy][0];}}
	    }
	  else if(ihel==1)
	    {for(ix=0;ix<4;++ix){for(iy=0;iy<4;++iy)
	      {news(ix,iy)=UnitRemoval::InvSqrtE*(
		      or3*vec[ix][0]*spinor[iy][1]+tor3*vec[ix][1]*spinor[iy][0]);}}}
	  else if(ihel==2)
	    {for(ix=0;ix<4;++ix){for(iy=0;iy<4;++iy)
		  {news(ix,iy)=UnitRemoval::InvSqrtE*(
		      or3*vec[ix][2]*spinor[iy][0]+tor3*vec[ix][1]*spinor[iy][1]);}}}
	  else if(ihel==3)
	    {for(ix=0;ix<4;++ix){for(iy=0;iy<4;++iy)
		  {news(ix,iy)=UnitRemoval::InvSqrtE*
		      vec[ix][2]*spinor[iy][1];}}
	    }
	  // boost the spinor to the lab frame
	  Boost boostv = getMomentum().boostVector();
	  if(boostv.mag()>eps){_wf=news.boost(boostv);}
	  else{_wf=news;}
	}
      // special for the massless case in the lab frame rather than the rest frame
      else
	{
	  // only two valid helicities in this case
	  if(ihel==1||ihel==2)
	    {throw HelicityLogicalError() << "Invalid Helicity = " << ihel 
					  << " requested for massless RSSpinor" 
					  << Exception::abortnow;}
	  else
	    {
	      // extract the momentum components
	      double fact=-1.; if(dir==incoming){fact=1.;}
	      Energy ppx=fact*px(),ppy=fact*py(),ppz=fact*pz(),pee=fact*e(),pmm=mass();
	      // define and calculate some kinematic quantities
	      Energy2 ptran2  = ppx*ppx+ppy*ppy;
	      Energy pabs   = sqrt(ptran2+ppz*ppz);
	      Energy ptran  = sqrt(ptran2);
	      Complex hel_wf[2],vec[4],ii(0.,1.);
	      double root = 1./sqrt(2.);
	      // positve 3/2 helicity spinor
	      if((dir==incoming && ihel==3)||(dir==outgoing &&ihel==0))
		{
		  // the polarization vector
		  // first the no pt case
		  if(ptran==Energy())
		    {
		      double sgnz;
		      if(ppz<Energy()){sgnz=-1.;}
		      else{sgnz=1.;}
		      vec[0]=-root;
		      vec[1]=-sgnz*root*ii;
		      vec[2]=0.;
		      vec[3]=0.;
		      if(ppz>=Energy())
			{
			  hel_wf[0] = 1;
			  hel_wf[1] = 0;
			}
		      else
			{
			  hel_wf[0] = 0;
			  hel_wf[1] = 1;
			}
		    }
		  else
		    {
		      InvEnergy opabs=1./pabs;
		      InvEnergy opt  =1./ptran;
		      vec[0]=root*Complex(-ppz*ppx*opabs*opt,ppy*opt);
		      vec[1]=root*Complex(-ppz*ppy*opabs*opt,-ppx*opt);
		      vec[2]=ptran*opabs*root;
		      vec[3]=0.;
		      InvSqrtEnergy denominator = 1./sqrt(2.*pabs);
		      SqrtEnergy rtppluspz;
		      if(ppz>=Energy())
			{rtppluspz = sqrt(pabs+ppz);}
		      else
			{rtppluspz = ptran/sqrt(pabs-ppz);} 
		      hel_wf[0] = denominator*rtppluspz;
		      hel_wf[1] = denominator/rtppluspz*complex<Energy>(ppx,ppy);
		    }
		}
	      // negative 3/2 helicity spinor
	      else
		{
		  // the polarization vector
		  // first the no pt case
		  if(ptran==Energy())
		    {
		      double sgnz;
		      if(ppz<Energy()){sgnz=-1.;}
		      else{sgnz=1.;}
		      vec[0]= root;
		      vec[1]= -sgnz*root*ii;
		      vec[2]=0.;
		      vec[3]=0.;
		      if(ppz>=Energy())
			{
			  hel_wf[0] = 0;
			  hel_wf[1] = 1;
			}
		      // transverse momentum 
		      else
			{
			  hel_wf[0] = -1;
			  hel_wf[1] =  0;
			}
		    }
		  else
		    {
		      InvEnergy opabs=1./pabs;
		      InvEnergy opt  =1./ptran;
		      vec[0]=root*Complex(ppz*ppx*opabs*opt,ppy*opt);
		      vec[1]=root*Complex(ppz*ppy*opabs*opt,-ppx*opt);
		      vec[2]=-ptran*opabs*root;
		      vec[3]=0.;
		      InvSqrtEnergy denominator = 1./sqrt(2.*pabs);
		      SqrtEnergy rtppluspz;
		      if(ppz>=Energy())
			{rtppluspz = sqrt(pabs+ppz);}
		      else
			{rtppluspz = ptran/sqrt(pabs-ppz);}
		      hel_wf[0] = denominator/rtppluspz*
			complex<Energy>(-ppx,ppy);
		      hel_wf[1] = denominator*rtppluspz;
		    }
		}
	      // decide which definition of the spinors we are using
	      SqrtEnergy eplusm,eminusm,eplusp,eminusp,upper,lower;
	      switch(dirac)
		{
		  // Haber lower energy
		case HaberDRep:
		  eplusm = sqrt(pee+pmm);
		  eminusm = pabs/eplusm;
		  if(dir==incoming)
		    {
		      upper = eplusm;
		      if(ihel==3) 
			{lower = eminusm;}
		      else
			{lower =-eminusm;}
		    }
		  else
		    {
		      upper = eminusm;
		      if(ihel==3)
			{lower =-eplusm;}
		      else
			{lower = eplusm;}
		    }
		  break;
		case HELASDRep:
		  // HELAS
		  eplusp = sqrt(pee+pabs);
		  if(pmm!=Energy()) 
		    {eminusp=pmm/eplusp;}
		  else
		    {eminusp=SqrtEnergy();}
		  // set up the coefficients for the different cases
		  if(dir==incoming)
		    {
		      if(ihel==3)
			{
			  upper = eminusp;
			  lower = eplusp;
			}
		      else
			{
			  upper = eplusp;
			  lower = eminusp;
			}
		    }
		  else
		    {
		      if(ihel==3)
			{
			  upper = -eplusp;
			  lower = eminusp;
			}
		      else
			{
			  upper = eminusp;
			  lower =-eplusp;
			}
		    }
		  break;
		  // invalid choice
		default:
		  upper=lower=SqrtEnergy(); // no warnings about uninitialized
		  ThePEG::Helicity::HelicityConsistencyError() 
		    << "Invalid choice of Dirac representation in "
		    << "SpinorWaveFunction::calculateWaveFunction() " 
		    << Exception::abortnow; 
		  break;
		}
	      complex<SqrtEnergy> spinor[4]={upper*hel_wf[0],upper*hel_wf[1],
				 lower*hel_wf[0],lower*hel_wf[1]};
	      for(ix=0;ix<4;++ix) 
		for(iy=0;iy<4;++iy)
		  news(ix,iy) = UnitRemoval::InvSqrtE*vec[ix]*spinor[iy];
	      _wf=news;
	    }
	}
    }
 }


}
}
