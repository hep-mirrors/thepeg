// -*- C++ -*-
#ifndef ThePEG_Particle_H
#define ThePEG_Particle_H
// This is the decalaration of the Particle class.

#include "EventConfig.h"
#include "ThePEG/CLHEPWrap/Lorentz5Vector.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/FixedSizeAllocator.h"
#include "ThePEG/EventRecord/ColourBase.h"
#include "ThePEG/EventRecord/SpinBase.h"

namespace ThePEG {

/**
 * The Particle class is used to describe an instance of a
 * particle. Properties of the corresponding particle type can be
 * accessed through a pointer to a ParticleData object.
 *
 * A Particle object contains pointers to other particles, such as a
 * list of parents and a list of children. It may also contain a
 * pointer to the previous or next instance of the same physical
 * particle if the properties of a given particle has been changed
 * during the generation. Coloured particles contains pointers to
 * ColourLine defining the colour connections to other particles.
 *
 * The Particle also has a pointer to the Step object where it was
 * first introduced in the Event.
 *
 * When printing a particle the format of the output is governed by
 * the static <code>outputFormat</code> string. When a particle is sent
 * to an <code>ostream</code>, the format string is written but with
 * keys prefixed by the <code>\%</code> character replaced with
 * infromation about the particle as follows:<BR> <code>\%\%</code> is
 * replaced by a singel <code>\%</code><BR> <code>\%C</code> sets a flag so
 * that subsequent output of children and parents etc. will contain
 * colour information.<BR> <code>\%n</code> is replaced by the particles
 * number in a fied ow width<BR> <code>\%s</code> is replaced by the name
 * of the particle<BR> <code>\%i</code> is replaced by the id number of
 * the particle type<BR><code>\%x, \%y, \%z, \%e, \%m</code> is replaced by
 * the x-, y-, z-, energy- and mass-component of the particles
 * momentum respectively<BR><code>\%dx, \%dy, \%dz, \%dt, \%dT</code> is
 * replaced by the x-, y-, z-, time- and invariant time-component of
 * the particles lifeLength respectively<BR><code>\%Vx, \%Vy, \%Vz,
 * \%Vt</code> is replaced by the x-, y-, z- and time-component of the
 * creation point relative to the vertex of the
 * collision.<BR><code>\%Lx, \%Ly, \%Lz, \%Lt</code> is replaced by the x-,
 * y-, z- and time-component of the creation point in the current
 * lab-system.<BR> <code>\%p[,]</code> is replaced by a list (of numbers)
 * of the particles parents enclosed by <code>[</code> and <code>]</code>
 * and separated by <code>,</code>, The parent from which the particle
 * inherits its (anti-) colour is marked by a (-)+<BR>
 * <code>\%c(,)</code> is replaced by a list (of numbers) of the
 * particles children enclosed by <code>(</code> and <code>)</code> and
 * separated by <code>,</code>, The child which inherits the particles
 * (anti-) colour is marked by a (-)+<BR> <code>\%&gt;</code> is replaced
 * by the number of the colour neighbor<BR> <code>\%&lt;</code> is
 * replaced by the number of the anti-colour neighbor<BR>
 * <code>\%^</code> is replaced by the number of the previous instance of
 * the same physical particle<BR> <code>\%v</code> is replaced by the
 * number of the next instance of the same physical particle.<BR>
 * <code>\%l{,}</code> is replaced by the indices of the colour lines to
 * which this particle is connected enclosed by <code>{</code> and
 * <code>}</code> and separated by <code>,</code>, The line corresponding
 * to the (anti-) colour of the particle is prefixed by a (-)+
 *
 * @see Event
 * @see Collision
 * @see Step
 * @see SubProcess
 * @see Lorentz5Vector
 * @see ColourLine
 * @see ColourBase 
 */
class Particle: public EventRecordBase {

public:

  /** Most of the Event classes are friends with each other. */
  friend class Event;
  /** Most of the Event classes are friends with each other. */
  friend class Collision;
  /** Most of the Event classes are friends with each other. */
  friend class Step;
  /** Most of the Event classes are friends with each other. */
  friend class SubProcess;
  /** ParticleData needs to be a friend. */
  friend class ParticleData;

  struct ParticleRep;

public:

  /** @name Construction and descruction functions. */
  //@{
  /**
   * Particle uses the FixedSizeAllocator for (de)allocation.
   */
  inline void * operator new(size_t);
 
  /**
   * Particle uses the FixedSizeAllocator for (de)allocation.
   */
 inline void operator delete(void *, size_t);

public:

  /**
   * Standard Constructor. Note that the default constructor is
   * private - there is no particle without a pointer to a
   * ParticleData object.
   */
  inline Particle(tcEventPDPtr);

  /**
   * Copy constructor.
   */
  Particle(const Particle &);

  /**
   * Destructor.
   */
  inline ~Particle();
  //@}

  /** @name Functions relating to ancestry of particles. */
  //@{
  /**
   * Returns true if and only if this particle has decayed.
   */
  inline bool decayed() const;

  /**
   * The list of decay products.
   */
  inline const ParticleVector & children() const;

  /**
   * Add a child (the childs parent pointer will be set accordingly).
   */
  inline void addChild(tPPtr);

  /**
   * Remove the given child from the list of children of this particle
   * (the corresponding parent pointer of the child will also be
   * removed).
   */
  inline void abandonChild(tPPtr);

  /**
   * The list of parent particles.
   */
  inline const tParticleVector & parents() const;

  /**
   * Return a set of neighboring particles coming from the same decay
   * as this one.
   */
  tParticleSet siblings() const;

  /**
   * Undo the decay of this particle, removing all children (and
   * grand children ...) from the event record
   */
  inline void undecay();

  /**
   * If this particle has decayed set the corresponding decay mode.
   */
  inline void decayMode(tDMPtr);

  /**
   * If this particle has decayed get the corresponding decay mode.
   */
  inline tDMPtr decayMode() const;

  /**
   * Next instance. Pointer to another instance of the same
   * physical particle in later steps.
   */
  inline tPPtr next() const;

  /**
   * Previous instance. Pointer to another instance of the same
   * physical particle in earlier steps.
   */
  inline tPPtr previous() const;

  /**
   * Original instance. If there exists another previous instance of
   * this particle return this instance (recursively).
   */
  inline tcPPtr original() const;

  /**
   * Original instance. If there exists another previous instance of
   * this particle return this instance (recursively).
   */
  inline tPPtr original();
  /**
   * Final instance. If there exists another subsequent instance of
   * this particle return this instance (recursively).
   */
  inline tcPPtr final() const;

  /**
   * Final instance. If there exists another subsequent instance of
   * this particle return this instance (recursively).
   */
  inline tPPtr final();

  //@}

  /** @name Relations to the Event and Step. */
  //@{
  /**
   * Get the first Step object where this particle occurred.
   */
  inline tStepPtr birthStep() const;

  /**
   * Get the order-number for this particle in the current event.
   */
  inline int number() const;
  //@}

  /** @name Access the underlying ParticleData object. */
  //@{
  /**
   * Access the ParticleData object of this particle type
   */
  inline const ParticleDataClass & data() const;

  /**
   * Access the ParticleData object of this particle type
   */
  inline tcEventPDPtr dataPtr() const;

  /**
   * Return the PDG name of this particle.
   */
  inline string PDGName() const;

  /**
   * Return the PDG id number of this particle.
   */
  inline long id() const;
  //@}

  /** @name Functions to access the momentum. */
  //@{
  /**
   * Return the momentum of this particle.
   */
  inline const Lorentz5Momentum & momentum() const;

  /**
   * Set the 3-momentum of this particle. The energy is set to be
   * consistent with the mass.
   */
  inline void set3Momentum(const Momentum3 &);

  /**
   * Set the momentum of this particle. Afterwards, the underlying
   * Lorentz5Momentum may have inconsistent mass.
   */
  inline void setMomentum(const LorentzMomentum &);

  /**
   * Set the momentum and mass.
   */
  inline void set5Momentum(const Lorentz5Momentum &);

  /**
   * Acces the mass of this particle.
   */
  inline Energy mass() const;

  /**
   * Acces the mass of this particle type.
   */
  inline Energy nominalMass() const;

  /**
   * Get the scale at which this particle is considered resolved.
   */
  inline Energy2 scale() const;

  /**
   * Set the scale at which this particle is considered resolved.
   */
  inline void scale(Energy2);

  /**
   * Return the transverse mass (squared), calculated from the energy
   * and the longitudinal momentum.
   */
  inline Energy2 mt2() const;
  /**
   * Return the transverse mass (squared), calculated from the energy
   * and the longitudinal momentum.
   */
  inline Energy mt() const;

  /**
   * Return the transverse mass (squared), calculated from the mass
   * and the transverse momentum.
   */
  inline Energy2 perpmass2() const;
  /**
   * Return the transverse mass (squared), calculated from the mass
   * and the transverse momentum.
   */
  inline Energy perpmass() const;

  /**
   * Return the (preudo) rapidity.
   */
  inline double rapidity() const;
  /**
   * Return the (preudo) rapidity.
   */
  inline double eta() const;

  /**
   * Return the positive and negative light-cone momenta.
   */
  inline Energy Pplus() const;
  /**
   * Return the positive and negative light-cone momenta.
   */
  inline Energy Pminus() const;

  //@}

  /** @name Functions to access the position. */
  //@{
  /**
   * The creation vertex of this particle. The point is given
   * relative to the collision vertex.
   */
  inline const LorentzPoint & vertex() const;

  /**
   * The creation vertex of this particle. The absolute
   * position in the lab is given.
   */
  LorentzPoint labVertex() const;

  /**
   * The decay vertex of this particle. The point is given
   * relative to the collision vertex.
   */
  inline LorentzPoint decayVertex() const;

  /**
   * The decay vertex of this particle. The absolute
   * position in the lab is given.
   */
  inline LorentzPoint labDecayVertex() const;

  /**
   * The life time/length. Return the Lorentz vector connecting the
   * creation to the decay vertes.
   */
  inline const Lorentz5Distance & lifeLength() const;

  /**
   * Set the creation vertex relative to the collision vertex.
   */
  inline void setVertex(const LorentzPoint &);

  /**
   * Set the creation vertex in the lab frame of this particle.
   */
  void setLabVertex(const LorentzPoint &);

  /**
   * Set the life length of this particle. The life time will be
   * automatically rescaled to be consistent with the invariant
   * distance.
   */
  inline void setLifeLength(const Distance &);

  /**
   * Set the life time/length of a particle. The invariant distance
   * may become inconsistent.
   */
  inline void setLifeLength(const LorentzDistance &);

  /**
   * Set the life time/length of a particle.
   */
  inline void setLifeLength(const Lorentz5Distance &);

  /**
   * The invariant life time of this particle.
   */
  inline Time lifeTime() const;

  //@}

  /** @name Functions for (Lorentz) transformations. */
  //@{
  /**
   * Do Lorentz transformations on this particle.
   */
  void transform(const LorentzRotation & r);

  /**
   * Do Lorentz transformations on this particle. \a bx, \a by and \a
   * bz are the boost vector components.
   */
  inline void boost(double bx, double by, double bz);

  /**
   * Do Lorentz transformations on this particle. \a b is the boost
   * vector.
   */
  inline void boost(const Vector3 & b);

  /**
   * Rotate around the x-axis.
   */
  void rotateX(double a);

  /**
   * Rotate around the y-axis.
   */
  void rotateY(double a);

  /**
   * Rotate around the z-axis.
   */
  void rotateZ(double a);

  /**
   * Rotate around the given \a axis.
   */
  void rotate(double a, const Vector3 & axis);

  /**
   * Mirror in the xy-plane.
   */
  inline void mirror();

  /**
   * Do Lorentz transformations on this particle and its decendants.
   */
  void deepTransform(const LorentzRotation & r);

  /**
   * Do Lorentz transformations on this particle and its
   * decendants. \a bx, \a by and \a bz are the boost vector
   * components.
   */
  inline void deepBoost(double bx, double by, double bz);

  /**
   * Do Lorentz transformations on this particle and its
   * decendants. \a b is the boost vector.
   */
  inline void deepBoost(const Vector3 & b);

  /**
   * Rotate this particle and its decendants around the x-axis.
   */
  void deepRotateX(double a);

  /**
   * Rotate this particle and its decendants around the y-axis.
   */
  void deepRotateY(double a);

  /**
   * Rotate this particle and its decendants around the z-axis.
   */
  void deepRotateZ(double a);

  /**
   * Rotate this particle and its decendants around the given \a axis.
   */
  void deepRotate(double a, const Vector3 & axis);

  //@}

  /** @name Functions controlling possible mass/momentum inconsistencies. */
  //@{
  /**
   * Return the relative inconsistency in the mass component.
   */
  inline Energy massError() const;

  /**
   * Return the relative inconsistency in the energy component.
   */
  inline Energy energyError() const;

  /**
   * Return the relative inconsistency in the spatial components.
   */
  inline Energy rhoError() const;

  /**
   * Rescale energy, so that the invariant length/mass of the
   * LorentzVector agrees with the current one.
   */
  inline void rescaleEnergy();

  /**
   * Rescale spatial component, so that the invariant length/mass of
   * the LorentzVector agrees with the current one.
   */
  inline void rescaleRho();

  /**
   * Set the invariant length/mass member, so that it agrees with the
   * invariant length/mass of the LorentzVector.
   */
  inline void rescaleMass();

  //@}

  /** @name Acces incormation about colour connections */
  //@{
  /**
   * True if this particle has colour information. To determine if
   * this particle is actually coloured, the colored(), hasColour() or
   * hasAntiColour() methods should be used instead.
   */
  inline bool hasColourInfo() const;

  /**
   * Return the colour lines to which this particles anti-colour is
   * connected.
   */
  inline tColinePtr antiColourLine() const;

  /**
   * Return the colour lines to which this particles (\a anti-)colour
   * is connected.
   */
  inline tColinePtr colourLine(bool anti = false) const;

  /**
   * True if this particle type is not a colour singlet.
   */
  inline bool coloured() const;

  /**
   * True if this particle type carries (\a anti-)colour.
   */
  inline bool hasColour(bool anti = false) const;

  /**
   * True if this particle type carries anti-colour.
   */
  inline bool hasAntiColour() const;

  /**
   * Get the ColourBase object.
   */
  inline tcCBPtr colourInfo() const;

  /**
   * Get the ColourBase object.
   */
  inline tCBPtr colourInfo();

  /**
   * Set the ColourBase object.
   */
  inline void colourInfo(tCBPtr);

  /**
   * Get a pointer to the colour neighbor. Returns a particle in the
   * Step where this particle was created which anti-colour is
   * connected to the same line as this particles colour. If \a anti
   * is true return antiColourNeighbour().
   */
  tPPtr colourNeighbour(bool anti = false) const;

  /**
   * Get a pointer to the anti-colour neighbor. Returns a particle in
   * the Step where this particle was created which colour is
   * connected to the same line as this particles anti-colour.
   */
  inline tPPtr antiColourNeighbour() const;

  /**
   * Set the colour neighbor. Connects the given particles anti-colour
   * to the same colour line as this particles colour. If \a anti
   * is true call antiColourNeighbour(tPPtr).
   */
  void colourNeighbour(tPPtr, bool anti = false);

  /**
   * Set the anti-colour neighbor. Connects the given particles colour
   * to the same colour line as this particles anti-colour.
   */
  inline void antiColourNeighbour(tPPtr);

  /**
   * Connect colour. Create a colour line connecting to it this
   * particles anti-colour and the given particles colour.
   */
  inline void antiColourConnect(tPPtr neighbour);

  /**
   * Connect colour. Create a colour line connecting to it this
   * particles colour and the given particles anti-colour. If \a anti
   * is true call antiColourConnect(tPPtr).
   */
  inline void colourConnect(tPPtr neighbour, bool anti = false);

  /**
   * Incoming colour. Return the parent particle which colour is
   * connected to the same colour line as this particle. If \a anti is
   * true return incomingAntiColour().
   */
  tPPtr incomingColour(bool anti = false) const;

  /**
   * Incoming anti-colour. Return the parent particle which
   * anti-colour is connected to the same colour line as this
   * particle.
   */
  inline tPPtr incomingAntiColour() const;

  /**
   * Set incoming colour. Connect this particles colour to the same
   * colour line as the given particle. If \a anti
   * is true call incomingAntiColour(tPPtr).
   */
  inline void incomingColour(tPPtr, bool anti = false);

  /**
   * Set incoming anti-colour. Connect this particles anti colour to
   * the same colour line as the given particle.
   */
  inline void incomingAntiColour(tPPtr);

  /**
   * Outgoing colour. Return the daughter particle which colour is
   * connected to the same colour line as this particle. If \a anti is
   * true return outgoingAntiColour().
   */
  tPPtr outgoingColour(bool anti = false) const;
  /**
   * Outgoing anti-colour. Return the daughter particle which
   * anti-colour is connected to the same colour line as this
   * particle.
   */
  inline tPPtr outgoingAntiColour() const;

  /**
   * Set outgoing colour. Connect this particles colour to the same
   * colour line as the given particle. If \a anti
   * is true call outgoingAntiColour(tPPtr).
   */
  void outgoingColour(tPPtr, bool anti = false);

  /**
   * Set outgoing anti-colour. Connect this particles anti-colour to
   * the same colour line as the given particle.
   */
  inline void outgoingAntiColour(tPPtr);

  /**
   * Specify colour flow. Calls outgoingColour(tPPtr,bool).
   */
  inline void colourFlow(tPPtr child, bool anti = false);
  /**
   * Specify anticolour flow. Calls outgoingAntiColour(tPPtr,bool).
   */
  inline void antiColourFlow(tPPtr child);

  /**
   * Remove all colour information;
   */
  inline void resetColour();

  //@}

  /** @name Functions to access spin. */
  //@{
  /**
   * Return the Spin object.
   */
  inline tcSpinPtr spinInfo() const;

  /**
   * Return the Spin object.
   */
  inline tSpinPtr spinInfo();

  /**
   * Set the Spin object.
   */
  inline void spinInfo(tSpinPtr s);
  //@}

  /** @name Accessing user-defined information. */
  //@{
  /**
   * Access user-defined information as a vector of EventInfoBase pointers.
   */
  inline const EIVector & getInfo() const;
  /**
   * Access user-defined information as a vector of EventInfoBase pointers.
   */
  inline EIVector & getInfo();
 
 //@}

public:

  /** @name Accessing user-defined information. */
  //@{
  /**
   * True if this particle has instantiated the object with
   * information other than type and momentum.
   */
  inline bool hasRep() const;

  /**
   * If this particle has only a type and momentum, instantiate the
   * rest of the information.
   */
  void initFull() const;

  //@}

public:

  /** @name Input and output functions. */
  //@{
  /**
   * Standard function for writing to a persistent stream.
   */
  void persistentOutput(PersistentOStream &) const;

  /**
   * Standard function for reading from a persistent stream.
   */
  void persistentInput(PersistentIStream &, int);

  //@}

  /**
   * Print a range of particles.
   */
  template <typename Iterator>
  static void PrintParticles(ostream & os, Iterator first, Iterator last);

  /**
   * Print a container of particles.
   */
  template <typename Cont>
  inline static void PrintParticles(ostream & os, const Cont &);
   
  /**
   * Standard Init function. @see Base::Init().
   */
  static void Init();

  /**
   * Specify how to print particles. The format string is analogous to
   * the one used by eg. the unix 'date' command as described above.
   */
  static string outputFormat;

private:

  /**
   * Standard clone function.
   */
  virtual PPtr clone() const;

  /**
   * Rebind to cloned objects. When an Event is cloned, a shallow
   * copy is done first, then all <code>Particle</code>s etc, are
   * cloned, and finally this method is used to see to that the
   * pointers in the cloned Particle points to the cloned objects.
   */
  virtual void rebind(const EventTranslationMap &);

  /**
   * Set the order-number for this particle in the current event.
   */
  inline void number(int);

  /**
   * Remove the given particle from the list of children.
   */
  inline void removeChild(tPPtr);

  /**
   * Remove the given particle from the list of parents.
   */
  inline void removeParent(tPPtr);

  /**
   * Set the mass of this particle.
   */
  inline void mass(Energy);

  /**
   * Set the invaiant life time of this particle.
   */
  inline void lifeTime(Length);

  /**
   * Return a reference to the bulk information of this particle. if
   * no ParticleRep object exists, one is created.
   */
  inline ParticleRep & rep();

  /**
   * Return a reference to the bulk information of this particle. if
   * no ParticleRep object exists, one is created.
   */
  inline const ParticleRep & rep() const;

  /**
   * The pointer to the ParticleData object
   */
  cEventPDPtr theData;

  /**
   * The momentum.
   */
  Lorentz5Momentum theMomentum;

  /**
   * The rest of the information in this particle is only instantiated
   * if needed.
   */
  mutable ParticleRep * theRep;

public:

  /**
   * This class is used internally in the Particle class to represent
   * information besides momentum and type. A corresponding object
   * will only be instantiated if needed to save memory and time when
   * temporarily creating particles.
   */
  struct ParticleRep {

    /**
     * ParticleRep uses the FixedSizeAllocator for (de)allocation.
     */
    inline void * operator new(size_t);
 
    /**
     * ParticleRep uses the FixedSizeAllocator for (de)allocation.
     */
    inline void operator delete(void *, size_t);

    /**
     * Default constructor.
     */
    ParticleRep();

    /**
     * Copy constructor.
     */
    ParticleRep(const ParticleRep &);

    /**
     * The pointers to the parents.
     */
    tParticleVector theParents;

    /**
     * The pointers to the children.
     */
    ParticleVector theChildren;

    /**
     * The pointer to the previous instance.
     */
    tPPtr thePrevious;

    /**
     * The pointer to the next instance.
     */
    PPtr theNext;

    /**
     * If this particle has decayed this is the pointer to the
     * corresponding decay mode.
     */
    tDMPtr theDecayMode;

    /**
     * The pointer to the first step where this particle occurred.
     */
    tStepPtr theBirthStep;

    /**
     * The creation point.
     */
    LorentzPoint theVertex;

    /**
     * The life time/length.
     */
    Lorentz5Distance theLifeLength;

    /**
     * the resolution scale.
     */
    Energy2 theScale;

    /**
     * The order-number for this particle in the current event.
     */
    int theNumber;

    /**
     * A pointer to the colour information object.
     */
    CBPtr theColourInfo;

    /**
     * Spin information
     */
    SpinPtr theSpinInfo;

    /**
     * Additional used-defined information.
     */
    EIVector theExtraInfo;

  };

private:

  /**
   * Private default constructor must only be used by the
   * PersistentIStream class via the ClassTraits<Particle> class.
   */
  inline Particle();

  /**
   * The ClassTraits<Particle> class must be a friend to be able to
   * use the private default constructor.
   */
  friend class ClassTraits<Particle>;

  /**
   * Private and non-existent assignment.
   */
  Particle & operator=(const Particle &);

  /**
   * Describe concrete class with persistent data.
   */
  static ClassDescription<Particle> initParticle;

};

/**
 * Write a Particle object to a stream.
 */
ostream & operator<<(ostream &, const Particle &);


/** This template specialization informs ThePEG about the
 *  base class of Particle. */
template <>
struct BaseClassTrait<Particle,1> {
  /** Typedef of the first base class of Collision. */
  typedef EventRecordBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the Particle class and how to create it. */
template <>
struct ClassTraits<Particle>: public ClassTraitsBase<Particle> {
  /** Return a platform-independent class name */
  static string className() { return "/ThePEG/Particle"; }
  /** Create a Event object. */
  static TPtr create() { return TPtr::Create(Particle()); }
};

}

#include "Particle.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Particle.tcc"
#endif

#endif /* ThePEG_Particle_H */
