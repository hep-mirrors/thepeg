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
#include "ThePEG/Interface/ClassDocumentation.h"
// #include "ThePEG/Utilities/Timer.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "KinematicalCuts.tcc"
#endif

using namespace ThePEG;

void KinematicalCuts::Init() {

  static ClassDocumentation<KinematicalCuts> documentation
    ("There is no documentation for the ThePEG::KinematicalCuts class");

  static Parameter<KinematicalCuts,Energy> interfaceMHatMin
    ("SubProcess/MHatMin",
     "The minimum value allowed for \\f$\\hat{m}=\\sqrt{\\hat{s}}\\f$ in GeV "
     "in the hard subprocess. If the upper limit in <code>MHatMax</code> "
     "is less than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theMHatMin, GeV,
     2.0*GeV, 1.0*MeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfaceMHatMax
    ("SubProcess/MHatMax",
     "The minimum value allowed for \\f$\\hat{m}=\\sqrt{\\hat{s}}\\f$ in GeV "
     "in the hard subprocess If the lower limit in <code>MHatMin</code> "
     "is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theMHatMax, GeV,
     -1.0*GeV, -1.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfacePTHatMin
    ("SubProcess/PTHatMin",
     "The minimum value allowed for \\f$\\hat{p_\\perp}\\f$ in GeV "
     "in the hard subprocess. If the upper limit in <code>PTHatMax</code> "
     "is less than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler",
     &KinematicalCuts::thePTHatMin, GeV,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfacePTHatMax
    ("SubProcess/PTHatMax",
     "The minimum value allowed for \\f$\\hat{p_\\perp}\\f$ in GeV "
     "in the hard subprocess If the lower limit in <code>PTHatMin</code> "
     "is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::thePTHatMax, GeV,
     -1.0*GeV, -1.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfacePTHatSingularMin
    ("SubProcess/PTHatSingularMin",
     "The minimum value allowed for \\f$\\hat{p_\\perp}\\f$ in GeV for "
     "processes which are singular in the limit "
     "\\f$\\hat{p_\\perp}\\rightarrow 0\\f$. This "
     "cut is in addition to <code>PTHatMin</code>. Hard "
     "\\f$2\\rightarrow 2\\f$ processes which do not proceed via intermediate "
     "resonances are considered singular if either or both final-state "
     "products have a mass less than <code>SingularMassMax</code>. This limit "
     "is not checked automatically, but is assumed to be checked by the "
     "relevant ThePEG::MEBase objects.",
     &KinematicalCuts::thePTHatSingularMin, GeV,
     1.0*GeV, 0.0*GeV, Constants::MaxEnergy,
     false, false, true);


  static Parameter<KinematicalCuts,Energy> interfaceSingularMassMax
    ("SubProcess/SingularMassMax",
     "Hard \\f$2\\rightarrow 2\\f$ processes which do not proceed via "
     "intermediate resonances are considered singular if either or both "
     "final-state products have a mass less than this limit (int GeV). For "
     "singular processes the aditional \\f$\\hat{p_\\perp}\\f$ cut in "
     "PTHatSingularMin should be applied. This limit is not "
     "checked automatically, but is assumed to be checked by the relevant "
     "ThePEG::PartonXSecFn objects.",
     &KinematicalCuts::theSingularMassMax, GeV,
     1.0*GeV, 0.0*GeV, Constants::MaxEnergy,
     false, false, true);

  static Parameter<KinematicalCuts,double> interfaceYStarMin
    ("Collision/YStarMin",
     "The minimum value of the scattering subsystem rapidity \\f$y^*\\f$ "
     "in the c.m. frame of the event, where \\f$y^* = (1/2)  \\ln(x_1/x_2)\\f$."
     " Must be less than <code>YStarMax</code>. This limit is automatically "
     "checked by the event handler.",
     &KinematicalCuts::theYStarMin,
     -10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true, 0, 0, 0, &KinematicalCuts::yStarMax);

  static Parameter<KinematicalCuts,double> interfaceYStarMax
    ("Collision/YStarMiax",
     "The maximum value of the scattering subsystem rapidity \\f$y^*\\f$ "
     "in the c.m. frame of the event, where \\f$y^* = (1/2)  \\ln(x_1/x_2)\\f$."
     " Must be larger than <code>YStarMin</code>. This limit is automatically "
     "checked by the event handler.",
     &KinematicalCuts::theYStarMax,
     10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true, 0, 0, &KinematicalCuts::yStarMin, 0);

  static Parameter<KinematicalCuts,double> interfaceMaxYMin
    ("Collision/MaxYMin",
     "The minimum value of the rapidity for the product with largest "
     "rapidity in a "
     "\\f$2 \\rightarrow 2\\f$ or a \\f$2 \\rightarrow 1 \\rightarrow 2\\f$ "
     "process, defined in the c.m. frame of the event. Must be less than "
     "<code>MaxYMax</code>. This limit is automatically checked by the "
     "event handler in the case of \\f$2 \\rightarrow 2\\f$ processes. In the "
     "case of \\f$2 \\rightarrow 1\\f$ processes it is the responsibility of "
     "the Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMaxYMin,
     -10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::minYMin, &KinematicalCuts::maxYMax);

  static Parameter<KinematicalCuts,double> interfaceMaxYMax
    ("Collision/MaxYMax",
     "The maximum value of the rapidity for the product with largest "
     "rapidity in a \\f$2 \\rightarrow 2\\f$ or a "
     "\\f$2 \\rightarrow 1 \\rightarrow 2\\f$ process, defined in the c.m. "
     "frame of the event. Must be less than <code>MaxYMin</code>. This "
     "limit is automatically checked by the event handler in the case of "
     "\\f$2 \\rightarrow 2\\f$ processes. In the case of "
     "\\f$2 \\rightarrow 1\\f$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMaxYMax,
     10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::maxYMinMax, 0);

  static Parameter<KinematicalCuts,double> interfaceMinYMin
    ("Collision/MinYMin",
     "The minimum value of the rapidity for the product with smallest "
     "rapidity in a \\f$2 \\rightarrow 2\\f$ or a "
     "\\f$2 \\rightarrow 1 \\rightarrow 2\\f$ process, defined in the c.m. "
     "frame of the event. Must be less than <code>MinYMax</code>. This "
     "limit is automatically checked by the event handler in the case of "
     "\\f$2 \\rightarrow 2\\f$ processes. In the case of "
     "\\f$2 \\rightarrow 1\\f$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMinYMin,
     -10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, 0, &KinematicalCuts::minYMaxMin);

  static Parameter<KinematicalCuts,double> interfaceMinYMax
    ("Collision/MinYMax",
     "The maximum value of the rapidity for the product with smallest "
     "rapidity in a \\f$2\\rightarrow 2\\f$ or a "
     "\\f$2\\rightarrow 1\\rightarrow 2\\f$ process, defined in the c.m. "
     "frame of the event. Must be less than <code>MinYMin</code>. This limit "
     "is automatically checked by the event handler in the case of "
     "\\f$2\\rightarrow 2\\f$ processes. In the case of "
     "\\f$2\\rightarrow 1\\f$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMinYMax,
     10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::minYMin, &KinematicalCuts::maxYMax);

  static Parameter<KinematicalCuts,double> interfaceMaxEtaMin
    ("Collision/MaxEtaMin",
     "The minimum value of the pseudo rapidity for the product with largest "
     "pseudo rapidity in a \\f$2\\rightarrow 2\\f$ or a "
     "\\f$2\\rightarrow 1\\rightarrow 2\\f$ process, defined in the c.m. "
     "frame of the event. Must be less than <code>MaxEtaMax</code>. This "
     "limit is automatically checked by the event handler in the case of "
     "\\f$2\\rightarrow 2\\f$ processes. In the case of "
     "\\f$2\\rightarrow 1\\f$ processes it is the responsibility of the"
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMaxEtaMin,
     -10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::minEtaMin, &KinematicalCuts::maxEtaMax);

  static Parameter<KinematicalCuts,double> interfaceMaxEtaMax
    ("Collision/MaxEtaMax",
     "The maximum value of the pseudo rapidity for the product with largest "
     "pseudo rapidity in a \\f$2\\rightarrow 2\\f$ or a "
     "\\f$2\\rightarrow 1\\rightarrow 2\\f$ process, defined in the c.m. "
     "frame of the event. Must be less than <code>MaxEtaMin</code>. This "
     "limit is automatically checked by the event handler in the case of "
     "\\f$2\\rightarrow 2\\f$ processes. In the case of "
     "\\f$2\\rightarrow 1\\f$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMaxEtaMax,
     10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::maxEtaMinMax, 0);

  static Parameter<KinematicalCuts,double> interfaceMinEtaMin
    ("Collision/MinEtaMin",
     "The minimum value of the pseudo rapidity for the product with smallest "
     "pseudo rapidity in a \\f$2\\rightarrow 2\\f$ or a "
     "\\f$2\\rightarrow 1\\rightarrow 2\\f$ process, defined in the c.m. "
     "frame of the event. Must be less than <code>MinEtaMax</code>. This "
     "limit is automatically checked by the event handler in the case of "
     "\\f$2\\rightarrow 2\\f$ processes. In the case of "
     "\\f$2\\rightarrow 1\\f$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMinEtaMin,
     -10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, 0, &KinematicalCuts::minEtaMaxMin);

  static Parameter<KinematicalCuts,double> interfaceMinEtaMax
    ("Collision/MinEtaMax",
     "The maximum value of the pseudo rapidity for the product with smallest "
     "pseudo rapidity in a \\f$2\\rightarrow 2\\f$ or a "
     "\\f$2\\rightarrow 1\\rightarrow 2\\f$ process, defined in the c.m. "
     "frame of the event. Must be less than <code>MinEtaMin</code>. This "
     "limit is automatically checked by the event handler in the case of "
     "\\f$2 \\rightarrow 2\\f$ processes. In the case of "
     "\\f$2 \\rightarrow 1\\f$ processes it is the responsibility of "
     "the Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMinEtaMax,
     10.0, -Constants::MaxRapidity, Constants::MaxRapidity,
     false, false, true,
     0, 0, &KinematicalCuts::minEtaMin, &KinematicalCuts::maxEtaMax);

  static Parameter<KinematicalCuts,double> interfaceMaxCTMin
    ("Collision/MaxCosThetaMin",
     "The minimum value of \\f$\\cos{\\theta^*}\\f$ for the product with "
     "largest \\f$\\cos{\\theta^*}\\f$ in a "
     "\\f$2 \\rightarrow 2\\f$ or a \\f$2 \\rightarrow 1 "
     "\\rightarrow 2\\f$ process, defined in the c.m. frame of the event. "
     "Must be less than <code>MaxCosThetaMax</code>. This limit is "
     "automatically checked by the event handler in the case of "
     "\\f$2 \\rightarrow 2\\f$ processes. In the case of "
     "\\f$2 \\rightarrow 1\\f$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMaxCTMin,
     -1.0, -1.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::minCTMin, &KinematicalCuts::maxCTMax);

  static Parameter<KinematicalCuts,double> interfaceMaxCTMax
    ("Collision/MaxCosThetaMax",
     "The maximum value of \\f$\\cos{\\theta^*}\\f$ for the product with "
     "largest \\f$\\cos{\\theta^*}\\f$ in a \\f$2 \\rightarrow 2\\f$ or a "
     "\\f$2 \\rightarrow 1 \\rightarrow 2\\f$ process, defined in the c.m. "
     "frame of the event. Must be less than <code>MaxCosThetaMin</code>. "
     "This limit is automatically checked by the event handler in the case of "
     "\\f$2 \\rightarrow 2\\f$ processes. In the case of "
     "\\f$2 \\rightarrow 1\\f$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMaxCTMax,
     1.0, -1.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::maxCTMinMax, 0);

  static Parameter<KinematicalCuts,double> interfaceMinCTMin
    ("Collision/MinCosThetaMin",
     "The minimum value of \\f$\\cos{\\theta^*}\\f$ for the product with "
     "smallest \\f$\\cos{\\theta^*}\\f$ in a \\f$2 \\rightarrow 2\\f$ or a "
     "\\f$2 \\rightarrow 1 \\rightarrow 2\\f$ process, defined in the c.m. "
     "frame of the event. Must be less than <code>MinCosThetaMax</code>. "
     "This limit is automatically checked by the event handler in the case of "
     "\\f$2\\rightarrow 2\\f$ processes. In the case of "
     "\\f$2 \\rightarrow 1\\f$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMinCTMin,
     -1.0, -1.0, 1.0, false, false, true,
     0, 0, 0, &KinematicalCuts::minCTMaxMin);

  static Parameter<KinematicalCuts,double> interfaceMinCTMax
    ("Collision/MinCosThetaMax",
     "The maximum value of \\f$\\cos{\\theta^*}\\f$ for the product with "
     "smallest \\f$\\cos{\\theta^*}\\f$ in a \\f$2 \\rightarrow 2\\f$ or a "
     "\\f$2 \\rightarrow 1 \\rightarrow 2\\f$ process, defined in the c.m. "
     "frame of the event. Must be less than <code>MinCosThetaMin</code>. "
     "This limit is automatically checked by the event handler in the case of "
     "\\f$2 \\rightarrow 2\\f$ processes. In the case of "
     "\\f$2 \\rightarrow 1\\f$ processes it is the responsibility of the "
     "Decay handler performing the resonance decay to check the limit.",
     &KinematicalCuts::theMinCTMax,
     1.0, -1.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::minCTMin, &KinematicalCuts::maxCTMax);

  static Parameter<KinematicalCuts,double> interfaceX1Min
    ("Collision/X1Min",
     "The minimum allowed value of \\f$x_1\\f$ for the parton entering the "
     "hard interaction from side 1 "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theX1Min,
     0.0, 0.0, 1.0, false, false, true,
     0, 0, 0, &KinematicalCuts::x1Max);

  static Parameter<KinematicalCuts,double> interfaceX1Max
    ("Collision/X1Max",
     "The maximum allowed value of \\f$x_1\\f$ for the parton entering the "
     "hard interaction from side 1 "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theX1Max,
     1.0, 0.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::x1Min, 0);

  static Parameter<KinematicalCuts,double> interfaceX2Min
    ("Collision/X2Min",
     "The minimum allowed value of \\f$x_2\\f$ for the parton entering the "
     "hard interaction from side 2 "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theX2Min,
     0.0, 0.0, 1.0, false, false, true,
     0, 0, 0, &KinematicalCuts::x2Max);

  static Parameter<KinematicalCuts,double> interfaceX2Max
    ("Collision/X2Max",
     "The maximum allowed value of \\f$x_2\\f$ for the parton entering the "
     "hard interaction from side 2 "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theX2Max,
     1.0, 0.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::x2Min, 0);

  static Parameter<KinematicalCuts,double> interfaceXFMin
    ("Collision/XFMin",
     "The minimum allowed value of \\f$x_F=x_1-x_2\\f$. "
     "This limit is automatically checked by the event handler",
     &KinematicalCuts::theXFMin,
     -1.0, -1.0, 1.0, false, false, true,
     0, 0, 0, &KinematicalCuts::xFMax);

  static Parameter<KinematicalCuts,double> interfaceXFMax
    ("Collision/XFMax",
     "The maximum allowed value of \\f$x_F=x_1-x_2\\f$. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theXFMin,
     1.0, -1.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::xFMin, 0);

  static Parameter<KinematicalCuts,double> interfaceCTHMin
    ("SubProcess/CosThetaHatMin",
     "The minimum allowed value of \\f$\\cos{\\hat{\\theta}}\\f$, where "
     "\\f$\\hat{\\theta}\\f$ is the scattering angle in the restframe of a "
     "hard \\f$2\\rightarrow 2\\f$ scattering. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theCTHMin,
     -1.0, -1.0, 1.0, false, false, true,
     0, 0, 0, &KinematicalCuts::cTHMax);

  static Parameter<KinematicalCuts,double> interfaceCTHMax
    ("SubProcess/CosThetaHatMax",
     "The maximum allowed value of \\f$\\cos{\\hat{\\theta}}\\f$, where "
     "\\f$\\hat{\\theta}\\f$ is the scattering angle in the restframe of a "
     "hard \\f$2\\rightarrow 2\\f$ scattering. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theCTHMax,
     1.0, -1.0, 1.0, false, false, true,
     0, 0, &KinematicalCuts::cTHMin, 0);

  static Parameter<KinematicalCuts,Energy2> interfaceTHatMin
    ("SubProcess/THatMin",
     "The minimum allowed value of \\f$|\\hat{t}|=-\\hat{t}\\f$ in "
     "GeV<sup>2</sup> in a hard \\f$2\\rightarrow 2\\f$ scattering. If the "
     "upper limit in <code>THatMax</code> "
     "is less than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theTHatMin, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceTHatMax
    ("SubProcess/THatMax",
     "The maximum allowed value of \\f$|\\hat{t}|=-\\hat{t}\\f$ in "
     "GeV<sup>2</sup> in a hard \\f$2\\rightarrow 2\\f$ scattering. If the "
     "lower limit in <code>THatMin</code> "
     "is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theTHatMax, GeV2,
     -1.0*GeV, -1.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceUHatMin
    ("SubProcess/UHatMin",
     "The minimum allowed value of \\f$|\\hat{u}|=-\\hat{u}\\f$ in "
     "GeV<sup>2</sup> in a hard \\f$2\\rightarrow 2\\f$ scattering. If the "
     "upper limit in <code>UHatMax</code> "
     "is less than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theUHatMin, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceUHatMax
    ("SubProcess/UHatMax",
     "The maximum allowed value of \\f$|\\hat{u}|=-\\hat{u}\\f$ in "
     "GeV<sup>2</sup> in a hard \\f$2\\rightarrow 2\\f$ scattering. If the "
     "lower limit in <code>UHatMin</code> "
     "is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler.",
     &KinematicalCuts::theUHatMax, GeV2,
     -1.0*GeV, -1.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceScaleMin
    ("SubProcess/ScaleMin",
     "The minimum allowed value of the user-defined scale in GeV<sup>2</sup> "
     "in a hard scattering. If the upper limit in "
     "<code>SubProcess/ScaleMax</code> is less than this, the upper limit "
     "is inactive. This limit is automatically checked by the event handler.",
     &KinematicalCuts::theScaleMin, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceScaleMax
    ("SubProcess/ScaleMax",
     "The maximum allowed value of user defined scale in GeV<sup>2</sup> "
     "in a hard scattering. If the lower limit in "
     "<code>SubProcess/ScaleMin</code> is larger than this, the upper limit "
     "is inactive. This limit is automatically checked by the event handler.",
     &KinematicalCuts::theScaleMax, GeV2,
     -1.0*GeV, -1.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfaceDISLepton1EnergyMin
    ("DIS/Lepton1EnergyMin",
     "In Deep inelastic scattering of leptons, this gives the minimum energy "
     "in GeV allowed for the scattered (first) lepton. If the upper limit "
     "given in <code>Lepton1EnergyMax</code> is smaller than this, the upper "
     "limit is inactive. This limit is automatically checked by the event "
     "handler.",
     &KinematicalCuts::theDISLepton1EnergyMin, GeV,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfaceDISLepton2EnergyMin
    ("DIS/Lepton2EnergyMin",
     "In Deep inelastic scattering of leptons, this gives the minimum energy "
     "in GeV allowed for the scattered (second) lepton. If the upper limit "
     "given in <code>Lepton2EnergyMax</code> is smaller than this, the upper "
     "limit is inactive. This limit is automatically checked by the event "
     "handler.",
     &KinematicalCuts::theDISLepton2EnergyMin, GeV,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfaceDISLepton1EnergyMax
    ("DIS/Lepton1EnergyMax",
     "In Deep inelastic scattering of leptons, this gives the maximum energy "
     "in GeV allowed for the scattered (first) lepton. If the lower limit "
     "given in <code>Lepton1EnergyMin</code> is larger than this, the upper "
     "limit is inactive. This limit is automatically checked by the event "
     "handler.",
     &KinematicalCuts::theDISLepton1EnergyMax, GeV,
     -1.0*GeV, 0.0*GeV, Constants::MaxEnergy, false, false, true);

  static Parameter<KinematicalCuts,Energy> interfaceDISLepton2EnergyMax
    ("DIS/Lepton2EnergyMax",
     "In Deep inelastic scattering of leptons, this gives the maximum energy "
     "in GeV allowed for the scattered (second) lepton. If the lower limit "
     "given in <code>Lepton2EnergyMin</code> is larger than this, the upper "
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
     "DIS/UseDISCuts is on.",
     &KinematicalCuts::theDISLepton1AngleMin,
     0.0, 0.0, Constants::pi, false, false, true,
     0, 0, 0, &KinematicalCuts::DISLepton1AngleMax);

  static Parameter<KinematicalCuts,double> interfaceDISLepton1AngleMax
    ("DIS/Lepton1AngleMax",
     "In Deep inelastic scattering of leptons, this gives the maximum angle "
     "allowed for the scattered (first) lepton. This limit is "
     "automatically checked by the event handler if "
     "<code>DIS/UseDISCuts</code> is on.",
     &KinematicalCuts::theDISLepton1AngleMax,
     Constants::pi, 0.0, Constants::pi, false, false, true,
     0, 0, &KinematicalCuts::DISLepton1AngleMin, 0);

  static Parameter<KinematicalCuts,double> interfaceDISLepton2AngleMin
    ("DIS/Lepton2AngleMin",
     "In Deep inelastic scattering of leptons, this gives the minimum angle "
     "allowed for the scattered (first) lepton. This limit is "
     "automatically checked by the event handler if "
     "<code>DIS/UseDISCuts</code> is on.",
     &KinematicalCuts::theDISLepton2AngleMin,
     0.0, 0.0, Constants::pi, false, false, true,
     0, 0, 0, &KinematicalCuts::DISLepton2AngleMax);

  static Parameter<KinematicalCuts,double> interfaceDISLepton2AngleMax
    ("DIS/Lepton2AngleMax",
     "In Deep inelastic scattering of leptons, this gives the maximum angle "
     "allowed for the scattered (first) lepton. This limit is "
     "automatically checked by the event handler if "
     "<code>DIS/UseDISCuts</code> is on.",
     &KinematicalCuts::theDISLepton2AngleMax,
     Constants::pi, 0.0, Constants::pi, false, false, true,
     0, 0, &KinematicalCuts::DISLepton2AngleMin, 0);

  static Parameter<KinematicalCuts,Energy2> interfaceDISQ21Min
    ("DIS/Q21Min",
     "In Deep inelastic scattering of leptons, this gives the minimum "
     "virtuality, \\f$Q_1^2\\f$ in GeV<sup>2</sup>, allowed for the boson "
     "emitted from the (first) lepton. If the upper limit given in "
     "<code>Q21Max</code> is smaller than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler if "
     "<code>DIS/UseDISCuts</code> is on. Note that for some processes "
     "\\f$Q_1^2=|\\hat{t}|\\f$.",
     &KinematicalCuts::theDISQ21Min, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceDISQ21Max
    ("DIS/Q21Max",
     "In Deep inelastic scattering of leptons, this gives the maximum "
     "virtuality, \\f$Q_1^2\\f$ in GeV<sup>2</sup>, allowed for the boson "
     "emitted from the (first) lepton. If the lower limit given in "
     "<code>Q21Min</code> is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler if "
     "<code>DIS/UseDISCuts</code> is on. Note that for some processes "
     "\\f$Q_1^2=|\\hat{t}|\\f$.",
     &KinematicalCuts::theDISQ21Max, GeV2,
     -1.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceDISQ22Min
    ("DIS/Q22Min",
     "In Deep inelastic scattering of leptons, this gives the minimum "
     "virtuality, \\f$Q_2^2\\f$ in GeV<sup>2</sup>, allowed for the boson "
     "emitted from the (second) lepton. If the upper limit given in "
     "<code>Q22Max</code> is smaller than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler if "
     "<code>DIS/UseDISCuts</code> is on. Note that for some processes "
     "\\f$Q_2^2=|\\hat{t}|\\f$.",
     &KinematicalCuts::theDISQ22Min, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceDISQ22Max
    ("DIS/Q22Max",
     "In Deep inelastic scattering of leptons, this gives the maximum "
     "virtuality, \\f$Q_2^2\\f$ in GeV<sup>2</sup>, allowed for the boson "
     "emitted from the (second) lepton. If the lower limit given in "
     "<code>Q22Min</code> is larger than this, the upper limit is inactive. "
     "This limit is automatically checked by the event handler if "
     "<code>DIS/UseDISCuts</code> is on. Note that for some processes "
     "\\f$Q_2^2=|\\hat{t}|\\f$.",
     &KinematicalCuts::theDISQ22Max, GeV2,
     -1.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceDISW2Min
    ("DIS/W2Min",
     "In Deep inelastic scattering of leptons, this gives the minimum "
     "invariant mass squared of the hadronic system, \\f$W^2\\f$ in "
     "Gev<sup>2</sup>. If the upper limit given in <code>W2Max</code> is "
     "smaller than this, the upper limit is inactive. This limit is "
     "automatically checked by the event handler if "
     "<code>DIS/UseDISCuts</code> is on.",
     &KinematicalCuts::theDISW2Min, GeV2,
     0.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Parameter<KinematicalCuts,Energy2> interfaceDISW2Max
    ("DIS/W2Max",
     "In Deep inelastic scattering of leptons, this gives the maximum "
     "invariant mass squared of the hadronic system, \\f$W^2\\f$ in "
     "GeV<sup>2</sup>. If the lower limit given in <code>W2Min</code> is "
     "larger than this, the upper limit is inactive. This limit is "
     "automatically checked by the event handler if "
     "<code>DIS/UseDISCuts</code> is on.",
     &KinematicalCuts::theDISW2Max, GeV2,
     -1.0*GeV, 0.0*GeV, Constants::MaxEnergy2, false, false, true);

  static Reference<KinematicalCuts,MatchLepton> interfaceLeptonMatcher
    ("LeptonMatcher",
     "A matcher object to be used to identify leptons.",
     &KinematicalCuts::theLeptonMatcher,
     true, true, true, false);

}

