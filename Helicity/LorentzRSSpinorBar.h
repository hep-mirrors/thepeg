// -*- C++ -*-
#ifndef ThePEG_LorentzRSSpinorBar_H
#define ThePEG_LorentzRSSpinorBar_H
// This is the declaration of the LorentzRSSpinorBar class.

#include "ThePEG/Config/Complex.h"
#include "ThePEG/CLHEPWrap/ThreeVector.h"
#include "HelicityDefinitions.h"
#include "LorentzRSSpinor.fh"
#include "LorentzRSSpinorBar.fh"
#include "LorentzSpinorBar.h"
#include "LorentzPolarizationVector.h"

namespace ThePEG {
namespace Helicity {

/**
 *  The <code>LorentzRSSpinorBar</code> class implements the storage of a
 *  barred Lorentz Rarita-Schwinger Spinor for a spin-3/2 particle.
 *  The design is based on that of the
 *  <code>LorentzRSSpinor</code> class and the details of the implemented
 *  are discussed in more detail in the header file for that class.
 *
 * @see LorentzRSSpinor
 *
 * \author Peter Richardson
 *
 */
class LorentzRSSpinorBar {

public:

  /** @name Standard constructors. */
  //@{
  /**
   * Default zero constructor, optionally specifying \a t, the type
   * and \a r, the choice of dirac matrix.
   */
  LorentzRSSpinorBar(SpinorType t = unknown_spinortype,
		     DiracRep r = defaultDRep);

  /**
   * Default zero constructor, optionally specifying the choice of
   * dirac matrix.
   */
  LorentzRSSpinorBar(DiracRep);

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying \a t, the type and \a r, the choice of
   * dirac matrix.
   */
  LorentzRSSpinorBar(Complex,Complex,Complex,Complex,
		     Complex,Complex,Complex,Complex,
		     Complex,Complex,Complex,Complex,
		     Complex,Complex,Complex,Complex,
		     SpinorType t=unknown_spinortype, DiracRep r=defaultDRep);
  
  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying the choice of dirac matrix
   */
  LorentzRSSpinorBar(Complex,Complex,Complex,Complex,
		     Complex,Complex,Complex,Complex,
		     Complex,Complex,Complex,Complex,
		     Complex,Complex,Complex,Complex,DiracRep);
  //@}

  /** @name Access the components. */
  //@{
  /**
   * Subscript operator to return spinor components
   */
  inline Complex operator()(int,int) const;

  /**
   * Set components by index
   */
  inline Complex & operator () (int,int);

  /**
   * Get first spinor component for the x vector
   */
  inline Complex xs1() const;

  /**
   * Get second spinor component for the x vector
   */
  inline Complex xs2() const;

  /**
   * Get third  spinor component for the x vector
   */
  inline Complex xs3() const;

  /**
   * Get fourth  spinor component for the x vector
   */
  inline Complex xs4() const;

  /**
   * Get first spinor component for the y vector
   */
  inline Complex ys1() const;

  /**
   * Get second spinor component for the y vector
   */
  inline Complex ys2() const;
  
  /**
   * Get third spinor component for the y vector
   */
  inline Complex ys3() const;
  
  /**
   * Get fourth spinor component for the y vector
   */
  inline Complex ys4() const;
  
  /**
   * Get first spinor component for the z vector
   */
  inline Complex zs1() const;
  
  /**
   * Get second spinor component for the z vector
   */
  inline Complex zs2() const;
  
  /**
   * Get third spinor component for the z vector
   */
  inline Complex zs3() const;
  
  /**
   * Get fourth spinor component for the z vector
   */
  inline Complex zs4() const;
  
  /**
   * Get first spinor component for the t vector
   */
  inline Complex ts1() const;
  
  /**
   * Get second spinor component for the t vector
   */
  inline Complex ts2() const;
  
  /**
   * Get third spinor component for the t vector
   */
  inline Complex ts3() const;
  
  /**
   * Get fourth spinor component for the t vector
   */
  inline Complex ts4() const;
  
  /**
   * Set first spinor component for the x vector
   */
  inline void setXS1(Complex);
  
  /**
   * Set second spinor component for the x vector
   */
  inline void setXS2(Complex);
  
  /**
   * Set third spinor component for the x vector
   */
  inline void setXS3(Complex);
  
  /**
   * Set fourth spinor component for the x vector
   */
  inline void setXS4(Complex);
  
  /**
   * Set first spinor component for the y vector
   */
  inline void setYS1(Complex);
  
  /**
   * Set second spinor component for the y vector
   */
  inline void setYS2(Complex);
  
  /**
   * Set third spinor component for the y vector
   */
  inline void setYS3(Complex);
  
  /**
   * Set fourth spinor component for the y vector
   */
  inline void setYS4(Complex);
  
  /**
   * Set first spinor component for the z vector
   */
  inline void setZS1(Complex);
  
  /**
   * Set second spinor component for the z vector
   */
  inline void setZS2(Complex);
  
  /**
   * Set third spinor component for the z vector
   */
  inline void setZS3(Complex);
  
  /**
   * Set fourth spinor component for the z vector
   */
  inline void setZS4(Complex);
  
  /**
   * Set first spinor component for the t vector
   */
  inline void setTS1(Complex);
  
  /**
   * Set second spinor component for the t vector
   */
  inline void setTS2(Complex);
  
  /**
   * Set third spinor component for the t vector
   */
  inline void setTS3(Complex);
  
  /**
   * Set fourth spinor component for the t vector
   */
  inline void setTS4(Complex);
  //@}

  /** @name Assignment and arithmetic operators. */
  //@{
  /**
   * The assignment operator
   */
  inline LorentzRSSpinorBar & operator = (const LorentzRSSpinorBar &);

  /**
   * dot product with a polarization vector
   */
  inline LorentzSpinorBar dot(const LorentzPolarizationVector &) const;

  /**
   * dot product with a 4-vector
   */
  inline LorentzSpinorBar dot(const LorentzVector &) const;
  //@}

  /** @name Transformations. */
  //@{
  /**
   * return the barred spinor
   */
  LorentzRSSpinor bar();

  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  inline LorentzRSSpinorBar boost(double,double,double) const;

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  inline LorentzRSSpinorBar boost(const Hep3Vector &) const;
  //@}

  /** @name Functions related to type and representation. */
  //@{
  /**
   * Change the dirac matrix representation.
   */
  inline void changeRep(DiracRep);

  /**
   * Return the spinor in a different representation.
   */
  inline LorentzRSSpinorBar transformRep(DiracRep);

  /**
   * Return the representation of the spinor.
   */
  inline DiracRep Rep();

  /**
   * Return the type of the spinor.
   */
  inline SpinorType Type();
  //@}

private:

  /**
   * Storage of the components.
   */
  Complex _spin[4][4];

  /**
   * Definition of the Dirac matrices used.
   */
  DiracRep _dirac;

  /**
   * Type of spinor.
   */
  SpinorType _type;

};
}
}
#include "LorentzRSSpinorBar.icc"

#endif
