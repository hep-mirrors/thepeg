// -*- C++ -*-
#ifndef ThePEG_Repository_H
#define ThePEG_Repository_H
//
// This is the declaration of the <!id>Repository<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>Repository<!!id> inherits from the
// <!class>BaseRepository<!!class> class. While
// <!class>BaseRepository<!!class> is fairly general and could in
// principle be used for any program where sets of
// <!class>InterfacedBase<!!class> are managed, the
// <!id>Repository<!!id> is ThePEG specific in that it deals with
// <!class>ParticleData<!!class>, <!class>ParticleMatcher<!!class>s,
// <!class>DecayMode<!!class>s, and <!class>EventGenerator<!!class>s.
//
// One main function is to write an <!class>EventGenerator<!!class> to
// disk using the <!id>saveRun<!!id> method. Hera all objects needed
// for the run, including the <!class>EventGenerator<!!class> is
// cloned and isolated from the <!id>Repository<!!id> (and are hence
// not handled by the <!id>Repository<!!id> anymore) before they are
// all persistently written out to disk.
//
// The <!id>Register<!!id> simply pass the objects to the corresonding
// method in BaseRepository, but if the object is a
// <!class>ParticleData<!!class>, <!class>ParticleMatcher<!!class> or
// a <!class>DecayMode<!!class>, they are stored separately. In
// addition, if a <!class>ParticleData<!!class> of a given type was
// not yet added to the list of default particles, this one will be.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:BaseRepository.html">BaseRepository.h</a>,
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:ParticleData.html">ParticleData.h</a>,
// <a href="http:ParticleMatcher.html">ParticleMatcher.h</a>,
// <a href="http:DecayMode.html">DecayMode.h</a>,
// <a href="http:EventGenerator.html">EventGenerator.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "BaseRepository.h"
#include "EventGenerator.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDT/MatcherBase.h"
#include "ThePEG/PDT/DecayMode.h"

namespace ThePEG {

class Repository: public BaseRepository {

public:

  typedef map<string,EGPtr> GeneratorMap;

public:

  static void Register(IBPtr);
  static void Register(IBPtr, string newName);
  // Register an object to the BaseRepository and add it to the list
  // of particles, decay modes or matchers if of any of those types.

  static void defaultParticle(tPDPtr);
  // Add a particle to the list of default ones. If one of the same
  // type alredy existed, it is removed from the list (but not from
  // the repository).

  static PDPtr defaultParticle(long id);
  static tPDPtr findParticle(string name);
  // Get a pointer to the default particle of the given type or
  // generic name.

  static EGPtr makeRun(tEGPtr eg, string name);
  static void saveRun(string EGname, string name, string filename);
  // Isolate an event generator and save it to disk.

  inline static const ParticleDataSet & allParticles();
  // Return the set of all particles in the repository.

  inline static const MatcherSet & allMatchers();
  // Return the set of all matchers in the repository.

  static tPMPtr findMatcher(string name);
  static tDMPtr findDecayMode(string name);
  // Find a matcher or decay mode with a given generic name

  static void load(string filename);
  // Load a while repository from the given file. All objects in the
  // Repository are discarded.

  static void save(string filename);
  inline static void save();
  // Save the repository to the given/default file.

  static void stats(ostream &);
  // Write some statistics about the repository to the standard output.

  static void read(istream &, ostream &, string prompt = "");
  // Read commands from a stream.

  static string exec(string, ostream & os);
  // Execute a command.

  static string copyParticle(tPDPtr, string);
  // Special function for copying particles. Also corresponding
  // anti-particle is copied to the same directory. In addition, their
  // decay modes are copied.

private:

  static void registerParticle(tPDPtr);
  static void registerMatcher(tPMPtr);
  static void registerDecayMode(tDMPtr);
  // Used by Register.

protected:

  static ParticleMap & defaultParticles();
  // The set of default particles.

  static ParticleDataSet & particles();
  // The set of all particles.

  static MatcherSet & matchers();
  // The set of all matchers.

  static DecayModeSet & decayModes();
  // The set of all decay modes.

  static GeneratorMap & generators();
  // All isolated generators mapped to their run name.

  static string & currentFileName();
  // The default file name used by save().

};

}

#include "Repository.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Repository.tcc"
#endif

#endif /* ThePEG_Repository_H */
