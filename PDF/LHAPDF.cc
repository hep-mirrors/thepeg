// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LHAPDF class.
//

#include "LHAPDF.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Command.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Utilities/EnumIO.h"
#include "ThePEG/Utilities/Debug.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LHAPDF.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

#ifdef ThePEG_HAS_FPU_CONTROL
#include <fpu_control.h>
#endif

using namespace ThePEG;

typedef double F77ThePEGDouble;
typedef int F77ThePEGInteger;

#ifdef ThePEG_HAS_LHAPDF

extern "C" {

  void initpdfsetbynamem_(F77ThePEGInteger &, const char *, F77ThePEGInteger);
  void initpdfm_(F77ThePEGInteger &,F77ThePEGInteger  &);
  void evolvepdfm_(F77ThePEGInteger &, F77ThePEGDouble &,
		   F77ThePEGDouble &, F77ThePEGDouble *);
  void evolvepdfpm_(F77ThePEGInteger &, F77ThePEGDouble &,
		    F77ThePEGDouble &, F77ThePEGDouble &,
		    F77ThePEGInteger &, F77ThePEGDouble *);
  void numberpdfm_(F77ThePEGInteger &, F77ThePEGInteger &);
  void getnfm_(F77ThePEGInteger &, F77ThePEGInteger &);
  void lhaprint_(F77ThePEGInteger &);
}

#else

void initpdfsetbynamem_(F77ThePEGInteger &, const char *, F77ThePEGInteger) {
  LHAPDF::throwNotInstalled();
}

void initpdfm_(F77ThePEGInteger &,F77ThePEGInteger  &) {
  LHAPDF::throwNotInstalled();
}

void evolvepdfm_(F77ThePEGInteger &, F77ThePEGDouble &,
		 F77ThePEGDouble &, F77ThePEGDouble *) {
  LHAPDF::throwNotInstalled();
}

void evolvepdfpm_(F77ThePEGInteger &, F77ThePEGDouble &,
		  F77ThePEGDouble &, F77ThePEGDouble &,
		  F77ThePEGInteger &, F77ThePEGDouble *){
  LHAPDF::throwNotInstalled();
}

void numberpdfm_(F77ThePEGInteger &, F77ThePEGInteger &) {}

void getnfm_(F77ThePEGInteger &, F77ThePEGInteger &) {}

void lhaprint_(F77ThePEGInteger &) {}

#endif

struct TmpMaskFpuDenorm {
#ifdef ThePEG_HAS_FPU_CONTROL_NEVER
  fpu_control_t oldcw;
  TmpMaskFpuDenorm() {
    volatile fpu_control_t cw;
    _FPU_GETCW(cw);
    oldcw = cw;
    cw |= (_FPU_MASK_DM);
    if ( cw != oldcw ) _FPU_SETCW(cw);
  }
  ~TmpMaskFpuDenorm() {
    volatile fpu_control_t cw;
    _FPU_GETCW(cw);
    if ( cw != oldcw ) {
      cw = oldcw;
      _FPU_SETCW(cw);
    }
  }
#else
  TmpMaskFpuDenorm() {
    Debug::maskFpuDenorm();
  }
#endif
};


#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDT/EnumParticles.h"

LHAPDF::~LHAPDF() {}

IBPtr LHAPDF::clone() const {
  return new_ptr(*this);
}

IBPtr LHAPDF::fullclone() const {
  return new_ptr(*this);
}

void LHAPDF::doinit() throw(InitException) {
  PDFBase::doinit();
  checkInit();
}

void LHAPDF::dofinish() {
  PDFBase::dofinish();
}

void LHAPDF::doinitrun() {
  PDFBase::doinitrun();
  checkInit();
}

void LHAPDF::throwNotInstalled() {
  throw LHAPDF::NotInstalled()
    << "Tried to initialize a LHAPDF object, "
    << "but the LHAPDF library was not installed" << Exception::runerror;
}

void LHAPDF::initpdfsetm() const {
  TmpMaskFpuDenorm fpumask;
  F77ThePEGInteger iset = nset + 1;
  initpdfsetbynamem_(iset, PDFName().c_str(), PDFName().length());
  lastNames[nset] = PDFName();
}

void LHAPDF::initpdfm() const {
  TmpMaskFpuDenorm fpumask;
  F77ThePEGInteger iset = nset + 1;
  F77ThePEGInteger mem = member();
  initpdfm_(iset, mem);
  lastMem[nset] = member();
  lastReset();
}

void LHAPDF::lastReset() const {
  lastQ2 = -1.0*GeV2;
  lastX = -1.0;
  lastP2 = -1.0*GeV2;
}

void LHAPDF::setnset() const {
  TmpMaskFpuDenorm fpumask;
  F77ThePEGInteger i = !theVerboseLevel;
  lhaprint_(i);
  if ( nset < 0 || nset >= MaxNSet) {
    nset = (lastNSet++)%MaxNSet;
  }
}

int LHAPDF::getMaxMember() const {
  TmpMaskFpuDenorm fpumask;
  checkInit();
  F77ThePEGInteger iset = nset + 1;
  F77ThePEGInteger maxmem = 1;
  numberpdfm_(iset, maxmem);
  return maxmem;
}

int LHAPDF::getMaxFlav() const {
  TmpMaskFpuDenorm fpumask;
  checkInit();
  F77ThePEGInteger iset = nset + 1;
  F77ThePEGInteger maxflav = 1;
  getnfm_(iset, maxflav);
  return maxflav;
}

void LHAPDF::setMaxNSet(int n) {
  MaxNSet = n;
  lastNames.resize(MaxNSet);
  lastMem.resize(MaxNSet);
}

int LHAPDF::getMaxNSet() const {
  return MaxNSet;
}

void LHAPDF::checkInit() const {
  if ( nset < 0 || nset >= MaxNSet) {
    setnset();
    initpdfsetm();
    initpdfm();
  }
  else if ( PDFName() != lastNames[nset] ) {
    initpdfsetm();
    initpdfm();
  }
  else if ( member() != lastMem[nset] ) {
    initpdfm();
  }
}

string LHAPDF::doTest(string input) {
  double x = 0;
  Energy2 Q2 = 0.0*GeV2;
  Energy2 P2 = 0.0*GeV2;
  istringstream is(input);
  is >> x >> iunit(Q2, GeV2) >> iunit(P2, GeV2);
  checkUpdate(x, Q2, P2);
  ostringstream os;
  for ( int i = 0; i < 13; ++i ) os << " " << lastXF[i];
  return os.str();
}  

void LHAPDF::checkUpdate(double x, Energy2 Q2, Energy2 P2) const {
  TmpMaskFpuDenorm fpumask;
  checkInit();
  if ( x == lastX && Q2 == lastQ2 && P2 == lastP2 ) return;
  lastX = x;
  lastQ2 = Q2;
  lastP2 = P2;
  vector<F77ThePEGDouble> res(13);
  F77ThePEGInteger iset = nset + 1;
  F77ThePEGDouble Q = sqrt(Q2/GeV2);
  F77ThePEGDouble xx = x;
  if ( ptype() == photonType ) {
    F77ThePEGDouble PP2 = P2/GeV2;
    F77ThePEGInteger IP2 = thePhotonOption;
    evolvepdfpm_(iset, xx, Q, PP2, IP2, &res[0]);
  } else {
    evolvepdfm_(iset, xx, Q, &res[0]);
  }
  lastXF = vector<double>(res.begin(), res.end());
}

bool LHAPDF::canHandleParticle(tcPDPtr particle) const {
  using namespace ParticleID;
  switch ( ptype() ) {
  case nucleonType:
    return abs(particle->id()) == pplus || abs(particle->id()) == n0;
  case pionType:
    return particle->id() == pi0 || particle->id() == ParticleID::gamma;
  case photonType:
    return particle->id() == ParticleID::gamma;
  default:
    return false;
  }
}

cPDVector LHAPDF::partons(tcPDPtr particle) const {
  // We assume that all standard partons can be extracted.
  cPDVector ret;
  if ( canHandleParticle(particle) ) {
    ret.push_back(getParticleData(ParticleID::g));
    for ( int i = 1, N = getMaxFlav(); i <= N; ++i ) {
      ret.push_back(getParticleData(i));
      ret.push_back(getParticleData(-i));
    }
  }
  return ret;
}

namespace LHAPDFIndex {
enum VectorIndices {
  topb = 0, botb = 1, chab = 2, strb = 3, upb = 4, dowb = 5, glu = 6, dow = 7,
  up = 8, str = 9, cha = 10, bot = 11, top = 12 };
}

double LHAPDF::xfx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
                      double x, double eps, Energy2 particleScale) const {
  // Here we should return the actual density.
  using namespace ThePEG::ParticleID;
  using namespace LHAPDFIndex;
  checkUpdate(x, partonScale, particleScale);

  switch ( parton->id() ) {
  case t:
    return lastXF[top];
  case tbar:
    return lastXF[topb];
  case b:
    return lastXF[bot];
  case bbar:
    return lastXF[botb];
  case c:
    return lastXF[cha];
  case cbar:
    return lastXF[chab];
  case ParticleID::s:
    return lastXF[str];
  case sbar:
    return lastXF[strb];
  case u:
    switch ( particle->id() ) {
    case n0: return lastXF[dow];
    case pbarminus: return lastXF[upb];
    case nbar0: return lastXF[dowb];
    case pplus:
    default: return lastXF[up];
    }
  case ubar:
    switch ( particle->id() ) {
    case n0: return lastXF[dowb];
    case pbarminus: return lastXF[up];
    case nbar0: return lastXF[dow];
    case pplus:
    default: return lastXF[upb];
    }
  case d:
    switch ( particle->id() ) {
    case n0: return lastXF[up];
    case pbarminus: return lastXF[dowb];
    case nbar0: return lastXF[upb];
    case pplus:
    default: return lastXF[dow];
    }
  case dbar:
    switch ( particle->id() ) {
    case n0: return lastXF[upb];
    case pbarminus: return lastXF[dow];
    case nbar0: return lastXF[up];
    case pplus:
    default: return lastXF[dowb];
    }
  case ParticleID::g:
    return lastXF[glu];
  }
  return 0.0;
}

double LHAPDF::xfvx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double x, double eps, Energy2 particleScale) const {
  // Here we should return the actual valence density. This will only
  // work properly for nucleons
  using namespace ThePEG::ParticleID;
  using namespace LHAPDFIndex;
  checkUpdate(x, partonScale, particleScale);

  switch ( parton->id() ) {
  case t:
  case tbar:
  case b:
  case bbar:
  case c:
  case cbar:
  case ParticleID::s:
  case sbar:
    return 0.0;
  case u:
    switch ( particle->id() ) {
    case n0: return lastXF[dow] - lastXF[dowb];
    case pbarminus: return 0.0;
    case nbar0: return 0.0;
    case pplus: return lastXF[up] - lastXF[upb];
    default: return 0.0;
    }
  case ubar:
    switch ( particle->id() ) {
    case n0: return 0.0;
    case pbarminus: return lastXF[up] - lastXF[upb];
    case nbar0: return lastXF[dow] - lastXF[dowb];
    case pplus:
    default: return 0.0;
    }
  case d:
    switch ( particle->id() ) {
    case n0: return lastXF[up] - lastXF[upb];
    case pbarminus: return 0.0;
    case nbar0: return 0.0;
    case pplus: return lastXF[dow] - lastXF[dowb];
    default: return 0.0;
    }
  case dbar:
    switch ( particle->id() ) {
    case n0: return 0.0;
    case pbarminus: return lastXF[dow] - lastXF[dowb];
    case nbar0: return lastXF[up] - lastXF[upb];
    case pplus:
    default: return 0.0;
    }
  case ParticleID::g:
    return 0.0;
  }
  return 0.0;
}


void LHAPDF::persistentOutput(PersistentOStream & os) const {
  os << oenum(thePType) << thePDFName << theMember << thePhotonOption
     << theVerboseLevel;
}

void LHAPDF::persistentInput(PersistentIStream & is, int) {
  is >> ienum(thePType) >> thePDFName >> theMember >> thePhotonOption
     >> theVerboseLevel;
  nset = -1;
  lastReset();
}

ClassDescription<LHAPDF> LHAPDF::initLHAPDF;
// Definition of the static class description member.

int LHAPDF::MaxNSet = 3;

int LHAPDF::lastNSet = 0;

vector<string> LHAPDF::lastNames = vector<string>(3);

vector<int> LHAPDF::lastMem = vector<int>(3);

void LHAPDF::Init() {

  static ClassDocumentation<LHAPDF> documentation
    ("The LHAPDF class inherits from PDFBase and implements an interface "
     "to the LHAPDF library of parton density function parameterizations. "
     "This class is available even if LHAPDF was not properly installed "
     "when ThePEG was installed, but will then produce an error in the "
     "initialization. Note that the valence densities from the xfvx() and "
     "xfvl() function will only work properly for nucleons. All other "
     "particles will have zero valence densities.");

  static Switch<LHAPDF,PType> interfacePType
    ("PType",
     "The type of incoming particles which can be handled by this PDF.",
     &LHAPDF::thePType, nucleonType, true, false);
  static SwitchOption interfacePTypeNucleon
    (interfacePType,
     "Nucleon",
     "Nucleon densities.",
     nucleonType);
  static SwitchOption interfacePTypePionOrVMD
    (interfacePType,
     "PionOrVMD",
     "Pion densities (can also be used for VMD photons).",
     pionType);
  static SwitchOption interfacePTypePhoton
    (interfacePType,
     "Photon",
     "Photon densities.",
     photonType);

  static Parameter<LHAPDF,string> interfacePDFName
    ("PDFName",
     "The name if the PDF set to be used. Should be the full name including "
     "the <code>.LHpdf</code> or <code>.LHgrid</code> suffix.",
     &LHAPDF::thePDFName, "cteq6ll.LHpdf", true, false);


  static Parameter<LHAPDF,int> interfaceMember
    ("Member",
     "The chosen member of the selected PDF set.",
     &LHAPDF::theMember, 0, 0, Constants::MaxInt,
     true, false, Interface::limited,
     (void(LHAPDF::*)(int))(0), (int(LHAPDF::*)()const)(0),
     (int(LHAPDF::*)()const)(0), &LHAPDF::getMaxMember,
     (int(LHAPDF::*)()const)(0));

  static Switch<LHAPDF,int> interfacePhotonOption
    ("PhotonOption",
     "Different options for handling off-shell photon distributions.",
     &LHAPDF::thePhotonOption, 7, true, false);
  static SwitchOption interfacePhotonOptionDipoleDampening
    (interfacePhotonOption,
     "DipoleDampening",
     "Dipole dampening by integration (very time consuming).",
     1);
  static SwitchOption interfacePhotonOptionMaxScales
    (interfacePhotonOption,
     "MaxScales",
     "\\f$P_0^2=\\max(Q_0^2,P^2)\\f$",
     2);
  static SwitchOption interfacePhotonOptionAddScales
    (interfacePhotonOption,
     "AddScales",
     "\\f$P_0^{'2}=Q_0^2+p^2\\f$",
     3);
  static SwitchOption interfacePhotonOptionPeffPreserve
    (interfacePhotonOption,
     "PeffPreserve",
     "\\f$P_{eff}\\f$ preserving momentum sum.",
     4);
  static SwitchOption interfacePhotonOptionPintPreserve
    (interfacePhotonOption,
     "PintPreserve",
     "\\f$P_{int}\\f$ preserving momentum sum and average evolution range.",
     5);
  static SwitchOption interfacePhotonOptionPeffMatch
    (interfacePhotonOption,
     "PeffMatch",
     "\\f$P_{eff}\\f$ matched to \\f$P_0\\f$ in \\f$P^2\\rightarrow Q^2\\f$ "
     "limit.",
     6);
  static SwitchOption interfacePhotonOptionPintMatch
    (interfacePhotonOption,
     "PintMatch",
     "\\f$P_{int}\\f$ matched to \\f$P_0\\f$ in \\f$P^2\\rightarrow Q^2\\f$ "
     "limit.",
     7);

  static Parameter<LHAPDF,int> interfaceMaxNSet
    ("MaxNSet",
     "The maximum number of simultaneous pdfs that can be used in LHAPDF. "
     "Should be set to the parameter <code>nmxset</code> in the "
     "<code>parmsetup.inc</code> file compiled into the installed LHAPDF "
     "library you are using (by default this is set to 3)",
     0, 3, 1, 0,
     true, false, Interface::lowerlim,
     &LHAPDF::setMaxNSet, &LHAPDF::getMaxNSet,
     (int(LHAPDF::*)()const)(0), (int(LHAPDF::*)()const)(0),
     (int(LHAPDF::*)()const)(0));


  static Command<LHAPDF> interfaceTest
    ("Test",
     "Write out the values of the chosen PDF set using the x, Q2 and P2 "
     "parameters supplied.",
     &LHAPDF::doTest, true);


  static Switch<LHAPDF,int> interfaceVerboseLevel
    ("VerboseLevel",
     "The verbosity of the output from the LHAPDF library.",
     &LHAPDF::theVerboseLevel, 0, true, false);
  static SwitchOption interfaceVerboseLevelSilent
    (interfaceVerboseLevel,
     "Silent",
     "Trying to inhibit all output from the LHAPDF library "
     "(unfortunately not always possible).",
     0);
  static SwitchOption interfaceVerboseLevelNormal
    (interfaceVerboseLevel,
     "Normal",
     "Normal output from the LHAPDF library "
     "(unfortunately to the standard output).",
     1);

  interfacePType.rank(10);
  interfacePDFName.rank(9);
  interfaceMember.rank(8);

}
