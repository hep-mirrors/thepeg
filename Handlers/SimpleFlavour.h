// -*- C++ -*-
#ifndef THEPEG_SimpleFlavour_H
#define THEPEG_SimpleFlavour_H
//
// This is the declaration of the <!id>SimpleFlavour<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This is a simple class to generate hadrons given the quark
// flavours. It implements a simplified version of the model of the
// old fortran version of Pythia.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:FlavourGenerator.html">FlavourGenerator.h</a>.
// 

#include "ThePEG/Handlers/FlavourGenerator.h"
#include "ThePEG/Utilities/VSelector.h"
// #include "SimpleFlavour.fh"
// #include "SimpleFlavour.xh"

namespace ThePEG {

class SimpleFlavour: public FlavourGenerator {

public:

  inline SimpleFlavour();
  inline SimpleFlavour(const SimpleFlavour &);
  virtual ~SimpleFlavour();
  // Standard ctors and dtor.

public:

  virtual tcPDPair generateHadron(tcPDPtr quark) const;
  // Given a quark(antiquark, diquark or antidiquark), choose a
  // quark-antiquark (or antidiquark-diquark) pair. Return (first) a
  // hadron formed by the original quark and the anti-quark together
  // with (second) the generated quark.

  virtual tcPDPtr getHadron(long iq1, long iq2) const;
  // Return a hadron with the flavour content given by the
  // (anti)(di)quarks codes in the argument. If no corresponding
  // hadron was formed it should return the null pointer.

  virtual tcPDPtr getBaryon(long q1, long q2, long q3) const;
  // Return a baryon with the flavour content given by the
  // (anti)quarks codes in the argument. If no corresponding hadron
  // was formed it should return the null pointer.

  virtual long selectQuark() const;
  // Generate a random quark flavour.

  virtual long selectFlavour() const;
  // Generate a random (di)quark flavour.

public:

  inline double sSup() const;
  // Return the suppression factor of strange quarks w.r.t. u and d.

  inline double diSup() const;
  // Return the suppression factor for di-quarks w.r.t. quarks

  inline double di1Sup() const;
  // Return the suppression of spin-1 di-quarks w.r.t. spin-0 ones;

  inline double diSSup() const;
  // Return the suppression of strange di-quarks w.r.t. u and d ones
  // in addition to the standard strangness suppression of quarks.

  inline double etaSup() const;
  // Return the extra suppression of eta's

  inline double etaPSup() const;
  // Return the extra suppression of ets-prime's

  inline double baryon10Sup() const;
  // Return the extra suppression for baryons of the spin 3/2
  // decuplet.

  inline double pSpin1() const;
  // Return the probability that light (u/d) mesons has spin 1;

  inline double pSpinS1() const;
  // Return the probability that strange mesons has spin 1;

  inline double pSpinC1() const;
  // Return the probability that charmed and heavier mesons has spin
  // 1;

protected:

  virtual double vectorMesonProbability(long iq1, long iq2) const;
  // Return the probability that the given quark flavours end up in a
  // vector meson rather than in a pseudo scalar meson.

  virtual double baryonDecupletProbability(long iq1, long iq2) const;
  // Return the probability that the given quark and diquark flavours
  // end up in a spin 3/2 decuplet baryon rather than in a spin 1/2
  // octet baryon.

  virtual tcPDPtr pseudoScalarMeson(long iq, long iqbar) const;
  // Return a pseudo scalar meson formed by the two quark flavours.

  virtual tcPDPtr vectorMeson(long iq, long iqbar) const;
  // Return a vector meson formed by the two quark flavours.

  virtual tcPDPtr baryonOctet(long iq, long idq) const;
  // Return a spin 1/2 octet baryon formed by the given quark and
  // diquark flavours.

  virtual tcPDPtr baryonDecuplet(long iq, long idq) const;
  // Return a spin 3/2 decuplet baryon formed by the given quark and
  // diquark flavours.

  virtual long pseudoScalarId(long iqh, long iql) const;
  // Return the PDG code of a pseudo scalar meson formed by the two
  // quark flavours for iqh >= iql > 0.

  virtual long vectorId(long iqh, long iql) const;
  // Return the PDG code of a vector meson formed by the two quark
  // flavours for iqh >= iql > 0.

  virtual long baryonOctetId(long iqa, long iqb, long iqc,
			     long iq, bool dqs1) const;
  // Return the PDG code for a spin 1/2 octet baryon formed by the
  // given quark flavours (iqa >= iqb >= iqc > 0). iq is one of the
  // flavours and the other two are assumed to be in a diquark (in a
  // spin-1 state if dqs1).

  virtual long baryonDecupletId(long iqa, long iqb, long iqc) const;
  // Return the PDG code for a spin 3/2 decuplet baryon formed by the
  // given quark flavours (iqa >= iqb >= iqc > 0).

  void clear();
  // Clear all cashed weights.

  static double weightSU6QDiQSpin(long iq, long idq, int spin);
  // Return the SU(6) weight for the given quark and di-quark flavours
  // to end up with in a baryon with the given spin (2S+1).


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

private:

  double theSSup;
  // Suppression factor of strange quarks w.r.t. u and d.

  double theDiSup;
  // Suppression factor for di-quarks w.r.t. quarks.

  double theDi1Sup;
  // Suppression of spin-1 di-quarks w.r.t. spin-0 ones.

  double theDiSSup;
  // Suppression of strange di-quarks w.r.t. u and d ones in addition
  // to the standard strangness suppression of quarks.

  double theEtaSup;
  // Extra suppression of eta's.

  double theEtaPSup;
  // Extra suppression of ets-prime's.

  double theBaryon10Sup;
  // Extra suppression for baryons of the spin 3/2 decuplet.

  double thePSpin1;
  // Probability that light (u/d) mesons has spin 1.

  double thePSpinS1;
  // Probability that strange mesons has spin 1.

  double thePSpinC1;
  // Probability that charmed and heavier mesons has spin 1.

  mutable VSelector<long> theFlavourSelector;
  // A selector used to weight thecreation of (di)quark-anti(di)quark
  // pairs.


private:

  static ClassDescription<SimpleFlavour> initSimpleFlavour;
  // Describe a concrete class with persistent data.

  SimpleFlavour & operator=(const SimpleFlavour &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of SimpleFlavour.
template <>
struct BaseClassTrait<SimpleFlavour,1> {
  typedef FlavourGenerator NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<SimpleFlavour>
  : public ClassTraitsBase<SimpleFlavour> {
  static string className() { return "ThePEG::SimpleFlavour"; }
  // Return the class name.
  static string library() { return "SimpleFlavour.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "SimpleFlavour.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleFlavour.tcc"
#endif

#endif /* THEPEG_SimpleFlavour_H */
