// header file for the Lorentz SpinorBar class
#ifndef ThePEG_LorentzSpinorBar_H
#define ThePEG_LorentzSpinorBar_H
#include <complex>
#include <iostream>
#include "ThePEG/Helicity/HelicityDefinitions.h"
#include "CLHEP/Vector/ThreeVector.h"
namespace ThePEG {
  namespace Helicity {
    using std::complex;
    using std::cerr;
    using std::endl;
    class LorentzSpinor;
    class LorentzSpinorBar
      {
      public:
	// default zero constructor
	LorentzSpinorBar();
	// constructor with complex numbers
	LorentzSpinorBar(complex<double>,complex<double>,
			 complex<double>,complex<double>);
	// subscript operator to return spinor components
	inline complex<double> operator[](int) const;
	inline complex<double> operator()(int) const;
	// Set components by index.
	inline complex<double> & operator () (int);
	inline complex<double> & operator [] (int);
	// Get components
	inline complex<double> s1() const;
	inline complex<double> s2() const;
	inline complex<double> s3() const;
	inline complex<double> s4() const;
	// Set components
	inline void setS1(complex<double>);
	inline void setS2(complex<double>);
	inline void setS3(complex<double>);
	inline void setS4(complex<double>);
	// return the unbarred spinor
	LorentzSpinor bar();
	// the equals operator
	inline LorentzSpinorBar & operator = (const LorentzSpinorBar &);
	// boost 
	inline LorentzSpinorBar boost(double,double,double) const;
	inline LorentzSpinorBar boost(const Hep3Vector &) const;
  // Assignment. 
      private:
	complex<double> _spin[4];
      };
#include "LorentzSpinorBar.icc"
  }
}
#endif
