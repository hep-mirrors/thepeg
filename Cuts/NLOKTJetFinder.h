// -*- C++ -*-
//
// NLOKTJetFinder.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
// Copyright (C) 2009-2011 Simon Platzer
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef THEPEG_NLOKTJetFinder_H
#define THEPEG_NLOKTJetFinder_H
//
// This is the declaration of the NLOKTJetFinder class.
//

#include "ThePEG/Cuts/JetFinder.h"

namespace ThePEG {

/**
 * NLOKTJetFinder implements the class of longitudinally invariant kt
 * jet clustering algorithms, as relevant for cuts on the real
 * emission contribution to a NLO calculation. Recombination is
 * exclusively performed using the pt scheme.
 *
 * @see \ref NLOKTJetFinderInterfaces "The interfaces"
 * defined for NLOKTJetFinder.
 */
class NLOKTJetFinder: public JetFinder {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  NLOKTJetFinder();

  /**
   * The destructor.
   */
  virtual ~NLOKTJetFinder();
  //@}

public:

  /**
   * Perform jet clustering on the given outgoing particles.
   * Optionally, information on the incoming particles is provided.
   * Return true, if a clustering has been performed.
   */
  virtual bool cluster(tcPDVector & ptype, vector<LorentzMomentum> & p,
		       tcCutsPtr parent, tcPDPtr t1 = tcPDPtr(),
		       tcPDPtr t2 = tcPDPtr()) const;

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
   * when this class is dynamically loaded.
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


// If needed, insert declarations of virtual function defined in the
// InterfacedBase class here (using ThePEG-interfaced-decl in Emacs).

private:

  /**
   * Perform pt scheme recombination.
   */
  LorentzMomentum recombine(const LorentzMomentum& pi,
			    const LorentzMomentum& pj) const;

private:

  /**
   * The resolution cut. Ignored, if algorithm is to act inclusively.
   */
  Energy2 theDCut;

  /**
   * The `cone radius' R. Ignored (R=1), if algorithm is to act
   * exclusively.
   */
  double theConeRadius;

  /**
   * The possible variants.
   */
  enum variants {
    kt = 1,
    ca = 2,
    antikt = 3
  };

  /**
   * The variant.
   */
  int theVariant;

  /**
   * The possible modes.
   */
  enum modes {
    inclusive = 1,
    exclusive = 2
  };

  /**
   * The mode.
   */
  int theMode;

  /**
   * The possible measures. Also triggers the choice of recombination
   * scheme by default.
   */
  enum measures {
    pt = 1,
    e = 2
  };

  /**
   * The measure
   */
  int theMeasure;

  /**
   * The possible recombination schemes.
   */
  enum recombinations {
    recoDefault = 1,
    recoPt = 2,
    recoE = 3
  };

  /**
   * The recombination scheme
   */
  int theRecombination;


  /**
   * Choose to not consider partons as jets which are out of in terms
   * or rapidity or transverse momentum
   */
  bool theRemoveOutOfRange;

private:

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  NLOKTJetFinder & operator=(const NLOKTJetFinder &);

};

}

#endif /* THEPEG_NLOKTJetFinder_H */
