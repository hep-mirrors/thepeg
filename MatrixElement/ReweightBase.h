// -*- C++ -*-
#ifndef ThePEG_ReweightBase_H
#define ThePEG_ReweightBase_H
//
// This is the declaration of the <!id>ReweightBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>ReweightBase<!!id> class is the base class of all objects
// representing external biases to matrix elements. These can be used
// to enhance certain matrix elements or certain phase space
// regions. They can be used in to ways, either to completely change
// the matrix element (re-weight), in which case the total cross
// section will be affected or, when using weighted events in an
// <!class>EventHandler<!!class>, to pre-weight certain events but
// leaving the cross section unchanged
//
// There is only one virtual function which must be overridden in
// derived classes: <!id>double weight() const<!!id>.
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:MEBase.html">MEBase.h</a>,
// <a href="http:EventHandler.html">EventHandler.h</a>,
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>.
// 

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
// #include "ReweightBase.fh"
// #include "ReweightBase.xh"

namespace ThePEG {

class ReweightBase: public HandlerBase, public LastXCombInfo<> {

public:

  inline ReweightBase();
  inline ReweightBase(const ReweightBase &);
  virtual ~ReweightBase();
  // Standard ctors and dtor.

public:

  virtual double weight() const = 0;
  // Return the wieght for the kinematical configuation
  // previously provided by the last call to setKinematics().

  void setKinematics(Energy2 shat, tcPDPair in, const cPDVector & out,
		     const Lorentz5Momentum & pina,
		     const Lorentz5Momentum & pinb,
		     const vector<Lorentz5Momentum> & pout);

  void setKinematics(tPPair in, const PVector & out);
  inline void setKinematics(const SubProcess & sub);
  void setXComb(tXCombPtr);
  // Set the typed and momenta of the incoming and outgoing partons to
  // be used in subsequent calls to me() and colourGeometries().

  inline virtual void setKinematics();
  // This method does nothing in this base class. Derived classes may
  // override it to setup derived quantities obtained from the
  // information provided by a call to setKinematics(...). (Allways
  // called from the setKinematics(...) method.)

  virtual void clearKinematics();
  // Clear the information previously provided by a call to
  // setKinematics(...).

public:

  inline Energy2 sHat() const;
  // Return the last set invariant mass squared.

  inline const cPDPair & inData() const;
  // Return the types of the last set incoming partons.

  inline const cPDVector & outData() const;
  // Return the types of the last set outgoing partons.

  inline const Lorentz5Momentum & inMomentumA() const;
  inline const Lorentz5Momentum & inMomentumB() const;
  // Return the momenta of the last set incoming partons.

  inline const vector<Lorentz5Momentum> & outMomentum() const;
  // Return the momenta of the last set outgoing partons.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  Energy2 theLastSHat;
  // The last set invariant mass squared.

  cPDPair theLastInData;
  // The types of the last set incoming partons.

  cPDVector theLastOutData;
  // The types of the last set outgoing partons.

  Lorentz5Momentum theLastInMomentumA;
  Lorentz5Momentum theLastInMomentumB;
  // The momenta of the last set incoming partons.

  vector<Lorentz5Momentum> theLastOutMomentum;
  // The momenta of the last set outgoing partons.

private:

  static AbstractClassDescription<ReweightBase> initReweightBase;
  // Describe an abstract base class with persistent data.

  ReweightBase & operator=(const ReweightBase &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of ReweightBase.
template <>
struct BaseClassTrait<ReweightBase,1> {
  typedef HandlerBase NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ReweightBase>: public ClassTraitsBase<ReweightBase> {
  static string className() { return "/ThePEG/ReweightBase"; }
  // Return the class name.
};

}

#include "ReweightBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ReweightBase.tcc"
#endif

#endif /* ThePEG_ReweightBase_H */
