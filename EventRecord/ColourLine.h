// -*- C++ -*-
#ifndef ThePEG_ColourLine_H
#define ThePEG_ColourLine_H
//
// This is the declaration of the <!id>ColourLine<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>ColourLine<!!id> class represents colour lines connecting
// <!class>Particle<!!class>s. A <!id>ColourLine<!!id> keeps track on
// the particles connected to it. To connect a particle to a colour
// line the <!id>addColoured<!!id> and <!id>addAntiColoured<!!id>
// methods should be used - these will automatically set up the
// <!class>Particle<!!class> correctly. There is no method in a
// Particle to directly set its colour lines.
//
// If a colour line stems from a colour source or ends in a colour
// sink, it is possible to obtain the neighbouring colour lines. This
// is also the way sinks and sources are implemented.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Particle.html">Particle.h</a>,
// <a href="http:ColourBase.html">ColourBase.h</a>.
// 

#include "EventConfig.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/EventRecord/ColourSinglet.h"

// #include "ColourLine.fh"
// #include "ColourLine.xh"

namespace ThePEG {

class ColourLine: public EventRecordBase {

public:

  inline ColourLine();
  inline ColourLine(const ColourLine &);
  virtual ~ColourLine();
  // Standard ctors and dtor.

  static tColinePtr create(tPPtr col, tPPtr anti);
  // Set a pair of colour - anticolour particles in a newly created
  // colour line.

  static tColinePtr create(tPPtr col, bool anti = false);
  // Set a (anti) particle in a newly created colour line.

public:

  inline const tPVector & coloured() const;
  inline const tPVector & antiColoured() const;
  // Return the vectors of particles connected to this line with their
  // coloures or anti colours.

  inline tPPtr startParticle() const;
  // Return the first particle on this colour line. Returns null if
  // this line stems from a colour source. If the particle is
  // outgoing, its anti colour is connected, otherwise its colour is
  // connected.

  inline tPPtr endParticle() const;
  // Return the last particle on this colour line. Returns null if
  // this line ends in a colour sink. If the particle is outgoing, its
  // colour is connected, otherwise its anti colour is connected.

  void addAntiColoured(tPPtr);
  // Add an anti coloured particle to this line.

  void addColoured(tPPtr, bool anti = false);
  // Add a coloured particle to this line.

  void removeAntiColoured(tPPtr);
  // Add an anti coloured particle to this line.

  void removeColoured(tPPtr, bool anti = false);
  // Add a coloured particle to this line.

  inline tColinePair sinkNeighbours() const;
  // If this colour line ends in a colour sink, these two colour lines
  // ends in the same.

  inline tColinePair sourceNeighbours(bool anti = false) const;
  // If this colour line stems from a colour source, these two colour
  // lines stems from the same.

  inline void setSinkNeighbours(tColinePtr, tColinePtr);
  inline void setSourceNeighbours(tColinePtr, tColinePtr);
  // Add two colour lines as neighbour to this lines sink or
  // source. Also the neighbors are set up correspondingly.

  template <typename Iterator>
  inline typename std::iterator_traits<Iterator>::value_type
  getColouredParticle(Iterator first, Iterator last, bool anti = false) const;
  // Return the first (anti-)coloured parton among the given range of
  // particles which is on this colour line.

  void write(ostream & os, tcEventPtr event, bool anti);
  // Write out information about this colour line to the stream.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

private:

  tPVector theColoured;
  tPVector theAntiColoured;
  // The particles connecting to this colour line, either following
  // the incoming colour flow or the outgoing one.

  tColinePair theSourceNeighbours;
  // If this colour line stems from a colour source, these two colour
  // lines stems from the same.

  tColinePair theSinkNeighbours;
  // If this colour line ends in a colour sink, these two colour lines
  // ends in the same.

private:

  static ClassDescription<ColourLine> initColourLine;
  // Describe a concrete class with persistent data.

  ColourLine & operator=(const ColourLine &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of ColourLine.
template <>
struct BaseClassTrait<ColourLine,1> {
  typedef EventRecordBase NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ColourLine>: public ClassTraitsBase<ColourLine> {
  static string className() { return "/ThePEG/ColourLine"; }
  // Return the class name.
  static string library() { return "ColourLine.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "ColourLine.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ColourLine.tcc"
#endif

#endif /* ThePEG_ColourLine_H */
