// -*- C++ -*-
#ifndef LWH_DataPoint_H
#define LWH_DataPoint_H
//
// This is the declaration of the DataPoint class representing
//


#include <limits>
#include <cmath>
#include <algorithm>
#include "AIDataPoint.h"
#include "Measurement.h"

namespace LWH {

using namespace AIDA;

/**
 * An DataPoint represents a binned histogram axis. A 1D Histogram would have
 * one DataPoint representing the X axis, while a 2D Histogram would have two
 * axes representing the X and Y DataPoint.
 */
class DataPoint: public IDataPoint {

public:

public:

  /**
   * Construct a data point with a given number of dimensions.
   */
  DataPoint(int dim = 2)
    : m(dim) {}

  /**
   * Copy constructor.
   */
  DataPoint(const DataPoint & d)
    : m(d.m) {}

  /**
   * Copy from any IDataPoint.
   */
  DataPoint(const IDataPoint & id)
    : m(id.dimension()) {
    for ( int i = 0, N = m.size(); i < N; ++i )
      m[i] = Measurement(id.coordinate(i)->value(),
			 id.coordinate(i)->errorPlus(),
			 id.coordinate(i)->errorMinus());
  }

  /**
   * Destructor.
   */
  virtual ~DataPoint() {}

  /**
   * Get the dimension of the IDataPoint, i.e. the number
   * of coordinates the point has.
   * @return The dimension.
   */
  virtual int dimension() const {
    m.size();
  }

  /**
   * Get the IMeasurement for a given coordinate.
   * @param coord The coordinate.
   * @return      The corresponding IMeasurement.
   */
  virtual IMeasurement * coordinate(int coord) {
    return &(m[coord]);
  }

  /**
   * Get the IMeasurement for a given coordinate.
   * @param coord The coordinate.
   * @return      The corresponding IMeasurement.
   */
  virtual const IMeasurement * coordinate(int coord) const {
    return &(m[coord]);
  }

  /**
   * The included measurements.
   */
  private std::vector<Measurement> m;

};

}

#endif /* LWH_DataPoint_H */
