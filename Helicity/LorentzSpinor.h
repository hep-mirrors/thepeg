// -*- C++ -*-
//
// LorentzSpinor.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
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
template<typename Value>
class LorentzSpinor {
public:

  /** @name Standard constructors. */
  //@{
  /**
   * Default zero constructor, optionally specifying \a t, the type
   * and \a r, the choice of dirac matrix.
   */
  LorentzSpinor(SpinorType t = unknown_spinortype,
		DiracRep r = defaultDRep) : _dirac(r), _type(t) {
    for(unsigned int ix=0;ix<4;++ix) _spin[ix]=Value();
  }

  /**
   * Default zero constructor, optionally specifying the choice of
   * dirac matrix.
   */
  LorentzSpinor(DiracRep d) : _dirac(d), _type(unknown_spinortype) {
    for(unsigned int ix=0;ix<4;++ix) _spin[ix]=Value();
  }

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying \a s, the type and \a r, the choice of
   * dirac matrix.
   */
  LorentzSpinor(complex<Value> a,complex<Value> b,
		complex<Value> c,complex<Value> d,
		SpinorType s = unknown_spinortype,
		DiracRep r = defaultDRep) : _dirac(r), _type(s) {
    _spin[0]=a;
    _spin[1]=b;
    _spin[2]=c;
    _spin[3]=d;
  }
  
  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying the choice of dirac matrix
   */
  LorentzSpinor(complex<Value> a, complex<Value> b,
		complex<Value> c, complex<Value> d, DiracRep r)
    : _dirac(r), _type(unknown_spinortype) {
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

  /** @name Functions related to type and representation. */
  //@{
  /**
   * Change the dirac matrix representation.
   */
  void changeRep(DiracRep newdirac) {
    if(newdirac!=_dirac) *this = transformRep(newdirac);
  }

  /**
   * Return the spinor in a different representation.
   */
  LorentzSpinor transformRep(DiracRep newdirac) const {
    // do nothing if all ready in the correct representation
    if(newdirac==_dirac) return LorentzSpinor(*this);
    double fact(sqrt(0.5));
    // transform from HELAS representation to Haber one
    complex<Value> output[4];
    if(newdirac==HELASDRep && _dirac==HaberDRep) {
      output[0] =-fact*( _spin[0]-_spin[2]);
      output[1] =-fact*( _spin[1]-_spin[3]);
      output[2] =-fact*( _spin[0]+_spin[2]);
      output[3] =-fact*( _spin[1]+_spin[3]);
    }
    // transform from Haber representation to HELAS one
    else if(newdirac==HaberDRep && _dirac==HELASDRep) {
      output[0] =-fact*( _spin[0]+_spin[2]);
      output[1] =-fact*( _spin[1]+_spin[3]);
      output[2] =-fact*(-_spin[0]+_spin[2]);
      output[3] =-fact*(-_spin[1]+_spin[3]);
    }
    // return the answer
    return LorentzSpinor(output[0],output[1],
			 output[2],output[3],_type,newdirac);
  }
  
  /**
   * Return the representation of the spinor.
   */
  DiracRep Rep() const {return _dirac;}

  /**
   * Return the type of the spinor.
   */
  SpinorType Type() const {return _type;}
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
    if(Rep()==fb.Rep()) {
      // HELAS representation
      if(Rep()==HELASDRep){
	ResultT p1(fb.s3()*s2()),p2(fb.s4()*s1());
	vec.setX(   -(p1+p2) );
	vec.setY( ii*(p1-p2) );
	p1 = fb.s3()*s1();p2 = fb.s4()*s2();
	vec.setZ(   -(p1-p2) );
	vec.setT(    (p1+p2) );
      }
      // Haber representation
      else {
	complex<Value> s2m4(s2()-s4()), s1m3(s1()-s3());
	complex<ValueB> sb1p3(fb.s1()+fb.s3()), sb2p4(fb.s2()+fb.s4());
	ResultT p1(sb1p3*s2m4),p2(sb2p4*s1m3);
	vec.setX( -0.5*(p1+p2) );
	vec.setY( ii*0.5*(p1-p2) );
	p1 = sb1p3*s1m3; p2=sb2p4*s2m4;
	vec.setZ( -0.5*(p1-p2) );
	vec.setT( 0.5*(p1+p2) );
      }
    }
    else {
      LorentzSpinorBar<ValueB> fbar(fb);
      fbar.changeRep(Rep());
      // HELAS representation
      if(Rep()==HELASDRep){
	ResultT p1(fbar.s3()*s2()),p2(fbar.s4()*s1());
	vec.setX(   -(p1+p2) );
	vec.setY( ii*(p1-p2) );
	p1 = fbar.s3()*s1();p2 = fbar.s4()*s2();
	vec.setZ(   -(p1-p2) );
	vec.setT(    (p1+p2) );
      }
      // Haber representation
      else {
	complex<Value> s2m4(s2()-s4()), s1m3(s1()-s3());
	complex<ValueB> sb1p3(fbar.s1()+fbar.s3()), sb2p4(fbar.s2()+fbar.s4());
	ResultT p1(sb1p3*s2m4),p2(sb2p4*s1m3);
	vec.setX( -0.5*(p1+p2) );
	vec.setY( ii*0.5*(p1-p2) );
	p1 = sb1p3*s1m3; p2=sb2p4*s2m4;
	vec.setZ( -0.5*(p1-p2) );
	vec.setT( 0.5*(p1+p2) );
      }
    }
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
    if(Rep()==fb.Rep()) {
      // HELAS representation
      if(Rep()==HELASDRep) {
	ResultT p1(fb.s1()*s4()),p2(fb.s2()*s3());
	vec.setX(     (p1+p2));
	vec.setY( -ii*(p1-p2));
	p1 = fb.s1()*s3();p2 = fb.s2()*s4();
	vec.setZ(     (p1-p2));
	vec.setT(     (p1+p2));
      }
      // HABAR representation
      else {
	complex<Value> s2p4(s2()+s4()),s1p3(s1()+s3());
	complex<ValueB> sb1m3(fb.s1()-fb.s3()),sb2m4(fb.s2()-fb.s4());
	ResultT p1(sb1m3*s2p4),p2(sb2m4*s1p3);
	vec.setX(    +0.5*( p1+p2));
	vec.setY( +ii*0.5*(-p1+p2));
	p1 = sb1m3*s1p3; p2=sb2m4*s2p4;
	vec.setZ(    +0.5*(+p1-p2));
	vec.setT(    +0.5*(+p1+p2));
      }
    }
    else {
      LorentzSpinorBar<ValueB> fbar(fb);
      fbar.changeRep(Rep());
      // HELAS representation
      if(Rep()==HELASDRep) {
	ResultT p1(fbar.s1()*s4()),p2(fbar.s2()*s3());
	vec.setX(     (p1+p2));
	vec.setY( -ii*(p1-p2));
	p1 = fbar.s1()*s3();p2 = fbar.s2()*s4();
	vec.setZ(     (p1-p2));
	vec.setT(     (p1+p2));
      }
      // HABAR representation
      else {
	complex<Value> s2p4(s2()+s4()),s1p3(s1()+s3());
	complex<ValueB> sb1m3(fbar.s1()-fbar.s3()),sb2m4(fbar.s2()-fbar.s4());
	ResultT p1(sb1m3*s2p4),p2(sb2m4*s1p3);
	vec.setX(    +0.5*( p1+p2));
	vec.setY( +ii*0.5*(-p1+p2));
	p1 = sb1m3*s1p3; p2=sb2m4*s2p4;
	vec.setZ(    +0.5*(+p1-p2));
	vec.setT(    +0.5*(+p1+p2));
      }
    }
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
    if(Rep()==fb.Rep()) {
      ResultT s1s4(fb.s1()*s4()),s2s3(fb.s2()*s3()),
	      s3s2(fb.s3()*s2()),s4s1(fb.s4()*s1()),
	      s1s3(fb.s1()*s3()),s2s4(fb.s2()*s4()),
	      s3s1(fb.s3()*s1()),s4s2(fb.s4()*s2());
      vec.setX(      s1s4+s2s3-s3s2-s4s1 );
      vec.setY( -ii*(s1s4-s2s3-s3s2+s4s1));
      vec.setZ(      s1s3-s2s4-s3s1+s4s2 );
      if(Rep()==HELASDRep) {
	vec.setT(      s1s3+s2s4+s3s1+s4s2);
      }
      else {
	vec.setT(+fb.s1()*s1()+fb.s2()*s2()
		 -fb.s3()*s3()-fb.s4()*s4());
      }
    }
    else {
      LorentzSpinorBar<ValueB> fbar(fb);
      fbar.changeRep(Rep());
      ResultT s1s4(fbar.s1()*s4()),s2s3(fbar.s2()*s3()),
	      s3s2(fbar.s3()*s2()),s4s1(fbar.s4()*s1()),
	      s1s3(fbar.s1()*s3()),s2s4(fbar.s2()*s4()),
	      s3s1(fbar.s3()*s1()),s4s2(fbar.s4()*s2());
      vec.setX(      s1s4+s2s3-s3s2-s4s1 );
      vec.setY( -ii*(s1s4-s2s3-s3s2+s4s1));
      vec.setZ(      s1s3-s2s4-s3s1+s4s2 );
      if(Rep()==HELASDRep) {
	vec.setT(      s1s3+s2s4+s3s1+s4s2 );
      }
      else {
	vec.setT(+fbar.s1()*s1()+fbar.s2()*s2()
		 -fbar.s3()*s3()-fbar.s4()*s4());
      }
    }
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
    if(Rep()==fb.Rep()) {
      // HELAS representation
      if(Rep()==HELASDRep) {
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
      }
      // Haber representation
      else {
	// left handed terms
	complex<Value>  s2m4(s2()-s4()),s1m3(s1()-s3());
	complex<ValueB> sb1p3(fb.s1()+fb.s3()), sb2p4(fb.s2()+fb.s4());
	ResultT p1(sb1p3*s2m4),p2(sb2p4*s1m3);
	vec.setX(  -0.5*left*(p1+p2));
	vec.setY(ii*0.5*left*(p1-p2));
	p1 = sb1p3*s1m3; p2=sb2p4*s2m4;
	vec.setZ(  -0.5*left*(p1-p2));
	vec.setT(   0.5*left*(p1+p2));
	// right handed terms
	complex<Value> s2p4(s2()+s4()),s1p3(s1()+s3());
	complex<ValueB> sb1m3(fb.s1()-fb.s3()), sb2m4(fb.s2()-fb.s4());
	p1=sb1m3*s2p4;p2=sb2m4*s1p3;
	vec.setX(vec.x()+0.5*right*( p1+p2));
	vec.setY(vec.y()+ii*0.5*right*(-p1+p2));
	p1 = sb1m3*s1p3; p2=sb2m4*s2p4;
	vec.setZ(vec.z()+0.5*right*(+p1-p2));
	vec.setT(vec.t()+0.5*right*(+p1+p2));
      }
    }
    else {
      LorentzSpinorBar<ValueB> fbar(fb);
      fbar.changeRep(Rep());
      // HELAS representation
      if(Rep()==HELASDRep) {
	ResultT p1(fbar.s3()*s2()),p2(fbar.s4()*s1());
	vec.setX(   -left*(p1+p2));
	vec.setY( ii*left*(p1-p2));
	p1 = fbar.s3()*s1();p2 = fbar.s4()*s2();
	vec.setZ(   -left*(p1-p2));
	vec.setT(    left*(p1+p2));
	p1=fbar.s1()*s4();p2=fbar.s2()*s3();
	vec.setX(vec.x()+right*(p1+p2));
	vec.setY(vec.y()-ii*right*(p1-p2));
	p1 = fbar.s1()*s3();p2 = fbar.s2()*s4();
	vec.setZ(vec.z()+right*(p1-p2));
	vec.setT(vec.t()+right*(p1+p2));
      }
      // Haber representation
      else {
	// left handed terms
	complex<Value>  s2m4(s2()-s4()),s1m3(s1()-s3());
	complex<ValueB> sb1p3(fbar.s1()+fbar.s3()), sb2p4(fbar.s2()+fbar.s4());
	ResultT p1(sb1p3*s2m4),p2(sb2p4*s1m3);
	vec.setX(  -0.5*left*(p1+p2));
	vec.setY(ii*0.5*left*(p1-p2));
	p1 = sb1p3*s1m3; p2=sb2p4*s2m4;
	vec.setZ(  -0.5*left*(p1-p2));
	vec.setT(   0.5*left*(p1+p2));
	// right handed terms
	complex<Value> s2p4(s2()+s4()),s1p3(s1()+s3());
	complex<ValueB> sb1m3(fbar.s1()-fbar.s3()), sb2m4(fbar.s2()-fbar.s4());
	p1=sb1m3*s2p4;p2=sb2m4*s1p3;
	vec.setX(vec.x()+0.5*right*( p1+p2));
	vec.setY(vec.y()+ii*0.5*right*(-p1+p2));
	p1 = sb1m3*s1p3; p2=sb2m4*s2p4;
	vec.setZ(vec.z()+0.5*right*(+p1-p2));
	vec.setT(vec.t()+0.5*right*(+p1+p2));
      }
    }
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
    if(Rep()==fb.Rep()) {
      // high energy conventions
      if(Rep()==HELASDRep) {
	return fb.s1()*s1()+fb.s2()*s2();
      }
      // low energy conventions
      else {
	return  0.5*( (fb.s1()-fb.s3())*(s1()-s3())+
		      (fb.s2()-fb.s4())*(s2()-s4()));
      }
    }
    else {
      LorentzSpinorBar<ValueB> fbar(fb);
      fbar.changeRep(Rep());
      // high energy conventions
      if(Rep()==HELASDRep) {
	return fbar.s1()*s1()+fbar.s2()*s2();
      }
      // low energy conventions
      else {
	return  0.5*( (fbar.s1()-fbar.s3())*(s1()-s3())+
		      (fbar.s2()-fbar.s4())*(s2()-s4()));
      }
    }
  }

  /**
   * Calculate the right-handed scalar \f$\bar{f}P_Rf\f$.
   * @param fb The barred spinor.
   */
  template<typename ValueB>
  complex<typename BinaryOpTraits<Value,ValueB>::MulT>
  rightScalar(const LorentzSpinorBar<ValueB>& fb) const {
    if(Rep()==fb.Rep()) {
      // high energy conventions
      if(Rep()==HELASDRep) {
	return fb.s3()*s3()+fb.s4()*s4();
      }
      // low energy conventions
      else {
	return 0.5*( (fb.s1()+fb.s3())*(s1()+s3())+
		     (fb.s2()+fb.s4())*(s2()+s4()));
      }
    }
    else {
      LorentzSpinorBar<ValueB> fbar(fb);
      fbar.changeRep(Rep());
      // high energy conventions
      if(Rep()==HELASDRep) {
	return fbar.s3()*s3()+fbar.s4()*s4();
      }
      // low energy conventions
      else {
	return 0.5*( (fbar.s1()+fbar.s3())*(s1()+s3())+
		     (fbar.s2()+fbar.s4())*(s2()+s4()));
      }
    }
  }

  /**
   *  Calculate the scalar \f$\bar{f}f\f$.
   * @param fb The barred spinor.
   */
  template<typename ValueB>
  complex<typename BinaryOpTraits<Value,ValueB>::MulT>
  scalar(const LorentzSpinorBar<ValueB>& fb) const {
    if(Rep()==fb.Rep()) {
      return fb.s1()*s1()+fb.s2()*s2()+fb.s3()*s3()+fb.s4()*s4();
    }
    else {
      LorentzSpinorBar<ValueB> fbar(fb);
      fbar.changeRep(Rep());
      return fbar.s1()*s1()+fbar.s2()*s2()+fbar.s3()*s3()+fbar.s4()*s4();
    }
  }

  /**
   *  Calculate the pseudoscalar \f$\bar{f}\gamma_5f\f$.
   * @param fb The barred spinor.
   */
  template<typename ValueB>
  complex<typename BinaryOpTraits<Value,ValueB>::MulT>
  pseudoScalar(const LorentzSpinorBar<ValueB>& fb) const {
    // ensure both spinors are in the same representation, otherwise change to default
    if(Rep()==fb.Rep()) {
      // high energy
      if(Rep()==HELASDRep) {
	return -fb.s1()*s1()-fb.s2()*s2()+fb.s3()*s3()+fb.s4()*s4();
      }
      // low energy
      else {
	return fb.s1()*s3()+fb.s2()*s4()+fb.s3()*s1()+fb.s4()*s2();
      }
    }
    else {
      LorentzSpinorBar<ValueB> fbar(fb);
      fbar.changeRep(Rep());
      // high energy
      if(Rep()==HELASDRep) {
	return -fbar.s1()*s1()-fbar.s2()*s2()+fbar.s3()*s3()+fbar.s4()*s4();
      }
      // low energy
      else {
	return fbar.s1()*s3()+fbar.s2()*s4()+fbar.s3()*s1()+fbar.s4()*s2();
      }
    }
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
    if(Rep()==HELASDRep) {
      // high energy conventions
      if(Rep()==HELASDRep) {
	return   left*(fb.s1()*s1()+fb.s2()*s2())
	       +right*(fb.s3()*s3()+fb.s4()*s4());
      }
      // high energy conventions
      else {
	return  0.5*(   left*( (fb.s1()-fb.s3())*(s1()-s3())
			      +(fb.s2()-fb.s4())*(s2()-s4()))
		      +right*( (fb.s1()+fb.s3())*(s1()+s3())
			      +(fb.s2()+fb.s4())*(s2()+s4())));
      }
    }
    else {
      LorentzSpinorBar<ValueB> fbar(fb);
      fbar.changeRep(Rep());
      // high energy conventions
      if(Rep()==HELASDRep) {
	return   left*(fbar.s1()*s1()+fbar.s2()*s2())
	       +right*(fbar.s3()*s3()+fbar.s4()*s4());
      }
      // high energy conventions
      else {
	return  0.5*(   left*( (fbar.s1()-fbar.s3())*(s1()-s3())
			      +(fbar.s2()-fbar.s4())*(s2()-s4()))
		      +right*( (fbar.s1()+fbar.s3())*(s1()+s3())
			      +(fbar.s2()+fbar.s4())*(s2()+s4())));
      }
    }
  }
  //@}

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
  complex<Value> _spin[4];
};

}
}

#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "LorentzSpinor.tcc"
#endif 

#endif

