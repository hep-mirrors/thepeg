// -*- C++ -*-
//
// VertexBase.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_VertexBase_H
#define ThePEG_VertexBase_H
//
// This is the declaration of the VertexBase class.

#include <ThePEG/Interface/Interfaced.h>
#include <ThePEG/PDT/ParticleData.h>
#include <ThePEG/PDT/WidthGenerator.h>
#include <ThePEG/Helicity/HelicityDefinitions.h>
#include <ThePEG/Repository/EventGenerator.h>
#include "ThePEG/StandardModel/StandardModelBase.h"
#include "VertexBase.fh"

namespace ThePEG {
namespace Helicity {

/**
 * Enumeration for naming of vertices
 */
enum VertexType {FFS,VSS,VVSS,VVS,SSS,SSSS,
		 FFV,VVV,VVVV,FFT,FFVT,SST,VVT,VVVT};

/** \ingroup Helicity
 * 
 *  The VertexBase class is the base class for all helicity amplitude
 *  vertices. In implements the storage of the particles 
 *  which are allowed to interact at the vertex and some simple functions 
 *  which are often needed by the classes which implement the specific 
 *  vertices.
 *
 *  In practice little use is made of this information and it is mainly
 *  included for future extensions. It can also be used at the development
 *  and debugging stage.
 *
 */
class VertexBase  : public Interfaced {
  
/**
 *  The output operator is a friend to avoid the data being public.
 */
friend ostream & operator<<(ostream &, const VertexBase &);

public:
  
  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Constructor for three point vertices.
   * @param ispin1 \f$2S+1\f$ for the first  particle.
   * @param ispin2 \f$2S+1\f$ for the second particle.
   * @param ispin3 \f$2S+1\f$ for the third  particle.
   * @param id1 The PDG codes for the first  set of particles.
   * @param id2 The PDG codes for the second set of particles.
   * @param id3 The PDG codes for the third  set of particles.
   * @param kine Whether the kinematic invariants should be calculated.
   */
  inline VertexBase(int ispin1,int ispin2,int ispin3,
		    vector<int> id1,vector<int> id2,vector<int> id3,bool kine=false);

  /**
   * Constructor for four point vertices.
   * @param ispin1 \f$2S+1\f$ for the first  particle.
   * @param ispin2 \f$2S+1\f$ for the second particle.
   * @param ispin3 \f$2S+1\f$ for the third  particle.
   * @param ispin4 \f$2S+1\f$ for the fourth  particle.
   * @param id1 The PDG codes for the first  set of particles.
   * @param id2 The PDG codes for the second set of particles.
   * @param id3 The PDG codes for the third  set of particles.
   * @param id4 The PDG codes for the fourth  set of particles.
   * @param kine Whether the kinematic invariants should be calculated.
   */
  inline VertexBase(int ispin1,int ispin2,int ispin3,int ispin4,
		    vector<int> id1,vector<int> id2,vector<int> id3,vector<int> id4,
		    bool kine=false);

  /**
   * Constructor for five point vertices.
   * @param ispin1 \f$2S+1\f$ for the first  particle.
   * @param ispin2 \f$2S+1\f$ for the second particle.
   * @param ispin3 \f$2S+1\f$ for the third  particle.
   * @param ispin4 \f$2S+1\f$ for the fourth particle.
   * @param ispin5 \f$2S+1\f$ for the fifth  particle.
   * @param id1 The PDG codes for the first  set of particles.
   * @param id2 The PDG codes for the second set of particles.
   * @param id3 The PDG codes for the third  set of particles.
   * @param id4 The PDG codes for the fourth set of particles.
   * @param id5 The PDG codes for the fifth  set of particles.
   * @param kine Whether the kinematic invariants should be calculated.
   */
  inline VertexBase(int ispin1,int ispin2,int ispin3,int ispin4,int ispin5,
		    vector<int> id1,vector<int> id2,vector<int> id3,vector<int> id4,
		    vector<int> id5,bool kine=false);

  /**
   * Constructor for \f$n\f$-point vertices.
   * @param npoint The number of external particles.
   * @param kine Whether the kinematic invariants should be calculated.
   */
  inline VertexBase(unsigned int npoint=0,bool kine=false);
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
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();
  
public:

  /**
   * Add particles to the lists.
   */
  //@{ 
  /**
   * Add item to three point list.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   */
  void add(int id1,int id2,int id3);

  /**
   * Add item to four point list.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   * @param id4 PDG code of the fourth particle.
   */
  void add(int id1,int id2,int id3,int id4);

  /**
   * Add item to five  point list.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   * @param id4 PDG code of the fourth particle.
   * @param id5 PDG code of the fifth particle.
   */
  void add(int id1,int id2,int id3,int id4,int id5);
  //@}

  /**
   *  Access to the particle information
   */
  //@{
  /**
   * Number of different particle combinations allowed.
   */
  inline unsigned int size();

  /**
   * Get the number of external particles.
   */
  inline unsigned int getNpoint();

  /**
   * Is a particle allowed as an incoming particle?
   * @param id The PDG code
   */
  inline bool incoming(int id);

  /**
   * Is a particle allowed as an outgoing particle?
   * @param id The PDG code
   */
  inline bool outgoing(int id);

  /**
   * Get the list of incoming particles.
   */
  inline vector<PDPtr> getIncoming();

  /**
   * Get the list of outgoing particles.
   */
  inline vector<PDPtr> getOutgoing();

  /**
   * Get the coupling.
   */
  inline const Complex & getNorm();

  /**
   * Function to search the list.
   * @param ilist Which list to search
   * @param id The PDG code to look for.
   */
  vector<PDPtr> search(unsigned int ilist,int id);

  /**
   * Is a given combination allowed.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   */
  bool allowed(int id1,int id2,int id3);

  /**
   * Is a given combination allowed.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   * @param id4 PDG code of the fourth particle.
   */
  bool allowed(int id1,int id2,int id3,int id4);

  /**
   * Is a given combination allowed.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   * @param id4 PDG code of the fourth particle.
   * @param id5 PDG code of the fifth particle.
   */
  bool allowed(int id1,int id2,int id3,int id4,int id5);

  /**
   * Get name of Vertex
   */
  inline VertexType getName() const;

  /**
   * Get the order in \f$g_EM\f$
   */
  inline unsigned int orderInGem() const;

  /**
   * Get the order in \f$g_s\f$
   */
  inline unsigned int orderInGs() const;
  //@}

protected:

  /**
   * @name Calculation of the strong, electromagnetic and weak couplings
   */
  //@{
  /**
   *  Strong coupling
   */
  inline double strongCoupling(Energy2);

  /**
   *  Electromagentic coupling
   */
  inline double electroMagneticCoupling(Energy2);

  /**
   *  Weak coupling
   */
  inline double weakCoupling(Energy2);
  //@}

protected:
  
  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit() throw(InitException);
  //@}

protected:

  /**
   *  Members to set-up the particles
   */
  //@{
  /**
   * Setup the spins of the particles for a three point vertex.
   * @param ispin1 \f$2S+1\f$ for the first  particle.
   * @param ispin2 \f$2S+1\f$ for the second particle.
   * @param ispin3 \f$2S+1\f$ for the third  particle.
   */
  inline void setSpin(int ispin1,int ispin2,int ispin3);

  /**
   * Setup the spins of the particles for a four point vertex.
   * @param ispin1 \f$2S+1\f$ for the first  particle.
   * @param ispin2 \f$2S+1\f$ for the second particle.
   * @param ispin3 \f$2S+1\f$ for the third  particle.
   * @param ispin4 \f$2S+1\f$ for the fourth particle.
   */
  inline void setSpin(int ispin1,int ispin2,int ispin3,int ispin4);

  /**
   * Setup the spins of the particles for a five point vertex.
   * @param ispin1 \f$2S+1\f$ for the first  particle.
   * @param ispin2 \f$2S+1\f$ for the second particle.
   * @param ispin3 \f$2S+1\f$ for the third  particle.
   * @param ispin4 \f$2S+1\f$ for the fourth particle.
   * @param ispin5 \f$2S+1\f$ for the fifth  particle.
   */
  inline void setSpin(int ispin1,int ispin2,int ispin3,int ispin4,int ispin5);

  /**
   * Set up the lists of particles for the three point vertex.
   * @param id1 The PDG codes for the first  set of particles.
   * @param id2 The PDG codes for the second set of particles.
   * @param id3 The PDG codes for the third  set of particles.
   */
  void setList(vector<int> id1,vector<int> id2,vector<int> id3);

  /**
   * Set up the lists of particles for the three point vertex.
   * @param id1 The PDG codes for the first  set of particles.
   * @param id2 The PDG codes for the second set of particles.
   * @param id3 The PDG codes for the third  set of particles.
   * @param id4 The PDG codes for the fourth set of particles.
   */
  void setList(vector<int> id1,vector<int> id2,vector<int> id3,vector<int> id4);

  /**
   * Set up the lists of particles for the three point vertex.
   * @param id1 The PDG codes for the first  set of particles.
   * @param id2 The PDG codes for the second set of particles.
   * @param id3 The PDG codes for the third  set of particles.
   * @param id4 The PDG codes for the fourth set of particles.
   * @param id5 The PDG codes for the fifth  set of particles.
   */
  void setList(vector<int> id1,vector<int> id2,vector<int> id3,vector<int> id4,
	       vector<int> id5);

  /**
   * Set the list of incoming particles.
   */
  void setIncoming();

  /**
   * Set the list of outgoing particles.
   */
  void setOutgoing();

  /**
   * Set the number of external particles.
   * @param npoint The number of external particles.
   */
  inline void setNpoint(unsigned int npoint);
  //@}

  /**
   *  Members for the amplitude calculations
   */
  //@{
  /**
   * Set the coupling.
   * @param coup The coupling.
   */
  inline void setNorm(const Complex & coup);

  /**
   * Calculate the propagator for a diagram.
   * @param iopt The option for the Breit-Wigner shape
   * @param q2 The scale
   * @param part The ParticleData pointer for the off-shell particle.
   * @param mass The mass if not to be taken from the ParticleData object
   * @param width The width if not to be taken from the ParticleData object
   */
  virtual Complex propagator(int iopt, Energy2 q2,tcPDPtr part,Energy mass=-GeV,
			     Energy width=-GeV);

  /**
   * Calculate propagator multiplied by coupling.
   * @param iopt The option for the Breit-Wigner shape
   * @param q2 The scale
   * @param part The ParticleData pointer for the off-shell particle.
   * @param mass The mass if not to be taken from the ParticleData object
   * @param width The width if not to be taken from the ParticleData object
   */
  inline Complex normPropagator(int iopt, Energy2 q2,tcPDPtr part,
				Energy mass=-GeV, Energy width=-GeV);
  //@}    

public:
  /** @name Kinematic invariants for loop diagrams */
  //@{

  /**
   * Whether or not to calculate the kinematics invariants
   */
  inline bool kinematics();

  /**
   * Set whether or not to calculate the kinematics invariants
   */
  inline void kinematics(bool );

  /**
   *  Calculate the kinematics for a 3-point vertex
   */
  inline void calculateKinematics(const Lorentz5Momentum &,const Lorentz5Momentum &,
				  const Lorentz5Momentum &);
  /**
   *  Calculate the kinematics for a 4-point vertex
   */
  inline void calculateKinematics(const Lorentz5Momentum &,const Lorentz5Momentum &,
				  const Lorentz5Momentum &,const Lorentz5Momentum &);
  /**
   *  Calculate the kinematics for a 5-point vertex
   */
  inline void calculateKinematics(const Lorentz5Momentum &,const Lorentz5Momentum &,
				  const Lorentz5Momentum &,const Lorentz5Momentum &,
				  const Lorentz5Momentum &);
  /**
   *  Calculate the kinematics for a n-point vertex
   */
  inline void calculateKinematics(const vector<Lorentz5Momentum> &);

  /**
   * Get one of the kinematic invariants
   */
  inline Energy2 invariant(unsigned int,unsigned int);
  //@}
  
protected:
  
  /**
   * Set the name of the vertex to one of enumerated values.
   */
  inline void setName(const VertexType &);

  /**
   * Set the order in \f$g_EM\f$
   * @param order The order of the vertex in \f$g_EM\f$
   */
  inline void orderInGem(unsigned int order);

  /**
   * Set the order in \f$g_s\f$
   * @param order The order of the vertex in \f$g_s\f$
   */
  inline void orderInGs(unsigned int order);
  
private:
  
  /**
   * Describe a concrete class with persistent data.
   */
  static AbstractClassDescription<ThePEG::Helicity::VertexBase> initVertexBase;
  
  /**
   * Private and non-existent assignment operator.
   */
  VertexBase & operator=(const VertexBase &);
  
private:

  /**
   * Storage of the particles.   
   */
  //@{
  /**
   * PDG codes for the first set of  particles.
   */
  vector<int> _iparticlea;

  /**
   * PDG codes for the second set of  particles.
   */
  vector<int> _iparticleb;

  /**
   * PDG codes for the third set of  particles.
   */
  vector<int> _iparticlec;

  /**
   * PDG codes for the fourth set of  particles.
   */
  vector<int> _iparticled;

  /**
   * PDG codes for the fifth set of  particles.
   */
  vector<int> _iparticlee;

  /**
   *  Particles interacting at the vertex
   */
  vector<vector<PDPtr> > _particles;

  /**
   * Spin.
   */
  vector<int> _ispin;

  /**
   *  Number of particles at the vertex
   */
  unsigned int _npoint;

  /**
   *  Number of particle combinations at the vertex
   */
  unsigned int _nsize;

  /**
   * ParticleData pointers for the allowed incoming particles.
   */
  vector<PDPtr> _inpart;

  /**
   * PDG codes for the allowed incoming particles.
   */
  vector <int> _iinpart;

  /**
   * ParticleData pointers for the allowed outgoing particles.
   */
  vector<PDPtr> _outpart;

  /**
   * PDG codes for the allowed outgoing particles.
   */
  vector <int> _ioutpart;
  //@}

  /**
   * The overall coupling.
   */
  Complex _norm;

  /**
   * Whether or not to calculate the kinematic invariants for the vertex
   */
  bool _calckinematics;

  /**
   * Kinematica quantities needed for loop vertices
   */
  Energy2 _kine[5][5];

  /**
   * Name of vertex
   */
  VertexType _theName;

  /**
   * Order of vertex in \f$g_EM\f$
   */
  unsigned int _ordergEM;

  /**
   * Order of vertex in \f$g_s\f$
   */
  unsigned int _ordergS;

  /**
   *  option for the coupling
   */
  unsigned int _coupopt;

  /**
   *  Fixed value of strong coupling to use
   */
  double _gs;

  /**
   *  Fixed value of the electromagentic coupling to use
   */
  double _ee;

  /**
   *  Fixed value of \f$\sin\theta_W\f$ to use
   */
  double _sw;
};
  
/**
 * Output the information on the vertex.
 */
ostream & operator<<(ostream &, const VertexBase &);
  
}
}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/**
 * The following template specialization informs ThePEG about the
 * base class of VertexBase.
 */
template <>
struct BaseClassTrait<ThePEG::Helicity::VertexBase,1> {
  /** Typedef of the base class of VertexBase. */
  typedef Interfaced NthBase;
};

/**
 * The following template specialization informs ThePEG about the
 * name of this class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ThePEG::Helicity::VertexBase>
  : public ClassTraitsBase<ThePEG::Helicity::VertexBase> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::VertexBase"; }
};

/** @endcond */

}
#include "VertexBase.icc"

#endif /* ThePEG_VertexBase_H */
