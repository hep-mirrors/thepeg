// -*- C++ -*-
#ifndef ThePEG_Particle_H
#define ThePEG_Particle_H
// This is the decalaration of the <!id>Particle<!!> class. It is uded
// to describe an instance of a partticle. Properties of the
// corresponding particle type can be accessed through a pointer to a
// <!class>ParticleData<!!class> object.
//
// A <!id>Particle<!!id> object contains pointers to other particles,
// such as a list of parents and a list of children. It may also
// contain a pointer to the previous or next instance of the same
// physical particle if the properties of a given particle has been
// changed during the generation. Coloured particles contains pointers
// to colour-neighbors, and pointers to the parents and children which
// carries the same (anti-) colour. Note that also colour-neutral
// particles may have pointers to colour neghbours, the meaning of
// these is in this case model dependent.
//
// The particle also has a pointer to the <!class>Step<!!class> object
// where it was first introduced in the <!class>Event<!!class>.
//
// When printing a particle the format of the output is governed by
// the static <!id>outputFormat<!!id> string. When a particle is sent
// to an <!id>ostream<!!id>, the format string is written but with
// keys prefixed by the <!id>%<!!id> character replaced with
// infromation about the particle as follows:<BR> <!id>%%<!!id> is
// replaced by a singel <!id>%<!!id><BR> <!id>%C<!!id> sets a flag so
// that subsequent output of children and parents etc. will contain
// colour information.<BR> <!id>%n<!!id> is replaced by the particles
// number in a fied ow width<BR> <!id>%s<!!id> is replaced by the name
// of the particle<BR> <!id>%i<!!id> is replaced by the id number of
// the particle type<BR><!id>%x, %y, %z, %e, %m<!!id> is replaced by
// the x-, y-, z-, energy- and mass-component of the particles
// momentum respectively<BR><!id>%dx, %dy, %dz, %dt, %dT<!!id> is
// replaced by the x-, y-, z-, time- and invariant time-component of
// the particles lifeLength respectively<BR><!id>%Vx, %Vy, %Vz,
// %Vt<!!id> is replaced by the x-, y-, z- and time-component of the
// creation point relative to the vertex of the
// collision.<BR><!id>%Lx, %Ly, %Lz, %Lt<!!id> is replaced by the x-,
// y-, z- and time-component of the creation point in the current
// lab-system.<BR> <!id>%p[,]<!!id> is replaced by a list (of numbers)
// of the particles parents enclosed by <!id>[<!!id> and <!id>]<!!id>
// and separated by <!id>,<!!id>, The parent from which the particle
// inherits its (anti-) colour is marked by a (-)+<BR>
// <!id>%c(,)<!!id> is replaced by a list (of numbers) of the
// particles children enclosed by <!id>(<!!id> and <!id>)<!!id> and
// separated by <!id>,<!!id>, The child which inherits the particles
// (anti-) colour is marked by a (-)+<BR> <!id>%&gt;<!!id> is replaced
// by the number of the colour neighbor<BR> <!id>%&lt;<!!id> is
// replaced by the number of the anti-colour neighbor<BR>
// <!id>%^<!!id> is replaced by the number of the previous instance of
// the same physical particle<BR> <!id>%v<!!id> is replaced by the
// number of the next instance of the same physical particle.<BR>
// <!id>%l{,}<!!id> is replaced by the indices of the colour lines to
// which this particle is connected enclosed by <!id>{<!!id> and
// <!id>}<!!id> and separated by <!id>,<!!id>, The line corresponding
// to the (anti-) colour of the particle is prefixed by a (-)+
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Event.html">Event.h</a>
// <a href="http:Collision.html">Collision.h</a>
// <a href="http:Step.html">Step.h</a>
// <a href="http:SubProcess.html">SubProcess.h</a>
// <a href="http:Lorentz5Vector.html">Lorentz5Vector.h</a>
// <a href="http:ColourLine.html">ColourLine.h</a>
// <a href="http:ColourBase.html">ColourBase.h</a>
// 

#include "EventConfig.h"
#include "ThePEG/CLHEPWrap/Lorentz5Vector.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/FixedSizeAllocator.h"
#include "ThePEG/EventRecord/ColourBase.h"
#include "ThePEG/EventRecord/SpinBase.h"

namespace ThePEG {

class Particle: public EventRecordBase {

public:

  friend class Event;
  friend class Collision;
  friend class Step;
  friend class SubProcess;
  friend class ParticleData;
  struct ParticleRep;

public:

  inline void * operator new(size_t);
  inline void operator delete(void *, size_t);

public:

  inline Particle(tcEventPDPtr);
  Particle(const Particle &);
  // Standard Constructors. Note that the default constructor is
  // private - there is no particle without a pointer to a particle
  // data object.

  inline ~Particle();
  // Destructor.

  inline bool decayed() const;
  // Returns true if and only if this particle has decayed.

  inline const ParticleVector & children() const;
  // The list of decay products.

  inline void addChild(tPPtr);
  // Add a child (the childs parent pointer will be set accordingly).

  inline void abandonChild(tPPtr);
  // Remove the given child from the list of children of this particle
  // (the corresponding parent pointer of the child will also be
  // removed).

  inline const tParticleVector & parents() const;
  // The list of parent particles.

  tParticleSet siblings() const;
  // Return a set of neighboring particles coming from the same decay
  // as this one.

  inline void undecay();
  // Undo the decay of this particle, removing all children (and
  // grand children ...) from the event record

  inline void decayMode(tDMPtr);
  inline tDMPtr decayMode() const;
  // If this particle has decayed set/get the corresponding decay
  // mode.

  inline tPPtr next() const;
  inline tPPtr previous() const;
  // Pointer to another instance of the same physical particle in
  // later and earlier steps.

  inline tcPPtr original() const;
  inline tPPtr original();
  inline tcPPtr final() const;
  inline tPPtr final();
  // If there exists another previous/subsequent instance of this
  // particle return this instance (recursively).

  inline tStepPtr birthStep() const;
  // Get the first Step object where this particle occurred.

  inline int number() const;
  // Get the order-number for this particle in the current event.

  inline const ParticleDataClass & data() const;
  inline tcEventPDPtr dataPtr() const;
  // Access the ParticleData object of this particle type

  inline string PDGName() const;
  inline long id() const;
  // Return the PDG name and id number of this particle.

  inline const Lorentz5Momentum & momentum() const;
  // Return the momentum of this particle.

  inline void set3Momentum(const Momentum3 &);
  // Set the 3-momentum of this particle. The energy is set to be
  // consistent with the mass.

  inline void setMomentum(const LorentzMomentum &);
  // Set the momentum of this particle. Afterwards, the underlying
  // Lorentz5Momentum may have inconsistent mass.

  inline void set5Momentum(const Lorentz5Momentum &);
  // Set the momentum and mass.

  inline Energy mass() const;
  inline Energy nominalMass() const;
  // Acces the mass of this particle (type).

  inline Energy2 scale() const;
  inline void scale(Energy2);
  // Get/Set the scale at which this particle is considered resolved.

  inline const LorentzPoint & vertex() const;
  LorentzPoint labVertex() const;
  inline LorentzPoint decayVertex() const;
  inline LorentzPoint labDecayVertex() const;
  inline const Lorentz5Distance & lifeLength() const;
  // Access the creation and decay vertices of this particle.

  inline void setVertex(const LorentzPoint &);
  void setLabVertex(const LorentzPoint &);
  inline void setLifeLength(const Distance &);
  inline void setLifeLength(const LorentzDistance &);
  inline void setLifeLength(const Lorentz5Distance &);
  // Set the creation and decay vertices of this particle. Setting the
  // lifeLength with a 3-distance will automatically rescale the time
  // to be consistent with the invariant distance. When specifying a
  // LorentzDistance, the invariant distance may become inconsistent.

  inline Time lifeTime() const;
  // The life time of this particle.

  void transform(const LorentzRotation & r);
  inline void boost(double bx, double by, double bz);
  inline void boost(const Vector3 & p);
  void rotateX(double a);
  void rotateY(double a);
  void rotateZ(double a);
  void rotate(double a, const Vector3 & axis);
  inline void mirror();
  // Do Lorentz transformations on this particle

  void deepTransform(const LorentzRotation & r);
  inline void deepBoost(double bx, double by, double bz);
  inline void deepBoost(const Vector3 & p);
  void deepRotateX(double a);
  void deepRotateY(double a);
  void deepRotateZ(double a);
  void deepRotate(double a, const Vector3 & axis);
  // Do Lorentz transformations on this particle and its decay products.

  inline Energy massError() const;
  inline Energy energyError() const;
  inline Energy rhoError() const;
  inline void rescaleEnergy();
  inline void rescaleRho();
  inline void rescaleMass();
  // The 5-momentum may be internally inconsistent, but can be made
  // consistent by rescaling any of the components.

  inline Energy2 mt2() const;
  inline Energy mt() const;
  // Return the transverse mass (squared), calculated from the energy
  // and the longitudinal momentum.

  inline Energy2 perpmass2() const;
  inline Energy perpmass() const;
  // Return the transverse mass (squared), calculated from the mass
  // and the transverse momentum.

  inline double rapidity() const;
  inline double eta() const;
  // Return the (preudo) rapidity.

  inline Energy Pplus() const;
  inline Energy Pminus() const;
  // Return the positive and negative light-cone momenta.

  inline bool hasColourInfo() const;
  // True if this particle has colour information. To determine if
  // this particle is actually coloured, the colored(), hasColour() or
  // hasAntiColour() methods should be used instead.

  inline tColinePtr antiColourLine() const;
  inline tColinePtr colourLine(bool anti = false) const;
  // Return the colour lines to which this particle is connected.

  inline bool coloured() const;
  inline bool hasColour(bool anti = false) const;
  inline bool hasAntiColour() const;
  // Query the undelying ParticleData object about the colour quantum
  // numbers of this particle.

  inline tcCBPtr colourInfo() const;
  inline tCBPtr colourInfo();
  inline void colourInfo(tCBPtr);
  // Set/get the colour information object.

  tPPtr colourNeighbour(bool anti = false) const;
  inline tPPtr antiColourNeighbour() const;
  void colourNeighbour(tPPtr, bool anti = false);
  inline void antiColourNeighbour(tPPtr);
  // Set/access colour connected particles. A particle set as (anti)
  // neighbour is assumed not to be connected to a (anti) colour line
  // The returned colour neighbour returned is one found in the Step
  // where this was created.

  inline void antiColourConnect(tPPtr neighbour);
  inline void colourConnect(tPPtr neighbour, bool anti = false);
  // make neighbour the (anti) colour neighbour of this. The neighbour
  // is also set accordingly.

  tPPtr incomingColour(bool anti = false) const;
  inline tPPtr incomingAntiColour() const;
  inline void incomingColour(tPPtr, bool anti = false);
  inline void incomingAntiColour(tPPtr);
  // Set/access parents from which this has gotten its colour charge.

  tPPtr outgoingColour(bool anti = false) const;
  inline tPPtr outgoingAntiColour() const;
  void outgoingColour(tPPtr, bool anti = false);
  inline void outgoingAntiColour(tPPtr);
  // Set/access children to which this has given its colour charge.

  inline void colourFlow(tPPtr child, bool anti = false);
  inline void antiColourFlow(tPPtr child);
  // Specify that the (anti) colour flows to the given child. The
  // childs incoming colourflow is also set up.

  inline void resetColour();
  // Remove all colour information;

  inline tcSpinPtr spinInfo() const;
  inline tSpinPtr spinInfo();
  inline void spinInfo(tSpinPtr s);
  // Set/access spin information

  inline const EIVector & getInfo() const;
  inline EIVector & getInfo();
  // Access user-defined information.

  void initFull() const;
  // If this particle has only a type and momentum, instantiate the
  // rest of the information.

public:

  static string outputFormat;
  // Specify how to print particles. The format string is analogous to
  // the one used by eg. the unix 'date' command as described above/

  template <typename Iterator>
  static void PrintParticles(ostream & os, Iterator first, Iterator last);
  template <typename Cont>
  inline static void PrintParticles(ostream & os, const Cont &);
  // Print a number of particles.
   
public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // The Init() method is run automatically once for each class.

public:

  inline bool hasRep() const;
  // True if this particle has instantiated the object with
  // information other than type and momentum.

private:

  virtual PPtr clone() const;
  virtual void rebind(const EventTranslationMap &);
  // Used when a whole event record is cloned.

  inline void number(int);
  // Set the order-number for this particle in the current event.

  inline void removeChild(tPPtr);
  inline void removeParent(tPPtr);

  inline void mass(Energy);
  // Set the mass of this particle.

  inline void lifeTime(Length);
  // Set the lifeTime of this particle.

  inline ParticleRep & rep();
  inline const ParticleRep & rep() const;
  // Return a reference to the bulk information of this particle. if
  // no ParticleRep object exists, one is created.

  cEventPDPtr theData;
  // The pointer to the ParticleData object

  Lorentz5Momentum theMomentum;
  // The momentum.

  mutable ParticleRep * theRep;
  // The rest of the information in this particle is only instantiated
  // if needed.

public:

  struct ParticleRep {

    inline void * operator new(size_t);
    inline void operator delete(void *, size_t);

    ParticleRep();
    ParticleRep(const ParticleRep &);

    tParticleVector theParents;
    ParticleVector theChildren;
    tPPtr thePrevious;
    PPtr theNext;
    // The pointers to parents and stuff/

    tDMPtr theDecayMode;
    // If this particle has decayed this is the pointer to the
    // corresponding decay mode.

    tStepPtr theBirthStep;
    // The pointer to the first step where this particles occurred.

    LorentzPoint theVertex;
    Lorentz5Distance theLifeLength;
    // The creation point and trajectory.

    Energy2 theScale;
    // the resolution scale.

    int theNumber;
    // The order-number for this particle in the current event.

    CBPtr theColourInfo;
    // A pointer to the colour information object.

    SpinPtr theSpinInfo;
    // Spin information

    EIVector theExtraInfo;
    // Additional used-defined information.

  };

private:

  inline Particle();
  friend class ClassTraits<Particle>;
  // Private default constructor must only be used by the
  // PersistentIStream class via the ClassTraits<Particle> class .

  Particle & operator=(const Particle &);
  // Private and non-existent assignment.

  static ClassDescription<Particle> initParticle;

};

ostream & operator<<(ostream &, const Particle &);
// Write a Particle object to a stream.

// CLASSDOC OFF

template <>
struct BaseClassTrait<Particle,1> {
  typedef EventRecordBase NthBase;
};

template <>
struct ClassTraits<Particle>: public ClassTraitsBase<Particle> {
  static string className() { return "/ThePEG/Particle"; }
  static TPtr create() { return TPtr::Create(Particle()); }
};

}

#include "Particle.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Particle.tcc"
#endif

#endif /* ThePEG_Particle_H */
