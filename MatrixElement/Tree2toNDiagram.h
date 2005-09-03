// -*- C++ -*-
#ifndef ThePEG_Tree2toNDiagram_H
#define ThePEG_Tree2toNDiagram_H
// This is the declaration of the Tree2toNDiagram class.

#include "ThePEG/MatrixElement/DiagramBase.h"
#include "ThePEG/MatrixElement/ColourLines.h"
#include "ThePEG/Handlers/StandardXComb.fh"
// #include "Tree2toNDiagram.fh"
#include "Tree2toNDiagram.xh"

namespace ThePEG {

/**
 * The Tree2toNDiagram class inherits from DiagramBase and represents
 * a Feynman tree diagram. It is represented by a chain of \f$n\f$
 * space-like propagators, where 0 is one incoming particle and
 * \f$n-1\f$ the other incoming one. For adiagram with in total
 * \f$m\f$ propagators the timelike propagators are then numbered
 * \f$n\f$ through \f$m-1\f$. The vector of type of the propagators
 * are accessible from the partons() method, and the parents of
 * propagator \f$i\f$ form the parents(int) method. The parent of a
 * space-like propagator is simply the previous space-like one. The
 * parent of a time-like propagator is either a previous time-like
 * propagator or the first of the connecting space-like ones.
 *
 * A Tree2toNDiagram is created by first constructing it with an
 * integer corresponding to the number of space-like propagators. Then
 * the comma operator is used to add first the particle data objects
 * corresponding to the space-like propagators, then the time-like
 * ones preceeded with the index of their parents. To complete a
 * Tree2toNDiagram, a negative integer is added with the comma
 * operator. This number is then used as an identifier. Note that the
 * parent must have been added before a child is. As an example, the
 * s-channel diagram \f$e \nu_e \rightarrow u \bar{d}\f$ is created
 * thus:<br>
 * <code>Tree2toNDiagram(2),eplus,nue,0,Wplus,1,u,1,dbar</code>.<br>
 * Similarly the t-channel diagram \f$e d \rightarrow \nu_e u\f$ is
 * created thus:<br>
 * <code>Tree2toNDiagram(3),eplus,Wplus,d,0,nu,1,u</code>.  Note that
 * only two chidren are allowed per propagator. This means that
 * four-propagator vertices are not allowed, but must be represented
 * by two three-propagator ones.
 *
 * @see DiagramBase
 * @see ColourLines
 * 
 */
class Tree2toNDiagram: public DiagramBase {

public:

  /** The integer type reresenting vector sizes. */
  typedef cPDVector::size_type size_type;
  /** A multi-set of particle data objects. */
  typedef multiset<tcPDPtr> PDMSet;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline Tree2toNDiagram();

  /**
   * Copy-constructor.
   */
  inline Tree2toNDiagram(const Tree2toNDiagram &);

  /**
   * Destructor.
   */
  inline ~Tree2toNDiagram();

  /**
   * The standard constructor giving the number of \a space-like
   * propagators.
   */
  inline Tree2toNDiagram(int space);
  //@}

public:

  /**
   * If less than zero indicate that this tree is competed. Otherwise
   * signal the parent of the next added parton.
   */
  inline Tree2toNDiagram & operator,(int);

  /**
   * Add a space- or time-like parton.
   */
  inline Tree2toNDiagram & operator,(PDPtr);

  /**
   * Add a space- or time-like parton.
   */
  inline Tree2toNDiagram & operator,(cPDPtr);

  /**
   * Add a space- or time-like parton.
   */
  inline Tree2toNDiagram & operator,(tPDPtr);

  /**
   * Add a space- or time-like parton.
   */
  inline Tree2toNDiagram & operator,(tcPDPtr);

  /**
   * Construct a sub process corresponding to this diagram. The
   * incoming partons, and the momenta of the outgoing ones, are given
   * by the XComb object. All parent/children pointers should be set
   * correspondingly and the partons should be colour connected as
   * specified by the ColourLines object.
   */
  virtual tPVector construct(SubProPtr sb, const StandardXComb &,
			     const ColourLines &) const;

  /**
   * Return the types of the incoming partons.
   */
  tcPDPair incoming() const;

  /**
   * Return the complete vector of partons in this tree diagram.
   */
  inline const cPDVector & allPartons() const;

  /**
   * Return the outgoing parton types of this tree diagram.
   */
  tcPDVector outgoing() const;

  /**
   * Return the incoming followed by the outgoing parton types of this
   * tree diagram.
   */
  tcPDVector external() const;

  /**
   * Return the index of the parent of the given parton.
   */
  inline int parent(int i) const;

  /**
   * Return the indices of the children of the given parton.
   */
  pair<int,int> children(int) const;

  /**
   * Return the number of space-like partons
   */
  inline int nSpace() const;

  /**
   * Return the number of outgoing partons.
   */
  inline int nOutgoing() const;

private:

  /**
   * Check the consistency of this tree diagram.
   */
  void check();

  /**
   * Add a space-like parton to this diagram.
   */
  inline void addSpacelike(tcPDPtr);
  /**
   * Add a time-like parton to this diagram.
   */
  void addTimelike(tcPDPtr);

  /**
   * Add a time-like parton to this diagram indicating its \a origin.
   */
  void addTimelike(tcPDPtr, size_type origin);

  /**
   * Add a parton to this diagram.
   */
  Tree2toNDiagram & add(tcPDPtr);

public:

  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(PersistentOStream & os) const;

  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(PersistentIStream & is, int version);
  //@}

private:

  /**
   * The number of space-like partons
   */
  size_type theNSpace;

  /**
   * The number of outgoing partons.
   */
  int theNOutgoing;

  /**
   * The parent of the next added parton.
   */
  int nextOrig;

  /**
   * The complete vector of partons in this tree diagram.
   */
  cPDVector thePartons;

  /**
   * The index of the parents.
   */
  vector<int> theParents;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<Tree2toNDiagram> initTree2toNDiagram;

  /**
   *  Private and non-existent assignment operator.
   */
  Tree2toNDiagram & operator=(const Tree2toNDiagram &);

};

}

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the
 * base class of Tree2toNDiagram.
 */
template <>
struct BaseClassTrait<Tree2toNDiagram,1>: public ClassTraitsType {
  /** Typedef of the base class of Tree2toNDiagram. */
  typedef DiagramBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * Tree2toNDiagram class.
 */
template <>
struct ClassTraits<Tree2toNDiagram>: public ClassTraitsBase<Tree2toNDiagram> {
  /** Return the class name. */
  static string className() { return "ThePEG::Tree2toNDiagram"; }
};

/** @endcond */

}

#include "Tree2toNDiagram.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Tree2toNDiagram.tcc"
#endif

#endif /* ThePEG_Tree2toNDiagram_H */
