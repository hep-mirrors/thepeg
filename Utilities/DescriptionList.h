#ifndef ThePEG_DescriptionList_H
#define ThePEG_DescriptionList_H
//
// This is the declaration of the <!id>DescriptionList<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>DescriptionList<!!id> keeps a static list of descriptions
// of classes included in the current run.
//

#include "ThePEG/Config/ThePEG.h"
#include "ClassDescription.fh"

namespace ThePEG {

class DescriptionList {

public:

  typedef map<const type_info *, ClassDescriptionBase *> DescriptionMap;
  typedef map<string, ClassDescriptionBase *> StringMap;

public:

  static void Register(ClassDescriptionBase &);
  // Insert a description in the list.

  static inline const ClassDescriptionBase * find(const type_info & ti);
  static inline const ClassDescriptionBase * find(const string & name);
  // Get the description of a class giving its name or type_info object.

  static void printHierarchies(ostream & os);
  // Print the classes in the list and their base classes.

protected:

  static void hookup();
  // Hookup the base class descriptions in the list.

  static void insert(ClassDescriptionBase & pb);
  // Insert a class description.

  static DescriptionMap & descriptionMap();
  // Return the static set of descriptions mapped to the relevant
  // type_info objects.

  static StringMap & stringMap();
  // Return the static set of descriptions mapped to the corresponding
  // class names.

};

}

#include "DescriptionList.icc"

#endif /* ThePEG_DescriptionList_H */
