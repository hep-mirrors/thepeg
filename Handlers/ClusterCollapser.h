// -*- C++ -*-
#ifndef ThePEG_ClusterCollapser_H
#define ThePEG_ClusterCollapser_H
//
// This is the declaration of the <!id>ClusterCollapser<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Handlers/StepHandler.h"
#include "ThePEG/Handlers/FlavourGenerator.h"
#include "ThePEG/EventRecord/ColourSinglet.h"
#include "ClusterCollapser.fh"
// #include "ClusterCollapser.xh"


namespace ThePEG {

class ClusterCollapser: public StepHandler {

public:

  typedef Ptr<FlavourGenerator>::pointer FlavGenPtr;

public:

  inline ClusterCollapser();
  inline ClusterCollapser(const ClusterCollapser &);
  virtual ~ClusterCollapser();
  // Standard ctors and dtor.

public:

  virtual void handle(PartialCollisionHandler & ch, const tPVector & tagged,
		      const Hint & hint) throw(Veto, Stop, Exception);
  // The main virtual method to be overridden by subclasses.

  virtual vector<ColourSinglet> collapse(tPVector tagged,
					 tStepPtr newstep);
  // Perform all necessary collapses. Return the uncollapsed clusters.

  virtual multimap<Energy,ColourSinglet>
  getSinglets(const tPVector & tagged) const;
  // Go through the tagged partons and extract all colour singlet
  // combination of partons. Order them in invariant mass (minus the
  // constituent masses of the partons).

  virtual ColourSinglet splitDiQuarkJunction(ColourSinglet & cs,
					     tStepPtr newStep) const;
  // If a singlet contains at least one diquark and a junction, split
  // the diquark and split off a new colour singlet.

  virtual ColourSinglet splitDiDiQuark(ColourSinglet & cs,
				       tStepPtr newStep) const;
  // If a singlet contains a simple string with diquarks in both ends,
  // split them into quarks and split off a new colour singlet.

  static bool diQuarkJunction(const ColourSinglet & cs);
  // Returns true iff the given singlet contains a junction and at
  // least one diquark.

  static bool diDiQuark(const ColourSinglet & cs);
  // Returns true iff the given singlet contains one string piece with
  // diquarks in both ends.

  inline Energy cut() const;
  // If the invariant mass of a cluster, minus the constituent masses
  // of its partons is below this cut, it will be collapsed into one
  // or two particles.

  inline int nTry2() const;
  // The number of attempts to collapse a cluster into two particles,
  // before it is collapsed into one particle.

  static Energy mass(const ColourSinglet & cl);
  // Return the invariant mass of a cluster minus the constituent
  // masses of its partons.

  virtual tcPDPtr pickFlavour() const;
  // Pick a random flavour. Default version picks u,d or s with ratio
  // 3:3:1.

protected:

  virtual void collapse(tStepPtr newStep, const ColourSinglet & cs,
			const tPVector & tagged) const;
  virtual bool collapse2(tStepPtr newStep, const ColourSinglet & cs) const;
  // Parform the actual collapse of a cluster into one or two hadrons
  // and add the produced hadrons into the given step as decay
  // products of the partons in the cluster. The latter returns false
  // if it fails, the former takes an extra argument with particles for
  // momentum compensation.

  virtual tPVector getCompensators(Energy mh, const ColourSinglet & cs,
				   const tPVector & tagged,
				   tStepPtr newStep) const;
  // Look through the tagged vector for particles (which are not in
  // the colour singlet cs) which can be used to compensate momentum
  // when cs collapses into a hadron with mass mh. These partons are
  // then copied into the new step so that their momentum can be
  // changed and then returned.

  virtual tcPDPtr getHadron(const ColourSinglet & cs) const;
  // Return a hadron into which the given cluster may collapse.

  virtual tcPDPair getHadrons(const ColourSinglet & cs) const;
  // Return a pair of hadrons  into which the given cluster may collapse.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void doinitrun();
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

  class ClusterException: public Exception {
  public:
    ClusterException(const ClusterCollapser & cc) {
      theMessage << "In ClusterCollapser '" << cc.name() << "': ";
    }
  };

private:

  Energy theEnergyCut;
  // If the invariant mass of a cluster, minus the constituent masses
  // of its partons is below this cut, it will be collapsed into one
  // or two particles.

  int theNTry2;
  // The number of attempts to collapse a cluster into two particles,
  // before it is collapsed into one particle.

  FlavGenPtr flavGen;
  // The flavour generator object to use to combine quarks and diqurks
  // into hadrons.

protected:

  Exception::Severity errorlevel;
  // How should we respond to errors? 0 means do nothing, ie. the
  // cluster will not be collapsed, or the momentum will not be
  // consterved. Otherwise the severity will be what is defined in the
  // class Exception.

  double pStrange;
  // The relative probability to produce a s-sbar pair in a split as
  // compared to a u-ubar or d-dbar pair.

private:

  static ClassDescription<ClusterCollapser> initClusterCollapser;
  // Describe a concrete class with persistent data.

  ClusterCollapser & operator=(const ClusterCollapser &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of ClusterCollapser.
template <>
struct BaseClassTrait<ClusterCollapser,1> {
  typedef StepHandler NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ClusterCollapser>: public ClassTraitsBase<ClusterCollapser> {
  static string className() { return "/ThePEG/ClusterCollapser"; }
  // Return the class name.
  static string library() { return "libThePEGString.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "ClusterCollapser.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ClusterCollapser.tcc"
#endif

#endif /* ThePEG_ClusterCollapser_H */
