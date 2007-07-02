// -*- C++ -*-
#ifndef ThePEG_LorentzRSSpinorBar_H
#define ThePEG_LorentzRSSpinorBar_H
// This is the declaration of the LorentzRSSpinorBar class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Config/Complex.h"
#include "ThePEG/CLHEPWrap/ThreeVector.h"
#include "HelicityDefinitions.h"
#include "LorentzRSSpinor.fh"
#include "LorentzRSSpinorBar.fh"
#include "LorentzSpinorBar.h"
#include "LorentzSpinor.h"
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
template <typename Value>
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
  LorentzRSSpinorBar(complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		     complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		     complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		     complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		     SpinorType t=unknown_spinortype, DiracRep r=defaultDRep);
  
  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying the choice of dirac matrix
   */
  LorentzRSSpinorBar(complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		     complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		     complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		     complex<Value>,complex<Value>,complex<Value>,complex<Value>,DiracRep);
  //@}

  /** @name Access the components. */
  //@{
  /**
   * Subscript operator to return spinor components
   */
  inline complex<Value> operator()(int,int) const;

  /**
   * Set components by index
   */
  inline complex<Value> & operator () (int,int);

  /**
   * Get first spinor component for the x vector
   */
  inline complex<Value> xs1() const;

  /**
   * Get second spinor component for the x vector
   */
  inline complex<Value> xs2() const;

  /**
   * Get third  spinor component for the x vector
   */
  inline complex<Value> xs3() const;

  /**
   * Get fourth  spinor component for the x vector
   */
  inline complex<Value> xs4() const;

  /**
   * Get first spinor component for the y vector
   */
  inline complex<Value> ys1() const;

  /**
   * Get second spinor component for the y vector
   */
  inline complex<Value> ys2() const;
  
  /**
   * Get third spinor component for the y vector
   */
  inline complex<Value> ys3() const;
  
  /**
   * Get fourth spinor component for the y vector
   */
  inline complex<Value> ys4() const;
  
  /**
   * Get first spinor component for the z vector
   */
  inline complex<Value> zs1() const;
  
  /**
   * Get second spinor component for the z vector
   */
  inline complex<Value> zs2() const;
  
  /**
   * Get third spinor component for the z vector
   */
  inline complex<Value> zs3() const;
  
  /**
   * Get fourth spinor component for the z vector
   */
  inline complex<Value> zs4() const;
  
  /**
   * Get first spinor component for the t vector
   */
  inline complex<Value> ts1() const;
  
  /**
   * Get second spinor component for the t vector
   */
  inline complex<Value> ts2() const;
  
  /**
   * Get third spinor component for the t vector
   */
  inline complex<Value> ts3() const;
  
  /**
   * Get fourth spinor component for the t vector
   */
  inline complex<Value> ts4() const;
  
  /**
   * Set first spinor component for the x vector
   */
  inline void setXS1(complex<Value>);
  
  /**
   * Set second spinor component for the x vector
   */
  inline void setXS2(complex<Value>);
  
  /**
   * Set third spinor component for the x vector
   */
  inline void setXS3(complex<Value>);
  
  /**
   * Set fourth spinor component for the x vector
   */
  inline void setXS4(complex<Value>);
  
  /**
   * Set first spinor component for the y vector
   */
  inline void setYS1(complex<Value>);
  
  /**
   * Set second spinor component for the y vector
   */
  inline void setYS2(complex<Value>);
  
  /**
   * Set third spinor component for the y vector
   */
  inline void setYS3(complex<Value>);
  
  /**
   * Set fourth spinor component for the y vector
   */
  inline void setYS4(complex<Value>);
  
  /**
   * Set first spinor component for the z vector
   */
  inline void setZS1(complex<Value>);
  
  /**
   * Set second spinor component for the z vector
   */
  inline void setZS2(complex<Value>);
  
  /**
   * Set third spinor component for the z vector
   */
  inline void setZS3(complex<Value>);
  
  /**
   * Set fourth spinor component for the z vector
   */
  inline void setZS4(complex<Value>);
  
  /**
   * Set first spinor component for the t vector
   */
  inline void setTS1(complex<Value>);
  
  /**
   * Set second spinor component for the t vector
   */
  inline void setTS2(complex<Value>);
  
  /**
   * Set third spinor component for the t vector
   */
  inline void setTS3(complex<Value>);
  
  /**
   * Set fourth spinor component for the t vector
   */
  inline void setTS4(complex<Value>);
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
  inline LorentzSpinorBar<Value> dot(const LorentzPolarizationVector &) const;

  /**
   * dot product with a 4-momentum
   */
  inline LorentzSpinorBar<Value> dot(const LorentzMomentum &) const;
  //@}

  /** @name Transformations. */
  //@{
  /**
   * return the barred spinor
   */
  LorentzRSSpinor<Value> bar();

  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzRSSpinorBar & boost(double,double,double);

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  LorentzRSSpinorBar & boost(const Boost &);

  /**
   * General transform
   */
  LorentzRSSpinorBar & transform(const LorentzRotation &);
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

  /**
   * Current \f$\bar{f}^\alpha(c_LP_L+c_RP_R)f\f$ for general couplings.
   * @param f The unbarred spinor
   * @param left The left-handed coupling, \f$c_L\f$.
   * @param right The right-handed coupling, \f$c_R\f$.
   */
  template <typename ValueB>
  inline LorentzVector<complex<
    typename BinaryOpTraits<Value,ValueB>::MulT> >
  generalCurrent(LorentzSpinor<ValueB>& f, Complex left, Complex right);
private:

  /**
   * Storage of the components.
   */
  complex<Value> _spin[4][4];

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
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "LorentzRSSpinorBar.tcc"
#endif 

#endif
