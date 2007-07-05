// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SpinHalfLorentzRotation class.
//

#include "SpinHalfLorentzRotation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SpinHalfLorentzRotation.tcc"
#endif


using namespace ThePEG;

// inverse ( inverse is gamma0 S dagger gamma 0)
SpinHalfLorentzRotation SpinHalfLorentzRotation::inverse() const {
  SpinHalfLorentzRotation output;
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      output=SpinHalfLorentzRotation
	(+conj(_mx[0][0]), conj(_mx[1][0]),-conj(_mx[2][0]),-conj(_mx[3][0]),
	 +conj(_mx[0][1]), conj(_mx[1][1]),-conj(_mx[2][1]),-conj(_mx[3][1]),
	 -conj(_mx[0][2]),-conj(_mx[1][2]), conj(_mx[2][2]), conj(_mx[3][2]),
	 -conj(_mx[0][3]),-conj(_mx[1][3]), conj(_mx[2][3]), conj(_mx[3][3]));
      break;
      // helas
    case HELASDRep:
      output=SpinHalfLorentzRotation
	(conj(_mx[2][2]),conj(_mx[3][2]),conj(_mx[0][2]),conj(_mx[1][2]),
	 conj(_mx[2][3]),conj(_mx[3][3]),conj(_mx[0][3]),conj(_mx[1][3]),
	 conj(_mx[2][0]),conj(_mx[3][0]),conj(_mx[0][0]),conj(_mx[1][0]),
	 conj(_mx[2][1]),conj(_mx[3][1]),conj(_mx[0][1]),conj(_mx[1][1]));
      break;
    }
  return output;
}

// specify the components of a lorentz boost
SpinHalfLorentzRotation & SpinHalfLorentzRotation::setBoost (double bx, double by, double bz)
{
  // work out beta and chi
  static double eps=1e-10;
  double beta(sqrt(bx*bx+by*by+bz*bz)),chi(atanh(beta)),chc(cosh(0.5*chi)),shc(0.5);
  if(beta>eps){shc=sinh(0.5*chi)/beta;}
  Complex ii(0.,1.),nxminy(bx-ii*by),nxplny(bx+ii*by);
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      _mx[0][0]= chc       ;_mx[0][1]= 0.        ;_mx[0][2]= shc*bz    ;_mx[0][3]= shc*nxminy;
      _mx[1][0]= 0.        ;_mx[1][1]= chc       ;_mx[1][2]= shc*nxplny;_mx[1][3]=-shc*bz    ;
      _mx[2][0]= shc*bz    ;_mx[2][1]= shc*nxminy;_mx[2][2]= chc       ;_mx[2][3]= 0.        ;
      _mx[3][0]= shc*nxplny;_mx[3][1]= shc*bz    ;_mx[3][2]= 0.        ;_mx[3][3]= chc       ;
      break;
      // helas
    case HELASDRep:
      _mx[0][0]= chc-shc*bz;_mx[0][1]=-shc*nxminy;_mx[0][2]= 0.        ;_mx[0][3]= 0.        ;
      _mx[1][0]=-shc*nxplny;_mx[1][1]= chc+shc*bz;_mx[1][2]= 0.        ;_mx[1][3]= 0.        ;
      _mx[2][0]= 0.        ;_mx[2][1]= 0.        ;_mx[2][2]= chc+shc*bz;_mx[2][3]=+shc*nxminy;
      _mx[3][0]= 0.        ;_mx[3][1]= 0.        ;_mx[3][2]=+shc*nxplny;_mx[3][3]= chc-shc*bz;
      break;
    }
  return *this;
}

// specify a boost vector
SpinHalfLorentzRotation & SpinHalfLorentzRotation::setBoost (const Boost & b)
{
  // work out beta and chi
  static double eps=1e-10;
  double bx(b.x()),by(b.y()),bz(b.z()),beta(b.mag()),chi(atanh(beta)),
    chc(cosh(0.5*chi)),shc(0.5);
  if(beta>eps){shc=sinh(0.5*chi)/beta;}
  Complex ii(0.,1.),nxminy(bx-ii*by),nxplny(bx+ii*by);
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      _mx[0][0]= chc       ;_mx[0][1]= 0.        ;_mx[0][2]= shc*bz    ;_mx[0][3]= shc*nxminy;
      _mx[1][0]= 0.        ;_mx[1][1]= chc       ;_mx[1][2]= shc*nxplny;_mx[1][3]=-shc*bz    ;
      _mx[2][0]= shc*bz    ;_mx[2][1]= shc*nxminy;_mx[2][2]= chc       ;_mx[2][3]= 0.        ;
      _mx[3][0]= shc*nxplny;_mx[3][1]= shc*bz    ;_mx[3][2]= 0.        ;_mx[3][3]= chc       ;
      break;
      // helas
    case HELASDRep:
      _mx[0][0]= chc-shc*bz;_mx[0][1]=-shc*nxminy;_mx[0][2]= 0.        ;_mx[0][3]= 0.        ;
      _mx[1][0]=-shc*nxplny;_mx[1][1]= chc+shc*bz;_mx[1][2]= 0.        ;_mx[1][3]= 0.        ;
      _mx[2][0]= 0.        ;_mx[2][1]= 0.        ;_mx[2][2]= chc+shc*bz;_mx[2][3]=+shc*nxminy;
      _mx[3][0]= 0.        ;_mx[3][1]= 0.        ;_mx[3][2]=+shc*nxplny;_mx[3][3]= chc-shc*bz;
      break;
    }
  return *this;
}

// lorentz boost in x direction
SpinHalfLorentzRotation & SpinHalfLorentzRotation::setBoostX (double & bx)
{
  // work out beta and chi
  double chi(atanh(bx)),shc(sinh(0.5*chi)),chc(cosh(0.5*chi));
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      _mx[0][0]= chc;_mx[0][1]= 0. ;_mx[0][2]= 0. ;_mx[0][3]= shc;
      _mx[1][0]= 0. ;_mx[1][1]= chc;_mx[1][2]= shc;_mx[1][3]= 0. ;
      _mx[2][0]= 0. ;_mx[2][1]= shc;_mx[2][2]= chc;_mx[2][3]= 0. ;
      _mx[3][0]= shc;_mx[3][1]= 0. ;_mx[3][2]= 0. ;_mx[3][3]= chc;
      break;
      // helas
    case HELASDRep:
      _mx[0][0]= chc;_mx[0][1]=-shc;_mx[0][2]= 0. ;_mx[0][3]= 0. ;
      _mx[1][0]=-shc;_mx[1][1]= chc;_mx[1][2]= 0. ;_mx[1][3]= 0. ;
      _mx[2][0]= 0  ;_mx[2][1]= 0. ;_mx[2][2]= chc;_mx[2][3]=+shc;
      _mx[3][0]= 0  ;_mx[3][1]= 0. ;_mx[3][2]=+shc;_mx[3][3]= chc;
      break;
    }
  return *this;
}

// lorentz boost in y direction
SpinHalfLorentzRotation & SpinHalfLorentzRotation::setBoostY (double & by)
{
  // work out beta and chi
  double chi(atanh(by)),chc(cosh(0.5*chi));
  Complex shc(0.,sinh(0.5*chi));
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      _mx[0][0]= chc;_mx[0][1]= 0. ;_mx[0][2]= 0. ;_mx[0][3]=-shc;
      _mx[1][0]= 0  ;_mx[1][1]= chc;_mx[1][2]= shc;_mx[1][3]= 0  ;
      _mx[2][0]= 0. ;_mx[2][1]=-shc;_mx[2][2]= chc;_mx[2][3]= 0. ;
      _mx[3][0]= shc;_mx[3][1]= 0. ;_mx[3][2]= 0. ;_mx[3][3]= chc;
      break;
      // helas
    case HELASDRep:
      _mx[0][0]= chc;_mx[0][1]= shc;_mx[0][2]= 0. ;_mx[0][3]= 0. ;
      _mx[1][0]=-shc;_mx[1][1]= chc;_mx[1][2]= 0. ;_mx[1][3]= 0  ;
      _mx[2][0]= 0. ;_mx[2][1]= 0. ;_mx[2][2]= chc;_mx[2][3]=-shc;
      _mx[3][0]= 0. ;_mx[3][1]= 0. ;_mx[3][2]=+shc;_mx[3][3]= chc;
      break;
    }
  return *this;
}

// lorentz boost in z direction 
SpinHalfLorentzRotation & SpinHalfLorentzRotation::setBoostZ (double & bz)
{
  // work out beta and chi
  double chi(atanh(bz)),shc(sinh(0.5*chi)),chc(cosh(0.5*chi));
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      _mx[0][0]= chc ;_mx[0][1]= 0  ;_mx[0][2]= shc;_mx[0][3]= 0. ;
      _mx[1][0]= 0.  ;_mx[1][1]= chc;_mx[1][2]= 0. ;_mx[1][3]=-shc;
      _mx[2][0]= shc ;_mx[2][1]= 0. ;_mx[2][2]= chc;_mx[2][3]= 0  ;
      _mx[3][0]= 0.  ;_mx[3][1]= shc;_mx[3][2]= 0. ;_mx[3][3]= chc;
      break;
      // helas
    case HELASDRep:
      _mx[0][0]= chc-shc;_mx[0][1]= 0.     ;_mx[0][2]= 0.        ;_mx[0][3]= 0.     ;
      _mx[1][0]= 0.     ;_mx[1][1]= chc+shc;_mx[1][2]= 0.        ;_mx[1][3]= 0.     ;
      _mx[2][0]= 0.     ;_mx[2][1]= 0.     ;_mx[2][2]= chc+shc   ;_mx[2][3]= 0.     ;
      _mx[3][0]= 0.     ;_mx[3][1]= 0.     ;_mx[3][2]=+0.        ;_mx[3][3]= chc-shc;
      break;
    }
  return *this;
}

// Pure boost along the x-axis; equivalent to LT = BoostX(beta) * LT
SpinHalfLorentzRotation & SpinHalfLorentzRotation::boostX(double bx)
{
  double chi(atanh(bx)),shc(sinh(0.5*chi)),chc(cosh(0.5*chi));
  Complex temp[4][4];
  unsigned int ix,iy;
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      for(ix=0;ix<4;++ix)
	{
	  temp[0][ix]= chc*_mx[0][ix]+shc*_mx[3][ix];
	  temp[1][ix]= chc*_mx[1][ix]+shc*_mx[2][ix];
	  temp[2][ix]= chc*_mx[2][ix]+shc*_mx[1][ix];
	  temp[3][ix]= chc*_mx[3][ix]+shc*_mx[0][ix];
	}
      break;
      // helas
    case HELASDRep:
      for(ix=0;ix<4;++ix)
	{
	  temp[0][ix]= chc*_mx[0][ix]-shc*_mx[1][ix];
	  temp[1][ix]= chc*_mx[1][ix]-shc*_mx[0][ix];
	  temp[2][ix]= chc*_mx[2][ix]+shc*_mx[3][ix];
	  temp[3][ix]= chc*_mx[3][ix]+shc*_mx[2][ix];
	}
      break;
    }
  for(ix=0;ix<4;++ix){for(iy=0;iy<4;++iy){_mx[ix][iy]=temp[ix][iy];}}
  return *this;
}
// Pure boost along the y-axis; equivalent to LT = BoostY(beta) * LT
SpinHalfLorentzRotation & SpinHalfLorentzRotation::boostY(double by)
{
  double chi(atanh(by)),chc(cosh(0.5*chi));
  Complex shc(0.,sinh(0.5*chi));
  Complex temp[4][4];
  unsigned int ix,iy;
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      for(ix=0;ix<4;++ix)
	{
	  temp[0][ix]= chc*_mx[0][ix]-shc*_mx[3][ix];
	  temp[1][ix]= chc*_mx[1][ix]+shc*_mx[2][ix];
	  temp[2][ix]= chc*_mx[2][ix]-shc*_mx[1][ix];
	  temp[3][ix]= chc*_mx[3][ix]+shc*_mx[0][ix];
	}
      break;
      // helas
    case HELASDRep:
      for(ix=0;ix<4;++ix)
	{
	  temp[0][ix]= chc*_mx[0][ix]+shc*_mx[1][ix];
	  temp[1][ix]= chc*_mx[1][ix]-shc*_mx[0][ix];
	  temp[2][ix]= chc*_mx[2][ix]-shc*_mx[3][ix];
	  temp[3][ix]= chc*_mx[3][ix]+shc*_mx[2][ix];
	}
      break;
    }
  for(ix=0;ix<4;++ix){for(iy=0;iy<4;++iy){_mx[ix][iy]=temp[ix][iy];}}
  return *this;
}

// Pure boost along the z-axis; equivalent to LT = BoostX(beta) * LT
SpinHalfLorentzRotation & SpinHalfLorentzRotation::boostZ(double bz)
{
  double chi(atanh(bz)),shc(sinh(0.5*chi)),chc(cosh(0.5*chi));
  Complex temp[4][4];
  unsigned int ix,iy;
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      for(ix=0;ix<4;++ix)
	{
	  temp[0][ix]= chc*_mx[0][ix]+shc*_mx[2][ix];
	  temp[1][ix]= chc*_mx[1][ix]-shc*_mx[3][ix];
	  temp[2][ix]= shc*_mx[0][ix]+chc*_mx[2][ix];
	  temp[3][ix]= shc*_mx[1][ix]+chc*_mx[3][ix];
	}
      break;
      // helas
    case HELASDRep:
      for(ix=0;ix<4;++ix)
	{
	  temp[0][ix]=(chc-shc)*_mx[0][ix];
	  temp[1][ix]=(chc+shc)*_mx[1][ix];
	  temp[2][ix]=(chc+shc)*_mx[2][ix];
	  temp[3][ix]=( chc-shc)*_mx[3][ix];
	}
      break;
    }
  for(ix=0;ix<4;++ix){for(iy=0;iy<4;++iy){_mx[ix][iy]=temp[ix][iy];}}
  return *this;
}

// General boost equivalent to LT = Boost(bx,by,bz) * LT
SpinHalfLorentzRotation & SpinHalfLorentzRotation::boost(double bx, double by, double bz)
{
  // work out beta and chi
  static double eps=1e-10;
  double beta(sqrt(bx*bx+by*by+bz*bz)),chi(atanh(beta)),chc(cosh(0.5*chi)),shc(0.5);
  if(beta>eps){shc=sinh(0.5*chi)/beta;}
  Complex ii(0.,1.),nxminy(bx-ii*by),nxplny(bx+ii*by),temp[4][4];
  unsigned int ix,iy;
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      for(ix=0;ix<4;++ix)
	{
	  temp[0][ix]=chc*_mx[0][ix]+shc*bz    *_mx[2][ix]+shc*nxminy*_mx[3][ix];
	  temp[1][ix]=chc*_mx[1][ix]+shc*nxplny*_mx[2][ix]-shc*bz    *_mx[3][ix];
	  temp[2][ix]=chc*_mx[2][ix]+shc*bz    *_mx[0][ix]+shc*nxminy*_mx[1][ix];
	  temp[3][ix]=chc*_mx[3][ix]+shc*nxplny*_mx[0][ix]+shc*bz    *_mx[1][ix];
	}
      break;
      // helas
    case HELASDRep:
      for(ix=0;ix<4;++ix)
	{
	  temp[0][ix]= (chc-shc*bz)*_mx[0][ix]-shc*nxminy  *_mx[1][ix];
	  temp[1][ix]=-shc*nxplny  *_mx[0][ix]+(chc+shc*bz)*_mx[1][ix];
	  temp[2][ix]= (chc+shc*bz)*_mx[2][ix]+shc*nxminy  *_mx[3][ix];
	  temp[3][ix]= shc*nxplny  *_mx[2][ix]+(chc-shc*bz)*_mx[3][ix];
	}
      break;
    }
  for(ix=0;ix<4;++ix){for(iy=0;iy<4;++iy){_mx[ix][iy]=temp[ix][iy];}}
  return *this;
}

// General boost equivalent to LT = Boost(bv) * LT
SpinHalfLorentzRotation & SpinHalfLorentzRotation::boost(const Boost & b)
{
  // work out beta and chi
  static double eps=1e-10;
  double bx(b.x()),by(b.y()),bz(b.z());
  double beta(b.mag()),chi(atanh(beta)),chc(cosh(0.5*chi)),shc(0.5);
  if(beta>eps){shc=sinh(0.5*chi)/beta;}
  Complex ii(0.,1.),nxminy(bx-ii*by),nxplny(bx+ii*by),temp[4][4];
  unsigned int ix,iy;
  switch(defaultDRep)
    {
      // haber low energy
    case HaberDRep:
      for(ix=0;ix<4;++ix)
	{
	  temp[0][ix]=chc*_mx[0][ix]+shc*bz    *_mx[2][ix]+shc*nxminy*_mx[3][ix];
	  temp[1][ix]=chc*_mx[1][ix]+shc*nxplny*_mx[2][ix]-shc*bz    *_mx[3][ix];
	  temp[2][ix]=chc*_mx[2][ix]+shc*bz    *_mx[0][ix]+shc*nxminy*_mx[1][ix];
	  temp[3][ix]=chc*_mx[3][ix]+shc*nxplny*_mx[0][ix]+shc*bz    *_mx[1][ix];
	}
      break;
      // helas
    case HELASDRep:
      for(ix=0;ix<4;++ix)
	{
	  temp[0][ix]= (chc-shc*bz)*_mx[0][ix]-shc*nxminy  *_mx[1][ix];
	  temp[1][ix]=-shc*nxplny  *_mx[0][ix]+(chc+shc*bz)*_mx[1][ix];
	  temp[2][ix]= (chc+shc*bz)*_mx[2][ix]+shc*nxminy  *_mx[3][ix];
	  temp[3][ix]= shc*nxplny  *_mx[2][ix]+(chc-shc*bz)*_mx[3][ix];
	}
      break;
    }
  for(ix=0;ix<4;++ix){for(iy=0;iy<4;++iy){_mx[ix][iy]=temp[ix][iy];}}
  return *this;
}

std::ostream & SpinHalfLorentzRotation::print( std::ostream & os ) const {
  os << "\n   [ ( " <<
    std::setw(14) << std::setprecision(6) << s1s1() << "   " <<
    std::setw(14) << std::setprecision(6) << s1s2() << "   " <<
    std::setw(14) << std::setprecision(6) << s1s3() << "   " <<
    std::setw(14) << std::setprecision(6) << s1s4() << ")\n"
     << "     ( " <<
    std::setw(14) << std::setprecision(6) << s2s1() << "   " <<
    std::setw(14) << std::setprecision(6) << s2s2() << "   " <<
    std::setw(14) << std::setprecision(6) << s2s3() << "   " <<
    std::setw(14) << std::setprecision(6) << s2s4() << ")\n"
     << "     ( " <<
    std::setw(14) << std::setprecision(6) << s3s1() << "   " <<
    std::setw(14) << std::setprecision(6) << s3s2() << "   " <<
    std::setw(14) << std::setprecision(6) << s3s3() << "   " <<
    std::setw(14) << std::setprecision(6) << s3s4() << ")\n"
     << "     ( " <<
    std::setw(14) << std::setprecision(6) << s4s1() << "   " <<
    std::setw(14) << std::setprecision(6) << s4s2() << "   " <<
    std::setw(14) << std::setprecision(6) << s4s3() << "   " <<
    std::setw(14) << std::setprecision(6) << s4s4() << ") ]\n";
  return os;
}
