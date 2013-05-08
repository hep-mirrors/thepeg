// -*- C++ -*-
//
// SamplerBase.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_SamplerBase_H
#define ThePEG_SamplerBase_H
// This is the declaration of the SamplerBase class.

#include "ThePEG/Interface/Interfaced.h"
#include "SamplerBase.fh"
#include "ThePEG/Handlers/StandardEventHandler.fh"
// #include "SamplerBase.xh"

namespace ThePEG {

/**
 * This is the base class for all phase space sampler classes to be
 * used by the EventHandler class to sample the phase space according
 * to the cross sections for the processes in the EventHandler. The
 * class should be able to sample a unit hyper-cube in arbitrary
 * dimensions. The points need not necessarily be sampled with unit
 * weight.
 *
 * The virtual methods to be implemented by concrete sub-classes are
 * initialize(), generate() and rejectLast().
 *
 * @see \ref SamplerBaseInterfaces "The interfaces"
 * defined for SamplerBase.
 * @see EventHandler
 */
class SamplerBase: public Interfaced {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Destructor.
   */
  virtual ~SamplerBase();
  //@}

public:

  /**
   * Set the event handler for which the function
   * StandardEventHandler::dSigDR(const vector<double> &) function
   * returns the cross section for the chosen phase space point.
   */
  void setEventHandler(tStdEHPtr eh) { theEventHandler = eh; }

  /** @name Virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * Initialize the the sampler, possibly doing presampling of the
   * phase space.
   */
  virtual void initialize() = 0;

  /**
   * Generarate a new phase space point and return a weight associated
   * with it. This weight should preferably be 1.
   */
  virtual double generate() = 0;

  /**
   * Reject the last chosen phase space point.
   */
  virtual void rejectLast() = 0;

  /**
   * Return the last generated phase space point.
   */
  const vector<double> & lastPoint() const { return theLastPoint; }

  /**
   * If the sampler is able to sample several different functions
   * separately, this function should return the last chosen
   * function. This default version always returns 0.
   */
  virtual int lastBin() const { return 0; }

  /**
   * Return the total integrated cross section determined from the
   * Monte Carlo sampling so far.
   */
  virtual CrossSection integratedXSec() const = 0;

  /**
   * Return the error on the total integrated cross section determined
   * from the Monte Carlo sampling so far.
   */
  virtual CrossSection integratedXSecErr() const = 0;

  /**
   * Return the overestimated integrated cross section.
   */
  virtual CrossSection maxXSec() const = 0;

  /**
   * Return the sum of the weights returned by generate() so far (of
   * the events that were not rejeted).
   */
  virtual double sumWeights() const = 0;

  /**
   * Return the sum of the weights squared returned by generate() so far (of
   * the events that were not rejeted).
   */
  virtual double sumWeights2() const = 0;
  //@}

protected:

  /**
   * Return the last generated phase space point.
   */
  vector<double> & lastPoint() { return theLastPoint; }

  /**
   * Return the associated event handler.
   */
  tStdEHPtr eventHandler() const { return theEventHandler; }

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
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();

private:

  /**
   * The associated event handler.
   */
  tStdEHPtr theEventHandler;

  /**
   * The last generated phase space point.
   */
  vector<double> theLastPoint;

private:

  /**
   * Describe an abstract base class with persistent data.
   */
  static AbstractClassDescription<SamplerBase> initSamplerBase;

  /**
   *  Private and non-existent assignment operator.
   */
  SamplerBase & operator=(const SamplerBase &);

};

}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the base class of
 * SamplerBase.
 */
template <>
struct BaseClassTrait<SamplerBase,1>: public ClassTraitsType {
  /** Typedef of the base class of SamplerBase. */
  typedef Interfaced NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * SamplerBase class.
 */
template <>
struct ClassTraits<SamplerBase>: public ClassTraitsBase<SamplerBase> {
  /** Return the class name. */
  static string className() { return "ThePEG::SamplerBase"; }

};

/** @endcond */

}

#endif /* ThePEG_SamplerBase_H */
