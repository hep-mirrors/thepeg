// -*- C++ -*-
#ifndef ThePEG_LorentzSpinorBar_H
#define ThePEG_LorentzSpinorBar_H
// This is the declaration of the LorentzSpinorBar class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Vectors/LorentzRotation.h"
#include "ThePEG/Vectors/ThreeVector.h"
#include "HelicityDefinitions.h"
#include "LorentzSpinor.fh"
#include "LorentzSpinorBar.fh"

namespace ThePEG {
namespace Helicity {

/**
 *  The LorentzSpinorBar class implements the storage of a barred
 *  LorentzSpinor. The design is based on that of the LorentzSpinor
 *  class where the details of the implemented are discussed in more
 *  detail.
 *
 * @see LorentzSpinor
 *
 * @author Peter Richardson
 */

template<typename Value>
class LorentzSpinorBar {
public:

  /** @name Standard constructors. */
  //@{
  /**
   * Default zero constructor, optionally specifying \a t, the type
   * and \a rep, the choice of dirac matrix.
   */
  inline LorentzSpinorBar(SpinorType t = unknown_spinortype,
			  DiracRep r = defaultDRep);

  /**
   * Default zero constructor, optionally specifying the choice of
   * dirac matrix.
   */
  inline LorentzSpinorBar(DiracRep);

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying \a t, the type and \a r, the choice of
   * dirac matrix.
   */
  inline LorentzSpinorBar(complex<Value>,complex<Value>,complex<Value>,complex<Value>,
			  SpinorType t = unknown_spinortype,
			  DiracRep r = defaultDRep);

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying the choice of dirac matrix
   */
  LorentzSpinorBar(complex<Value>,complex<Value>,complex<Value>,complex<Value>,DiracRep);
  //@}

  /** @name Access the components. */
  //@{
  /**
   * Subscript operator to return spinor components
   */
  inline complex<Value> operator[](int) const;

  /**
   * Subscript operator to return spinor components
   */
  inline complex<Value> operator()(int) const;

  /**
   * Set components by index.
   */
  inline complex<Value> & operator()(int);

  /**
   * Set components by index.
   */
  inline complex<Value> & operator[](int);

  /**
   * Get first component.
   */
  inline complex<Value> s1() const;

  /**
   * Get second component.
   */
  inline complex<Value> s2() const;

  /**
   * Get third component.
   */
  inline complex<Value> s3() const;

  /**
   * Get fourth component.
   */
  inline complex<Value> s4() const;

  /**
   * Set first component.
   */
  inline void setS1(complex<Value>);

  /**
   * Set second component.
   */
  inline void setS2(complex<Value>);

  /**
   * Set third component.
   */
  inline void setS3(complex<Value>);

  /**
   * Set fourth component.
   */
  inline void setS4(complex<Value>);
  //@}

  /**
   * The assignment operator.
   */
  inline LorentzSpinorBar & operator = (const LorentzSpinorBar &);

  /** @name Transformations. */
  //@{
  /**
   * Return the barred spinor
   */
  LorentzSpinor<Value> bar() const;

  /**
   * Return the conjugated spinor \f$u_c=C\bar{u}^T\f$. This operation
   * transforms u-spinors to v-spinors and vice-versa and is required when
   * dealing with majorana particles.
   */
  LorentzSpinorBar conjugate() const;

  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzSpinorBar & boost(double,double,double);

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  LorentzSpinorBar & boost(const Boost &);

  /**
   * General Lorentz transformation
   */
  LorentzSpinorBar & transform(const SpinHalfLorentzRotation &);

  /**
   * General Lorentz transformation
   */
  inline LorentzSpinorBar & transform(const LorentzRotation &);
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
  inline LorentzSpinorBar transformRep(DiracRep) const;

  /**
   * Return the representation of the spinor.
   */
  inline const DiracRep Rep() const;

  /**
   * Return the type of the spinor.
   */
  inline const SpinorType Type() const;
  //@}

private:

  /**
   * Storage of the components.
   */
  complex<Value> _spin[4];

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

#include "LorentzSpinorBar.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "LorentzSpinorBar.tcc"
#endif 

#endif
