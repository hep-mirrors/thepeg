// -*- C++ -*-

namespace ThePEG {

template <typename PType>
LorentzRotation UtilityBase::boostToCM(const pair<PType,PType> & pp) {
  typedef ParticleTraits<PType> Traits;
  LorentzRotation boost(-(Traits::momentum(pp.first) +
			  Traits::momentum(pp.second)).boostVector());
  Traits::transform(pp.first, boost);
  Traits::transform(pp.second, boost);
  LorentzRotation rot;
  rot.rotateZ(-Traits::momentum(pp.first).phi());
  rot.rotateY(-Traits::momentum(pp.first).theta());
  Traits::transform(pp.first, rot);
  Traits::transform(pp.second, rot);
  return rot*boost;
}

template <typename PType>
LorentzRotation UtilityBase::getBoostToCM(const pair<PType,PType> & pp) {
  typedef ParticleTraits<PType> Traits;
  LorentzMomentum p1 = Traits::momentum(pp.first);
  LorentzMomentum p2 = Traits::momentum(pp.second);
  Vector3 b = (p1 + Traits::momentum(pp.second)).boostVector();
  p1.boost(-b);
  LorentzRotation rot(-b);
  rot.rotateZ(-p1.phi());
  rot.rotateY(-p1.theta());
  return rot;
}

template <typename PType>
LorentzRotation UtilityBase::getBoostFromCM(const pair<PType,PType> & pp) {
  typedef ParticleTraits<PType> Traits;
  LorentzMomentum p1 = Traits::momentum(pp.first);
  Vector3 b = (p1 + Traits::momentum(pp.second)).boostVector();
  p1.boost(-b);
  LorentzRotation rot;
  rot.rotateZ(p1.phi());
  rot.rotateY(p1.theta());
  rot.boost(b);
  return rot;
}

template <typename Iterator>
LorentzRotation UtilityBase::boostToCM(Iterator first, Iterator last,
				       Iterator zAxis, Iterator xzPlane) {
  LorentzRotation boost(-sumMomentum(first, last).boostVector());
  typedef typename std::iterator_traits<Iterator>::value_type PType;
  typedef ParticleTraits<PType> Traits;

  transform(first, last, boost);
  if ( zAxis != last ) {
    LorentzRotation rot;
    rot.rotateZ(-Traits::momentum(*zAxis).phi());
    rot.rotateY(-Traits::momentum(*zAxis).theta());
    transform(first, last, rot);
    boost = rot*boost;
  }    
  if ( xzPlane != last ) {
    LorentzRotation rot;
    rot.rotateZ(-Traits::momentum(*xzPlane).phi());
    transform(first, last, rot);
    boost = rot*boost;
  }
  return boost;
}

template <typename LV>
LorentzRotation UtilityBase::
transformFromCMS(const LV & p) {
  LorentzRotation r(0.0, 0.0, p.rho()/p.e());
  r.rotateY(p.theta());
  r.rotateZ(p.phi());
  return r;
}

template <typename LV>
LorentzRotation UtilityBase::
transformFromCMS(const LV & sum, LV zAxis) {
  LorentzRotation r;
  Vector3 bz(sum.boostVector());
  zAxis.boost(-bz);
  r.rotateY(zAxis.theta());
  r.rotateZ(zAxis.phi());
  r.boost(bz);
  return r;
}

template <typename LV>
LorentzRotation UtilityBase::
transformFromCMS(const LV & sum, const LV & zAxis, LV xyPlane) {
  LorentzRotation r;
  LorentzRotation r1 = transformFromCMS(sum, zAxis);
  xyPlane.transform(r1.inverse());
  r.rotateZ(xyPlane.phi());
  r.transform(r1);
  return r;
}
  
template <typename LV>
LorentzRotation UtilityBase::
transformToCMS(const LV & p) {
  LorentzRotation r;
  r.rotateZ(-p.phi());
  r.rotateY(-p.theta());
  r.boost(0.0, 0.0, -p.rho()/p.e());
  return r;
}

template <typename LV>
LorentzRotation UtilityBase::
transformToCMS(const LV & sum, LV zAxis) {
  LorentzRotation r(-sum.boostVector());
  zAxis.transform(r);
  r.rotateZ(-zAxis.phi());
  r.rotateY(-zAxis.theta());
  return r;
}

template <typename LV>
LorentzRotation UtilityBase::
transformToCMS(const LV & sum, const LV & zAxis, LV xyPlane) {
  LorentzRotation r(transformToCMS(sum, zAxis));
  xyPlane.transform(r);
  r.rotateZ(-xyPlane.phi());
  return r;
}
  
template <typename PType>
void UtilityBase::setMomentum(PType & p, const Momentum3 & q) {
  typedef ParticleTraits<PType> Traits;
  if ( Traits::mass(p) == 0.0*GeV ) {
    Traits::set3Momentum(p, q);
  } else {
    Traits::transform(p, transformToCMS(Traits::momentum(p)));
    setMomentumFromCMS(p, q);
  }
}

template <typename PType>
void UtilityBase::setMomentumFromCMS(PType & p, const Momentum3 & q) {
  typedef ParticleTraits<PType> Traits;
  LorentzMomentum q4(q, sqrt(q.mag2() + sqr(Traits::mass(p))));
  if ( Traits::momentum(p) == LorentzMomentum() )
    Traits::set5Momentum(p, q4);
  else
    Traits::transform(p, transformFromCMS(q4));
  return;
}

template <typename Iter>
void UtilityBase::setMomentum(Iter first, Iter last, const Momentum3 & q) {
  typedef typename std::iterator_traits<Iter>::value_type PType;
  typedef ParticleTraits<PType> Traits;
  Iter second = first;
  if ( ++second == last ) return setMomentum(Traits::ref(*first), q);
  LorentzMomentum sum = sumMomentum(first, last);
  transform(first, last, transformToCMS(sum));
  setMomentumFromCMS(first, last, sum.m2(), q);
}

template <typename Iter>
void UtilityBase::
setMomentumFromCMS(Iter first, Iter last, Energy2 m2, const Momentum3 & q) {
  typedef typename std::iterator_traits<Iter>::value_type PType;
  typedef ParticleTraits<PType> Traits;
  Iter second = first;
  if ( ++second == last ) return setMomentumFromCMS(Traits::ref(*first), q);
  transform(first, last,
	    transformFromCMS(LorentzMomentum(q, sqrt(q.mag2() + m2))));
}

template <typename Cont1, typename Cont2>
void UtilityBase::add(Cont1 & c1, const Cont2 & c2) {
  typename Cont2::const_iterator i = c2.begin();
  while ( i != c2.end() ) c1.insert(c1.end(), *i++);
}

}
