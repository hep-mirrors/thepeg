// -*- C++ -*-
#ifndef ACDCGen_H
#define ACDCGen_H

#include "ACDCGenConfig.h"
#include "ACDCTraits.h"
#include "ACDCGenCell.h"

namespace ACDCGenerator {

template <typename Rnd, typename FncPtr>
class ACDCGen {

public:

  typedef Rnd RndType;
  typedef ACDCRandomTraits<RndType> RndTraits;
  typedef FncPtr FncPtrType;
  typedef vector<ACDCGenCell*> CellVector;
  typedef vector<FncPtrType> FncVector;
  typedef vector<DimType> DimVector;
  typedef DimVector::size_type size_type;
  typedef ACDCFncTraits<FncPtrType> FncTraits;

public:

  inline ACDCGen(Rnd & r);
  // Standard constructor requiring a random generator object to be
  // used.

  inline ACDCGen();
  // Default Constructor.

  inline bool addFunction(DimType dim, FncPtrType f);
  // Add a function of a given dimension according to which points
  // will be generated. Note that each function added like this will
  // have its own tree of cells.

  inline void clear();
  // Remove all added functions and reset the generator;

public:

  inline FncPtrType generate();
  // Generate a point, choosing between the different functions
  // specified. The chosen function is returned, while the generated
  // point is obtained by the function 'lastPoint()'.

  inline void reject();
  // Reject the last generated point.

  inline const DVector & lastPoint() const;
  // Return the last generated point.

  inline double lastF() const;
  // Return the value of the last chosen function in the last point.

  inline FncPtrType lastFunction() const;
  // Return the function chosen for the last generated point.

  inline bool compensating();
  // Returns true if the generator is currently in a state of
  // compensating an erroneous overestimation of one of the specified
  // functions. If so, the integral and the generated points are not
  // statistically correct.

  inline double integral() const;
  // Return the current Monte Carlo estimate of the integral of the
  // specified functions over the unit volume.

public:
  // The following routines influence the efficiency of the
  // generation.

  inline void eps(double newEps);
  // Set the minimum cell size considered for this generation. The
  // default is the machine limit for double precision times a
  // hundred.

  inline void margin(double newMargin);
  // Set the safety margin used to multiply the highest found function
  // value in a cell when setting its overestimated value. Default is
  // 1.1.

  inline void nTry(size_type newNTry);
  // Set the number of points (with non-zero function value used to
  // initialize the tree of cells to use in the generation for each
  // function.

  inline void maxTry(long);
  // Set the maximum number of attempts to generate a phase space
  // point, or to find non-zero points in the initialization.

  inline void cheapRandom(bool b);
  // Set to true if generating random numbers are so cheap that a new
  // one can be thrown everytime a sub-cell is chosen. Otherwise
  // random numbers used for this will be reused.

  inline void setRnd(Rnd & r);
  // Set a new random number generator.

  inline size_type last() const;
  // return the index of the function chosen for the last generated
  // point.

public:
  // The following functions provide some information about the
  // current generation.

  inline long n() const;
  // The number of accepted points so far.

  inline long N() const;
  // The number of tried point so far. Note that the number of calls
  // to the specified functions may be larger. It is up to the user to
  // keep track of those.

  inline double efficiency() const;
  // The ratio of the number of accepted and number of tried points
  // n()/N();

  inline int nBins() const;
  // Return the number of active cells created so far.

  inline int depth() const;
  // Return the maximum depth of any tree of cells used.

  inline double maxInt() const;
  // Return the current overestimation of the full integral of all
  // specified functions over the unit volume.

  inline double eps() const;
  // The minimum cell size considered for this generation.

  inline double margin() const;
  // The safety margin used to multiply the highest found function
  // value in a cell when setting its overestimated value.

  inline size_type nTry() const;
  // The number of points used to initialize the tree of cells to use
  // in the generation.

  inline long maxTry() const;
  // The maximum number of attempts to generate a phase space point,
  // or to find non-zero points in the initialization.

  inline bool cheapRandom() const;
  // Returns true if generating random numbers are so cheap that a new
  // one can be thrown everytime a sub-cell is chosen. Otherwise
  // random numbers used for this will be reused.

  inline size_type size() const;
  // The number of functions used.

  vector<ACDCGenCellInfo> extractCellInfo() const;
  // Return a vector with information about all cells.

public:
  // The following methods forwards the request to the specified
  // random number generator.

  inline double rnd() const;
  // Double precision number in the interval ]0,1[.

  inline double rnd(double lo, double up) const;
  // Double precision number in the interval ]lo,up[.

  inline void rnd(const DVector & lo, const DVector & up, DVector & r)const;
  // Fill the r vector with doubles r[i] in the interval ]lo[i],up[i][.

  inline void rnd(DimType D, DVector & r) const;
  // Fill the D first elements in the r vector with doubles in the
  // interval ]0,1[.

  inline long rndInt(long x) const;
  // Integer in the interval [0,x[

public:

  template <typename POStream>
  void output(POStream &) const;
  template <typename PIStream>
  void input(PIStream &);
  // These functions are to be ysed in ThePEG for input and output to
  // a persistent stream and will not work properly for normal
  // iostreams.

private:

  inline double doMaxInt();
  // Calculate the overestimated integral for all functions.

  inline const FncVector & functions() const;
  // Return the vector of functions.

  inline FncPtrType function(size_type i) const;
  // Return the i'th function.

  inline const DimVector & dimensions() const;
  // Return a vector with the dimensions of all functions.

  inline DimType dimension(size_type i) const;
  // Return the dimension of the i'th function.

  inline DimType lastDimension() const;
  // Return the dimension of the function chosen for the last
  // generated point.

  inline const CellVector & cells() const;
  // Return the roots of all cell trees.

  inline ACDCGenCell * cell(size_type i) const;
  // Return the root cell for the i'th function.

  inline ACDCGenCell * lastPrimary() const;
  // Return the root cell for the function chosen for the last
  // generated point.

  inline const DVector & sumMaxInts() const;
  // Return a vector with the incremental sum of overestimated
  // integrals for each function.

  inline ACDCGenCell * lastCell() const;
  // Return the cell chosen for the last generated point.


  inline void chooseCell(DVector & lo, DVector & up);
  // Choose a function according to its overestimated integral and
  // choose a cell to generate a point in.

  inline void  compensate(const DVector & lo, const DVector & up);
  // Start the compensation procedure for the last chosen cell when a
  // function velue has been found which exceeds the previous
  // overestimation.

private:

  RndType * theRnd;
  // The random number generator to be used for this Generator.
  
  long theNAcc;
  // The number of accepted points (weight > 0) so far.

  long theN;
  // The number of attempted points so far.

  double theEps;
  // The smallest possible division allowed.

  double theMargin;
  // The factor controlling the loss of efficiency when compensating.

  size_type theNTry;
  // The number of points to use to find initial average.

  long theMaxTry;
  // The maximum number of attempts to generate a phase space point,
  // or to find non-zero points in the initialization.

  bool useCheapRandom;
  // True if generating random numbers are so cheap that a new one can
  // be thrown everytime a sub-cell is chosen. Otherwise random
  // numbers used for this will be reused.

  FncVector theFunctions;
  DimVector theDimensions;
  CellVector thePrimaryCells;
  DVector theSumMaxInts;
  // The bins representing each function to be sampled and their
  // corresponding dimensions and root cells and the accumulated max
  // integrals.

  size_type theLast;
  // The last index chosen

  ACDCGenCell * theLastCell;
  // The last cell chosen.

  DVector theLastPoint;
  // The last point generated.

  double theLastF;
  // The function value of the last point.

  // A struct representing a level of compensation.
  struct Level {

    long lastN;
    // The number of attempts at which point this level disapprears.

    double g;
    // The previous max value in the Cell to compensate.

    ACDCGenCell * cell;
    // The cell which is being compensated.

    size_type index;
    // The index corresponding to the cell being compensated.

    DVector up;
    DVector lo;
    // The integration limits for the cell being compensated.

  };

  typedef vector<Level> LevelVector;
  LevelVector levels;
  // The vector (stack) of levels


  // This is a help struct to perform the divide-and-conquer slicing
  // of cells before starting the compensation procedure.
  struct Slicer {

    Slicer(DimType, ACDCGen &, const DVector &, const DVector &);
    // The constructor takes the number of dipmensions of the function
    // approximated by the current cell, the ACDCGen object
    // controlling the generation and the lower-left and upper-right
    // corners of the cell to be sliced.

    Slicer(DimType Din, const Slicer & s, ACDCGenCell * cellin,
	   const DVector & loin, const DVector & xselin, const DVector & upin,
	   double fselin);
    // The constructor used internally when diagonally chopped-off
    // cells need to be sliced themselves.

    void divideandconquer();
    // Called from both constructors to do the actual work.

    void init();
    // Initialize the procedure, finding the slicing points around the
    // current point

    void slice();
    // Do the slicing and increase the overestimate of the function in
    // the resulting cell. If a point with a higher function value has
    // been found repeat the slicing around that point etc.

    double shiftmaxmin();
    // After slicing a cell, find the maximum function value found in
    // the resulting cell. Also set the minimum value found.

    void dohalf(DimType);
    // Find the slice point of the current cell in the direction given.

    void checkdiag(ACDCGenCell * cell, DimType d, double lod, double upd);
    // If split is in more than one dimensions check the overestimate
    // for the chopped-off cell.

    DimType D;
    // The dimension of the cell to be sliced.

    DVector lo;
    DVector up;
    // The lower-left and upper-right corners of the current cell.

    DVector xcl;
    DVector xcu;
    // The lower-left (upper-right) point found closest to the current
    // point which gives a function value below the overestimate.

    DVector xhl;
    DVector xhu;
    // The lower-left (upper-right) point furthest away from the
    // current point which gives a function value abov the
    // overestimate.

    DVector fhl;
    DVector fhu;
    // The function values found for the xhl and xhu points.

    DVector xsel;
    // The current point around which we are slicing.

    double fsel;
    // The function value in the current point.

    ACDCGenCell * current;
    // The current cell.

    ACDCGenCell * first;
    // The cell which resulted from the first slicing procedure. This
    // is the first one to get an increased overestimate and is the
    // one to be compensated. All other cells with increased
    // overestimates are sub-cells to this one

    DVector firstlo;
    DVector firstup;
    // The lower-left and upper-right corners of the 'first' cell.

    FncPtr f;
    // A pointer to the function to be used.

    double epsilon;
    double margin;
    // The epsilon() and margin() values obtained from the controlling
    // ACDCGen object.

    multimap<double,DimType> rateslice;
    // The dimensions to slice in rated by the resulting fractional
    // volume of the resulting slice. If the dimension is negative it
    // means that the cell should be slized from below.

    double minf;
    // The minimu function value found in the current sliced cell (set
    // by shiftmaxmin()).

    bool wholecomp;
    // If true, then the whole original cell should compensated in the
    // continued generation.

  };

public:

  static size_type maxsize;

private:

  ACDCGen(const ACDCGen &);
  ACDCGen & operator=(const ACDCGen &);
  // Copy constructor and assignment is private.

};

}

#include "ACDCGen.icc"

#endif
