// -*- C++ -*-
//
// AlphaSBase.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_AlphaSBase_H
#define ThePEG_AlphaSBase_H
// This is the declaration of the AlphaSBase class.

#include "ThePEG/Interface/Interfaced.h"
#include "StandardModelBase.fh"

namespace ThePEG {

/**
 * AlphaSBase is an abstract base class used by the StandardModelBase
 * to implement the QCD coupling, \f$\alpha_S\f$. The AlphaSBase also
 * encodes the number of active flavours at a given scale and the
 * \f$\Lambda_{QCD}\f$ for a given number of active flavours or for a
 * given scale.
 *
 * @see \ref AlphaSBaseInterfaces "The interfaces"
 * defined for AlphaSBase.
 * @see StandardModelBase
 */
class AlphaSBase: public Interfaced {

public:

  /** @name Virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * The \f$\alpha_S\f$. Return the QCD coupling for a given \a scale
   * using the given standard model object \a sm.
   */
  virtual double value(Energy2 scale, const StandardModelBase & sm) const = 0;

  /**
   * Return the flavour thresholds used. The returned vector contains
   * (in position <code>i</code>) the scales when the active number of
   * flavours changes from <code>i</code> to <code>i+1</code>.
   */
  virtual vector<Energy2> flavourThresholds() const = 0;

  /**
   * Return the \f$\Lambda_{QCD}\f$ used for different numbers of
   * active flavours.
   */
  virtual vector<Energy> LambdaQCDs() const = 0;
  //@}

  /** @name Access information about number of flavours and
      \f$\Lambda_{QCD}\f$. */
  //@{
  /**
   * Return the number of avtive quark flavours.
   */
  unsigned int Nf(Energy2 scale) const {
    unsigned int i = 0;
    while ( i < theFlavourThresholds.size() &&
	    theFlavourThresholds[i] < scale ) ++i;
    return i;
  }

  /**
   * Return the \f$\Lambda_{QCD}\f$ used for \a nflav active flavours.
   */
  Energy LambdaQCD(unsigned int nflav) const  { return theLambdaQCDs[nflav]; }

  /**
   * Return the \f$\Lambda_{QCD}\f$ used for corresponding given \a scale.
   */
  Energy LambdaQCD(Energy2 scale) const { return theLambdaQCDs[Nf(scale)]; }
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
   * Flavour thresholds, set from the virtual functions in the
   * initialization.
   */
  vector<Energy2> theFlavourThresholds;

  /**
   * The values of \f$\Lambda_{QCD}\f$ corresponding to
   * theFlavourThresholds, set from the virtual functions in the
   * initialization.
   */
  vector<Energy> theLambdaQCDs;

private:

  /**
   * Describe an abstract class with persistent data.
   */
  static AbstractClassDescription<AlphaSBase> initAlphaSBase;

  /**
   *  Private and non-existent assignment operator.
   */
  AlphaSBase & operator=(const AlphaSBase &);

};

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the base classes
 *  of AlphaSBase. */
template <>
struct BaseClassTrait<AlphaSBase,1>: public ClassTraitsType {
  /** Typedef of the first base class of AlphaSBase. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  AlphaSBase class. */
template <>
struct ClassTraits<AlphaSBase>: public ClassTraitsBase<AlphaSBase> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::AlphaSBase"; }
};

/** @endcond */

}

#endif /* ThePEG_AlphaSBase_H */
