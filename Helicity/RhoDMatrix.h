// -*- C++ -*-
#ifndef ThePEG_RhoDMatrix_H
#define ThePEG_RhoDMatrix_H
//
// This is the declaration of the <!id>RhoDMatrix<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//  This class is designed to implement the storage of the rho and D
//  matrices which are required for the spin correlation algorithm.
//  The matrix stores the spin as 2s+1.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
//
// Author: Peter Richardson
//

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Config/Complex.h"
// #include "RhoDMatrix.fh"
// #include "RhoDMatrix.xh"

namespace ThePEG {
namespace Helicity {

class RhoDMatrix {

public:

  inline RhoDMatrix();
  inline RhoDMatrix(int);
  inline RhoDMatrix(const RhoDMatrix &);
  virtual ~RhoDMatrix();
  // Standard ctors and dtor.

public:

  inline Complex operator () (int,int) const;
  // operator to return an element of the matrix

  inline Complex & operator () (int,int);
  // operator to set an element of the matrix

  inline void setSpin(int);
  // set 2s+1 for the particle

  inline int getSpin();
  // get 2s+1 for the particle

  inline void average();
  // set the matrix to 1/(2s+1) on diagonals and zero elsewhere

  inline void zero();
  // zero the matrix

  inline RhoDMatrix & operator=(const RhoDMatrix &);
  // assignment operator.

  inline void normalize();
  // renormalise the matrix so it has unit trace

  inline void output();
  // output the spin density matrix

private:

  int _ispin;
  // 2s+1 for the particle
  Complex _matrix[5][5];
  // storage for the matrix allowing up to spin 2 particles

};

}
}


#include "RhoDMatrix.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RhoDMatrix.tcc"
#endif

#endif /* ThePEG_RhoDMatrix_H */
