// -*- C++ -*-
#ifndef ThePEG_ColourLine_H
#define ThePEG_ColourLine_H
// This is the declaration of the ColourLine class.

#include "EventConfig.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/EventRecord/ColourSinglet.h"

// #include "ColourLine.fh"
// #include "ColourLine.xh"

namespace ThePEG {

/**
 * The ColourLine class represents colour lines connecting
 * <code>Particle</code>s. A <code>ColourLine</code> keeps track on
 * the particles connected to it. To connect a particle to a colour
 * line the <code>addColoured()</code> and
 * <code>addAntiColoured()</code> functions should be used - these
 * will automatically set up the Particle correctly. There is no
 * method in a Particle to directly set its colour lines.
 *
 * If a colour line stems from a colour source or ends in a colour
 * sink, it is possible to obtain the neighbouring colour lines. This
 * is also the way junction strings and sinks and sources are
 * implemented.
 *
 * @see Particle
 * @see ColourBase
 */
class ColourLine: public EventRecordBase {

public:

  /** @name Creation functions. */
  //@{
  /**
   * Default Constructor.
   */
  inline ColourLine();

  /**
   * Copy constructor.
   */
  inline ColourLine(const ColourLine &);

  /**
   * Create a colour line. Set a pair of colour - anticolour particles
   * in a newly created colour line.
   */
  static tColinePtr create(tPPtr col, tPPtr anti);

  /**
   * Create a colour line. Set a particle for which the created object
   * is a (anti-)colour line .
   * @param p the particle to be connected.
   * @param anti if true, the created object is the anti-colour line
   * of \a p.
   */
  static tColinePtr create(tPPtr p, bool anti = false);

  /**
   * Create a colour line. Set a particle for which the created object
   * is a anti-colour line .
   * @param p the particle to be connected.
   */
  static inline tColinePtr createAnti(tPPtr p);

  //@}

  /**
   * Destructor.
   */
  virtual ~ColourLine();

public:

  /** @name Access particles connected to the colour line. */
  //@{
  /**
   * Return the vectors of particles connected to this line with their
   * colours.
   */
  inline const tPVector & coloured() const;

  /**
   * Return the vectors of particles connected to this line with their
   * anti-colours.
   */
  inline const tPVector & antiColoured() const;

  /**
   * Return the first particle on this colour line. Returns null if
   * this line stems from a colour source. If the particle is
   * outgoing, its anti colour is connected, otherwise its colour is
   * connected.
   */
  inline tPPtr startParticle() const;

  /**
   * Return the last particle on this colour line. Returns null if
   * this line ends in a colour sink. If the particle is outgoing, its
   * colour is connected, otherwise its anti colour is connected.
   */
  inline tPPtr endParticle() const;

  //@}

  /** @name Add and remove particles in a colour line. */
  //@{
  /**
   * Add a particle having this as a anti-colour line.
   */
  void addAntiColoured(tPPtr);

  /**
   * Add a particle having this as a (anti-)colour line.
   * @param p the particle to be connected.
   * @param anti if true, this is the anti-colour line of \a p.
   */
  void addColoured(tPPtr p, bool anti = false);

  /**
   * Remove a particle having this as an anti-colour line.
   */
  void removeAntiColoured(tPPtr);

  /**
   * Remove a particle having this as a (anti-)colour line.
   * @param p the particle to be removed.
   * @param anti if true, this is the anti-colour line of \a p.
   */
  void removeColoured(tPPtr p, bool anti = false);

  //@}

  /** @name Functions for junction strings. */
  //@{
  /**
   * If this colour line ends in a colour sink, these two colour lines
   * ends in the same.
   */
  inline tColinePair sinkNeighbours() const;

  /**
   * If this colour line stems from a colour source (sink), these two colour
   * lines stems from (ends in) the same.
   * @param anti if true return sinkNeighbours().
   */
  inline tColinePair sourceNeighbours(bool anti = false) const;

  /**
   * Add two colour lines as neighbours to this line. Afterwards all
   * three will end in the same sink. Also the neighbors are set up
   * correspondingly.
   */
  inline void setSinkNeighbours(tColinePtr, tColinePtr);

  /**
   * Add two colour lines as neighbours to this line. Afterwards all
   * three will stem from the same source. Also the neighbors are set
   * up correspondingly.
   */
  inline void setSourceNeighbours(tColinePtr, tColinePtr);

  //@}

  /**
   * Join with the given ColourLine. The colour of the given \a line
   * is joined so that it will flow into this line, ie. the
   * anti-coloured particle in the end of the \a line will become
   * connected to the coloured particle in the of this line.  After
   * the joining the given \a line will not be connected to
   * anything. Also the anti-coloured particle in the end of this
   * line, which must be the same as the coloured particle in the end
   * of the \line, will not be connected to any line afterwards.
   */
  bool join(ColinePtr line);

  /**
   * Return the first (anti-)coloured parton among the given range of
   * particles which is on this colour line.
   */
  template <typename Iterator>
  inline typename std::iterator_traits<Iterator>::value_type
  getColouredParticle(Iterator first, Iterator last, bool anti = false) const;

  /**
   * Write out information about this colour line to the stream.
   */
  void write(ostream & os, tcEventPtr event, bool anti);

public:

  /**
   * Standard function for writing to a persistent stream.
   */
  void persistentOutput(PersistentOStream &) const;

  /**
   * Standard function for reading from a persistent stream.
   */
  void persistentInput(PersistentIStream &, int);

private:

  /**
   * The particles connecting to this colour line, following the
   * incoming colour flow.
   */
  tPVector theColoured;

  /**
   * The particles connecting to this colour line, following the
   * outgoing colour flow.
   */
  tPVector theAntiColoured;

  /**
   * If this colour line stems from a colour source, these two colour
   * lines stems from the same.
   */
  tColinePair theSourceNeighbours;

  /**
   * If this colour line ends in a colour sink, these two colour lines
   * ends in the same.
   */
  tColinePair theSinkNeighbours;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<ColourLine> initColourLine;

  /**
   *  Private and non-existent assignment operator.
   */
  ColourLine & operator=(const ColourLine &);

};

}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/**
 * The following template specialization informs ThePEG about the
 * base class of ColourLine.
 */
template <>
struct BaseClassTrait<ColourLine,1>: public ClassTraitsType {
  /** Typedef of the first base class of ColourLine. */
  typedef EventRecordBase NthBase;
};

/**
 * The following template specialization informs ThePEG about the
 * name of this class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ColourLine>: public ClassTraitsBase<ColourLine> {
  /** Return the class name. */
  static string className() { return "ThePEG::ColourLine"; }
  /** Return the name of the shared library to be loaded to get
   * access to this class. */
  static string library() { return "ColourLine.so"; }
};

/** @endcond */

}

#include "ColourLine.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ColourLine.tcc"
#endif

#endif /* ThePEG_ColourLine_H */
