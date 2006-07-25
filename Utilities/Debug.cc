// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Debug class.
//

#include "Debug.h"
#ifdef ThePEG_HAS_FPU_CONTROL
#include <fpu_control.h>
#endif

using namespace ThePEG;

int Debug::level = 0;

std::vector<bool> Debug::debugItems;

void Debug::debugItem(int item, bool on) {
  if ( item < 0 ) return;
  debugItems.resize(item + 1, false);
  debugItems[item] = on;
}

void Debug::setDebug(int ilev) {
  if ( ilev < 0 ) debugItem(-ilev, true);
  else level = ilev;
}

void Debug::unmaskFpuErrors() {
  unmaskFpuOverflow();
  unmaskFpuDivZero();
  unmaskFpuDenorm();
  unmaskFpuInvalid();
}

void Debug::unmaskFpuOverflow() {
#ifdef ThePEG_HAS_FPU_CONTROL
  fpu_control_t cw;
  _FPU_GETCW(cw);
  cw &= ~(_FPU_MASK_OM);
  _FPU_SETCW(cw);
#endif
}

void Debug::unmaskFpuUnderflow() {
#ifdef ThePEG_HAS_FPU_CONTROL
  fpu_control_t cw;
  _FPU_GETCW(cw);
  cw &= ~(_FPU_MASK_UM);
  _FPU_SETCW(cw);
#endif
}

void Debug::unmaskFpuDivZero() {
#ifdef ThePEG_HAS_FPU_CONTROL
  fpu_control_t cw;
  _FPU_GETCW(cw);
  cw &= ~(_FPU_MASK_ZM);
  _FPU_SETCW(cw);
#endif
}

void Debug::unmaskFpuDenorm() {
#ifdef ThePEG_HAS_FPU_CONTROL
  fpu_control_t cw;
  _FPU_GETCW(cw);
  cw &= ~(_FPU_MASK_DM);
  _FPU_SETCW(cw);
#endif
}

void Debug::unmaskFpuInvalid()  {
#ifdef ThePEG_HAS_FPU_CONTROL
  fpu_control_t cw;
  _FPU_GETCW(cw);
  cw &= ~(_FPU_MASK_IM);
  _FPU_SETCW(cw);
#endif
}

void Debug::maskFpuErrors() {
  maskFpuOverflow();
  maskFpuDivZero();
  maskFpuDenorm();
  maskFpuInvalid();
}

void Debug::maskFpuOverflow() {
#ifdef ThePEG_HAS_FPU_CONTROL
  fpu_control_t cw;
  _FPU_GETCW(cw);
  cw |= (_FPU_MASK_OM);
  _FPU_SETCW(cw);
#endif
}

void Debug::maskFpuUnderflow() {
#ifdef ThePEG_HAS_FPU_CONTROL
  fpu_control_t cw;
  _FPU_GETCW(cw);
  cw |= (_FPU_MASK_UM);
  _FPU_SETCW(cw);
#endif
}

void Debug::maskFpuDivZero() {
#ifdef ThePEG_HAS_FPU_CONTROL
  fpu_control_t cw;
  _FPU_GETCW(cw);
  cw |= (_FPU_MASK_ZM);
  _FPU_SETCW(cw);
#endif
}

void Debug::maskFpuDenorm() {
#ifdef ThePEG_HAS_FPU_CONTROL
  fpu_control_t cw;
  _FPU_GETCW(cw);
  cw |= (_FPU_MASK_DM);
  _FPU_SETCW(cw);
#endif
}

void Debug::maskFpuInvalid() {
#ifdef ThePEG_HAS_FPU_CONTROL
  fpu_control_t cw;
  _FPU_GETCW(cw);
  cw |= (_FPU_MASK_IM);
  _FPU_SETCW(cw);
#endif
}

