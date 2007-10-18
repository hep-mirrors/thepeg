// -*- C++ -*-
#ifndef ThePEG_epsilon_H
#define ThePEG_epsilon_H
//
// This is the declaration of the epsilon class.

#include "ThePEG/Vectors/LorentzVector.h"

namespace ThePEG {
namespace Helicity {

/** \ingroup Helicity
 *  \author Peter Richardson
 *
 *  This class is designed to combine 5-momenta and polarization 
 *  vectors together with the result being the product with the 
 *  eps function. The class is purely static and contains no data.
 *
 *  @see LorentzPolarizationVector
 *  @see Lorentz5Vector
 */

  /**
   *  Return the product 
   *  \f$\epsilon^{\mu\alpha\beta\gamma}v_{1\alpha}v_{2\beta}v_{3\gamma}\f$.
   * @param a The first  vector \f$v_{1\alpha}\f$.
   * @param b The second vector \f$v_{2\alpha}\f$.
   * @param c The third  vector \f$v_{3\alpha}\f$.
   * @return The product 
   * \f$\epsilon^{\mu\alpha\beta\gamma}v_{1\alpha}v_{2\beta}v_{3\gamma}\f$.
   */
  template <typename A, typename B, typename C>
  inline LorentzVector<typename BinaryOpTraits<
			 typename BinaryOpTraits<A,B>::MulT, C>::MulT>
  epsilon(const LorentzVector<A> & a,
	  const LorentzVector<B> & b,
	  const LorentzVector<C> & c);


}
}


#include "epsilon.icc"

#endif /* ThePEG_epsilon_H */