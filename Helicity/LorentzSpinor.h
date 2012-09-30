// -*- C++ -*-
//
// LorentzSpinor.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2011 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_LorentzSpinor_H
#define ThePEG_LorentzSpinor_H
// This is the declaration of the LorentzSpinor class.
#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Vectors/LorentzRotation.h"
#include "ThePEG/Vectors/ThreeVector.h"
#include "HelicityDefinitions.h"
#include "LorentzSpinor.fh"
#include "LorentzSpinorBar.h"
#include "LorentzPolarizationVector.h"
#include "LorentzTensor.h"

namespace ThePEG{
namespace Helicity{

/**
 *  The LorentzSpinor class is designed to store a spinor. In addition
 *  to storing the components of the spinor, information is stored on
 *  the representation of the type of spinor, for example u or v type.
 *
 *  At the moment only one choice of the Dirac matrix representation
 *  is supported. For high-energy calculations the choice made by the
 *  HELAS collaboration is more efficient for numerical
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
template<typename Value>
class LorentzSpinor {
public:

  /** @name Standard constructors. */
  //@{
  /**
   * Default zero constructor, optionally specifying \a t, the type.
   */
  LorentzSpinor(SpinorType t = unknown_spinortype) : _type(t) {
    for(unsigned int ix=0;ix<4;++ix) _spin[ix]=Value();
  }

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying \a s, the type.
   */
  LorentzSpinor(complex<Value> a,complex<Value> b,
		complex<Value> c,complex<Value> d,
		SpinorType s = unknown_spinortype) : _type(s) {
    _spin[0]=a;
    _spin[1]=b;
    _spin[2]=c;
    _spin[3]=d;
  }
  //@}

  /** @name Access the components. */
  //@{
  /**
   * Subscript operator to return spinor components
   */
  complex<Value> operator[](int i) const  {
    assert( i >= 0 && i <= 3 );
    return _spin[i];
  }

  /**
   * Subscript operator to return spinor components
   */
  complex<Value> operator()(int i) const  {
    assert( i >= 0 && i <= 3 );
    return _spin[i];
  }
  
  /**
   * Set components by index.
   */
  complex<Value> & operator()(int i) {
    assert( i >= 0 && i <= 3 );
    return _spin[i];
  }
  
  /**
   * Set components by index.
   */
  complex<Value> & operator[](int i) {
    assert( i >= 0 && i <= 3 );
    return _spin[i];
  }
  
  /**
   * Get first component.
   */
  complex<Value> s1() const {return _spin[0];}

  /**
   * Get second component.
   */
  complex<Value> s2() const {return _spin[1];}

  /**
   * Get third component.
   */
  complex<Value> s3() const {return _spin[2];}

  /**
   * Get fourth component.
   */
  complex<Value> s4() const {return _spin[3];}

  /**
   * Set first component.
   */
  void setS1(complex<Value> in) {_spin[0]=in;}

  /**
   * Set second component.
   */
  void setS2(complex<Value> in) {_spin[1]=in;}

  /**
   * Set third component.
   */
  void setS3(complex<Value> in) {_spin[2]=in;}

  /**
   * Set fourth component.
   */
  void setS4(complex<Value> in) {_spin[3]=in;}
  //@}

  /** @name Transformations. */
  //@{
  /**
   * Return the barred spinor
   */
  LorentzSpinorBar<Value> bar() const;

  /**
   * Return the conjugated spinor \f$u_c=C\bar{u}^T\f$. This operation
   * transforms u-spinors to v-spinors and vice-versa and is required when
   * dealing with majorana particles.
   */
  LorentzSpinor conjugate() const;

  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzSpinor & boost(double,double,double);

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  LorentzSpinor & boost(const Boost &);

  /**
   * General Lorentz transformation
   */
  LorentzSpinor & transform(const SpinHalfLorentzRotation & );

  /**
   * General Lorentz transformation
   */
  LorentzSpinor & transform(const LorentzRotation & r) {
    transform(r.half());
    return *this;
  }
  //@}

  /** @name Functions related to type. */
  //@{
  /**
   * Return the type of the spinor.
   */
  SpinorType Type() const {return _type;}
  //@}

  /**
   *  @name Functions to apply the projection operator
   */
  //@{
  /**
   *   Apply \f$p\!\!\!\!\!\not\,\,\,+m\f$
   */
  template<typename ValueB> 
  LorentzSpinor<typename BinaryOpTraits<Value,ValueB>::MulT>
  projectionOperator(const LorentzVector<ValueB> & p, const ValueB & m) const {
    typedef typename BinaryOpTraits<Value,ValueB>::MulT ResultT;
    LorentzSpinor<ResultT> spin;
    static const Complex ii(0.,1.);
    complex<ValueB> p0pp3=p.t()+p.z();
    complex<ValueB> p0mp3=p.t()-p.z();
    complex<ValueB> p1pp2=p.x()+ii*p.y();
    complex<ValueB> p1mp2=p.x()-ii*p.y();
    spin.setS1(m*s1()+p0mp3*s3()-p1mp2*s4());
    spin.setS2(m*s2()+p0pp3*s4()-p1pp2*s3());
    spin.setS3(m*s3()+p0pp3*s1()+p1mp2*s2());
    spin.setS4(m*s4()+p0mp3*s2()+p1pp2*s1());
    return spin;
  }

  /**
   *  Apply \f$g^LP_L+g^RP_R\f$
   */
  LorentzSpinor
  helicityProjectionOperator(const Complex & gL, const Complex & gR) const {
    LorentzSpinor spin;
    spin.setS1(gL*s1());
    spin.setS2(gL*s2());
    spin.setS3(gR*s3());
    spin.setS4(gR*s4());
    return spin;
  }
  //@}


  /** @name Functions to calculate certain currents. */
  //@{
  /**
   *  Calculate the left-handed current \f$\bar{f}\gamma^\mu P_Lf\f$.
   * @param fb The barred spinor.
   */
  template<typename ValueB>
  LorentzVector<complex<typename BinaryOpTraits<Value,ValueB>::MulT> >
  leftCurrent(const LorentzSpinorBar<ValueB>& fb) const {
    typedef complex<typename BinaryOpTraits<Value,ValueB>::MulT> ResultT;
    LorentzVector<ResultT> vec;
    Complex ii(0.,1.);
    ResultT p1(fb.s3()*s2()),p2(fb.s4()*s1());
    vec.setX(   -(p1+p2) );
    vec.setY( ii*(p1-p2) );
    p1 = fb.s3()*s1();p2 = fb.s4()*s2();
    vec.setZ(   -(p1-p2) );
    vec.setT(    (p1+p2) );
    return vec;
  }

  /**
   *  Calculate the right-handed current \f$\bar{f}\gamma^\mu P_Rf\f$.
   * @param fb The barred spinor.
   */
  template<typename ValueB>
  LorentzVector<complex<typename BinaryOpTraits<Value,ValueB>::MulT> >
  rightCurrent(const LorentzSpinorBar<ValueB>& fb) const {
    typedef complex<typename BinaryOpTraits<Value,ValueB>::MulT> ResultT;
    LorentzVector<ResultT> vec;
    Complex ii(0.,1.);
    ResultT p1(fb.s1()*s4()),p2(fb.s2()*s3());
    vec.setX(     (p1+p2));
    vec.setY( -ii*(p1-p2));
    p1 = fb.s1()*s3();p2 = fb.s2()*s4();
    vec.setZ(     (p1-p2));
    vec.setT(     (p1+p2));
    return vec;
  }

  /**
   *  Calculate the vector current \f$\bar{f}\gamma^\mu f\f$
   * @param fb The barred spinor.
   */
  template<typename ValueB>
  LorentzVector<complex<typename BinaryOpTraits<Value,ValueB>::MulT> >
  vectorCurrent(const LorentzSpinorBar<ValueB>& fb) const {
    typedef complex<typename BinaryOpTraits<Value,ValueB>::MulT> ResultT;
    LorentzVector<ResultT> vec;
    Complex ii(0.,1.);
    ResultT s1s4(fb.s1()*s4()),s2s3(fb.s2()*s3()),
      s3s2(fb.s3()*s2()),s4s1(fb.s4()*s1()),
      s1s3(fb.s1()*s3()),s2s4(fb.s2()*s4()),
      s3s1(fb.s3()*s1()),s4s2(fb.s4()*s2());
    vec.setX(      s1s4+s2s3-s3s2-s4s1 );
    vec.setY( -ii*(s1s4-s2s3-s3s2+s4s1));
    vec.setZ(      s1s3-s2s4-s3s1+s4s2 );
    vec.setT(      s1s3+s2s4+s3s1+s4s2);
    return vec;
  }

  /**
   * Calculate a general current with arbitary left and right couplings,
   * i.e. \f$\bar{f}\gamma^\mu(c_lP_L+c_RP_R)f\f$
   * @param fb The barred spinor.
   * @param left The left coupling, \f$c_L\f$.
   * @param right The right coupling, \f$c_R\f$.
   */
  template<typename ValueB>
  LorentzVector<complex<typename BinaryOpTraits<Value,ValueB>::MulT> >
  generalCurrent(const LorentzSpinorBar<ValueB>& fb,
		 Complex left, Complex right) const {
    typedef complex<typename BinaryOpTraits<Value,ValueB>::MulT> ResultT;
    LorentzVector<ResultT> vec;
    Complex ii(0.,1.);
    ResultT p1(fb.s3()*s2()),p2(fb.s4()*s1());
    vec.setX(   -left*(p1+p2));
    vec.setY( ii*left*(p1-p2));
    p1 = fb.s3()*s1();p2 = fb.s4()*s2();
    vec.setZ(   -left*(p1-p2));
    vec.setT(    left*(p1+p2));
    p1=fb.s1()*s4();p2=fb.s2()*s3();
    vec.setX(vec.x()+right*(p1+p2));
    vec.setY(vec.y()-ii*right*(p1-p2));
    p1 = fb.s1()*s3();p2 = fb.s2()*s4();
    vec.setZ(vec.z()+right*(p1-p2));
    vec.setT(vec.t()+right*(p1+p2));
    return vec;
  }
  //@}

  /** @name Functions to calculate certain scalars. */
  //@{
  /**
   * Calculate the left-handed scalar \f$\bar{f}P_Lf\f$.
   * @param fb The barred spinor.
   */
  template<typename ValueB>
  complex<typename BinaryOpTraits<Value,ValueB>::MulT>
  leftScalar(const LorentzSpinorBar<ValueB>& fb) const  {
    return fb.s1()*s1()+fb.s2()*s2();
  }

  /**
   * Calculate the right-handed scalar \f$\bar{f}P_Rf\f$.
   * @param fb The barred spinor.
   */
  template<typename ValueB>
  complex<typename BinaryOpTraits<Value,ValueB>::MulT>
  rightScalar(const LorentzSpinorBar<ValueB>& fb) const {
    return fb.s3()*s3()+fb.s4()*s4();
  }
  
  /**
   *  Calculate the scalar \f$\bar{f}f\f$.
   * @param fb The barred spinor.
   */
  template<typename ValueB>
  complex<typename BinaryOpTraits<Value,ValueB>::MulT>
  scalar(const LorentzSpinorBar<ValueB>& fb) const {
    return fb.s1()*s1()+fb.s2()*s2()+fb.s3()*s3()+fb.s4()*s4();
  }

  /**
   *  Calculate the pseudoscalar \f$\bar{f}\gamma_5f\f$.
   * @param fb The barred spinor.
   */
  template<typename ValueB>
  complex<typename BinaryOpTraits<Value,ValueB>::MulT>
  pseudoScalar(const LorentzSpinorBar<ValueB>& fb) const {
    return -fb.s1()*s1()-fb.s2()*s2()+fb.s3()*s3()+fb.s4()*s4();
  }

  /**
   * Calculate a general scalar product with arbitary left and right couplings,
   * i.e. \f$\bar{f}c_lP_L+c_RP_Rf\f$
   * @param fb The barred spinor.
   * @param left The left coupling, \f$c_L\f$.
   * @param right The right coupling, \f$c_R\f$.
   */
  template<typename ValueB>
  complex<typename BinaryOpTraits<Value,ValueB>::MulT>
  generalScalar(const LorentzSpinorBar<ValueB>& fb,
		Complex left, Complex right) const {
    return left*(fb.s1()*s1()+fb.s2()*s2())
         + right*(fb.s3()*s3()+fb.s4()*s4());
  }
  //@}

  /**
   *  Calculate the product with \f$\sigma^{\mu\nu}\f$, i.e.
   *  \f$\bar{f}\sigma^{\mu\nu}f\f$
   */
  template<typename ValueB>
  LorentzTensor<typename BinaryOpTraits<Value,ValueB>::MulT>
  sigma(const LorentzSpinorBar<ValueB>& fb) const {
    typedef typename BinaryOpTraits<Value,ValueB>::MulT ResultT;
    LorentzTensor<ResultT> output;
    complex<ResultT> s11(fb.s1()*s1()),s22(fb.s2()*s2()),
      s33(fb.s3()*s3()),s44(fb.s4()*s4()),
      s12(fb.s1()*s2()),s21(fb.s2()*s1()),
      s34(fb.s3()*s4()),s43(fb.s4()*s3());
    Complex ii(0.,1.);
    complex<ResultT> zero;
    zero = ZERO;
    output.setTT(         zero         );
    output.setTX(-ii*( s12+s21-s34-s43));
    output.setTY(     -s12+s21+s34-s43 );
    output.setTZ(-ii*( s11-s22-s33+s44));
    output.setXT(      -output.tx()    );
    output.setXX(         zero         );
    output.setXY(      s11-s22+s33-s44 );
    output.setXZ(-ii*(-s12+s21-s34+s43));
    output.setYT(     -output.ty()     );
    output.setYX(     -output.xy()     );
    output.setYY(         zero         );
    output.setYZ(      s12+s21+s34+s43 );
    output.setZT(     -output.tz()     );
    output.setZX(     -output.xz()     );
    output.setZY(     -output.yz()     );
    output.setZZ(         zero         );
    return output;
  }

private:
  /**
   * Type of spinor
   */
  SpinorType _type;

  /**
   * Storage of the components.
   */
  complex<Value> _spin[4];
};

}
}

#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "LorentzSpinor.tcc"
#endif 

#endif

