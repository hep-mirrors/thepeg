// -*- C++ -*-
#ifndef LWH_DataPointSet_H
#define LWH_DataPointSet_H
//
// This is the declaration of the DataPointSet class representing
//


#include <limits>
#include <cmath>
#include <algorithm>
#include "AIDataPointSet.h"
#include "ManagedObject.h"

namespace LWH {

using namespace AIDA;

/**
 * An DataPointSet represents a binned histogram axis. A 1D Histogram would have
 * one DataPointSet representing the X axis, while a 2D Histogram would have two
 * axes representing the X and Y DataPointSet.
 */
class DataPointSet: public IDataPointSet, public ManagedObject {

public: 
  /**
   * Destructor.
   */
  virtual ~IDataPointSet() {}

  /**
   * Not implemented in LWH. will throw an exception.
   */
  IAnnotation & annotation() {
    throw std::runtime_error("LWH cannot handle annotations");
    return *anno;
  }

  /**
   * Not implemented in LWH. will throw an exception.
   */
  const IAnnotation & annotation() const {
    throw std::runtime_error("LWH cannot handle annotations");
    return *anno;
  }

  /**
   * Get the Histogram's title.
   * @return The Histogram's title.
   */
  std::string title() const {
    return theTitle;
  }

  /**
   * Get the Histogram's title.
   * @return The Histogram's title.
   */
  std::string name() const {
    return theTitle;
  }

  /**
   * Set the histogram title.
   * @param title The title.
   * @return false If title cannot be changed.
   */
  bool setTitle(const std::string & title) {
    theTitle = title;
    return true;
  }

  /**
   * Get the dimension of the IDataPoints that can be stored in the set.
   * @return The dimension of the IDataPoints storable in the set.
   *
   */
  virtual int dimension() const {
    if ( dset.empty() ) return 0;
    return dset[0].dimension();
  }

  /**
   * Remove all the IDataPoints in the set.
   * After this the IDataPointSet is as just created.
   */
  virtual void clear() {
    dset.clear();
  }

  /**
   * Get the current size of the IDataPointSet, i.e. the number
   * of IDataPoints contained in the set.
   * @return The size of the IDataPointSet.
   */
  virtual int size() const {
    return dset.size();
  }

  /**
   * Get the IDataPoint at a give index in the set.
   * @param index The IDataPoint index.
   * @return      The corresponding IDataPoint.
   */
  virtual IDataPoint * point(int index) = {
    return &(dset[index]);
  }

  /**
   * Set the values and errors of a given coordinate all at once.  If
   * this method is called on an empty IDataPointSet, a number of
   * points equal to the size of the arrays provided is created; if
   * the IDataPointSet is not empty the dimension of the array must
   * match with the size of the IDataPointSet.
   * @param coord The coordinate's index
   * @param val   The array of the values for the given coordinate
   * @param err   The array with the symmetric errors.

   * @return false if an illegal coordinate is provided or if there is
   *      a mismatch between the size of the array and the size of the
   *      IDataPointSet.
   */
  virtual bool setCoordinate(int coord,
			     const std::vector<double>  & val,
			     const std::vector<double>  & err) {
    if ( coord < 0 || coord >= dset.size() ) return false;
    DataPoint & dp = dset[coord];
    if ( dp.dimension() && ( dp.dimension() != val.size() ||
			     dp.dimension() != err.size() ) )
      return false;
    dp = DataPoint(val.size());
    for ( int i = 0, N = val.size(); i < N; ++i ) {
      dp.coordinate(i)->setValue(val[i]);
      dp.coordinate(i)->setErrorPlus(err[i]);
      dp.coordinate(i)->setErrorMinus(err[i]);
    }
    return true;
  }

  /**
   * Set the values and errors of a given coordinate all at once.  If
   * this method is called on an empty IDataPointSet, a number of
   * points equal to the size of the arrays provided is created; if
   * the IDataPointSet is not empty the dimension of the array must
   * match with the size of the IDataPointSet.
   * @param coord The coordinate's index
   * @param val   The array of the values for the given coordinate
   * @param errp  The array with the plus errors.
   * @param errm  The array with the minus errors.
   * @return false if an illegal coordinate is provided or if there is
   *     a mismatch between the size of the array and the size of the
   *     IDataPointSet.
   *
   */
  virtual bool setCoordinate(int coord,
			     const std::vector<double>  & val,
			     const std::vector<double>  & errp,
			     const std::vector<double>  & errm) {
    if ( coord < 0 || coord >= dset.size() ) return false;
    DataPoint & dp = dset[coord];
    if ( dp.dimension() && ( dp.dimension() != val.size() ||
			     dp.dimension() != errp.size()
			     dp.dimension() != errm.size() ) )
      return false;
    dp = DataPoint(val.size());
    for ( int i = 0, N = val.size(); i < N; ++i ) {
      dp.coordinate(i)->setValue(val[i]);
      dp.coordinate(i)->setErrorPlus(errp[i]);
      dp.coordinate(i)->setErrorMinus(errm[i]);
    }
    return true;
  }

  /**
   * Return the data point at the given index.
   * @return 0 if index is out of range.
   */
  virtual const IDataPoint * point(int index) const {
    if ( index < 0 || index >= dset.size() ) return 0;
    return &(dset[coord]);
  }

  /**
   * Add a new empty IDataPoint at the end of the set.
   * @return The newly added point.
   */
  virtual IDataPoint * addPoint() {
    dset.push_back(DataPoint(0));
    return &(dset.back());
  }

  /**
   * Add a copy of an IDataPoint at the end of the set.
   * @param point The IDataPoint to be added.
   * @return false If the point has the wrong dimension or
   *                                       if the point cannot be added.
   */
  virtual bool addPoint(const IDataPoint & point) {
    if ( dimension() && dimension() != point.dimension() ) return false;
    dset.push_back(DataPoint(point));
    return true;
  }

  /**
   * Remove the IDataPoint at a given index.
   * @param index The index of the IDataPoint to be removed.
   * @return false If the index is < 0 or >= size().
   */
  virtual bool removePoint(int index) {
    if ( index < 0 || index >= dset.size() ) return false;
    dset.erase(dset.begin() + index);
  }

  /**
   * Get the lower value for a give axis.
   * @param coord The coordinate of the axis.
   * @return      The lower edge of the corresponding axis.
   *              If coord < 0 or coord >= dimension(), or if the
   *              set is empty NaN is returned.
   */
  virtual double lowerExtent(int coord) const {
    if ( dset.empty() ) return std::numeric_limits<double>::quiet_NaN();
    if ( coord < 0 || coord >= dimension() )
      return std::numeric_limits<double>::quiet_NaN();
    double low = dset[0].coordinate(coord)->value();
    for ( int i = 1, N = dset.size(); i < N; ++i )
      low = std::min(low, dset[i].coordinate(coord)->value());
    return low;
  }

  /**
   * Get the upper value for a give axis.
   * @param coord The coordinate of the axis.
   * @return      The upper edge of the corresponding axis.
   *              If coord < 0 or coord >= dimension(), or if the set
   *              is empty NaN is returned.
   */
  virtual double upperExtent(int coord) const {
    if ( dset.empty() ) return std::numeric_limits<double>::quiet_NaN();
    if ( coord < 0 || coord >= dimension() )
      return std::numeric_limits<double>::quiet_NaN();
    double upp = dset[0].coordinate(coord)->value();
    for ( int i = 1, N = dset.size(); i < N; ++i )
      upp = std::max(upp, dset[i].coordinate(coord)->value());
    return upp;
  }

  /**
   * Scales the values and the errors of all the measurements
   * of each point by a given factor.
   * @param scale The scale factor.
   * @return false If an illegal scaleFactor is provided.
   */
  virtual bool scale(double scale) {
    for ( int i = 0, N = dset.size(); i < N; ++i )
      for ( int j = 0, M = dset[i].dimension(); j < M; ++j ) {
	IMeasurement * m = dset[i].coordinate(j);
	m->setValue(m->value()*scale);
	m->setErrorPlus(m->errorPlus()*scale);
	m->setErrorMinus(m->errorPlus()*scale);
      }
    return true;
  }
	
  /**
   * Scales the values of all the measurements
   * of each point by a given factor.
   * @param scale The scale factor.
   * @return false If an illegal scaleFactor is provided.
   */
  virtual bool scaleValues(double scale) {
    for ( int i = 0, N = dset.size(); i < N; ++i )
      for ( int j = 0, M = dset[i].dimension(); j < M; ++j ) {
	IMeasurement * m = dset[i].coordinate(j);
	m->setValue(m->value()*scale);
      }
    return true;
  }

  /**
   * Scales the errors of all the measurements
   * of each point by a given factor.
   * @param scale The scale factor.
   * @return false If an illegal scaleFactor is provided.
   */
  virtual bool scaleErrors(double scale) {
    for ( int i = 0, N = dset.size(); i < N; ++i )
      for ( int j = 0, M = dset[i].dimension(); j < M; ++j ) {
	IMeasurement * m = dset[i].coordinate(j);
	m->setErrorPlus(m->errorPlus()*scale);
	m->setErrorMinus(m->errorPlus()*scale);
      }
    return true;
  }

  /**
   * Not implemented in LWH.
   * @return null pointer always.
   */ 
  void * cast(const std::string & className) const {
    return 0;
  }

private:

  /**
   * The included data points.
   */
  vector<DataPoint> dset;

  /** dummy pointer to non-existen annotation. */
  IAnnotation * anno;

};

}

#endif /* LWH_DataPointSet_H */
