#ifndef ThePEG_sstream_H
#define ThePEG_sstream_H

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

class ostringstream: public ostrstream {

public:

  inline ostringstream();
  inline ostringstream(const string &);
  inline string str();

private:

  inline ostringstream(const ostringstream &);
  inline ostringstream & operator=(const ostringstream &);
  inline bool operator==(const ostringstream &) const;
};

class istringstream: public istrstream {

public:

  inline istringstream(const string &);

private:

  inline istringstream();
  inline istringstream(const istringstream &);
  inline istringstream & operator=(const istringstream &);
  inline bool operator==(const istringstream &) const;

};

}

#include "sstream.icc"

#endif

#endif /* ThePEG_sstream_H */
