// -*- C++ -*-
#ifndef ACDCGenCell_H
#define ACDCGenCell_H

#include "ACDCGenConfig.h"
#include "ACDCTraits.h"

namespace ACDCGenerator {

struct ACDCGenCellInfo;

class ACDCGenCell {

public:

  inline ACDCGenCell(double newG);
  inline ACDCGenCell(double newG, double newV);
  // The standard constructors. The default and copy constructors are
  // private.

  inline ~ACDCGenCell();
  // The destuctor will also delete all child cells,

  template <typename RndType>
  inline ACDCGenCell * generate(DVector & lo, DVector & up, RndType & rnd);
  inline ACDCGenCell * generate(DVector & lo, DVector & up, DVector & rndv);
  // Choose a cell recursively according to their relative
  // overestimated integrals. The first version uses a random
  // generator object throw dice to choose sub-cell. The second
  // version uses a pre-generated set of random numbers (one for each
  // dimension) to choose sub-cell and then rescales the random number
  // used.

  inline ACDCGenCell * getCell(DVector & lo, const DVector & x, DVector &  up);
  // For a given phase space point, find the corresponding
  // cell. Afterwards, the up and lo vectors will caontain the
  // upper-right and lower-left corners of the chosen cell.

  inline bool isSplit() const;
  // Returns true if this cell has been split.

  inline double doMaxInt();
  // Recalculate (recursively) the overestimated integral for this
  // cell (and of the sub-cells) and return it.

  inline double maxInt() const;
  // Return the last calculated the overestimated integral for this
  // cell.

  inline void splitme(double lo, double newDiv, double up, DimType newDim);
  // Split this cell into two alogh the newDim direction, where the
  // lower and upper limit is given by lo and up and the point of
  // division is given by newDiv.

  inline void g(double newG);
  // Set a new overestimated maximum function value in this cell.

  inline double g() const;
  // Return the overestimated maximum function value in this cell.

  inline double v() const;
  // Return the volume of this cell.

  inline DimType dim() const;
  // If this cell is split, return the direction in which it has been
  // split. Otherwise return -1.

  inline double div() const;
  // If this cell is split, return the point of division in the dim()
  // direction. Otherwise return -1.0.

  inline ACDCGenCell * upper() const;
  // If this cell is split, return the upper sub-cell.

  inline ACDCGenCell * lower() const;
  // If this cell is split, return the lower sub-cell.

  inline int nBins() const;
  // Return the number of cells in this sub-tree which have not been
  // split.

  inline int depth() const;
  // Return the maximum depth of this sub-tree.

  inline void extract(DVector & lo, DVector & up,
		      vector<ACDCGenCellInfo> &) const;
  // Append ACDCGenCellInfo objects describing this subtree to a given
  // vector.

  inline long getIndex(const ACDCGenCell * c) const;
  inline long getIndex(const ACDCGenCell * c, long & indx) const;
  // Get the index of the given cell;
   
  inline ACDCGenCell * getCell(long i);
  inline ACDCGenCell * getCell(long i, long & indx);
  // Return the cell corresponding to the given index i.

public:

  double theG;
  // If the cell has not been split this is the overestimated maximum
  // function value in this cell. Otherwise it is the weighted
  // average of the sub-cells values.

  double theV;
  // The volume of this cell.

  ACDCGenCell * theUpper;
  ACDCGenCell * theLower;
  // Pointers to the upper and lower sub-cells.

  double theDivision;
  // The point of division in the dim() direction.

  DimType theSplitDimension;
  // The direction in which it has been split.

private:

  ACDCGenCell();
  ACDCGenCell(const ACDCGenCell &);
  ACDCGenCell & operator=(const ACDCGenCell &);
  // Private default methods to avoid misuse.

};


// This is a class describing cells to the outside world to be used
// for debugging purposes. They only make sense if extracted with the
// ACDCGenCell::extract function.
struct ACDCGenCellInfo {
  typedef vector<ACDCGenCellInfo>::size_type Index;

  double g;
  // The overestimated maximum function value of the corresponding
  // cell.

  double v;
  // The volume of the corresponding cell.

  DVector up;
  DVector lo;
  // The upper-right and lower-left corners of the corresponding cell.

  Index iup;
  Index ilo;
  // The indices of the upper and lower sub-cells in the vector in
  // which the corresponding cell was inserted.

};

}

#include "ACDCGenCell.icc"

#endif
