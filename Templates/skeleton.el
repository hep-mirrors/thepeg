(require 'dired)

(defun p7replace (regexp newtext string)
  (dired-string-replace-match regexp string newtext t t))

(defun p7skeleton (class)
  "Create a buffer with skelton class/functions for CLASS"
  (interactive "sClass Name: ")
  (switch-to-buffer (concat "*Skeleton*" class))
  (c++-mode)
  (beginning-of-buffer)
  (insert-string "

class FileName;

class FileName: public PublicBaseClass {

public:

  inline FileName();
  inline FileName(const FileName &);
  virtual ~FileName();
  // Standard ctors and dtor.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void doinitrun();
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  static ClassDescription<FileName> initFileName;
  // Describe concrete class with persistent data.
  static AbstractClassDescription<FileName> initFileName;
  // Describe abstract base class with persistent data.
  static NoPIOClassDescription<FileName> initFileName;
  // Describe concrete class without persistent data.
  static AbstractNoPIOClassDescription<FileName> initFileName;
  // Describe abstract base class without persistent data.

  FileName & operator=(const FileName &);
  // Private and non-existent assignment operator.

};

// CLASSDOC OFF

ThePEG_DECLARE_CLASS_TRAITS(FileName,PublicBaseClass);

template <>
struct BaseClassTrait<FileName,1> {
  typedef PublicBaseClass NthBase;
};

template <>
struct ClassTraits<FileName>: public ClassTraitsBase<FileName> {
  static string className() { return \"/ThePEG/FileName\"; }
};





inline FileName::FileName() {}

inline FileName::FileName(const FileName & x)
  : PublicBaseClass(x) {}

inline IBPtr FileName::clone() const {
  return new_ptr(*this);
}

inline IBPtr FileName::fullclone() const {
  return new_ptr(*this);
}

inline void FileName::doupdate() throw(UpdateException) {
  PublicBaseClass::doupdate();
  // First update base class.
  bool redo = touched();
  // redo if touched.
//  UpdateChecker::check(aDependentMember, redo);
  // Update referenced objects on which this depends redo is set to true
  // if the dependent object is touched.
//  for_each(ContainerOfDependencies, UpdateChecker(redo));
  // Update a container of references.
//  for_each(MapOfDependencies, UpdateMapChecker(redo));
  // Update a map of references.
  if ( !redo ) return;
  // return if nothing has been touched. Otherwise do the actual update.
//  touch()
  // Touch if anything has changed.
}

inline void FileName::doinit() throw(InitException) {
  PublicBaseClass::doinit();
}

inline void FileName::doinitrun() {
  PublicBaseClass::doinitrun();
}

inline void FileName::dofinish() {
  PublicBaseClass::dofinish();
}

inline void FileName::rebind(const TranslationMap & trans)
   throw(RebindException) {
  // dummy = trans.translate(dummy);
  PublicBaseClass::rebind(trans);
}

inline IVector FileName::getReferences() {
  IVector ret = PublicBaseClass::getReferences();
  // ret.push_back(dummy);
  return ret;
}




#include \"ThePEG/Persistency/PersistentOStream.h\"
#include \"ThePEG/Persistency/PersistentIStream.h\"


FileName::~FileName() {}

void FileName::persistentOutput(PersistentOStream & os) const {
  os << ;
}

void FileName::persistentInput(PersistentIStream & is, int) {
  is >> ;
}

AbstractClassDescription<FileName> FileName::initFileName;
NoPIOClassDescription<FileName> FileName::initFileName;
AbstractNoPIOClassDescription<FileName> FileName::initFileName;
ClassDescription<FileName> FileName::initFileName;

void FileName::Init() {}

")
  (beginning-of-buffer)
  (cond ((string-match ":" class)
	 (replace-string "FileName" (substring class 0 (string-match ":" class)))
	 (beginning-of-buffer)
	 (replace-string "PublicBaseClass" (substring class (+ 1 (string-match ":" class)))))
	(t (replace-string "FileName" class)))
  (beginning-of-buffer)
)

(defun ph7icc (class)
  "Insert a standard heading for suitable for the .icc file of CLASS."
  (interactive "sClass Name: ")
  (insert-string "// -*- C++ -*-
//
// This is the implementation of the inlined member functions of
// the ")
  (insert-string class)
  (insert-string " class.
//

"))


(defun p7icc-file (class)
  "Open the .icc file for CLASS in the current directory.
   If file is empty, insert a skeleton"
  (interactive "sClass Name: ")
  (find-file (concat class ".icc"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (ph7icc class) (insert-string "namespace ThePEG {

}

")
	   (beginning-of-buffer))))

(defun ph7tcc (class)
  "Insert a standard heading for suitable for the .tcc file of CLASS."
  (interactive "sClass Name: ")
  (insert-string "// -*- C++ -*-
//
// This is the implementation of the non-inlined templated member
// functions of the ")
  (insert-string class)
  (insert-string " class.
//

"))

(defun p7tcc-file (class)
  "Open the .tcc file for CLASS in the current directory.
   If file is empty, insert a skeleton"
  (interactive "sClass Name: ")
  (find-file (concat class ".tcc"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (ph7tcc class) (insert-string "namespace ThePEG {

}

")
	   (beginning-of-buffer))))

(defun ph7h (class)
  "Insert a standard heading for suitable for the .h file of CLASS."
  (interactive "sClass Name: ")
  (insert-string "//
// This is the declaration of the <!id>")
  (insert-string class)
  (insert-string "<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href=\"http:.html\">.h</a>,
// <a href=\"http:.html\">.h</a>.
// 

"))

(defun p7h-file (class)
  "Open the .h file for CLASS in the current directory.
   If file is empty, insert a skeleton"
  (interactive "sClass Name: ")
  (find-file (concat class ".h"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (insert-string "// -*- C++ -*-
#ifndef ThePEG_FileName_H
#define ThePEG_FileName_H
")
	   (ph7h class)
	   (insert-string "#include \"ThePEG/Config/ThePEG.h\"
// #include \"FileName.fh\"
// #include \"FileName.xh\"

namespace ThePEG {

}

#include \"FileName.icc\"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include \"FileName.tcc\"
#endif

#endif /* ThePEG_FileName_H */
")
	   (beginning-of-buffer)
	   (replace-string "FileName" class)
	   (beginning-of-buffer))))

(defun ph7fh (class)
  "Insert a standard heading for suitable for the .fh file of CLASS."
  (interactive "sClass Name: ")
  (insert-string "//
// This is the forward declaration of the ")
  (insert-string class)
  (insert-string " class.
//

"))

(defun p7fh-file (class)
  "Open the .fh file for CLASS in the current directory.
   If file is empty, insert a skeleton"
  (interactive "sClass Name: ")
  (find-file (concat class ".fh"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (insert-string "// -*- C++ -*-
#ifndef ThePEG_FileName_FH
#define ThePEG_FileName_FH
")
	   (ph7fh class)
	   (insert-string (concat "namespace ThePEG {

class " class ";

ThePEG_DECLARE_CLASS_POINTERS(" class "," class "Ptr);

}

#endif /* ThePEG_FileName_FH */
"))
	   (beginning-of-buffer)
	   (replace-string "FileName" class)
	   (beginning-of-buffer))))

(defun ph7xh (class)
  "Insert a standard heading for suitable for the .xh file of CLASS."
  (interactive "sClass Name: ")
  (insert-string "//
// This is the declarations of the exception classes used by the
// ")
  (insert-string class)
  (insert-string " class.
//

"))

(defun p7xh-file (class)
  "Open the .xh file for CLASS in the current directory.
   If file is empty, insert a skeleton"
  (interactive "sClass Name: ")
  (find-file (concat class ".xh"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (insert-string "// -*- C++ -*-
#ifndef ThePEG_FileName_XH
#define ThePEG_FileName_XH")
	   (ph7xh class)
	   (insert-string "// #include \"FileName.fh\"

namespace ThePEG {






}

#endif /* ThePEG_FileName_XH */

")
	   (beginning-of-buffer)
	   (replace-string "FileName" class)
	   (beginning-of-buffer))))

(defun ph7cc (class)
  "Insert a standard heading for suitable for the .cc file of CLASS."
  (interactive "sClass Name: ")
  (insert-string "// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ")
  (insert-string class)
  (insert-string " class.
//

"))

(defun p7cc-file (class)
  "Open the .cc file for CLASS in the current directory.
   If file is empty, insert a skeleton"
  (interactive "sClass Name: ")
  (find-file (concat class ".cc"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (ph7cc class) (insert-string "#include \"FileName.h\"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include \"FileName.tcc\"
#endif

using namespace ThePEG;

")
	   (beginning-of-buffer)
	   (replace-string "FileName" class)
	   (beginning-of-buffer))))


(defun insert-id-p7 ()
  "Insert <!id><!!id> markers."
  (interactive)
  (save-excursion
    (goto-char (region-end))
    (insert "<!!id>"))
  (save-excursion
    (goto-char (region-beginning))
    (insert "<!id>")))
(defun insert-class-p7 ()
  "Insert <!class><!!class> markers."
  (interactive)
  (save-excursion
    (goto-char (region-end))
    (insert "<!!class>"))
  (save-excursion
    (goto-char (region-beginning))
    (insert "<!class>")))

(global-set-key "\C-xt" 'insert-id-p7)
(global-set-key "\C-xc" 'insert-class-p7)

(defun P7-h-file (class base baseheader)
  "Create a header file for a class CLASS
derived from a base class BASE which may be found in the include file
BASEHEADER. The class may or may not be PERSISTENT and/or CONCRETE."
  (interactive "sClass Name: 
sBase class name: 
s#include file for the base class: ")
  (setq persist (y-or-n-p "Will this class be persistent "))
  (setq interfaced (y-or-n-p "Will this class be interfaced "))
  (setq concrete (y-or-n-p "Will this class be concrete "))
  (setq namespace (p7-get-namespace class))
  (setq class (p7-get-class class))
  (p7headerfile namespace class base baseheader interfaced persist concrete ""))

(defun p7headerfile (namespace class base baseheader interfaced
			   persistent concrete specialfn)
  "Create a header file for a class CLASS
derived from a base class BASE which may be found in the include file
BASEHEADER. The class may or may not be INTERFACED, PERSISTENT and/or CONCRETE.
SPECIALFN may be used to include special function definitions"
  (find-file (concat class ".h"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (insert-string (p7header namespace class base baseheader persistent
				    concrete interfaced specialfn))
	   (beginning-of-buffer))))

(defun p7header (namespace class base baseheader persistent concrete interfaced specialfn)
  "Return a skeleton suitable for the header file of a class CLASS
derived from a base class BASE which may be found in the include file
BASEHEADER. The class may or may not be PERSISTENT, INTERFACED and/or CONCRETE.
SPECIALFN may be used to include special function definitions"

  (setq piostring (cond (persistent "
  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.
")
		       (t "")))
  (setq cloning (cond ((and concrete interfaced) "
protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods.
")
		      (t "")))
  (setq interface (cond (interfaced "
protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void doinitrun();
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.
")
			(t "")))
  (setq include (cond ((string-equal baseheader "") "ThePEG/Config/ThePEG.h")
		      (t baseheader)))
  (setq special (cond ((string-equal specialfn "") "")
		      (t (concat "
public:
" specialfn))))
  (setq description (cond (persistent (cond (concrete "
  static ClassDescription<THECLASS> initTHECLASS;
  // Describe a concrete class with persistent data.")
					    (t "
  static AbstractClassDescription<THECLASS> initTHECLASS;
  // Describe an abstract base class with persistent data.")))
			  (t (cond (concrete "
  static NoPIOClassDescription<THECLASS> initTHECLASS;
  // Describe a concrete class without persistent data.")
				   (t "
  static AbstractNoPIOClassDescription<THECLASS> initTHECLASS;
  // Describe an abstract base class without persistent data.")))))

  (setq using (cond ((string-match namespace "ThePEG") "")
		    (t "
using namespace ThePEG;
")))

  (setq NAMESPACE (upcase namespace))

  (setq namespacequalifyer (cond ((string-match namespace "ThePEG") "")
				 (t (concat namespace "::"))))

  (setq basedeclare (cond ((string-equal base "") "")
		      (t (concat ": public " base))))

  (p7replace "THECLASS" class (p7replace "THEBASE" base
					 (concat "// -*- C++ -*-
#ifndef " NAMESPACE "_THECLASS_H
#define " NAMESPACE "_THECLASS_H
//
// This is the declaration of the <!id>THECLASS<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href=\"http:.html\">.h</a>,
// <a href=\"http:.html\">.h</a>.
// 

#include \"" include "\"
// #include \"THECLASS.fh\"
// #include \"THECLASS.xh\"

namespace " namespace " {
" using "
class THECLASS" basedeclare " {

public:

  inline THECLASS();
  inline THECLASS(const THECLASS &);
  virtual ~THECLASS();
  // Standard ctors and dtor.
" specialfn "
public:
" piostring "
  static void Init();
  // Standard Init function used to initialize the interfaces.
" cloning interface "
private:
" description "

  THECLASS & operator=(const THECLASS &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of THECLASS.
template <>
struct BaseClassTrait<" namespacequalifyer "THECLASS,1> {
  typedef THEBASE NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<" namespacequalifyer "THECLASS>: public ClassTraitsBase<" namespacequalifyer "THECLASS> {
  static string className() { return \"/" namespace "/THECLASS\"; }
  // Return the class name.
  static string library() { return \"THECLASS.so\"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include \"THECLASS.icc\"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include \"THECLASS.tcc\"
#endif

#endif /* " NAMESPACE "_THECLASS_H */
"))))

(defun P7-icc-file (class base)
  "Create a icc-header file suitable for the inline function definitions
of a class CLASS which derives from the base class BASE."
  (interactive "sClass Name: 
sBase class name: ")
  (setq interfaced (y-or-n-p "Will this class be interfaced "))
  (setq concrete (y-or-n-p "Will this class be concrete "))
  (setq namespace (p7-get-namespace class))
  (setq class (p7-get-class class))
  (p7iheaderfile namespace class base interfaced concrete))

(defun p7iheaderfile (namespace class base interfaced concrete)
  "Create a icc-header file suitable for the inline function definitions
of a class CLASS which derives from the base class BASE. The class may or
may not be INTERFACED and/or CONCRETE."
  (find-file (concat class ".icc"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (insert-string (p7iheader namespace class base interfaced concrete))
	   (beginning-of-buffer))))

(defun p7iheader (namespace class base interfaced concrete)
  "Return a skeleton suitable for the icc-header file for the inline
function definitions of a class CLASS which derives from the base
class BASE."

(setq interface (cond (interfaced (concat (cond (concrete "
inline IBPtr THECLASS::clone() const {
  return new_ptr(*this);
}

inline IBPtr THECLASS::fullclone() const {
  return new_ptr(*this);
}
")
					       (t "")) "
inline void THECLASS::doupdate() throw(UpdateException) {
  THEBASE::doupdate();
  // First update base class.
  bool redo = touched();
  // redo if touched.
//  UpdateChecker::check(aDependentMember, redo);
  // Update referenced objects on which this depends redo is set to true
  // if the dependent object is touched.
//  for_each(ContainerOfDependencies, UpdateChecker(redo));
  // Update a container of references.
//  for_each(MapOfDependencies, UpdateMapChecker(redo));
  // Update a map of references.
  if ( !redo ) return;
  // return if nothing has been touched. Otherwise do the actual update.
//  touch()
  // Touch if anything has changed.
}

inline void THECLASS::doinit() throw(InitException) {
  THEBASE::doinit();
}

inline void THECLASS::dofinish() {
  THEBASE::dofinish();
}

inline void THECLASS::doinitrun() {
  THEBASE::doinitrun();
}

inline void THECLASS::rebind(const TranslationMap & trans)
  throw(RebindException) {
  // dummy = trans.translate(dummy);
  THEBASE::rebind(trans);
}

inline IVector THECLASS::getReferences() {
  IVector ret = THEBASE::getReferences();
  // ret.push_back(dummy);
  return ret;
}
"))
		     (t "")))
  (p7replace "THECLASS" class
	     (p7replace "THEBASE" base (concat "// -*- C++ -*-
//
// This is the implementation of the inlined member functions of
// the THECLASS class.
//

namespace " namespace " {

inline THECLASS::THECLASS() {}

inline THECLASS::THECLASS(const THECLASS & x)
  : THEBASE(x) {}
" interface "
}
"))))

(defun P7-cc-file (class)
  "Create a file suitable for the implementation of a class CLASS.
The class may or may not be PERSISTENT and/or CONCRETE."
  (interactive "sClass Name: ")
  (setq persist (y-or-n-p "Will this class be persistent "))
  (setq concrete (y-or-n-p "Will this class be concrete "))
  (setq namespace (p7-get-namespace class))
  (setq class (p7-get-class class))
  (p7sourcefile namespace class persist concrete ""))

(defun p7sourcefile (namespace class persistent concrete specialfn)
  "Create a file suitable for the implementation of a class CLASS.
The class may or may not be PERSISTENT and/or CONCRETE. SPECIALFN may be
used to include special function definitions"
  (find-file (concat class ".cc"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (insert-string (p7source namespace class persistent concrete specialfn))
	   (beginning-of-buffer))))

(defun p7source (namespace class persistent concrete specialfn)
  "Return a skeleton suitable for the implementation file of a class CLASS.
The class may or may not be PERSISTENT and/or CONCRETE. SPECIALFN may be
used to include special function definitions"

  (setq piostring (cond (persistent "
void THECLASS::persistentOutput(PersistentOStream & os) const {
  // *** ATTENTION *** os << ; // Add all member variable which should be written persistently here.
}

void THECLASS::persistentInput(PersistentIStream & is, int) {
  // *** ATTENTION *** is >> ; // Add all member variable which should be read persistently here.
}
")
			(t "")))

  (setq pioinclude (cond (persistent "
#include \"ThePEG/Persistency/PersistentOStream.h\"
#include \"ThePEG/Persistency/PersistentIStream.h\"")
			(t "")))

  (setq description (cond (persistent (cond (concrete "
ClassDescription<THECLASS> THECLASS::initTHECLASS;")
					    (t "
AbstractClassDescription<THECLASS> THECLASS::initTHECLASS;")))
			  (t (cond (concrete "
NoPIOClassDescription<THECLASS> THECLASS::initTHECLASS;")
				   (t "
AbstractNoPIOClassDescription<THECLASS> THECLASS::initTHECLASS;")))))

  (p7replace "THECLASS" class (concat "// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the THECLASS class.
//

#include \"THECLASS.h\"
#include \"ThePEG/Interface/ClassDocumentation.h\"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include \"THECLASS.tcc\"
#endif
" pioinclude "

using namespace " namespace ";

THECLASS::~THECLASS() {}
" specialfn piostring description "
// Definition of the static class description member.

void THECLASS::Init() {

  static ClassDocumentation<THECLASS> documentation
    (\"There is no documentation for the \\\\classname{THECLASS} class\");

}

")))

(defun P7class-files (class base baseheader)
  "Create the .h, .icc and .cc files with skeletons suitable for a class
CLASS derived from a base class BASE which may be found in the include file
BASEHEADER. The class may or may not be INTERFACED PERSISTENT and/or CONCRETE."
  (interactive "sClass Name: 
sBase class name: 
s#include file for the base class: ")
  (setq interfaced (y-or-n-p "Will this class be interfaced "))
  (setq persist (y-or-n-p "Will this class be persistent "))
  (setq concrete (y-or-n-p "Will this class be concrete "))
  (setq namespace (p7-get-namespace class))
  (setq class (p7-get-class class))
  (p7sourcefile namespace class persist concrete "")
  (p7iheaderfile namespace class base interfaced concrete)
  (p7headerfile namespace class base baseheader interfaced persist concrete ""))

(defun P7-class-files (class)
  "Create the .h, .icc and .cc files with skeletons suitable for a class
CLASS. THe user will be prompted for the base class and the main include file.
The class may or may not be INTERFACED, PERSISTENT and/or CONCRETE."
  (interactive "sClass Name: ")
  (setq base (read-from-minibuffer "Base class name: " "HandlerBase"))
  (setq namespace (p7-get-namespace class))
  (setq class (p7-get-class class))
  (setq baseheader
	(cond ((string-equal base "")
	       "ThePEG/Config/ThePEG.h")
	      ((string-equal base "Base")
	       "ThePEG/Config/ThePEG.h")
	      ((string-equal base "PersistentBase") 
	       "ThePEG/Config/ThePEG.h")
	      ((string-equal base "Interfaced")
	       "ThePEG/Interface/Interfaced.h")
	      ((string-equal base "HandlerBase")
	       "ThePEG/Handlers/HandlerBase.h")
	      ((string-equal base "StepHandler")
	       "ThePEG/Handlers/StepHandler.h")
	      ((string-equal base "CascadeHandler")
	       "ThePEG/Handlers/CascadeHandler.h")
	      ((string-equal base "HadronizationHandler")
	       "ThePEG/Handlers/HadronizationHandler.h")
	      ((string-equal base "DecayHandler")
	       "ThePEG/Handlers/DecayHandler.h")
	      ((string-equal base "MEBase")
	       "ThePEG/MatrixElement/MEBase.h")
	      ((string-equal base "PDFBase")
	       "ThePEG/PDF/PDFBase.h")
	      (t (concat namespace "/"
			 (car (reverse (split-string default-directory "/")))
			 "/" base ".h"))))
  (setq baseheader (read-from-minibuffer "#include file for the base class: "
					 baseheader))
  (cond ((string-equal base "Interfaced") (setq interfaced t))
	((string-equal base "HandlerBase") (setq interfaced t))
	((string-equal base "StepHandler") (setq interfaced t))
	((string-equal base "CascadeHandler") (setq interfaced t))
	((string-equal base "HadronizationHandler") (setq interfaced t))
	((string-equal base "DecayHandler") (setq interfaced t))
	((string-equal base "MEBase") (setq interfaced t))
	((string-equal base "PDFBase") (setq interfaced t))
	(t (setq interfaced (y-or-n-p "Will this class be interfaced "))))
  (setq persist (y-or-n-p "Will this class be persistent "))
  (setq concrete (y-or-n-p "Will this class be concrete "))
  (p7sourcefile namespace class persist concrete "")
  (p7iheaderfile namespace class base interfaced concrete)
  (p7headerfile namespace class base baseheader interfaced persist concrete ""))

(defun P7StepHandler-files (class base baseheader)
  "Create the .h, .icc and .cc files with skeletons suitable for a
new StepHandler class named CLASS derived from a base class BASE (default is
ThePEG::StepHandler) which may be found in the include file BASEHEADER.
(default /ThePEG/Handlers/StepHandler.h) The class may or may not be
PERSISTENT and/or CONCRETE."
  (interactive "sClass Name: 
sBase class name (default ThePEG::StepHandler): 
s#include file for the base class (default ThePEG/Handlers/StepHandler.h): ")
  (cond ((string-equal base "") (setq base "StepHandler")))
  (cond ((string-equal baseheader "")
         (setq baseheader "ThePEG/Handlers/StepHandler.h")))
  (setq persist (y-or-n-p "Will this class be persistent "))
  (setq concrete (y-or-n-p "Will this class be concrete "))
  (setq namespace (p7-get-namespace class))
  (setq class (p7-get-class class))
  (setq declare "
public:

  virtual void handle(PartialCollisionHandler & ch, const tcPVector & tagged,
		      const Hint & hint) throw(Veto, Stop, Exception);
  // The main virtual method to be overridden by subclasses.
")
  (setq implement (concat "
void " class "::
handle(PartialCollisionHandler & ch, const tcPVector & tagged,
       const Hint & hint) throw(Veto, Stop, Exception) {
  // Implement the Handle method here.
  // Note that if the method actually does anything to the current event
  // the changes should be inserted in a new step which should be obtained
  // by 'ch.newStep()'.
  // Note also that the general advice is to only consider the particles in
  // the 'tagged' vector.
}
"))
  (p7sourcefile namespace class persist concrete implement)
  (p7iheaderfile namespace class base t concrete)
  (p7headerfile namespace class base baseheader t persist concrete declare))


(defun p7-get-namespace (class)
  "Return the namespace part in an \"namepace::class\" string"
  (interactive  "sClass Name: ")
  (message (cond ((cdr (split-string class "::"))
		   (car (split-string class "::")))
		 (t "ThePEG"))))

(defun p7-get-class (class)
  "Return the namespace part in an \"namepace::class\" string"
  (interactive  "sClass Name: ")
  (message (cond ((cdr (split-string class "::"))
		   (car (cdr (split-string class "::"))))
		 (t class))))

(defun p7-parameter ()
  "Create a Parameter variable suitable for inclusion in an Init() function."
  (interactive)
  (setq class (read-from-minibuffer "Class Name: "
				    (file-name-sans-extension
				     (file-name-nondirectory
				      (buffer-file-name)))))
  (setq type (read-from-minibuffer "Type: " "double"))
  (setq name (read-from-minibuffer "Name: "))
  (setq desc (read-from-minibuffer "Description: "))
  (setq memb (read-from-minibuffer "Member variable: "
				   (concat "&" class "::the" name)))
  (setq hasu (y-or-n-p "Does this parameter have a unit? "))
  (cond (hasu (setq unit (read-from-minibuffer "Unit: " "GeV"))
	      (setq stru (concat "*" unit)))
	(t    (setq stru "")))
  (setq defa (read-from-minibuffer "Default value: " (concat "1.0" stru)))
  (setq limi (y-or-n-p "Is this parameter limited? "))
  (cond (limi (setq mini (read-from-minibuffer "Minimum value: "
					       (concat "0.0" stru)))
	      (setq maxi (read-from-minibuffer "Maximum value: "
					       (concat "10.0" stru))))
	(t    (setq mini (concat "-1.0e12" stru))
	      (setq maxi (concat "1.0e12" stru))))
  (setq safe (y-or-n-p "Is this parameter dependency safe? "))
  (setq ronl (y-or-n-p "Is this parameter read-only? "))
  (insert-string (concat "
  static Parameter<" class "," type "> interface" name "
    (\"" name "\",
     \"" desc "\",
     " memb ", " (cond (hasu (concat unit ", "))(t "")) defa ", "
     mini ", " maxi ",
     " (cond (safe "true")(t "false")) ", " (cond (ronl "true")(t "false")) ", "
     (cond (limi "true")(t "false"))))
  (cond ((y-or-n-p "Are there any set/get functions? ")
	 (insert-string (concat ",
     " (read-from-minibuffer "Set-function: " (concat "&" class "::set" name))
     ",
     "
     (read-from-minibuffer "Get-function: " (concat "&" class "::get" name))
     ", "
     (read-from-minibuffer "Default-function: " (concat "&" class "::def" name))
     ",
     "
     (read-from-minibuffer "Min-function: " (concat "&" class "::min" name))
     ", "
     (read-from-minibuffer "Max-function: " (concat "&" class "::max" name))))))
  (insert-string ");
"))

(defun p7-reference ()
  "Create a Reference variable suitable for inclusion in an Init() function."
  (interactive)
  (setq class (read-from-minibuffer "Class Name: "
				    (file-name-sans-extension
				     (file-name-nondirectory
				      (buffer-file-name)))))
  (setq type (read-from-minibuffer "Type: " "Interfaced"))
  (setq name (read-from-minibuffer "Name: "))
  (setq desc (read-from-minibuffer "Description: "))
  (setq memb (read-from-minibuffer "Member variable: "
				   (concat "&" class "::the" name)))
  (setq safe (y-or-n-p "Is this reference dependency safe? "))
  (setq ronl (y-or-n-p "Is this reference read-only? "))
  (setq rebi (y-or-n-p "Should this reference be automatically rebound? "))
  (setq null (y-or-n-p "Can this reference be null? "))
  (setq defn (y-or-n-p "Should this reference be given a default if null? "))

  (insert-string (concat "
  static Reference<" class "," type "> interface" name "
    (\"" name "\",
     \"" desc "\",
     " memb ", "
     (cond (safe "true")(t "false")) ", " (cond (ronl "true")(t "false")) ", "
     (cond (rebi "true")(t "false")) ", " (cond (null "true")(t "false")) ", "
     (cond (defn "true")(t "false"))))
  (cond ((y-or-n-p "Are there any set/get functions? ")
	 (insert-string (concat ",
     " (read-from-minibuffer "Set-function: " (concat "&" class "::set" name))
     ",
     "
     (read-from-minibuffer "Get-function: " (concat "&" class "::get" name))
     ", "
     (read-from-minibuffer "Check-function: "
			   (concat "&" class "::check" name))))))
  (insert-string ");
"))

(defun p7-switch-option (switchname)
  "Create a SwitchOption variable suitable for inclusion in an Init() function."
  (cond ((y-or-n-p "Do you want to add an option? ")
	 (setq name (read-from-minibuffer "Name: "))
	 (setq desc (read-from-minibuffer "Description: "))
	 (setq valu (read-from-minibuffer "Value: "))
	 (insert-string (concat "
  static SwitchOption " switchname name "
    (" switchname ",
     \"" name "\",
     \"" desc "\",
     " valu ");"))
	 (p7-switch-option switchname))
	(t (insert-string "
"))))

(defun p7-switch ()
  "Create a Switch variable suitable for inclusion in an Init() function."
  (interactive)
  (setq class (read-from-minibuffer "Class Name: "
				    (file-name-sans-extension
				     (file-name-nondirectory
				      (buffer-file-name)))))
  (setq type (read-from-minibuffer "Integer type: " "int"))
  (setq name (read-from-minibuffer "Name: "))
  (setq desc (read-from-minibuffer "Description: "))
  (setq memb (read-from-minibuffer "Member variable: "
				   (concat "&" class "::the" name)))
  (setq defa (read-from-minibuffer "Default value: " "0"))
  (setq safe (y-or-n-p "Is this reference dependency safe? "))
  (setq ronl (y-or-n-p "Is this reference read-only? "))
  (insert-string (concat "
  static Switch<" class "," type "> interface" name "
    (\"" name "\",
     \"" desc "\",
     " memb ", " defa ", "
     (cond (safe "true")(t "false")) ", " (cond (ronl "true")(t "false"))))
  (cond ((y-or-n-p "Are there any set/get functions? ")
	 (insert-string (concat ",
     " (read-from-minibuffer "Set-function: " (concat "&" class "::set" name))
     ",
     "
     (read-from-minibuffer "Get-function: " (concat "&" class "::get" name))
     ", "
     (read-from-minibuffer "Default-function: "
			   (concat "&" class "::def" name))))))
  (insert-string ");")
  (p7-switch-option (concat "interface" name)))
