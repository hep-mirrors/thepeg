// -*- C++ -*-
#ifndef ThePEG_ColourSinglet_H
#define ThePEG_ColourSinglet_H
//
// This is the declaration of the <!id>ColourSinglet<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// A <!id>ColourSinglet<!!id> object represents a set of
// colour-connected partons in a total colour-singlet state. The
// simplest form is a single string represented by a vector of partons
// starting from a colour-triplet parton followed by a number of
// colour-octet partons and ending in a anti-triplet. A closed string
// is represented by a vector of colour-octet partons. If junctions
// are present, there will be a vector of string pieces containing the
// associated partons, with associated information about the string
// pieces connected via sinks or sources.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ColourLine.html">ColourLine.h</a>,
// <a href="http:Particle.html">Particle.h</a>.
// 

#include "ThePEG/EventRecord/EventConfig.h"
// #include "ColourSinglet.fh"
// #include "ColourSinglet.xh"

namespace ThePEG {

class ColourSinglet {

public:

  typedef deque<tcPPtr> StringPiece;
  typedef StringPiece::size_type Index;
  typedef pair<Index,Index> Junction;

public:

  inline ColourSinglet();
  inline ColourSinglet(const ColourSinglet &);
  inline ~ColourSinglet();
  // Standard ctors and dtor.

  inline ColourSinglet & operator=(const ColourSinglet &);
  //  Private and non-existent assignment operator.

  ColourSinglet(tcColinePtr cl, tcParticleSet & left);
  // Constructor taking an initial colour line and a set of partons to
  // select from.

protected:

  ColourSinglet(const ColourSinglet & cs, Index si);
  // When splitting an internal line create a new colour singlet
  // starting from the string piece si in the singlet cs.

public:

  inline tcPVector & partons();
  inline const tcPVector & partons() const;
  inline tcPPtr parton(tcPVector::size_type i) const;
  // Access the vector of partons.

  LorentzMomentum momentum() const;
  // Return the total momentum for the partons in the colour singlet.

  inline Index nPieces() const;
  // Return the number of string pieces.

  inline StringPiece & piece(Index i);
  inline const StringPiece & piece(Index i) const;
  // Return the partons belonging to string piece with index i (note
  // that the indices starts with 1).

  inline Junction & junction(Index i, bool forward);
  inline const Junction & junction(Index i, bool forward) const;
  // Return the sink (or source if not forward) neghbors of string
  // piece with index i (note that the indices starts with 1).

  inline Junction & sink(Index i);
  inline const Junction & sink(Index i) const;
  inline Junction & source(Index i);
  inline const Junction & source(Index i) const;
  // Return the sink or source neghbors of string piece with index
  // i (note that the indices starts with 1).

  static vector<ColourSinglet> getSinglets(tcParticleSet & left);
  // Extract colour-singlet strings/clusters of partons from the given
  // set. The set will be empty afterwards if all went well - even
  // colour-singlet particles will be removed.

  template <typename Iterator>
  inline static vector<ColourSinglet>
  getSinglets(Iterator first, Iterator last);
  // Extract colour-singlet strings/clusters of partons from the given
  // range of particles.

  tcPDVector getTripletData() const;
  // Return a vector with data objects corresponding to all triplet
  // partons in this singlet.

  ColourSinglet splitInternal(Index sp = 0);
  // Split the internal string piece sp (one that starts from a source
  // and ends in a sink). Randomly pair together the connectin string
  // pieces and randomly assign possible colour octet partons to the
  // two joined string pieces. The singlet will then split into two - 
  // one is returned and this will contain the other. If no argument
  // is given, a random internal line will be picked.

  ColourSinglet splitInternal(Index sp, Index sa, Index sc,
			      const vector<bool> & assing);
  // Split the internal string piece sp(one that starts from a source
  // and ends in a sink). The source neighbour sa will be joined with
  // the sink neighbour sc. Possible colour octet partons in the split
  // string piece will be assigned to the joined sa-sc string piece if
  // the corresponing assign element is true. The singlet will then
  // split into two - one is returned and this will contain the other.

  ColourSinglet
  splitDiQuarkJunction(Index sp, tcPPtr diq, tcPPair qq,
		       const vector<bool> & assign = vector<bool>());
  // If a sting piece sp is connected to a junction and ends in a
  // diquark diq, split the diquark into two quarks qq, remove the
  // junction, adding the other partons to the first neighbouring
  // string piece if the corresponding assign element is true. The
  // singlet will then split into two - one is returned and this will
  // contain the other. Note that the parent-children relationship and
  // colour flows of the diquark and the two quarks is not handled by
  // this function.

  ColourSinglet splitDiDiQuark(tcPPair qq1, tcPPair qq2,
			       const vector<bool> & assign = vector<bool>());
  // If the singlet is a simple string with diquarks in both ends,
  // split the diquarks into the given quark pairs and create two new
  // string pieces the betwen the quark and anit-quarks, adding the
  // remaining partons to the first piece if the corresponding assign
  // element is true. The singlet will then split into two - one is
  // returned and this will contain the other. Note that the
  // parent-children relationship and colour flows of the diquark and
  // the two quarks is not handled by this function.

  inline void swap(ColourSinglet & x);
  // Swap this colour singlet for the argument.

private:

  bool fill(Index s0, bool forward, tcColinePtr first, tcParticleSet & left);
  // Follow a colour line 'forward' in colour removing partons from
  // the left set and adding them to the string piece s0 as we go
  // along. If a line ends in a colour sink/source, follow the other
  // two colour lines in turn '!forward'.

  void fill(Index i0, bool forward, const ColourSinglet & cs, Index i1);
  // When creating a new singlet from an old one which has been split,
  // add the string piece i1. If it ends in a sink or a source add the
  // neighbors recursively.

  inline Index addPiece();
  // Add a new string piece and return its index.

  Junction addJunction(Index s0, bool forward);
  // Add a junction which is a source (or sink if forward). Return the
  // indices of the two connected string pieces.

public:

  class ColourSingletException: public Exception {};

private:

  tcPVector thePartons;
  // The vector of all partons.

  vector<StringPiece> thePieces;
  // The different string pieces.

  vector<Junction> theSources;
  vector<Junction> theSinks;
  // The sources and sink neighbours corresponding to the string
  // pieces.

};

}

#include "ColourSinglet.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ColourSinglet.tcc"
#endif

#endif /* ThePEG_ColourSinglet_H */
