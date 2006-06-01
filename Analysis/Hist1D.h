// -*- C++ -*-
#ifndef LWH_Hist1D_H
#define LWH_Hist1D_H
//
// This is the declaration of the Hist1D class.
//

#include "AIHistogram1D.h"
#include "Axis.h"
#include <vector>
#include <stdexcept>

namespace LWH {

using namespace AIDA;

/**
 * User level interface to 1D Histogram.
 */
class Hist1D: public IHistogram1D {

public:

  /** HistFactory is a friend. */
  friend class HistFactory;

public:

  /**
   * Standard constructor.
   */
  Hist1D(int n, double lo, double up)
    : ax(n, lo, up), sum(n + 2), sumw(n + 2), sumw2(n + 2) {}

  /**
   * Constructor form Axis object.
   */
  Hist1D(const Axis & a)
    : ax(a.bins(), a.lowerEdge(), a.upperEdge()),
      sum(a.bins() + 2), sumw(a.bins() + 2), sumw2(a.bins() + 2) {}

  /**
   * Copy constructor.
   */
  Hist1D(const Hist1D & h)
    : ax(h.ax), sum(h.sum), sumw(h.sumw), sumw2(h.sumw2) {}

  /// Destructor.
  virtual ~Hist1D() {}

  /**
   * Get the Histogram's title.
   * @return The Histogram's title.
   */
  std::string title() const {
    return name;
  }

  /**
   * Set the histogram title.
   * @param title The title.
   * @return false If title cannot be changed.
   */
  bool setTitle(const std::string & title) {
    name = title;
    return true;
  }

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
   * Get the Histogram's dimension.
   * @return The Histogram's dimension.
   */ 
  int dimension() const {
    return 1;
  }

  /**
   * Reset the Histogram; as if just created.
   * @return false If something goes wrong.
   */
  bool reset() {
    sum = std::vector<int>(ax.bins());
    sumw = std::vector<double>(ax.bins());
    sumw2 = std::vector<double>(ax.bins());
    return true;
  }

  /**
   * Get the number of in-range entries in the Histogram.
   * @return The number of in-range entries.
   *
   */ 
  int entries() const {
    int si = 0;
    for ( int i = 2; i < ax.bins() + 2; ++i ) si += sum[i];
    return si;
  }

  /**
   * Sum of the entries in all the IHistogram's bins,
   * i.e in-range bins, UNDERFLOW and OVERFLOW.
   * This is equivalent to the number of times the
   * method fill was invoked.
   * @return The sum of all the entries.
   */
  int allEntries() const {
    return entries() + extraEntries();
  }

  /**
   * Number of entries in the UNDERFLOW and OVERFLOW bins.
   * @return The number of entries outside the range of the IHistogram.
   */
  int extraEntries() const {
    return sum[0] + sum[1];
  }

  /**
   * Number of equivalent entries,
   * i.e. <tt>SUM[ weight ] ^ 2 / SUM[ weight^2 ]</tt>
   * @return The number of equivalent entries.
   */
  double equivalentBinEntries() const {
    double sw = 0.0;
    double sw2 = 0.0;
    for ( int i = 2; i < ax.bins() + 2; ++i ) {
      sw += sumw[i];
      sw2 += sumw2[i];
    }
    return sw2/(sw*sw);
  }
    
  /**
   * Sum of in-range bin heights in the IHistogram,
   * UNDERFLOW and OVERFLOW bins are excluded.
   * @return The sum of the in-range bins heights.
   *
   */
  double sumBinHeights() const {
    double sw = 0.0;
    for ( int i = 2; i < ax.bins() + 2; ++i ) sw += sumw[i];
    return sw;
  }
    
  /**
   * Sum of the heights of all the IHistogram's bins,
   * i.e in-range bins, UNDERFLOW and OVERFLOW.
   * @return The sum of all the bins heights.
   */
  double sumAllBinHeights() const {
    return sumBinHeights() + sumExtraBinHeights();
  }

  /**
   * Sum of heights in the UNDERFLOW and OVERFLOW bins.
   * @return The sum of the heights of the out-of-range bins.
   */
  double sumExtraBinHeights() const {
    return sumw[0] + sumw[1];
  }

  /**
   * Minimum height of the in-range bins,
   * i.e. not considering the UNDERFLOW and OVERFLOW bins.
   * @return The minimum height among the in-range bins.
   */
  double minBinHeight() const {
    double minw = sumw[2];
    for ( int i = 3; i < ax.bins() + 2; ++i ) minw = std::min(minw, sumw[i]);
    return minw;
  }

  /**
   * Maximum height of the in-range bins,
   * i.e. not considering the UNDERFLOW and OVERFLOW bins.
   * @return The maximum height among the in-range bins.
   */
  double maxBinHeight() const{
    double maxw = sumw[2];
    for ( int i = 3; i < ax.bins() + 2; ++i ) maxw = std::max(maxw, sumw[i]);
    return maxw;
  }

  /**
   * Fill the IHistogram1D with a value and the
   * corresponding weight.
   * @param x      The value to be filled in.
   * @param weight The corresponding weight (by default 1).
   * @return false If the weight is <0 or >1 (?).
   */
  bool fill(double x, double weight = 1.) {
    int i = ax.coordToIndex(x) + 2;
    ++sum[i];
    sumw[i] += weight;
    sumw2[i] += weight*weight;
    return weight >= 0 && weight <= 1;
  }

  /**
   * The weighted mean of a bin. 
   * @param index The bin number (0...N-1) or OVERFLOW or UNDERFLOW.
   * @return      The mean of the corresponding bin.
   */
  double binMean(int index) const {
    return sumw[index + 2]/double(std::max(sum[index + 2], 1));
  };

  /**
   * Number of entries in the corresponding bin (ie the number of
   * times fill was called for this bin).
   * @param index The bin number (0...N-1) or OVERFLOW or UNDERFLOW.
   * @return      The number of entries in the corresponding bin. 
   */
  int binEntries(int index) const {
    return sum[index + 2];
  }

  /**
   * Total height of the corresponding bin (ie the sum of the weights
   * in this bin).
   * @param index The bin number (0...N-1) or OVERFLOW or UNDERFLOW.
   * @return      The height of the corresponding bin.
   */
  double binHeight(int index) const {
    return sumw[index + 2];
  }

  /**
   * The error of a given bin.
   * @param index The bin number (0...N-1) or OVERFLOW or UNDERFLOW.
   * @return      The error on the corresponding bin.
   *
   */
  double binError(int index) const {
    return sqrt(sumw2[index + 2]);
  }

  /**
   * The mean of the whole IHistogram1D.
   * @return The mean of the IHistogram1D.
   */
  double mean() const {
    double s = 0.0;
    double sx = 0.0;
    for ( int i = 2; i < ax.bins() + 2; ++i ) {
      s += sumw[i];
      sx += ax.binMidPoint(i - 2)*sumw[i];
    }
    return sx/std::max(s, 1.0);
  }

  /**
   * The RMS of the whole IHistogram1D.
   * @return The RMS if the IHistogram1D.
   */
  double rms() const {
    double s = 0.0;
    double sx = 0.0;
    double sx2 = 0.0;
    for ( int i = 2; i < ax.bins() + 2; ++i ) {
      double x = ax.binMidPoint(i - 2);
      s += sumw[i];
      sx += x*sumw[i];
      sx2 += x*x*sumw[i];
    }
    return sqrt(s*sx2 - sx*sx)/std::max(s, 1.0);
  }

  /**
   * Get the x axis of the IHistogram1D.
   * @return The x coordinate IAxis.
   */
  const IAxis & axis() const {
    return ax;
  }

  /**
   * Get the bin number corresponding to a given coordinate along the
   * x axis.  This is a convenience method, equivalent to
   * <tt>axis().coordToIndex(coord)</tt>.
   * @param coord The coordinalte along the x axis.
   * @return      The corresponding bin number.
   */
  int coordToIndex(double coord) const {
    return ax.coordToIndex(coord);
  }
  
  /**
   * Add to this Hist1D the contents of another IHistogram1D.
   * @param h The Hist1D to be added to this IHistogram1D.
   * @return false If the IHistogram1Ds binnings are incompatible.
   */
  bool add(const Hist1D & h) {
    if ( ax.upperEdge() != h.ax.upperEdge() ||
	 ax.lowerEdge() != h.ax.lowerEdge() ||
	 ax.bins() != h.ax.bins() ) return false;
    for ( int i = 0; i < ax.bins() + 2; ++i ) {
      sum[i] += h.sum[i];
      sumw[i] += h.sumw[i];
      sumw2[i] += h.sumw2[i];
    }
    return true;
  }

  /**
   * Add to this IHistogram1D the contents of another IHistogram1D.
   * @param hist The IHistogram1D to be added to this IHistogram1D.
   * @return false If the IHistogram1Ds binnings are incompatible.
   */
  bool add(const IHistogram1D & hist) {
    return add(dynamic_cast<const Hist1D &>(hist));
  }

  /**
   * Scale the contents of this histogram with the given factor.
   * @param s the scaling factor to use.
   */
  bool scale(double s) {
    for ( int i = 0; i < ax.bins() + 2; ++i ) {
      sumw[i] *= s;
      sumw2[i] *= s*s;
    }
    return true;
  }

  /**
   * Return the integral of this histogram between the edges.
   */
  double integral() const {
    return sumBinHeights()*ax.binWidth(0);
  }

  /**
   * Normalize this histogram so that the integral between the edges
   * becomes \a N.
   */
  void norm(double N = 1.0) {
    scale(N/integral());
  }

  /**
   * Not implemented in LWH.
   * @return null pointer always.
   */ 
  void * cast(const std::string & className) const {
    return 0;
  }

private:

  /** The name */
  std::string name;

  /** The axis. */
  Axis ax;

  /** The counts. */
  std::vector<int> sum;

  /** The weights. */
  std::vector<double> sumw;

  /** The squared weights. */
  std::vector<double> sumw2;

  /** dummy pointer to non-existen annotation. */
  IAnnotation * anno;

};

}

#endif /* LWH_Hist1D_H */
