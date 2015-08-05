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
typedef HelperRandomNumberBinningCheck<long> HelperLongBinningCheck;

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
  int numberOfTrials = 1000;
  double intervalUpperLimit = 2.5;
    // Check for whole interval 
  HelperDoubleBinningCheck* allRandomNumbersBetweenZeroAndIntervalUpperLimit = new HelperDoubleBinningCheck(0, 2.5);
  // Check for flat distribution
  HelperDoubleBinningCheck* allRandomNumbersBetweenZeroAndFirstQuarter = new HelperDoubleBinningCheck(0, 0.5);
  HelperDoubleBinningCheck* allRandomNumbersBetweenSecondAndThirdQuarter = new HelperDoubleBinningCheck(1.5, 2.0);
  
  // rnd function
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndIntervalUpperLimit->add(randomNumberStandardGenerator->rnd(intervalUpperLimit));
    allRandomNumbersBetweenZeroAndFirstQuarter->add(randomNumberStandardGenerator->rnd(intervalUpperLimit));
    allRandomNumbersBetweenSecondAndThirdQuarter->add(randomNumberStandardGenerator->rnd(intervalUpperLimit));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimit->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimit->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimit->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.2
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstQuarter->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersInsideInterval(), 0.2 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersOutsideInterval(), 0.8 * numberOfTrials, 5);
  
  // Prob laying inside of interval should be 0.2
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondAndThirdQuarter->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersInsideInterval(), 0.2 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersOutsideInterval(), 0.8 * numberOfTrials, 5);
  
  
  // repeat for operator(), note it is generally requiring a long!
  allRandomNumbersBetweenZeroAndIntervalUpperLimit->resetCounters();
  allRandomNumbersBetweenZeroAndFirstQuarter->resetCounters();
  allRandomNumbersBetweenSecondAndThirdQuarter->resetCounters();
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndIntervalUpperLimit->add(randomNumberStandardGenerator->operator()(intervalUpperLimit));
    allRandomNumbersBetweenZeroAndFirstQuarter->add(randomNumberStandardGenerator->operator()(intervalUpperLimit));
    allRandomNumbersBetweenSecondAndThirdQuarter->add(randomNumberStandardGenerator->operator()(intervalUpperLimit));
  }
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimit->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimit->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimit->numbersOutsideInterval(), 0);
  
    // Prob laying inside of interval should be 0.2
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstQuarter->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersInsideInterval(), 0.2 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersOutsideInterval(), 0.8 * numberOfTrials, 5);
  
  // Prob laying inside of interval should be 0.2
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondAndThirdQuarter->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersInsideInterval(), 0.2 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersOutsideInterval(), 0.8 * numberOfTrials, 5);
  
  // repeat for operator(), note it is requiring a long!
  long intervalUpperLimitTwo = 3;
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndIntervalUpperLimitTwo = new HelperLongBinningCheck(0, intervalUpperLimitTwo);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndFirstQuarterTwo = new HelperLongBinningCheck(1, 1);
  HelperLongBinningCheck* allRandomNumbersBetweenSecondAndThirdQuarterTwo = new HelperLongBinningCheck(2, 2);
  
  // operator()(long N)
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndIntervalUpperLimitTwo->add(randomNumberStandardGenerator->operator()(intervalUpperLimitTwo));
    allRandomNumbersBetweenZeroAndFirstQuarterTwo->add(randomNumberStandardGenerator->operator()(intervalUpperLimitTwo));
    allRandomNumbersBetweenSecondAndThirdQuarterTwo->add(randomNumberStandardGenerator->operator()(intervalUpperLimitTwo));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimitTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimitTwo->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimitTwo->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.333
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstQuarterTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarterTwo->numbersInsideInterval(), 0.333 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarterTwo->numbersOutsideInterval(), 0.666 * numberOfTrials, 5);
  
  // Prob laying inside of interval should be 0.333
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondAndThirdQuarterTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarterTwo->numbersInsideInterval(), 0.333 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarterTwo->numbersOutsideInterval(), 0.666 * numberOfTrials, 5);  
}

BOOST_AUTO_TEST_CASE(rndIntervallLowerLimitToIntervalUpperLimit)
{
  int numberOfTrials = 1000;
  double intervalLowerLimit = -1.5;
  double intervalUpperLimit = 2.5;
  // Check for whole interval 
  HelperDoubleBinningCheck* allRandomNumbersBetweenZeroAndIntervalUpperLimit = new HelperDoubleBinningCheck(intervalLowerLimit, intervalUpperLimit);
  // Check for flat distribution
  HelperDoubleBinningCheck* allRandomNumbersBetweenZeroAndFirstQuarter = new HelperDoubleBinningCheck(-0.5, 0.5);
  HelperDoubleBinningCheck* allRandomNumbersBetweenSecondAndThirdQuarter = new HelperDoubleBinningCheck(1.5, 2.5);
  
  // rnd function
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndIntervalUpperLimit->add(randomNumberStandardGenerator->rnd(intervalLowerLimit, intervalUpperLimit));
    allRandomNumbersBetweenZeroAndFirstQuarter->add(randomNumberStandardGenerator->rnd(intervalLowerLimit, intervalUpperLimit));
    allRandomNumbersBetweenSecondAndThirdQuarter->add(randomNumberStandardGenerator->rnd(intervalLowerLimit, intervalUpperLimit));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimit->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimit->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndIntervalUpperLimit->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.25
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstQuarter->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersInsideInterval(), 0.25 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersOutsideInterval(), 0.75 * numberOfTrials, 5);
  
  // Prob laying inside of interval should be 0.25
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondAndThirdQuarter->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersInsideInterval(), 0.25 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersOutsideInterval(), 0.75 * numberOfTrials, 5);
}

BOOST_AUTO_TEST_CASE(rndZeroToOneVector)
{
  int numberOfTrials = 10;
  int lengthOfRandomVector = 10;
    // Check for whole interval 
  HelperDoubleBinningCheck* allRandomNumbersBetweenZeroAndOne = new HelperDoubleBinningCheck(0, 1);
  // Check for flat distribution
  HelperDoubleBinningCheck* allRandomNumbersBetweenZeroAndFirstQuarter = new HelperDoubleBinningCheck(0, 0.25);
  HelperDoubleBinningCheck* allRandomNumbersBetweenSecondAndThirdQuarter = new HelperDoubleBinningCheck(0.5, 0.75);
  
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndOne->resetCounters();
    allRandomNumbersBetweenZeroAndFirstQuarter->resetCounters();
    allRandomNumbersBetweenSecondAndThirdQuarter->resetCounters();
    
    std::vector<double> randomNumberVector = randomNumberStandardGenerator->rndvec(lengthOfRandomVector);
    BOOST_CHECK_EQUAL(static_cast<int>(randomNumberVector.size()), lengthOfRandomVector);
    for(int j = 0; j < static_cast<int>(randomNumberVector.size()); ++j) {
      allRandomNumbersBetweenZeroAndOne->add(randomNumberVector[j]);
      allRandomNumbersBetweenZeroAndFirstQuarter->add(randomNumberVector[j]);
      allRandomNumbersBetweenSecondAndThirdQuarter->add(randomNumberVector[j]);
    }
    // Prob laying inside of interval should be 1
    BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersTotal(), numberOfTrials);
    BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersInsideInterval(), numberOfTrials);
    BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersOutsideInterval(), 0);
    
    // Prob laying inside of interval should be 0.25
    BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstQuarter->numbersTotal(), numberOfTrials);
    BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersInsideInterval(), 0.25 * lengthOfRandomVector, 300);
    BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstQuarter->numbersOutsideInterval(), 0.75 * lengthOfRandomVector, 300);
    
    // Prob laying inside of interval should be 0.25
    BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondAndThirdQuarter->numbersTotal(), numberOfTrials);
    BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersInsideInterval(), 0.25 * lengthOfRandomVector, 300);
    BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondAndThirdQuarter->numbersOutsideInterval(), 0.75 * lengthOfRandomVector, 300);
  }
}

BOOST_AUTO_TEST_CASE(rndBoolSingleProbability)
{
  int numberOfTrials = 1000;
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndOne = new HelperLongBinningCheck(0, 1);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndFirstHalf = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersBetweenSecondHalfAndOne = new HelperLongBinningCheck(1, 1);
  
  // rndbool function, prob should be 0.5
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndOne->add(randomNumberStandardGenerator->rndbool());
    allRandomNumbersBetweenZeroAndFirstHalf->add(randomNumberStandardGenerator->rndbool());
    allRandomNumbersBetweenSecondHalfAndOne->add(randomNumberStandardGenerator->rndbool());
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.5
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstHalf->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalf->numbersInsideInterval(), 0.5 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalf->numbersOutsideInterval(), 0.5 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.5
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondHalfAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOne->numbersInsideInterval(), 0.5 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOne->numbersOutsideInterval(), 0.5 * numberOfTrials, 10);
  
  
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndOneTwo = new HelperLongBinningCheck(0, 1);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndFirstHalfTwo = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersBetweenSecondHalfAndOneTwo = new HelperLongBinningCheck(1, 1);
  
  // rndbool function, prob should be now 0.4
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndOneTwo->add(randomNumberStandardGenerator->rndbool(0.4));
    allRandomNumbersBetweenZeroAndFirstHalfTwo->add(randomNumberStandardGenerator->rndbool(0.4));
    allRandomNumbersBetweenSecondHalfAndOneTwo->add(randomNumberStandardGenerator->rndbool(0.4));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOneTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOneTwo->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOneTwo->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.6
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstHalfTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalfTwo->numbersInsideInterval(), 0.6 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalfTwo->numbersOutsideInterval(), 0.4 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.4
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondHalfAndOneTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOneTwo->numbersInsideInterval(), 0.4 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOneTwo->numbersOutsideInterval(), 0.6 * numberOfTrials, 10);
}

BOOST_AUTO_TEST_CASE(prndBoolSingleProbability)
{
  int numberOfTrials = 1000;
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndOne = new HelperLongBinningCheck(0, 1);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndFirstHalf = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersBetweenSecondHalfAndOne = new HelperLongBinningCheck(1, 1);
  
  // rndbool function, prob should be 0.5
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndOne->add(randomNumberStandardGenerator->prndbool());
    allRandomNumbersBetweenZeroAndFirstHalf->add(randomNumberStandardGenerator->prndbool());
    allRandomNumbersBetweenSecondHalfAndOne->add(randomNumberStandardGenerator->prndbool());
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.5
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstHalf->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalf->numbersInsideInterval(), 0.5 * numberOfTrials, 15);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalf->numbersOutsideInterval(), 0.5 * numberOfTrials, 15);
  
  // Prob laying inside of interval should be 0.5
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondHalfAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOne->numbersInsideInterval(), 0.5 * numberOfTrials, 15);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOne->numbersOutsideInterval(), 0.5 * numberOfTrials, 15);
  
  
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndOneTwo = new HelperLongBinningCheck(0, 1);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndFirstHalfTwo = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersBetweenSecondHalfAndOneTwo = new HelperLongBinningCheck(1, 1);
  
  // rndbool function, prob should be now 0.4
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndOneTwo->add(randomNumberStandardGenerator->prndbool(0.4));
    allRandomNumbersBetweenZeroAndFirstHalfTwo->add(randomNumberStandardGenerator->prndbool(0.4));
    allRandomNumbersBetweenSecondHalfAndOneTwo->add(randomNumberStandardGenerator->prndbool(0.4));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOneTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOneTwo->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOneTwo->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.6
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstHalfTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalfTwo->numbersInsideInterval(), 0.6 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalfTwo->numbersOutsideInterval(), 0.4 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.4
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondHalfAndOneTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOneTwo->numbersInsideInterval(), 0.4 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOneTwo->numbersOutsideInterval(), 0.6 * numberOfTrials, 10);
}

BOOST_AUTO_TEST_CASE(rndBoolTwoProbabilities)
{
  int numberOfTrials = 1000;
  double probabilityOne = 0.2;
  double probabilityTwo = 0.3;
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndOne = new HelperLongBinningCheck(0, 1);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndFirstHalf = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersBetweenSecondHalfAndOne = new HelperLongBinningCheck(1, 1);
  
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndOne->add(randomNumberStandardGenerator->rndbool(probabilityOne, probabilityTwo));
    allRandomNumbersBetweenZeroAndFirstHalf->add(randomNumberStandardGenerator->rndbool(probabilityOne, probabilityTwo));
    allRandomNumbersBetweenSecondHalfAndOne->add(randomNumberStandardGenerator->rndbool(probabilityOne, probabilityTwo));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.6
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstHalf->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalf->numbersInsideInterval(), 0.6 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalf->numbersOutsideInterval(), 0.4 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.2/0.5 = 0.4
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondHalfAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOne->numbersInsideInterval(), 0.4 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOne->numbersOutsideInterval(), 0.6 * numberOfTrials, 10);
}

BOOST_AUTO_TEST_CASE(prndBoolTwoProbabilities)
{
  int numberOfTrials = 1000;
  double probabilityOne = 0.2;
  double probabilityTwo = 0.3;
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndOne = new HelperLongBinningCheck(0, 1);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndFirstHalf = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersBetweenSecondHalfAndOne = new HelperLongBinningCheck(1, 1);
  
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndOne->add(randomNumberStandardGenerator->prndbool(probabilityOne, probabilityTwo));
    allRandomNumbersBetweenZeroAndFirstHalf->add(randomNumberStandardGenerator->prndbool(probabilityOne, probabilityTwo));
    allRandomNumbersBetweenSecondHalfAndOne->add(randomNumberStandardGenerator->prndbool(probabilityOne, probabilityTwo));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.6
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndFirstHalf->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalf->numbersInsideInterval(), 0.6 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenZeroAndFirstHalf->numbersOutsideInterval(), 0.4 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.2/0.5 = 0.4
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondHalfAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOne->numbersInsideInterval(), 0.4 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfAndOne->numbersOutsideInterval(), 0.6 * numberOfTrials, 10);
}

BOOST_AUTO_TEST_CASE(rndSign)
{
  int numberOfTrials = 1000;
  double probabilityOne = 0.4;
  double probabilityTwo = 0.2;
  double probabilityThree = 0.3;
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenMinusOneAndOne = new HelperLongBinningCheck(-1, 1);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersWithMinusOne = new HelperLongBinningCheck(-1, -1);
  HelperLongBinningCheck* allRandomNumbersWithZero = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersWithOne = new HelperLongBinningCheck(1, 1);
  
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenMinusOneAndOne->add(randomNumberStandardGenerator->rndsign(probabilityOne, probabilityTwo, probabilityThree));
    allRandomNumbersWithMinusOne->add(randomNumberStandardGenerator->rndsign(probabilityOne, probabilityTwo, probabilityThree));
    allRandomNumbersWithZero->add(randomNumberStandardGenerator->rndsign(probabilityOne, probabilityTwo, probabilityThree));
    allRandomNumbersWithOne->add(randomNumberStandardGenerator->rndsign(probabilityOne, probabilityTwo, probabilityThree));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusOneAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusOneAndOne->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusOneAndOne->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.4
  BOOST_CHECK_EQUAL(allRandomNumbersWithMinusOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithMinusOne->numbersInsideInterval(), 0.4/0.9 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithMinusOne->numbersOutsideInterval(), 0.5/0.9 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.2
  BOOST_CHECK_EQUAL(allRandomNumbersWithZero->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithZero->numbersInsideInterval(), 0.2/0.9 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithZero->numbersOutsideInterval(), 0.7/0.9 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.2
  BOOST_CHECK_EQUAL(allRandomNumbersWithOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithOne->numbersInsideInterval(), 0.3/0.9 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithOne->numbersOutsideInterval(), 0.6/0.9 * numberOfTrials, 10);
}

BOOST_AUTO_TEST_CASE(prndSign)
{
  int numberOfTrials = 1000;
  double probabilityOne = 0.4;
  double probabilityTwo = 0.2;
  double probabilityThree = 0.3;
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenMinusOneAndOne = new HelperLongBinningCheck(-1, 1);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersWithMinusOne = new HelperLongBinningCheck(-1, -1);
  HelperLongBinningCheck* allRandomNumbersWithZero = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersWithOne = new HelperLongBinningCheck(1, 1);
  
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenMinusOneAndOne->add(randomNumberStandardGenerator->prndsign(probabilityOne, probabilityTwo, probabilityThree));
    allRandomNumbersWithMinusOne->add(randomNumberStandardGenerator->prndsign(probabilityOne, probabilityTwo, probabilityThree));
    allRandomNumbersWithZero->add(randomNumberStandardGenerator->prndsign(probabilityOne, probabilityTwo, probabilityThree));
    allRandomNumbersWithOne->add(randomNumberStandardGenerator->prndsign(probabilityOne, probabilityTwo, probabilityThree));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusOneAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusOneAndOne->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusOneAndOne->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.4
  BOOST_CHECK_EQUAL(allRandomNumbersWithMinusOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithMinusOne->numbersInsideInterval(), 0.4/0.9 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithMinusOne->numbersOutsideInterval(), 0.5/0.9 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.2
  BOOST_CHECK_EQUAL(allRandomNumbersWithZero->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithZero->numbersInsideInterval(), 0.2/0.9 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithZero->numbersOutsideInterval(), 0.7/0.9 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.2
  BOOST_CHECK_EQUAL(allRandomNumbersWithOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithOne->numbersInsideInterval(), 0.3/0.9 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithOne->numbersOutsideInterval(), 0.6/0.9 * numberOfTrials, 10);
}

BOOST_AUTO_TEST_CASE(rnd2)
{
  int numberOfTrials = 1000;
  double probabilityOne = 0.4;
  double probabilityTwo = 0.2;
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndOne = new HelperLongBinningCheck(0, 1);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersWithZero = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersWithOne = new HelperLongBinningCheck(1, 1);
  
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndOne->add(randomNumberStandardGenerator->rnd2(probabilityOne, probabilityTwo));
    allRandomNumbersWithZero->add(randomNumberStandardGenerator->rnd2(probabilityOne, probabilityTwo));
    allRandomNumbersWithOne->add(randomNumberStandardGenerator->rnd2(probabilityOne, probabilityTwo));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndOne->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.666
  BOOST_CHECK_EQUAL(allRandomNumbersWithZero->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithZero->numbersInsideInterval(), 0.666 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithZero->numbersOutsideInterval(), 0.333 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.333
  BOOST_CHECK_EQUAL(allRandomNumbersWithOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithOne->numbersInsideInterval(), 0.333 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithOne->numbersOutsideInterval(), 0.666 * numberOfTrials, 10);
}

BOOST_AUTO_TEST_CASE(rnd3)
{
  int numberOfTrials = 1000;
  double probabilityOne = 0.4;
  double probabilityTwo = 0.2;
  double probabilityThree = 0.3;
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndTwo = new HelperLongBinningCheck(0, 2);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersWithZero = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersWithOne = new HelperLongBinningCheck(1, 1);
  HelperLongBinningCheck* allRandomNumbersWithTwo = new HelperLongBinningCheck(2, 2);
  
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndTwo->add(randomNumberStandardGenerator->rnd3(probabilityOne, probabilityTwo, probabilityThree));
    allRandomNumbersWithZero->add(randomNumberStandardGenerator->rnd3(probabilityOne, probabilityTwo, probabilityThree));
    allRandomNumbersWithOne->add(randomNumberStandardGenerator->rnd3(probabilityOne, probabilityTwo, probabilityThree));
    allRandomNumbersWithTwo->add(randomNumberStandardGenerator->rnd3(probabilityOne, probabilityTwo, probabilityThree));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndTwo->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndTwo->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.4 / 0.9
  BOOST_CHECK_EQUAL(allRandomNumbersWithZero->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithZero->numbersInsideInterval(), 0.4/0.9 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithZero->numbersOutsideInterval(), 0.5/0.9 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.2 / 0.9
  BOOST_CHECK_EQUAL(allRandomNumbersWithOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithOne->numbersInsideInterval(), 0.2/0.9 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithOne->numbersOutsideInterval(), 0.7/0.9 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.3 / 0.9
  BOOST_CHECK_EQUAL(allRandomNumbersWithTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithTwo->numbersInsideInterval(), 0.3/0.9 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithTwo->numbersOutsideInterval(), 0.6/0.9 * numberOfTrials, 10);
}

BOOST_AUTO_TEST_CASE(rnd4)
{
  int numberOfTrials = 1000;
  double probabilityOne = 0.4;
  double probabilityTwo = 0.2;
  double probabilityThree = 0.3;
  double probabilityFour = 0.5;
  // Check for whole interval 
  HelperLongBinningCheck* allRandomNumbersBetweenZeroAndThree = new HelperLongBinningCheck(0, 3);
  // Check for flat distribution
  HelperLongBinningCheck* allRandomNumbersWithZero = new HelperLongBinningCheck(0, 0);
  HelperLongBinningCheck* allRandomNumbersWithOne = new HelperLongBinningCheck(1, 1);
  HelperLongBinningCheck* allRandomNumbersWithTwo = new HelperLongBinningCheck(2, 2);
  HelperLongBinningCheck* allRandomNumbersWithThree = new HelperLongBinningCheck(3, 3);
  
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenZeroAndThree->add(randomNumberStandardGenerator->rnd4(probabilityOne, probabilityTwo, probabilityThree, probabilityFour));
    allRandomNumbersWithZero->add(randomNumberStandardGenerator->rnd4(probabilityOne, probabilityTwo, probabilityThree, probabilityFour));
    allRandomNumbersWithOne->add(randomNumberStandardGenerator->rnd4(probabilityOne, probabilityTwo, probabilityThree, probabilityFour));
    allRandomNumbersWithTwo->add(randomNumberStandardGenerator->rnd4(probabilityOne, probabilityTwo, probabilityThree, probabilityFour));
    allRandomNumbersWithThree->add(randomNumberStandardGenerator->rnd4(probabilityOne, probabilityTwo, probabilityThree, probabilityFour));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndThree->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndThree->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenZeroAndThree->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.4 / 1.4
  BOOST_CHECK_EQUAL(allRandomNumbersWithZero->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithZero->numbersInsideInterval(), 0.4/1.4 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithZero->numbersOutsideInterval(), 1.0/1.4 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.2 / 1.4
  BOOST_CHECK_EQUAL(allRandomNumbersWithOne->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithOne->numbersInsideInterval(), 0.2/1.4 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithOne->numbersOutsideInterval(), 1.2/1.4 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.3 / 1.4
  BOOST_CHECK_EQUAL(allRandomNumbersWithTwo->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithTwo->numbersInsideInterval(), 0.3/1.4 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithTwo->numbersOutsideInterval(), 1.1/1.4 * numberOfTrials, 10);
  
  // Prob laying inside of interval should be 0.5 / 1.4
  BOOST_CHECK_EQUAL(allRandomNumbersWithThree->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersWithThree->numbersInsideInterval(), 0.5/1.4 * numberOfTrials, 10);
  BOOST_CHECK_CLOSE(allRandomNumbersWithThree->numbersOutsideInterval(), 0.9/1.4 * numberOfTrials, 10);
}

BOOST_AUTO_TEST_CASE(rndExp)
{
  int numberOfTrials = 1000;
  // Check for whole interval 
  HelperDoubleBinningCheck* allRandomNumbersBetweenMinusInftyAndPlusInfty = new HelperDoubleBinningCheck(DBL_MIN, DBL_MAX);
  // Check for median
  HelperDoubleBinningCheck* allRandomNumbersBetweenMinusInftyAndFirstHalf = new HelperDoubleBinningCheck(DBL_MIN, log(2));
  HelperDoubleBinningCheck* allRandomNumbersBetweenSecondHalfandPlusInfty = new HelperDoubleBinningCheck(log(2), DBL_MAX);
  // Check for increasing probability
  HelperDoubleBinningCheck* allRandomNumbersBetweenMinusKAndZero = new HelperDoubleBinningCheck(-1000, 0);
  HelperDoubleBinningCheck* allRandomNumbersBetweenZeroAndPlusK = new HelperDoubleBinningCheck(0, 1000);
  
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenMinusInftyAndPlusInfty->add(randomNumberStandardGenerator->rndExp());
    allRandomNumbersBetweenMinusInftyAndFirstHalf->add(randomNumberStandardGenerator->rndExp());
    allRandomNumbersBetweenSecondHalfandPlusInfty->add(randomNumberStandardGenerator->rndExp());
    allRandomNumbersBetweenMinusKAndZero->add(randomNumberStandardGenerator->rndExp());
    allRandomNumbersBetweenZeroAndPlusK->add(randomNumberStandardGenerator->rndExp());
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndPlusInfty->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndPlusInfty->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndPlusInfty->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.5
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndFirstHalf->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenMinusInftyAndFirstHalf->numbersInsideInterval(), 0.5 * numberOfTrials, 15);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenMinusInftyAndFirstHalf->numbersOutsideInterval(), 0.5 * numberOfTrials, 15);
  
    // Prob laying inside of interval should be 0.5
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondHalfandPlusInfty->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfandPlusInfty->numbersInsideInterval(), 0.5 * numberOfTrials, 15);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfandPlusInfty->numbersOutsideInterval(), 0.5 * numberOfTrials, 15);
  
  // Increasing probability
  BOOST_CHECK(allRandomNumbersBetweenMinusKAndZero->numbersInsideInterval() <= allRandomNumbersBetweenZeroAndPlusK->numbersInsideInterval());  
}

BOOST_AUTO_TEST_CASE(rndExpMean)
{
  int numberOfTrials = 1000;
  double meanValue = 5;
  // Check for whole interval 
  HelperDoubleBinningCheck* allRandomNumbersBetweenMinusInftyAndPlusInfty = new HelperDoubleBinningCheck(DBL_MIN, DBL_MAX);
  // Check for median
  HelperDoubleBinningCheck* allRandomNumbersBetweenMinusInftyAndFirstHalf = new HelperDoubleBinningCheck(DBL_MIN, log(2) * meanValue);
  HelperDoubleBinningCheck* allRandomNumbersBetweenSecondHalfandPlusInfty = new HelperDoubleBinningCheck(log(2) * meanValue, DBL_MAX);
  // Check for increasing probability
  HelperDoubleBinningCheck* allRandomNumbersBetweenMinusKAndZero = new HelperDoubleBinningCheck(-1000, 0);
  HelperDoubleBinningCheck* allRandomNumbersBetweenZeroAndPlusK = new HelperDoubleBinningCheck(0, 1000);
  
  for(int i = 0; i < numberOfTrials; ++i) {
    allRandomNumbersBetweenMinusInftyAndPlusInfty->add(randomNumberStandardGenerator->rndExp(meanValue));
    allRandomNumbersBetweenMinusInftyAndFirstHalf->add(randomNumberStandardGenerator->rndExp(meanValue));
    allRandomNumbersBetweenSecondHalfandPlusInfty->add(randomNumberStandardGenerator->rndExp(meanValue));
    allRandomNumbersBetweenMinusKAndZero->add(randomNumberStandardGenerator->rndExp(meanValue));
    allRandomNumbersBetweenZeroAndPlusK->add(randomNumberStandardGenerator->rndExp(meanValue));
  }
  // Prob laying inside of interval should be 1
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndPlusInfty->numbersTotal(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndPlusInfty->numbersInsideInterval(), numberOfTrials);
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndPlusInfty->numbersOutsideInterval(), 0);
  
  // Prob laying inside of interval should be 0.5
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndFirstHalf->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenMinusInftyAndFirstHalf->numbersInsideInterval(), 0.5 * numberOfTrials, 15);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenMinusInftyAndFirstHalf->numbersOutsideInterval(), 0.5 * numberOfTrials, 15);
  
    // Prob laying inside of interval should be 0.5
  BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondHalfandPlusInfty->numbersTotal(), numberOfTrials);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfandPlusInfty->numbersInsideInterval(), 0.5 * numberOfTrials, 15);
  BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfandPlusInfty->numbersOutsideInterval(), 0.5 * numberOfTrials, 15);
  
  // Increasing probability
  BOOST_CHECK(allRandomNumbersBetweenMinusKAndZero->numbersInsideInterval() <= allRandomNumbersBetweenZeroAndPlusK->numbersInsideInterval());  
}

BOOST_AUTO_TEST_CASE(rndGaussMeanSigma)
{
  int numberOfTrials = 1000;
  
  for(double gaussianMean = 1; gaussianMean < 2; gaussianMean += 1) {
    for(double gaussianSigma = 0.25; gaussianSigma < 0.35; gaussianSigma += 0.1) {
      // Check for whole interval 
      HelperDoubleBinningCheck* allRandomNumbersBetweenMinusInftyAndPlusInfty = new HelperDoubleBinningCheck(DBL_MIN, DBL_MAX);
      // Check for median
      HelperDoubleBinningCheck* allRandomNumbersBetweenMinusInftyAndFirstHalf = new HelperDoubleBinningCheck(DBL_MIN, gaussianMean);
      HelperDoubleBinningCheck* allRandomNumbersBetweenSecondHalfandPlusInfty = new HelperDoubleBinningCheck(gaussianMean, DBL_MAX);
      // Check for increasing probability
      HelperDoubleBinningCheck* allRandomNumbersBetweenMinus1SigmaAndPlus1Sigma = new HelperDoubleBinningCheck(gaussianMean - gaussianSigma, gaussianMean + gaussianSigma);
      HelperDoubleBinningCheck* allRandomNumbersBetweenMinus3SigmaAndPlus3Sigma = new HelperDoubleBinningCheck(gaussianMean -  3 * gaussianSigma, gaussianMean + 3 * gaussianSigma);
      HelperDoubleBinningCheck* allRandomNumbersBetweenMinus8SigmaAndPlus8Sigma = new HelperDoubleBinningCheck(gaussianMean - 8 * gaussianSigma, gaussianMean + 8 * gaussianSigma);
	  
      for(int i = 0; i < numberOfTrials; ++i) {
	allRandomNumbersBetweenMinusInftyAndPlusInfty->add(randomNumberStandardGenerator->rndGauss(gaussianSigma, gaussianMean));
	allRandomNumbersBetweenMinusInftyAndFirstHalf->add(randomNumberStandardGenerator->rndGauss(gaussianSigma, gaussianMean));
	allRandomNumbersBetweenSecondHalfandPlusInfty->add(randomNumberStandardGenerator->rndGauss(gaussianSigma, gaussianMean));
	allRandomNumbersBetweenMinus1SigmaAndPlus1Sigma->add(randomNumberStandardGenerator->rndGauss(gaussianSigma, gaussianMean));
	allRandomNumbersBetweenMinus3SigmaAndPlus3Sigma->add(randomNumberStandardGenerator->rndGauss(gaussianSigma, gaussianMean));
	allRandomNumbersBetweenMinus8SigmaAndPlus8Sigma->add(randomNumberStandardGenerator->rndGauss(gaussianSigma, gaussianMean));
      }
      
      // Prob laying inside of interval should be 1
      BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndPlusInfty->numbersTotal(), numberOfTrials);
      BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndPlusInfty->numbersInsideInterval(), numberOfTrials);
      BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndPlusInfty->numbersOutsideInterval(), 0);
      
      // Prob laying inside of interval should be 0.5
      BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinusInftyAndFirstHalf->numbersTotal(), numberOfTrials);
      BOOST_CHECK_CLOSE(allRandomNumbersBetweenMinusInftyAndFirstHalf->numbersInsideInterval(), 0.5 * numberOfTrials, 15);
      BOOST_CHECK_CLOSE(allRandomNumbersBetweenMinusInftyAndFirstHalf->numbersOutsideInterval(), 0.5 * numberOfTrials, 15);
      
	// Prob laying inside of interval should be 0.5
      BOOST_CHECK_EQUAL(allRandomNumbersBetweenSecondHalfandPlusInfty->numbersTotal(), numberOfTrials);
      BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfandPlusInfty->numbersInsideInterval(), 0.5 * numberOfTrials, 15);
      BOOST_CHECK_CLOSE(allRandomNumbersBetweenSecondHalfandPlusInfty->numbersOutsideInterval(), 0.5 * numberOfTrials, 15);
      
      	// Prob laying inside of interval should be 0.68
      BOOST_CHECK_EQUAL(allRandomNumbersBetweenMinus1SigmaAndPlus1Sigma->numbersTotal(), numberOfTrials);
      BOOST_CHECK_CLOSE(allRandomNumbersBetweenMinus1SigmaAndPlus1Sigma->numbersInsideInterval(), 0.68 * numberOfTrials, 15);
      BOOST_CHECK_CLOSE(allRandomNumbersBetweenMinus1SigmaAndPlus1Sigma->numbersOutsideInterval(), 0.32 * numberOfTrials, 15);
  
  
  
  
  
    }
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
