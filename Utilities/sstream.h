#ifndef ThePEG_sstream_H
#define ThePEG_sstream_H

/** \file This file ensures that the platform has a istringstream and
 *  an ostringstream class. If the header <sstream> does not exist,
 *  istringstream and ostringstream will be simple wrappers around
 *  istrtream and ostrstream respectively. */

#include "ThePEG/Config/ThePEG.h"

#ifdef ThePEG_HAS_SSTREAM

#include <sstream>

namespace ThePEG {

using std::stringstream;
using std::istringstream;
using std::ostringstream;

}

#else

#include <strstream.h>

namespace ThePEG {

/** Simple wrapper around the ostrsteam class. Will only be included
 *  if the sstream header is absent. */
class ostringstream: public ostrstream {

public:

  /** Default constructor. */
  inline ostringstream();

  /** Constructor taking a string to be written to. */
  inline ostringstream(const string &);

  /** Return a copy of the undelying string. */
  inline string str();

private:

  /** Copy Constructor is private an not implemented. */
  inline ostringstream(const ostringstream &);

  /** Assignment is private an not implemented. */
  inline ostringstream & operator=(const ostringstream &);

  /** Equality operator is private an not implemented. */
  inline bool operator==(const ostringstream &) const;

};

/** Simple wrapper around the istrsteam class. Will only be included
 *  if the sstream header is absent. */
class istringstream: public istrstream {

public:

  /** Constructor taking a string to be read from. */
  inline istringstream(const string &);

private:

  /** Default Constructor is private an not implemented. */
  inline istringstream();

  /** Copy Constructor is private an not implemented. */
  inline istringstream(const istringstream &);

  /** Assignment is private an not implemented. */
  inline istringstream & operator=(const istringstream &);

  /** Equality operator is private an not implemented. */
  inline bool operator==(const istringstream &) const;

};

}

#include "sstream.icc"

#endif

#endif /* ThePEG_sstream_H */
