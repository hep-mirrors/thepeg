// -*- C++ -*-
//
// This is the implementation of the non-inlined, templated member
// functions of the Integrator class.
//

namespace ThePEG {

template <typename FncT, typename RetT, typename ValT, typename ArgT>
void Integrator<FncT,RetT,ValT,ArgT>::init(const PeakSet & peaks) {
  bins.push_back(make_pair(xmin, fnc(xmin)));
  for ( PeakSet::const_iterator it = peaks.begin(); it != peaks.end(); ++it )
    if ( *it > xmin && *it < xmax ) bins.push_back(make_pair(*it, fnc(*it)));
  bins.push_back(make_pair(xmax, fnc(xmax)));
  Bin it = bins.begin();
  Bin prev = it++;
  while ( it != bins.end() ) {
    checksplit(prev, it);
    prev = it++;
  }
  it = bins.begin();
  prev = it++;
  while ( it != bins.end() ) {
    selector.insert(integrate(prev, it), it);
    prev = it++;
  }
}

template <typename FncT, typename RetT, typename ValT, typename ArgT>
void Integrator<FncT,RetT,ValT,ArgT>::
checksplit(Bin lo, Bin up) {
  Bin m = bins.insert(up);
  ArgT x = 0.5*(lo->first + up->first);
  *m = make_pair(x, fnc(x));
  ValT approx = 0.5*(lo->second + up->second);
  if ( m->second < wmax*approx && m->second > wmin*approx ) return;
  checksplit(lo, m);
  checksplit(m, up);
}

template <typename FncT, typename RetT, typename ValT, typename ArgT>
ArgT Integrator<FncT,RetT,ValT,ArgT>::
generate(double rnd, double & weight) const {
  double remrnd = 0.0;
  CBin lo = selector.select(rnd, &remrnd);
  CBin up = lo--;
  ArgT x = generate(lo, up, remrnd);
  weight = fnc(x)/((lo->second + (x - lo->first)*(up->second - lo->second)/
		    (up->first - lo->first))*wmax);
  return x;
} 

}
