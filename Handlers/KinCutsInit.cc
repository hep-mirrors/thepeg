// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the KinematicalCuts class.
//

#include "KinematicalCuts.h"
#include "KinematicalCuts.xh"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/Switch.h"
// #include "ThePEG/Utilities/Timer.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "KinematicalCuts.tcc"
#endif

using namespace ThePEG;

void KinematicalCuts::Init() {

  static Parameter<KinematicalCuts,Energy> interfaceMHatMin
    ("SubProcess/MHatMin",
     "The minimum value allowed for $\\hat{m}=\\sqrt{\\hat{s}}$ in GeV "
     "in the hard subprocess. If the upper limit in \\parameter{MHatMax} "
     "is less than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theMHatMin, GeV,
     2.0*GeV, 1.0*MeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfaceMHatMax
    ("SubProcess/MHatMax",
     "The minimum value allowed for $\\hat{m}=\\sqrt{\\hat{s}}$ in GeV "
     "in the hard subprocess If the lower limit in \\parameter{MHatMin} "
     "is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theMHatMax, GeV,
     -1.0*GeV, -1.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfacePTHatMin
    ("SubProcess/PTHatMin",
     "The minimum value allowed for $\\hat{p_\\perp}$ in GeV "
     "in the hard subprocess. If the upper limit in \\parameter{PTHatMax} "
     "is less than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler",
     &KinematicalCuts::thePTHatMin, GeV,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfacePTHatMax
    ("SubProcess/PTHatMax",
     "The minimum value allowed for $\\hat{p_\\perp}$ in GeV "
     "in the hard subprocess If the lower limit in \\parameter{PTHatMin} "
     "is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::thePTHatMax, GeV,
     -1.0*GeV, -1.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfacePTHatSingularMin
    ("SubProcess/PTHatSingularMin",
     "The minimum value allowed for $\\hat{p_\\perp}$ in GeV for processes "
     "which are singular in the limit $\\hat{p_\\perp}\\rightarrow 0$. This "
     "cut is in addition to \\parameter{PTHatMin}. Hard $2\rightarrow 2$ "
     "processes which do not proceed via intermediate resonances are "
     "considered singular if either or both final-state products have a mass "
     "less than \\parameter{SingularMassMax}. This limit is not checked "
     "automatically, but is assumed to be checked by the relevant "
     "\\class{PartonXSecFn} objects.",
     &KinematicalCuts::thePTHatSingularMin, GeV,
     1.0*GeV, 0.0*GeV, Constants::MaxEnergy,
     false, false, true);


  static Parameter<KinematicalCuts,Energy> interfaceSingularMassMax
    ("SubProcess/SingularMassMax",
     "Hard $2\rightarrow 2$ processes which do not proceed via intermediate "
     "resonances are considered singular if either or both final-state "
     "products have a mass less than this limit (int GeV). For singular "
     "processes the aditional $\\hat{p_\\perp}$ cut in "
     "\\Parameter{PTHatSingularMin} should be applied. This limit is not "
     "checked automatically, but is assumed to be checked by the relevant "
     "\\class{PartonXSecFn} objects.",
     &KinematicalCuts::theSingularMassMax, GeV,
     1.0*GeV, 0.0*GeV, Constants::MaxEnergy,
     false, false, true);

  static Parameter<KinematicalCuts,double> interfaceYStarMin
    ("Collision/YStarMin",
     "The minimum value of the scattering subsystem rapidity $y^*$ "
     "in the c.m. frame of the event, where $y^* = (1/2)  \\ln(x_1/x_2)$. "
     "Must be less than \\parameter{YStarMax}. This limit is automatically "
     "checked by the event handler.",
     &KinematicalCuts::theYStarMin,
     -10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true, 0, 0, 0, &KinematicalCuts::yStarMax);

  static Parameter<KinematicalCuts,double> interfaceYStarMax
    ("Collision/YStarMiax",
     "The maximum value of the scattering subsystem rapidity $y^*$ "
     "in the c.m. frame of the event, where $y^* = (1/2)  \\ln(x_1/x_2)$. "
     "Must be larger than \\parameter{YStarMin}. This limit is automatically "
     "checked by the event handler.",
     &KinematicalCuts::theYStarMax,
     10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true, 0, 0, &KinematicalCuts::yStarMin, 0);

  static Parameter<KinematicalCuts,double> interfaceMaxYMin
    ("Collision/MaxYMin",
     "The minimum value of the rapidity for the product with largest "
     "rapidity in a $2 \rightarrow 2$ or a $2 \rightarrow 1 \rightarrow 2$ "
     "process, defined in the c.m. frame of the event. Must be less than "
     "\\parameter{MaxYMax}. This limit is automatically checked by the "
     "event handler in the case of $2 \rightarrow 2$ processes. In the "
     "case of $2 \rightarrow 1$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMaxYMin,
     -10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::minYMin, &KinematicalCuts::maxYMax);

  static Parameter<KinematicalCuts,double> interfaceMaxYMax
    ("Collision/MaxYMax",
     "The maximum value of the rapidity for the product with largest "
     "rapidity in a $2 \rightarrow 2$ or a $2 \rightarrow 1 \rightarrow 2$ "
     "process, defined in the c.m. frame of the event. Must be less than "
     "\\parameter{MaxYMin}. This limit is automatically checked by the "
     "event handler in the case of $2 \rightarrow 2$ processes. In the "
     "case of $2 \rightarrow 1$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMaxYMax,
     10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::maxYMinMax, 0);

  static Parameter<KinematicalCuts,double> interfaceMinYMin
    ("Collision/MinYMin",
     "The minimum value of the rapidity for the product with smallest "
     "rapidity in a $2 \rightarrow 2$ or a $2 \rightarrow 1 \rightarrow 2$ "
     "process, defined in the c.m. frame of the event. Must be less than "
     "\\parameter{MinYMax}. This limit is automatically checked by the "
     "event handler in the case of $2 \rightarrow 2$ processes. In the "
     "case of $2 \rightarrow 1$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMinYMin,
     -10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, 0, &KinematicalCuts::minYMaxMin);

  static Parameter<KinematicalCuts,double> interfaceMinYMax
    ("Collision/MinYMax",
     "The maximum value of the rapidity for the product with smallest "
     "rapidity in a $2 \rightarrow 2$ or a $2 \rightarrow 1 \rightarrow 2$ "
     "process, defined in the c.m. frame of the event. Must be less than "
     "\\parameter{MinYMin}. This limit is automatically checked by the "
     "event handler in the case of $2 \rightarrow 2$ processes. In the "
     "case of $2 \rightarrow 1$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMinYMax,
     10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::minYMin, &KinematicalCuts::maxYMax);

  static Parameter<KinematicalCuts,double> interfaceMaxEtaMin
    ("Collision/MaxEtaMin",
     "The minimum value of the pseudo rapidity for the product with largest "
     "pseudo rapidity in a $2 \rightarrow 2$ or a $2 \rightarrow 1 \rightarrow "
     "2$ process, defined in the c.m. frame of the event. Must be less than "
     "\\parameter{MaxEtaMax}. This limit is automatically checked by the "
     "event handler in the case of $2 \rightarrow 2$ processes. In the "
     "case of $2 \rightarrow 1$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMaxEtaMin,
     -10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::minEtaMin, &KinematicalCuts::maxEtaMax);

  static Parameter<KinematicalCuts,double> interfaceMaxEtaMax
    ("Collision/MaxEtaMax",
     "The maximum value of the pseudo rapidity for the product with largest "
     "pseudo rapidity in a $2 \rightarrow 2$ or a $2 \rightarrow 1 \rightarrow "
     "2$ process, defined in the c.m. frame of the event. Must be less than "
     "\\parameter{MaxEtaMin}. This limit is automatically checked by the "
     "event handler in the case of $2 \rightarrow 2$ processes. In the "
     "case of $2 \rightarrow 1$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMaxEtaMax,
     10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::maxEtaMinMax, 0);

  static Parameter<KinematicalCuts,double> interfaceMinEtaMin
    ("Collision/MinEtaMin",
     "The minimum value of the pseudo rapidity for the product with smallest "
     "pseudo rapidity in a $2 \rightarrow 2$ or a $2 \rightarrow 1 \rightarrow "
     "2$ process, defined in the c.m. frame of the event. Must be less than "
     "\\parameter{MinEtaMax}. This limit is automatically checked by the "
     "event handler in the case of $2 \rightarrow 2$ processes. In the "
     "case of $2 \rightarrow 1$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMinEtaMin,
     -10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, 0, &KinematicalCuts::minEtaMaxMin);

  static Parameter<KinematicalCuts,double> interfaceMinEtaMax
    ("Collision/MinEtaMax",
     "The maximum value of the pseudo rapidity for the product with smallest "
     "pseudo rapidity in a $2 \rightarrow 2$ or a $2 \rightarrow 1 \rightarrow "
     "2$ process, defined in the c.m. frame of the event. Must be less than "
     "\\parameter{MinEtaMin}. This limit is automatically checked by the "
     "event handler in the case of $2 \rightarrow 2$ processes. In the "
     "case of $2 \rightarrow 1$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMinEtaMax,
     10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::minEtaMin, &KinematicalCuts::maxEtaMax);

  static Parameter<KinematicalCuts,double> interfaceMaxCTMin
    ("Collision/MaxCosThetaMin",
     "The minimum value of $\\cos{\\theta^*}$ for the product with largest "
     "$\\cos{\\theta^*}$ in a $2 \rightarrow 2$ or a $2 \rightarrow 1 "
     "\rightarrow 2$ process, defined in the c.m. frame of the event. "
     "Must be less than \\parameter{MaxCosThetaMax}. This limit is "
     "automatically checked by the event handler in the case of "
     "$2 \rightarrow 2$ processes. In the case of $2 \rightarrow 1$ "
     "processes it is the responsibility of the Decay handler performing "
     "the resonance decay to check the limit.",
     &KinematicalCuts::theMaxCTMin,
     -1.0, -1.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::minCTMin, &KinematicalCuts::maxCTMax);

  static Parameter<KinematicalCuts,double> interfaceMaxCTMax
    ("Collision/MaxCosThetaMax",
     "The maximum value of $\\cos{\\theta^*}$ for the product with largest "
     "$\\cos{\\theta^*}$ in a $2 \rightarrow 2$ or a $2 \rightarrow 1 "
     "\rightarrow 2$ process, defined in the c.m. frame of the event. "
     "Must be less than \\parameter{MaxCosThetaMin}. This limit is "
     "automatically checked by the event handler in the case of "
     "$2 \rightarrow 2$ processes. In the case of $2 \rightarrow 1$ "
     "processes it is the responsibility of the Decay handler performing "
     "the resonance decay to check the limit.",
     &KinematicalCuts::theMaxCTMax,
     1.0, -1.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::maxCTMinMax, 0);

  static Parameter<KinematicalCuts,double> interfaceMinCTMin
    ("Collision/MinCosThetaMin",
     "The minimum value of $\\cos{\\theta^*}$ for the product with smallest "
     "$\\cos{\\theta^*}$ in a $2 \rightarrow 2$ or a $2 \rightarrow 1 "
     "\rightarrow 2$ process, defined in the c.m. frame of the event. "
     "Must be less than \\parameter{MinCosThetaMax}. This limit is "
     "automatically checked by the event handler in the case of "
     "$2 \rightarrow 2$ processes. In the case of $2 \rightarrow 1$ "
     "processes it is the responsibility of the Decay handler performing "
     "the resonance decay to check the limit.",
     &KinematicalCuts::theMinCTMin,
     -1.0, -1.0, 1.0, false, false, true,
     0, 0, 0, &KinematicalCuts::minCTMaxMin);

  static Parameter<KinematicalCuts,double> interfaceMinCTMax
    ("Collision/MinCosThetaMax",
     "The maximum value of $\\cos{\\theta^*}$ for the product with smallest "
     "$\\cos{\\theta^*}$ in a $2 \rightarrow 2$ or a $2 \rightarrow 1 "
     "\rightarrow 2$ process, defined in the c.m. frame of the event. "
     "Must be less than \\parameter{MinCosThetaMin}. This limit is "
     "automatically checked by the event handler in the case of "
     "$2 \rightarrow 2$ processes. In the case of $2 \rightarrow 1$ "
     "processes it is the responsibility of the Decay handler performing "
     "the resonance decay to check the limit.",
     &KinematicalCuts::theMinCTMax,
     1.0, -1.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::minCTMin, &KinematicalCuts::maxCTMax);

  static Parameter<KinematicalCuts,double> interfaceX1Min
    ("Collision/X1Min",
     "The minimum allowed value of $x_1$ for the parton entering the "
     "hard interaction from side 1 "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theX1Min,
     0.0, 0.0, 1.0, false, false, true,
     0, 0, 0, &KinematicalCuts::x1Max);

  static Parameter<KinematicalCuts,double> interfaceX1Max
    ("Collision/X1Max",
     "The maximum allowed value of $x_1$ for the parton entering the "
     "hard interaction from side 1 "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theX1Max,
     1.0, 0.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::x1Min, 0);

  static Parameter<KinematicalCuts,double> interfaceX2Min
    ("Collision/X2Min",
     "The minimum allowed value of $x_2$ for the parton entering the "
     "hard interaction from side 2 "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theX2Min,
     0.0, 0.0, 1.0, false, false, true,
     0, 0, 0, &KinematicalCuts::x2Max);

  static Parameter<KinematicalCuts,double> interfaceX2Max
    ("Collision/X2Max",
     "The maximum allowed value of $x_2$ for the parton entering the "
     "hard interaction from side 2 "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theX2Max,
     1.0, 0.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::x2Min, 0);

  static Parameter<KinematicalCuts,double> interfaceXFMin
    ("Collision/XFMin",
     "The minimum allowed value of $x_F=x_1-x_2$. "
     "This limit is automatically checked by the event handler",
     &KinematicalCuts::theXFMin,
     -1.0, -1.0, 1.0, false, false, true,
     0, 0, 0, &KinematicalCuts::xFMax);

  static Parameter<KinematicalCuts,double> interfaceXFMax
    ("Collision/XFMax",
     "The maximum allowed value of $x_F=x_1-x_2$. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theXFMin,
     1.0, -1.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::xFMin, 0);

  static Parameter<KinematicalCuts,double> interfaceCTHMin
    ("SubProcess/CosThetaHatMin",
     "The minimum allowed value of $\\cos{\\hat{\\theta}}$, where "
     "$\\hat{\\theta}$ is the scattering angle in the restframe of a hard "
     "$2\rightarrow 2$ scattering. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theCTHMin,
     -1.0, -1.0, 1.0, false, false, true,
     0, 0, 0, &KinematicalCuts::cTHMax);

  static Parameter<KinematicalCuts,double> interfaceCTHMax
    ("SubProcess/CosThetaHatMax",
     "The maximum allowed value of $\\cos{\\hat{\\theta}}$, where "
     "$\\hat{\\theta}$ is the scattering angle in the restframe of a hard "
     "$2\rightarrow 2$ scattering. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theCTHMax,
     1.0, -1.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::cTHMin, 0);

  static Parameter<KinematicalCuts,Energy2> interfaceTHatMin
    ("SubProcess/THatMin",
     "The minimum allowed value of $|\\hat{t}|=-\\hat{t}$ in GeV$^2$ in a hard "
     "$2\rightarrow 2$ scattering. If the upper limit in \\parameter{THatMax} "
     "is less than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theTHatMin, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceTHatMax
    ("SubProcess/THatMax",
     "The maximum allowed value of $|\\hat{t}|=-\\hat{t}$ in GeV$^2$ in a hard "
     "$2\rightarrow 2$ scattering. If the lower limit in \\parameter{THatMin} "
     "is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theTHatMax, GeV2,
     -1.0*GeV, -1.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceUHatMin
    ("SubProcess/UHatMin",
     "The minimum allowed value of $|\\hat{u}|=-\\hat{u}$ in GeV$^2$ in a hard "
     "$2\rightarrow 2$ scattering. If the upper limit in \\parameter{UHatMax} "
     "is less than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theUHatMin, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceUHatMax
    ("SubProcess/UHatMax",
     "The maximum allowed value of $|\\hat{u}|=-\\hat{u}$ in GeV$^2$ in a hard "
     "$2\rightarrow 2$ scattering. If the lower limit in \\parameter{UHatMin} "
     "is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theUHatMax, GeV2,
     -1.0*GeV, -1.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceScaleMin
    ("SubProcess/ScaleMin",
     "The minimum allowed value of the user-defined scale in GeV$^2$ in a hard "
     "scattering. If the upper limit in \\parameter{SubProcess/ScaleMax} "
     "is less than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theScaleMin, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceScaleMax
    ("SubProcess/ScaleMax",
     "The maximum allowed value of user defined scale in GeV$^2$ in a hard "
     "scattering. If the lower limit in \\parameter{SubProcess/ScaleMin} "
     "is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theScaleMax, GeV2,
     -1.0*GeV, -1.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfaceDISLepton1EnergyMin
    ("DIS/Lepton1EnergyMin",
     "In Deep inelastic scattering of leptons, this gives the minimum energy "
     "in GeV allowed for the scattered (first) lepton. If the upper limit "
     "given in \\parameter{Lepton1EnergyMax} is smaller than this, the upper "
     "limit is inactive. This limit is automatically checked by the event "
     "handler.",
     &KinematicalCuts::theDISLepton1EnergyMin, GeV,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfaceDISLepton2EnergyMin
    ("DIS/Lepton2EnergyMin",
     "In Deep inelastic scattering of leptons, this gives the minimum energy "
     "in GeV allowed for the scattered (second) lepton. If the upper limit "
     "given in \\parameter{Lepton2EnergyMax} is smaller than this, the upper "
     "limit is inactive. This limit is automatically checked by the event "
     "handler.",
     &KinematicalCuts::theDISLepton2EnergyMin, GeV,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfaceDISLepton1EnergyMax
    ("DIS/Lepton1EnergyMax",
     "In Deep inelastic scattering of leptons, this gives the maximum energy "
     "in GeV allowed for the scattered (first) lepton. If the lower limit "
     "given in \\parameter{Lepton1EnergyMin} is larger than this, the upper "
     "limit is inactive. This limit is automatically checked by the event "
     "handler.",
     &KinematicalCuts::theDISLepton1EnergyMax, GeV,
     -1.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfaceDISLepton2EnergyMax
    ("DIS/Lepton2EnergyMax",
     "In Deep inelastic scattering of leptons, this gives the maximum energy "
     "in GeV allowed for the scattered (second) lepton. If the lower limit "
     "given in \\parameter{Lepton2EnergyMin} is larger than this, the upper "
     "limit is inactive. This limit is automatically checked by the event "
     "handler.",
     &KinematicalCuts::theDISLepton2EnergyMax, GeV,
     -1.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true);

  static Switch<KinematicalCuts,bool> interfaceUseLeptoCuts
    ("DIS/UseDISCuts",
     "Main switch for cuts on Deep inelastic scattering of leptons.",
     &KinematicalCuts::useLeptoCuts, false, false, false);

  static SwitchOption interfaceUseLeptoCutsOff
    (interfaceUseLeptoCuts, "Off", "No DIS cuts are applied", 0);

  static SwitchOption interfaceUseLeptoCutsOn
    (interfaceUseLeptoCuts, "On", "All DIS cuts are applied", 1);

  static Parameter<KinematicalCuts,double> interfaceDISLepton1AngleMin
    ("DIS/Lepton1AngleMin",
     "In Deep inelastic scattering of leptons, this gives the minimum angle "
     "allowed for the scattered (first) lepton. This limit is "
     "automatically checked by the event handler if "
     "\\interface{DIS/UseDISCuts} is on.",
     &KinematicalCuts::theDISLepton1AngleMin,
     0.0, 0.0, Constants::pi, false, false, true,
     0, 0, 0, &KinematicalCuts::DISLepton1AngleMax);

  static Parameter<KinematicalCuts,double> interfaceDISLepton1AngleMax
    ("DIS/Lepton1AngleMax",
     "In Deep inelastic scattering of leptons, this gives the maximum angle "
     "allowed for the scattered (first) lepton. This limit is "
     "automatically checked by the event handler if "
     "\\interface{DIS/UseDISCuts} is on.",
     &KinematicalCuts::theDISLepton1AngleMax,
     Constants::pi, 0.0, Constants::pi, false, false, true,
     0, 0, &KinematicalCuts::DISLepton1AngleMin, 0);

  static Parameter<KinematicalCuts,double> interfaceDISLepton2AngleMin
    ("DIS/Lepton2AngleMin",
     "In Deep inelastic scattering of leptons, this gives the minimum angle "
     "allowed for the scattered (first) lepton. This limit is "
     "automatically checked by the event handler if "
     "\\interface{DIS/UseDISCuts} is on.",
     &KinematicalCuts::theDISLepton2AngleMin,
     0.0, 0.0, Constants::pi, false, false, true,
     0, 0, 0, &KinematicalCuts::DISLepton2AngleMax);

  static Parameter<KinematicalCuts,double> interfaceDISLepton2AngleMax
    ("DIS/Lepton2AngleMax",
     "In Deep inelastic scattering of leptons, this gives the maximum angle "
     "allowed for the scattered (first) lepton. This limit is "
     "automatically checked by the event handler if "
     "\\interface{DIS/UseDISCuts} is on.",
     &KinematicalCuts::theDISLepton2AngleMax,
     Constants::pi, 0.0, Constants::pi, false, false, true,
     0, 0, &KinematicalCuts::DISLepton2AngleMin, 0);

  static Parameter<KinematicalCuts,Energy2> interfaceDISQ21Min
    ("DIS/Q21Min",
     "In Deep inelastic scattering of leptons, this gives the minimum "
     "virtuality, $Q_1^2$ in GeV$^2$, allowed for the boson emitted from the "
     "(first) lepton. If the upper limit given in \\parameter{Q21Max} is "
     "smaller than this, the upper limit is inactive. This limit is "
     "automatically checked by the event handler if "
     "\\interface{DIS/UseDISCuts} is on. Note that for some processes "
     "$Q_1^2=|\\har{t}|$.",
     &KinematicalCuts::theDISQ21Min, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceDISQ21Max
    ("DIS/Q21Max",
     "In Deep inelastic scattering of leptons, this gives the maximum "
     "virtuality, $Q_1^2$ in GeV$^2$, allowed for the boson emitted from the "
     "(first) lepton. If the lower limit given in \\parameter{Q21Min} is "
     "larger than this, the upper limit is inactive. This limit is "
     "automatically checked by the event handler if "
     "\\interface{DIS/UseDISCuts} is on. Note that for some processes "
     "$Q_1^2=|\\har{t}|$.",
     &KinematicalCuts::theDISQ21Max, GeV2,
     -1.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceDISQ22Min
    ("DIS/Q22Min",
     "In Deep inelastic scattering of leptons, this gives the minimum "
     "virtuality, $Q_2^2$ in GeV$^2$, allowed for the boson emitted from the "
     "(second) lepton. If the upper limit given in \\parameter{Q22Max} is "
     "smaller than this, the upper limit is inactive. This limit is "
     "automatically checked by the event handler if "
     "\\interface{DIS/UseDISCuts} is on. Note that for some processes "
     "$Q_2^2=|\\har{t}|$.",
     &KinematicalCuts::theDISQ22Min, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceDISQ22Max
    ("DIS/Q22Max",
     "In Deep inelastic scattering of leptons, this gives the maximum "
     "virtuality, $Q_2^2$ in GeV$^2$, allowed for the boson emitted from the "
     "(second) lepton. If the lower limit given in \\parameter{Q22Min} is "
     "larger than this, the upper limit is inactive. This limit is "
     "automatically checked by the event handler if "
     "\\interface{DIS/UseDISCuts} is on. Note that for some processes "
     "$Q_2^2=|\\har{t}|$.",
     &KinematicalCuts::theDISQ22Max, GeV2,
     -1.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceDISW2Min
    ("DIS/W2Min",
     "In Deep inelastic scattering of leptons, this gives the minimum "
     "invariant mass squared of the hadronic system, $W^2$ in Gev$^2$. If the "
     "upper limit given in \\parameter{W2Max} is smaller than this, "
     "the upper limit is inactive. This limit is automatically checked "
     "by the event handler if \\interface{DIS/UseDISCuts} is on.",
     &KinematicalCuts::theDISW2Min, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceDISW2Max
    ("DIS/W2Max",
     "In Deep inelastic scattering of leptons, this gives the maximum "
     "invariant mass squared of the hadronic system, $W^2$ in GeV$^2$. If the "
     "lower limit given in \\parameter{W2Min} is larger than this, "
     "the upper limit is inactive. This limit is automatically checked "
     "by the event handler if \\interface{DIS/UseDISCuts} is on.",
     &KinematicalCuts::theDISW2Max, GeV2,
     -1.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Reference<KinematicalCuts,MatchLepton> interfaceLeptonMatcher
    ("LeptonMatcher",
     "A matcher object to be used to identify leptons.",
     &KinematicalCuts::theLeptonMatcher,
     true, true, true, false);

}

