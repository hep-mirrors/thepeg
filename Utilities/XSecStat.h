// -*- C++ -*-
//
// XSecStat.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef THEPEG_XSecStat_H
#define THEPEG_XSecStat_H
//
// This is the declaration of the XSecStat class.
//

#include "ThePEG/Config/ThePEG.h"

namespace ThePEG {

/**
 * XSecStat is a concrete helper class used to collect statistics
 * about the cross section for a specific process or group of
 * processes. It contains an overestimated cross section and
 * information about the number of times the process has been used to
 * generate an event and how many times this event has been accepted.
 *
 * An object of this class must initially be given an overestimated
 * cross section in the constructor or with the maxXSec(CrossSection)
 * function. Each time the corresponding process is selected
 * (according to maxXSec()), the select(double) function should be
 * called giving the weight with which the event will be accepted as
 * argument. If the event is then accepted, the accept() function
 * should be called. If an event is later vetoed, the reject()
 * function should be called.
 * 
 */
class XSecStat {

public:

  /** @name Standard constructors, destructor and assignment operator. */
  //@{
  /**
   * The default constructor.
   */
  inline XSecStat();

  /**
   * Constructor taking the overestimated cross section, \a xsecmax,
   * as argument.
   */
  inline XSecStat(CrossSection xsecmax);

  /**
   * The copy constructor.
   */
  inline XSecStat(const XSecStat &);

  /**
   * The assignment operator.
   */
  inline XSecStat & operator=(const XSecStat &);

  /**
   * Add the contents of another XSecStat.
   */
  inline XSecStat & operator+=(const XSecStat &);

  /**
   * Reset the statistics.
   */
  inline void reset();

  //@}

public:

  /** @name Simple access functions */
  //@{

  /**
   * An event of the corresponding class has been accepted. The
   * select() method must have been called before.
   */
  inline void accept();

  /**
   * An event of the corresponding class has been attempted. It will
   * subsequently be accepted with the given \a weight.
   */
  inline void select(double weight);

  /**
   * Reject the event which was last accepted with accept() or
   * selected with select(double). The \a weight should be set to the
   * value, \f$w\f$, used in the previous call to select(double),
   * except if the event has been accepted with the probability
   * \f$w\f$, in which case \a weight should be set to \f$sign(1,
   * w)\f$.
   */
  inline void reject(double weight = 1.0);

  /**
   * The current estimate of the cross section for the corresponding
   * class of events. If no events have been generated, maxXSec() will
   * be returned.
   */
  inline CrossSection xSec() const;

  /**
   * The current estimate of the error in the cross section for the
   * corresponding class of events. If no events have been generated,
   * maxXSec() will be returned.
   */
  inline CrossSection xSecErr() const;

  /**
   * The overestimated cross section.
   */
  inline CrossSection maxXSec() const;

  /**
   * The sum of the weights so far.
   */
  inline double sumWeights() const;

  /**
   * The sum of the squared weights so far.
   */
  inline double sumWeights2() const;

  /**
   * Number of attempts so far.
   */
  inline long attempts() const;

  /**
   * Number of attempts so far.
   */
  inline long accepted() const;

  /**
   * Set the overestimated cross section.
   */
  inline void maxXSec(CrossSection);
  //@}

public:

  /** @name I/O functions */
  //@{
  /**
   * Output to a persistent stream.
   */
  void output(PersistentOStream & os) const;

  /**
   * Input from a persistent stream.
   */
  void input(PersistentIStream & is);
  //@}

private:

  /**
   * The overestimated cross section.
   */
  CrossSection theMaxXSec;

  /**
   * Number of attempts so far.
   */
  long theAttempts;

  /**
   * Number of accepted events so far.
   */
  long theAccepted;

  /**
   * The sum of the weights so far.
   */
  double theSumWeights;

  /**
   * The sum of the squared weights so far.
   */
  double theSumWeights2;

};

/** Ouptut an XSecStat to a persistent stream. */
PersistentOStream & operator<<(PersistentOStream &, const XSecStat &);

/** Input an XSecStat from a persistent stream. */
PersistentIStream & operator>>(PersistentIStream &, XSecStat &);

/** Add the contents of two XSecStat objects. */
inline XSecStat operator+(const XSecStat & x1, const XSecStat & x2);

}

#include "XSecStat.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "XSecStat.tcc"
#endif

#endif /* THEPEG_XSecStat_H */
