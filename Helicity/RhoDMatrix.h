// -*- C++ -*-
#ifndef ThePEG_RhoDMatrix_H
#define ThePEG_RhoDMatrix_H
// This is the declaration of the RhoDMatrix class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Config/Complex.h"
// #include "RhoDMatrix.fh"
// #include "RhoDMatrix.xh"

namespace ThePEG {
namespace Helicity {

/**
 *  The RhoDMatrix class is designed to implement the storage of the
 *  rho and D matrices which are required for the spin correlation
 *  algorithm.  The matrix stores the spin as 2s+1.
 *
 * @author Peter Richardson
 *
 */
class RhoDMatrix {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor with undefined spin.
   */
  inline RhoDMatrix();

  /**
   * Standard constructor giving the spin as 2s+1.
   */
  inline RhoDMatrix(int);

  /**
   * Copy constructor.
   */
  inline RhoDMatrix(const RhoDMatrix &);

  /**
   * Destructor.
   */
  virtual ~RhoDMatrix();
  //@}

public:

  /** @name Access matrix elements. */
  //@{
  /**
   * Return an element of the matrix.
   */
  inline Complex operator () (int,int) const;

  /**
   * Set an element of the matrix.
   */
  inline Complex & operator () (int,int);

  /**
   * set the matrix to 1/(2s+1) on diagonals and zero elsewhere
   */
  inline void average();

  /**
   * zero the matrix
   */
  inline void zero();

  /**
   * renormalise the matrix so it has unit trace
   */
  inline void normalize();
  //@}

  /** @name Access the spin. */
  //@{
  /**
   * Set 2s+1 for the particle.
   */
  inline void setSpin(int);

  /**
   * Get 2s+1 for the particle.
   */
  inline int getSpin();
  //@}

  /**
   * Assignment operator.
   */
  inline RhoDMatrix & operator=(const RhoDMatrix &);

  /**
   * Rutput the spin density matrix for debugging purposes.
   */
  inline void output();

private:

  /**
   * 2s+1 for the particle.
   */
  int _ispin;

  /**
   * Storage for the matrix allowing up to spin 2 particles
   */
  Complex _matrix[5][5];

};

}
}


#include "RhoDMatrix.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RhoDMatrix.tcc"
#endif

#endif /* ThePEG_RhoDMatrix_H */
