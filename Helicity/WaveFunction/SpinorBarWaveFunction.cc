// non-inlined functions of SpinorBarWaveFunction class
// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SpinorBarWaveFunction class.
//
// Author: Peter Richardson
//

#include "SpinorBarWaveFunction.h"

namespace ThePEG {
namespace Helicity {

// calculate the Wavefunction
void SpinorBarWaveFunction::calculateWaveFunction(unsigned int ihel,DiracRep dirac)
{
  Direction dir=direction();
  if(dir==intermediate)
    {ThePEG::Helicity::HelicityConsistencyError() 
	<< "In SpinorBarWaveFunction::calcluateWaveFunction "
	<< "particle must be incoming or outgoing not intermediate" 
	<< Exception::abortnow;}
  // check ihelicity is O.K.
  if(ihel>1)
    {
      ThePEG::Helicity::HelicityConsistencyError() 
	<< "Invalid Helicity = " << ihel << " requested for SpinorBar" 
	<< Exception::abortnow;
      for(int ix=0;ix<4;++ix){_wf[ix]=0.0;}
    }
  else
    {
      // extract the momentum components
      double fact=-1.; if(dir==incoming){fact=1.;}
      Energy ppx=fact*px(),ppy=fact*py(),ppz=fact*pz(),pee=fact*e(),pmm=mass();
      // define and calculate some kinematic quantities
      Energy2 ptran2  = ppx*ppx+ppy*ppy;
      Energy pabs   = sqrt(ptran2+ppz*ppz);
      Energy ptran  = sqrt(ptran2);
      // first need to evalulate the 2-component helicity spinors 
      // this is the same regardless of which definition of the spinors
      // we are using
      Complex hel_wf[2];
      // compute the + spinor for + helicty particles and - helicity antiparticles
      if((dir==outgoing && ihel== 1) || (dir==incoming && ihel==0))
	{
	  // no transverse momentum 
	  if(ptran==Energy())
	    {
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
	      InvSqrtEnergy denominator = 1./sqrt(2.*pabs);
	      SqrtEnergy rtppluspz;
	      if(ppz>=Energy())
		{rtppluspz = sqrt(pabs+ppz);}
	      else
		{rtppluspz = ptran/sqrt(pabs-ppz);} 
	      hel_wf[0] = denominator*rtppluspz;
	      hel_wf[1] = denominator/rtppluspz*complex<Energy>(ppx,-ppy);
	    }
	}
      // compute the - spinor for - helicty particles and + helicity antiparticles
      else
	{
	  // no transverse momentum
	  if(ptran==Energy())
	    {
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
	      InvSqrtEnergy denominator = 1./sqrt(2.*pabs);
	      SqrtEnergy rtppluspz;
	      if(ppz>=Energy())
		{rtppluspz = sqrt(pabs+ppz);}
	      else
		{rtppluspz = ptran/sqrt(pabs-ppz);}
	      hel_wf[0] = denominator/rtppluspz*complex<Energy>(-ppx,-ppy);
	      hel_wf[1] = denominator*rtppluspz;
	    }
	}
      // decide which definition of the spinors we are using
      SqrtEnergy eplusm,eminusm,upper,lower,eplusp,eminusp;
      switch(dirac)
	{
	  // Haber lower energy
	case HaberDRep:
	  eplusm = sqrt(pee+pmm);
	  eminusm = pabs/eplusm;
	  if(dir==outgoing)
	    {
	      upper = eplusm;
	      if(ihel==1) 
		{lower =-eminusm;}
	      else
		{lower = eminusm;}
	    }
	  else
	    {
	      upper = eminusm;
	      if(ihel==1)
		{lower = eplusm;}
	      else
		{lower =-eplusm;}
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
	  if(dir==outgoing)
	    {
	      if(ihel==1)
		{
		  upper = eplusp;
		  lower = eminusp;
		}
	      else
		{
		  upper = eminusp;
		  lower = eplusp;
		}
	    }
	  else
	    {
	      if(ihel==1)
		{
		  upper = eminusp;
		  lower = -eplusp;
		}
	      else
		{
		  upper =-eplusp;
		  lower = eminusp;
		}
	    }
	  break;
	  // invalid choice
	default:
	  upper= lower=SqrtEnergy(); // no warnings about uninitialized
	  ThePEG::Helicity::HelicityConsistencyError() 
	    << "Invalid choice of Dirac representation in "
	    << "SpinorWaveFunction::calculateWaveFunction() " << Exception::abortnow; 
	  break;
	}
      // now finally we can construct the spinors
      if(dir==incoming) {
	_wf = LorentzSpinorBar<double>(v_spinortype,dirac);
      }
      else {
	_wf = LorentzSpinorBar<double>(u_spinortype,dirac);
      }
      _wf[0] = upper*hel_wf[0]*UnitRemoval::InvSqrtE;
      _wf[1] = upper*hel_wf[1]*UnitRemoval::InvSqrtE;
      _wf[2] = lower*hel_wf[0]*UnitRemoval::InvSqrtE;
      _wf[3] = lower*hel_wf[1]*UnitRemoval::InvSqrtE;
    }
}

// construct the spininfo object
void SpinorBarWaveFunction::constructSpinInfo(vector<LorentzSpinorBar<SqrtEnergy> >& wave,
					      tPPtr part,bool time, bool vertex)
{
  tFermionSpinPtr inspin;
  if(part->spinInfo())
    {inspin=dynamic_ptr_cast<tFermionSpinPtr>(part->spinInfo());}
  if(direction()==outgoing)
    {
      if(inspin)
	{
	  wave.resize(2);
	  wave[0]=inspin->getProductionBasisState(0).bar();
	  wave[1]=inspin->getProductionBasisState(1).bar();
	}
      else
	{
	  if(vertex)
	    {
	      SpinPtr temp = new_ptr(FermionSpinInfo(part->momentum(),time));
	      inspin=dynamic_ptr_cast<tFermionSpinPtr>(temp);
	      part->spinInfo(temp);
	    }
	  constructSpinInfo(wave,inspin,vertex);
	}
    }
  else
    {
      if(inspin)
	{
	  inspin->decay();
	  wave.resize(2);
	  wave[0]=inspin->getDecayBasisState(0).bar();
	  wave[1]=inspin->getDecayBasisState(1).bar();
	}
      else
	{
	  if(part->spinInfo())
	    {throw ThePEG::Helicity::HelicityConsistencyError() 
		<< "Wrong type of SpinInfo for the incoming particle in "
		<< "SpinorBarWaveFunction::constructSpinInfo() "
		<< Exception::warning;}
	  if(vertex)
	    {
	      SpinPtr newspin=new_ptr(FermionSpinInfo(part->momentum(),time));
	      inspin= dynamic_ptr_cast<tFermionSpinPtr>(newspin);
	      if(time) inspin->decayed(true);
	      part->spinInfo(newspin);
	    }
	  constructSpinInfo(wave,inspin,vertex);
	}
    }
}

// construct the spininfo object
void SpinorBarWaveFunction::constructSpinInfo(vector<LorentzSpinorBar<SqrtEnergy> >& wave,
					      RhoDMatrix& rho,tPPtr part,bool time,
					      bool vertex)
{
  tFermionSpinPtr inspin;
  if(part->spinInfo())
    {inspin=dynamic_ptr_cast<tFermionSpinPtr>(part->spinInfo());}
  if(direction()==outgoing)
    {
      if(inspin)
	{
	  wave.resize(2);
	  wave[0]=inspin->getProductionBasisState(0).bar();
	  wave[1]=inspin->getProductionBasisState(1).bar();
	}
      else
	{
	  if(vertex)
	    {
	      SpinPtr temp = new_ptr(FermionSpinInfo(part->momentum(),time));
	      inspin=dynamic_ptr_cast<tFermionSpinPtr>(temp);
	      part->spinInfo(temp);
	    }
	  constructSpinInfo(wave,inspin,vertex);
	}
      rho = RhoDMatrix(PDT::Spin1Half);rho.average();
    }
  else
    {
      if(inspin)
	{
	  inspin->decay();
	  rho = inspin->rhoMatrix();
	  // rho matrix should be here
	  wave.resize(2);
	  wave[0]=inspin->getDecayBasisState(0).bar();
	  wave[1]=inspin->getDecayBasisState(1).bar();
	}
      else
	{
	  if(part->spinInfo())
	    {throw ThePEG::Helicity::HelicityConsistencyError() 
		<< "Wrong type of SpinInfo for the incoming particle in "
		<< "SpinorBarWaveFunction::constructSpinInfo() "
		<< Exception::warning;}
	  if(vertex)
	    {
	      SpinPtr newspin=new_ptr(FermionSpinInfo(part->momentum(),time));
	      inspin= dynamic_ptr_cast<tFermionSpinPtr>(newspin);
	      if(time) inspin->decayed(true);
	      part->spinInfo(newspin);
	    }
	  rho = RhoDMatrix(PDT::Spin1Half);rho.average();
	  constructSpinInfo(wave,inspin,vertex);
	}
    }
}

// construct the spininfo object
void SpinorBarWaveFunction::constructSpinInfo(vector<SpinorBarWaveFunction>& wave,
					      tPPtr part,bool time, bool vertex)
{
  tFermionSpinPtr inspin;
  if(part->spinInfo())
    {inspin=dynamic_ptr_cast<tFermionSpinPtr>(part->spinInfo());}
  if(direction()==outgoing)
    {
      if(inspin)
	{
	  wave.resize(2);
	  wave[0]=SpinorBarWaveFunction(getMomentum(),getParticle(),
					inspin->getProductionBasisState(0).bar(),
					DummyType(),
					direction());
	  wave[1]=SpinorBarWaveFunction(getMomentum(),getParticle(),
					inspin->getProductionBasisState(1).bar(),
					DummyType(),
					direction());
	}
      else
	{
	  if(vertex)
	    {
	      SpinPtr temp = new_ptr(FermionSpinInfo(part->momentum(),time));
	      inspin=dynamic_ptr_cast<tFermionSpinPtr>(temp);
	      part->spinInfo(temp);
	    }
	  constructSpinInfo(wave,inspin,vertex);
	}
    }
  else
    {
      if(inspin)
	{
	  inspin->decay();
	  wave.resize(2);
	  wave[0]=SpinorBarWaveFunction(getMomentum(),getParticle(),
					inspin->getDecayBasisState(0).bar(),
					DummyType(),
					direction());
	  wave[1]=SpinorBarWaveFunction(getMomentum(),getParticle(),
					inspin->getDecayBasisState(1).bar(),
					DummyType(),
					direction());
	}
      else
	{
	  if(part->spinInfo())
	    {throw ThePEG::Helicity::HelicityConsistencyError() 
		<< "Wrong type of SpinInfo for the incoming particle in "
		<< "SpinorBarWaveFunction::constructSpinInfo() "
		<< Exception::warning;}
	  if(vertex)
	    {
	      SpinPtr newspin=new_ptr(FermionSpinInfo(part->momentum(),time));
	      inspin= dynamic_ptr_cast<tFermionSpinPtr>(newspin);
	      if(time) inspin->decayed(true);
	      part->spinInfo(newspin);
	    }
	  constructSpinInfo(wave,inspin,vertex);
	}
    }
}

// construct the spininfo object
void SpinorBarWaveFunction::constructSpinInfo(vector<SpinorBarWaveFunction>& wave,
					      RhoDMatrix& rho,tPPtr part,bool time,
					      bool vertex)
{
  tFermionSpinPtr inspin;
  if(part->spinInfo())
    {inspin=dynamic_ptr_cast<tFermionSpinPtr>(part->spinInfo());}
  if(direction()==outgoing)
    {
      if(inspin)
	{
	  wave.resize(2);
	  wave[0]=SpinorBarWaveFunction(getMomentum(),getParticle(),
					inspin->getProductionBasisState(0).bar(),
					DummyType(),
					direction());
	  wave[1]=SpinorBarWaveFunction(getMomentum(),getParticle(),
					inspin->getProductionBasisState(1).bar(),
					DummyType(),
					direction());
	}
      else
	{
	  if(vertex)
	    {
	      SpinPtr temp = new_ptr(FermionSpinInfo(part->momentum(),time));
	      inspin=dynamic_ptr_cast<tFermionSpinPtr>(temp);
	      part->spinInfo(temp);
	    }
	  constructSpinInfo(wave,inspin,vertex);
	}
      rho = RhoDMatrix(PDT::Spin1Half);rho.average();
    }
  else
    {
      if(inspin)
	{
	  inspin->decay();
	  rho = inspin->rhoMatrix();
	  // rho matrix should be here
	  wave.resize(2);
	  wave[0]=SpinorBarWaveFunction(getMomentum(),getParticle(),
					inspin->getDecayBasisState(0).bar(),
					DummyType(),
					direction());
	  wave[1]=SpinorBarWaveFunction(getMomentum(),getParticle(),
					inspin->getDecayBasisState(1).bar(),
					DummyType(),
					direction());
	}
      else
	{
	  if(part->spinInfo())
	    {throw ThePEG::Helicity::HelicityConsistencyError() 
		<< "Wrong type of SpinInfo for the incoming particle in "
		<< "SpinorBarWaveFunction::constructSpinInfo() "
		<< Exception::warning;}
	  if(vertex)
	    {
	      SpinPtr newspin=new_ptr(FermionSpinInfo(part->momentum(),time));
	      inspin= dynamic_ptr_cast<tFermionSpinPtr>(newspin);
	      if(time) inspin->decayed(true);
	      part->spinInfo(newspin);
	    }
	  rho = RhoDMatrix(PDT::Spin1Half);rho.average();
	  constructSpinInfo(wave,inspin,vertex);
	}
    }
}

void SpinorBarWaveFunction::conjugate() {
  _wf=_wf.conjugate();
}

}
}