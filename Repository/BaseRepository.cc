// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the BaseRepository class.
//

#include "BaseRepository.h"
#include "ThePEG/Config/algorithm.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/InterfaceBase.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/DescriptionList.h"
#include "ThePEG/Utilities/HoldFlag.h"
#include "ThePEG/Utilities/TypeInfo.h"
#include "ThePEG/Utilities/DynamicLoader.h"
#include "ThePEG/Utilities/StringUtils.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "BaseRepository.tcc"
#endif

using namespace ThePEG;

ostream *& BaseRepository::coutp() {
  static ostream * theCout = &std::cout;
  return theCout;
}

ostream *& BaseRepository::cerrp() {
  static ostream * theCerr = &std::cerr;
  return theCerr;
}

ostream *& BaseRepository::clogp() {
  static ostream * theClog = &std::clog;
  return theClog;
}

bool & BaseRepository::updating() {
  static bool theBool = false;
  return theBool;
}

ObjectMap & BaseRepository::objects() {
  static ObjectMap theObjectMap;
  return theObjectMap;
}

ObjectSet & BaseRepository::allObjects() {
  static ObjectSet theObjectSet;
  return theObjectSet;
}

BaseRepository::TypeInterfaceMap & BaseRepository::interfaces() {
  static TypeInterfaceMap theInterfaceMap;
  return theInterfaceMap;
}

BaseRepository::TypeDocumentationMap & BaseRepository::documentations() {
  static TypeDocumentationMap theDocumentationMap;
  return theDocumentationMap;
}

BaseRepository::DirectorySet & BaseRepository::directories() {
  static char root[1][2] = {"/"};
  static DirectorySet theDirectories(root, root+1);
  return theDirectories;
}

BaseRepository::StringVector & BaseRepository::directoryStack() {
  static StringVector theDirectoryStack(1, "/");
  return theDirectoryStack;
}

void BaseRepository::Register(const InterfaceBase & ib, const type_info & i) {
  const ClassDescriptionBase * db = DescriptionList::find(i);
  if ( db ) interfaces()[db].insert(&ib);
}

void BaseRepository::
Register(const ClassDocumentationBase & cd, const type_info & i) {
  const ClassDescriptionBase * db = DescriptionList::find(i);
  if ( db ) documentations()[db] = &cd;
}

void BaseRepository::Register(IBPtr ip, string newName) {
  DirectoryAppend(newName);
  ip->name(newName);
  Register(ip);
}

void BaseRepository::Register(IBPtr ip) {
  if ( !ip || member(allObjects(), ip) ) return;
  while ( member(objects(), ip->fullName()) ) ip->name(ip->fullName() + "#");
  objects()[ip->fullName()] = ip;
  allObjects().insert(ip);
  ip->clear();
  ip->update();
  ip->touch();
}

void BaseRepository::DirectoryAppend(string & name) {
  if ( name[0] != '/' ) name = directoryStack().back() + name;
}  

void BaseRepository::CreateDirectory(string name) {
  DirectoryAppend(name);
  if ( name[name.size()-1] != '/' ) name += "/";
  if ( member(directories(), name) ) return;
  directories().insert(name);
  name = name.substr(0, name.size() - 1);
  name = name.substr(0, name.rfind('/'));
  if ( name.size() ) CreateDirectory(name);
}

void BaseRepository::CheckObjectDirectory(string name) {
  if ( name[name.size() - 1] != '/' )
    name = name.substr(0, name.rfind('/') + 1);
  CheckDirectory(name);
}

void BaseRepository::CheckDirectory(string name) {
  DirectoryAppend(name);
  if ( name[name.size()-1] != '/' ) name += "/";  
  if ( member(directories(), name) ) return;
  throw RepositoryNoDirectory(name);
}

void BaseRepository::ChangeDirectory(string name) {
  DirectoryAppend(name);
  if ( name[name.size()-1] != '/' ) name += "/";  
  if ( member(directories(), name) ) {
    directoryStack().back() = name;
    return;
  }
  throw RepositoryNoDirectory(name);
}

void BaseRepository::PushDirectory(string name) {
  DirectoryAppend(name);
  if ( name[name.size()-1] != '/' ) name += "/";  
  if ( member(directories(), name) ) {
    directoryStack().push_back(name);
    return;
  }
  throw RepositoryNoDirectory(name);
}

void BaseRepository::PopDirectory() {
  if ( directoryStack().size() > 1 ) directoryStack().pop_back();
}

IBPtr BaseRepository::GetPointer(string name) {
  ObjectMap::iterator it = objects().find(name);
  return it == objects().end()? IBPtr(): it->second;
}

IVector BaseRepository::SearchDirectory(string name, string className) {
  IVector ret;
  DirectoryAppend(name);
  const ClassDescriptionBase * cdb = 0;
  if ( className.size() ) {
    cdb = DescriptionList::find(className);
    if ( !cdb ) return ret;
  }
  if ( name[name.size()-1] != '/' ) name += "/";
  string::size_type size = name.size();
  for ( ObjectMap::const_iterator i = objects().begin();
	i != objects().end(); ++i ) {
    if ( cdb && !DescriptionList::find(typeid(*(i->second)))->isA(*cdb) )
      continue;
    if ( i->first.substr(0, size) == name ) ret.push_back(i->second);
  }
  return ret;
}

IVector BaseRepository::GetObjectsReferingTo(IBPtr obj) {
  IVector ret;
  for ( ObjectMap::const_iterator i = objects().begin();
	i != objects().end(); ++i ) {
    if ( obj == i->second ) continue;
    IVector ov = DirectReferences(i->second);
    if ( member(ov, obj) ) ret.push_back(i->second);
  }
  return ret;
} 

IVector BaseRepository::DirectReferences(IBPtr obj) {
  IVector ov = obj->getReferences();
  InterfaceMap interfaceMap = getInterfaces(typeid(*obj));
  for ( InterfaceMap::iterator iit = interfaceMap.begin();
	iit != interfaceMap.end(); ++iit ) {
    IVector ovi = iit->second->getReferences(*obj);
    ov.insert(ov.end(), ovi.begin(), ovi.end());
  }
  return ov;
}

void BaseRepository::
addReferences(tIBPtr obj, ObjectSet & refs) {
  if ( !obj ) return;
  refs.insert(obj);
  IVector ov = obj->getReferences();
  for ( IVector::const_iterator it = ov.begin(); it != ov.end(); ++it )
    if ( !member(refs, *it) ) addReferences(*it, refs);
  InterfaceMap interfaceMap = getInterfaces(typeid(*obj));
  for ( InterfaceMap::iterator iit = interfaceMap.begin();
	iit != interfaceMap.end(); ++iit ) {
    IVector ov = iit->second->getReferences(*obj);
    for ( IVector::const_iterator it = ov.begin(); it != ov.end(); ++it )
      if ( !member(refs, *it) ) addReferences(*it, refs);
  }
}

void BaseRepository::
addInterfaces(const ClassDescriptionBase & db,
	      InterfaceMap & interfaceMap, bool all) {
  for ( ClassDescriptionBase::DescriptionVector::const_iterator it =
	  db.descriptions().begin(); it != db.descriptions().end(); ++it )
    if ( *it ) addInterfaces(**it, interfaceMap, all);
  TypeInterfaceMap::const_iterator cit = interfaces().find(&db);
  if ( cit == interfaces().end() ) return;
  for ( InterfaceSet::const_iterator iit = (cit->second).begin();
	iit != (cit->second).end(); ++iit ) {
    string n = (**iit).name();
    while ( all && member(interfaceMap, n) ) n = "+" + n;
    interfaceMap[n] = *iit;
  }
}

InterfaceMap BaseRepository::getInterfaces(const type_info & ti, bool all) {
  InterfaceMap interfaceMap;
  const ClassDescriptionBase * db = DescriptionList::find(ti);
  if ( !db ) return interfaceMap;
  addInterfaces(*db, interfaceMap, all);
  return interfaceMap;
}

void BaseRepository::
rebind(InterfacedBase & i, const TranslationMap & trans,
       const IVector & defaults) {
  InterfaceMap interfaceMap = getInterfaces(typeid(i), true);
  for ( InterfaceMap::iterator iit = interfaceMap.begin();
	iit != interfaceMap.end(); ++iit )
    iit->second->rebind(i, trans, defaults);
  i.rebind(trans);
}

void BaseRepository::update() {
  for_each(allObjects(), mem_fun(&InterfacedBase::update));
  clearAll(allObjects());
}

template <typename Set1, typename Set2>
bool overlap(const Set1 & s1, const Set2 & s2) {
  typename Set1::const_iterator i1 = s1.begin();
  typename Set2::const_iterator i2 = s2.begin();
  while ( i1 != s1.end() && i2 != s2.end() ) {
    if ( *i1 == *i2 ) return true;
    if ( *i1 < *i2 ) {
      i1 = s1.lower_bound(*i2);
      if ( *i1 == *i2 ) return true;
      ++i1;
    } else {
      i2 = s2.lower_bound(*i1);
      if ( *i1 == *i2 ) return true;
      ++i2;
    }
  }
  return false;
}

void BaseRepository::remove(tIBPtr ip) {
  ObjectMap::iterator it = objects().find(ip->fullName());
  if ( it == objects().end() || ip != it->second ) return;
  objects().erase(it);
  allObjects().erase(ip);
}

void BaseRepository::rename(tIBPtr ip, string newName) {
  ObjectSet::iterator it = allObjects().find(ip);
  if ( it == allObjects().end() ) {
    Register(ip, newName);
    return;
  }
  ObjectMap::iterator mit = objects().find(ip->fullName());
  if ( mit == objects().end() || mit->second != ip )
    throw RepoNameException(ip->fullName());
  
  objects().erase(mit);
  ip->name(newName);
  objects()[ip->fullName()] = ip;
}

const InterfaceBase * BaseRepository::FindInterface(IBPtr ip, string name) {
  InterfaceMap imap = getInterfaces(typeid(*ip), false);
  InterfaceMap::iterator it = imap.find(name);
  return it == imap.end()? 0: it->second;
}

const ClassDocumentationBase * BaseRepository::getDocumentation(tcIBPtr ip) {
  TypeDocumentationMap::const_iterator cdoc =
    documentations().find(DescriptionList::find(typeid(*ip)));
  return cdoc != documentations().end()? cdoc->second: 0;
}

string BaseRepository::getModelDescription(tcIBPtr ip) {
  const ClassDocumentationBase *  cd = getDocumentation(ip);
  return cd? cd->modelDescription(): string("");
}

string BaseRepository::getModelReferences(tcIBPtr ip) {
  const ClassDocumentationBase *  cd = getDocumentation(ip);
  return cd? cd->modelReferences(): string("");
}

IBPtr BaseRepository::TraceObject(string path) {
  DirectoryAppend(path);
  string::size_type colon = path.find(':');
  IBPtr ip = GetPointer(path.substr(0, colon));
  while ( colon != string::npos ) {
  if ( !ip ) throw RepositoryNotFound(path);
    path = path.substr(colon+1);
    colon = path.find(':');
    string::size_type bra = path.find('[');
    const InterfaceBase * ifb =
      FindInterface(ip, path.substr(0, min(colon, bra)));
    const ReferenceBase * rb = dynamic_cast<const ReferenceBase *>(ifb);
    if ( rb ) {
      ip = rb->get(*ip);
      continue;
    }
    const RefVectorBase * rvb = dynamic_cast<const RefVectorBase *>(ifb);
    if ( rvb ) {
      unsigned int place = 0;
      if ( bra < colon ) {
	string::size_type ket = path.find(']');
	place = atoi(path.substr(bra + 1,ket - bra - 1).c_str());
      }
      IVector iv = rvb->get(*ip);
      if ( place >= iv.size() || place < 0 ) throw RepositoryNotFound(path);
      ip = iv[place];
      continue;
    }
    throw RepositoryNotFound(path);
  }
  if ( !ip ) throw RepositoryNotFound(path);
  return ip;
}

IBPtr BaseRepository::getObjectFromNoun(string noun) {
  string::size_type colon = noun.rfind(':');
  return TraceObject(noun.substr(0, colon));
}

string BaseRepository::getInterfaceFromNoun(string noun) {
  string::size_type colon = noun.rfind(':');
  string interface = noun.substr(colon+1);
  string::size_type bra = interface.find('[');
  if ( bra != string::npos ) return interface.substr(0, bra);
  else return interface;  
}

string BaseRepository::getPosArgFromNoun(string noun) {
  string::size_type colon = noun.rfind(':');
  string interface = noun.substr(colon+1);
  string::size_type bra = interface.find('[');
  if ( bra != string::npos ) {
    string::size_type ket = interface.find(']');
    return interface.substr(bra + 1,ket - bra - 1);
  }
  return "";
}

void BaseRepository::readSetup(tIBPtr ip, istream & is) {
  ip->readSetup(is);
}

string BaseRepository::exec(string command, ostream & os) {
  string verb = StringUtils::car(command);
  command = StringUtils::cdr(command);
  if ( verb.empty() || verb[0] == '#' ) return "";
  try {
    if ( verb == "DISABLEREADONLY" ) {
      InterfaceBase::NoReadOnly = true;
      return "";
    }
    if ( verb == "ENABLEREADONLY" ) {
      InterfaceBase::NoReadOnly = false;
      return "";
    }
    if ( verb == "cd" || verb == "pushd" || verb == "mkdir") {
      string dir = StringUtils::car(command);
      if ( verb == "cd" )
	ChangeDirectory(dir);
      else if ( verb == "pushd" )
	PushDirectory(dir);
      else
	CreateDirectory(dir);
      return "";
    }
    if ( verb == "popd" ) {
      PopDirectory();
      return "";
    }
    if ( verb == "pwd" ) return directoryStack().back();
    if ( verb == "dirs" ) {
      string ret;
      for ( StringVector::reverse_iterator it = directoryStack().rbegin();
	    it != directoryStack().rend(); ++it ) ret += *it;
      return ret;
    }
    if ( verb == "cp" || verb == "mv" ) {
      string oldname = StringUtils::car(command);
      DirectoryAppend(oldname);
      IBPtr obj = GetPointer(oldname);
      if ( !obj ) return "Error: No object named '" + oldname + "' available.";
      command = StringUtils::cdr(command);
      string newname = StringUtils::car(command);
      DirectoryAppend(newname);
      if ( newname[newname.size() - 1] == '/' ) newname += obj->name();
      if ( verb == "cp" ) obj = obj->fullclone();
      rename(obj, newname);
      return "";
    }
    if ( verb == "ls" ) {
      string dir = StringUtils::car(command);
      if ( dir.size() ) PushDirectory(dir);
      string ret;
      string thisdir = directoryStack().back();
      for ( DirectorySet::iterator it = directories().begin();
	    it != directories().end(); ++it ) {
	string d = *it;
	if ( d.size() <= thisdir.size() ) continue;
	string d0 = d.substr(0, thisdir.size());
	string d1 = d.substr(thisdir.size());
	if ( d0 == thisdir && d1.find('/') == d1.size() - 1 )
	  ret += (dir.size()? d: d1) + "\n";
      }
      for ( ObjectMap::iterator it = objects().begin();
	    it != objects().end(); ++it )
	if ( thisdir + it->second->name() == it->first )
	  ret += (dir.size()? it->first: it->second->name()) + '\n';
      if ( dir.size() ) PopDirectory();
      return ret;
    }
    if ( verb == "library" ) {
      string library = StringUtils::car(command);
      if ( library.empty() ) return "Error: No library specified.";
      if ( !DynamicLoader::load(library) )
	return "Error: Could not load library " + library +
	  "\n - " + DynamicLoader::lastErrorMessage;
      return "";
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
      if ( !db ) return "Error: No such class found.";
      IBPtr obj = dynamic_ptr_cast<IBPtr>(db->create());
      if ( !obj ) return "Error: Could not create object of this class class.";
      if ( name.empty() ) return "Error: No name specified.";
      Register(obj, name);
      return "";
    }
    if ( verb == "setup" ) {
      string name = StringUtils::car(command);
      DirectoryAppend(name);
      IBPtr obj = GetPointer(name);
      if ( !obj ) return "Error: Could not find object named " + name;
      istringstream is(StringUtils::cdr(command));
      readSetup(obj, is);
      return "";
    }
    if ( verb == "rm" ) {
      ObjectSet rmset;
      ObjectSet refset;
      while ( !command.empty() ) {
	string name = StringUtils::car(command);
	DirectoryAppend(name);
	IBPtr obj = GetPointer(name);
	if ( !obj ) return "Error: Could not find object named " + name;
	rmset.insert(obj);
	IVector ov = GetObjectsReferingTo(obj);
	refset.insert(ov.begin(), ov.end());
	command = StringUtils::cdr(command);
      }
      for ( ObjectSet::iterator oi = rmset.begin(); oi != rmset.end(); ++oi )
	refset.erase(*oi);
      if ( refset.empty() ) {
	for ( ObjectSet::iterator oi = rmset.begin(); oi != rmset.end(); ++oi )
	  remove(*oi);
	return "";
      }
      string ret = "Error: cannot remove the objects because the following "
	"objects refers to them:\n";
      for ( ObjectSet::iterator oi = refset.begin(); oi != refset.end(); ++oi )
	ret += (**oi).fullName() + "\n";
      return ret;
    }
    if ( verb == "rmdir" ) {
      string dir = StringUtils::car(command);
      DirectoryAppend(dir);
      if ( dir[dir.size() - 1] != '/' ) dir += '/';
      if ( !member(directories(), dir) )
	return "Error: No such directory.";
      IVector ov = SearchDirectory(dir);
      if ( ov.size() )
	return "Error: Cannot remove a non-empty directory.";
      directories().erase(dir);
      for ( StringVector::size_type i = 0; i < directoryStack().size(); ++i )
	if ( directoryStack()[i] == dir ) directoryStack()[i] = '/';
      return "";
    }
    if ( verb == "rcp" ) {
      string name = StringUtils::car(command);
      DirectoryAppend(name);
      string newName = StringUtils::car(StringUtils::cdr(command));
      if ( newName.empty() )
	return "Error: No destination directory specified.";
      DirectoryAppend(newName);
      CreateDirectory(newName);
      if ( newName[newName.size() - 1]  != '/' ) newName += '/';
      IBPtr obj = GetPointer(name);
      if ( name[name.size() - 1]  != '/' ) name += '/';
      IVector ov = SearchDirectory(name);
      ov.push_back(obj);
      if ( ov.empty() ) return "Error: No such object or directory.";
      ObjectSet toclone;
      for ( IVector::iterator i = ov.begin(); i != ov.end(); ++i ) {
	toclone.insert(*i);
	addReferences(*i, toclone);
      }
      for ( ObjectSet::iterator i = toclone.begin(); i != toclone.end(); ++i )
	Register((**i).clone(), newName + (**i).name());
    }
    if ( verb == "mset" || verb == "msetdef" || verb == "minsert" ||
	 verb == "mdo" || verb == "mget" || verb == "mdef" || verb == "mmin" ||
	 verb == "mmax" || verb == "merase" || verb == "msend"  ) {
      if ( verb == "msend" ) verb = "mdo";
      string dir = StringUtils::car(command);
      command = StringUtils::cdr(command);
      string className = StringUtils::car(command);
      command = StringUtils::cdr(command);
      string interface = StringUtils::car(command);
      string arguments = StringUtils::cdr(command);
      string::size_type bra = interface.find('[');
      if ( bra != string::npos ) {
	string::size_type ket = interface.find(']');
	arguments = interface.substr(bra + 1,ket - bra - 1) + " " + arguments;
	interface = interface.substr(0, bra);
      }
      IVector ov = SearchDirectory(dir, className);
      if ( ov.empty() ) return "Error: no matching objects found.";
      string ret;
      verb = verb.substr(1);
      for ( IVector::size_type i = 0; i < ov.size(); ++i ) {
	const InterfaceBase * ifb = FindInterface(ov[i], interface);
	if ( !ifb ) continue;
	string mess = ifb->exec(*ov[i], verb, arguments);
	if ( !mess.empty() ) ret += ov[i]->fullName() + ": " + mess + "\n";
      }
      return ret.substr(0, ret.size() - 1);
    }
    if ( verb == "set" || verb == "setdef" || verb == "insert" ||
	 verb == "do" || verb == "get" || verb == "def" || verb == "min" ||
	 verb == "max" || verb == "describe" || verb == "fulldescribe" ||
	 verb == "erase" || verb == "send"  ) {
      if ( verb == "send" ) verb = "do";
      string noun = StringUtils::car(command);
      string arguments = getPosArgFromNoun(noun) + " "
	+ StringUtils::cdr(command);
      IBPtr ip = getObjectFromNoun(noun);
      const InterfaceBase * ifb = FindInterface(ip, getInterfaceFromNoun(noun));
      if ( !ifb && verb != "describe" && verb != "fulldescribe" )
	return "Error: The interface '" + noun + "' was not found.";
      if ( verb == "describe" ) {
	if ( ifb ) return ifb->description();
	const ClassDescriptionBase * cd = DescriptionList::find(typeid(*ip));
	string ret = "Object '" + ip->name() + "' of class '" +
	  cd->name() + "':\n";
	TypeDocumentationMap::const_iterator cdoc = documentations().find(cd);
	if ( cdoc != documentations().end() )
	  ret += cdoc->second->documentation() + "\n";
	ret +="Interfaces:\n";
	InterfaceMap imap = getInterfaces(typeid(*ip));
	for ( InterfaceMap::iterator it = imap.begin(); it != imap.end(); ++it )
	  ret += "* " + it->second->name() + "\n";
	return ret;
      } else if ( verb == "fulldescribe" ) {
	if ( ifb ) return ifb->fullDescription(*ip);
	ostringstream ret;
	const ClassDescriptionBase * cd = DescriptionList::find(typeid(*ip));
	TypeDocumentationMap::const_iterator cdoc = documentations().find(cd);
	ret << ip->fullName() << endl << cd->name() << endl;
	if ( cdoc != documentations().end() )
	  ret << cdoc->second->documentation() << endl;
	ret << "Interfaces:" << endl;
	InterfaceMap imap = getInterfaces(typeid(*ip));
	for ( InterfaceMap::iterator it = imap.begin(); it != imap.end(); ++it )
	  ret << it->second->type() << " " << it->second->name() << endl;
	return ret.str();
      } else
	return ifb->exec(*ip, verb, arguments);
    }
  }
  catch (const Exception & e) {
    e.handle();
    return "Error: " + e.message();
  }
  return "Error: Unrecognized command '" + verb + "'.";
}

BadClassClone::BadClassClone(const InterfacedBase & o) {
  theMessage << "Could not clone the object '" << o.name()
	     << "' of class '" << TypeInfo::name(o)
	     << "' because the class does not"
	     << " implement a working 'clone' method.";
  severity(abortnow);
}

BadClone::BadClone(const InterfacedBase & o) {
  theMessage << "Could not clone the object '" << o.name()
	     << "' of class '" << TypeInfo::name(o)
	     << "' because the clone method threw an unknown exception.";
  severity(abortnow);
}

RepoNameException::RepoNameException(string name) {
  theMessage << "The object '" << name << "' is present in the Repository but "
	     << "under a different name. This means that the name of the "
	     << "object has been illegally changed outside of the Repository.";
  severity(abortnow);
}

RepositoryNoDirectory::RepositoryNoDirectory(string name) {
  theMessage << "The directory '" << name << "' does not exist.";
  severity(warning);
}

RepositoryNotFound::RepositoryNotFound(string name) {
  theMessage << "There was no object named '" << name << "' in the repository.";
  severity(warning);
}

RepositoryClassMisMatch::
RepositoryClassMisMatch(const InterfacedBase & o, string name) {
  theMessage << "The requested object '" << o.fullName() << "' was not of the "
	     << "specified type (" << name << ").";
  severity(warning);
}

