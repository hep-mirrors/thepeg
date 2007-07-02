// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StandardRandom class.
//

#include "StandardRandom.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StandardRandom.tcc"
#endif

using namespace ThePEG;

StandardRandom::~StandardRandom() {}

IBPtr StandardRandom::clone() const {
  return new_ptr(*this);
}

IBPtr StandardRandom::fullclone() const {
  return new_ptr(*this);
}

void StandardRandom::setSeed(long seed) {
  long ij = seed/30082;
  long kl = seed - 30082*ij;
  long i = (ij/177) % 177 + 2;
  long j = ij % 177 + 2;
  long k = (kl/169) % 178 + 1;
  long l = kl % 169;

  for ( int n = 1 ; n < 98 ; n++ ) {
    double s = 0.0;
    double t = 0.5;
    for ( int m = 1 ; m < 25 ; m++) {
      int mm = ( ( (i*j) % 179 ) * k ) % 179;
      i = j;
      j = k;
      k = mm;
      l = ( 53 * l + 1 ) % 169;
      if ( (l*mm % 64 ) >= 32 )
        s += t;
      t *= 0.5;
    }
    u[n-1] = s;
  }
  c = 362436.0 / 16777216.0;
  cd = 7654321.0 / 16777216.0;
  cm = 16777213.0 / 16777216.0;

  i97 = 96;
  j97 = 32;

  flush();
}

void StandardRandom::fill() {

  for ( int i = 0, N = theNumbers.size(); i < N; ++i ) {
    double & uni = theNumbers[i];
    do {
      uni = u[i97] - u[j97];
      if ( uni < 0.0 ) uni++;
      u[i97] = uni;
      
      if (i97 == 0) i97 = 96;
      else i97--;
      
      if (j97 == 0) j97 = 96;
      else j97--;
      
      c -= cd;
      if (c < 0.0) c += cm;
      
      uni -= c;
      if (uni < 0.0) uni += 1.0;
    } while ( uni <= 0.0 || uni >= 1.0 );
  }
  nextNumber = theNumbers.begin();
}

void StandardRandom::persistentOutput(PersistentOStream & os) const {
  os << u << c << cd << cm << i97 << j97;
}

void StandardRandom::persistentInput(PersistentIStream & is, int) {
  is >> u >> c >> cd >> cm >> i97 >> j97;
}

ClassDescription<StandardRandom> StandardRandom::initStandardRandom;

void StandardRandom::Init() {

  static ClassDocumentation<StandardRandom> documentation
    ("Interface to the CLHEP::JamesRandom engine class.");

}

