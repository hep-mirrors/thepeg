// -*- C++ -*-
#ifndef ThePEG_BaseRepository_H
#define ThePEG_BaseRepository_H
//
// This is the declaration of the <!id>BaseRepository<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>BaseRepository<!!id> is a purely static class which keeps a
// set of <!class>InterfacedBase<!!class> objects indexed by their
// name. The name is divided up in a tree-like structure inspired by
// the Unix file system.
//
// The <!class>InterfacedBase<!!class> objects may be manipulated
// using <!class>InterfaceBase<!!class> objects. This may be done
// directly or via a simple command interface using the
// <!id>exec()<!!id> method.
//
// Commands given to <!id><!id>exec()<!!id> can be of the following
// forms:<BR> the empty string and string beginning with #<!!id> are
// ignored.<BR> <!id>cd dir<!!id> sets the current directory to
// <!id>dir<!!id> (if it exists).<BR> <!id>pushd dir<!!id> sets the
// current directory to <!id>dir<!!id> (if it exists) but saves the
// previous directory on a stack.<BR> <!id>popd<!!id> leaves the
// current directory and sets the next one on the stack as
// current.<BR> <!id>dirs<!!id> returns the current stack of
// directories.<BR> <!id>ls<!!id> returns the names of the objects
// (and sub-directories) in the current directory.<BR> <!id>ls
// dir<!!id> returns the names of the objects (and sub-directories) in
// the given directory.<BR>
//
// <!id>set object:interface value<!!id>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:InterfaceBase.html">InterfaceBase.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
// #include "BaseRepository.fh"
#include "BaseRepository.xh"
#include "ThePEG/Interface/InterfaceBase.fh"
#include "ThePEG/Interface/ClassDocumentation.fh"
#include "ThePEG/Interface/InterfacedBase.h"
#include "ThePEG/Utilities/ClassDescription.fh"

namespace ThePEG {

class BaseRepository {

public:

  typedef StringSet DirectorySet;
  typedef vector<string> StringVector;
  typedef set<const InterfaceBase *> InterfaceSet;
  typedef map<const ClassDescriptionBase *, InterfaceSet> TypeInterfaceMap;
  typedef map<const ClassDescriptionBase *, const ClassDocumentationBase *>
    TypeDocumentationMap;
 
public:

  static void Register(const InterfaceBase &, const type_info &);
  // Register an interface. (this is done automatically in the
  // InterfaceBase constructor.

  static void Register(const ClassDocumentationBase &, const type_info &);
  // Register a class documentation. (this is done automatically in the
  // ClassDocumentationBase constructor.

  static void Register(IBPtr);
  static void Register(IBPtr, string newName);
  // Register a new object using the its current name or giving it a
  // new one. If the object is already in the repository, nothing
  // happens. If another object already exists with the same name, the
  // new object will have '#'s appended to its name to make it unique.

  static void CreateDirectory(string);
  static void CheckObjectDirectory(string);
  static void CheckDirectory(string);
  static void DirectoryAppend(string &);
  static void ChangeDirectory(string name);
  static void PushDirectory(string name);
  static void PopDirectory();
  // Do things with the directiory stack.

  template <typename T>
  static typename Ptr<T>::pointer GetPtr(const T &);
  // Return a reference counted pointer to the given
  // object. (Currently not needed).

  template <typename PtrType>
  static PtrType GetPtr(string);
  template <typename PtrType>
  static PtrType GetObject(string);
  // Return a pointer of the specified type to an object with the
  // given name. If such an object does not exist, GetPtr will return
  // a null pointer, while GetObject with throw an exception.

  static IBPtr GetPointer(string);
  // Return a pointer to an object with the given name ot null if no
  // such object exists.

  static IVector SearchDirectory(string name, string className = "");
  // Return all objects in the given directory. Optionally only return
  // objects of a certain class.

  static IVector GetObjectsReferingTo(IBPtr);
  // Return all object which refers to the given object.

  static IVector DirectReferences(IBPtr);
  // Return all objects the given object refers to directly.

  static void addReferences(tIBPtr obj, ObjectSet & refs);
  // If obj contains references to other objects, either through a
  // Reference or RefVector interface or through the virtual
  // getReferences member function, add these to refs. Do the same to
  // the references recursively.

  static InterfaceMap getInterfaces(const type_info & ti, bool all = true);
  // Return the interfaces defined for the InterfacedBase class with
  // the given type_into, mapped to their name. If several interfaces
  // with the same name exists only the one which correspond to the
  // most derived class will be given, except if all is true in which
  // case all interfaces are given (prefixed by '+'s to become
  // unique).

  static const InterfaceBase * FindInterface(IBPtr, string);
  // Return an interface with the given name to the given object.

  static void update();
  // Call the update mathod of all abjects.

  template<typename Cont>
  inline static void clearAll(const Cont &);
  // Clear the touched flag in all objects in the given container.

  template<typename Cont>
  inline static void resetAll(const Cont &);
  // Set the stat of all objects in the given container to
  // 'uninitialized'.

  static void remove(tIBPtr);
  // Remove the given object from the repository.

  static void rename(tIBPtr, string newName);
  // Rename a given object.

  static const ClassDocumentationBase * getDocumentation(tcIBPtr ip);
  // Return the class documentation of a given object

  static string getModelDescription(tcIBPtr ip);
  static string getModelReferences(tcIBPtr ip);
  // Get the description and references for the model implemented in
  // the class of the given object.

  static IBPtr TraceObject(string);
  // Find an object. If the name does not begin with '/', the current
  // directory is prepended. If the string is on the form
  // 'object:interface' (or 'object:interface[i]') and 'interface'
  // corresponds to an Reference (or RefVector) interface, the
  // corresponding referenced object is returned. (also
  // 'object:interface:interface' is allowed etc.)

  static void readSetup(tIBPtr ip, istream & is);
  // Execute the readSetup method of ip with is as argument.

  static IBPtr getObjectFromNoun(string noun);
  static string getInterfaceFromNoun(string noun);
  static string getPosArgFromNoun(string noun);
  // Decompose a string of the form 'object:interface' or
  // 'object:vector-interface[pos]'.

  static string exec(string cmd, ostream &);
  // Interpret the command in 'cmd'.

  inline static void lock(tIBPtr);
  inline static void unlock(tIBPtr);
  // Lock or unlock the given objects. Locked objects cannot be
  // changed through an interface.

  inline static void cout(ostream &);
  inline static ostream & cout();
  // Set/get the standard output stream

  inline static void cerr(ostream &);
  inline static ostream & cerr();
  // Set/get the standard error stream

  inline static void clog(ostream &);
  inline static ostream & clog();
  // Set/get the standard log stream

protected:

  template <typename T>
  static typename Ptr<T>::pointer clone(const T &);
  template <typename T>
  static typename Ptr<T>::pointer fullclone(const T &);
  // Return a clone of the given object.

  static void rebind(InterfacedBase & obj, const TranslationMap & trans,
		     const IVector & defaults);
  // For all objects directly referenced by obj, replace them with the
  // translation found in trans. If obj has a Reference or a member of
  // a RefVector interface which is null, and the corresponding
  // interface has the defaultIfNull flag set, translate the null
  // pointer to the first acceptable object in defaults.
  

  static void addInterfaces(const ClassDescriptionBase &,
			    InterfaceMap &, bool all = true);
  // Add interfaces to the given map for the class with the given
  // class description. Recursively do the same with the base classes.

  static ObjectMap & objects();
  // All InterfacedBase objects mapped to their name.

  static ObjectSet & allObjects();
  // All InterfacedBase objects.

  static TypeInterfaceMap & interfaces();
  // Sets of Interfacebase object mapped to the corresponding class
  // description.

  static TypeDocumentationMap & documentations();
  // Sets of Interfacebase object mapped to the corresponding class
  // description.

  static DirectorySet & directories();
  // All defined directories.

  static StringVector & directoryStack();
  // The current directory stack.

  static bool & updating();
  // Flag to say if we are in the middle of an update procedure.

  static ostream *& coutp();
  static ostream *& cerrp();
  static ostream *& clogp();
  // The current current standard output, error, and log streams.

};


}

#include "BaseRepository.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "BaseRepository.tcc"
#endif

#endif /* ThePEG_BaseRepository_H */
