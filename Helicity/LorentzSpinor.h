// -*- C++ -*-
#ifndef ThePEG_LorentzSpinor_H
#define ThePEG_LorentzSpinor_H
// This is the declaration of the LorentzSpinor class.
#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Config/Complex.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/CLHEPWrap/ThreeVector.h"
#include "HelicityDefinitions.h"
#include "LorentzSpinor.fh"
#include "LorentzSpinorBar.h"
#include "LorentzPolarizationVector.h"

namespace ThePEG{
namespace Helicity{

/**
 *  The LorentzSpinor class is designed to store a spinor. In addition
 *  to storing the components of the spinor, information is stored on
 *  the representation of the Dirac matrices used in calculating the
 *  spinor and the type of spinor, for example u or v type.
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
 *  The LorentzSpinorBar class is also provided to store the barred
 *  spinor.
 *
 * @see LorentzSpinorBar
 *
 * @author Peter Richardson
 *
 */
class LorentzSpinor {

public:

  /** @name Standard constructors. */
  //@{
  /**
   * Default zero constructor, optionally specifying \a t, the type
   * and \a r, the choice of dirac matrix.
   */
  inline LorentzSpinor(SpinorType t = unknown_spinortype,
		       DiracRep r = defaultDRep);

  /**
   * Default zero constructor, optionally specifying the choice of
   * dirac matrix.
   */
  inline LorentzSpinor(DiracRep);

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying \a t, the type and \a r, the choice of
   * dirac matrix.
   */
  inline LorentzSpinor(Complex,Complex,Complex,Complex,
		       SpinorType t = unknown_spinortype,
		       DiracRep r = defaultDRep);

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying the choice of dirac matrix
   */
  inline LorentzSpinor(Complex,Complex,Complex,Complex,DiracRep);
  //@}

  /** @name Access the components. */
  //@{
  /**
   * Subscript operator to return spinor components
   */
  inline Complex operator[](int) const;

  /**
   * Subscript operator to return spinor components
   */
  inline Complex operator()(int) const;

  /**
   * Set components by index.
   */
  inline Complex & operator()(int);

  /**
   * Set components by index.
   */
  inline Complex & operator[](int);

  /**
   * Get first component.
   */
  inline Complex s1() const;

  /**
   * Get second component.
   */
  inline Complex s2() const;

  /**
   * Get third component.
   */
  inline Complex s3() const;

  /**
   * Get fourth component.
   */
  inline Complex s4() const;

  /**
   * Set first component.
   */
  inline void setS1(Complex);

  /**
   * Set second component.
   */
  inline void setS2(Complex);

  /**
   * Set third component.
   */
  inline void setS3(Complex);

  /**
   * Set fourth component.
   */
  inline void setS4(Complex);
  //@}

  /**
   * The assignment operator.
   */
  inline LorentzSpinor & operator = (const LorentzSpinor &);

  /** @name Transformations. */
  //@{
  /**
   * Return the barred spinor
   */
  LorentzSpinorBar bar();

  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzSpinor & boost(double,double,double);

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  LorentzSpinor & boost(const Hep3Vector &);

  /**
   * General Lorentz transformation
   */
  LorentzSpinor & transform(const SpinHalfLorentzRotation & );

  /**
   * General Lorentz transformation
   */
  inline LorentzSpinor & transform(const LorentzRotation &);
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
  inline LorentzSpinor transformRep(DiracRep) const;

  /**
   * Return the representation of the spinor.
   */
  inline const DiracRep Rep() const;

  /**
   * Return the type of the spinor.
   */
  inline const SpinorType Type() const;
  //@}


  /** @name Functions to calculate certain currents. */
  //@{
  /**
   *  Calculate the left-handed current \f$\bar{f}\gamma^\mu P_Lf\f$.
   * @param fbar The barred spinor.
   */
  inline LorentzPolarizationVector leftCurrent(const LorentzSpinorBar& fbar) const;
  /**
   *  Calculate the right-handed current \f$\bar{f}\gamma^\mu P_Rf\f$.
   * @param fbar The barred spinor.
   */
  inline LorentzPolarizationVector rightCurrent(const LorentzSpinorBar& fbar) const;
  /**
   *  Calculate the vector current \f$\bar{f}\gamma^\mu f\f$
   * @param fbar The barred spinor.
   */
  inline LorentzPolarizationVector vectorCurrent(const LorentzSpinorBar& fbar) const;

  /**
   * Calculate a general current with arbitary left and right couplings,
   * i.e. \f$\bar{f}\gamma^\mu(c_lP_L+c_RP_R)f\f$
   * @param fbar The barred spinor.
   * @param left The left coupling, \f$c_L\f$.
   * @param right The right coupling, \f$c_R\f$.
   */
  inline LorentzPolarizationVector generalCurrent(const LorentzSpinorBar& fbar,
						  Complex left, Complex right) const;
  //@}

  /** @name Functions to calculate certain scalars. */
  //@{
  /**
   * Calculate the left-handed scalar \f$\bar{f}P_Lf\f$.
   * @param fbar The barred spinor.
   */
  inline Complex leftScalar(const LorentzSpinorBar& fbar) const;

  /**
   * Calculate the right-handed scalar \f$\bar{f}P_Rf\f$.
   * @param fbar The barred spinor.
   */
  inline Complex rightScalar(const LorentzSpinorBar& fbar) const;

  /**
   *  Calculate the scalar \f$\bar{f}f\f$.
   * @param fbar The barred spinor.
   */
  inline Complex scalar(const LorentzSpinorBar& fbar) const;
  /**
   *  Calculate the pseudoscalar \f$\bar{f}\gamma_5f\f$.
   * @param fbar The barred spinor.
   */
  inline Complex pseudoScalar(const LorentzSpinorBar& fbar) const;

  /**
   * Calculate a general scalar product with arbitary left and right couplings,
   * i.e. \f$\bar{f}c_lP_L+c_RP_Rf\f$
   * @param fbar The barred spinor.
   * @param left The left coupling, \f$c_L\f$.
   * @param right The right coupling, \f$c_R\f$.
   */
  inline Complex generalScalar(const LorentzSpinorBar& fbar,
			       Complex left, Complex right) const;
  //@}

private:

  /**
   * Storage of the components.
   */
  Complex _spin[4];

  /**
   * Definition of the Dirac matrices used.
   */
  DiracRep _dirac;

  /**
   * Type of spinor
   */
  SpinorType _type;

};

}
}

#include "LorentzSpinor.icc"

#endif

