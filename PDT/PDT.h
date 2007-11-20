// -*- C++ -*-
//
// PDT.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_PDT_H
#define ThePEG_PDT_H
// This is the declaration of the PDT class.

#include "ThePEG/Config/ThePEG.h"
// #include "PDT.fh"
// #include "PDT.xh"

namespace ThePEG {

/**
 * PDT is a helper class implementing enumerations for charge, colour
 * and spin to be used by the ParticleData class. In addition, some
 * static utility functions are provided.
 *
 * @see ParticleData
 */
class PDT {

public:

  /**
   * Definition of enumerated values used for spin information. THe
   * integer values are given according to 2s+1.
   */
  enum Spin {
    SpinNA = -1,       /**< Spin is not applicable. */
    SpinUnknown = 0,   /**< Unknown spin */
    SpinUndefined = 0, /**< Undefined spin */
    Spin0 = 1,         /**< Spin zero. */
    Spin1Half = 2,     /**< Spin 1/2. */
    Spin1 = 3,         /**< Spin 1. */
    Spin3Half = 4,     /**< Spin 3/2. */
    Spin2 = 5,         /**< Spin 2. */
    Spin5Half = 6,     /**< Spin 5/2. */
    Spin3 = 7,         /**< Spin 4. */
    Spin7Half = 8,     /**< Spin 7/2. */
    Spin4 = 9          /**< Spin 5. */
  };

  /**
   * Definition of enumerated values used for charge information. The
   * integer values are given in units of e/3.
   */
  enum Charge {
    ChargeUnknown = -999999,   /**< Unknown charge. */
    ChargeUndefined = -999999, /**< Undefined charge. */
    Charged = 999990,          /**< Is charged. */ 
    Positive = 900000,         /**< Is positively charged. */ 
    Negative = -900000,        /**< Is negatively charged. */ 
    ChargeNeutral = 0,         /**< Uncharged. */ 
    Charge0 = 0,               /**< Uncharged. */ 
    Plus1Third = 1,            /**< e/3. */ 
    Plus2Third = 2,            /**< 2e/3. */ 
    Plus1 = 3,                 /**< e. */ 
    Minus1Third = -1,          /**< -e/3. */ 
    Minus2Third = -2,          /**< -2e/3. */ 
    Minus1 = -3,               /**< -e. */ 
    Plus4Third = 4,            /**< 4e/3. */ 
    Plus5Third = 5,            /**< 5e/3. */ 
    Plus2 = 6,                 /**< 2e. */ 
    Minus4Third = -4,          /**< -4e/3. */ 
    Minus5Third = -5,          /**< -5e/3. */ 
    Minus2 = -6,               /**< -3e. */ 
    Plus7Third = 7,            /**< 7e/3. */ 
    Plus8Third = 8,            /**< 8e/3. */ 
    Plus3 = 9,                 /**< 3e. */ 
    Minus7Third = -7,          /**< -7e/3. */ 
    Minus8Third = -8,          /**< -8e/3. */ 
    Minus3 = -9,               /**< -3e. */ 
    Plus4 = 12,                /**< 4e. */ 
    Plus5 = 15,                /**< 5e. */ 
    Plus6 = 18,                /**< 6e. */ 
    Plus7 = 21,                /**< 7e. */ 
    Plus8 = 24,                /**< 8e. */ 
    Minus4 = -12,              /**< -4e. */ 
    Minus5 = -15,              /**< -5e. */ 
    Minus6 = -18,              /**< -6e. */ 
    Minus7 = -21,              /**< -7e. */ 
    Minus8 = -24               /**< -8e. */ 
  };

  /**
   *Definition of enumerated values used for color information.
   */
  enum Colour {
    ColourUnknown = -1,   /**< Unknown colour */
    ColourUndefined = -1, /**< Undefined colour */
    ColourNeutral = 0,    /**< Colour-singlet */
    Colour0 = 0,          /**< Colour-singlet */
    Coloured = 1,         /**< Coloured */
    Colour3 = 3,          /**< Colour-triplet */
    Colour3bar = -3,      /**< Colour-anti-triplet */
    Colour8 = 8,          /**< Colour-octet */
    ColorUnknown = -1,    /**< Unknown colour */
    ColorUndefined = -1,  /**< Undefined colour */
    ColorNeutral = 0,     /**< Colour-singlet */
    Color0 = 0,           /**< Colour-singlet */
    Colored = 1,          /**< Coloured */
    Color3 = 3,           /**< Colour-triplet */
    Color3bar = -3,       /**< Colour-anti-triplet */
    Color8 = 8            /**< Colour-octet */
 };

  /**
   * Allow also for american spelling.
   */
  typedef Colour Color;

  /**
   * True if the argument corresponds to a non-zero charge.
   */
  static inline bool charged(Charge c);

  /**
   * True if the argument corresponds to a positive charge.
   */
  static inline bool positive(Charge c);

  /**
   * True if the argument corresponds to a negative charge.
   */
  static inline bool negative(Charge c);

  /**
   * True if the argument corresponds to a non-zero color charge.
   */
  static inline bool colored(Color c);

  /**
   * True if the argument corresponds to a non-zero color charge.
   */
  static inline bool coloured(Color c);

  /**
   * Return the anti-colour of the specified colour.
   */
  static inline Color antiColor(Color c);

  /**
   * Return the anti-colour of the specified colour.
   */
  static inline Colour antiColour(Color c);

  /**
   * Return the flavour content of the given particle. The flavours
   * will be given in decreasing mass with flavour before
   * anti-flavour.
   */
  static vector<long> flavourContent(long id);

  /**
   * Return the flavour content of the given particle. The flavours
   * will be given in decreasing mass with flavour before
   * anti-flavour.
   */
  static vector<long> flavourContent(tcPDPtr);

  /**
   * Return the flavour content of the given particle. The flavours
   * will be given in decreasing mass with flavour before
   * anti-flavour.
   */
  static vector<long> flavourContent(tcPPtr);

  /**
   * Return the flavour content of the given particle. The flavours
   * will be given in decreasing mass with flavour before
   * anti-flavour.
   */
  static vector<long> flavourContent(const ParticleData &);

  /**
   * Return the flavour content of the given particle. The flavours
   * will be given in decreasing mass with flavour before
   * anti-flavour.
   */
  static vector<long> flavourContent(const Particle &);

};

/** Input a colour from a stream. */
template <typename IStream>
inline IStream & operator>>(IStream &, PDT::Colour &);

/** Input a charge from a stream. */
template <typename IStream>
inline IStream & operator>>(IStream &, PDT::Charge &);

/** Input a spin from a stream. */
template <typename IStream>
inline IStream & operator>>(IStream &, PDT::Spin &);

}

#include "PDT.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PDT.tcc"
#endif

#endif /* ThePEG_PDT_H */
