// -*- C++ -*-
#ifndef ThePEG_LoopGuard_H
#define ThePEG_LoopGuard_H
//
// This is the declaration of the <!id>LoopGuard<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

namespace ThePEG {

template <typename ExceptionT = Exception,
          typename MessageT = const char *>
class LoopGuard {

public:

  inline LoopGuard(const MessageT & mess, long maxc = 1000000 );
  // Create a loop guard which will throw an exception of type
  // ExceptionT, constructed with 'mess' as argument, if the maximum
  // number of iterations is exceeded.

  void operator()() throw (ExceptionT);
  // Increase the iteration count and throw an ExceptionT if the
  // maximum number of iterations is exceeded.

private:

  long count;
  // The number of counts so far.

  long maxCount;
  // The maximum number of counts allowed.

  const MessageT & message;
  // The message with which the thrown ExceptionT object will be
  // initialized.

private:

  LoopGuard() {}
  LoopGuard(const LoopGuard &) {}
  // Standard ctors are private


};

}

#include "LoopGuard.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LoopGuard.tcc"
#endif

#endif /* ThePEG_LoopGuard_H */
