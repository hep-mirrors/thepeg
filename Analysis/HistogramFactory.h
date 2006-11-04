// -*- C++ -*-
#ifndef LWH_HistogramFactory_H
#define LWH_HistogramFactory_H
//
// This is the declaration of the HistogramFactory class.
//

#include "AIHistogramFactory.h"
#include "Histogram1D.h"
#include "Tree.h"
#include <string>
#include <stdexcept>

namespace LWH {

using namespace AIDA;

/**
 * User level interface for factory classes of Histograms (binned,
 * unbinned, and profile). The created objects are assumed to be
 * managed by the tree which is associated to the factory. So far only
 * one-dimensional histograms are implemented in LWH.
 */
class HistogramFactory: public IHistogramFactory {

public:

  /**
   * Standard constructor.
   */
  HistogramFactory(Tree & t)
    : tree(&t) {}

  /**
   * Destructor.
   */
  virtual ~HistogramFactory() {}

  /**
   * Destroy an IBaseHistogram object.
   * @param hist The IBaseHistogram to be destroyed.
   * @return false If the histogram cannot be destroyed.
   */
  bool destroy(IBaseHistogram * hist) {
    IManagedObject * mo = dynamic_cast<IManagedObject *>(hist);
    if ( !mo ) return false;
    return tree->rm(tree->findPath(*mo));
  }

  /**
   * LWH cannot create a ICloud1D, an unbinned 1-dimensional histogram.
   */
  ICloud1D * createCloud1D(const std::string &, const std::string &,
			   int = -1, const std::string & = "") {
    return error<ICloud1D>("ICloud1D");
  }

  /**
   * LWH cannot create a ICloud1D, an unbinned 1-dimensional histogram.
   */
  ICloud1D * createCloud1D(const std::string &) {
    return error<ICloud1D>("ICloud1D");
  }

  /**
   * LWH cannot create a copy of an ICloud1D.
   */
  ICloud1D * createCopy(const std::string &, const ICloud1D &) {
    return error<ICloud1D>("ICloud1D");
  }

  /**
   * LWH cannot create a ICloud2D, an unbinned 2-dimensional histogram.
   */
  ICloud2D * createCloud2D(const std::string &, const std::string &, int = -1,
			   const std::string & = "") {
    return error<ICloud2D>("ICloud2D");
  }


  /**
   * LWH cannot create a ICloud2D, an unbinned 2-dimensional histogram.
   */
  ICloud2D * createCloud2D(const std::string &) {
    return error<ICloud2D>("ICloud2D");
  }

  /**
   * LWH cannot create a copy of an ICloud2D.
   */
  ICloud2D * createCopy(const std::string &, const ICloud2D &) {
    return error<ICloud2D>("ICloud2D");
  }

  /**
   * LWH cannot create a ICloud3D, an unbinned 3-dimensional histogram.
   */
  ICloud3D * createCloud3D(const std::string &, const std::string &, int = -1,
			   const std::string & = "") {
    return error<ICloud3D>("ICloud3D");
  }

  /**
   * LWH cannot create a ICloud3D, an unbinned 3-dimensional histogram.
   */
  ICloud3D * createCloud3D(const std::string &) {
    return error<ICloud3D>("ICloud3D");
  }

  /**
   * LWH cannot create a copy of an ICloud3D.
   */
  ICloud3D * createCopy(const std::string &, const ICloud3D &) {
    return error<ICloud3D>("ICloud3D");
  }

  /**
   * Create a IHistogram1D.
   * @param path      The path of the created IHistogram. The path must be a
   *                  full path.  ("/folder1/folder2/dataName" is a valid path).
   *                  The characther `/` cannot be used in names; it is only
   *                  used to delimit directories within paths.
   * @param title     The title of the IHistogram1D.
   * @param nBins     The number of bins of the x axis.
   * @param lowerEdge The lower edge of the x axis.
   * @param upperEdge The upper edge of the x axis.
   * @return          The newly created IHistogram1D ot the null pointer
   *                  if something went wrong, such as a non existing
   *                  directrory in the path or that an object with the
   *                  given path already existed.
   * @throws          std::runtime_error if histogram could not be created.
   */
  IHistogram1D *
  createHistogram1D(const std::string & path, const std::string & title,
		    int nBins, double lowerEdge, double upperEdge,
		    const std::string & = "") {
    Histogram1D * hist = new Histogram1D(nBins, lowerEdge, upperEdge);
    hist->setTitle(title);
    if ( !tree->insert(path, hist) ) {
      delete hist;
      hist = 0;
      throw std::runtime_error("LWH could not create histogram '"
			       + title + "'." );
    }
    return hist;
  }

  /**
   * Create a IHistogram1D.
   * @param pathAndTitle The path of the created IHistogram. The path must be a
   *                     full path.  ("/folder1/folder2/dataName" is a valid
   *                     path). The characther `/` cannot be used in names; it
   *                     is only used to delimit directories within paths.
   * @param nBins        The number of bins of the x axis.
   * @param lowerEdge    The lower edge of the x axis.
   * @param upperEdge    The upper edge of the x axis.
   * @return             The newly created IHistogram1D.
   * @throws             std::runtime_error if histogram could not be created.
   */
  IHistogram1D *
  createHistogram1D(const std::string & pathAndTitle,
		    int nBins, double lowerEdge, double upperEdge) {
    std::string title = pathAndTitle.substr(pathAndTitle.rfind('/') + 1);
    return createHistogram1D(pathAndTitle, title, nBins, lowerEdge, upperEdge);
  }


    /**
     * Create a IHistogram1D.

     * @param path      The path of the created IHistogram. The path can either
     *                  be a relative or full path.
     *                  ("/folder1/folder2/dataName" and "../folder/dataName"
     *                  are valid paths). All the directories in the path must
     *                  exist. The characther `/` cannot be used in names;
     *                  it is only used to delimit directories within paths.
     * @param title     The title of the IHistogram1D.
     * @param binEdges  The array of the bin edges for the x axis.
     */
  IHistogram1D *
  createHistogram1D(const std::string & path, const std::string & title,
		    const std::vector<double> & binEdges,
		    const std::string & = "") {
    Histogram1D * hist = new Histogram1D(binEdges);
    hist->setTitle(title);
    if ( !tree->insert(path, hist) ) {
      delete hist;
      hist = 0;
      throw std::runtime_error("LWH could not create histogram '"
			       + title + "'." );
    }
    return hist;
  }

  /**
   * Create a copy of an IHistogram1D.
   * @param path The path of the created IHistogram. The path must be a
   *             full path.  ("/folder1/folder2/dataName" is a valid
   *             path). The characther `/` cannot be used in names; it
   *             is only used to delimit directories within paths.
   * @param hist The IHistogram1D to be copied.
   * @return     The copy of the IHistogram1D.
   * @throws     std::runtime_error if histogram could not be created.
   */
  IHistogram1D *
  createCopy(const std::string & path, const IHistogram1D & hist) {
    Histogram1D * h = new Histogram1D(dynamic_cast<const Histogram1D &>(hist));
    h->setTitle(path.substr(path.rfind('/') + 1));
    if ( !tree->insert(path, h) ) {
      delete h;
      h = 0;
      throw std::runtime_error("LWH could not create a copy of histogram '"
			       + hist.title() + "'." );
    }
    return h;
  }

  /**
   * LWH cannot create a IHistogram2D.
   */
  IHistogram2D * createHistogram2D(const std::string &, const std::string &,
				   int, double, double, int, double, double,
				   const std::string & = "") {
    return error<IHistogram2D>("IHistogram2D");
  }

  /**
   * LWH cannot create a IHistogram2D.
   */
  IHistogram2D * createHistogram2D(const std::string &,
				   int, double, double, int, double, double) {
    return error<IHistogram2D>("IHistogram2D");
  }

  /**
   * LWH cannot create a IHistogram2D.
   */
  IHistogram2D * createHistogram2D(const std::string &, const std::string &,
				   const std::vector<double> &,
				   const std::vector<double> &,
				   const std::string & = "") {
    return error<IHistogram2D>("IHistogram2D");
  }

  /**
   * LWH cannot create a copy of an IHistogram2D.
   */
  IHistogram2D * createCopy(const std::string &, const IHistogram2D &) {
    return error<IHistogram2D>("IHistogram2D");
  }

  /**
   * LWH cannot create a IHistogram3D.
   */
  IHistogram3D * createHistogram3D(const std::string &, const std::string &,
				   int, double, double, int, double, double,
				   int, double, double,
				   const std::string & = "") {
    return error<IHistogram3D>("IHistogram3D");
  }

  /**
   * LWH cannot create a IHistogram3D.
   */
  IHistogram3D * createHistogram3D(const std::string &, int, double, double,
				   int, double, double, int, double, double) {
    return error<IHistogram3D>("IHistogram3D");
  }

  /**
   * LWH cannot create a IHistogram3D.
   */
  IHistogram3D * createHistogram3D(const std::string &, const std::string &,
				   const std::vector<double> &,
				   const std::vector<double> &,
				   const std::vector<double> &,
				   const std::string & = "") {
    return error<IHistogram3D>("IHistogram3D");
  }

  /**
   * LWH cannot create a copy of an IHistogram3D.
   */
  IHistogram3D * createCopy(const std::string &, const IHistogram3D &) {
    return error<IHistogram3D>("IHistogram3D");
  }

  /**
   * LWH cannot create a IProfile1D.
   */
  IProfile1D * createProfile1D(const std::string &, const std::string &,
			       int, double, double, const std::string & = "") {
    return error<IProfile1D>("IProfile1D");
  }

  /**
   * LWH cannot create a IProfile1D.
   */
  IProfile1D * createProfile1D(const std::string &, const std::string &,
			       int, double, double, double, double,
			       const std::string & = "") {
    return error<IProfile1D>("IProfile1D");
  }

  /**
   * LWH cannot create a IProfile1D.
   */
  IProfile1D * createProfile1D(const std::string &, const std::string &,
			       const std::vector<double> &,
			       const std::string & = "") {
    return error<IProfile1D>("IProfile1D");
  }

  /**
   * LWH cannot create a IProfile1D.
   */
  IProfile1D * createProfile1D(const std::string &, const std::string &,
			       const std::vector<double> &, double, double,
			       const std::string & = "") {
    return error<IProfile1D>("IProfile1D");
  }

  /**
   * LWH cannot create a IProfile1D.
   */
  IProfile1D * createProfile1D(const std::string &, int, double, double) {
    return error<IProfile1D>("IProfile1D");
  }

  /**
   * LWH cannot create a IProfile1D.
   */
  IProfile1D * createProfile1D(const std::string &,
			       int, double, double, double, double) {
    return error<IProfile1D>("IProfile1D");
  }

  /**
   * LWH cannot create a copy of an IProfile1D.
   */
  IProfile1D * createCopy(const std::string &, const IProfile1D &) {
    return error<IProfile1D>("IProfile1D");
  }

  /**
   * LWH cannot create a IProfile2D.
   */
  IProfile2D * createProfile2D(const std::string &, const std::string &,
			       int, double, double, int, double, double,
			       const std::string & = "") {
    return error<IProfile2D>("IProfile2D");
  }

  /**
   * LWH cannot create a IProfile2D.
   */
  IProfile2D * createProfile2D(const std::string &, const std::string &,
			       int, double, double, int,
			       double, double, double, double,
			       const std::string & = "") {
    return error<IProfile2D>("IProfile2D");
  }

  /**
   * LWH cannot create a IProfile2D.
   */
  IProfile2D * createProfile2D(const std::string &, const std::string &,
			       const std::vector<double> &,
			       const std::vector<double> &,
			       const std::string & = "") {
    return error<IProfile2D>("IProfile2D");
  }

  /**
   * LWH cannot create a IProfile2D.
   */
  IProfile2D * createProfile2D(const std::string &, const std::string &,
			       const std::vector<double> &,
			       const std::vector<double> &,
			       double, double, const std::string & = "") {
    return error<IProfile2D>("IProfile2D");
  }

  /**
   * LWH cannot create a IProfile2D.
   */
  IProfile2D * createProfile2D(const std::string &, int, double, double,
			       int, double, double) {
    return error<IProfile2D>("IProfile2D");
  }

  /**
   * LWH cannot create a IProfile2D.
   */
  IProfile2D * createProfile2D(const std::string &, int, double, double,
			       int, double, double, double, double) {
    return error<IProfile2D>("IProfile2D");
  }

  /**
   * LWH cannot create a copy of an IProfile2D.
   */
  IProfile2D * createCopy(const std::string &, const IProfile2D &) {
    return error<IProfile2D>("IProfile2D");
  }

  /**
   * Create a Histogram1D by adding two Histogram1D.
   * @param path  The path of the created IHistogram. The path must be a
   *              full path.  ("/folder1/folder2/dataName" is a valid
   *              path). The characther `/` cannot be used in names; it
   *              is only used to delimit directories within paths.
   * @param hist1 The first member of the addition.
   * @param hist2 The second member of the addition.
   * @return      The sum of the two IHistogram1D.
   * @throws      std::runtime_error if histogram could not be created.
   */
  Histogram1D * add(const std::string & path,
		     const Histogram1D & hist1, const Histogram1D & hist2) {
    Histogram1D * h = new Histogram1D(hist1);
    h->setTitle(path.substr(path.rfind('/') + 1));
    h->add(hist2);
    if ( !tree->insert(path, h) ) return 0;
    return h;
  }
    
  /**
   * Create an IHistogram1D by adding two IHistogram1D.
   * @param path  The path of the created IHistogram. The path must be a
   *              full path.  ("/folder1/folder2/dataName" is a valid
   *              path). The characther `/` cannot be used in names; it
   *              is only used to delimit directories within paths.
   * @param hist1 The first member of the addition.
   * @param hist2 The second member of the addition.
   * @return      The sum of the two IHistogram1D.
   * @throws      std::runtime_error if histogram could not be created.
   */
  IHistogram1D * add(const std::string & path,
		     const IHistogram1D & hist1, const IHistogram1D & hist2) {
    return add(path, dynamic_cast<const Histogram1D &>(hist1),
	       dynamic_cast<const Histogram1D &>(hist2));
  }
    
  /**
   * Create a Histogram1D by subtracting two Histogram1D.
   * @param path  The path of the created IHistogram. The path must be a
   *              full path.  ("/folder1/folder2/dataName" is a valid
   *              path). The characther `/` cannot be used in names; it
   *              is only used to delimit directories within paths.
   * @param h1    The first member of the subtraction.
   * @param h2    The second member of the subtraction.
   * @return      The difference of the two IHistogram1D.
   * @throws      std::runtime_error if histogram could not be created.
   */
  Histogram1D * subtract(const std::string & path,
		    const Histogram1D & h1, const Histogram1D & h2) {
    Histogram1D * h = new Histogram1D(h1);
    h->setTitle(path.substr(path.rfind('/') + 1));
    if ( h->ax->upperEdge() != h2.ax->upperEdge() ||
	 h->ax->lowerEdge() != h2.ax->lowerEdge() ||
	 h->ax->bins() != h2.ax->bins() ) return 0;
    for ( int i = 0; i < h->ax->bins() + 2; ++i ) {
      h->sum[i] += h2.sum[i];
      h->sumw[i] -= h2.sumw[i];
      h->sumw2[i] += h2.sumw2[i];
    }
    if ( !tree->insert(path, h) ) return 0;
    return h;
  }

  /**
   * Create an IHistogram1D by subtracting two IHistogram1D.
   * @param path  The path of the created IHistogram. The path must be a
   *              full path.  ("/folder1/folder2/dataName" is a valid
   *              path). The characther `/` cannot be used in names; it
   *              is only used to delimit directories within paths.
   * @param hist1 The first member of the subtraction.
   * @param hist2 The second member of the subtraction.
   * @return      The difference of the two IHistogram1D.
   * @throws      std::runtime_error if histogram could not be created.
   */
  IHistogram1D * subtract(const std::string & path, const IHistogram1D & hist1,
			  const IHistogram1D & hist2) {
    return subtract(path, dynamic_cast<const Histogram1D &>(hist1),
		    dynamic_cast<const Histogram1D &>(hist2));
  }

  /**
   * Create a Histogram1D by multiplying two Histogram1D.
   * @param path  The path of the created IHistogram. The path must be a
   *              full path.  ("/folder1/folder2/dataName" is a valid
   *              path). The characther `/` cannot be used in names; it
   *              is only used to delimit directories within paths.
   * @param h1    The first member of the multiplication.
   * @param h2    The second member of the multiplication.
   * @return      The product of the two IHistogram1D.
   * @throws      std::runtime_error if histogram could not be created.
   */
  Histogram1D * multiply(const std::string & path,
		    const Histogram1D & h1, const Histogram1D & h2) {
    Histogram1D * h = new Histogram1D(h1);
    h->setTitle(path.substr(path.rfind('/') + 1));
    if ( h->ax->upperEdge() != h2.ax->upperEdge() ||
	 h->ax->lowerEdge() != h2.ax->lowerEdge() ||
	 h->ax->bins() != h2.ax->bins() ) return 0;
    for ( int i = 0; i < h->ax->bins() + 2; ++i ) {
      h->sum[i] *= h2.sum[i];
      h->sumw[i] *= h2.sumw[i];
      h->sumw2[i] += h1.sumw[i]*h1.sumw[i]*h2.sumw2[i] +
	h2.sumw[i]*h2.sumw[i]*h1.sumw2[i];
    }
    if ( !tree->insert(path, h) ) return 0;
    return h;
  }

  /**
   * Create an IHistogram1D by multiplying two IHistogram1D.
   * @param path  The path of the created IHistogram. The path must be a
   *              full path.  ("/folder1/folder2/dataName" is a valid
   *              path). The characther `/` cannot be used in names; it
   *              is only used to delimit directories within paths.
   * @param hist1 The first member of the multiplication.
   * @param hist2 The second member of the multiplication.
   * @return      The product of the two IHistogram1D.
   * @throws      std::runtime_error if histogram could not be created.
   */
  IHistogram1D * multiply(const std::string & path, const IHistogram1D & hist1,
			  const IHistogram1D & hist2) {
    return multiply(path, dynamic_cast<const Histogram1D &>(hist1),
		    dynamic_cast<const Histogram1D &>(hist2));
  }

  /**
   * Create n Histogram1D by dividing two Histogram1D.
   * @param path  The path of the created IHistogram. The path must be a
   *              full path.  ("/folder1/folder2/dataName" is a valid
   *              path). The characther `/` cannot be used in names; it
   *              is only used to delimit directories within paths.
   * @param h1    The first member of the division.
   * @param h2    The second member of the division.
   * @return      The ration of the two IHistogram1D.
   * @throws      std::runtime_error if histogram could not be created.
   */
  Histogram1D * divide(const std::string & path,
		  const Histogram1D & h1, const Histogram1D & h2) {
    Histogram1D * h = new Histogram1D(h1);
    h->setTitle(path.substr(path.rfind('/') + 1));
    if ( h->ax->upperEdge() != h2.ax->upperEdge() ||
	 h->ax->lowerEdge() != h2.ax->lowerEdge() ||
	 h->ax->bins() != h2.ax->bins() ) return 0;
    for ( int i = 0; i < h->ax->bins() + 2; ++i ) {
      h->sum[i] /= h2.sum[i];
      h->sumw[i] /= h2.sumw[i];
      h->sumw2[i] += h1.sumw2[i]/(h2.sumw[i]*h2.sumw[i]) +
	h1.sumw[i]*h1.sumw[i]*h2.sumw2[i]/
	           (h2.sumw[i]*h2.sumw[i]*h2.sumw[i]*h2.sumw[i]);
    }
    if ( !tree->insert(path, h) ) return 0;
    return h;
  }

  /**
   * Create an IHistogram1D by dividing two IHistogram1D.
   * @param path  The path of the created IHistogram. The path must be a
   *              full path.  ("/folder1/folder2/dataName" is a valid
   *              path). The characther `/` cannot be used in names; it
   *              is only used to delimit directories within paths.
   * @param hist1 The first member of the division.
   * @param hist2 The second member of the division.
   * @return      The ration of the two IHistogram1D.
   * @throws      std::runtime_error if histogram could not be created.
   */
  IHistogram1D * divide(const std::string & path, const IHistogram1D & hist1,
			const IHistogram1D & hist2) {
    return divide(path, dynamic_cast<const Histogram1D &>(hist1),
		    dynamic_cast<const Histogram1D &>(hist2));
  }

  /**
   * LWH cannot create an IHistogram2D by adding two IHistogram2D.
   */
  IHistogram2D * add(const std::string &,
		     const IHistogram2D &, const IHistogram2D &) {
    return error<IHistogram2D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram2D by subtracting two IHistogram2D.
   */
  IHistogram2D * subtract(const std::string &,
			  const IHistogram2D &, const IHistogram2D &) {
    return error<IHistogram2D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram2D by multiplying two IHistogram2D.
   */
  IHistogram2D * multiply(const std::string &,
			  const IHistogram2D &, const IHistogram2D &) {
    return error<IHistogram2D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram2D by dividing two IHistogram2D.
   */
  IHistogram2D * divide(const std::string &,
			const IHistogram2D &, const IHistogram2D &) {
    return error<IHistogram2D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram3D by adding two IHistogram3D.
   */
  IHistogram3D * add(const std::string &,
		     const IHistogram3D &, const IHistogram3D &) {
    return error<IHistogram3D>("3D histograms");
  }

  /**
   * LWH cannot create an IHistogram3D by subtracting two IHistogram3D.
   */
  IHistogram3D * subtract(const std::string &,
			  const IHistogram3D &, const IHistogram3D &) {
    return error<IHistogram3D>("3D histograms");
  }

  /**
   *  LWH cannot create an IHistogram3D by multiplying two IHistogram3D.
   */
  IHistogram3D * multiply(const std::string &,
			  const IHistogram3D &, const IHistogram3D &) {
    return error<IHistogram3D>("3D histograms");
  }

  /**
   * LWH cannot create an IHistogram3D by dividing two IHistogram3D.
   */
  IHistogram3D * divide(const std::string &,
			const IHistogram3D &, const IHistogram3D &) {
    return error<IHistogram3D>("3D histograms");
  }

  /**
   * LWH cannot create an IHistogram1D by projecting an IHistogram2D
   * along its x axis.
   */
  IHistogram1D * projectionX(const std::string &, const IHistogram2D &) {
    return error<IHistogram1D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram1D by projecting an IHistogram2D
   * along its y axis.
   */
  IHistogram1D * projectionY(const std::string &, const IHistogram2D &) {
    return error<IHistogram1D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram1D by slicing an IHistogram2D
   * parallel to the y axis at a given bin.
   */
  IHistogram1D * sliceX(const std::string &, const IHistogram2D &, int) {
    return error<IHistogram1D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram1D by slicing an IHistogram2D
   * parallel to the x axis at a given bin.
   */
  IHistogram1D * sliceY(const std::string &, const IHistogram2D &, int) {
    return error<IHistogram1D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram1D by slicing an IHistogram2D
   * parallel to the y axis between two bins (inclusive).
   */
  IHistogram1D * sliceX(const std::string &, const IHistogram2D &, int, int) {
    return error<IHistogram1D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram1D by slicing an IHistogram2D
   * parallel to the x axis between two bins (inclusive).
   */
  IHistogram1D * sliceY(const std::string &, const IHistogram2D &, int, int) {
    return error<IHistogram1D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram2D by projecting an IHistogram3D
   * on the x-y plane.
   */
  IHistogram2D * projectionXY(const std::string &, const IHistogram3D &) {
    return error<IHistogram2D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram2D by projecting an IHistogram3D
   * on the x-z plane.
   */
  IHistogram2D * projectionXZ(const std::string &, const IHistogram3D &) {
    return error<IHistogram2D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram2D by projecting an IHistogram3D
   * on the y-z plane.
   */
  IHistogram2D * projectionYZ(const std::string &, const IHistogram3D &) {
    return error<IHistogram2D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram2D by slicing an IHistogram3D
   * perpendicular to the Z axis, between "index1" and "index2"
   * (inclusive).
   */
  IHistogram2D * sliceXY(const std::string &, const IHistogram3D &, int, int) {
    return error<IHistogram2D>("2D histograms");
  }

  /**
   * LWH cannot create an IHistogram2D by slicing an IHistogram3D
   * perpendicular to the Y axis, between "index1" and "index2"
   * (inclusive).
   */
  IHistogram2D * sliceXZ(const std::string &, const IHistogram3D &, int, int) {
    return error<IHistogram2D>("2D histograms");
  }

  /**
   *  LWH cannot create an IHistogram2D by slicing an IHistogram3D
   * perpendicular to the X axis, between "index1" and "index2"
   * (inclusive).
   */
  IHistogram2D * sliceYZ(const std::string &, const IHistogram3D &, int, int) {
    return error<IHistogram2D>("2D histograms");
  }


private:

  /** Throw a suitable error. */
  template <typename T>
  static T * error(std::string feature) {
    throw std::runtime_error("LWH cannot handle " + feature + ".");
    return 0;
  }

  /** The tree where the actual histograms are stored. */
  Tree * tree;

};

}

#endif /* LWH_HistogramFactory_H */
