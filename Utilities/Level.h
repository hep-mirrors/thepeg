// -*- C++ -*-
#ifndef ThePEG_Level_H
#define ThePEG_Level_H

#include "ThePEG/Config/ThePEG.h"
// #include "Level.fh"
// #include "Level.xh"

namespace ThePEG {

template <typename T = int>
class Level {

public:

  inline Level(T & newLevel);
  inline ~Level();

private:

  T & theLevel;

  inline Level();
  inline Level(const Level &);
  inline Level & operator=(const Level &);

};

}

#include "Level.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Level.tcc"
#endif

#endif /* ThePEG_Level_H */
