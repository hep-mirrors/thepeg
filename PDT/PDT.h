// -*- C++ -*-
#ifndef ThePEG_PDT_H
#define ThePEG_PDT_H
//
// This is the declaration of the <!id>PDT<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>PDT<!!id> is a helper class implementing enumerations for
// charge, colour and spin to be used by the
// <!class>ParticleData<!!class> class. In addition, some static
// utility functions are given.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ParticleData.html">ParticleData.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
// #include "PDT.fh"
// #include "PDT.xh"

namespace ThePEG {

class PDT {

public:

  enum Spin {
    SpinNA = -1, SpinUnknown = 0, SpinUndefined = 0,
    Spin0 = 1, Spin1Half = 2, Spin1 = 3, Spin3Half = 4,
    Spin2 = 5, Spin5Half = 6, Spin3 = 7, Spin7Half = 8, Spin4 = 9 };
  //Definition of enumerated values used for spin information.

  enum Charge {
    ChargeUnknown = -999999, ChargeUndefined = -999999, Charged = 999990, 
    Positive = 900000, Negative = -900000, ChargeNeutral = 0, Charge0 = 0,
    Plus1Third = 1, Plus2Third = 2, Plus1 = 3,
    Minus1Third = -1, Minus2Third = -2, Minus1 = -3,
    Plus4Third = 4, Plus5Third = 5, Plus2 = 6,
    Minus4Third = -4, Minus5Third = -5, Minus2 = -6,
    Plus7Third = 7, Plus8Third = 8, Plus3 = 9,
    Minus7Third = -7, Minus8Third = -8, Minus3 = -9,
    Plus4 = 12, Plus5 = 15, Plus6 = 18, Plus7 = 21, Plus8 = 24,
    Minus4 = -12, Minus5 = -15, Minus6 = -18, Minus7 = -21, Minus8 = -24 };
  //Definition of enumerated values used for charge information.

  enum Colour {
    ColourUnknown = -1, ColourUndefined = -1, ColourNeutral = 0, Colour0 = 0,
    Coloured = 1, Colour3 = 3, Colour3bar = -3, Colour8 = 8,
    ColorUnknown = -1, ColorUndefined = -1, ColorNeutral = 0, Color0 = 0,
    Colored = 1, Color3 = 3, Color3bar = -3, Color8 = 8 };
  typedef Colour Color;
  //Definition of enumerated values used for color information.

  static inline bool charged(Charge c);
  // True if the argument corresponds to a non-zero charge.

  static inline bool positive(Charge c);
  // True if the argument corresponds to a positive charge.

  static inline bool negative(Charge c);
  // True if the argument corresponds to a negative charge.

  static inline bool colored(Color c);
  static inline bool coloured(Color c);
  // True if the argument corresponds to a non-zero color charge.

  static inline Color antiColor(Color c);
  static inline Colour antiColour(Color c);
  // Return the anti-colour of the specified colour.

  static vector<long> flavourContent(long id);
  static vector<long> flavourContent(tcPDPtr);
  static vector<long> flavourContent(tcPPtr);
  static vector<long> flavourContent(const ParticleData &);
  static vector<long> flavourContent(const Particle &);
  // Return the flavour content of the given particle. The flavours
  // will be given in decreasing mass with flavour before
  // anti-flavour.

};

template <typename IStream>
inline IStream & operator>>(IStream &, PDT::Colour &);

template <typename IStream>
inline IStream & operator>>(IStream &, PDT::Charge &);

template <typename IStream>
inline IStream & operator>>(IStream &, PDT::Spin &);

}

#include "PDT.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PDT.tcc"
#endif

#endif /* ThePEG_PDT_H */
