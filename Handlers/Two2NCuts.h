// -*- C++ -*-
#ifndef ThePEG_Two2NCuts_H
#define ThePEG_Two2NCuts_H
// This is the declaration of the Two2NCuts class.

#include "ThePEG/Handlers/KinematicalCuts.h"
// #include "Two2NCuts.fh"
#include "Two2NCuts.xh"

namespace ThePEG {

/**
 * Two2NCuts inherits from the KinematicalCuts class and introduces
 * cuts on general \f$2\rightarrow N\f$ subprocesses.
 *
 * @see KinematicalCuts
 */
class Two2NCuts: public KinematicalCuts {

  /** Map two-dimensional indices to energies. */
  typedef map<pair<int,int>,Energy> Limits2Map;

  /** Map three-dimensional indices to energies. */
  typedef map<Triplet<int,int,int>,Energy> Limits3Map;

  /** A vector of energies.. */
  typedef vector<Energy> LimitsVector;

  /** A vector of character strings. */
  typedef vector<string> StringVector;

public:

  //@{
  /**
   * Default constructor.
   */
  inline Two2NCuts();

  /**
   * Copy-constructor.
   */
  inline Two2NCuts(const Two2NCuts &);

  /**
   * Destructor.
   */
  virtual ~Two2NCuts();
  //@}

public:

  /** @name Access individual cuts. */
  //@{
  /**
   * Minimum mass. For a 2\f$\rightarrow\f$\a n hard sub-process, the
   * minimum value of the masses of outgoing (resonance) particle \a
   * i.
   */
  double massMin(int n, int i) const;

  /**
   * Maximum mass. For a 2\f$\rightarrow\f$\a n hard sub-process, the
   * maximum value of the masses of outgoing (resonance) particle \a
   * i.
   */
  double massMax(int n, int i) const;

  /**
   * Minimum transverse momenta. For a 2\f$\rightarrow\f$\a n hard
   * sub-process, the minimum value of the transverse momentum of
   * outgoing particle \a i.
   */
  double pTMin(int n, int i) const;

  /**
   * Maximum mass. For a 2\f$\rightarrow\f$\a n hard sub-process, the
   * maximum value of the transverse momentum of outgoing particle \a
   * i.
   */
  double pTMax(int n, int i) const;

  /**
   * Minimum invariant mass. For a 2\f$\rightarrow\f$\a n hard
   * sub-process, the minimum value of the invariant mass of outgoing
   * particles \a i and \a j.
   */
  double diMassMin(int n, int i, int j) const;

  /**
   * Maximum invariant mass. For a 2\f$\rightarrow\f$\a n hard
   * sub-process, the maximum value of the invariant mass of outgoing
   * particles \a i and \a j.
   */
  double diMassMax(int n, int i, int j) const;
  //@}
  
protected:

  /**
   * This method is called by the KinematicalCuts::cut(const
   * SubProcess &) function of the base class with the primary
   * SubProcess provided in its cm frame. All the cuts introduced in
   * this class are checked.
   */
  virtual void newcut(const SubProcess &) const ThePEG_THROW_SPEC((Veto));

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
  inline virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr fullclone() const;
  //@}

protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish();

  /**
   * Rebind pointer to other Interfaced objects. Called in the setup phase
   * after all objects used in an EventGenerator has been cloned so that
   * the pointers will refer to the cloned objects afterwards.
   * @param trans a TranslationMap relating the original objects to
   * their respective clones.
   * @throws RebindException if no cloned object was found for a given pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in
   * this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * Utility function for the interface.
   */
  string ssetMassMins(string);

  /**
   * Utility function for the interface.
   */
  void setMassMins(Energy, int);

  /**
   * Utility function for the interface.
   */
  void insMassMins(Energy, int);

  /**
   * Utility function for the interface.
   */
  void delMassMins(int);

  /**
   * Utility function for the interface.
   */
  LimitsVector getMassMins() const;

  /**
   * Utility function for the interface.
   */
  StringVector sgetMassMins() const;


  /**
   * Utility function for the interface.
   */
  string ssetMassMaxs(string);

  /**
   * Utility function for the interface.
   */
  void setMassMaxs(Energy, int);

  /**
   * Utility function for the interface.
   */
  void insMassMaxs(Energy, int);

  /**
   * Utility function for the interface.
   */
  void delMassMaxs(int);

  /**
   * Utility function for the interface.
   */
  LimitsVector getMassMaxs() const;

  /**
   * Utility function for the interface.
   */
  StringVector sgetMassMaxs() const;

  /**
   * Utility function for the interface.
   */
  string ssetPTMins(string);

  /**
   * Utility function for the interface.
   */
  void setPTMins(Energy, int);

  /**
   * Utility function for the interface.
   */
  void insPTMins(Energy, int);

  /**
   * Utility function for the interface.
   */
  void delPTMins(int);

  /**
   * Utility function for the interface.
   */
  LimitsVector getPTMins() const;

  /**
   * Utility function for the interface.
   */
  StringVector sgetPTMins() const;

  /**
   * Utility function for the interface.
   */
  string ssetPTMaxs(string);

  /**
   * Utility function for the interface.
   */
  void setPTMaxs(Energy, int);

  /**
   * Utility function for the interface.
   */
  void insPTMaxs(Energy, int);

  /**
   * Utility function for the interface.
   */
  void delPTMaxs(int);

  /**
   * Utility function for the interface.
   */
  LimitsVector getPTMaxs() const;

  /**
   * Utility function for the interface.
   */
  StringVector sgetPTMaxs() const;

  /**
   * Utility function for the interface.
   */
  string ssetDiMassMins(string);

  /**
   * Utility function for the interface.
   */
  void setDiMassMins(Energy, int);

  /**
   * Utility function for the interface.
   */
  void insDiMassMins(Energy, int);

  /**
   * Utility function for the interface.
   */
  void delDiMassMins(int);

  /**
   * Utility function for the interface.
   */
  LimitsVector getDiMassMins() const;

  /**
   * Utility function for the interface.
   */
  StringVector sgetDiMassMins() const;


  /**
   * Utility function for the interface.
   */
  string ssetDiMassMaxs(string);

  /**
   * Utility function for the interface.
   */
  void setDiMassMaxs(Energy, int);

  /**
   * Utility function for the interface.
   */
  void insDiMassMaxs(Energy, int);

  /**
   * Utility function for the interface.
   */
  void delDiMassMaxs(int);

  /**
   * Utility function for the interface.
   */
  LimitsVector getDiMassMaxs() const;

  /**
   * Utility function for the interface.
   */
  StringVector sgetDiMassMaxs() const;

  /**
   * Utility function for the interface.
   */
  pair<int,int> get2index(int k) const;

  /**
   * Utility function for the interface.
   */
  Triplet<int,int,int> get3index(int k) const;

  /**
   * Utility function for the interface.
   */
  inline int index2(const pair<int,int> &) const;

  /**
   * Utility function for the interface.
   */
  inline int index3(const Triplet<int,int,int> &) const;

private:

  /**
   * For a 2\f$\rightarrow\f$n hard sub-process, the minimum values of
   * the masses of outgoing (resonance) particle i.
   */
  Limits2Map theMassMins;

  /**
   * For a 2\f$\rightarrow\f$n hard sub-process, the maximum values of
   * the masses of outgoing (resonance) particle i.
   */
  Limits2Map theMassMaxs;

  /**
   * For a 2\f$\rightarrow\f$n hard sub-process, the minimum values of
   * the transverse momentum of outgoing particle i.
   */
  Limits2Map thePTMins;

  /**
   * For a 2\f$\rightarrow\f$n hard sub-process, the maximum values of
   * the transverse momentum of outgoing particle i.
   */
  Limits2Map thePTMaxs;

  /**
   * For a 2\f$\rightarrow\f$n hard sub-process, the minimum values of
   * the invariant mass of outgoing particles i and j.
   */
  Limits3Map theDiMassMins;
  /**
   * For a 2\f$\rightarrow\f$n hard sub-process, the maximum values of
   * the invariant mass of outgoing particles i and j.
   */
  Limits3Map theDiMassMaxs;

private:

  /**
   * Describe concrete class with persistent data.
   */
  static ClassDescription<Two2NCuts> initTwo2NCuts;

  /**
   *  Private and non-existent assignment operator.
   */
  Two2NCuts & operator=(const Two2NCuts &);

};


ThePEG_DECLARE_DYNAMIC_CLASS_TRAITS(Two2NCuts,KinematicalCuts,"Two2NCuts.so");

}

#include "Two2NCuts.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Two2NCuts.tcc"
#endif

#endif /* ThePEG_Two2NCuts_H */
