// -*- C++ -*-
#ifndef ThePEG_Named_H
#define ThePEG_Named_H
//
// This is the declaration of the <!id>Named<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Named<!!id> class is a concrete base class to used by
// classes of objects with a name.
//


#include <string>

namespace ThePEG {

class Named {

public:

  inline Named();
  // Empty constructor.

  inline Named(const string & newName);
  // Constructor with name.

  inline Named(const Named &);
  // Copy constructor.

  inline ~Named();
  // Empty Destructor.

  inline const string & name() const;
  // Return name.

  inline bool operator == (const Named &) const;
  inline bool operator < (const Named &) const;
  // Comparisons.

protected:

  inline const Named & operator = (const Named &);
  inline const string & name(const string & newName);
  // Set new name.

private:

  string theName;
  // The string containing the name.

};

}

#include "Named.icc"

#endif /* ThePEG_Named_H */
