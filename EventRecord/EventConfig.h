// -*- C++ -*-
#ifndef ThePEG_EventConfig_H
#define ThePEG_EventConfig_H

#ifndef ThePEG_NOT_ThePEG

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Rebinder.fh"
#include "ThePEG/Utilities/FixedSizeAllocator.h"
#include "ThePEG/Persistency/PersistentOStream.fh"
#include "ThePEG/Persistency/PersistentIStream.fh"

#ifndef ThePEG_ALTERNATIVE_EVENT_RECORD

#include "ThePEG/CLHEPWrap/Lorentz5Vector.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"

namespace ThePEG {

typedef Base EventRecordBase;
// EventRecordBase is the base class of all event record classes. It
// should be typedefed to a class which allows for garbage collection,
// since none of the event record classes are deleted explicitly.
typedef Ptr<EventRecordBase>::pointer EventBasePtr;
typedef Ptr<EventRecordBase>::const_pointer cEventBasePtr;
typedef Ptr<EventRecordBase>::transient_pointer tEventBasePtr;
typedef Ptr<EventRecordBase>::transient_const_pointer tcEventBasePtr;
typedef Rebinder<EventRecordBase> EventTranslationMap;

// See ThePEG.h for declaration of Event, Collision, Step, SubProcess,
// Particle, ParticleData, and the different garbage collecting
// pointers to these

typedef Particle ParticleClass;
typedef ParticleData ParticleDataClass;

typedef Ptr<ParticleDataClass>::pointer EventPDPtr;
typedef Ptr<ParticleDataClass>::const_pointer cEventPDPtr;
typedef Ptr<ParticleDataClass>::transient_pointer tEventPDPtr;
typedef Ptr<ParticleDataClass>::transient_const_pointer tcEventPDPtr;

// See ThePEG.h for declaration of 

typedef vector<PPtr> ParticleVector;
typedef vector<tPPtr> tParticleVector;
// typedef set<PPtr> ParticleSet;
// ThePEG_DECLARE_SET(PPtr,ParticleSet);
typedef set<PPtr, less<PPtr>, Allocator<PPtr> > ParticleSet;
typedef set<tPPtr, less<tPPtr>, Allocator<tPPtr> > tParticleSet;
typedef set<tcPPtr, less<tcPPtr>, Allocator<tcPPtr> > tcParticleSet;
typedef vector<StepPtr> StepVector;
typedef vector<SubProPtr> SubProcessVector;
typedef vector<tSubProPtr> tSubProcessVector;
typedef vector<CollPtr> CollisionVector;
// typedef set<StepPtr> StepSet;
// ThePEG_DECLARE_SET(StepPtr,StepSet);
typedef set<StepPtr, less<StepPtr>, Allocator<StepPtr> > StepSet;
// typedef set<SubProPtr> SubProcessSet;
// ThePEG_DECLARE_SET(SubProPtr,SubProcessSet);
typedef set<SubProPtr, less<SubProPtr>, Allocator<SubProPtr> > SubProcessSet;

struct Spin { int s; };

struct EventConfig {

  static tcEventBasePtr currentGenerator;
  // If this is set during persistent output, only the PDG number of a
  // particle type is written rather than the full ParticleData
  // object. Also only the name of handlers is written rather than the
  // full objects. When this is read back in again, the
  // 'currentGenerator' must be set so that conversion from
  // name/number back to objects can be done.

  static void putHandler(PersistentOStream & os, tcEventBasePtr h);
  static void getHandler(PersistentIStream & is, tcEventBasePtr & h);
  static void putParticleData(PersistentOStream & os, tcEventPDPtr pd);
  static void getParticleData(PersistentIStream & is, cEventPDPtr & pd);
  static string nameHandler(tcEventBasePtr h);

};

}

#else

#include ThePEG_ALTERNATIVE_EVENT_RECORD

#endif

#endif /* ThePEG_NOT_ThePEG */


#endif /* ThePEG_EventConfig_H */

