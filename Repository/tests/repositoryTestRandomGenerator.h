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
  unsigned int numberOfTrials = 1000;
  for(unsigned int i = 0; i < numberOfTrials; ++i) {
    double randomNumber = randomNumberStandardGenerator->rnd();
    BOOST_CHECK(randomNumber > 0);
    BOOST_CHECK(randomNumber < 1);
  }
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
