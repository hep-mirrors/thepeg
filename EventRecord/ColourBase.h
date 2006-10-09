// -*- C++ -*-
#ifndef ThePEG_ColourBase_H
#define ThePEG_ColourBase_H
// This is the declaration of the ColourBase class.

#include "ThePEG/EventRecord/EventInfoBase.h"
#include "ThePEG/EventRecord/ColourLine.h"
// #include "ColourBase.fh"
// #include "ColourBase.xh"

namespace ThePEG {

/**
 * ColourBase is the base class to be used to supply a
 * Particle with information about its colour
 * state. This base class supplies information about the
 * <code>ColourLine</code>s to which the particle is
 * connected. This should be sufficient for most uses. If any other
 * info is required for a particle, it may be supplied by an object of
 * a sub-class of <code>ColourBase</code>, the additional information
 * would then have to be extracted by dynamically casting to the
 * sub-class.
 *
 * @see Particle
 * @see ColourLine
 */
class ColourBase: public EventInfoBase {

public:

  /** ColourLine is a good friend. */
  friend class ColourLine;
  
public:

  /**
   * Default constructor.
   */
  inline ColourBase();

  /**
   * Copy constructor.
   */
  inline ColourBase(const ColourBase &);

  /**
   * Destructor.
   */
  virtual ~ColourBase();

public:

  /**
   * Return the anti-colour line to which this particle is connected.
   */
  inline tColinePtr antiColourLine() const;

  /**
   * Return the colour line to which this particle is connected.
   */
  inline tColinePtr colourLine() const;

  /**
   * Return true if the particle is connected to the given (\a anti-)
   * colour \a line.
   */
  virtual bool hasColourLine(tcColinePtr line, bool anti = false) const;

  /**
   * Return true if the particle is connected to the given anti-colour
   * \a line.
   */
  inline bool hasAntiColourLine(tcColinePtr line) const;

protected:

  /**
   * Set the anti-colour line to which this particle is connected.
   */
  inline void antiColourLine(tColinePtr);

  /**
   * Set the colour line to which this particle is connected.
   */
  inline void colourLine(tColinePtr);

public:

  /**
   * Rebind to cloned objects. When a ColourBase is cloned, a shallow
   * copy is done first, then all <code>ColourLine</code>s etc, are
   * cloned, and finally this method is used to see to that the
   * pointers in the cloned ColourBase points to the cloned
   * <code>ColourLine</code>s etc.
   */
  virtual void rebind(const EventTranslationMap & trans);

  /**
   * Standard function for writing to a persistent stream.
   */
  void persistentOutput(PersistentOStream &) const;

  /**
   * Standard functions for reading from a persistent stream.
   */
  void persistentInput(PersistentIStream &, int);

  /**
   * Standard Init function. @see Base::Init().
   */
  static void Init();

  /**
   * Standard clone method.
   */
  inline virtual EIPtr clone() const;

private:

  /**
   * The anti-colour line to which this particle is connected.
   */
  ColinePtr theAntiColourLine;

  /**
   * The colour line to which this particle is connected.
   */
  ColinePtr theColourLine;

private:

  /**
   * Describe concrete class with persistent data.
   */
  static ClassDescription<ColourBase> initColourBase;

  /**
   *  Private and non-existent assignment operator.
   */
  ColourBase & operator=(const ColourBase &);

};


/** @cond TRAITSPECIALIZATIONS */
ThePEG_DECLARE_CLASS_TRAITS(ColourBase,EventInfoBase);
/** @endcond */

}

#include "ColourBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ColourBase.tcc"
#endif

#endif /* ThePEG_ColourBase_H */
