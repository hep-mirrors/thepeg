// -*- C++ -*-
#ifndef ThePEG_LorentzPolarizationVector_H
#define ThePEG_LorentzPolarizationVector_H
//
// This is the declaration of the <!id>LorentzPolarizationVector<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
//
// Author: Peter Richardson
//

#include "ThePEG/Config/Complex.h"
#include "ThePEG/CLHEPWrap/LorentzVector.h"
#include "ThePEG/CLHEPWrap/Lorentz5Vector.h"
#include "ThePEG/CLHEPWrap/ThreeVector.h"

namespace ThePEG {
namespace Helicity {

class LorentzPolarizationVector {

public:
  inline LorentzPolarizationVector(Complex x, Complex y,
				   Complex z, Complex t);
  // Constructor giving the components x, y, z, t.
      
  inline LorentzPolarizationVector(Complex x, Complex y,
				   Complex z);
  // Constructor giving the components x, y, z with t-component set to 0.0.
      
  inline LorentzPolarizationVector(Complex t);
  // Constructor giving the t-component with x,y,z set to 0.0.
      
  inline LorentzPolarizationVector();
  // Default Constructor zero everything
      
  inline LorentzPolarizationVector(const LorentzVector &);
  // setup from a LorentzVector
      
  inline LorentzPolarizationVector(const LorentzPolarizationVector &);
  // copy constructor
      
  inline ~LorentzPolarizationVector();
  // The destructor
      
  inline Complex x() const;
  inline Complex y() const;
  inline Complex z() const;
  inline Complex t() const;
  // Get position and time.
      
  inline void setX(Complex);
  inline void setY(Complex);
  inline void setZ(Complex);
  inline void setT(Complex);
  // Set position and time.
      
  inline Complex operator () (int) const;
  inline Complex operator [] (int) const;
  // Get components by index.
  
  inline Complex & operator () (int);
  inline Complex & operator [] (int);
  // Set components by index.
  
  inline LorentzPolarizationVector &
  operator = (const LorentzPolarizationVector &);
  // Assignment. 
      
  inline LorentzPolarizationVector
  operator +  (const LorentzPolarizationVector &) const;
  inline LorentzPolarizationVector &
  operator += (const LorentzPolarizationVector &);
  // Additions.
      
  inline LorentzPolarizationVector 
  operator -  (const LorentzPolarizationVector &) const;
  inline LorentzPolarizationVector &
  operator -= (const LorentzPolarizationVector &);
  // Subtractions.
      
  inline LorentzPolarizationVector operator - () const;
  // Unary minus.
  
  inline LorentzPolarizationVector & operator *= (Complex);
  // Scaling with complex numbers.
  
  LorentzPolarizationVector & operator /= (Complex);
  // Dividing LorentzVector by a complex number
  
  inline bool operator == (const LorentzPolarizationVector &) const;
  inline bool operator != (const LorentzPolarizationVector &) const;
  // Comparisons.
  
  inline Complex dot(const LorentzVector &) const;
  inline Complex operator * (const LorentzVector &) const;
  // Scalar product with momentum.
  
  inline Complex dot(const LorentzPolarizationVector &) const;
  inline Complex operator * (const LorentzPolarizationVector &) const;
  // Scalar product with other polarization.
  
  
  LorentzPolarizationVector & boostX( double beta );
  // boost along x direction
  LorentzPolarizationVector & boostY( double beta );
  // boost along y direction
  LorentzPolarizationVector & boostZ( double beta );
  // boost along z direction
  
  LorentzPolarizationVector & boost(double, double, double);
  inline LorentzPolarizationVector & boost(const Hep3Vector &);
  // Lorentz boost.
  
  inline LorentzPolarizationVector &
  boost ( const Hep3Vector & axis,  double beta );
  // Normalizes the Hep3Vector to define a direction, and uses beta to
  // define the magnitude of the boost.
  
  LorentzPolarizationVector & rotateX(double);
  // Rotate the spatial component around the x-axis.
  
  LorentzPolarizationVector & rotateY(double);
  // Rotate the spatial component around the y-axis.
  
  LorentzPolarizationVector & rotateZ(double);
  // Rotate the spatial component around the z-axis.
  
  LorentzPolarizationVector &  rotateUz(const Hep3Vector &);
  // Rotates the reference frame from Uz to newUz (unit vector).
  
  LorentzPolarizationVector & rotate(double, const Hep3Vector &);
  // Rotate the spatial component around specified axis.
  
  LorentzPolarizationVector conjugate();
private:
  Complex _vec[4];
};


inline LorentzPolarizationVector operator / 
(const LorentzPolarizationVector &, Complex a);
inline LorentzPolarizationVector operator *
(Complex a,const LorentzPolarizationVector &);
// multiplication by  scalar
inline LorentzPolarizationVector operator *
(Complex a,const Lorentz5Momentum &);
// Dividing LorentzVector by a complex number

// some more functions functions
inline LorentzPolarizationVector boostXOf
( const LorentzPolarizationVector & vec, double beta );
inline LorentzPolarizationVector boostYOf
( const LorentzPolarizationVector & vec, double beta );
inline LorentzPolarizationVector boostZOf
( const LorentzPolarizationVector & vec, double beta );
inline LorentzPolarizationVector  boostOf
( const LorentzPolarizationVector & vec, const Hep3Vector & betaVector );
inline LorentzPolarizationVector  boostOf
( const LorentzPolarizationVector & vec, const Hep3Vector & axis,  double beta );

}
}

#include "LorentzPolarizationVector.icc"

#endif
