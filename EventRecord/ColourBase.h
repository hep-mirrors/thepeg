// -*- C++ -*-
#ifndef ThePEG_ColourBase_H
#define ThePEG_ColourBase_H
//
// This is the declaration of the <!id>ColourBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>ColourBase<!!id> is the base class to be used to supply a
// <!class>Particle<!!class> with information about its colour
// state. This base class supplies information about the
// <!class>ColourLine<!!class>s to which the particle is
// connected. This should be sufficient for most uses. If any other
// info is required for a particle, it may be supplied by an object of
// a sub-class of <!id>ColourBase<!!id>, the additional information
// would then have to be extracted by dynamically casting to the
// sub-class.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Particle.html">Particle.h</a>,
// <a href="http:ColourLine.html">ColourLine.h</a>.
// 

#include "ThePEG/EventRecord/EventInfoBase.h"
#include "ThePEG/EventRecord/ColourLine.h"
// #include "ColourBase.fh"
// #include "ColourBase.xh"

namespace ThePEG {

class ColourBase: public EventInfoBase {

public:

  friend class ColourLine;
  

public:

  inline ColourBase();
  inline ColourBase(const ColourBase &);
  virtual ~ColourBase();
  // Standard ctors and dtor.

public:

  inline tColinePtr antiColourLine() const;
  inline tColinePtr colourLine() const;
  // Return the colour lines to which this particle is connected.

private:

  inline void antiColourLine(tColinePtr);
  inline void colourLine(tColinePtr);
  // Set the colour lines to which this particle is connected.

public:

  virtual void rebind(const EventTranslationMap & trans);

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

  inline virtual EIPtr clone() const;
  // Standard clone method.

private:

  ColinePtr theAntiColourLine;
  ColinePtr theColourLine;
  // The colour lines to which this particle is connected.

private:

  static ClassDescription<ColourBase> initColourBase;
  // Describe concrete class with persistent data.

  ColourBase & operator=(const ColourBase &);
  //  Private and non-existent assignment operator.

};

// CLASSDOC OFF

ThePEG_DECLARE_CLASS_TRAITS(ColourBase,EventInfoBase);

}

#include "ColourBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ColourBase.tcc"
#endif

#endif /* ThePEG_ColourBase_H */
