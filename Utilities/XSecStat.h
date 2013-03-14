// -*- C++ -*-
//
// XSecStat.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad
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
  XSecStat() 
    : theMaxXSec(ZERO), theAttempts(0), theAccepted(0), theVetoed(0),
      theSumWeights (vector<double>(5,0.0)),
      theSumWeights2(vector<double>(5,0.0)), theLastWeight(0.0) {}

  /**
   * Constructor taking the overestimated cross section, \a xsecmax,
   * as argument.
   */
  XSecStat(CrossSection xsecmax) 
    : theMaxXSec(xsecmax), theAttempts(0), theAccepted(0), theVetoed(0),
      theSumWeights (vector<double>(5,0.0)),
      theSumWeights2(vector<double>(5,0.0)), theLastWeight(0.0) {}

  /**
   * The assignment operator.
   */
  XSecStat & operator=(const XSecStat & x) {
    theMaxXSec     = x.theMaxXSec;
    theAttempts    = x.theAttempts;
    theAccepted    = x.theAccepted;
    theVetoed      = x.theVetoed;
    theSumWeights  = x.theSumWeights;
    theSumWeights2 = x.theSumWeights2;
    theLastWeight  = x.theLastWeight;
    return *this;
  }

  /**
   * Add the contents of another XSecStat.
   */
  XSecStat & operator+=(const XSecStat & x) {
    theMaxXSec     += x.theMaxXSec;
    theAttempts    += x.theAttempts;
    theAccepted    += x.theAccepted;
    theVetoed      += x.theVetoed;
    for(unsigned int ix=0;ix<5;++ix) {
      theSumWeights [ix] += x.theSumWeights [ix];
      theSumWeights2[ix] += x.theSumWeights2[ix];
    }
    theLastWeight = 0.0;
    return *this;
  }

  /**
   * Reset the statistics.
   */
  void reset() {
    theAttempts = theAccepted = theVetoed = 0;
    theSumWeights = theSumWeights2 = vector<double>(5,0.0);
    theLastWeight = 0.0;
  }

  //@}

public:

  /** @name Simple access functions */
  //@{

  /**
   * An event of the corresponding class has been accepted. The
   * select() method must have been called before.
   */
  void accept() { 
    ++theAccepted;
    theSumWeights [1] += 1.;
    theSumWeights2[1] += 1.;
  }

  /**
   * An event of the corresponding class has been attempted. It will
   * subsequently be accepted with the given \a weight.
   */
  void select(double weight) {
    ++theAttempts;
    theSumWeights [0] +=     weight ;
    theSumWeights2[0] += sqr(weight);
    theSumWeights [3] +=     weight ;
    theSumWeights2[3] += sqr(weight);
    theLastWeight = weight;
  }

  /**
   * Reweight a selected and accepted event.
   */
  void reweight(double oldWeight, double newWeight) {
    theSumWeights [0] +=     newWeight  -     oldWeight ;
    theSumWeights2[0] += sqr(newWeight) - sqr(oldWeight);
  }

  /**
   * Reject the event which was last accepted with accept() or
   * selected with select(double). The \a weight should be set to the
   * value, \f$w\f$, used in the previous call to select(double),
   * except if the event has been accepted with the probability
   * \f$w\f$, in which case \a weight should be set to \f$sign(1,
   * w)\f$.
   */
  void reject(double weight = 1.0) {
    theSumWeights [1] -=               1.0 ;
    theSumWeights2[1] -=               1.0 ;
    theSumWeights [2] +=            weight ;
    theSumWeights2[2] +=        sqr(weight);
    theSumWeights [4] +=     theLastWeight ;
    theSumWeights2[4] += sqr(theLastWeight);
    ++theVetoed;
  }

  /**
   * The current estimate of the cross section for the corresponding
   * class of events. If no events have been generated, maxXSec() will
   * be returned.
   */
  CrossSection xSec() const {
    return attempts() ? maxXSec()*(theSumWeights[0]-theSumWeights[2])/attempts() : maxXSec();
  }

  /**
   * The current estimate of the error in the cross section for the
   * corresponding class of events. If no events have been generated,
   * maxXSec() will be returned.
   */
  CrossSection xSecErr() const {
    return attempts() ? maxXSec()*sqrt(theSumWeights2[0]+
				       theSumWeights2[2])/attempts() : maxXSec();
  }

  /**
   * The current estimate of the cross section for the corresponding
   * class of events, excluding reweighting. If no events have been
   * generated, maxXSec() will be returned.
   */
  CrossSection xSecNoReweight() const {
    return attempts() ? maxXSec()*(theSumWeights[3]-theSumWeights[4])/attempts() : maxXSec();
  }

  /**
   * The current estimate of the error in the cross section for the
   * corresponding class of events, excluding reweighting. If no
   * events have been generated, maxXSec() will be returned.
   */
  CrossSection xSecErrNoReweight() const {
    return attempts() ? maxXSec()*sqrt(theSumWeights2[3]+
				       theSumWeights2[4])/attempts() : maxXSec();
  }

  /**
   * The overestimated cross section.
   */
  CrossSection maxXSec() const { return theMaxXSec; }

  /**
   * The sum of the weights so far.
   */
  double sumWeights() const { return theSumWeights[0] - theSumWeights[2]; }

  /**
   * The sum of the squared weights so far.
   */
  double sumWeights2() const { return theSumWeights2[0] + theSumWeights2[2]; }

  /**
   * The sum of the weights so far, excluding reweighting.
   */
  double sumWeightsNoReweight() const { return theSumWeights[3] - theSumWeights[4]; }

  /**
   * The sum of the squared weights so far, excluding reweighting.
   */
  double sumWeights2NoReweight() const { return theSumWeights2[3] + theSumWeights2[4]; }

  /**
   * Number of attempts so far.
   */
  long attempts() const { return theAttempts; }

  /**
   * Number of attempts so far.
   */
  long accepted() const { return theAccepted-theVetoed; }

  /**
   * Set the overestimated cross section.
   */
  void maxXSec(CrossSection x) { theMaxXSec = x; }
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
   * Number of events vetoed after being accepted
   */
  long theVetoed;

  /**
   * The sum of the weights so far.
   */
  vector<double> theSumWeights;

  /**
   * The sum of the squared weights so far.
   */
  vector<double> theSumWeights2;

  /**
   * The last selected weight, ignoring reweighting.
   */
  double theLastWeight;

};

/** Ouptut an XSecStat to a persistent stream. */
PersistentOStream & operator<<(PersistentOStream &, const XSecStat &);

/** Input an XSecStat from a persistent stream. */
PersistentIStream & operator>>(PersistentIStream &, XSecStat &);

/** Add the contents of two XSecStat objects. */
inline XSecStat operator+(const XSecStat & x1, const XSecStat & x2) {
  XSecStat x = x1;
  return x += x2;
}

}

#endif /* THEPEG_XSecStat_H */
