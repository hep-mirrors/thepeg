// -*- C++ -*-
//
// LeptonLeptonRemnant.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_LeptonLeptonRemnant_H
#define ThePEG_LeptonLeptonRemnant_H

#include "ThePEG/PDF/RemnantHandler.h"

namespace ThePEG {

/**
 * LeptonLeptonRemnant inherits from the RemnantHandler and implements
 * the generation of a single collinear photon remnant when a lepton
 * is extracted from a lepton.
 *
 * @see \ref LeptonLeptonRemnantInterfaces "The interfaces"
 * defined for LeptonLeptonRemnant.
 * @see LeptonLeptonPDF
 */
class LeptonLeptonRemnant: public RemnantHandler {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  LeptonLeptonRemnant();
  //@}

public:

  /** @name Virtual functions mandated by the RemnantHandler base class. */
  //@{
  /**
   * Return true if this remnant handler can handle extracting all
   * specified \a partons form the given \a particle.
   */
  virtual bool canHandle(tcPDPtr particle, const cPDVector & partons) const;

  /**
   * Generate momenta. Generates the momenta of the extracted parton
   * in the particle cms (but with the parton \f$x\f$ still the
   * positive light-cone fraction) as given by the last argument, \a
   * p. If the particle is space-like the positive and negative
   * light-cone momenta are \f$\sqrt{-m^2}\f$ and \f$-sqrt{-m^2}\f$
   * respectively. If the \a scale is negative, it means that the \a
   * doScale in the previous call to nDim() was true, otherwise the
   * given scale should be the virtuality of the extracted
   * parton. Generated quantities which are not returned in the
   * momentum may be saved in the PartonBin, \a pb, for later use. In
   * particular, if the nDim() random numbers, \a r, are not enough to
   * generate with weight one, the resulting weight should be stored
   * with the remnantWeight() method of the parton bin.
   */
  virtual Lorentz5Momentum generate(PartonBinInstance & pb, const double * r,
				    Energy2 scale,
				    const LorentzMomentum & p) const;

  /**
   * Generate the momentum of the extracted parton with the \a parent
   * momentum given by the last argument. If the \a scale is negative,
   * it means that the doScale in the previous call to nDim() was
   * true, otherwise the given \a scale should be the virtuality of
   * the extracted parton. \a shat is the total invariant mass squared
   * of the hard sub-system produced by the extracted parton and the
   * primary parton entering from the other side. Generated quantities
   * which are not returned in the momentum may be saved in the
   * PartonBinInstance, \a pb, for later use. In particular, if the
   * nDim() random numbers, \a r, are not enough to generate with
   * weight one, the resulting weight should be stored with the
   * remnantWeight() method of the parton bin.
   */
  virtual Lorentz5Momentum generate(PartonBinInstance & pb, const double * r,
				    Energy2 scale, Energy2 shat,
				    const LorentzMomentum & parent) const;
  //@}

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
   * Standard Init function used to initialize the interface.
   */
  static void Init();

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

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit() throw(InitException);
  //@}

private:

  /**
   * The minimum energy fraction allowed for a photon remnant.
   */
  double minX;

  /**
   * Easy access to a proton data object.
   */
  tPDPtr photon;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<LeptonLeptonRemnant> initLeptonLeptonRemnant;

  /**
   *  Private and non-existent assignment operator.
   */
  LeptonLeptonRemnant & operator=(const LeptonLeptonRemnant &);

};

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of LeptonLeptonRemnant. */
template <>
struct BaseClassTrait<LeptonLeptonRemnant,1>: public ClassTraitsType {
  /** Typedef of the first base class of LeptonLeptonRemnant. */
  typedef RemnantHandler NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  LeptonLeptonRemnant class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<LeptonLeptonRemnant>:
    public ClassTraitsBase<LeptonLeptonRemnant> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::LeptonLeptonRemnant"; }
  /** Return the name of the shared library be loaded to get access to
   *  the LeptonLeptonRemnant class and every other class it uses
   *  (except the base class). */
  static string library() { return "LeptonLeptonRemnant.so"; }
};

/** @endcond */

}

#endif /* ThePEG_LeptonLeptonRemnant_H */
