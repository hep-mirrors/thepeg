// -*- C++ -*-
#ifndef ThePEG_ClassDocumentation_H
#define ThePEG_ClassDocumentation_H
//
// This is the declaration of the <!id>ClassDocumentation<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>ClassDocumentation<!!id> class is used to communicate
// documetation about an <!class>Interfaced<!!class> class to the
// <!class>Repository<!!class>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Interfaced.html">Interfaced.h</a>,
// <a href="http:Repository.html">Repository.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ClassDocumentation.fh"
// #include "ClassDocumentation.xh"

namespace ThePEG {

class ClassDocumentationBase  {


protected:

  ClassDocumentationBase(string newDocumentation,
			 string newModelDescription,
			 string newModelReferences,
			 const type_info & newTypeInfo);
  // The constructor can only be used from subclasses..

public:

  inline virtual ~ClassDocumentationBase();
  // The dtor.

public:

  inline string documentation() const;
  // Return the documentation of the corresponding class.

  inline string modelDescription() const;
  inline string modelReferences() const;
  // The string returned from modelDescription() should contain a very
  // brief description of the model of the process implemented in the
  // step handler, given in the form of a LaTeX \item. If any LaTeX
  // \cite reference are given, a corresponding \bibitem should be
  // returned by modelReference(). E.g. modelDescription() could
  // return "The XXX model \\cite{XXX} was used for the YYY pocess",
  // and modelReferences() should then return something like
  // "\\bibitem{XXX} J.~Doe, \\textit{Journal} \\textbf{volume} (year)
  // page."  Note the double-slash to get a single slash, and that
  // modelReferences() must begin with a "\\bibitem".

private:

  string theDocumentation;
  // The documentation of the corresponding class.

  string theModelDescription;
  string theModelReferences;
  // A (LaTeX) sentence describing the implemented model (if any). If
  // any \\cite references are given, the corresponding citation
  // should be listed in theModelReferences.

private:

  ClassDocumentationBase();
  ClassDocumentationBase(const ClassDocumentationBase &);
  ClassDocumentationBase & operator=(const ClassDocumentationBase &);
  // Private and unimplemented.

};


template <typename T>
class ClassDocumentation: public ClassDocumentationBase {

public:

  inline ClassDocumentation(string newDocumentation,
			 string newModelDescription = "",
			 string newModelReferences = "");
  inline virtual ~ClassDocumentation();
  // Standard ctors and dtor.

private:

  ClassDocumentation();
  ClassDocumentation(const ClassDocumentation &);
  ClassDocumentation & operator=(const ClassDocumentation &);
  // Private and unimplemented.

};

}

#include "ClassDocumentation.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ClassDocumentation.tcc"
#endif

#endif /* ThePEG_ClassDocumentation_H */
