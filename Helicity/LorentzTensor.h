// header file for the LorentzTensors
#ifndef ThePEG_LorentzTensor_H
#define ThePEG_LorentzTensor_H
#include <complex>
#include "LorentzPolarizationVector.h"
namespace ThePEG {
  namespace Helicity {
    using std::complex;
    class LorentzTensor{
    public:
      // constructors 
      inline LorentzTensor();
      // default zero constructor
      LorentzTensor(complex<double>,complex<double>,complex<double>,complex<double>,
		    complex<double>,complex<double>,complex<double>,complex<double>,
		    complex<double>,complex<double>,complex<double>,complex<double>,
		    complex<double>,complex<double>,complex<double>,complex<double>);
      // constructor specifyign all components
      inline LorentzTensor(LorentzPolarizationVector, LorentzPolarizationVector);
      // constructor in terms of two polarization vectors
      inline complex<double> xx() const;
      inline complex<double> yx() const;
      inline complex<double> zx() const;
      inline complex<double> tx() const;
      inline complex<double> xy() const;
      inline complex<double> yy() const;
      inline complex<double> zy() const;
      inline complex<double> ty() const;
      inline complex<double> xz() const;
      inline complex<double> yz() const;
      inline complex<double> zz() const;
      inline complex<double> tz() const;
      inline complex<double> xt() const;
      inline complex<double> yt() const;
      inline complex<double> zt() const;
      inline complex<double> tt() const;
      // Get components
      
      inline void setXX(complex<double>);
      inline void setYX(complex<double>);
      inline void setZX(complex<double>);
      inline void setTX(complex<double>);
      inline void setXY(complex<double>);
      inline void setYY(complex<double>);
      inline void setZY(complex<double>);
      inline void setTY(complex<double>);
      inline void setXZ(complex<double>);
      inline void setYZ(complex<double>);
      inline void setZZ(complex<double>);
      inline void setTZ(complex<double>);
      inline void setXT(complex<double>);
      inline void setYT(complex<double>);
      inline void setZT(complex<double>);
      inline void setTT(complex<double>);
      // Set components.
      inline complex<double> operator () (int,int) const;
      // Get components by index.
      
      inline complex<double> & operator () (int,int);
      // Set components by index.
      
      
      inline LorentzTensor & operator = (const LorentzTensor &);
      // Assignment. 
      
    private:
      complex<double> _tensor[4][4];
    };
#include "LorentzTensor.icc"
  }
}
#endif
