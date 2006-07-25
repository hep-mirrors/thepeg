// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ColourLines class.
//

#include "ColourLines.h"
#include "ColourLines.xh"
#include "ThePEG/EventRecord/ColourLine.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Utilities/StringUtils.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ColourLines.tcc"
#endif


using namespace ThePEG;

ColourLines::~ColourLines() {}

ColourLines::ColourLines(string s) {
  while ( true ) {
    istringstream is(StringUtils::car(s, ","));
    int i;
    Line l;
    while ( is >> i ) l.push_back(i);
    if ( l.empty() ) return;
    theLines.push_back(l);
    s = StringUtils::cdr(s, ",");
  }
}

void ColourLines::connect(const tPVector & partons) const {
  VertexVector sinks;
  VertexVector sources;
  long np = partons.size();

  // Create each line and connect the specified partons to them. Save
  // all lines coming from a source or ending in a sink.
  for ( LineVector::size_type il = 0; il < theLines.size(); ++il ) {
    const Line & line = theLines[il];
    ColinePtr cline = new_ptr(ColourLine());
    for ( Line::size_type i = 0; i < line.size(); ++i ) {
      if ( line[i] > np ) {
	// this is a colour source.
	int is = line[i] - np;
	sources.resize(is);
	sources[is - 1].push_back(cline);
      } else if ( -line[i] > np ) {
	// this is a colour sink.
	int is = -line[i] - np;
	sources.resize(is);
	sources[is - 1].push_back(cline);
      } else if ( line[i] > 0 ) {
	// This is a coloured particle.
	if ( !partons[line[i] - 1]->hasColour() )
	  throw ColourGeometryException(partons, line);
	cline->addColoured(partons[line[i] - 1]);
      } else {
	if ( !partons[-line[i] - 1]->hasAntiColour() )
	  throw ColourGeometryException(partons, line);
	cline->addAntiColoured(partons[-line[i] - 1]);
      }
    }
  }

  // Now connect up all lines steming from sources.
  for ( VertexVector::size_type i = 0; i < sources.size(); ++i ) {
    if ( sources[i].empty() ) continue;
    if ( sources[i].size() != 3 ) throw ColourGeometryException(partons);
    sources[i][0]->setSourceNeighbours(sources[i][1], sources[i][2]);
  }

  // Now connect up all lines ending in sinks.
  for ( VertexVector::size_type i = 0; i < sinks.size(); ++i ) {
    if ( sinks[i].empty() ) continue;
    if ( sinks[i].size() != 3 ) throw ColourGeometryException(partons);
    sinks[i][0]->setSinkNeighbours(sinks[i][1], sinks[i][2]);
  }

}

ColourGeometryException::
ColourGeometryException(const tPVector & p, const vector<int> & c) {
  if ( c.empty() )
    theMessage << "The number of colour lines steming from one colour source "
	       << "or ending in one colour sink was not equal to three.\n";
  else {
    theMessage << "Cannot connect the following partons:\n";
    for ( unsigned i = 0; i < p.size(); ++i )
      theMessage << " " << p[i]->PDGName();
    theMessage << "\n to the following colour line:\n";
    for ( unsigned i = 0; i < c.size(); ++i ) theMessage << " " << c[i];
    theMessage << endl;
  }
  severity(maybeabort);
}

