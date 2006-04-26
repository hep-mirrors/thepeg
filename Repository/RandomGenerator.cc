// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RandomGenerator class.
//

#include "RandomGenerator.h"
#include "ThePEG/CLHEPWrap/RandomEngine.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Utilities/Timer.h"

using namespace ThePEG;

RandomGenerator::RandomGenerator()
  : theNumbers(1000), theSize(1000), theSeed(0) {
  nextNumber = theNumbers.end();
}

RandomGenerator::RandomGenerator(const RandomGenerator & rg)
  : Interfaced(rg), theNumbers(rg.theNumbers), theSize(rg.theSize),
    theSeed(rg.theSeed)  {
  nextNumber = theNumbers.begin() +
    ( RndVector::const_iterator(rg.nextNumber) - rg.theNumbers.begin() );
}

RandomGenerator::~RandomGenerator() {}

void RandomGenerator::doinit() throw (InitException) {
  if ( theSeed > 0 ) setSeed(theSeed);
}

void RandomGenerator::getFlatNumbers() {
  Timer<1> timer("RandomGenerator::getFlatNumbers()");
  nextNumber = theNumbers.begin();
  randomGenerator().flatArray(theSize, &(theNumbers.front()));
}

void RandomGenerator::setSize(size_type newSize) {
  RndVector newNumbers(newSize);
  RndVector::iterator nextNew = newNumbers.end() -
    min( int(theNumbers.end() - nextNumber), int(newSize) );
  for ( RndVector::iterator i = nextNew; i != newNumbers.end(); ++i )
    *i = *nextNumber++;
  RndVector::difference_type pos = nextNew - newNumbers.begin();
  theNumbers.swap(newNumbers);
  nextNumber = theNumbers.begin() + pos;
}

bool RandomGenerator::rndbool(double p) {
  if ( p >= 1.0 ) return true;
  if ( p <= 0.0 ) return false;
  double r = rnd();
  if ( r < p ) {
    push_back(r/p);
    return true;
  } else {
    push_back((r - p)/(1.0 - p));
    return false;
  }
}

int RandomGenerator::rndsign(double p1, double p2, double p3) {
  double sum = p1 + p2 + p3;
  double r = rnd()*sum;
  if ( r < p1 ) {
    push_back(r/p1);
    return -1;
  } else if ( r < p1 + p2 ) {
    push_back((r - p1)/p2);
    return 0;
  } else {
    push_back((r - p1 - p2)/p3);
    return 1;
  }
}

int RandomGenerator::rnd4(double p0, double p1, double p2, double p3) {
  double sum = p0 + p1 + p2 + p3;
  double r = rnd()*sum;
  if ( r < p0 ) {
    push_back(r/p0);
    return 0;
  } else if ( r < p0 + p1 ) {
    push_back((r - p0)/p1);
    return 1;
  } else if ( r < p0 + p1 + p2 ) {
    push_back((r - p0 - p1)/p2);
    return 2;
  } else {
    push_back((r - p0 - p1 - p2)/p3);
    return 3;
  }
}

void RandomGenerator::persistentOutput(PersistentOStream & os) const {
  os << theNumbers
     << RndVector::const_iterator(nextNumber) - theNumbers.begin() << theSize
     << theSeed;
}

void RandomGenerator::persistentInput(PersistentIStream & is, int) {
  RndVector::difference_type pos;
  is >> theNumbers >> pos >> theSize >> theSeed;
  nextNumber = theNumbers.begin() + pos;
}

ClassDescription<RandomGenerator> RandomGenerator::initRandomGenerator;

void RandomGenerator::Init() {

  static ClassDocumentation<RandomGenerator> documentation
    ("There is no documentation for the ThePEG::RandomGenerator class");

  static Parameter<RandomGenerator,size_type> interfaceSize
    ("CacheSize",
     "The Random numbers are generated in chunks of this size.",
     &RandomGenerator::theSize, 1000, 10, 100000, true, false, true,
     &RandomGenerator::setSize);

  static Parameter<RandomGenerator,long> interfaceSeed
    ("Seed",
     "The seed with which this random generator is initialized. "
     "If set to zero, the default build-in seed will be used.",
     &RandomGenerator::theSeed, 0, 0, 100000000, true, false, false);

  interfaceSize.rank(10);
  interfaceSeed.rank(9);

}

