// -*- C++ -*-
#ifndef ThePEG_Named_H
#define ThePEG_Named_H
// This is the declaration of the Named class.


#include <string>

namespace ThePEG {

/**
 * The <code>Named</code> class is a simple concrete base class to
 * used by classes of objects with a name. It just defines a string
 * member variable with corresponding (protected) set and get
 * functions.
 */
class Named {

public:

  /**
   * Empty constructor.
   */
  inline Named();

  /**
   * Constructor with name.
   */
  inline Named(const string & newName);

  /**
   * Copy constructor.
   */
  inline Named(const Named &);

  /**
   * Empty Destructor.
   */
  inline ~Named();

  /**
   * Return name.
   */
  inline const string & name() const;

  /**
   * Test for equality.
   */
  inline bool operator == (const Named &) const;
  /**
   * Lexicographical comparison.
   */
  inline bool operator < (const Named &) const;

protected:

  /**
   * Assignment.
   */
  inline const Named & operator = (const Named &);

  /**
   * Set new name.
   */
  inline const string & name(const string & newName);

private:

  /**
   * The string containing the name.
   */
  string theName;

};

}

#include "Named.icc"

#endif /* ThePEG_Named_H */
