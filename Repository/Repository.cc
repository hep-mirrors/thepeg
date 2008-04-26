// -*- C++ -*-
//
// Repository.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Repository class.
//

#include "Repository.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/Handlers/EventHandler.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/Repository/Strategy.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Config/algorithm.h"
#include "ThePEG/Utilities/DynamicLoader.h"
#include "ThePEG/Utilities/StringUtils.h"
#include "ThePEG/Utilities/SystemUtils.h"

using namespace ThePEG;

ParticleMap & Repository::defaultParticles() {
  static ParticleMap theMap;
  return theMap;
}


ParticleDataSet & Repository::particles() {
  static ParticleDataSet theSet;
  return theSet;
}

MatcherSet & Repository::matchers() {
  static MatcherSet theSet;
  return theSet;
}

DecayModeSet & Repository::decayModes() {
  static DecayModeSet theSet;
  return theSet;
}

Repository::GeneratorMap & Repository::generators() {
  static GeneratorMap theMap;;
  return theMap;
}

string & Repository::currentFileName() {
  static string theCurrentFileName;
  return theCurrentFileName;
}

string & Repository::currentReadDir() {
  static string theCurrentReadDir;
  return theCurrentReadDir;
}

int & Repository::exitOnError() {
  static int exitonerror = 0;
  return exitonerror;
}

void Repository::cleanup() {
  generators().clear();
}

void Repository::Register(IBPtr ip) {
  BaseRepository::Register(ip);
  registerParticle(dynamic_ptr_cast<PDPtr>(ip));
  registerMatcher(dynamic_ptr_cast<PMPtr>(ip));
  registerDecayMode(dynamic_ptr_cast<DMPtr>(ip));
}

void Repository::Register(IBPtr ip, string newName) {
  DirectoryAppend(newName);
  BaseRepository::Register(ip, newName);
  registerParticle(dynamic_ptr_cast<PDPtr>(ip));
  registerMatcher(dynamic_ptr_cast<PMPtr>(ip));
  registerDecayMode(dynamic_ptr_cast<DMPtr>(ip));
}

void Repository::registerParticle(tPDPtr pd) {
  if ( !pd || member(particles(), pd) ) return;
  particles().insert(pd);
  CreateDirectory(pd->fullName());
  if ( !member(defaultParticles(), pd->id()) )
    defaultParticles()[pd->id()] = pd;
  for ( MatcherSet::iterator it = matchers().begin();
	it != matchers().end(); ++it) (*it)->addPIfMatch(pd);
}

void Repository::registerMatcher(tPMPtr pm) {
  if ( !pm || member(matchers(), pm) ) return;
  pm->addPIfMatchFrom(particles());
  for ( MatcherSet::iterator it = matchers().begin();
	it != matchers().end(); ++it) {
    (*it)->addMIfMatch(pm);
    pm->addMIfMatch(*it);
  }
  matchers().insert(pm);
}

void Repository::registerDecayMode(tDMPtr dm) {
  if ( !dm || member(decayModes(), dm) ) return;
  decayModes().insert(dm);
}

tPDPtr Repository::findParticle(string name) {
  for ( ParticleMap::iterator pit = defaultParticles().begin();
	pit != defaultParticles().end(); ++pit )
    if ( pit->second->PDGName() == name ) return pit->second;
  return tPDPtr();
}

tPMPtr Repository::findMatcher(string name) {
  for ( MatcherSet::iterator mit = matchers().begin();
	mit != matchers().end(); ++mit )
    if ( name == (**mit).name() ) return *mit;
  return tPMPtr();
}

tDMPtr Repository::findDecayMode(string name) {
  for ( DecayModeSet::iterator dit = decayModes().begin();
	dit != decayModes().end(); ++dit )
    if ( name == (**dit).tag() ) return *dit;
  return tDMPtr();
}

void Repository::saveRun(string EGname, string name, string filename) {
  EGPtr eg = BaseRepository::GetObject<EGPtr>(EGname);
  EGPtr run = makeRun(eg, name);
  PersistentOStream os(filename, globalLibraries());
  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "Saving event generator '" << name << "'... " << flush;
  os << run;
  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "done" << endl;
}

EGPtr Repository::makeRun(tEGPtr eg, string name) {

  // Clone all objects relevant for the OldEventGenerator. This is
  // the OldEventGenerator itself, all particles and all particle
  // matchers. 'localObject' is the set of all object refered to by
  // the generator particles and matcher and in the end these are
  // cloned as well.

  // Clone all Particle matchers

  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "Making event generator '" << name << "':" << endl
	   << "Updating all objects... " << flush;

  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "done\nCloning matchers and particles... " << flush;

  MatcherSet localMatchers;
  ObjectSet localObjects;
  ObjectSet clonedObjects;
  TranslationMap trans;

  for ( MatcherSet::iterator mit = matchers().begin();
	mit != matchers().end(); ++mit ) {
    PMPtr pm = clone(**mit);
    pm->clear();
    trans[*mit] = pm;
    localMatchers.insert(pm);
    clonedObjects.insert(pm);
    localObjects.insert(*mit);
    addReferences(*mit, localObjects);
  }


  // Clone the particles. But only the ones which should be
  // used. First select the localParticles of the OldEventGenerator, then
  // add particles from the strategy of the OldEventGenerator which have
  // not already been selected. Finally add particles from the global
  // default which have not already been selected.
  PDVector allParticles;
  for ( ParticleMap::const_iterator pit = eg->localParticles().begin();
 	pit != eg->localParticles().end(); ++pit )
    allParticles.push_back(pit->second);
  if ( eg->strategy() ) {
    tcStrategyPtr strat = eg->strategy();
    for ( ParticleMap::const_iterator pit = strat->particles().begin();
 	  pit != strat->particles().end(); ++pit )
      allParticles.push_back(pit->second);
    if ( eg->strategy()->localParticlesDir().length() ) {
      string dir = eg->strategy()->localParticlesDir();
      for ( ParticleDataSet::iterator pit = particles().begin();
	    pit != particles().end(); ++pit )
	if ( (**pit).fullName().substr(0, dir.length()) == dir )
	  allParticles.push_back(*pit);
    }
  }
  for ( ParticleMap::iterator pit = defaultParticles().begin();
	pit != defaultParticles().end(); ++pit )
    allParticles.push_back(pit->second);

  ParticleMap localParticles;

  for ( PDVector::iterator pit = allParticles.begin();
	pit != allParticles.end(); ++pit ) {
    ParticleMap::iterator it = localParticles.find((**pit).id());
    if ( it == localParticles.end() ) {
      PDPtr pd = clone(**pit);
      trans[*pit] = pd;
      localParticles[pd->id()] = pd;
      clonedObjects.insert(pd);
      localObjects.insert(*pit);
      addReferences(*pit, localObjects);
    } else
      trans[*pit] = it->second;
  }

  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "done\nCloning other objects... " << flush;

  // Clone the OldEventGenerator object to be used:
  localObjects.insert(eg);
  addReferences(eg, localObjects);
  EGPtr egrun = clone(*eg);
  clonedObjects.insert(egrun);
  trans[eg] = egrun;

  for ( ObjectSet::iterator it = localObjects.begin();
	it != localObjects.end(); ++it ) {
    if ( member(trans.map(), *it) ) continue;
    IBPtr ip = clone(**it);
    trans[*it] = ip;
    clonedObjects.insert(ip);
  }

  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "done\nRebind references... " << flush;

  IVector defaults;

  trans.translate(inserter(defaults), eg->defaultObjects().begin(),
		  eg->defaultObjects().end());
  if ( eg->strategy() )
    trans.translate(inserter(defaults),
		    eg->strategy()->defaultObjects().begin(),
		    eg->strategy()->defaultObjects().end());

  for ( ObjectSet::iterator it = clonedObjects.begin();
	it != clonedObjects.end(); ++it ) {
    dynamic_cast<Interfaced &>(**it).theGenerator = egrun;
    rebind(**it, trans, defaults);
  }

  // Now, dependencies may have changed, so we do a final round of
  // updates.
  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "done\nUpdating cloned objects... " << flush;


  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "done\nInitializing... " << flush;

  clonedObjects.erase(egrun);
  egrun->setup(name, clonedObjects, localParticles, localMatchers);

  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "done" << endl;

  generators()[name] = egrun;

  return egrun;

}

PDPtr Repository::defaultParticle(long id) {
  ParticleMap::iterator pit = defaultParticles().find(id);
  return pit == defaultParticles().end()? PDPtr(): pit->second;
}

void Repository::defaultParticle(tPDPtr pdp) {
  if ( pdp ) defaultParticles()[pdp->id()] = pdp;
}

struct ParticleOrdering {
  bool operator()(tcPDPtr p1, tcPDPtr p2) {
    return abs(p1->id()) > abs(p2->id()) ||
      ( abs(p1->id()) == abs(p2->id()) && p1->id() > p2->id() ) ||
      ( p1->id() == p2->id() && p1->fullName() > p2->fullName() );
  }
};

struct ModeOrdering {
  bool operator()(tcDMPtr d1, tcDMPtr d2) {
    ParticleOrdering ord;
    return ord(d1->parent(), d2->parent()) ||
      ( !ord(d2->parent(), d1->parent()) &&
	( d1->tag() < d2->tag() ||
	  ( d1->tag() == d2->tag() && d1->fullName() < d2->fullName() ) ) );
  }
};

struct MatcherOrdering {
  bool operator()(tcPMPtr m1, tcPMPtr m2) {
    return m1->name() < m2->name() ||
      ( m1->name() == m2->name() && m1->fullName() < m2->fullName() );
  }
};

struct InterfaceOrdering {
  bool operator()(tcIBPtr i1, tcIBPtr i2) {
    return i1->fullName() < i2->fullName();
  }
};

void Repository::save(string filename) {
  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "saving '" << filename << "'... " << flush;
  PersistentOStream os(filename, globalLibraries());
  set<tcPDPtr,ParticleOrdering>
    part(particles().begin(), particles().end());
  set<tcPMPtr,MatcherOrdering>  match(matchers().begin(), matchers().end());
  set<tcDMPtr,ModeOrdering> modes(decayModes().begin(), decayModes().end());

  os << objects().size();
  for ( ObjectMap::iterator it = objects().begin();
	it != objects().end(); ++it ) os << it->second;
  os << defaultParticles() << part << match << modes << generators()
     << directories() << directoryStack() << globalLibraries();
  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "(" << objects().size() << " objects in " << directories().size()
	   << " directories) done" << endl;
}

void Repository::load(string filename) {
  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "loading '" << filename << "'... " << flush;
  currentFileName() = filename;
  PersistentIStream * is = new PersistentIStream(filename);
  if ( !*is ) {
    delete is;
    is = new PersistentIStream(SystemUtils::getenv("ThePEG_INSTALL_PATH")
			       + "/" + filename);
    if ( !*is ) {
      delete is;
      cerr() << "Error: Could not find repository '" << filename << "'" << endl;
      return;
    }
  }
  *is >> allObjects() >> defaultParticles()
      >> particles() >> matchers() >> decayModes() >> generators()
      >> directories() >> directoryStack() >> globalLibraries();
  delete is;
  objects().clear();
  for ( ObjectSet::iterator it = allObjects().begin();
	it != allObjects().end(); ++it )
    objects()[(**it).fullName()] = *it;

  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "(" << objects().size() << " objects in " << directories().size()
	   << " directories) done\nUpdating... " << flush;
  BaseRepository::resetAll(allObjects());
  BaseRepository::update();

  if ( ThePEG_DEBUG_ITEM(3) )
    clog() << "done" << endl;
}

void Repository::stats(ostream & os) {
  os << "number of objects:        " << setw(6) << objects().size() << endl;
  os << "number of objects (all):  " << setw(6) << allObjects().size() << endl;
  os << "number of particles:        " << setw(6) << particles().size() << endl;
  os << "number of matchers:         " << setw(6) << matchers().size() << endl;
  os << "number of decay modes:      " << setw(6)
     << decayModes().size() << endl;
}

void Repository::read(string filename, ostream & os) {
  currentReadDir() = StringUtils::dirname(filename);
  ifstream is(filename.c_str());
  if ( !is ) {
    cerr() << "Error: Could not find input file '" << filename << "'" << endl;
    return;
  }
  Repository::read(is, os);
}

void Repository::read(istream & is, ostream & os, string prompt) {
  string line;
  if ( prompt.size() ) os << prompt;
  while ( getline(is, line) ) {
    while ( !line.empty() && line[line.size() - 1] == '\\' ) {
      line[line.size() - 1] = ' ';
      string cont;
      if ( prompt.size() ) os << "> ";
      getline(is, cont);
      line += cont;
    }
    if ( prompt.empty() && ThePEG_DEBUG_LEVEL > 0 )
      os << "(" << line << ")" << endl;;
    string reply = exec(line, os);
    if ( reply.size() ) os << reply;
    if ( reply.size() && reply[reply.size()-1] != '\n' ) os << endl;
    if ( exitOnError() && reply.size() >= 7 && reply.substr(0, 7) == "Error: " )
      exit(exitOnError());
    if ( prompt.size() ) os << prompt;
  }
  if ( prompt.size() ) os << endl;
}

string Repository::copyParticle(tPDPtr p, string newname) {
  DirectoryAppend(newname);
  
  string newdir = newname.substr(0, newname.rfind('/')+1);
  newname =newname.substr(newname.rfind('/')+1);
  if ( newname.empty() ) newname = p->name();
  if ( GetPointer(newdir + newname) )
    return "Error: Cannot create particle " + newdir + newname +
      ". Object already exists.";
  if ( p->CC() && GetPointer(newdir + p->CC()->name()) )
    return "Error: Cannot create anti-particle " + newdir + newname +
      ". Object already exists.";
  PDPtr pd = p->pdclone();
  Register(pd, newdir + newname);
  pd->theDecaySelector.clear();
  pd->theDecayModes.clear();
  if ( p->CC() ) {
    PDPtr apd = p->CC()->pdclone();
    Register(apd, newdir + apd->name());
    apd->theDecaySelector.clear();
    apd->theDecayModes.clear();
    pd->theAntiPartner = apd;
    apd->theAntiPartner = pd;
    pd->syncAnti = p->syncAnti;
    apd->syncAnti = p->CC()->syncAnti;
  }
  HoldFlag<> dosync(pd->syncAnti, true);
  for ( DecaySet::const_iterator it = p->theDecayModes.begin();
	it != p->theDecayModes.end(); ++it )
    pd->addDecayMode(*it);
  return "";
}

void Repository::remove(tIBPtr ip) {
  ObjectMap::iterator it = objects().find(ip->fullName());
  if ( it == objects().end() || ip != it->second ) return;
  objects().erase(it);
  allObjects().erase(ip);
  if ( dynamic_ptr_cast<tPDPtr>(ip) ) {
    particles().erase(dynamic_ptr_cast<tPDPtr>(ip));
    defaultParticles().erase(dynamic_ptr_cast<tPDPtr>(ip)->id());
  }
  if ( dynamic_ptr_cast<tPMPtr>(ip) )
    matchers().erase(dynamic_ptr_cast<tPMPtr>(ip));
  if ( dynamic_ptr_cast<tDMPtr>(ip) )
    decayModes().erase(dynamic_ptr_cast<tDMPtr>(ip));
}

string Repository::remove(const ObjectSet & rmset) {
  ObjectSet refset;
  for ( ObjectMap::const_iterator i = objects().begin();
	i != objects().end(); ++i ) {
    if ( member(rmset, i->second) ) continue;
    IVector ov = DirectReferences(i->second);
    for ( int j = 0, M = ov.size(); j < M; ++j )
      if ( member(rmset, ov[j]) ) {
	refset.insert(i->second);
	break;
      }
  }
  if ( refset.empty() ) {
    for ( ObjectSet::iterator oi = rmset.begin(); oi != rmset.end(); ++oi )
      remove(*oi);
    return "";
  }
  string ret = "Error: cannot remove the objects because the following "
    "objects refers to some of them:\n";
  for ( ObjectSet::iterator oi = refset.begin(); oi != refset.end(); ++oi )
    ret += (**oi).fullName() + "\n";
  return ret;
}
   
string Repository::exec(string command, ostream & os) {
  string cpcmd = command;
  try {
    string verb = StringUtils::car(command);
    command = StringUtils::cdr(command);
    if ( verb == "rm" ) {
      ObjectSet rmset;
      while ( !command.empty() ) {
	string name = StringUtils::car(command);
	DirectoryAppend(name);
	IBPtr obj = GetPointer(name);
	if ( !obj ) return "Error: Could not find object named " + name;
	rmset.insert(obj);
	command = StringUtils::cdr(command);
      }
      return remove(rmset);
    }
    if ( verb == "rmdir" || verb == "rrmdir" ) {
      string dir = StringUtils::car(command);
      DirectoryAppend(dir);
      if ( dir[dir.size() - 1] != '/' ) dir += '/';
      if ( !member(directories(), dir) )
	return verb == "rmdir"? "Error: No such directory.": "";
      IVector ov = SearchDirectory(dir);
      if ( ov.size() && verb == "rmdir" )
	return "Error: Cannot remove a non-empty directory. "
	  "(Use rrmdir do remove all object and subdirectories.)";
      ObjectSet rmset(ov.begin(), ov.end());
      string ret = remove(rmset);
      if ( !ret.empty() ) return ret;
      StringVector dirs(directories().begin(), directories().end());
      for ( int i = 0, N = dirs.size(); i < N; ++ i )
	if ( dirs[i].substr(0, dir.size()) == dir )
	  directories().erase(dirs[i]);
      for ( int i = 0, N = directoryStack().size(); i < N; ++i )
	if ( directoryStack()[i].substr(0, dir.size()) == dir )
	  directoryStack()[i] = '/';
      return "";
    }
    if ( verb == "cp" ) {
      string name = StringUtils::car(command);
      DirectoryAppend(name);
      tPDPtr p = dynamic_ptr_cast<tPDPtr>(GetPointer(name));
      if ( p ) return copyParticle(p, StringUtils::cdr(command));
      return BaseRepository::exec(cpcmd, os);
    }
    if ( verb == "decaymode" ) {
      string tag = StringUtils::car(command);
      tPDPtr pd;
      string::size_type pos = tag.find("->");
      if ( pos == string::npos )
	return "Error: Could not create decay mode from the tag " +
	  StringUtils::car(command);
      string pobj = tag.substr(0,pos);
      try {
	DirectoryAppend(pobj);
	pd = dynamic_ptr_cast<tPDPtr>(GetPointer(pobj));
      } catch ( ... ) {}
      pos = tag.rfind('/');
      if ( pos != string::npos ) {
	if ( !pd ) {
	  pobj = tag.substr(0,pos);
	  DirectoryAppend(pobj);
	  pd = dynamic_ptr_cast<tPDPtr>(GetPointer(pobj));
	  if ( !pd ) return "Error: cannot add decay mode to '"
		       + pobj + "'. No such particle";
	}
	tag = tag.substr(pos + 1);
      }
      DMPtr dm = DecayMode::constructDecayMode(tag, pd);
      if ( !dm ) return "Error: Could not create decay mode from the tag " +
		   StringUtils::car(command);
      istringstream is(StringUtils::cdr(command));
      readSetup(dm, is);
      if ( !dm->CC() ) return "";
      is.clear();
      is.seekg(0);
      readSetup(dm->CC(), is);
      return "";
    }
    if ( verb == "makeanti" ) {
      string name = StringUtils::car(command);
      DirectoryAppend(name);
      tPDPtr p = dynamic_ptr_cast<tPDPtr>(GetPointer(name));
      if ( !p ) return "Error: No particle named " + name;
      name = StringUtils::car(StringUtils::cdr(command));
      DirectoryAppend(name);
      tPDPtr ap = dynamic_ptr_cast<tPDPtr>(GetPointer(name));
      if ( !ap ) return "Error: No particle named " + name;
      ParticleData::antiSetup(PDPair(p, ap));
      return "";
    }
    if ( verb == "read" ) {
      string file = StringUtils::car(command);
      string dir = currentReadDir();
      if (dir != "")
 	file = dir + '/' + file;
      ifstream input(file.c_str());
      if (!input) return "Error: Could not access file " + file;
      read(input, os);
      return "";
    }      
    if ( verb == "load" ) {
      load(StringUtils::car(command));
      return "";
    }      
    if ( verb == "save" ) {
      save(StringUtils::car(command));
      return "";
    }
    if ( verb == "lsruns" ) {
      string ret;
      for ( GeneratorMap::iterator ieg = generators().begin();
	    ieg != generators().end(); ++ieg ) ret += ieg->first + "\n";
      return ret;
    }
    if ( verb == "makerun" ) {
      string runname = StringUtils::car(command);
      string generator = StringUtils::car(StringUtils::cdr(command));
      DirectoryAppend(generator);
      EGPtr eg = BaseRepository::GetObject<EGPtr>(generator);
      makeRun(eg, runname);
      return "";
    }
    if ( verb == "rmrun" ) {
      string runname = StringUtils::car(command);
      generators().erase(runname);
      return "";
    }
    if ( verb == "saverun" || verb == "saverunfile" || verb == "run" ) {
      string runname = StringUtils::car(command);
      string generator = StringUtils::car(StringUtils::cdr(command));
      DirectoryAppend(generator);
      GeneratorMap::iterator ieg = generators().find(runname);
      EGPtr eg;
      if ( ieg == generators().end() ) {
	eg = BaseRepository::GetObject<EGPtr>(generator);
	eg = makeRun(eg, runname);
      } else
	eg = ieg->second;
      if ( !eg )
	return "Error: Could not create/find run named'" + runname + "'.";
      if ( verb == "run" ) 
	eg->go();
      else if ( verb == "saverunfile" ) {
	string file = generator;
	PersistentOStream os(file, globalLibraries());
	os << eg;
	if ( !os ) return "Save failed! (I/O error)";
      } else {
	string file = eg->path() + "/" + eg->filename() + ".run";
	PersistentOStream os(file, globalLibraries());
	os << eg;
	if ( !os ) return "Save failed! (I/O error)";
      }
      return "";
    }
    if ( verb == "removerun" ) {
      string runname = StringUtils::car(command);
      GeneratorMap::iterator ieg = generators().find(runname);
      if ( ieg != generators().end() ) {
	generators().erase(ieg);
	return "";
      } else
	return "Error: No run named '" + runname + "' available.";
    }
    if ( verb == "create" ) {
      string className = StringUtils::car(command);
      command = StringUtils::cdr(command);
      string name = StringUtils::car(command);
      const ClassDescriptionBase * db = DescriptionList::find(className);
      command = StringUtils::cdr(command);
      while ( !db && command.length() ) {
	string library = StringUtils::car(command);
	command = StringUtils::cdr(command);
	DynamicLoader::load(library);
	db = DescriptionList::find(className);
      }
      if ( !db ) {
	string msg = "Error: " + className + ": No such class found.";
	if ( !DynamicLoader::lastErrorMessage.empty() )
	  msg += "\nerror message from dynamic loader:\n" +
	    DynamicLoader::lastErrorMessage;
	return msg;
      }
      IBPtr obj = dynamic_ptr_cast<IBPtr>(db->create());
      if ( !obj ) return "Error: Could not create object of this class class.";
      if ( name.empty() ) return "Error: No name specified.";
      Register(obj, name);
      return "";
    }
    if ( verb == "defaultparticle" ) {
      while ( !command.empty() ) {
	string name = StringUtils::car(command);
	DirectoryAppend(name);
	tPDPtr p = dynamic_ptr_cast<tPDPtr>(GetPointer(name));
	if ( !p ) return "Error: No particle named " + name;
	defaultParticle(p);
	command = StringUtils::cdr(command);
      }
      return "";
    }
    if ( verb == "EXITONERROR" ) {
      exitOnError() = 1;
      return "";
    }
  }
  catch (const Exception & e) {
    e.handle();
    return "Error: " + e.message();
  }

  return BaseRepository::exec(cpcmd, os);
}

Repository::Repository() {
  ++ninstances;
}

Repository::~Repository() {
  --ninstances;
  if ( ninstances <= 0 ) {
    generators().clear();
  }
}

int Repository::ninstances = 0;

