// -*- C++ -*-
//
// JetFinder.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
// Copyright (C) 2009-2011 Simon Platzer
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef THEPEG_JetFinder_H
#define THEPEG_JetFinder_H
//
// This is the declaration of the JetFinder class.
//

#include "ThePEG/Interface/Interfaced.h"
#include "ThePEG/PDT/MatcherBase.h"
#include "Cuts.fh"

namespace ThePEG {

/**
 * JetFinder defines an interface to jet finders to be used when cuts
 * should actually be defined on the level of reconstructed jets such
 * as typically encountered in higher order corrections.
 *
 * @see \ref JetFinderInterfaces "The interfaces"
 * defined for JetFinder.
 */
class JetFinder: public Interfaced {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  JetFinder();

  /**
   * The destructor.
   */
  virtual ~JetFinder();
  //@}

public:

  /**
   * Perform jet clustering on the given outgoing particles.
   * Optionally, information on the incoming particles is provided.
   * Return true, if a clustering has been performed.
   */
  virtual bool cluster(tcPDVector & ptype, vector<LorentzMomentum> & p,
		       tcCutsPtr parent, tcPDPtr t1 = tcPDPtr(),
		       tcPDPtr t2 = tcPDPtr()) const = 0;

  /**
   * Return the matcher for unresolved partons.
   */
  Ptr<MatcherBase>::tptr unresolvedMatcher() const { return theUnresolvedMatcher; }

  /**
   * Set the minimum number of outgoing partons on which clustering
   * should be performed.
   */
  void minOutgoing(unsigned int n) { theMinOutgoing = n; }

  /**
   * Return the minimum number of outgoing partons on which clustering
   * should be performed.
   */
  unsigned int minOutgoing() const { return theMinOutgoing; }

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


// If needed, insert declarations of virtual function defined in the
// InterfacedBase class here (using ThePEG-interfaced-decl in Emacs).


private:

  /**
   * A matcher for unresolved partons.
   */
  Ptr<MatcherBase>::ptr theUnresolvedMatcher;

  /**
   * The minimum number of outgoing partons on which clustering
   * should be performed.
   */
  unsigned int theMinOutgoing;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  JetFinder & operator=(const JetFinder &);

};

}

#endif /* THEPEG_JetFinder_H */
