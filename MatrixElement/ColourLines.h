// -*- C++ -*-
#ifndef ThePEG_ColourLines_H
#define ThePEG_ColourLines_H
// This is the declaration of the ColourLines class.

#include "ThePEG/Config/ThePEG.h"
// #include "ColourLines.fh"
// #include "ColourLines.xh"

namespace ThePEG {

/**
 * The ColourLines class defines the colour flow in a SubProcess. It
 * defines a number of colour lines and specifies which particles are
 * connected to them.
 * 
 */
class ColourLines: public Base {

public:

  /** A single colour line */
  typedef vector<int> Line;
  /** A vector of colour lines. */
  typedef vector<Line> LineVector;
  /** A vector of <code>ColourLine</code>. */
  typedef vector<ColinePtr> Vertex;
  /** A vector of vertices. */
  typedef vector<Vertex> VertexVector;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline ColourLines();

  /**
   * Copy-constructor.
   */
  inline ColourLines(const ColourLines &);

  /**
   * The standard constructor. The string \a s should contain a
   * comma-separated sequence of integers. Each sequence of numbers
   * indicates a colour line and the integer represents a parton
   * connected to it. If the integer is negative, it means that the
   * line is the corresponding partons anti-colour. Note that the
   * partons are numbered from 1: The first incoming is 1, the second
   * is 2 and the internal and outgoing are numbered 3 and upwards.
   */
  ColourLines(string s);

  /**
   * Destructor.
   */
  virtual ~ColourLines();
  //@}

public:

  /**
   * Create the corresponding <code>ColourLine</code>s and connect the
   * given \a partons. The partons are assumed to be in the same order
   * as the numbers specified in the constructor.
   */
 void connect(const tPVector & partons) const;

private:

  /**
   * The vector of colour lines.
   */
  LineVector theLines;

};

}

#include "ColourLines.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ColourLines.tcc"
#endif

#endif /* ThePEG_ColourLines_H */
