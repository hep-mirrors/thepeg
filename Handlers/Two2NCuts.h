// -*- C++ -*-
#ifndef ThePEG_Two2NCuts_H
#define ThePEG_Two2NCuts_H
//
// This is the declaration of the <!id>Two2NCuts<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>Two2NCuts<!!id> inherits from the
// <!class>KinematicalCuts<!!class> class and introduces cuts on
// general 2->N subprocesses.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:KinematicalCuts.html">KinematicalCuts.h</a>.
// 

#include "ThePEG/Handlers/KinematicalCuts.h"
// #include "Two2NCuts.fh"
#include "Two2NCuts.xh"

namespace ThePEG {

class Two2NCuts: public KinematicalCuts {

  typedef map<pair<int,int>,Energy> Limits2Map;
  typedef map<Triplet<int,int,int>,Energy> Limits3Map;
  typedef vector<Energy> LimitsVector;
  typedef vector<string> StringVector;

public:

  inline Two2NCuts();
  inline Two2NCuts(const Two2NCuts &);
  virtual ~Two2NCuts();
  // Standard ctors and dtor.

public:

  double massMin(int n, int i) const;
  double massMax(int n, int i) const;
  // For a 2->n hard sub-process, the minimum and maximum values of
  // the masses of outgoing (resonance) particle i.

  double pTMin(int n, int i) const;
  double pTMax(int n, int i) const;
  // For a 2->n hard sub-process, the minimum and maximum values of
  // the transverse momentum of outgoing particle i.

  double diMassMin(int n, int i, int j) const;
  double diMassMax(int n, int i, int j) const;
  // For a 2->n hard sub-process, the minimum and maximum values of
  // the invariant mass of outgoing particles i and j.
  
protected:

  virtual void newcut(const SubProcess &) const ThePEG_THROW_SPEC((Veto));
  // This method is called by the corresponding cut method with the
  // primary SubProcess provided in its cm frame. This bas-class
  // method does nothing.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  string ssetMassMins(string);
  void setMassMins(Energy, int);
  void insMassMins(Energy, int);
  void delMassMins(int);
  LimitsVector getMassMins() const;
  StringVector sgetMassMins() const;
  // Utility functions for the interface.

  string ssetMassMaxs(string);
  void setMassMaxs(Energy, int);
  void insMassMaxs(Energy, int);
  void delMassMaxs(int);
  LimitsVector getMassMaxs() const;
  StringVector sgetMassMaxs() const;
  // Utility functions for the interface.

  string ssetPTMins(string);
  void setPTMins(Energy, int);
  void insPTMins(Energy, int);
  void delPTMins(int);
  LimitsVector getPTMins() const;
  StringVector sgetPTMins() const;
  // Utility functions for the interface.

  string ssetPTMaxs(string);
  void setPTMaxs(Energy, int);
  void insPTMaxs(Energy, int);
  void delPTMaxs(int);
  LimitsVector getPTMaxs() const;
  StringVector sgetPTMaxs() const;
  // Utility functions for the interface.

  string ssetDiMassMins(string);
  void setDiMassMins(Energy, int);
  void insDiMassMins(Energy, int);
  void delDiMassMins(int);
  LimitsVector getDiMassMins() const;
  StringVector sgetDiMassMins() const;
  // Utility functions for the interface.

  string ssetDiMassMaxs(string);
  void setDiMassMaxs(Energy, int);
  void insDiMassMaxs(Energy, int);
  void delDiMassMaxs(int);
  LimitsVector getDiMassMaxs() const;
  StringVector sgetDiMassMaxs() const;
  // Utility functions for the interface.

  pair<int,int> get2index(int k) const;
  Triplet<int,int,int> get3index(int k) const;
  inline int index2(const pair<int,int> &) const;
  inline int index3(const Triplet<int,int,int> &) const;
  // Utility functions for the interface.

private:

  Limits2Map theMassMins;
  Limits2Map theMassMaxs;
  // For a 2->n hard sub-process, the minimum and maximum values of
  // the masses of outgoing (resonance) particle i.

  Limits2Map thePTMins;
  Limits2Map thePTMaxs;
  // For a 2->n hard sub-process, the minimum and maximum values of
  // the transverse momentum of outgoing particle i.

  Limits3Map theDiMassMins;
  Limits3Map theDiMassMaxs;
  // For a 2->n hard sub-process, the minimum and maximum values of
  // the invariant mass of outgoing particles i and j.

private:

  static ClassDescription<Two2NCuts> initTwo2NCuts;
  // Describe concrete class with persistent data.

  Two2NCuts & operator=(const Two2NCuts &);
  //  Private and non-existent assignment operator.

};

// CLASSDOC OFF

ThePEG_DECLARE_DYNAMIC_CLASS_TRAITS(Two2NCuts,KinematicalCuts,"Two2NCuts.so");

}

#include "Two2NCuts.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Two2NCuts.tcc"
#endif

#endif /* ThePEG_Two2NCuts_H */
