// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SimpleFlavour class.
//

#include "SimpleFlavour.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/PDT/StandardMatchers.h"
#include "ThePEG/Repository/RandomGenerator.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/Triplet.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleFlavour.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

SimpleFlavour::~SimpleFlavour() {}

void SimpleFlavour::clear() {
  theFlavourSelector.clear();
}

long SimpleFlavour::selectQuark() const {
  return rndsign(1.0, 1.0, sSup()) + 2;
}

long SimpleFlavour::selectFlavour() const {
  if ( theFlavourSelector.empty() ) {
    theFlavourSelector.insert(1.0, 1);
    theFlavourSelector.insert(1.0, 2);
    theFlavourSelector.insert(sSup(), 3);
    for ( int ifla = 1; ifla <= 3; ++ifla )
      for ( int iflb = 1; iflb <= ifla; ++iflb ) {
	double w = diSup();
	if ( ifla == 3 ) w *= diSSup();
	theFlavourSelector.insert(3.0*di1Sup()*w, 1000*ifla + 100*iflb + 3);
	if ( ifla != iflb )
	  theFlavourSelector.insert(w, 1000*ifla + 100*iflb + 1);
      }
  }
  return theFlavourSelector[rnd()];
}

tcPDPair SimpleFlavour::generateHadron(tcPDPtr q) const {
  tcPDPair ret;
  bool isdiq = DiquarkMatcher::Check(*q);
  while ( true ) {
    long flav = selectFlavour();
    if ( isdiq && DiquarkMatcher::Check(flav) ) continue;
    if ( isdiq )
      ret.second = getParticleData(q->id() > 0? -flav: flav);
    else
      ret.second = getParticleData(q->id() > 0? flav: -flav);
    ret.first = getHadron(q->id(), ret.second->CC()->id());
    if ( ret.first->id() == ParticleID::eta && !rndbool(etaSup()) )
      continue;
    if ( ret.first->id() == ParticleID::etaprime && !rndbool(etaPSup()) )
      continue;
    if ( DiquarkMatcher::Check(ret.second->id()) &&
	 !rndbool(weightSU6QDiQSpin(abs(q->id()), abs(ret.second->id()), 2) +
		  weightSU6QDiQSpin(abs(q->id()), abs(ret.second->id()), 4)*
		  baryon10Sup()) ) continue;
      return ret;
  }
  return tcPDPair();
}

double SimpleFlavour::vectorMesonProbability(long iq1, long iq2) const {
  switch ( max(abs(iq1), abs(iq2)) ) {
  case 1:
  case 2:
    return pSpin1();
  case 3:
    return pSpinS1();
  case 4:
  case 5:
    return pSpinC1();
  default:
    return 0.0;
  }
}

double weightSU6QDiQSpin(long iq, long idq, int spin) {
  typedef Triplet<long,long,int> QDiQS;
  typedef map<QDiQS,double> QDiQSpinMap;
  static QDiQSpinMap qDiQSpin;

  QDiQS i(iq, idq, spin);
  QDiQSpinMap::iterator it = qDiQSpin.find(i);
  if ( it != qDiQSpin.end() ) return it->second;
  long idq1 = (idq/1000)%10;
  long idq2 = (idq/100)%10;
  if ( idq1 == idq2 ) {
    // Two of the same flavour in diquark, only spin 1
    if ( iq == idq1 ) return qDiQSpin[i] = (spin == 4? 1.0: 0.0);
    return qDiQSpin[i] = (spin == 4? 1.0/3.0: 1.0/6.0);
  }
  else if ( idq%10 == 1 ) {
    // Spin 0 diquarks:
    if ( iq == idq1 || iq == idq2 ) return qDiQSpin[i] = (spin == 4? 0.0: 0.75);
    return qDiQSpin[i] = (spin == 4? 0.0: 0.5);
  }
  else {
    // Spin 1 diquarks:
    if ( iq == idq1 || iq == idq2 )
      return qDiQSpin[i] = (spin == 4? 2.0/3.0: 1.0/12.0);
    return qDiQSpin[i] = (spin == 4? 1.0/3.0: 1.0/6.0);
  }
}

double SimpleFlavour::baryonDecupletProbability(long iq1, long iq2) const {
  double pd = weightSU6QDiQSpin(iq1, iq2, 4)*baryon10Sup();
  double po = weightSU6QDiQSpin(iq1, iq2, 2);
  return pd/(pd + po);
}

tcPDPtr SimpleFlavour::getBaryon(long iq1, long iq2, long iq3) const {
  if ( abs(iq1) >= 10 || abs(iq2) >= 10 || abs(iq3) ) return tcPDPtr();
  if ( iq1*iq2*iq3 == 0 ) return tcPDPtr();
  int sign = 0;
  if ( iq1 > 0 && iq2 > 0 && iq3 > 0 ) sign = 1;
  if ( iq1 < 0 && iq2 < 0 && iq3 < 0 ) sign = -1;
  if ( !sign ) return tcPDPtr();
  VSelector< pair<long,long> > sel;
  iq1 = abs(iq1);
  iq2 = abs(iq2);
  iq3 = abs(iq3);
  sel.insert(3.0, make_pair(iq1, 1000*max(iq2, iq3) + 100*min(iq2, iq3) + 3));
  if ( iq2 != iq3 )
    sel.insert(1.0, make_pair(iq1, 1000*max(iq2, iq3) + 100*min(iq2, iq3) + 1));
  sel.insert(3.0, make_pair(iq2, 1000*max(iq3, iq1) + 100*min(iq3, iq1) + 3));
  if ( iq3 != iq1 )
    sel.insert(1.0, make_pair(iq2, 1000*max(iq3, iq1) + 100*min(iq3, iq1) + 1));
  sel.insert(3.0, make_pair(iq3, 1000*max(iq1, iq2) + 100*min(iq1, iq2) + 3));
  if ( iq1 != iq2 )
    sel.insert(1.0, make_pair(iq3, 1000*max(iq1, iq2) + 100*min(iq1, iq2) + 1));
  pair<long,long> qdq = sel[rnd()];
  return getHadron(qdq.first, qdq.second);
}

tcPDPtr SimpleFlavour::getHadron(long iq1, long iq2) const {
  if ( iq1*iq2 == 0 ) return tcPDPtr();
  if ( DiquarkMatcher::Check(iq1) ) swap(iq1, iq2);
  if ( DiquarkMatcher::Check(iq2) ) {
    if ( abs(iq1) >= 10 || iq1*iq2 < 0 ) return tcPDPtr();
    return rndbool(baryonDecupletProbability(abs(iq1), abs(iq2)))?
      baryonDecuplet(iq1, iq2): baryonOctet(iq1, iq2);
  } else {
    if ( abs(iq1) >= 10 || abs(iq2) >= 10 || iq1*iq2 > 0 ) return tcPDPtr();
    return rndbool(vectorMesonProbability(iq1, iq2))?
      vectorMeson(iq1, iq2):   pseudoScalarMeson(iq1, iq2);
  }
}

tcPDPtr SimpleFlavour::pseudoScalarMeson(long iq, long iqbar) const {
  return getParticleData((min(iq, iqbar) < max(iq, iqbar)? -1: 1)*
			 pseudoScalarId(max(abs(iq), abs(iqbar)),
					min(abs(iq), abs(iqbar))));
}

long SimpleFlavour::pseudoScalarId(long iqh, long iql) const {
  if ( iql == iqh && iql <= 3 ) {
    if ( iql <= 2 )
      return rndbool()? ParticleID::pi0:
	( rndbool()? ParticleID::eta: ParticleID::etaprime );
    else
      return rndbool()? ParticleID::eta: ParticleID::etaprime;
  } else
    return iqh*100 + iql*10 + 1;
}

tcPDPtr SimpleFlavour::vectorMeson(long iq, long iqbar) const {
  return getParticleData((min(iq, iqbar) < max(iq, iqbar)? -1: 1)*
			 vectorId(max(abs(iq), abs(iqbar)),
				  min(abs(iq), abs(iqbar))));
}

long SimpleFlavour::vectorId(long iqh, long iql) const {
  if ( iql == iqh && iql <= 2 )
    return rndbool()? ParticleID::rho0: ParticleID::omega;
  else
    return iqh*100 + iql*10 + 3;
}

tcPDPtr SimpleFlavour::baryonOctet(long iq, long idq) const {
  long aiq = abs(iq);
  vector<long> flv = PDT::flavourContent(idq);
  long iqa = max(abs(flv[0]), aiq);
  long iqc = min(abs(flv[1]), aiq);
  long iqb = abs(flv[0]) + abs(flv[1]) + aiq - iqa - iqc;
  return getParticleData((iq > 0? 1: -1)*
			 baryonOctetId(iqa, iqb, iqc, aiq,
				       (abs(idq)%10) == 3));
}

long SimpleFlavour::
baryonOctetId(long iqa, long iqb, long iqc, long iq, bool dqs1) const {
  if ( iqa > iqb && iqb > iqc &&
       ( ( dqs1 && ( iqa == iq || rndbool(0.25) ) ) ||
	 ( !dqs1 && iqa != iq && rndbool(0.75) ) ) ) swap(iqb, iqc);
  return 1000*iqa + 100*iqb + 10*iqc + 2;
}

tcPDPtr SimpleFlavour::baryonDecuplet(long iq, long idq) const {
  long aiq = abs(iq);
  vector<long> flv = PDT::flavourContent(idq);
  long iqa = max(abs(flv[0]), aiq);
  long iqc = min(abs(flv[1]), aiq);
  long iqb = abs(flv[0]) + abs(flv[1]) + aiq - iqa - iqc;
  return getParticleData((iq > 0? 1: -1)*baryonDecupletId(iqa, iqb, iqc));
}

long SimpleFlavour::
baryonDecupletId(long iqa, long iqb, long iqc) const {
  return 1000*iqa + 100*iqb + 10*iqc + 4;
}

void SimpleFlavour::persistentOutput(PersistentOStream & os) const {
  os << theSSup << theDiSup << theDi1Sup << theDiSSup << theEtaSup
     << theEtaPSup << theBaryon10Sup << thePSpin1 << thePSpinS1 << thePSpinC1;
}

void SimpleFlavour::persistentInput(PersistentIStream & is, int) {
  is >> theSSup >> theDiSup >> theDi1Sup >> theDiSSup >> theEtaSup
     >> theEtaPSup >> theBaryon10Sup >> thePSpin1 >> thePSpinS1 >> thePSpinC1;
  clear();
}

ClassDescription<SimpleFlavour> SimpleFlavour::initSimpleFlavour;
// Definition of the static class description member.

void SimpleFlavour::Init() {

  static ClassDocumentation<SimpleFlavour> documentation
    ("This is a simple class to generate hadrons given the quark "
     "flavours. It implements a simplified version of the model of the "
     "old fortran version of Pythia.");

  static Parameter<SimpleFlavour,double> interfaceSSup
    ("SSup",
     "Suppression factor of strange quarks w.r.t. u and d.",
     &SimpleFlavour::theSSup, 0.3, 0.0, 1.0,
     true, false, true);

  static Parameter<SimpleFlavour,double> interfaceDiSup
    ("DiSup",
     "Suppression factor for di-quarks w.r.t. quarks.",
     &SimpleFlavour::theDiSup, 0.1, 0.0, 1.0,
     true, false, true);

  static Parameter<SimpleFlavour,double> interfaceDi1Sup
    ("Di1Sup",
     "Suppression of spin-1 di-quarks w.r.t. spin-0 ones.",
     &SimpleFlavour::theDi1Sup, 0.05, 0.0, 1.0,
     true, false, true);

  static Parameter<SimpleFlavour,double> interfaceDiSSup
    ("DiSSup",
     "Suppression of strange di-quarks w.r.t. u and d ones in addition to "
     "the standard strangness suppression of quarks.",
     &SimpleFlavour::theDiSSup, 0.4, 0.0, 1.0,
     true, false, true);

  static Parameter<SimpleFlavour,double> interfaceEtaSup
    ("EtaSup",
     "Extra suppression of eta's.",
     &SimpleFlavour::theEtaSup, 1.0, 0.0, 1.0,
     true, false, true);

  static Parameter<SimpleFlavour,double> interfaceEtaPSup
    ("EtaPSup",
     "Extra suppression of ets-prime's.",
     &SimpleFlavour::theEtaPSup, 0.4, 0.0, 1.0,
     true, false, true);

  static Parameter<SimpleFlavour,double> interfaceBaryon10Sup
    ("Baryon10Sup",
     "Extra suppression for baryons of the spin 3/2 decuplet.",
     &SimpleFlavour::theBaryon10Sup, 1.0, 0.0, 1.0,
     true, false, true);

  static Parameter<SimpleFlavour,double> interfacePSpin1
    ("PSpin1",
     "Probability that light (u/d) mesons has spin 1.",
     &SimpleFlavour::thePSpin1, 0.5, 0.0, 1.0,
     true, false, true);

  static Parameter<SimpleFlavour,double> interfacePSpinS1
    ("PSpinS1",
     "Probability that strange mesons has spin 1.",
     &SimpleFlavour::thePSpinS1, 0.6, 0.0, 1.0,
     true, false, true);

  static Parameter<SimpleFlavour,double> interfacePSpinC1
    ("PSpinC1",
     " Probability that charmed and heavier mesons has spin 1.",
     &SimpleFlavour::thePSpinC1, 0.75, 0.0, 1.0,
     true, false, true);

}

