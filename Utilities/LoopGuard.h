// -*- C++ -*-
#ifndef ThePEG_LoopGuard_H
#define ThePEG_LoopGuard_H
// This is the declaration of the LoopGuard class.

namespace ThePEG {

/**
 * A LoopGuard object can be used to throw an exception if a loop is
 * iterated too many times. It is used by constructing an object
 * before the loop giving the maximum number of iterations allowed and
 * a message to be used as argument to the constructor of the
 * exception to be thrown. Inside the loop the parenthesis is called
 * without argument, which will increment and check an internal counter.
 * 
 *
 * @see Level
 */
template <typename ExceptionT = Exception,
          typename MessageT = const char *>
class LoopGuard {

public:

  /**
   * Create a loop guard object which will throw an exception of type
   * ExceptionT, constructed with 'mess' as argument, if the maximum
   * number of iterations is exceeded.
   */
  inline LoopGuard(const MessageT & mess, long maxc = 1000000 );

  /**
   * Increase the iteration count and throw an ExceptionT if the
   * maximum number of iterations is exceeded.
   */
  void operator()() throw (ExceptionT);

private:

  /**
   * The number of counts so far.
   */
  long count;

  /**
   * The maximum number of counts allowed.
   */
  long maxCount;

  /**
   * The message with which the thrown ExceptionT object will be
   * initialized.
   */
  const MessageT & message;

private:

  /**
   * Default constructor is private and not implemented.
   */
  LoopGuard() {}

  /**
   * Copy constructor is private and not implemented.
   */
  LoopGuard(const LoopGuard &) {}

};

}

#include "LoopGuard.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LoopGuard.tcc"
#endif

#endif /* ThePEG_LoopGuard_H */
