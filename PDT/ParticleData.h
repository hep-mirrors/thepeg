// -*- C++ -*-
//
#ifndef ThePEG_ParticleData_H
#define ThePEG_ParticleData_H
//
// This is the declaration of the <!id>ParticleData<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>ParticleData<!!id> inherits from
// <!class>InterfacedBase<!!class> and represents the properties of a
// particle type. It is also able to produce instances of this
// particle type, and to decay them among other things.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/PDT/PDT.h"
#include "ThePEG/CLHEPWrap/PhysicalConstants.h"
#include "ThePEG/CLHEPWrap/LorentzVector.h"
#include "ThePEG/Interface/Interfaced.h"
#include "ThePEG/Utilities/Selector.h"
#include "ThePEG/PDT/WidthGenerator.fh"
#include "ThePEG/PDT/MassGenerator.fh"
#include "ThePEG/PDT/DecayMode.fh"
#include "ThePEG/Utilities/ClassTraits.h"
#include "ThePEG/Utilities/ClassDescription.h"

namespace ThePEG {

class ParticleData: public Interfaced {

public:

  friend class Repository;
  friend class DecayMode;
  typedef Selector<tDMPtr> DecaySelector;

public:

  ParticleData();
  ParticleData(const ParticleData &);
  virtual ~ParticleData();
  // Standard ctors and dtor.

  static PDPtr Create(long newId, string newPDGName);
  // Create a Particle which is its own anti-particle.

  static PDPair Create(long newId, string newPDGName, string newAntiPDGName);
  // Create a particle - anti particle  pair.

public:

  inline long id() const;
  // Acces to id number.

  inline string PDGName() const;
  // Return the generic PDG name.

  inline string genericName() const;
  // Return the standardized name of this particle.

  PPtr produceParticle(const Lorentz5Momentum &) const;
  PPtr produceParticle(const LorentzMomentum &) const;
  PPtr produceParticle(const Momentum3 & pp = Momentum3()) const;
  PPtr produceParticle(Energy m, const Momentum3 & pp = Momentum3()) const;
  PPtr produceParticle(Energy plus, Energy minus, Energy px, Energy py) const;
  // Produce a particle specifying momentum

  Energy generateMass() const;
  // Generate a mass for an instance of this particle type.

  Energy generateWidth(Energy m) const;
  // Given a mass of an instance of this particle type, calculate its
  // width.

  Length generateLifeTime(Energy m, Energy w) const;
  // Given a mass and a width of an instance of this particle type,
  // generate a life time.

  inline const DecaySelector & decaySelector() const;
  // Return the nominal selector for this particle.

  tDMPtr selectMode(Particle &) const;
  // Selects a decay mode randomly according to the branching ratios.

  inline Energy mass() const;
  inline Energy massMax() const;
  inline Energy massMin() const;
  // Get the nominal mass.

  inline virtual Energy constituentMass() const;
  // Return the constituent mass of this particle if relevant. This
  // version simply returns the nominal mass.

  Energy width(Energy);
  inline Energy width() const;
  // Set/get the width. If no width is specified, it is calculated
  // from the lifetime.

  Energy widthCut(Energy);
  inline Energy widthCut() const;
  // Set/get the width cut.

  Length cTau(Length);
  inline Length cTau() const;
  // Set/get cTau. If no life time is specified, it is calculated from
  // the width.

  PDT::Charge iCharge(PDT::Charge);
  inline Charge charge() const;
  inline PDT::Charge iCharge() const;
  inline bool charged() const;
  inline bool positive() const;
  inline bool negative() const;
  // Set/get the charge. In the set method the charge should be given
  // in units of e/3. In the charge() method the charge is returned in
  // standard units and in iCharge the charge is returned in units of e/3.

  PDT::Spin iSpin(PDT::Spin);
  inline AngularMomentum spin() const;
  inline PDT::Spin iSpin() const;
  // Set/get the spin. In the set method the spin should be given as
  // 2J+1 in units of hbar/2. In the spin() method the spin is
  // returned in standard units, and in iSpin the spin is returned as
  // 2J+1 in units of hbar/2.

  PDT::Color iColor(PDT::Color);
  PDT::Colour iColour(PDT::Colour);
  inline PDT::Color iColor() const;
  inline PDT::Colour iColour() const;
  inline bool colored() const;
  inline bool coloured() const;
  inline bool hasColour(bool anti = false) const;
  inline bool hasAntiColour() const;
  // Set/get the color of the particle in units of PDT::Color.

  void stable(bool);
  inline bool stable() const;
  // Set/get if particle is to be considered stable. If the decay
  // table is empty the get method always returns true, even if the
  // member variable is false.

  inline tPDPtr CC() const;
  // Get the pointer to the corresponding anti partner.

  void synchronized(bool);
  inline bool synchronized() const;
  // Set/get if the anti partner chould be changed automatically when
  // this object is changed.

  void synchronize();
  // If there is an anti partner, update this object to have correct
  // anti-properties.

  void massGenerator(tMassGenPtr);
  inline tMassGenPtr massGenerator() const;
  // Set/get the mass generator object.

  void widthGenerator(tWidthGeneratorPtr);
  inline tWidthGeneratorPtr widthGenerator() const;
  // Get/set the width generator object.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();

protected:

  virtual IBPtr clone() const;
  virtual PDPtr pdclone() const;
  virtual IBPtr fullclone() const;
  // Create a copy of this object. Also make copies the decay modes
  // and the anti-partner if it exists and if synchronized() is true.

  ParticleData(long newId, string newPDGName);
  // Protected constructor only to be used by subclasses or by the
  // Create method.

  virtual void readSetup(istream & is) throw(SetupException);
  // Read setup info from a standard stream.

  static void antiSetup(const PDPair & pap);
  // Used by subclasses or by the Create method to setup
  // anti-relationship.

  inline virtual void doinit() throw(InitException);
  // Initialize this object. Set up branching fractions etc.

  virtual void doupdate() throw(UpdateException);

  inline virtual void dofinish();

  virtual void rebind(const TranslationMap & trans) throw(RebindException);
  virtual IVector getReferences();

private:

  void addDecayMode(tDMPtr);
  void removeDecayMode(tDMPtr);
  // Add a decay mode for this particle.

  long theId;
  string thePDGName;
  // Name and Id number according to the STDHEP standard.

  Energy theMass;
  Energy theWidth;
  Energy theWidthCut;
  Length theCTau;
  // Mass, width, width cut and lifetime.

  PDT::Charge theCharge;
  PDT::Spin theSpin;
  // Three times the charge and 2 times the spin plus one.

  PDT::Color theColor;
  // The colour for this particle.

  MassGenPtr theMassGenerator;
  // A pointer to an object capable to generate a mass for a particle
  // of this type.

  bool isStable;
  // True if the particle is considered stable.

  DecaySelector theDecaySelector;
  DecaySet theDecayModes;
  // A map of branching fractions to decaymodes.

  WidthGeneratorPtr theWidthGenerator;
  bool variableRatio;
  // A pointer to an object capable to generate the branching
  // fractions for different decay modes for this particle type. The
  // object will be asked to generate branching fractions every time
  // the ParticleData object it updated and will modify the branching
  // fractions for every particle instance if variableRatio is true.

  tPDPtr theAntiPartner;
  bool syncAnti;
  // Pointer to the object corresponding to the antiparticle. Set to
  // zero if it is its own antiparticle. If syncAnti is true all
  // changes to this object will be transfered to the antiParticle.

  Energy theDefMass;
  void setMass(Energy);
  Energy defMass() const;
  Energy maxMass() const;
  Energy theDefWidth;
  void setWidth(Energy);
  Energy getWidth() const;
  Energy defWidth() const;
  Energy maxWidth() const;
  Energy theDefCut;
  void setCut(Energy);
  Energy getCut() const;
  Energy defCut() const;
  Energy maxCut() const;
  Length theDefCTau;
  void setCTau(Length);
  Length getCTau() const;
  Length defCTau() const;
  Length maxCTau() const;
  void setStable(long);
  long getStable() const;
  void setSync(long);
  long getSync() const;
  string doSync(string);
  void setMassGenerator(MassGenPtr);
  void setWidthGenerator(WidthGeneratorPtr);
  PDT::Charge theDefCharge;
  void setCharge(int);
  string ssetCharge(string);
  int getCharge() const;
  int defCharge() const;
  PDT::Spin theDefSpin;
  void setSpin(int);
  int getSpin() const;
  int defSpin() const;
  PDT::Colour theDefColour;
  void setColour(long);
  long getColour() const;
  long defColour() const;
  void insDecayModes(DMPtr dm, int);
  void delDecayModes(int i);
  vector<DMPtr> getDecayModes() const;
  // Utility functions for the interface.

  static ClassDescription<ParticleData> initParticleData;

};

template <>
struct BaseClassTrait<ParticleData,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<ParticleData>: public ClassTraitsBase<ParticleData> {
  static string className() { return "/ThePEG/ParticleData"; }
};

}

#include "ParticleData.icc"

#endif /* ThePEG_ParticleData_H */
