// -*- C++ -*-
#ifndef THEPEG_CompSelector_H
#define THEPEG_CompSelector_H
//
// This is the declaration of the CompSelector class.
//

#include "ThePEG/Utilities/Selector.h"

namespace ThePEG {

/**
 * The CompSelector class works like the Selector class in that it can
 * be used to randomly select objects according to associated
 * probabilities. In addition, the CompSelector class is able to
 * handle the case where the associated probabilities are
 * overestimates and the selected object will be discarded according
 * to some weight. If then a weight above one is encountered, this
 * means that the overestimated probability for the selected object
 * was wrong and it should in fact have been higher. If this happens,
 * the CompSelecteor will go into compensation mode, which means that
 * the selected object will be oversampled a period after the
 * violation to compensate for having been undersampled before. Also
 * the associated probability is adjusted to reflect the new
 * overestimate.
 *
 * The available functions are not as many as in Selector, and some of
 * the works somewhat differently. Before starting sampling the
 * objects should be added to a CompSelector object with the insert()
 * function. To selct an object the select() function should be
 * used. After that the weight with which the object should be
 * accepted should be presented with the reweight() function which
 * normally returns zero. If, however, the weight is larger than unity
 * the new overestimated probability is returned and the CompSelector
 * enters the compensating mode. Note that the weight is passed as a
 * reference and may be changed in by the reweight function if in the
 * compensating mode.
 */
template <typename T, typename WeightType = double>
class CompSelector {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor. The optional argument gives the margin
   * used to get a new overestimated probability for an object when
   * entering compensation mode.
   */
  inline CompSelector(double newMargin = 1.1);
  //@}

public:

  /** @name The main function controlling the selection and compensation. */
  //@{
  /**
   * Insert an object given a probability for this object. If the
   * probability is zero or negative, the object will not be inserted
   * and the probability itself is returned. Otherwise the sum of
   * probabilities so far is returned. Note that if selection has
   * already started and this CompSelector is in compensating mode, it
   * will immediately leave this mode and the selection procedure will
   * start from scratch.
   */
  inline WeightType insert(WeightType, const T &);

  /**
   * Selct an object randomly. Given a random number generator which
   * generates flat random numbers in the interval ]0,1[ with the
   * <code>operator()()</code> function, select an object according to
   * the individual probabilities specified when they were
   * inserted. If the generated number is outside the allowed range or
   * the Selector is empty, a range_error will be thrown. The
   * generator should have a push_back function which will be used
   * push back a uniform random number in the interval ]0,1[
   * calculated from the fraction of rnd which was in the range of the
   * selected object.
   */
  template <typename RNDGEN>
  inline T & select(RNDGEN & rnd) throw(range_error);

  /**
   * Report the weight associated with the last selected
   * object. Returns the zero if weight was below unity, otherwise the
   * compensation mode will be entered and the new overestimated
   * probabilty for the last selected object will be returned.
   */
  inline WeightType reweight(double & weight);

  /**
   * Exit compensation mode and start selection procedure from
   * scratch.
   */
  inline void reset();

  /**
   * Erases all objects.
   */
  inline void clear();

  /**
   * Set the margin used to get a new overestimated probability for an
   * object when entering compensation mode.
   */
  inline void margin(double);
  //@}


  /** @name Simple access functions. */
  //@{
  /**
   * Return true if this CompSelector is in a compensating state.
   */
  inline bool compensating();

  /**
   * If in a compensating mode, return the number of selection needed
   * before exiting this mode.
   */
  inline long compleft() const;

  /**
   * Return the sum of probabilities of the objects inserted. Note
   * that probabilities specified when objects are inserted are
   * rescaled with this number to give unit probability for
   * 'select()'.
   */
  inline WeightType sum() const;

  /**
   * Return the margin used to get a new overestimated probability for an
   * object when entering compensation mode.
   */
  inline double margin() const;
  //@}

  /** @name I/O functions. */
  //@{
  /**
   * Output to a stream.
   */
  template <typename OStream>
  inline void output(OStream &) const;

  /**
   * Input from a stream.
   */
  template <typename IStream>
  inline void input(IStream &);
  //@}

private:

  /**
   * Internal struct used for bookkeeping when compensating.
   */
  struct Level {

    /**
     * The selection number at which point this level of compensation
     * is ended.
     */
    long lastN;

    /**
     * The minimum weight allowed when compensating on this level.
     */
    double weight;

  };

private:

  /**
   * The underlying selector
   */
  Selector<T,WeightType> selector;

  /**
   * The number of selections so far.
   */
  long N;

  /**
   * The last selected object.
   */
  T last;

  /**
   * The margin used to get a new overestimated probability for an
   * object when entering compensation mode.
   */
  double theMargin;

  /**
   * The currently active compensation levels.
   */
  vector<Level> levels;

};

/**
 * Output a Selector to a stream.
 */
template <typename OStream, typename T, typename WeightType>
inline OStream & operator<<(OStream &, const CompSelector<T,WeightType> &);

/**
 * Input a Selector from a stream.
 */
template <typename IStream, typename T, typename WeightType>
inline IStream & operator>>(IStream &, CompSelector<T,WeightType> &);

}

#include "CompSelector.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "CompSelector.tcc"
#endif

#endif /* THEPEG_CompSelector_H */
