// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Two2NCuts class.
//

#include "Two2NCuts.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/Interface/ParVector.h"
#include "ThePEG/Interface/Command.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Two2NCuts.tcc"
#endif

using namespace ThePEG;

Two2NCuts::~Two2NCuts() {}

void Two2NCuts::newcut(const SubProcess & sp) const ThePEG_THROW_SPEC((Veto)) {
  KinematicalCuts::newcut(sp);
  const ParticleVector & out = sp.outgoing();
  int N = out.size();

  // Check for lower limits of outgoing particle masses
  for ( Limits2Map::const_iterator it =
	  theMassMins.lower_bound(make_pair(N, 0));
	it != theMassMins.lower_bound(make_pair(N+1, 0)); ++ it )
    if ( out[it->first.second-1]->mass() < it->second ) throw Veto();

  // Check for upper limits of outgoing particle masses
  for ( Limits2Map::const_iterator it =
	  theMassMaxs.lower_bound(make_pair(N, 0));
	it != theMassMaxs.lower_bound(make_pair(N+1, 0)); ++ it )
    if ( it->second > massMin(it->first.first, it->first.second) &&
	 out[it->first.second-1]->mass() > it->second ) throw Veto();

  // Check for lower limits of outgoing particle pt
  for ( Limits2Map::const_iterator it =
	  thePTMins.lower_bound(make_pair(N, 0));
	it != thePTMins.lower_bound(make_pair(N+1, 0)); ++ it )
    if ( out[it->first.second-1]->momentum().perp() < it->second ) throw Veto();

  // Check for upper limits of outgoing particle pt
  for ( Limits2Map::const_iterator it =
	  thePTMaxs.lower_bound(make_pair(N, 0));
	it != thePTMaxs.lower_bound(make_pair(N+1, 0)); ++ it )
    if ( it->second > pTMin(it->first.first, it->first.second) &&
	 out[it->first.second-1]->momentum().perp() > it->second ) throw Veto();

  // Check for lower limits of outgoing di-particle masses
  for ( Limits3Map::const_iterator it =
	  theDiMassMins.lower_bound(makeTriplet(N, 0, 0));
	it != theDiMassMins.lower_bound(makeTriplet(N+1, 0, 0)); ++ it )
    if ( (out[it->first.second-1]->momentum() +
	  out[it->first.third-1]->momentum()).m() < it->second ) throw Veto();

  // Check for upper limits of outgoing di-particle masses
  for ( Limits3Map::const_iterator it =
	  theDiMassMaxs.lower_bound(makeTriplet(N, 0, 0));
	it != theDiMassMaxs.lower_bound(makeTriplet(N+1, 0, 0)); ++ it )
    if ( it->second >
	 diMassMin(it->first.first, it->first.second, it->first.third) &&
	 (out[it->first.second-1]->momentum() +
	  out[it->first.third-1]->momentum()).m() > it->second ) throw Veto();

}

Energy Two2NCuts::massMin(int n, int i) const {
  Limits2Map::const_iterator it = theMassMins.find(make_pair(n, i));
  return it == theMassMins.end()? 0.0*GeV: it->second;
}

Energy Two2NCuts::massMax(int n, int i) const {
  Limits2Map::const_iterator it = theMassMaxs.find(make_pair(n, i));
  if ( it == theMassMaxs.end() ) return Constants::MaxEnergy;
  if ( it->second < massMin(n, i) ) return Constants::MaxEnergy;
  return it->second;
}

Energy Two2NCuts::pTMin(int n, int i) const {
  Limits2Map::const_iterator it = thePTMins.find(make_pair(n, i));
  return it == thePTMins.end()? 0.0*GeV: it->second;
}

Energy Two2NCuts::pTMax(int n, int i) const {
  Limits2Map::const_iterator it = thePTMaxs.find(make_pair(n, i));
  if ( it == thePTMaxs.end() ) return Constants::MaxEnergy;
  if ( it->second < pTMin(n, i) ) return Constants::MaxEnergy;
  return it->second;
}

Energy Two2NCuts::diMassMin(int n, int i, int j) const {
  if ( n < 2 ) return 0.0*GeV;
  if ( i == j ) return massMin(n, i);
  if ( i < j ) swap(i, j);
  Limits3Map::const_iterator it =
    theDiMassMins.find(makeTriplet(n, i, j));
  return it == theDiMassMins.end()? 0.0*GeV: it->second;
}

Energy Two2NCuts::diMassMax(int n, int i, int j) const {
  if ( n < 2 ) return Constants::MaxEnergy;
  if ( i == j ) return massMax(n, i);
  if ( i < j ) swap(i, j);
  Limits3Map::const_iterator it =
    theDiMassMaxs.find(makeTriplet(n, i, j));
  if ( it == theDiMassMaxs.end() ) return Constants::MaxEnergy;
  if ( it->second < diMassMin(n, i, j) ) return Constants::MaxEnergy;
  return it->second;
}

pair<int,int> Two2NCuts::get2index(int k) const {
  pair<int,int> r(1, 0);
  while ( r.first*(r.first+1) <= 2*k ) ++r.first;
  r.second = k - (r.first*(r.first-1))/2;
  return r;
}

Triplet<int,int,int> Two2NCuts::get3index(int k) const {
  Triplet<int,int,int> r(2, 2, 0);
  while ( (r.first+1)*r.first*(r.first-1) <= 6*k ) ++r.first;
  k -= (r.first*(r.first-1)*(r.first-2))/6;
  while ( r.second*(r.second-1) <= 2*k ) ++r.second;
  r.third = k - ((r.second-1)*(r.second-2))/2;
  return r;
}

string Two2NCuts::ssetMassMins(string arg) {
  istringstream is(arg);
  int n;
  int i;
  Energy e;
  is >> n >> i >> e;
  if ( !is || i > n || i <= 0 )
    throw KinCutCmdFail2(*this, arg, "SetResonanceMassMin");
  theMassMins[make_pair(n, i)] = e;
  return "New minimum for mass of particle i in 2->n processes: " + arg;
}

void Two2NCuts::setMassMins(Energy e, int i) {
  theMassMins[get2index(i)] = e;
}

void Two2NCuts::insMassMins(Energy e, int i) {
  theMassMins[get2index(i)] = e;
}

void Two2NCuts::delMassMins(int i) {
  Limits2Map::iterator it = theMassMins.find(get2index(i));
  if ( it != theMassMins.end() ) theMassMins.erase(it);
}

Two2NCuts::LimitsVector Two2NCuts::getMassMins() const {
  LimitsVector res;
  for ( Limits2Map::const_iterator it = theMassMins.begin();
	it != theMassMins.end(); ++it ) {
    res.resize(index2(it->first)+1);
    res[index2(it->first)] = it->second;
  }
  return res;
}

Two2NCuts::StringVector Two2NCuts::sgetMassMins() const {
  StringVector r;
  for ( Limits2Map::const_iterator it = theMassMins.begin();
	it != theMassMins.end(); ++it ) {
    int n = it->first.first;
    int i = it->first.second;
    ostringstream os;
    os << "(index=" << index2(it->first) << " n=" << n << " i=" << i << ") "
       << it->second/GeV << "GeV";
    r.push_back(os.str());
  }
  return r;
}

string Two2NCuts::ssetMassMaxs(string arg) {
  istringstream is(arg);
  int n;
  int i;
  Energy e;
  is >> n >> i >> e;
  if ( !is || i > n || i <= 0 )
    throw KinCutCmdFail2(*this, arg, "SetResonanceMassMax");
  theMassMaxs[make_pair(n, i)] = e;
  return "New maximum for mass of particle i in 2->n processes: " + arg;
}

void Two2NCuts::setMassMaxs(Energy e, int i) {
  theMassMaxs[get2index(i)] = e;
}

void Two2NCuts::insMassMaxs(Energy e, int i) {
  theMassMaxs[get2index(i)] = e;
}

void Two2NCuts::delMassMaxs(int i) {
  Limits2Map::iterator it = theMassMaxs.find(get2index(i));
  if ( it != theMassMaxs.end() ) theMassMaxs.erase(it);
}

Two2NCuts::LimitsVector Two2NCuts::getMassMaxs() const {
  LimitsVector res;
  for ( Limits2Map::const_iterator it = theMassMaxs.begin();
	it != theMassMaxs.end(); ++it ) {
    res.resize(index2(it->first)+1);
    res[index2(it->first)] = it->second;
  }
  return res;
}

Two2NCuts::StringVector Two2NCuts::sgetMassMaxs() const {
  StringVector r;
  for ( Limits2Map::const_iterator it = theMassMaxs.begin();
	it != theMassMaxs.end(); ++it ) {
    int n = it->first.first;
    int i = it->first.second;
    ostringstream os;
    os << "(index=" << index2(it->first) << " n=" << n << " i=" << i << ") "
       << it->second/GeV << "GeV";
    r.push_back(os.str());
  }
  return r;
}

string Two2NCuts::ssetPTMins(string arg) {
  istringstream is(arg);
  int n;
  int i;
  Energy e;
  is >> n >> i >> e;
  if ( !is || i > n || i <= 0 )
    throw KinCutCmdFail1(*this, arg, "SetPTMin");
  thePTMins[make_pair(n, i)] = e;
  return "New minimum for pT of particle i in 2->n processes: " + arg;
}

void Two2NCuts::setPTMins(Energy e, int i) {
  thePTMins[get2index(i)] = e;
}

void Two2NCuts::insPTMins(Energy e, int i) {
  thePTMins[get2index(i)] = e;
}

void Two2NCuts::delPTMins(int i) {
  Limits2Map::iterator it = thePTMins.find(get2index(i));
  if ( it != thePTMins.end() ) thePTMins.erase(it);
}

Two2NCuts::LimitsVector Two2NCuts::getPTMins() const {
  LimitsVector res;
  for ( Limits2Map::const_iterator it = thePTMins.begin();
	it != thePTMins.end(); ++it ) {
    res.resize(index2(it->first)+1);
    res[index2(it->first)] = it->second;
  }
  return res;
}

Two2NCuts::StringVector Two2NCuts::sgetPTMins() const {
  StringVector r;
  for ( Limits2Map::const_iterator it = thePTMins.begin();
	it != thePTMins.end(); ++it ) {
    int n = it->first.first;
    int i = it->first.second;
    ostringstream os;
    os << "(index=" << index2(it->first) << " n=" << n << " i=" << i << ") "
       << it->second/GeV << "GeV";
    r.push_back(os.str());
  }
  return r;
}

string Two2NCuts::ssetPTMaxs(string arg) {
  istringstream is(arg);
  int n;
  int i;
  Energy e;
  is >> n >> i >> e;
  if ( !is || i > n || i <= 0 )
    throw KinCutCmdFail1(*this, arg, "SetPTMax");
  thePTMaxs[make_pair(n, i)] = e;
  return "New maximum for pt of particle i in 2->n processes: " + arg;
}

void Two2NCuts::setPTMaxs(Energy e, int i) {
  thePTMaxs[get2index(i)] = e;
}

void Two2NCuts::insPTMaxs(Energy e, int i) {
  thePTMaxs[get2index(i)] = e;
}

void Two2NCuts::delPTMaxs(int i) {
  Limits2Map::iterator it = thePTMaxs.find(get2index(i));
  if ( it != thePTMaxs.end() ) thePTMaxs.erase(it);
}

Two2NCuts::LimitsVector Two2NCuts::getPTMaxs() const {
  LimitsVector res;
  for ( Limits2Map::const_iterator it = thePTMaxs.begin();
	it != thePTMaxs.end(); ++it ) {
    res.resize(index2(it->first)+1);
    res[index2(it->first)] = it->second;
  }
  return res;
}

Two2NCuts::StringVector Two2NCuts::sgetPTMaxs() const {
  StringVector r;
  for ( Limits2Map::const_iterator it = thePTMaxs.begin();
	it != thePTMaxs.end(); ++it ) {
    int n = it->first.first;
    int i = it->first.second;
    ostringstream os;
    os << "(index=" << index2(it->first) << " n=" << n << " i=" << i << ") "
       << it->second/GeV << "GeV";
    r.push_back(os.str());
  }
  return r;
}

string Two2NCuts::ssetDiMassMins(string arg) {
  istringstream is(arg);
  int n;
  int i;
  int j;
  Energy e;
  is >> n >> i >> j >> e;
  if ( !is || i > n || j >= i || j <= 0 )
    throw KinCutCmdFail3(*this, arg, "SetDiMassMin");
  theDiMassMins[makeTriplet(n, i, j)] = e;
  return "New minimum for mass of particles i and j in 2->n processes: " + arg;
} 

void Two2NCuts::setDiMassMins(Energy e, int i) {
  theDiMassMins[get3index(i)] = e;
}

void Two2NCuts::insDiMassMins(Energy e, int i) {
  theDiMassMins[get3index(i)] = e;
}

void Two2NCuts::delDiMassMins(int i) {
  Limits3Map::iterator it = theDiMassMins.find(get3index(i));
  if ( it != theDiMassMins.end() ) theDiMassMins.erase(it);
}

Two2NCuts::LimitsVector Two2NCuts::getDiMassMins() const {
  LimitsVector res;
  for ( Limits3Map::const_iterator it = theDiMassMins.begin();
	it != theDiMassMins.end(); ++it ) {
    res.resize(index3(it->first)+1);
    res[index3(it->first)] = it->second;
  }
  return res;
}

Two2NCuts::StringVector Two2NCuts::sgetDiMassMins() const {
  StringVector r;
  for ( Limits3Map::const_iterator it = theDiMassMins.begin();
	it != theDiMassMins.end(); ++it ) {
    int n = it->first.first;
    int i = it->first.second;
    int j = it->first.third;
    ostringstream os;
    os << "(index=" << index3(it->first) << " n=" << n
       << " i=" << i << " j=" << j << ") " << it->second/GeV << "GeV";
    r.push_back(os.str());
  }
  return r;
}

string Two2NCuts::ssetDiMassMaxs(string arg) {
  istringstream is(arg);
  int n;
  int i;
  int j;
  Energy e;
  is >> n >> i >> j >> e;
  if ( !is || i > n || j >= i || j <= 0 )
    throw KinCutCmdFail3(*this, arg, "SetDiMassMax");
  theDiMassMaxs[makeTriplet(n, i, j)] = e;
  return "New maximum for mass of particles i and j in 2->n processes: " + arg;
} 

void Two2NCuts::setDiMassMaxs(Energy e, int i) {
  theDiMassMaxs[get3index(i)] = e;
}

void Two2NCuts::insDiMassMaxs(Energy e, int i) {
  theDiMassMaxs[get3index(i)] = e;
}

void Two2NCuts::delDiMassMaxs(int i) {
  Limits3Map::iterator it = theDiMassMaxs.find(get3index(i));
  if ( it != theDiMassMaxs.end() ) theDiMassMaxs.erase(it);
}

Two2NCuts::LimitsVector Two2NCuts::getDiMassMaxs() const {
  LimitsVector res;
  for ( Limits3Map::const_iterator it = theDiMassMaxs.begin();
	it != theDiMassMaxs.end(); ++it ) {
    res.resize(index3(it->first)+1);
    res[index3(it->first)] = it->second;
  }
  return res;
}

Two2NCuts::StringVector Two2NCuts::sgetDiMassMaxs() const {
  StringVector r;
  for ( Limits3Map::const_iterator it = theDiMassMaxs.begin();
	it != theDiMassMaxs.end(); ++it ) {
    int n = it->first.first;
    int i = it->first.second;
    int j = it->first.third;
    ostringstream os;
    os << "(index=" << index3(it->first) << " n=" << n
       << " i=" << i << " j=" << j << ") " << it->second/GeV << "GeV";
    r.push_back(os.str());
  }
  return r;
}

void Two2NCuts::persistentOutput(PersistentOStream & os) const {
  os << ounit(theMassMins, GeV) << ounit(theMassMaxs, GeV)
     << ounit(thePTMins, GeV) << ounit(thePTMaxs, GeV)
     << ounit(theDiMassMins, GeV) << ounit(theDiMassMaxs, GeV);
}

void Two2NCuts::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theMassMins, GeV) >> iunit(theMassMaxs, GeV)
     >> iunit(thePTMins, GeV) >> iunit(thePTMaxs, GeV)
     >> iunit(theDiMassMins, GeV) >> iunit(theDiMassMaxs, GeV);
}

ClassDescription<Two2NCuts> Two2NCuts::initTwo2NCuts;

void Two2NCuts::Init() {

  static ClassDocumentation<Two2NCuts> documentation
    ("There is no documentation for the ThePEG::Two2NCuts class");

  static ParVector<Two2NCuts,Energy> interfaceMassMins
    ("SubProcess/ResonanceMassMin",
     "These limits are in addition to otherwse specified limits. For any "
     "\\f$2\\rightarrow n\\f$ process this vector gives the minimum allowed "
     "mass in GeV of any produced (resonance) particle \\f$i\\f$. The index "
     "should be given according to \\f$(n(n-1))/2+i\\f$. If any of these "
     "limits are larger than the corresponding upper limit in "
     "<code>SubProcess/ResonanceMassMax</code>, the upper limit is inactive. "
     "These limits are checked automatically by the event handler. This limit "
     "can also be set through command interface "
     "<code>SetResonanceMassMin</code>.",
     0, GeV, 0, 0.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true,
     &Two2NCuts::setMassMins, &Two2NCuts::insMassMins,
     &Two2NCuts::delMassMins, &Two2NCuts::getMassMins, 0, 0, 0);
  
  static ParVector<Two2NCuts,Energy> interfaceMassMaxs
    ("SubProcess/ResonanceMassMax",
     "These limits are in addition to otherwse specified limits. For any "
     "\\f$2\\rightarrow n\\f$ process this vector gives the maximum allowed "
     "mass in GeV of any produced (resonance) particle \\f$i\\f$. The index "
     "should be given according to \\f$(n(n-1))/2+i\\f$. If any of these "
     "limits are smaller than the corresponding lower limit in "
     "<code>ResonanceMassMax</code>, the upper limit is inactive. These "
     "limits are checked automatically by the event handler. This limit "
     "can also be set through command interface "
     "<code>SetResonanceMassMax</code>.",
     0, GeV, 0, -1.0*GeV, -1.0*GeV, Constants::MaxEnergy, false, false, true,
     &Two2NCuts::setMassMaxs, &Two2NCuts::insMassMaxs,
     &Two2NCuts::delMassMaxs, &Two2NCuts::getMassMaxs, 0, 0, 0);

  static ParVector<Two2NCuts,Energy> interfacePTMins
    ("SubProcess/PTMin",
     "These limits are in addition to otherwse specified limits. For any "
     "\\f$2\\rightarrow n\\f$ process this vector gives the minimum allowed "
     "\\f$p_\\perp\\f$ in GeV of any produced particle \\f$i\\f$. The index "
     "should be given according to \\f$(n(n-1))/2+i\\f$. If any of these "
     "limits are larger than the corresponding upper limit in "
     "<code>ResonanceMassMax</code>, the upper limit is inactive. These "
     "limits are checked automatically by the event handler. This limit can "
     "also be set through the comand interface <code>SetPTMassMin</code>.",
     0, GeV, 0, 0.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true,
     &Two2NCuts::setPTMins, &Two2NCuts::insPTMins,
     &Two2NCuts::delPTMins, &Two2NCuts::getPTMins, 0, 0, 0);
  
  static ParVector<Two2NCuts,Energy> interfacePTMaxs
    ("SubProcess/PTMax",
     "These limits are in addition to otherwse specified limits. For any "
     "\\f$2\\rightarrow n\\f$ process this vector gives the maximum allowed "
     "\\f$p_\\perp\\f$ in GeV of any produced particle \\f$i\\f$. The index "
     "should be given according to \\f$(n(n-1))/2+i\\f$. If any of these "
     "limits are smaller than the corresponding lower limit in "
     "<code>ResonanceMassMax</code>, the upper limit is inactive. These "
     "limits are checked automatically by the event handler. This limit can "
     "also be set through the command interface <code>SetPTMax</code>.",
     0, GeV, 0, -1.0*GeV, -1.0*GeV, Constants::MaxEnergy, false, false, true,
     &Two2NCuts::setPTMaxs, &Two2NCuts::insPTMaxs,
     &Two2NCuts::delPTMaxs, &Two2NCuts::getPTMaxs, 0, 0, 0);

  static ParVector<Two2NCuts,Energy> interfaceDiMassMins
    ("SubProcess/DiMassMin",
     "These limits are in addition to otherwse specified limits. For any "
     "\\f$2\\rightarrow n\\f$ process this vector gives the minimum allowed "
     "invariant mass in GeV of any two produced particle \\f$i,j\\f$. The "
     "index should be given according to "
     "\\f$(n(n-1)(n-2)/6+(i-1)(i-2)/2+j\\f$. with \\f$i>j\\f$ If any of these "
     "limits are larger than the corresponding upper limit in "
     "<code>DiMassMax</code>, the upper limit is inactive. These limits "
     "are checked automatically by the event handler. This limit can also "
     "be set through the command interface <code>SetDiMassMin</code>.",
     0, GeV, 0, 0.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true,
     &Two2NCuts::setDiMassMins, &Two2NCuts::insDiMassMins,
     &Two2NCuts::delDiMassMins, &Two2NCuts::getDiMassMins, 0, 0, 0);
  
  static ParVector<Two2NCuts,Energy> interfaceDiMassMaxs
    ("SubProcess/DiMassMax",
     "These limits are in addition to otherwse specified limits. For any "
     "\\f$2\\rightarrow n\\f$ process this vector gives the maximum allowed "
     "invariant mass in GeV of any two produced particle \\f$i,j\\f$. The "
     "index should be given according to "
     "\\f$(n(n-1)(n-2)/6+(i-1)(i-2)/2+j\\f$. with \\f$i>j\\f$ "
     "If any of these limits are smaller than the corresponding lower limit "
     "in <code>DiMassMax</code>, the upper limit is inactive. These limits "
     "are checked automatically by the event handler. This limit can also "
     "be set through the command interface <code>SetDiMassMin</code>.",
     0, GeV, 0, -1.0*GeV, -1.0*GeV, Constants::MaxEnergy, false, false, true,
     &Two2NCuts::setDiMassMaxs, &Two2NCuts::insDiMassMaxs,
     &Two2NCuts::delDiMassMaxs, &Two2NCuts::getDiMassMaxs, 0, 0, 0);

  static Command<Two2NCuts> interfaceSetMassMins
    ("SubProcess/SetResonanceMassMin",
     "Set a value for <code>ResonanceMassMin</code>. The argument should be "
     "on the form '\\f$n\\f$ \\f$i\\f$ mass' for the minimum mass of particle "
     "\\f$i\\f$ in a \\f$2\\rightarrow n\\f$ process, with "
     "\\f$n \\leq i > 0\\f$.",
     &Two2NCuts::ssetMassMins);

  static Command<Two2NCuts> interfaceSetMassMaxs
    ("SubProcess/SetResonanceMassMax",
     "Set a value for <code>ResonanceMassMax</code>. The argument should be "
     "on the form '\\f$n\\f$ \\f$i\\f$ mass' for the maximum mass of particle "
     "\\f$i\\f$ in a \\f$2\\rightarrow n\\f$ process, with "
     "\\f$n \\leq i > 0\\f$.",
     &Two2NCuts::ssetMassMins);

  static Command<Two2NCuts> interfaceSetPTMins
    ("SubProcess/SetPTMin",
     "Set a value for <code>PTMin</code>. The argument should be "
     "on the form '\\f$n\\f$ \\f$i\\f$ \\f$p_\\perp\\f$' for the minimum "
     "\\f$p_\\perp\\f$ of particle \\f$i\\f$ in a \\f$2\\rightarrow n\\f$ "
     "process, with \\f$n \\leq i > 0\\f$.",
     &Two2NCuts::ssetPTMins);

  static Command<Two2NCuts> interfaceSetPTMaxs
    ("SubProcess/SetPTMax",
     "Set a value for <code>ResonanceMassMax</code>. The argument should be "
     "on the form '\\f$n\\f$ \\f$i\\f$ \\f$p_\\perp\\f$' for the maximum "
     "\\f$p_\\perp\\f$ of particle \\f$i\\f$ in a \\f$2\\rightarrow n\\f$ "
     "process, with \\f$n \\leq i > 0\\f$.",
     &Two2NCuts::ssetPTMins);

  static Command<Two2NCuts> interfaceSetDiMassMins
    ("SubProcess/SetDiMassMin",
     "Set a value for <code>DiMassMin</code>. The argument should be "
     "on the form '\\f$n\\f$ \\f$i\\f$ \\f$j\\f$ mass' for the minimum mass "
     "of particles \\f$i\\f$ and \\f$j\\f$ in a \\f$2\\rightarrow n\\f$ "
     "process, with \\f$n \\leq i > j > 0\\f$.",
     &Two2NCuts::ssetMassMins);

  static Command<Two2NCuts> interfaceSetDiMassMaxs
    ("SubProcess/SetDiMassMax",
     "Set a value for <code>DiMassMax</code>. The argument should be "
     "on the form '\\f$n\\f$ \\f$i\\f$ \\f$j\\f$ mass' for the maximum mass "
     "of particles \\f$i\\f$ and \\f$j\\f$ in a \\f$2\\rightarrow n\\f$ "
     "process, with \\f$n \\leq i > j > 0\\f$.",
     &Two2NCuts::ssetMassMins);

}

KinCutCmdFail1::KinCutCmdFail1(const Two2NCuts & i, string a, string s) {
  theMessage << "Could not execute the command '" << s << "' for the object '"
	     << i.name() << "' with argument '" << a << "' because the syntax "
	     << "is wrong. Expected 'n i pt' for the pt of particle i in "
	     << "a 2->n process, with n >= i > 0.";
  severity(warning);
}
  
KinCutCmdFail2::KinCutCmdFail2(const Two2NCuts & i, string a, string s) {
  theMessage << "Could not execute the command '" << s << "' for the object '"
	     << i.name() << "' with argument '" << a << "' because the syntax "
	     << "is wrong. Expected 'n i mass' for the mass of particle i in "
	     << "a 2->n process, with n >= i > 0.";
  severity(warning);
}
  
KinCutCmdFail3::KinCutCmdFail3(const Two2NCuts & i, string a, string s) {
  theMessage << "Could not execute the command '" << s << "' for the object '"
	     << i.name() << "' with argument '" << a << "' because the syntax "
	     << "is wrong. Expected 'n i j mass' for the mass of particles "
	     << "i and j in a 2->n process, with n >= i > j > 0.";
  severity(warning);
}

