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
		 FFV,VVV,VVVV,FFT,FFVT,SST,VVT,VVVT,UNDEFINED};

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
  VertexBase(int ispin1,int ispin2,int ispin3,
	     vector<long> id1,vector<long> id2,vector<long> id3,
	     bool kine=false) 
  : _npoint(3), _nsize(0), _norm(0), _calckinematics(kine), 
    _kine(5,vector<Energy2>(5)), _theName(UNDEFINED), 
    _ordergEM(0), _ordergS(0),
    _coupopt(0), _gs(sqrt(4.*Constants::pi*0.3)), 
    _ee(sqrt(4.*Constants::pi/137.04)),
    _sw(sqrt(0.232)) {
    // initialise the spins
    setSpin(ispin1,ispin2,ispin3);
    // and the particles;
    setList(id1,id2,id3);
  }

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
  VertexBase(int ispin1,int ispin2,int ispin3,int ispin4,
	     vector<long> id1,vector<long> id2,vector<long> id3,
	     vector<long> id4,bool kine=false)
    : _npoint(4), _nsize(0), _norm(0), _calckinematics(kine), 
      _kine(5,vector<Energy2>(5)), _theName(UNDEFINED), 
      _ordergEM(0), _ordergS(0),
      _coupopt(0), _gs(sqrt(4.*Constants::pi*0.3)), 
      _ee(sqrt(4.*Constants::pi/137.04)),
      _sw(sqrt(0.232)) {
    // initialise the spins
    setSpin(ispin1,ispin2,ispin3,ispin4);
    // and the particles
    setList(id1,id2,id3,id4);
  }

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
  VertexBase(int ispin1,int ispin2,int ispin3,int ispin4,int ispin5,
	     vector<long> id1,vector<long> id2,vector<long> id3,vector<long> id4,
	     vector<long> id5,bool kine=false) 
    :  _npoint(5), _nsize(0), _norm(0), _calckinematics(kine), 
       _kine(5,vector<Energy2>(5)), _theName(UNDEFINED), 
       _ordergEM(0), _ordergS(0),
       _coupopt(0), _gs(sqrt(4.*Constants::pi*0.3)), 
       _ee(sqrt(4.*Constants::pi/137.04)),
       _sw(sqrt(0.232)) {
    // initialise the spins
    setSpin(ispin1,ispin2,ispin3,ispin4,ispin5);
    // and the particles
    setList(id1,id2,id3,id4,id5);
  }

  /**
   * Constructor for \f$n\f$-point vertices.
   * @param npoint The number of external particles.
   * @param kine Whether the kinematic invariants should be calculated.
   */
  VertexBase(unsigned int npoint=0,bool kine=false) 
    : _npoint(npoint), _nsize(0), _norm(0), _calckinematics(kine), 
      _kine(5,vector<Energy2>(5)), _theName(UNDEFINED), 
      _ordergEM(0), _ordergS(0),
      _coupopt(0), _gs(sqrt(4.*Constants::pi*0.3)), 
      _ee(sqrt(4.*Constants::pi/137.04)),
      _sw(sqrt(0.232)) 
  {}
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
  void add(long id1,long id2,long id3);

  /**
   * Add item to four point list.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   * @param id4 PDG code of the fourth particle.
   */
  void add(long id1,long id2,long id3,long id4);

  /**
   * Add item to five  point list.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   * @param id4 PDG code of the fourth particle.
   * @param id5 PDG code of the fifth particle.
   */
  void add(long id1,long id2,long id3,long id4,long id5);
  //@}

  /**
   *  Access to the particle information
   */
  //@{
  /**
   * Number of different particle combinations allowed.
   */
  unsigned int size() { return _nsize; }

  /**
   * Get the number of external particles.
   */
  unsigned int getNpoint() { return _npoint; }

  /**
   * Is a particle allowed as an incoming particle?
   * @param id The PDG code
   */
  bool incoming(long id) {
    if(_iinpart.size()==0) return false; 
    for(unsigned int ix=0;ix<_iinpart.size();++ix) {
      if(_iinpart[ix]==id) return true;
    }
    return false;
  }

  /**
   * Is a particle allowed as an outgoing particle?
   * @param id The PDG code
   */
  bool outgoing(long id) {
    if(_outpart.size()==0) return false; 
    for(unsigned int ix=0;ix<_ioutpart.size();++ix) {
      if(_ioutpart[ix]==id) return true;
    }
    return false;
  }

  /**
   * Get the list of incoming particles.
   */
  const vector<tPDPtr> & getIncoming() const { return _inpart;}

  /**
   * Get the list of outgoing particles.
   */
  const vector<tPDPtr> & getOutgoing() const { return _outpart; }

  /**
   * Get the coupling.
   */
  Complex getNorm() const { return _norm; }

  /**
   * Function to search the list.
   * @param ilist Which list to search
   * @param id The PDG code to look for.
   */
  vector<tPDPtr> search(unsigned int ilist,long id);

  /**
   * Is a given combination allowed.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   */
  bool allowed(long id1,long id2,long id3);

  /**
   * Is a given combination allowed.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   * @param id4 PDG code of the fourth particle.
   */
  bool allowed(long id1,long id2,long id3,long id4);

  /**
   * Is a given combination allowed.
   * @param id1 PDG code of the first particle.
   * @param id2 PDG code of the second particle.
   * @param id3 PDG code of the third particle.
   * @param id4 PDG code of the fourth particle.
   * @param id5 PDG code of the fifth particle.
   */
  bool allowed(long id1,long id2,long id3,long id4,long id5);

  /**
   * Get name of Vertex
   */
  VertexType getName() const { return _theName; }

  /**
   * Get the order in \f$g_EM\f$
   */
  unsigned int orderInGem() const { return _ordergEM; }

  /**
   * Get the order in \f$g_s\f$
   */
  unsigned int orderInGs() const { return _ordergS; }
  //@}

protected:

  /**
   * @name Calculation of the strong, electromagnetic and weak couplings
   */
  //@{
  /**
   *  Strong coupling
   */
  double strongCoupling(Energy2 q2) {
    if(_coupopt==0)
      return sqrt(4.0*Constants::pi*generator()->standardModel()->alphaS(q2));
    else if(_coupopt==1)
      return sqrt(4.0*Constants::pi*generator()->standardModel()->alphaS());
    else
      return _gs;
  }

  /**
   *  Electromagentic coupling
   */
  double electroMagneticCoupling(Energy2 q2) {
    if(_coupopt==0)
      return sqrt(4.0*Constants::pi*generator()->standardModel()->alphaEM(q2));
    else if(_coupopt==1)
      return sqrt(4.0*Constants::pi*generator()->standardModel()->alphaEM());
    else
      return _ee;
  }

  /**
   *  Weak coupling
   */
  double weakCoupling(Energy2 q2) {
    if( _coupopt == 0 )
      return sqrt(4.0*Constants::pi*generator()->standardModel()->alphaEM(q2)/
		  generator()->standardModel()->sin2ThetaW());
    else if( _coupopt == 1 )
      return sqrt(4.0*Constants::pi*generator()->standardModel()->alphaEM()/
		  generator()->standardModel()->sin2ThetaW());
    else
      return _ee/_sw;
  }

  double sin2ThetaW() {
    if( _coupopt == 0 || _coupopt  == 1)
      return generator()->standardModel()->sin2ThetaW();
    else
      return sqr(_sw);
  }
  //@}

protected:
  
  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit();
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
  void setSpin(int ispin1,int ispin2,int ispin3) {
    if(_ispin.size()!=0)
      throw HelicityConsistencyError() << "VertexBase::setSpin the spins have already "
				       << "been set" << Exception::warning;
    else if(_npoint!=3)
      throw HelicityConsistencyError() << "VertexBase::setSpin not a three point vertex" 
				       << Exception::abortnow;
    else {
      _ispin.push_back(ispin1);
      _ispin.push_back(ispin2);
      _ispin.push_back(ispin3);
    }
  }

  /**
   * Setup the spins of the particles for a four point vertex.
   * @param ispin1 \f$2S+1\f$ for the first  particle.
   * @param ispin2 \f$2S+1\f$ for the second particle.
   * @param ispin3 \f$2S+1\f$ for the third  particle.
   * @param ispin4 \f$2S+1\f$ for the fourth particle.
   */
  void setSpin(int ispin1,int ispin2,int ispin3,int ispin4) {
    if(_ispin.size()!=0)
      throw HelicityConsistencyError() << "VertexBase::setSpin the spins have already "
				       << "been set" << Exception::warning;
    else if(_npoint!=4)
      throw HelicityConsistencyError() << "VertexBase::setSpin not a four point vertex" 
				       << Exception::abortnow;
    else {
      _ispin.push_back(ispin1);
      _ispin.push_back(ispin2);
      _ispin.push_back(ispin3);
      _ispin.push_back(ispin4);
    }
  }

  /**
   * Setup the spins of the particles for a five point vertex.
   * @param ispin1 \f$2S+1\f$ for the first  particle.
   * @param ispin2 \f$2S+1\f$ for the second particle.
   * @param ispin3 \f$2S+1\f$ for the third  particle.
   * @param ispin4 \f$2S+1\f$ for the fourth particle.
   * @param ispin5 \f$2S+1\f$ for the fifth  particle.
   */
  void setSpin(int ispin1,int ispin2,int ispin3,int ispin4,int ispin5) {
    if(_ispin.size()!=0)
      throw HelicityConsistencyError() << "VertexBase::setSpin the spins have already "
				       << "been set" << Exception::warning;
    else if(_npoint!=5)
      throw HelicityConsistencyError() << "VertexBase::setSpin not a five point vertex" 
				       << Exception::abortnow;
    else {
      _ispin.push_back(ispin1);
      _ispin.push_back(ispin2);
      _ispin.push_back(ispin3);
      _ispin.push_back(ispin4);
      _ispin.push_back(ispin5);
    }
  }

  /**
   * Set up the lists of particles for the three point vertex.
   * @param id1 The PDG codes for the first  set of particles.
   * @param id2 The PDG codes for the second set of particles.
   * @param id3 The PDG codes for the third  set of particles.
   */
  void setList(vector<long> id1,vector<long> id2,vector<long> id3);

  /**
   * Set up the lists of particles for the three point vertex.
   * @param id1 The PDG codes for the first  set of particles.
   * @param id2 The PDG codes for the second set of particles.
   * @param id3 The PDG codes for the third  set of particles.
   * @param id4 The PDG codes for the fourth set of particles.
   */
  void setList(vector<long> id1,vector<long> id2,vector<long> id3,vector<long> id4);

  /**
   * Set up the lists of particles for the three point vertex.
   * @param id1 The PDG codes for the first  set of particles.
   * @param id2 The PDG codes for the second set of particles.
   * @param id3 The PDG codes for the third  set of particles.
   * @param id4 The PDG codes for the fourth set of particles.
   * @param id5 The PDG codes for the fifth  set of particles.
   */
  void setList(vector<long> id1,vector<long> id2,vector<long> id3,vector<long> id4,
	       vector<long> id5);

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
  void setNpoint(unsigned int npoint) { _npoint= npoint; }
  //@}

  /**
   *  Members for the amplitude calculations
   */
  //@{
  /**
   * Set the coupling.
   * @param coup The coupling.
   */
  void setNorm(const Complex & coup) { _norm = coup; }

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
  Complex normPropagator(int iopt, Energy2 q2,tcPDPtr part,
			 Energy mass=-GeV, Energy width=-GeV) {
    return _norm*propagator(iopt,q2,part,mass,width);
  }
  //@}    

public:
  /** @name Kinematic invariants for loop diagrams */
  //@{

  /**
   * Whether or not to calculate the kinematics invariants
   */
  bool kinematics() { return _calckinematics; }

  /**
   * Set whether or not to calculate the kinematics invariants
   */
  void kinematics(bool kine ) { _calckinematics=kine; }

  /**
   *  Calculate the kinematics for a 3-point vertex
   */
  void calculateKinematics(const Lorentz5Momentum & p0,
			   const Lorentz5Momentum & p2,
			   const Lorentz5Momentum & p1) {
    _kine[0][0]=p0*p0;
    _kine[1][1]=p1*p1;
    _kine[2][2]=p2*p2;
    _kine[0][1]=p0*p1;_kine[1][0]=_kine[0][1];
    _kine[0][2]=p0*p2;_kine[2][0]=_kine[0][2];
    _kine[1][2]=p1*p2;_kine[2][1]=_kine[1][2];
  }
  
  /**
   *  Calculate the kinematics for a 4-point vertex
   */
  void calculateKinematics(const Lorentz5Momentum & p0,
			   const Lorentz5Momentum & p1,
			   const Lorentz5Momentum & p2,
			   const Lorentz5Momentum & p3) {
    _kine[0][0]=p0*p0;
    _kine[1][1]=p1*p1;
    _kine[2][2]=p2*p2;
    _kine[3][3]=p3*p3;
    _kine[0][1]=p0*p1;_kine[1][0]=_kine[0][1];
    _kine[0][2]=p0*p2;_kine[2][0]=_kine[0][2];
    _kine[0][3]=p0*p3;_kine[3][0]=_kine[0][3];
    _kine[1][2]=p1*p2;_kine[2][1]=_kine[1][2];
    _kine[1][3]=p1*p3;_kine[3][1]=_kine[1][3];
    _kine[2][3]=p2*p3;_kine[3][2]=_kine[2][3];
  }
  
  /**
   *  Calculate the kinematics for a 5-point vertex
   */
  void calculateKinematics(const Lorentz5Momentum & p0,
			   const Lorentz5Momentum & p1,
			   const Lorentz5Momentum & p2,
			   const Lorentz5Momentum & p3,
			   const Lorentz5Momentum & p4) {
    _kine[0][0]=p0*p0;
    _kine[1][1]=p1*p1;
    _kine[2][2]=p2*p2;
    _kine[3][3]=p3*p3;
    _kine[4][4]=p4*p4;
    _kine[0][1]=p0*p1;_kine[1][0]=_kine[0][1];
    _kine[0][2]=p0*p2;_kine[2][0]=_kine[0][2];
    _kine[0][3]=p0*p3;_kine[3][0]=_kine[0][3];
    _kine[0][4]=p0*p4;_kine[4][0]=_kine[0][4];
    _kine[1][2]=p1*p2;_kine[2][1]=_kine[1][2];
    _kine[1][3]=p1*p3;_kine[3][1]=_kine[1][3];
    _kine[1][4]=p1*p4;_kine[4][1]=_kine[1][4];
    _kine[2][3]=p2*p3;_kine[3][2]=_kine[2][3];
    _kine[2][4]=p2*p4;_kine[4][2]=_kine[2][4];
    _kine[3][4]=p3*p4;_kine[4][3]=_kine[3][4];
  }
  
  /**
   *  Calculate the kinematics for a n-point vertex
   */
  void calculateKinematics(const vector<Lorentz5Momentum> & p) {
    unsigned int ix,iy;
    for(ix=0;ix<p.size();++ix) {
      for(iy=0;iy<=ix;++ix) {
	_kine[ix][iy]=p[ix]*p[iy];
	_kine[iy][ix]=_kine[ix][iy];
      }
    }
  }

  /**
   * Get one of the kinematic invariants
   */
  Energy2 invariant(unsigned int ix ,unsigned int iy) {
    if(ix>_npoint||iy>_npoint)
      throw Exception() << "Invalid invariant requested in"
			<< " VertexBase::invariant() " 
			<< ix << " " << iy << Exception::abortnow;
    return _kine[ix][iy];
  }
  //@}
  
protected:
  
  /**
   * Set the name of the vertex to one of enumerated values.
   */
  void setName(const VertexType & name) { _theName = name; }

  /**
   * Set the order in \f$g_EM\f$
   * @param order The order of the vertex in \f$g_EM\f$
   */
  void orderInGem(unsigned int order) { _ordergEM = order; }

  /**
   * Set the order in \f$g_s\f$
   * @param order The order of the vertex in \f$g_s\f$
   */
  void orderInGs(unsigned int order) { _ordergS = order; }
  
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
  vector<long> _iparticlea;

  /**
   * PDG codes for the second set of  particles.
   */
  vector<long> _iparticleb;

  /**
   * PDG codes for the third set of  particles.
   */
  vector<long> _iparticlec;

  /**
   * PDG codes for the fourth set of  particles.
   */
  vector<long> _iparticled;

  /**
   * PDG codes for the fifth set of  particles.
   */
  vector<long> _iparticlee;

  /**
   *  Particles interacting at the vertex
   */
  vector<vector<tPDPtr> > _particles;

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
  vector<tPDPtr> _inpart;

  /**
   * PDG codes for the allowed incoming particles.
   */
  vector <long> _iinpart;

  /**
   * ParticleData pointers for the allowed outgoing particles.
   */
  vector<tPDPtr> _outpart;

  /**
   * PDG codes for the allowed outgoing particles.
   */
  vector <long> _ioutpart;
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
  vector<vector<Energy2> > _kine;

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

#endif /* ThePEG_VertexBase_H */
