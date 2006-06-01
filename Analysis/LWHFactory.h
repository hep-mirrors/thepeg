// -*- C++ -*-
#ifndef THEPEG_LWHFactory_H
#define THEPEG_LWHFactory_H
//
// This is the declaration of the LWHFactory class.
//

#include "ThePEG/Analysis/HistogramFactory.h"

namespace ThePEG {

/**
 * Here is the documentation of the LWHFactory class. It inherits from
 * the abstract HistogramFactory class and implements the Light-Weight
 * Histogram package, LWH. This implements the most rudimentary
 * histogramming facilities according to the <a
 * href="http://aida.freehep.org">AIDA</a> interface
 * specifications. Currently the only thing that is supported is
 * simple, equally binned, one dimensional histograms. It is mainly
 * intended to be used in applications where one needs to fill simple
 * histograms and output them. With LWH it is then possible to do this
 * without the overhead of a full AIDA implementation, but still
 * having the option to use a full implementation later on with
 * minimal changes.
 *
 * @see \ref LWHFactoryInterfaces "The interfaces"
 * defined for LWHFactory.
 */
class LWHFactory: public HistogramFactory {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline LWHFactory();

  /**
   * The copy constructor.
   */
  inline LWHFactory(const LWHFactory &);

  /**
   * The destructor.
   */
  virtual ~LWHFactory();
  //@}

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

  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr fullclone() const;
  //@}



protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  virtual void doinitrun();
  //@}


private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<LWHFactory> initLWHFactory;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  LWHFactory & operator=(const LWHFactory &);

};

}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of LWHFactory. */
template <>
struct BaseClassTrait<LWHFactory,1> {
  /** Typedef of the first base class of LWHFactory. */
  typedef HistogramFactory NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the LWHFactory class and the shared object where it is defined. */
template <>
struct ClassTraits<LWHFactory>
  : public ClassTraitsBase<LWHFactory> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::LWHFactory"; }
};

/** @endcond */

}

#include "LWHFactory.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LWHFactory.tcc"
#endif

#endif /* THEPEG_LWHFactory_H */
