// -*- C++ -*-
#ifndef ThePEG_Repository_H
#define ThePEG_Repository_H
// This is the declaration of the Repository class.

#include "ThePEG/Config/ThePEG.h"
#include "BaseRepository.h"
#include "EventGenerator.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDT/MatcherBase.h"
#include "ThePEG/PDT/DecayMode.h"

namespace ThePEG {

/**
 * Repository inherits from the BaseRepository class. While
 * BaseRepository is fairly general and could in principle be used for
 * any program where sets of InterfacedBase objects are managed, the
 * Repository is ThePEG specific in that it deals with ParticleData,
 * ParticleMatchers, DecayModes, and EventGenerators.
 *
 * One main function is to write an EventGenerator to disk using
 * saveRun(). Here all objects needed for the run, including the
 * EventGenerator is cloned and isolated from the other objects in the
 * Repository (and are hence not handled by the Repository anymore)
 * before they are all persistently written out to disk.
 *
 * The Register() function simply pass the objects to the corresonding
 * method in BaseRepository, but if the object is a ParticleData,
 * ParticleMatcher or a DecayMode, they are stored separately. In
 * addition, if a ParticleData with a given PDG id number was not yet
 * added to the list of default particles, this one will be.
 *
 * @see BaseRepository
 * @see InterfacedBase
 * @see ParticleData
 * @see ParticleMatcher
 * @see DecayMode
 * @see EventGenerator
 * 
 */
class Repository: public BaseRepository {

public:

  /** A map of EventGenerator objects indexed by their run name. */
  typedef map<string,EGPtr> GeneratorMap;

public:

  /** @name Functions for register objects in the Repository. */
  //@{
  /**
   * Register an object with BaseRepository::Register() and add it to
   * the list of particles, decay modes or matchers if of any of those
   * types.
   */
  static void Register(IBPtr);

  /**
   * Register an object with BaseRepository::Register() and add it to
   * the list of particles, decay modes or matchers if of any of those
   * types.
   */
  static void Register(IBPtr, string newName);
  //@}

  /** @name Access ParticleData, MatcherBase and DecayMode objects in
      the Repository. */
  //@{
  /**
   * Add a particle to the list of default ones. If one of the same
   * type alredy existed, it is removed from the list (but not from
   * the repository).
   */
  static void defaultParticle(tPDPtr);

  /**
   * Get a pointer to the default particle of the given type or
   * generic name.
   */
  static PDPtr defaultParticle(long id);
  /**
   * Get a pointer to the default particle of the given type or
   * generic name.
   */
  static tPDPtr findParticle(string name);

  /**
   * Return the set of all particles in the repository.
   */
  inline static const ParticleDataSet & allParticles();

  /**
   * Return the set of all matchers in the repository.
   */
  inline static const MatcherSet & allMatchers();

  /**
   * Find a matcher or decay mode with a given generic name
   */
  static tPMPtr findMatcher(string name);
  /**
   * Find a matcher or decay mode with a given generic name
   */
  static tDMPtr findDecayMode(string name);

  /**
   * Special function for copying particles. Also corresponding
   * anti-particle is copied to the same directory. In addition, their
   * decay modes are copied.
   */
  static string copyParticle(tPDPtr, string);
  //@}

  /** @name Functions to isolate Eventgenerator objects. */
  //@{
  /**
   * Isolate an event generator, \a eg, and save it to disk in a file
   * named \a name (with <code>.run</code> appended.
   */
  static EGPtr makeRun(tEGPtr eg, string name);

  /**
   * Isolate an event generatorn, named \a EGname, set its run \a name
   * and save it to a file named \a filename.
   */
  static void saveRun(string EGname, string name, string filename);
  //@}

  /** @name I/O functions for the Repository. */
  //@{
  /**
   * Load a whole repository from the given file. All objects
   * previously in the Repository are discarded.
   */
  static void load(string filename);

  /**
   * Save the repository to the given file.
   */
  static void save(string filename);

  /**
   * Save the repository to the default file.
   */
  inline static void save();

  /**
   * Write some statistics about the repository to the standard output.
   */
  static void stats(ostream &);
  //@}

  /** @name Command-line interface functions. */
  //@{
  /**
   * Read commands from a stream and send them one by one to exec().
   *
   * @param is the stream from which to read commands.
   * @param os the stream where output is written.
   * @param prompt before reading a command from \a is, this string is
   * written to \a os.
   */
  static void read(istream & is, ostream & os, string prompt = "");

  /**
   * Interpret the command in \a cmd and return possible
   * messages. This is the main function for the command-line
   * interface. The syntax is described elsewhere. The ostream
   * argument is currently unused.
   */
  static string exec(string cmd, ostream &);
  //@}

private:

  /**
   * Used by Register.
   */
  static void registerParticle(tPDPtr);

  /**
   * Used by Register.
   */
  static void registerMatcher(tPMPtr);

  /**
   * Used by Register.
   */
  static void registerDecayMode(tDMPtr);

protected:

  /** @name Functions containing the static instances of objects used
      by the repository. */
  //@{
  /**
   * The set of default particles.
   */
  static ParticleMap & defaultParticles();

  /**
   * The set of all particles.
   */
  static ParticleDataSet & particles();

  /**
   * The set of all matchers.
   */
  static MatcherSet & matchers();

  /**
   * The set of all decay modes.
   */
  static DecayModeSet & decayModes();

  /**
   * All isolated generators mapped to their run name.
   */
  static GeneratorMap & generators();

  /**
   * The default file name used by save().
   */
  static string & currentFileName();
  //@}

};

}

#include "Repository.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Repository.tcc"
#endif

#endif /* ThePEG_Repository_H */
