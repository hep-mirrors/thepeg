// -*- C++ -*-
#ifndef ThePEG_LorentzSpinorBar_H
#define ThePEG_LorentzSpinorBar_H
// This is the declaration of the LorentzSpinorBar class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Config/Complex.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/CLHEPWrap/ThreeVector.h"
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
  inline LorentzSpinorBar(Complex,Complex,Complex,Complex,
			  SpinorType t = unknown_spinortype,
			  DiracRep r = defaultDRep);

  /**
   * Constructor with complex numbers specifying the components,
   * optionally specifying the choice of dirac matrix
   */
  LorentzSpinorBar(Complex,Complex,Complex,Complex,DiracRep);
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
  inline LorentzSpinorBar & operator = (const LorentzSpinorBar &);

  /** @name Transformations. */
  //@{
  /**
   * Return the barred spinor
   */
  LorentzSpinor bar();

  /**
   * Standard Lorentz boost specifying the components of the beta vector.
   */
  LorentzSpinorBar & boost(double,double,double);

  /**
   * Standard Lorentz boost specifying the beta vector.
   */
  LorentzSpinorBar & boost(const Hep3Vector &);

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
  inline LorentzSpinorBar transformRep(DiracRep);

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

#include "LorentzSpinorBar.icc"

#endif
