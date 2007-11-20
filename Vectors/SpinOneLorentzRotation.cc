// -*- C++ -*-
//
// SpinOneLorentzRotation.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LorentzRotation class.
//

#include "SpinOneLorentzRotation.h"

using namespace ThePEG;

// output operator
std::ostream & SpinOneLorentzRotation::print( std::ostream &  os) const {  
  os << "\n   [ ( " <<
    std::setw(14) << std::setprecision(6) << xx() << "   " <<
    std::setw(14) << std::setprecision(6) << xy() << "   " <<
    std::setw(14) << std::setprecision(6) << xz() << "   " <<
    std::setw(14) << std::setprecision(6) << xt() << ")\n"
     << "     ( " <<
    std::setw(14) << std::setprecision(6) << yx() << "   " <<
    std::setw(14) << std::setprecision(6) << yy() << "   " <<
    std::setw(14) << std::setprecision(6) << yz() << "   " <<
    std::setw(14) << std::setprecision(6) << yt() << ")\n"
     << "     ( " <<
    std::setw(14) << std::setprecision(6) << zx() << "   " <<
    std::setw(14) << std::setprecision(6) << zy() << "   " <<
    std::setw(14) << std::setprecision(6) << zz() << "   " <<
    std::setw(14) << std::setprecision(6) << zt() << ")\n"
     << "     ( " <<
    std::setw(14) << std::setprecision(6) << tx() << "   " <<
    std::setw(14) << std::setprecision(6) << ty() << "   " <<
    std::setw(14) << std::setprecision(6) << tz() << "   " <<
    std::setw(14) << std::setprecision(6) << tt() << ") ]\n";
  return os;
}

SpinOneLorentzRotation & SpinOneLorentzRotation::
setBoost (double bx, double by, double bz, double gamma) {
  double beta2 = sqr(bx) + sqr(by) + sqr(bz);
  if (beta2 >= 1.0) {
    throw Exception() << "Invalid boost (" << bx << ',' << by << ',' << bz 
		      << ") in SpinOneLorentzRotatio::setBoost" << Exception::eventerror;
  }
  if(gamma<0.) gamma = 1.0 / sqrt((1.-bz)*(1.+bz)-sqr(bx)-sqr(by));
  double bgamma = sqr(gamma) / (1.0 + gamma);
  xx_() = 1.0 + bgamma * bx * bx;
  yy_() = 1.0 + bgamma * by * by;
  zz_() = 1.0 + bgamma * bz * bz;
  xy_() = yx_() = bgamma * bx * by;
  xz_() = zx_() = bgamma * bx * bz;
  yz_() = zy_() = bgamma * by * bz;
  xt_() = tx_() = gamma * bx;
  yt_() = ty_() = gamma * by;
  zt_() = tz_() = gamma * bz;
  tt_() = gamma;
  return *this;
}
