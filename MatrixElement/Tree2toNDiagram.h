// -*- C++ -*-
#ifndef ThePEG_Tree2toNDiagram_H
#define ThePEG_Tree2toNDiagram_H
//
// This is the declaration of the <!id>Tree2toNDiagram<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Tree2toNDiagram<!!id> class inherits from
// <!class>DiagramBase<!!class> and represents a Feynman tree
// diagram. It is represented by a chain of <i>n</i> space-like
// propagators, where 0 is one incoming particle and <i>n-1</i> the
// other incoming one. For a <i>m</i>-propagator diagram the timelike
// propagators are then numbered <i>n</i> through <i>m-1</i>. The
// vector of type of the propagators are accessible from the
// <!id>partons()<!!id> method, and the parents of propagator <i>i</i>
// form the <!id>parents(i)<!!id> method. The parent of a space-like
// propagator is simply the previous space-like one. The parent of a
// time-like propagator is either a previous time-like propagator or
// the first of the connecting space-like ones.
//
// A <!id>Tree2toNDiagram<!!id> is created by first constructing it
// with an integer corresponding to the number of space-like
// propagators. Then the comma operator is used to add first the
// particle data objects corresponding to the time-like propagators,
// then the space-like ones prceeded with the index of their
// parents. To complete a <!id>Tree2toNDiagram<!!id>, a negative is
// added with the comma operator. This number is then used as an
// identifier. Note that the parent must have been added before a
// child is. As an example, the s-channel diagram <i>e nu -> u
// dbar</i> is created thus:
// <!id>Tree2toNDiagram(2),eplus,nue,0,Wplus,1,u,1,dbar<!!id>. Similarly
// the t-channel diagram <i>e d -> nu u</i> is created thus:
// <!id>Tree2toNDiagram(3),eplus,Wplus,d,0,nu,1,u<!!id>.  Note that
// only two chidren are allowed per propagator. This means that
// four-propagator vertices are not allowed, but must be represented
// by two three-propagator ones.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:DiagramBase.html">DiagramBase.h</a>,
// <a href="http:ColourLines.html">ColourLines.h</a>.
// 

#include "ThePEG/MatrixElement/DiagramBase.h"
#include "ThePEG/MatrixElement/ColourLines.h"
// #include "Tree2toNDiagram.fh"
#include "Tree2toNDiagram.xh"

namespace ThePEG {

class Tree2toNDiagram: public DiagramBase {

public:

  typedef cPDVector::size_type size_type;
  typedef multiset<tcPDPtr> PDMSet;

public:

  inline Tree2toNDiagram();
  inline Tree2toNDiagram(const Tree2toNDiagram &);
  inline ~Tree2toNDiagram();
  // Standard ctors and dtor.

  inline Tree2toNDiagram(int space);
  
public:

  inline Tree2toNDiagram & operator,(int);
  // If less than zero indicate that this tree is competed. Otherwise
  // signal the parent of the next added parton.

  inline Tree2toNDiagram & operator,(PDPtr);
  inline Tree2toNDiagram & operator,(cPDPtr);
  inline Tree2toNDiagram & operator,(tPDPtr);
  inline Tree2toNDiagram & operator,(tcPDPtr);
  // Add a space- or time-like parton.

  virtual tPVector construct(SubProPtr sb, const XComb &,
			     const ColourLines &) const;
  // Construct a sub process corresponding to this diagram. The
  // incoming partons, and the momenta of the outgoing ones, are given
  // by the XComb object. All parent/children pointers should be set
  // correspondingly and the partons should be colour connected as
  // specified by the ColourLines object.

  tcPDPair incoming() const;
  // Return the type of the incoming partons.

  inline const cPDVector & allPartons() const;
  // Return the complete vector of partons in this tree diagram.

  tcPDVector outgoing() const;
  // Return the outgoing parton types of this tree diagram.

  tcPDVector external() const;
  // Return the incoming followed by the outgoing parton types of this
  // tree diagram.

  inline int parent(int i) const;
  // Return the index of the parent of the given parton.

  pair<int,int> children(int) const;
  // Return the indices of the children of the given parton.

  inline int nSpace() const;
  // Return the number of space-like partons

  inline int nOutgoing() const;
  // Return the number of outgoing partons.

private:

  void check();
  // Check the consistency of this tree diagram.

  inline void addSpacelike(tcPDPtr);
  void addTimelike(tcPDPtr);
  void addTimelike(tcPDPtr, size_type orig);
  Tree2toNDiagram & add(tcPDPtr);
  // Add partons to this diagram.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

private:

  size_type theNSpace;
  // The number of space-like partons

  int theNOutgoing;
  // The number of outgoing partons.

  int nextOrig;
  // The parent of the next added parton.

  cPDVector thePartons;
  // The complete vector of partons in this tree diagram.

  vector<int> theParents;
  // The index of the parents.

private:

  static ClassDescription<Tree2toNDiagram> initTree2toNDiagram;
  // Describe an abstract base class with persistent data.

  Tree2toNDiagram & operator=(const Tree2toNDiagram &);
  //  Private and non-existent assignment operator.

};

}

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of DiagramBase.
template <>
struct BaseClassTrait<Tree2toNDiagram,1> {
  typedef DiagramBase NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<Tree2toNDiagram>: public ClassTraitsBase<Tree2toNDiagram> {
  static string className() { return "/ThePEG/Tree2toNDiagram"; }
  // Return the class name.
};

}

#include "Tree2toNDiagram.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Tree2toNDiagram.tcc"
#endif

#endif /* ThePEG_Tree2toNDiagram_H */
