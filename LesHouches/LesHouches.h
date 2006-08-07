// -*- C++ -*-
#ifndef THEPEG_LesHouches_H
#define THEPEG_LesHouches_H
//
// This is the declaration of the LesHouches class.
//

#include "ThePEG/Config/ThePEG.h"

namespace ThePEG {

/**
 * The HEPRUP class is a simple container corresponding to the Les
 * Houches accord (hep-ph/0109068) common block with the same
 * name. The members are named in the same way as in the common
 * block. However, fortran arrays are represented by vectors, except
 * for the arrays of length two which are represented by pair objects.
 */
class HEPRUP {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline HEPRUP();

  /**
   * Copy-constructor.
   */
  inline HEPRUP(const HEPRUP &);

  /**
   * Assignment operator.
   */
  inline HEPRUP & operator=(const HEPRUP &);

  /**
   * Destructor.
   */
  inline ~HEPRUP();
  //@}

public:

  /**
   * PDG id's of beam particles. (first/second is in +/-z direction).
   */
  pair<long,long> IDBMUP;

  /**
   * Energy of beam particles given in GeV.
   */
  pair<double,double> EBMUP;

  /**
   * The author group for the PDF used for the beams according to the
   * PDFLib specification.
   */
  pair<int,int> PDFGUP;

  /**
   * The id number the PDF used for the beams according to the
   * PDFLib specification.
   */
  pair<int,int> PDFSUP;

  /**
   * Master switch indicating how the ME generator envisages the
   * events weights should be interpreted according to the Les Houches
   * accord.
   */
  int IDWTUP;

  /**
   * The number of different subprocesses in this file (should
   * typically be just one)
   */
  int NPRUP;

  /**
   * The cross sections for the different subprocesses in pb.
   */
  vector<double> XSECUP;

  /**
   * The statistical error in the cross sections for the different
   * subprocesses in pb.
   */
  vector<double> XERRUP;

  /**
   * The maximum event weights (in XWGTUP) for different subprocesses.
   */
  vector<double> XMAXUP;

  /**
   * The subprocess code for the different subprocesses.
   */
  vector<int> LPRUP;

};


/**
 * The HEPEUP class is a simple container corresponding to the Les
 * Houches accord (hep-ph/0109068) common block with the same
 * name. The members are named in the same way as in the common
 * block. However, fortran arrays are represented by vectors, except
 * for the arrays of length two which are represented by pair objects.
 */
class HEPEUP {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline HEPEUP();

  /**
   * Copy-constructor.
   */
  inline HEPEUP(const HEPEUP &);

  /**
   * Assignment operator.
   */
  inline HEPEUP & operator=(const HEPEUP &);

  /**
   * Destructor.
   */
  inline ~HEPEUP();
  //@}

public:

  /**
   * The number of particle entries in the current event.
   */
  int NUP;

  /**
   * The subprocess code for this event (as given in LPRUP).
   */
  int IDPRUP;

  /**
   * The weight for this event.
   */
  double XWGTUP;

  /**
   * The PDF weights for the two incoming partons. Note that this
   * variable is not present in the current LesHouches accord
   * (hep-ph/0109068), hopefully it will be present in a future
   * accord.
   */
  pair<double,double> XPDWUP;

  /**
   * The scale in GeV used in the calculation of the PDF's in this
   * event.
   */
  double SCALUP;

  /**
   * The value of the QED coupling used in this event.
   */
  double AQEDUP;

  /**
   * The value of the QCD coupling used in this event.
   */
  double AQCDUP;

  /**
   * The PDG id's for the particle entries in this event.
   */
  vector<long> IDUP;

  /**
   * The status codes for the particle entries in this event.
   */
  vector<int> ISTUP;

  /**
   * Indices for the first and last mother for the particle entries in
   * this event.
   */
  vector< pair<int,int> > MOTHUP;

  /**
   * The colour-line indices (first(second) is (anti)colour) for the
   * particle entries in this event.
   */
  vector< pair<int,int> > ICOLUP;

  /**
   * Lab frame momentum (Px, Py, Pz, E and M in GeV) for the particle
   * entries in this event.
   */
  vector< vector<double> > PUP;

  /**
   * Invariant lifetime (c*tau, distance from production to decay im
   * mm) for the particle entries in this event.
   */
  vector<double> VTIMUP;

  /**
   * Spin info for the particle entries in this event given as the
   * cosine of the angle between the spin vector of a particle and the
   * 3-momentum of the decaying particle, specified in the lab frame.
   */
  vector<double> SPINUP;

};

}

#include "LesHouches.icc"

#endif /* THEPEG_LesHouches_H */
