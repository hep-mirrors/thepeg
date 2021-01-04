// -*- C++ -*-
//
// HepMCReader.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2020 Julian Lukwata
//
// ThePEG is licenced under version 3 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the HepMCReader class.
//

/* #ifndef HAVE_HEPMC3 */
/* #define HAVE_HEPMC3 1 */
/* #endif */

#include "HepMCReader.h"
#include "HepMCEventHandler.h"
#ifdef HAVE_HEPMC3
#include "HepMC3/ReaderAscii.h"
#include "HepMC3/ReaderAsciiHepMC2.h"
#include "HepMC3/GenEvent.h"
#include "HepMC3/GenParticle.h"
#include "HepMC3/GenVertex.h"
#include "HepMC3/FourVector.h"
#include "HepMC3/Attribute.h"
#else
#include "HepMC/IO_GenEvent.h"
#include "HepMC/GenEvent.h"
#include "HepMC/SimpeVector.h"
#endif


/* #include "ThePEG/Handlers/HandlerBase.h" */

#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Reference.h"

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

/* #include "ThePEG/EventRecord/Event.h" */
/* #include "ThePEG/PDF/NoPDF.h" */
/* #include "ThePEG/PDF/BeamParticleData.h" */
#include "ThePEG/PDF/RemnantHandler.h"
#include "ThePEG/PDF/PartonExtractor.h"
#include "ThePEG/PDF/PartonBin.h"
#include "ThePEG/Handlers/CascadeHandler.h"
#include "ThePEG/Cuts/Cuts.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Utilities/Throw.h"
/* #include "ThePEG/Utilities/HoldFlag.h" */
/* #include "ThePEG/Utilities/Debug.h" */
#include <iostream>
#include <iomanip>


using namespace ThePEG;

HepMCReader::HepMCReader()
  : _eventNumber(1), _format(1), _filename(),
  _unitchoice(), _event() {}

  // Cannot copy streams.
  // Let doinitrun() take care of their initialization.
HepMCReader::HepMCReader(const HepMCReader & x)
  : HandlerBase(x), LastXCombInfo<>(x),
  _eventNumber(x._eventNumber), _format(x._format), _filename(x._filename),
  _hepmcin(x._hepmcin), _unitchoice(x._unitchoice), _event(x._event),
  thePartonExtractor(x.thePartonExtractor), theCKKW(x.theCKKW),
  thePartonBins(x.thePartonBins), theXComb(x.theXComb), theCuts(x.theCuts),
  theIncoming(x.theIncoming), theOutgoing(x.theOutgoing) {}


HepMCReader::~HepMCReader() {}

IBPtr HepMCReader::fullclone() const {
  return new_ptr(*this);
}

IBPtr HepMCReader::clone() const {
  return new_ptr(*this);
}


void HepMCReader::doinitrun() {
  HandlerBase::doinitrun();
  // TODO: What does emax do
  Energy emax = 100.0*GeV;

  /* PDPair inData = make_pair(getParticleData(2212), getParticleData(2212)); */

  // partonBins() is not implemented
  /* thePartonBins = partonExtractor()->getPartons(emax, inData, cuts()); */
  PDFCuts cuts1(cuts(), true, emax);
  PBPair partonPair(
      new_ptr(PartonBin(PDPtr(), PBPtr(), inData.first,  PDFPtr(), cuts1)),
      new_ptr(PartonBin(PDPtr(), PBPtr(), inData.second, PDFPtr(), cuts1)));
  PBIPair partonBIPair(
      new_ptr(PartonBinInstance(partonPair.first)),
      new_ptr(PartonBinInstance(partonPair.second)));
  xComb()->resetPartonBinInstances(partonBIPair);

  /* std::cout << "Size of PartonBins: " << partonBins().size() << std::endl; */
  /* theXComb = new_ptr(XComb(emax, inData, &eh, partonExtractor(), CKKWHandler(), */
  /*       partonBins()[50], theCuts)); */

  if ( _filename.empty() ) Throw<HepMCInitError>()
      << "No Filename for HepMC file was set." << Exception::runerror;
#ifdef HAVE_HEPMC3
  // create event to store stuff
  /* _event  = new HepMC3::GenEvent(); */
#endif

  switch(_format){
    default:
    case 1: {
#ifdef HAVE_HEPMC3
              _hepmcin = new HepMC3::ReaderAsciiHepMC2(_filename.c_str());
              // set reader option to correctly read flow
              std::map< std::string, std::string > read_opt;
              read_opt["particle_flows_are_separated"] = "1";
              _hepmcin->set_options(read_opt);
#else
              _hepmcin = new HepMC::IO_GenEvent(_filename.c_str(), std::ios::in);
#endif

            }
            break;
#ifdef HAVE_HEPMC3
    case 2: {
              _hepmcin = new HepMC3::ReaderAscii(_filename.c_str());
            }
#endif
  }
  _eventNumber = 0;
}

void HepMCReader::dofinish() {
#ifdef HAVE_HEPMC3
  _hepmcin->close();
  std::cout << "Closing AsciiReader.\n";
  /* delete _event; */
#else
  if (_hepmcin) {
    delete _hepmcin;
    _hepmcin = 0;
  }
#endif
  HandlerBase::dofinish();
  std::cout << "\nHepMCReader: read HepMC input.\n";
}

bool HepMCReader::doReadEvent() {
#ifdef HAVE_HEPMC3
  _event = std::make_shared<HepMC3::GenEvent>();
  _hepmcin->read_event(*_event);
#else
  _event = _hepmcin->read_next_event();
#endif
  // check if new evt was read
  if ( !event() ) {
    std::cout << "could not read event apparantly." << std::endl;
    return false;
  }

  return true;
}

void HepMCReader::initialize(HepMCEventHandler & eh) {

  if ( !theCuts ) {
    theCuts = eh.cuts();
    if ( !theCuts ) Throw<HepMCInitError>()
      << "No Cuts object was assigned to the HepMCReader '"
      << name() << "' nor was one\nassigned to the controlling "
      << "HepMCEventHandler '" << eh.name() << "'.\nAt least one of them "
      << "needs to have a Cuts object." << Exception::runerror;
  }

  theCKKW = eh.CKKWHandler();

  if ( !partonExtractor() ) {
    thePartonExtractor = eh.partonExtractor();
    if ( !partonExtractor() )  Throw<HepMCInitError>()
      << "No PartonExtractor object was assigned to the HepMCReader '"
      << name() << "' nor was one\nassigned to the controlling "
      << "HepMCEventHandler '" << eh.name() << "'.\nAt least one of them "
      << "needs to have a PartonExtractor object." << Exception::runerror;
  }
  double E_double = 100.0;
  Energy emax = E_double*GeV;
  // TODO: just a work around
  // set incoming particles fixed to protons
  PDPair inData = make_pair(getParticleData(2212), getParticleData(2212));
  // partonBins() is not implemented
  thePartonBins = partonExtractor()->getPartons(emax, inData, cuts());
  /* PDFCuts cuts1(cuts(), true, emax); */
  /* PBPair partonPair( */
  /*     new_ptr(PartonBin(PDPtr(), PBPtr(), inData.first,  PDFPtr(), cuts1)), */
  /*     new_ptr(PartonBin(PDPtr(), PBPtr(), inData.second, PDFPtr(), cuts1))); */

  /* for ( int i = 0, N = partonBins().size(); i < N; ++i ) { */
  /*   theXCombs[partonBins()[i]] = */
  /*     new_ptr(XComb(emax, inData, &eh, partonExtractor(), CKKWHandler(), */
  /*                   partonBins()[i], theCuts)); */
  /*   partonExtractor()->nDims(partonBins()[i]); */
  /* } */
  /* outPDF = make_pair(partonExtractor()->getPDF(inData.first), */
  /*                    partonExtractor()->getPDF(inData.second)); */

  /* std::cout << "Size of PartonBins: " << partonBins().size() << std::endl; */
  theXComb = new_ptr(XComb(emax, inData, &eh, partonExtractor(), CKKWHandler(),
        partonBins()[1],
        /* partonPair, */
        /* PBPair(new PartonBin(), new PartonBin()), */
        theCuts));
  /* theXComb = tXCombPtr(); */
  /* partonExtractor()->nDims(partonBins()[50]); */
  /* if(!xComb()->empty()) std::cout << "LastXComb is not empty." << std::endl; */
  /* std::cout << "the Max energy is : " << lastXCombPtr()->maxEnergy() << std::endl; */
  /* theXComb = new_ptr(XComb()); */
  /* _event = NULL; */

}

bool HepMCReader::readEvent() {

  reset();

  if ( !doReadEvent() ) return false;

  fillEvent();

  return true;
}

tXCombPtr HepMCReader::getXComb() {
  if ( lastXCombPtr() ) return lastXCombPtr();
  fillEvent();
  connectMothers();
  //TODO: not implemented
  /* tcPBPair sel = createPartonBinInstances(); */
  // set parton bin instances
  thePartonBinInstances.first =
    new_ptr(PartonBinInstance(incoming().first, partonBins()[0].first,
                              _e_scale));
  thePartonBinInstances.second =
    new_ptr(PartonBinInstance(incoming().second, partonBins()[0].second,
                              _e_scale));
  /* PPair lastParts = PPair(incoming()[0], incoming()[1]); */
  tXCombPtr lastXC = xComb();
  // use default constructor
  /* tXCombPtr lastXC = new_ptr(XComb()); */
  /* lastXC-lastParticles(lastParts); */
  // clean up the old XComb object before switching to a new one
  if ( theLastXComb && theLastXComb != lastXC )
    theLastXComb->clean();
  theLastXComb = lastXC;
  lastXCombPtr()->subProcess(SubProPtr());
  lastXCombPtr()->setPartonBinInstances(partonBinInstances(),
                                        _e_scale);
  /* if( !xComb()->empty()) std::cout << "xComb is not empyt." << std::endl; */

#ifdef HAVE_HEPMC3
  std::shared_ptr<HepMC3::DoubleAttribute> A_QCD = event()->attribute<HepMC3::DoubleAttribute>("alphaQCD");
  std::shared_ptr<HepMC3::DoubleAttribute> A_EM = event()->attribute<HepMC3::DoubleAttribute>("alphaEM");
  double a_QCD =A_QCD?(A_QCD->value()):0.0;
  double a_EM = A_EM?(A_EM->value()):0.0;
#else
  double a_QCD = event()->alphaQCD();
  double a_EM = event()->alphaQED();
#endif
  lastXCombPtr()->lastAlphaS(a_QCD);
  lastXCombPtr()->lastAlphaEM(a_EM);

  return lastXCombPtr();
}

tSubProPtr HepMCReader::getSubProcess() {
  getXComb();
  if ( subProcess() ) return subProcess();
  //TODO: Don't have lastPartons
  lastXCombPtr()->subProcess(new_ptr(SubProcess(lastPartons(), tCollPtr(), this)));
  subProcess()->setOutgoing(outgoing().begin(), outgoing().end());
  subProcess()->setIntermediates(intermediates().begin(),
                                 intermediates().end());
  return subProcess();
}

void HepMCReader::fillEvent() {
  if ( !particleIndex.empty() ) return;
  // read eventNumber
  _eventNumber = event()->event_number();
#ifdef HAVE_HEPMC3
  std::shared_ptr<HepMC3::DoubleAttribute> E_scale = event()->attribute<HepMC3::DoubleAttribute>("event_scale");
  _e_scale = E_scale?(E_scale->value())*GeV2:0.0*GeV2;
#else
  _e_scale = event()->event_scale()*GeV2;
#endif
  //create particles
  particleIndex.clear();
  colourIndex.clear();
  colourIndex(0, tColinePtr());
  // own functions
  createParticles();
  //TODO: not implementes yet, don't know if needed
  /* createBeams(); */
}

void HepMCReader::reset() {
  particleIndex.clear();
  colourIndex.clear();
  if ( theLastXComb ) theLastXComb->clean();
  theLastXComb = tXCombPtr();
  /* delete _event; */
  if ( _eventNumber > 0 ) {
    /* std::cout << "Clear event " << event()->event_number() */
    /*   << "." << std::endl; */
#ifdef HAVE_HEPMC3
    _event->clear();
#else
    delete _event;
#endif
    _eventNumber = -1;
  }
}

void HepMCReader::createParticles() {
  theBeams = PPair();
  /* PDPair incoming; */
  /* incoming =  make_pair(getParticleData(2212), getParticleData(2212)); */
  theIncoming = PPair();
  /* theBeams = PVector(); */
  /* theIncoming = PVector(); */

  /* incoming.first = getParticleData(2212); */
  /* incoming.second = getParticleData(2212); */

  /* theIncoming = incoming; */
  theOutgoing = PVector();
  theIntermediates = PVector();

  // to store the momentum
  double x, y, z, t;

#ifdef HAVE_HEPMC3
  for(auto part: event()->particles()) {
    const HepMC3::FourVector partMom = part->momentum();
#else
  for( HepMC::GenEvent::particle_const_iterator pci = event()->particles_begin();
      pci != event()->particles_end(); ++pci ){
    HepMC::GenParticle * part = (*pci);
    const HepMC::FourVector partMom = (*pci)->momentum();
#endif

    x = partMom.px();
    y = partMom.py();
    z = partMom.pz();
    t = partMom.e();

    Lorentz5Momentum mom(x*GeV, y*GeV, z*GeV, t*GeV);

    PDPtr pd = getParticleData(part->pdg_id());

    PPtr p = pd->produceParticle(mom);

#ifdef HAVE_HEPMC3
    tColinePtr c;

    std::shared_ptr<HepMC3::IntAttribute> Flow1(part->attribute<HepMC3::IntAttribute>("flow1"));
    std::shared_ptr<HepMC3::IntAttribute> Flow2(part->attribute<HepMC3::IntAttribute>("flow2"));
    if(Flow1) {
      c = colourIndex(Flow1->value());
      c->addColoured(p);
    }
    if(Flow2){
      c = colourIndex(Flow2->value());
      c->addAntiColoured(p);
    }

    // use id as identifier
    particleIndex(part->id(), p);
#else
    const HepMC::Flow * flow = &(*pci)->flow();

    tColinePtr c = colourIndex(flow->icode(1));
    if ( c ) {
      c->addColoured(p);
    }
    c = colourIndex(flow->icode(2));
    if ( c ) {
      c->addAntiColoured(p);
    }
    // use barcode as identifier
    particleIndex(part->barcode(), p);
#endif

    /* const ObjectIndexer<long,Particle> & part_i = particleIndex; */
    // copy status
    switch (part->status() ) {
      // incoming beam particle
      // TODO: use the first two particles as incoming particles
      case 4: {
#ifdef HAVE_HEPMC3
                HepMC3::ConstGenVertexPtr ver = part->end_vertex();
                if(ver) {
                  x = ver->data().position.x();
                  y = ver->data().position.y();
                  z = ver->data().position.z();
                  t = ver->data().position.t();

                  //  hope it is in mm
                  p->setVertex(LorentzPoint(x*mm, y*mm, z*mm, t*mm));

                }
#else
                HepMC::GenVertex *ver = part->end_vertex();

                if ( ver ) {
                  /* std::cout << "Particle status " << part->status() << std::endl; */
                  /* std::cout << "x: " << std::scientific << ver->position().x() << std::endl; */
                  /* std::cout << "y: " << ver->position().y() << std::endl; */
                  /* std::cout << "z: " << ver->position().z() << std::endl; */
                  x = ver->position().x();
                  y = ver->position().y();
                  z = ver->position().z();
                  t = ver->position().t();
                  //  hope it is in mm
                  LorentzPoint pos(x*mm, y*mm, z*mm, t*mm);
                  // set vertex position
                  p->setVertex(pos);
                }
#endif
                if( !theIncoming.first ) {
                  theBeams.first = p;
                  theIncoming.first = p;
                }
                else if ( !theIncoming.second ) {
                  theBeams.second = p;
                  theIncoming.second = p;
                }
                else  Throw<HepMCInconsistencyError>()
                  << "To many incoming particles." << Exception::warning;
                break;
              }
      //outgoing finalstate particle
      case 1:
        theOutgoing.push_back(p);
        /* p->scale(sqr(hepeup.SCALUP*GeV)); */
        break;
      // intermediate particle
      case 11:
      // decaying particles
      case 2:
        theIntermediates.push_back(p);
        break;
      default:
      Throw<HepMCInconsistencyError>()
        << "Unknown status code (" << part->status()
        << ") in the HepMCReader '" << name() << "'."
        << Exception::runerror;
    }
  }
}

/* void HepMCReader::createBeams() { */
/*   //TODO: Maybe not needed */
/* } */

void HepMCReader::connectMothers() {
  const ObjectIndexer<long,Particle> & pi = particleIndex;
  /* double test */
  double x, y, z, t;

#ifdef HAVE_HEPMC3
  for(auto part: event()->particles()) {
    /* std::cout << "Hallo." << std::endl; */
    HepMC3::ConstGenVertexPtr ver = part->production_vertex();
    // set position of production vertex
    /* x = y = z = t = 0.0; */

    if( ver ){
      x = ver->data().position.x();
      y = ver->data().position.y();
      z = ver->data().position.z();
      t = ver->data().position.t();

      //  hope it is in mm
      LorentzPoint pos(x*mm, y*mm, z*mm, t*mm);
      // set vertex position
      if(part->status() != 4)
        pi(part->id())->setVertex(pos);

      for(auto part_in: ver->particles_in()) {
        pi(part_in->id())->addChild(pi(part->id()));
      }
    }
#else
  for( HepMC::GenEvent::particle_const_iterator pci = event()->particles_begin();
      pci != event()->particles_end(); ++pci ){
    HepMC::GenVertex *ver = (*pci)->production_vertex();

    if ( ver ) {
      x = ver->position().x();
      y = ver->position().y();
      z = ver->position().z();
      t = ver->position().t();
      //  hope it is in mm
      LorentzPoint pos(x*mm, y*mm, z*mm, t*mm);
      // set vertex position
      if((*pci)->status() != 4)
        pi((*pci)->barcode())->setVertex(pos);

      for(HepMC::GenVertex::particles_in_const_iterator pici = ver->particles_in_const_begin();
          pici != ver->particles_in_const_end(); ++pici ){
        pi((*pici)->barcode())->addChild(pi((*pci)->barcode()));
      }
    }
#endif
  }
}

void HepMCReader::persistentOutput(PersistentOStream & os) const {
  os << _eventNumber << _format << _filename
    << _unitchoice << theCuts
    /* << _emax */
    << E_double
    << theCKKW
    << inData
    << thePartonBins
    << theXComb
    << theIncoming << theOutgoing
    /* << theLastXComb ; */
    << thePartonExtractor;
}

void HepMCReader::persistentInput(PersistentIStream & is, int) {
  is >> _eventNumber >> _format >> _filename
    >> _unitchoice >> theCuts
    /* >> _emax */
    >> E_double
    >> theCKKW
    >> inData
    >> thePartonBins
    >> theXComb
    >> theIncoming >> theOutgoing
  /*   >> theLastXComb ; */
    >> thePartonExtractor;
}

ClassDescription<HepMCReader> HepMCReader::initHepMCReader;
// Definition of the static class description member.

void HepMCReader::Init() {

  static ClassDocumentation<HepMCReader> documentation
    ("This event handler will read the event record from HepMC format.");

  static Parameter<HepMCReader,string> interfaceFilename
    ("Filename", "Name of the input file",
     &HepMCReader::_filename, "");

  //TODO: Unit choice should be in input file
  static Switch<HepMCReader,int> interfaceUnits
    ("Units",
     "Unit choice for energy and length",
     &HepMCReader::_unitchoice, 0, false, false);
  static SwitchOption interfaceUnitsGeV_mm
    (interfaceUnits,
     "GeV_mm",
     "Use GeV and mm as units.",
     0);
  static SwitchOption interfaceUnitsMeV_mm
    (interfaceUnits,
     "MeV_mm",
     "Use MeV and mm as units.",
     1);
  static SwitchOption interfaceUnitsGeV_cm
    (interfaceUnits,
     "GeV_cm",
     "Use GeV and cm as units.",
     2);
  static SwitchOption interfaceUnitsMeV_cm
    (interfaceUnits,
     "MeV_cm",
     "Use MeV and cm as units.",
     3);

  static Reference<HepMCReader,Cuts> interfaceCuts
    ("Cuts",
     "The Cuts object to be used for this reader. Note that these "
     "must not be looser cuts than those used in the actual generation. "
     "If no object is provided the HepMCEventHandler object must "
     "provide one instead.",
     &HepMCReader::theCuts, true, false, true, true, false);

  static Switch<HepMCReader,int> interfaceFormat
    ("Format",
#ifdef HAVE_HEPMC3
     "Input format (1 = GenEvent,  2 = GenEventHepMC3",
#else
     "Input format (1 = GenEvent",
#endif
     &HepMCReader::_format, 1, false, false);
  static SwitchOption interfaceFormatGenEvent
    (interfaceFormat,
     "GenEvent",
     "IO_GenEvent format",
     1);
  static SwitchOption interfaceFormatGenEventHepMC3
    (interfaceFormat,
     "GenEventHepMC3",
     "GenEvent in HepMC3",
     2);

  interfaceCuts.rank(8);

}
