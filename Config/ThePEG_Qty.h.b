


#ifdef ThePEG_HAS_UNITS_CHECKING
#include "PhysicalQty.h"
#include "PhysicalQtyOps.h"
#include "PhysicalQtyComplex.h"

namespace ThePEG {

#else

#include <cmath>
namespace ThePEG {

// pow<P,R>(double) --- required for consistency
template<int P, int R>
double pow(double q) {
  return std::pow(q,double(P)/double(R));
}

#endif

template <int L, int E, int Q, int DL = 1, int DE = 1, int DQ = 1>
struct QTY {
#ifdef ThePEG_HAS_UNITS_CHECKING
  typedef Qty<L,E,Q,DL,DE,DQ> Type;
#else
  typedef double	      Type;
#endif
};

}

#endif
