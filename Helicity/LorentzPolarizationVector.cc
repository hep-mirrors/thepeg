// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LorentzPolarizationVector class.
//
// Author: Peter Richardson
//

#include "LorentzPolarizationVector.h"
using namespace ThePEG;
using namespace Helicity;

// boost along the X direction
LorentzPolarizationVector & LorentzPolarizationVector::boostX (double beta){
  double b2 = beta*beta;
  if (b2 >= 1) {
    cout <<  "boost along X with beta >= 1 (speed of light) -- no boost done"
	 << endl;}
  else {
    double gamma = sqrt(1./(1-b2));
    Complex tt = _vec[3];
    _vec[3] = gamma*(_vec[3] + beta*_vec[0]);
    _vec[0] = gamma*(_vec[0] + beta*tt    );
  }
  return *this;
}

// boost along the y direction
LorentzPolarizationVector & LorentzPolarizationVector::boostY (double beta){
  double b2 = beta*beta;
  if (b2 >= 1) {
    cout <<  "boost along Y with beta >= 1 (speed of light) -- no boost done"
	 << endl;}
  else {
    double gamma = sqrt(1./(1-b2));
    Complex tt = _vec[3];
    _vec[3] = gamma*(_vec[3] + beta*_vec[1]);
    _vec[1] = gamma*(_vec[1] + beta*tt    );
  }
  return *this;
}

// boost along the z direction
LorentzPolarizationVector & LorentzPolarizationVector::boostZ (double beta){
  double b2 = beta*beta;
  if (b2 >= 1) {
    cout <<  "boost along Y with beta >= 1 (speed of light) -- no boost done"
	 << endl;}
  else {
    double gamma = sqrt(1./(1-b2));
    Complex tt = _vec[3];
    _vec[3] = gamma*(_vec[3] + beta*_vec[2]);
    _vec[2] = gamma*(_vec[2] + beta*tt    );
  }
  return *this;
}

// general boost
LorentzPolarizationVector & LorentzPolarizationVector::
boost(double bx, double by, double bz){
  double b2 = bx*bx+by*by+bz*bz;
  double gamma = 1.0/sqrt(1.0-b2);
  Complex bdotp = bx*x()+by*y()+bz*z();
  double gmmone = b2 >0 ? (gamma-1.)/b2 : 0.0;
  _vec[0] = _vec[0]+gamma*bx*_vec[3]+gmmone*bdotp*bx;
  _vec[1] = _vec[1]+gamma*by*_vec[3]+gmmone*bdotp*by;
  _vec[2] = _vec[2]+gamma*bz*_vec[3]+gmmone*bdotp*bz;
  _vec[3] = gamma*(_vec[3]+bdotp);
  return *this;
}

// rotation about X axis
LorentzPolarizationVector & LorentzPolarizationVector::rotateX(double phi) {
  double sphi=sin(phi);
  double cphi=cos(phi);
  Complex ty=y();
  _vec[1] = _vec[1]*cphi-_vec[2]*sphi;
  _vec[2] = _vec[2]*cphi+ty    *sphi;
  return *this;
}

// rotation about Y axis
LorentzPolarizationVector & LorentzPolarizationVector::rotateY(double phi) {
  double sphi=sin(phi);
  double cphi=cos(phi);
  Complex tz=z();
  _vec[2] = _vec[2]*cphi-_vec[0]*sphi;
  _vec[0] = _vec[0]*cphi+tz    *sphi;
  return *this;
}

// rotation about Z axis
LorentzPolarizationVector & LorentzPolarizationVector::rotateZ(double phi) {
  double sphi=sin(phi);
  double cphi=cos(phi);
  Complex tx=x();
  _vec[0] = _vec[0]*cphi-_vec[1]*sphi;
  _vec[1] = _vec[1]*cphi+tx    *sphi;
  return *this;
}

// rotate the axis
LorentzPolarizationVector & LorentzPolarizationVector::
rotateUz(const Hep3Vector &v) {
  double v1=v.x();
  double v2=v.y();
  double v3=v.z();
  double vpt=v1*v1+v2*v2;
  Complex vtmp[3];
  if(vpt>0.)
    {
      vpt=sqrt(vpt);
      for(int ix=0;ix<3;++ix){vtmp[ix]=_vec[ix];}
      _vec[0] = (v1*v3*vtmp[0]-v2*vtmp[1])/vpt+v1*vtmp[0];
      _vec[1] = (v2*v3*vtmp[0]+v1*vtmp[1])/vpt+v2*vtmp[1];
      _vec[2] =   -vpt*vtmp[0]                +v3*vtmp[2];
    }
  else if(v3<0.)
    {
      _vec[0]=-_vec[0];
      _vec[2]=-_vec[2];
    }
  else
    {;}
  return *this;
}

// Dividing LorentzVector by a complex number
LorentzPolarizationVector & LorentzPolarizationVector::
operator /= (Complex c)
{
  if(c.real()==0. && c.imag()==0.)
    {
      cout << "Attempt to divid LorentzPolarizationVector by zero" << endl;
    }
  else
    {
      Complex ooverc=1./c;
      for(int ix=0; ix<4; ++ix){_vec[ix] *= ooverc;}
    }
  return *this;
}

// Dividing LorentzVector by a complex number
LorentzPolarizationVector
operator / (const LorentzPolarizationVector & v, Complex c)
{
  if(c.real()==0. && c.imag()==0.)
    {
      cout << "Attempt to divid LorentzPolarizationVector by zero" << endl;
      return LorentzPolarizationVector();
    }
  else
    {
      Complex ooverc=1./c;
      return LorentzPolarizationVector(v.x()*ooverc,v.y()*ooverc,
				       v.z()*ooverc,v.t()*ooverc);
    }
}


