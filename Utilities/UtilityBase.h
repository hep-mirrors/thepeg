// -*- C++ -*-
#ifndef ThePEG_UtilityBase_H
#define ThePEG_UtilityBase_H

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/EventRecord/ParticleTraits.h"
// #include "UtilityBase.fh"
// #include "UtilityBase.xh"

namespace ThePEG {

struct UtilityBase {

  template <typename Cont>
  static inline LorentzMomentum sumMomentum(const Cont &);
  template <typename Iterator>
  static inline LorentzMomentum sumMomentum(Iterator first, Iterator last);
  // Sums the four-momentum of the entries between first and last. The
  // class Iterator::value_type must be of a type T for which
  // ParticleTraits<T>::momentum(const T&) is implemented correctly.

  template <typename Iterator>
  static inline void transform(Iterator first, Iterator last,
			       const LorentzRotation & boost);
  // Transform the entries between first and last. The class
  // Iterator::value_type must be of a type T for which
  // ParticleTraits<T>::transform(T&, const LorentzRotation &) is
  // implemented correctly.

  template <typename PType>
  static LorentzRotation boostToCM(const pair<PType,PType> & pp);
  // Boost the two first and second in the pair to their CM
  // system. Also rotate so that the first is along the z-axis. The
  // class PType must have ParticleTraits<PType>::momentum(const
  // PType&) and ParticleTraits<PType>::transform(PType&, const
  // LorentzRotation&) implemented correctly.

  template <typename PType>
  static LorentzRotation getBoostToCM(const pair<PType,PType> & pp);
  // Obtain the LorentzRotation needed to boost the two first and
  // second in the pair to their CM system. Also rotate so that the
  // first is along the z-axis. The class PType must have
  // ParticleTraits<PType>::momentum(const PType&) implemented
  // correctly.

  template <typename PType>
  static LorentzRotation getBoostFromCM(const pair<PType,PType> & pp);
  // Get the inverse boost as compared to getBoostToCM.

  template <typename Iterator>
  inline static LorentzRotation boostToCM(Iterator first, Iterator last);
  template <typename Iterator>
  inline static LorentzRotation boostToCM(Iterator first, Iterator last,
					  Iterator zAxis);
  template <typename Iterator>
  static LorentzRotation boostToCM(Iterator first, Iterator last,
				   Iterator zAxis, Iterator xzPlane);
  // Boost the entries between fisrt and last into their CM system. If
  // zAxis is provided and != last, also rotate the entries so that
  // zAxis becomes paralell to the z-axis. Also, if xzPlane is
  // provided and != last, rotate the entries so that xzPlane is
  // placed in the xz-plane.  The class Iterator::value_type must be
  // of a type T for which ParticleTraits<T>::momentum(const T&) and
  // ParticleTraits<T>::transform(T&, const LorentzRotation&) are
  // implemented correctly.

  template <typename PType>
  static void setMomentum(PType & p, const Momentum3 & q);
  // Rotate p to the z-axis and boost it to its CMS, then boost it
  // along the z-axis and rotate it so that it ends up with momentum
  // q. If p is massless - simply set its momentum.

  template <typename PType>
  static void setMomentumFromCMS(PType & p, const Momentum3 & q);
  // Boost p along the z-axis and rotate it so that, if it was
  // previously at rest, it ends up with momentum q. If p is massless
  // - simply set its momentum to q.

  template <typename Iter>
  static void setMomentum(Iter first, Iter last, const Momentum3 & q);
  // Rotate the range of particles so their sum is along z-axis and
  // boost them to their CMS, then boost them along the z-axis and
  // rotate them so that they end up with total momentum q.

  template <typename Iter>
  static void setMomentumFromCMS(Iter first, Iter last,
				 Energy2 m2, const Momentum3 & q);
  // Boost the range of particles along the z-axis and rotate them so
  // that, if they were previously in their rest frame, they end up
  // with total momentum q.

  template <typename LV>
  static LorentzRotation transformFromCMS(const LV & p);
  // Create a rotation corresponding to transforming sum to its
  // current value from its CMS by first boosting along the z-axis and
  // then rotating.

  template <typename LV>
  static LorentzRotation transformFromCMS(const LV & sum, LV zAxis);
  // Create a rotation corresponding to transforming sum to its
  // current value from its CMS, with zAxis along the z-axis in that
  // CMS frame.

  template <typename LV>
  static LorentzRotation transformFromCMS(const LV & sum,
					  const LV & zAxis, LV xyPlane);
  // Create a rotation corresponding to transforming sum to its
  // current value from its CMS, with zAxis along the z-axis and
  // xyPlane in the x-y plane in that CMS frame.

  template <typename LV>
  static LorentzRotation transformToCMS(const LV & sum, LV zAxis);
  // Create a rotation which would transform sum to its CMS frame with
  // zAxis along the z-axis in that frame.

  template <typename LV>
  static LorentzRotation transformToCMS(const LV & p);
  // Create a rotation which would transform sum to its CMS frame
  // first rotating it to the z-axis and then boost it along the
  // z-axis..

  template <typename LV>
  static LorentzRotation transformToCMS(const LV & sum,
					const LV & zAxis, LV xyPlane);
  // Create a rotation which would transform sum to its CMS frame with
  // zAxis along the z-axis and xyPlane in the x-y plane in that frame.

  template <typename Cont1, typename Cont2>
  static void add(Cont1 & c1, const Cont2 & c2);
  // Add the elements in Cont2 to Cont1, appending them to the end if
  // possible.

};

struct Utilities: public UtilityBase {};

}

#include "UtilityBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "UtilityBase.tcc"
#endif

#endif /* ThePEG_UtilityBase_H */
