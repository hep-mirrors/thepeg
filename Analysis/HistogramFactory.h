// -*- C++ -*-
#ifndef THEPEG_HistogramFactory_H
#define THEPEG_HistogramFactory_H
//
// This is the declaration of the HistogramFactory class.
//

#include "ThePEG/Interface/Interfaced.h"
#include "HistogramFactory.fh"
#include "AIAnalysisFactory.h"
#include "AITreeFactory.h"
#include "AIHistogramFactory.h"
#include "AIHistogram1D.h"

namespace ThePEG {

/**
 * Here is the documentation of the HistogramFactory class. This
 * abstract class is used to wrap the interface to a particular
 * AIDA-compliant histogram package to be used in
 * <code>AnalysisHandler</code>s in ThePEG. Concrete subclasses must
 * implement the doinitrun() function to create an object of a class
 * inheriting from AIDA::IAnalysisFactory and assign it with the
 * analysisFactory(AIDA::IAnalysisFactory*) function before calling
 * doinitrun() for the HistogramFactory base class.
 *
 * A HistogramFactory object should be assigned to the EventGenerator
 * object controlling a run, and <code>AnalysisHandler</code>s should
 * access it via the Generator with the generator() function.
 *
 * @see \ref HistogramFactoryInterfaces "The interfaces"
 * defined for HistogramFactory.
 */
class HistogramFactory: public Interfaced {

public:

  /**
   * Convenient typedef for pointer to AIDA::IHistogram1D.
   */
  typedef AIDA::IHistogram1D * tH1DPtr;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline HistogramFactory();

  /**
   * The copy constructor.
   */
  inline HistogramFactory(const HistogramFactory &);

  /**
   * The destructor.
   */
  virtual ~HistogramFactory();
  //@}

public:

  /** @name Simple access functions. */
  //@{
  /**
   * Together with suffix(), the name of the file where the resulting
   * histograms will be stored. If empty, generator()->filename() will
   * be used instead.
   */
  inline string filename() const;

  /**
   * Together with filename(), the name of the file where the
   * resulting histograms will be stored.
   */
  inline string suffix() const;

  /**
   * The format in which the histograms are stored in the output file.
   */
  inline string storeType() const;
  //@}

  /** @name Access the underlying AIDA objects. */
  //@{
  /**
   * Access the underlying AIDA::IAnalysisFactory object.
   */
  inline AIDA::IAnalysisFactory & analysisFactory() const;

  /**
   * Access the underlying AIDA::ITree object.
   */
  inline AIDA::ITree & tree() const;

  /**
   * A pointer to the underlying AIDA::IHistogramFactory object.
   */
  inline AIDA::IHistogramFactory & histogramFactory() const;

  /**
   * Create a new directory in the underlying AIDA tree.
   */
  inline void mkdir(string);

  /**
   * Create a new directory in the underlying AIDA tree.
   */
  inline void mkdirs(string);

  /**
   * Create and return a AIDA::IHistogram1D object in the underlying
   * AIDA histogram factory. Note that the histogram factory is
   * responsible for deleting this histogram.
   * @param path the full path of where the histogram should be placed
   * in the underlying AIDA tree (on the form
   * "/dir/subdir/histogramname"). Not that the directory part of the
   * path typically must already exist in the tree. The directories
   * can be created with mkdir(string) or mkdirs(string).
   * @param nb the number of bins in the histogram.
   * @param lo the lower edge of the histogram.
   * @param up the upper edge of the histogram.
   * @return a pointer to the created AIDA::IHistogram1D object.
   */
  inline tH1DPtr createHistogram1D(string path, int nb, double lo, double up);

  //@}

protected:

  /**
   * Set the underlying AIDA::IAnalysisFactory object. Note that this
   * surrenders the controll of the factory to the HistogramFactory
   * object which will delete it in the finish() function. Typically
   * this function should be called by a concrete subclass in the
   * doinitrun() function before the doinitrun() function of this
   * class is called.
   */
  inline void analysisFactory(AIDA::IAnalysisFactory *);

  /**
   * Delete all associated AIDA objects. Note that the tree is not
   * explicitly committed.
   */
  void clear();


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

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  virtual void doinitrun();

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  virtual void dofinish();
  //@}

private:

  /**
   * Together with theSuffix, the name of the file where the resulting
   * histograms will be stored. If empty, generator()->filename() will
   * be used instead.
   */
  string theFilename;

  /**
   * Together with theFilename, the name of the file where the
   * resulting histograms will be stored.
   */
  string theSuffix;

  /**
   * The format in which the histograms are stored in the output file.
   */
  string theStoreType;

  /**
   * A pointer to the underlying AIDA::IAnalysisFactory object.
   */
  AIDA::IAnalysisFactory * theAnalysisFactory;

  /**
   * A pointer to the underlying AIDA::ITree object.
   */
  AIDA::ITree * theTree;

  /**
   * A pointer to the underlying AIDA::IHistogramFactory object.
   */
  AIDA::IHistogramFactory * theHistogramFactory;

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is an abstract class with persistent data.
   */
  static AbstractClassDescription<HistogramFactory> initHistogramFactory;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  HistogramFactory & operator=(const HistogramFactory &);

};

}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of HistogramFactory. */
template <>
struct BaseClassTrait<HistogramFactory,1> {
  /** Typedef of the first base class of HistogramFactory. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the HistogramFactory class and the shared object where it is defined. */
template <>
struct ClassTraits<HistogramFactory>
  : public ClassTraitsBase<HistogramFactory> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::HistogramFactory"; }
};

/** @endcond */

}

#include "HistogramFactory.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HistogramFactory.tcc"
#endif

#endif /* THEPEG_HistogramFactory_H */
