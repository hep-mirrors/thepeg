// -*- C++ -*-
#ifndef ThePEG_ColourLines_H
#define ThePEG_ColourLines_H
//
// This is the declaration of the <!id>ColourLines<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
// #include "ColourLines.fh"
// #include "ColourLines.xh"

namespace ThePEG {

class ColourLines: public Base {

public:

  typedef vector<int> Line;
  typedef vector<Line> LineVector;
  typedef vector<ColinePtr> Vertex;
  typedef vector<Vertex> VertexVector;

public:

  inline ColourLines();
  inline ColourLines(const ColourLines &);
  ColourLines(string s);
  virtual ~ColourLines();
  // Standard ctors and dtor.

public:

  void connect(const tPVector & partons) const;

private:

  LineVector theLines;

};

}

#include "ColourLines.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ColourLines.tcc"
#endif

#endif /* ThePEG_ColourLines_H */
