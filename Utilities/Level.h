// -*- C++ -*-
#ifndef ThePEG_Level_H
#define ThePEG_Level_H
// This is the declaration of the Level class.

#include "ThePEG/Config/ThePEG.h"
// #include "Level.fh"
// #include "Level.xh"

namespace ThePEG {

/**
 * Level is used to increment temporarily a given integer
 * variable. Everytime a Level object is created with a given integer
 * variable as argument, the variable will be incremented. When the
 * corresponding Level object is destroyed, the associated integer
 * variable is decremented again.
 *
 * @see HoldFlag.
 */
template <typename T = int>
class Level {

public:

  /** Constructor taking an integer variable which is incremented. A
   *  reference to the variable will be stored. */
  inline Level(T & newLevel);

  /** Destructor decrementing the associated integer variable. */
  inline ~Level();

private:

  /** A reference to the integer variable to be decremmmented when
   *  this object is destroyed. */
  T & theLevel;

  /**
   * Default constructor is private and not implemented.
   */
  inline Level();

  /**
   * Copy constructor is private and not implemented.
   */
  inline Level(const Level &);

  /**
   * Assignment is private and not implemented.
   */
  inline Level & operator=(const Level &);

};

}

#include "Level.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Level.tcc"
#endif

#endif /* ThePEG_Level_H */
