// -*- C++ -*-
#ifndef ThePEG_HardSphereYukawaFormFactor_H
#define ThePEG_HardSphereYukawaFormFactor_H
//
// This is the declaration of the HardSphereYukawaFormFactor class.
//

#include "NucleonFormFactor.h"
#include "ThePEG/PDT/ParticleData.h"

namespace ThePEG {

/**
 * The HardSphereYukawaFormFactor class implements a form factor model using a hard space + yukawaw interaction.
 *
 * @see \ref HardSphereYukawaFormFactorInterfaces "The interfaces"
 * defined for HardSphereYukawaFormFactor.
 */
class HardSphereYukawaFormFactor: public NucleonFormFactor {

public:

  /**
   * The default constructor.
   */
  HardSphereYukawaFormFactor() : yukawaRange_(0.7*femtometer), aFact_(1.2*femtometer)
  {}

  /**
   *  Convolution of hard sphere and Yukawa for heavy nuclei
   */
  Complex formFactor(tcPDPtr nucleon, Energy2 q2) const {
    pair<int,int> AZ = massAndZ(nucleon->id());
    Length R = aFact_*pow(AZ.first,1./3.);
    double Rq = sqrt(q2)*R/hbarc;
    return 3./pow(Rq,3)*(sin(Rq)-Rq*cos(Rq))/(1.+sqr(yukawaRange_/hbarc)*q2);
  }

public:

  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(PersistentOStream & os) const;

  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(PersistentIStream & is, int version);
  //@}

  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.xs
   */
  static void Init();

protected:

  /**
   *  Extract the mass and atomic number for the nuclear PDG code
   */
  pair<int,int> massAndZ(long pid) const {
    pair<int,int> output;
    output.first  = (abs(pid)%10000)/10;
    output.second = (abs(pid)%10000000)/10000;
    return output;
  }

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const;
  //@}

private:

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  HardSphereYukawaFormFactor & operator=(const HardSphereYukawaFormFactor &) = delete;

private :

  /**
   *  Range of the Yukawa potential
   */
  Length yukawaRange_;

  /**
   *  Prefactor for the nucleur radius \f$R_A=aA^{\frac13}\f$
   */
  Length aFact_;

  
};

}

#endif /* ThePEG_HardSphereYukawaFormFactor_H */
