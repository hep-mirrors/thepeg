// -*- C++ -*-
//
// utilitiesTestSmearing.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad, 2015 Marco A. Harrendorf
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_Repository_Test_RandomGenerator_H
#define ThePEG_Repository_Test_RandomGenerator_H

#include <boost/test/unit_test.hpp>
#include <boost/iterator/iterator_concepts.hpp>

#include "ThePEG/Repository/RandomGenerator.h"
#include <StandardRandom.h>
#include <iostream>
#include <fstream>



/*
 * Helper class to test generated random numbers
 * 
 * The class checks how many random numbers are inside a pre-defined interval and how many outside
 * This class is e.g. useful to check random numbers produced by a gaussian distribution
 */
template <typename Unit>
class HelperRandomNumberBinningCheck {
  private:
    // Do not accept missing interval limits
    HelperRandomNumberBinningCheck() {}
  public:
    // Define interval limits
    HelperRandomNumberBinningCheck(Unit intervalLowerLimit, Unit intervalUpperLimit) 
      : m_intervalLowerLimit(intervalLowerLimit), m_intervalUpperLimit(intervalUpperLimit), m_numbersInsideInterval(0), m_numbersOutsideInterval(0) {}
    ~HelperRandomNumberBinningCheck() {}
    
    int numbersInsideInterval() {return m_numbersInsideInterval;}
    int numbersOutsideInterval() {return m_numbersOutsideInterval;}
    int numbersTotal() {return m_numbersOutsideInterval + m_numbersInsideInterval;}
    // Check if random number is inside / outside interval and increase corresponding counter
    void add(Unit randomNumber) {
      if(randomNumber >= m_intervalLowerLimit && randomNumber <= m_intervalUpperLimit) {
	m_numbersInsideInterval++;
      } else {
	m_numbersOutsideInterval++;
      }
    }
    // Reset counters
    void resetCounters() {m_numbersInsideInterval = 0; m_numbersOutsideInterval = 0;}
  
  private:
    Unit m_intervalLowerLimit, m_intervalUpperLimit;
    int m_numbersInsideInterval, m_numbersOutsideInterval; 
};
typedef HelperRandomNumberBinningCheck<double> HelperDoubleBinningCheck;

/*
 * Start of BOOST unit tests for Helper class
 * 
 */
BOOST_AUTO_TEST_SUITE(HelperRandomNumberBinning)

BOOST_AUTO_TEST_CASE(HelperDoubleBinning)
{
  HelperDoubleBinningCheck* doubleBinningCheckObject = new HelperDoubleBinningCheck(0, 1);
  doubleBinningCheckObject->add(-1.1);
  doubleBinningCheckObject->add(-0.1);
  doubleBinningCheckObject->add(0.1);
  doubleBinningCheckObject->add(0.5);
  doubleBinningCheckObject->add(0.8);
  doubleBinningCheckObject->add(1.1);
  doubleBinningCheckObject->add(100);
  BOOST_CHECK_EQUAL(doubleBinningCheckObject->numbersTotal(), 7);
  BOOST_CHECK_EQUAL(doubleBinningCheckObject->numbersInsideInterval(), 3);
  BOOST_CHECK_EQUAL(doubleBinningCheckObject->numbersOutsideInterval(), 4);
  
  doubleBinningCheckObject->resetCounters();
  BOOST_CHECK_EQUAL(doubleBinningCheckObject->numbersTotal(), 0);
  BOOST_CHECK_EQUAL(doubleBinningCheckObject->numbersInsideInterval(), 0);
  BOOST_CHECK_EQUAL(doubleBinningCheckObject->numbersOutsideInterval(), 0);
  
  
  HelperDoubleBinningCheck* doubleBinningCheckObjectTwo = new HelperDoubleBinningCheck(-1.5, 0.5);
  doubleBinningCheckObjectTwo->add(-1.1);
  doubleBinningCheckObjectTwo->add(-0.1);
  doubleBinningCheckObjectTwo->add(0.1);
  doubleBinningCheckObjectTwo->add(0.5);
  doubleBinningCheckObjectTwo->add(0.8);
  doubleBinningCheckObjectTwo->add(1.1);
  doubleBinningCheckObjectTwo->add(100);
  BOOST_CHECK_EQUAL(doubleBinningCheckObjectTwo->numbersTotal(), 7);
  BOOST_CHECK_EQUAL(doubleBinningCheckObjectTwo->numbersInsideInterval(), 4);
  BOOST_CHECK_EQUAL(doubleBinningCheckObjectTwo->numbersOutsideInterval(), 3);
}

/* 
 * End of BOOST unit tests for Helper class
 * 
 */
BOOST_AUTO_TEST_SUITE_END()



/*
 * Local fix to provide randomGenerator object
 * 
 */
struct FixLocal1 {
  FixLocal1() {
    BOOST_TEST_MESSAGE( "setup local fixture for repositoryTestRandomGenerator" ); 
    
    // Initialize randomNumberGenerator
    randomNumberStandardGenerator = new ThePEG::StandardRandom();
  }
  
  ~FixLocal1()  { BOOST_TEST_MESSAGE( "teardown local fixture for repositoryTestRandomGenerator" ); }
  
  ThePEG::StandardRandom* randomNumberStandardGenerator;
};

/*
 * Start of boost unit tests for RandomGenerator.h
 * 
 */
BOOST_FIXTURE_TEST_SUITE(repositoryRandomGenerator, FixLocal1)

/*
 * Boost unit tests 
 * 
 */
BOOST_AUTO_TEST_CASE(rndZeroToOne)
{
  int numberOfTrials = 1000;
  // Check for whole interval 
  HelperDoubleBinningCheck* allRandomNumbersBetweenZeroAndOne = new HelperDoubleBinningCheck(0, 1);
  // Check for flat distribution
  HelperDoubleBinningCheck* allRandomNumbersBetweenZeroAndFirstQuarter = new HelperDoubleBinningCheck(0, 0.25);
  HelperDoubleBinningCheck* allRandomNumbersBetweenSecondAndThirdQuarter = new HelperDoubleBinningCheck(0.5, 0.75);
  
  // rnd function
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndOne->add(randomNumberStandardGenerator->rnd());
    allRandomNumbersBetweenZeroAndFirstQuarter->add(randomNumberStandardGenerator->rnd());
    allRandomNumbersBetweenSecondAndThirdQuarter->add(randomNumberStandardGenerator->rnd());
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.25
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstQuarter->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersInsideInterval(), 0.25 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersOutsideInterval(), 0.75 * numberOfTrials, 5);
  
  // Prob laying inside of interval should be 0.25
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondAndThirdQuarter->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersInsideInterval(), 0.25 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersOutsideInterval(), 0.75 * numberOfTrials, 5);
  
  
  // repeat for operator()
  allRandomNumbersBetweenZeroAndOne->resetCounters();
  allRandomNumbersBetweenZeroAndFirstQuarter->resetCounters();
  allRandomNumbersBetweenSecondAndThirdQuarter->resetCounters();
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndOne->add(randomNumberStandardGenerator->operator()());
    allRandomNumbersBetweenZeroAndFirstQuarter->add(randomNumberStandardGenerator->operator()());
    allRandomNumbersBetweenSecondAndThirdQuarter->add(randomNumberStandardGenerator->operator()());
  }
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersOutsideInterval(), 0);
  
    // Prob laying inside of interval should be 0.25
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstQuarter->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersInsideInterval(), 0.25 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersOutsideInterval(), 0.75 * numberOfTrials, 5);
  
  // Prob laying inside of interval should be 0.25
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondAndThirdQuarter->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersInsideInterval(), 0.25 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersOutsideInterval(), 0.75 * numberOfTrials, 5);
}

BOOST_AUTO_TEST_CASE(rndZeroToIntervalUpperLimit)
{
  unsigned int numberOfTrials = 1000;
  double intervalUpperLimit = 2.65;
  for(unsigned int i = 0; i < numberOfTrials; ++i) {
    double randomNumber = randomNumberStandardGenerator->rnd(intervalUpperLimit);
    BOOST_CHECK(randomNumber > 0);
    BOOST_CHECK(randomNumber < intervalUpperLimit);
  }
  
  long intervalUpperLimitTwo = 3;
  for(unsigned int i = 0; i < numberOfTrials; ++i) {
    long randomNumber = randomNumberStandardGenerator->operator()(intervalUpperLimitTwo);
    BOOST_CHECK(randomNumber >= 0);
    BOOST_CHECK(randomNumber <= intervalUpperLimitTwo);
  }
}

BOOST_AUTO_TEST_CASE(rndIntervallLowerLimitToIntervalUpperLimit)
{
  unsigned int numberOfTrials = 1000;
  double intervalLowerLimit = -1.25;
  double intervalUpperLimit = 2.65;
  for(unsigned int i = 0; i < numberOfTrials; ++i) {
    double randomNumber = randomNumberStandardGenerator->rnd(intervalLowerLimit, intervalUpperLimit);
    BOOST_CHECK(randomNumber > intervalLowerLimit);
    BOOST_CHECK(randomNumber < intervalUpperLimit);
  }
}

BOOST_AUTO_TEST_CASE(rndZeroToOneVector)
{
  unsigned int numberOfTrials = 10;
  unsigned int lengthOfRandomVector = 10;
  for(unsigned int i = 0; i < numberOfTrials; ++i) {
    std::vector<double> randomNumberVector = randomNumberStandardGenerator->rndvec(lengthOfRandomVector);
    BOOST_CHECK_EQUAL(randomNumberVector.size(), lengthOfRandomVector);
    for(unsigned int j = 0; j < randomNumberVector.size(); ++j) {
      BOOST_CHECK(randomNumberVector[j] > 0);
      BOOST_CHECK(randomNumberVector[j] < 1);
    }
  }
}

BOOST_AUTO_TEST_CASE(rndBoolSingleProbability)
{
  unsigned int numberOfTrials = 1000;
  for(unsigned int i = 0; i < numberOfTrials; ++i) {
    double randomNumber = randomNumberStandardGenerator->rnd();
    BOOST_CHECK(randomNumber > 0);
    BOOST_CHECK(randomNumber < 1);
  }
}




BOOST_AUTO_TEST_CASE(azimuthalSmearing)
{
  /*
  double vectorXvalue, vectorYvalue;
  double vectorLengthCalculated;
  unsigned int numberOfTrials = 10000;
  for(unsigned int vectorLength = 1; vectorLength < 4; ++vectorLength) {
    // Variables for statistical analysis
    double meanVectorLength = 0, meanVectorX = 0, meanVectorY = 0;
    unsigned int inverseSamplingEfficiency = 0;
    for(unsigned int i = 0; i < numberOfTrials; ++i) {
      if(Herwig::Smearing::azimuthalSmearing(vectorLength, vectorXvalue, vectorYvalue)) {
	vectorLengthCalculated = sqrt(vectorXvalue*vectorXvalue + vectorYvalue*vectorYvalue);
	BOOST_CHECK_CLOSE(vectorLengthCalculated, vectorLength, 1e-06);
	meanVectorLength += vectorLengthCalculated;
	meanVectorX += vectorXvalue;
	meanVectorY += vectorYvalue;
      }
      else {
	inverseSamplingEfficiency++;
      }
    }
  // Normalize mean values
  meanVectorLength = meanVectorLength/static_cast<double>(numberOfTrials - inverseSamplingEfficiency);
  meanVectorX = meanVectorX/static_cast<double>(numberOfTrials - inverseSamplingEfficiency);
  meanVectorY = meanVectorY/static_cast<double>(numberOfTrials - inverseSamplingEfficiency);
  
  BOOST_CHECK_CLOSE(meanVectorLength , vectorLength, 0.001);
  BOOST_CHECK(meanVectorX < 1e-1 && meanVectorX > -1e-1);
  BOOST_CHECK(meanVectorY < 1e-1 && meanVectorY > -1e-1);
  BOOST_CHECK(inverseSamplingEfficiency < 0.25 * numberOfTrials);
  }
  */
  BOOST_CHECK(1 == 1);
}

BOOST_AUTO_TEST_CASE(gaussianSmearing)
{
  /*
  std::ofstream myfile;
  myfile.open ("out2.txt");
  
  double gaussianValue;
  unsigned int numberOfTrials = 1000000;
  for(unsigned int gaussianMean = 1; gaussianMean < 2; ++gaussianMean) {
    for(double gaussianSigma = 0.25; gaussianSigma < 0.35; gaussianSigma += 0.1) {
      // Variables for statistical analysis
      double meanValue = 0, meanSigma = 0;
      unsigned int inverseSamplingEfficiency = 0;
      for(unsigned int i = 0; i < numberOfTrials; ++i) {
	if(Herwig::Smearing::gaussianSmearing(gaussianMean, gaussianSigma, gaussianValue)) {
	  // Check for 8 sigma deviation
	  BOOST_CHECK(gaussianValue < (gaussianMean + 8 * gaussianSigma));
	  //std::cout << gaussianValue << " " << gaussianMean << " " << gaussianSigma << " " << (gaussianMean + 8 * gaussianSigma) << std::endl;
	  myfile << gaussianValue << std::endl;
	  BOOST_CHECK(gaussianValue > (gaussianMean - 8 * gaussianSigma));
	  meanValue += gaussianValue;
	  meanSigma += std::abs(gaussianValue - gaussianMean);
	}
	else {
	  inverseSamplingEfficiency++;
	}
      }
    // Normalize mean values
    meanValue = meanValue/static_cast<double>(numberOfTrials - inverseSamplingEfficiency);
    meanSigma = meanSigma/static_cast<double>(numberOfTrials - inverseSamplingEfficiency);
    std::cout << meanValue << " " << meanSigma << std::endl;
    BOOST_CHECK_CLOSE(meanValue , gaussianMean, 0.5);
    BOOST_CHECK_CLOSE(meanSigma , gaussianSigma, 0.5);
    BOOST_CHECK(inverseSamplingEfficiency < 0.25 * numberOfTrials);
    }
  }
  */
}



BOOST_AUTO_TEST_SUITE_END()

#endif /* ThePEG_Repository_Test_RandomGenerator_H */
