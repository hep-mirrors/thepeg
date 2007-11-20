// -*- C++ -*-
//
// DescriptionList.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_DescriptionList_H
#define ThePEG_DescriptionList_H
// This is the declaration of the DescriptionList class.

#include "ThePEG/Config/ThePEG.h"
#include "ClassDescription.fh"

namespace ThePEG {

/**
 * The <code>DescriptionList</code> keeps a static list of descriptions
 * of classes included in the current run.
 */
class DescriptionList {

public:

#ifndef THEPEG_DYNAMIC_TYPE_INFO_BUG
  /** Map of class descriptions indexed by type_info objects. */
  typedef map<const type_info *, ClassDescriptionBase *> DescriptionMap;
#else
  /** Map of class descriptions indexed by type_info objects. */
  typedef map<string, ClassDescriptionBase *> DescriptionMap;
#endif

  /** Map of class descriptions indexed by platform-independent class
   * names. */
  typedef map<string, ClassDescriptionBase *> StringMap;

public:

  /**
   * Insert a description in the list.
   */
  static void Register(ClassDescriptionBase &);

  /**
   * Get the description of a class giving its type_info object.
   */
  static inline const ClassDescriptionBase * find(const type_info & ti);

  /**
   * Get the description of a class giving its name.
   */
  static inline const ClassDescriptionBase * find(const string & name);

  /**
   * Return the static set of descriptions mapped to the relevant
   * type_info objects.
   */
  static inline const DescriptionMap & all();

  /**
   * Print the classes in the list and their base classes to a
   * stream. Mainly intended for debugging purposes.
   */
  static void printHierarchies(ostream & os);

protected:

  /**
   * Hookup the base class descriptions in the list.
   */
  static void hookup();

  /**
   * Insert a class description.
   */
  static void insert(ClassDescriptionBase & pb);

  /**
   * Return the static set of descriptions mapped to the relevant
   * type_info objects. This function has a static DescriptionMap
   * variable which is initialized the first time it is called.
   */
  static DescriptionMap & descriptionMap();

  /**
   * Return the static set of descriptions mapped to the corresponding
   * class names. This function has a static StringMap variable which
   * is initialized the first time it is called.
   */
  static StringMap & stringMap();

};

}

#include "DescriptionList.icc"

#endif /* ThePEG_DescriptionList_H */
