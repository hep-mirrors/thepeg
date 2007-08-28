// -*- C++ -*-
#ifndef ThePEG_LorentzRSSpinor_H
#define ThePEG_LorentzRSSpinor_H

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Vectors/ThreeVector.h"
#include "HelicityDefinitions.h"
#include "LorentzRSSpinor.fh"
#include "LorentzRSSpinorBar.h"
#include "LorentzSpinorBar.h"
#include "LorentzSpinor.h"
#include "LorentzPolarizationVector.h"

namespace ThePEG{
namespace Helicity{

/**
 *  The LorentzRSSpinor class is designed to store a
 *  Rarita-Schwinger spinor for a spin-3/2 particle. In addition
 *  to storing the components of the spinor
 *  information is stored on the representation of the Dirac matrices
 *  used in calculating the spinor and the type of spinor, for example
 *  u or v type.
 *
 *  At the moment only two choices of the Dirac matrix representation
 *  are supported.  These are specified using the DiracRep
 *  enumeration. The first HaberDRep is a low energy representation in
 *  which
 *
 *  \f[
 * \gamma_{i=1,2,3}=\left(\begin{array}{cc}
 *                          0 & \sigma_i \\
 *                          -\sigma_i & 0
 *                        \end{array}\right)
 *          \quad
 * \gamma_0=\left(\begin{array}{cc}
 *                  1 & 0 \\
 *                  0 & -1
 *                \end{array}\right)
 *          \quad
 * \gamma_5=\left(\begin{array}{cc}
 *                  0 & 1 \\
 *                  1 & 0
 *                \end{array}\right)
 * \f]
 *
 *  this choice is perhaps more familiar from undergraduate courses
 *  and is most appropriate for low-energy calculations. However for
 *  high-energy calculations the choice made by the HELAS
 *  collaboration is more efficient for numerical calculations. This
 *  choice is supported as HELASDRep and is recommend for most
 *  calculations. In this representation
 *
 *  \f[
 * \gamma_{i=1,2,3}=\left(\begin{array}{cc}
 *                          0 & \sigma_i \\
 *                          -\sigma_i & 0
 *                        \end{array}\right)
 *          \quad
 * \gamma_0=\left(\begin{array}{cc}
 *                  0 & 1 \\
 *                  1 & 0
 *                \end{array}\right)
 *          \quad
 * \gamma_5=\left(\begin{array}{cc}
 *                  -1 & 0 \\
 *                  0 & 1
 *                \end{array}\right)
 * \f]
 *
 *  These two representations are related by the transformation
 *
 * \f[
 * \psi_{\mbox{HELAS}} = S \psi_{\mbox{Haber}}\quad\mbox{where}\quad
 * S=\frac{1}{\sqrt{2}}\left(\begin{array}{cc}
 *                             1 & -1 \\
 *                             1 & 1
 *                     \end{array}\right)
 * \f]
 *
 *  and this transformation is used in the transformRep(int) member to
 *  return the spinor in whichever of the supported representations is
 *  required or the changeRep(int) member to change the representation
 *  of this spinor.
 *
 *  The file HelicityDefinitions.h contains a default choice for the
 *  representation which should be used if possible.
 *
 *  The type of the spinor is also stored using the SpinorType
 *  enumeration.  There are three types supported u_spinortype,
 *  v_spinortype, unknown_spinortype.  This information is intended
 *  mainly for use in the case of Majorana particles where matrix
 *  elements can be calculated with either u or v type spinors and
 *  knowledge of which was used will be needed in order to give the
 *  correct correlations. The unknown_spinortypee is intended for
 *  cases where either the spinor for an off-shell line in a matrix
 *  element calculation or the information is genuinely unknown.
 *
 *  The LorentzRSSpinorBar class is also provided to store the barred
 *  spinor.
 *
 *
 * @see HelicityDefinitions
 * @see LorentzRSSpinorBar
 *
 * \author Peter Richardson
 *
 */
template<typename Value>
class LorentzRSSpinor {

public:

  /** @name Standard constructors. */
  //@{
  /**
   * Default zero constructor, optionally specifying \a t, the type
   * and \a r, the choice of dirac matrix.
   */
  LorentzRSSpinor(SpinorType t = unknown_spinortype,
		  DiracRep r = defaultDRep);

  /**
   * Default zero constructor, optionally specifying the choice of
   * dirac matrix.
   */
  LorentzRSSpinor(DiracRep);

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying \a t, the type and \a r, the choice of
   * dirac matrix.
   */
  LorentzRSSpinor(complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		  complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		  complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		  complex<Value>,complex<Value>,complex<Value>,complex<Value>,
		  SpinorType t=unknown_spinortype, DiracRep r=defaultDRep);

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying the choice of dirac matrix
   */
  LorentzRSSpinor(complex<Value>,complex<Value>,complex<Value>,complex<Value>,
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

  /** @name Arithmetic operators. */
  //@{
  /**
   * dot product with a polarization vector
   */
  inline LorentzSpinor<Value> dot(const LorentzPolarizationVector &) const;

  /**
   * dot product with a 4-vector
   */
  inline LorentzSpinor<Value> dot(const LorentzMomentum &) const;
  //@}

  /** @name Transformations. */
  //@{
  /**
   * return the barred spinor
   */
  LorentzRSSpinorBar<Value> bar();

  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzRSSpinor & boost(double,double,double);

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  LorentzRSSpinor & boost(const Boost &);

  /**
   * General transform
   */
  LorentzRSSpinor & transform(const LorentzRotation &);
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
  inline LorentzRSSpinor transformRep(DiracRep) const;

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
   * Scalar product \f$\bar{f}^\alpha(c_LP_L+c_RP_R)f_\alpha\f$for general couplings
   * @param fbar The barred spinor
   * @param left The left-handed coupling, \f$c_L\f$.
   * @param right The right-handed coupling, \f$c_R\f$.
   */
  template <typename ValueB>
  inline complex<typename BinaryOpTraits<Value,ValueB>::MulT>
  generalScalar(LorentzRSSpinorBar<ValueB>& fbar, Complex left, Complex right);

  /**
   *  Current \f$\bar{f}(c_LP_L+c_RP_R)f^\alpha\f$ for general couplings.
   * @param fbar The barred spinor
   * @param left The left-handed coupling, \f$c_L\f$.
   * @param right The right-handed coupling, \f$c_R\f$.
   */
  template <typename ValueB>
  inline LorentzVector<complex<
    typename BinaryOpTraits<Value,ValueB>::MulT> >
  generalCurrent(LorentzSpinorBar<ValueB>& fbar, Complex left, Complex right);

private:
  /**
   * Definition of the Dirac matrices used.
   */
  DiracRep _dirac;

  /**
   * Type of spinor
   */
  SpinorType _type;

  /**
   * Storage of the components.
   */
  vector<vector<complex<Value> > > _spin;
};

}
}

#include "LorentzRSSpinor.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "LorentzRSSpinor.tcc"
#endif 

#endif
