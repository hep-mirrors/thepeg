// -*- C++ -*-
//
#ifndef ThePEG_StandardMatchers_H
#define ThePEG_StandardMatchers_H
//
// This is the declaration of the <!id>AnyMatcher<!!id>,
// <!id>ChargedMatcher<!!id>, <!id>NegativeMatcher<!!id>,
// <!id>PositiveMatcher<!!id>, <!id>NeutralMatcher<!!id>,
// <!id>BaryonMatcher<!!id>, <!id>MesonMatcher<!!id>,
// <!id>DiquarkMatcher<!!id>, <!id>LeptonMatcher<!!id>,
// <!id>LightAntiQuarkMatcher<!!id>, <!id>LightQuarkMatcher<!!id> and
// <!id>StandardQCDPartonMatcher<!!id> classes.
//
// Also defined are typedefs of <!class>Matcher<!!class> classes
// instantiated with these classes as objects turning them into
// <!class>MatcherBase<!!class> objects.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Matcher.html">Matcher.h</a>,
// <a href="http:MatcherBase.html">MatcherBase.h</a>.
// 

//

#include "Matcher.h"
#include "ThePEG/PDT/EnumParticles.h"

namespace ThePEG {

struct AnyMatcher {
  typedef AnyMatcher CC;
  static bool Check(const ParticleData & pd) {
    return bool(pd.id());
  }
  static string className() { return "Any"; }
};
typedef Matcher<AnyMatcher> MatchAny;
// Matches any particle.


struct ChargedMatcher {
  typedef ChargedMatcher CC;
  static bool Check(const ParticleData & pd) {
    return PDT::charged(pd.iCharge());
  }
  static string className() { return "Charged"; }
};
typedef Matcher<ChargedMatcher> MatchCharged;
// Matches any charged particle.

struct NegativeMatcher;
struct PositiveMatcher {
  typedef NegativeMatcher CC;
  static bool Check(const ParticleData & pd) {
    return PDT::positive(pd.iCharge());
  }
  static string className() { return "Positive"; }
};
typedef Matcher<PositiveMatcher> MatchPositive;
// Matches any positively charged particle.


struct NeutralMatcher {
  typedef NeutralMatcher CC;
  static bool Check(const ParticleData & pd) {
    return pd.iCharge() == PDT::Charge0;
  }
  static string className() { return "Neutral"; }
};
typedef Matcher<NeutralMatcher> MatchNeutral;
// Matches any neutral particle.

struct NegativeMatcher {
  typedef PositiveMatcher CC;
  static bool Check(const ParticleData & pd) {
    return PDT::negative(pd.iCharge());
  }
  static string className() { return "Negative"; }
};
typedef Matcher<NegativeMatcher> MatchNegative;
// Matches any negatively charged particle.

struct BaryonMatcher {
  typedef BaryonMatcher CC;
  static bool Check(const ParticleData & pd) {
    return (pd.id()/10)%10 && (pd.id()/100)%10 && (pd.id()/1000)%10;
  }
  static string className() { return "Baryon"; }
};
typedef Matcher<BaryonMatcher> MatchBaryon;
// Matches any baryon.


struct MesonMatcher {
  typedef MesonMatcher CC;
  static bool Check(const ParticleData & pd) {
    return (pd.id()/10)%10 && (pd.id()/100)%10 && (pd.id()/1000)%10 == 0;
  }
  static string className() { return "Meson"; }
};
typedef Matcher<MesonMatcher> MatchMeson;
// Matches any meson.


struct DiquarkMatcher {
  typedef DiquarkMatcher CC;
  static bool Check(const ParticleData & pd) { return Check(pd.id()); }
  static bool Check(long id) {
    return id/10 && (id/10)%10 == 0 && (id/100)%10 && (id/1000)%10;
  }
  static string className() { return "Diquark"; }
};
typedef Matcher<DiquarkMatcher> MatchDiquark;
// Matches any meson.


struct LeptonMatcher {
  typedef LeptonMatcher CC;
  static bool Check(const ParticleData & pd) { return Check(pd.id()); }
  static bool Check(long id) {
    return abs(id) > 10 && abs(id) <= 20;
  }
  static string className() { return "Lepton"; }
};
typedef Matcher<LeptonMatcher> MatchLepton;
// Matches any lepton.

struct LightAntiQuarkMatcher;
struct LightQuarkMatcher {
  typedef LightAntiQuarkMatcher CC;
  static bool Check(const ParticleData & pd) { return Check(pd.id()); }
  static bool Check(long id) {
    return id > 0 && id < 4 ;
  }
  static string className() { return "LightQuark"; }
};
typedef Matcher<LightQuarkMatcher> MatchLightQuark;
// Matches any light quark.


struct LightAntiQuarkMatcher {
  typedef LightQuarkMatcher CC;
  static bool Check(const ParticleData & pd) { return Check(pd.id()); }
  static bool Check(long id) {
    return id < 0 && id > -4 ;
  }
  static string className() { return "LightAntiQuark"; }
};
typedef Matcher<LightAntiQuarkMatcher> MatchLightAntiQuark;
// Matches any light antiquark.

struct StandardQCDPartonMatcher {
  static bool Check(const ParticleData & pd) { return Check(pd.id()); }
  static bool Check(long id) {
    return id && ( abs(id) <= 5 || id == ParticleID::g );
  }
  static string className() { return "StandardQCDParton"; }
};

typedef Matcher<StandardQCDPartonMatcher> MatchStandardQCDParton;

}

#endif /* ThePEG_StandardMatchers_H */
