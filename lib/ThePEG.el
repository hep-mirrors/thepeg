(require 'dired)

(defun ThePEG-class-files (class)
  "Create the .h, .icc and .cc files with skeletons suitable for a class
CLASS. THe user will be prompted for the base class and the main include file.
The class may or may not be INTERFACED, PERSISTENT and/or CONCRETE."
  (interactive "sClass Name: ")
  (setq base (read-from-minibuffer "Base class name: " "HandlerBase"))
  (setq namespace (thepeg-get-namespace class))
  (setq class (thepeg-get-class class))
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
	      ((string-equal base "Decayer")
	       "ThePEG/PDT/Decayer.h")
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
	((string-equal base "Decayer") (setq interfaced t))
	(t (setq interfaced (y-or-n-p "Will this class be interfaced "))))

  (setq declarations (cond ((string-equal base "MEBase")
			    (thepeg-ME-declare class base))
			   (t "")))
  (setq implementations (cond ((string-equal base "MEBase")
			       (thepeg-ME-implement class base))
			      (t "")))

  (setq persist (y-or-n-p "Will this class be persistent "))
  (setq concrete (y-or-n-p "Will this class be concrete "))
  (thepeg-sourcefile namespace class persist concrete implementations)
  (thepeg-iheaderfile namespace class base interfaced concrete)
  (thepeg-headerfile namespace class base baseheader interfaced
		persist concrete declarations))

(defun ThePEG-ME-class-files ()
  (interactive)
  (thepeg-specific-class-files "MEBase" "ThePEG/MatrixElement/MEBase.h"
			       'thepeg-ME-declare 'thepeg-ME-implement))

(defun ThePEG-StepHandler-class-files ()
  (interactive)
  (thepeg-specific-class-files "StepHandler" "ThePEG/Handlers/StepHandler.h"
			       'thepeg-StepHandler-declare
			       'thepeg-StepHandler-implement))

(defun ThePEG-AnalysisHandler-class-files ()
  (interactive)
  (thepeg-specific-class-files "AnalysisHandler" "ThePEG/Handlers/AnalysisHandler.h"
			       'thepeg-AnalysisHandler-declare
			       'thepeg-AnalysisHandler-implement))

(defun ThePEG-Decayer-class-files ()
  (interactive)
  (thepeg-specific-class-files "Decayer" "ThePEG/PDT/Decayer.h"
			       'thepeg-Decayer-declare
			       'thepeg-Decayer-implement))

(defun thepeg-specific-class-files (base baseheader declfn implfn)
  (setq class (read-from-minibuffer "Class name: "))
  (setq base (read-from-minibuffer "Base class name: " base))
  (setq namespace (thepeg-get-namespace class))
  (setq class (thepeg-get-class class))
  (setq baseheader (read-from-minibuffer "#include file for the base class: "
					 baseheader))
  (setq interfaced t)
  (setq persist (y-or-n-p "Will this class be persistent "))
  (setq concrete (y-or-n-p "Will this class be concrete "))
  (setq declare (funcall declfn class base))

  (setq implement (funcall implfn class base))

  (thepeg-sourcefile namespace class persist concrete implement)
  (thepeg-iheaderfile namespace class base interfaced concrete)
  (thepeg-headerfile namespace class base baseheader
		interfaced persist concrete declare))

(defun thepeg-get-namespace (class)
  "Return the namespace part in an \"namepace::class\" string"
  (cond ((cdr (split-string class "::"))
	 (car (split-string class "::")))
	(t "ThePEG")))

(defun thepeg-get-class (class)
  "Return the namespace part in an \"namepace::class\" string"
  (cond ((cdr (split-string class "::"))
	 (car (cdr (split-string class "::"))))
	(t class)))

(defun thepeg-sourcefile (namespace class persistent concrete specialfn)
  "Create a file suitable for the implementation of a class CLASS.
The class may or may not be PERSISTENT and/or CONCRETE. SPECIALFN may be
used to include special function definitions"
  (find-file (concat class ".cc"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (insert-string (thepeg-source namespace class persistent
					 concrete specialfn))
	   (beginning-of-buffer))))

(defun thepeg-source (namespace class persistent concrete specialfn)
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

  (thepeg-replace "THECLASS" class (concat "// -*- C++ -*-
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

(defun thepeg-iheaderfile (namespace class base interfaced concrete)
  "Create a icc-header file suitable for the inline function definitions
of a class CLASS which derives from the base class BASE. The class may or
may not be INTERFACED and/or CONCRETE."
  (find-file (concat class ".icc"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (insert-string (thepeg-iheader namespace class base
					  interfaced concrete))
	   (beginning-of-buffer))))


(defun thepeg-iheader (namespace class base interfaced concrete)
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
  (thepeg-replace "THECLASS" class
		  (thepeg-replace "THEBASE" base (concat "// -*- C++ -*-
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

(defun thepeg-headerfile (namespace class base baseheader interfaced
				    persistent concrete specialfn)
  "Create a header file for a class CLASS
derived from a base class BASE which may be found in the include file
BASEHEADER. The class may or may not be INTERFACED, PERSISTENT and/or CONCRETE.
SPECIALFN may be used to include special function definitions"
  (find-file (concat class ".h"))
  (c++-mode)
  (cond ((> (buffer-size) 0))
	(t (insert-string (thepeg-header namespace class base baseheader
					 persistent concrete interfaced
					 specialfn))
	   (beginning-of-buffer))))

(defun thepeg-header (namespace class base baseheader persistent
				concrete interfaced specialfn)
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
  
  (thepeg-replace "THECLASS" class (thepeg-replace "THEBASE" base
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
struct ClassTraits<" namespacequalifyer "THECLASS>
  : public ClassTraitsBase<" namespacequalifyer "THECLASS> {
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

(defun thepeg-replace (regexp newtext string)
  (dired-string-replace-match regexp string newtext t t))

(defun thepeg-ME-implement (class base)
(concat "

#include \"ThePEG/PDT/EnumParticles.h\"
#include \"ThePEG/MatrixElement/Tree2toNDiagram.h\"

void " class "::getDiagrams() const {
  // Here is an example on how to specify diagrams.

  tcPDPtr g = getParticleData(ParticleID::g);
  for ( int i = 1; i <= 5; ++i ) {
    tcPDPtr q = getParticleData(i);
    tcPDPtr qb = q->CC();

    // For each flavour we add:
    add(new_ptr((Tree2toNDiagram(3), q, qb, qb, 1, g, 2, g, -1)));
    // t-channel q + qbar -> g + g
    add(new_ptr((Tree2toNDiagram(3), q, qb, qb, 2, g, 1, g, -2)));
    // u-channel q + qbar -> g + g
    add(new_ptr((Tree2toNDiagram(2), q, qb, 1, g , 3, g, 3, g, -3)));
    // s-channel q + qbar -> g + g
  }
}

Energy2 " class "::scale() const {
  return sHat();
}

int " class "::nDim() const {
  return 1;
}

void " class "::setKinematics() {
  " base "::setKinematics(); // Always call the base class method first.
}

bool " class "::generateKinematics(const double * r) {
  // Here you can use nDim() random numbers in the vector provided
  // to generate the internal kinematics. Note that sHat() has
  // already been given from the outside.

  // Save the jacobian dPS/dr for later use.
  jacobian(1.0);

  return false; // Return false if matrix element was zero.
}

double " class "::me2() const {
  return 0.0;
}

CrossSection " class "::dSigHatDR() const {
  return me2()*jacobian()/sHat(); // Here we can add other prefactors coming
                                  // from the phase space integration.
}

unsigned int " class "::orderInAlphaS() const {
  return 0;
}

unsigned int " class "::orderInAlphaEW() const {
  return 0;
}

Selector<MEBase::DiagramIndex>
" class "::diagrams(const DiagramVector & diags) const {
  // This example corresponds to the diagrams specified in the example
  // in the getDiagrams() function.

  Selector<DiagramIndex> sel;
  for ( DiagramIndex i = 0; i < diags.size(); ++i ) 
    if ( diags[i]->id() == -1 ) sel.insert(1.0, i);
    else if ( diags[i]->id() == -2 )  sel.insert(1.0, i);
    else if ( diags[i]->id() == -3 )  sel.insert(1.0, i);
  // You probably do not want equal weights here...
  return sel;

  // If there is only one possible diagram you can override the
  // MEBase::diagram function instead.

}

Selector<const ColourLines *>
" class "::colourGeometries(tcDiagPtr diag) const {
  // This example corresponds to the diagrams specified in the example
  // in the getDiagrams() function.

  static ColourLines ctST(\"1 4, -4 -2 5, -5 -3\");
  static ColourLines ctSU(\"1 5, -5 -2 4, -4 -3\");

  Selector<const ColourLines *> sel;
  if ( diag->id() == -1 || diag->id() == -3 )
    sel.insert(1.0, &ctST);
  else
    sel.insert(1.0, &ctSU);
  return sel;

  // If there is only one possible colour geometry you can override the
  // MEBase::selectColourGeometry function instead.

}

"))

(defun thepeg-ME-declare (class base)
  (concat "
public:

  virtual unsigned int orderInAlphaS() const;
  virtual unsigned int orderInAlphaEW() const;
  // Return the order in respective couplings in which this matrix
  // element is given.

  virtual double me2() const;
  // Return the matrix element for the kinematical configuation
  // previously provided by the last call to setKinematics(), suitably
  // scaled by sHat() to give a dimension-less number.

  virtual Energy2 scale() const;
  // Return the scale associated with the last set phase space point.

  virtual void setKinematics();
  // Set the typed and momenta of the incoming and outgoing partons to
  // be used in subsequent calls to me() and colourGeometries()
  // according to the associated XComb object. If the fun ction is
  // overridden in a sub class the new function must call the base
  // class one first.

  virtual int nDim() const;
  // The number of internal degreed of freedom used in the matrix
  // element. This default version returns 0;

  virtual bool generateKinematics(const double * r);
  // Generate internal degrees of freedom given 'nDim()' uniform
  // random numbers in the interval ]0,1[. To help the phase space
  // generator, the 'dSigHatDR' should be a smooth function of these
  // numbers, although this is not strictly necessary. THe return
  // value should be true of the generation succeeded.

  virtual CrossSection dSigHatDR() const;
  // Return the matrix element squared differential in the variables
  // given by the last call to 'generateKinematics()'.

  virtual void getDiagrams() const;
  // Add all possible diagrams with the add() function.

  inline virtual Selector<DiagramIndex> diagrams(const DiagramVector &) const;
  // With the information previously supplied with the
  // setKinematics(...) method, a derived class may optionally
  // override this method to weight the given diagrams with their
  // (although certainly not physical) relative probabilities.

  virtual Selector<const ColourLines *>
  colourGeometries(tcDiagPtr diag) const;
  // Return a Selector with possible colour geometries for the selected
  // diagram weighted by their relative probabilities.

"))

(defun thepeg-StepHandler-declare (class base)
  (concat "
public:

  virtual void handle(PartialCollisionHandler & ch, const tcPVector & tagged,
		      const Hint & hint) throw(Veto, Stop, Exception);
  // The main virtual method to be overridden by subclasses.
"))

(defun thepeg-StepHandler-implement (class base)
  (concat "
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

(defun thepeg-AnalysisHandler-declare (class base)
  (concat "
public:

  virtual void analyze(tEventPtr event, long ieve, int loop, int state);
  // Analyse a given 'event'. 'ieve' is the event number, 'loop' is
  // the number of times this event has been presented. If loop is
  // negative, the event is now fully generated.  'state' is a number
  // different from zero if the event has been manipulated in some way
  // since it was last presented. Note that a fully generated event
  // may be presented several times, if it has been manipulated in
  // between. The default version of this function will call transform
  // to make a lorentz transformation of the whole event, then extract
  // all final state particles and call analyze(tPVector) of this
  // analysis object and those of all associated analysis objects. The
  // default version will not, however, do anything on events which
  // have not been fully generated, or have been manipulated in any
  // way.

  virtual LorentzRotation transform(tEventPtr) const;
  // transform the event to the desired Lorentz frame and return the
  // used LorentzRotation. The default version does nothing and
  // returns the identity rotation.

  virtual void analyze(const tPVector & particles);
  // Analyze the given vector of particles. The default version calls
  // analyze(tPPtr) for each of the particles.

  virtual void analyze(tPPtr particle);
  // Analyze the given particle. The default version does nothing

"))

(defun thepeg-AnalysisHandler-implement (class base)
  (concat "
void " class "::analyze(tEventPtr event, long ieve, int loop, int state) {
  " base "::analyze(event, ieve, loop, state);
  // Rotate to CMS, extract final state particles and call analyze(particles).
}

LorentzRotation " class "::transform(tEventPtr event) const {
  return LorentzRotation();
  // Return the Rotation to the frame in which you want to perform the analysis.
}

void " class "::analyze(const tPVector & particles) {
  " base "::analyze(particles);
  // Calls analyze() for each particle.
}

void " class "::analyze(tPPtr) {}
"))

(defun thepeg-Decayer-declare (class base)
  (concat "
public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual ParticleVector decay(const DecayMode &, const Particle &) const;
  // for a given decay mode and a given particle instance, perform the
  // decay and return the decay products.

"))

(defun thepeg-Decayer-implement (class base)
  (concat "
bool " class "::accept(const DecayMode & dm) const {
  return false;
}

ParticleVector " class "::decay(const DecayMode & dm,
				  const Particle & parent) const {
  ParticleVector children = dm.produceProducts();
  return children;
}

"))

(defun ThePEG-parameter ()
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

(defun ThePEG-reference ()
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

(defun thepeg-switch-option (switchname)
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
	 (thepeg-switch-option switchname))
	(t (insert-string "
"))))

(defun ThePEG-switch ()
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
  (thepeg-switch-option (concat "interface" name)))
