// -*- C++ -*-
#ifndef ThePEG_SimplePhaseSpace_H
#define ThePEG_SimplePhaseSpace_H

#include "ThePEG/Config/ThePEG.h"
// #include "SimplePhaseSpace.fh"

#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/EventRecord/ParticleTraits.h"
#include "ThePEG/Repository/UseRandom.h"
#include "SimplePhaseSpace.xh"
#include <numeric>

namespace ThePEG {

struct SimplePhaseSpace {

  template <typename PType>
  static void CMS(Energy2 s, PType & p1, PType & p2)
    ThePEG_THROW_SPEC((ImpossibleKinematics));
  // Set momenta of PTypes p1 and p2 in their center of mass system
  // so that their total invariant mass squared is s, and their
  // direction is distributed isotropically.

  template <typename PType>
  static void CMS(PType & p1, PType & p2, Energy2 s,
		  double cosTheta, double phi)
    ThePEG_THROW_SPEC((ImpossibleKinematics));
  // Set momenta of particles p1 and p2 in their center of mass system
  // so that their total invariant mass squared is s, and the
  // direction of the first particle is given by cosTHeta and phi.

  template <typename PType>
  static void CMS(PType & p1, PType & p2, Energy2 s, Energy2 t, double phi,
		  const PType & p0) ThePEG_THROW_SPEC((ImpossibleKinematics));
  // Set momenta of particles p1 and p2 in their center of mass system
  // so that their total invariant mass squared is s, t=(p0-p1)^2 and
  // p1 has the azimuth angle phi around p0.

  template <typename PType>
  static void CMS(PType & p1, PType & p2, Energy2 s)
    ThePEG_THROW_SPEC((ImpossibleKinematics));
  template <typename PPairType>
  inline static void CMS(const PPairType & p, Energy2 s)
    ThePEG_THROW_SPEC((ImpossibleKinematics));
  // Set momenta of particles p1 and p2 in their center of mass system
  // so that their total invariant mass squared is s, and p1 is along
  // the z-axis.

  template <typename PType>
  static void CMS(PType & p1, PType & p2, PType & p3, Energy2 s,
		  double x1, double x3)
    ThePEG_THROW_SPEC((ImpossibleKinematics));
  // Set momenta of particles p1, p2 and p3 in their center of mass
  // system so that their total invariant mass squared is s, the
  // energy fraction of particle p1(3) is x1(3) of the total energy
  // and the angles of the system is distributed isotropically.

  template <typename PType>
  static void CMS(PType & p1, PType & p2, PType & p3, Energy2 s,
		  double x1, double x3, double phii = 0.0,
		  double theta = 0.0, double phi = 0.0)
    ThePEG_THROW_SPEC((ImpossibleKinematics));
  // Set momenta of particles p1, p2 and p3 in their center of mass
  // system so that their total invariant mass squared is s, the
  // energy fraction of particle p1(3) is x1(3) of the total energy.
  // Particle p1 is initially placed along the z-axis and particle p2
  // is given azimuth angle phii. Then the system is rotated with
  // phi and theta respectively.

  static Energy getMagnitude(Energy2 s, Energy m1, Energy m2)
    ThePEG_THROW_SPEC((ImpossibleKinematics));
  // Calculate the absolute momentum of two particles with masses m1
  // and m2 when put in their CMS of total invariant mass squared s.

  inline static Momentum3 polar3Vector(Energy p, double costheta, double phi);
  // Return a three-vector given the absolute momentum, cos(theta) and
  // phi.

  static vector<LorentzMomentum>
  CMSn(Energy m0, const vector<Energy> & m)
    ThePEG_THROW_SPEC((ImpossibleKinematics));
  // Given a number of particles with masses m and total invariant
  // mass m0, return the corresponding four-momenta randomly
  // distributed according to phase space.

  template <typename Container>
  static void CMSn(Container & particles, Energy m0)
    ThePEG_THROW_SPEC((ImpossibleKinematics));
  // Given a number of particles and total invariant mass m0,
  // distribute their four-momenta randomly according to phase space.

};

}

#include "SimplePhaseSpace.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "SimplePhaseSpace.tcc"
#endif

#endif /* ThePEG_SimplePhaseSpace_H */
