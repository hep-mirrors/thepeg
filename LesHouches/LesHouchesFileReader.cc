// -*- C++ -*-
//
// LesHouchesFileReader.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LesHouchesFileReader class.
//

#include "LesHouchesFileReader.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Utilities/Throw.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

LesHouchesFileReader::
LesHouchesFileReader(const LesHouchesFileReader & x)
  : LesHouchesReader(x), neve(x.neve), ieve(0),
    LHFVersion(x.LHFVersion), outsideBlock(x.outsideBlock),
    headerBlock(x.headerBlock), initComments(x.initComments),
    initAttributes(x.initAttributes), eventComments(x.eventComments),
    eventAttributes(x.eventAttributes),
    theFileName(x.theFileName), theQNumbers(x.theQNumbers),
    theDecayer(x.theDecayer) {}

LesHouchesFileReader::~LesHouchesFileReader() {}

IBPtr LesHouchesFileReader::clone() const {
  return new_ptr(*this);
}

IBPtr LesHouchesFileReader::fullclone() const {
  return new_ptr(*this);
}

bool LesHouchesFileReader::preInitialize() const {
  return true;
}

void LesHouchesFileReader::doinit() {
  LesHouchesReader::doinit();
  // are we using QNUMBERS
  if(!theQNumbers) return;
  // parse the header block and create 
  // any new particles needed in QNUMBERS blocks
  string block = headerBlock;
  string line  = "";
  bool readingSLHA = false;
  int (*pf)(int) = tolower;
  unsigned int newNumber(0);
  do {
    line  = StringUtils::car(block,"\r\n");
    block = StringUtils::cdr(block,"\r\n");
    if(line[0]=='#') continue;
    // are we reading the SLHA block
    if(readingSLHA) {
      // reached the end of slha block ?
      if(line.find("</slha") != string::npos) {
	readingSLHA = false;
	break;
      }
      // remove trailing comment from line
      vector<string> split = StringUtils::split(line,"#");
      // check for a qnumbers block
      transform(split[0].begin(), split[0].end(), split[0].begin(), pf);
      // if not contine
      if(split[0].find("block qnumbers")==string::npos)
	continue;
      // get name from comment
      string name;
      if(split.size()>=2) {
	name = StringUtils::stripws(split[1]);
      }
      else {
	++newNumber;
	ostringstream tname;
	tname << "NP" << newNumber;
	name = tname.str();
      }
      // extract the PDG code
      split = StringUtils::split(split[0]," ");
      istringstream is(split[2]);
      long PDGCode(0);
      is >> PDGCode;
      // get the charge, spin, colour and whether an antiparticle
      int charge(0),spin(0),colour(0),anti(0);
      for(unsigned int ix=0;ix<4;++ix) {
	line = StringUtils::car(block,"\r\n");
	block = StringUtils::cdr(block,"\r\n");
	int dummy[2];
	istringstream is(line);
	is >> dummy[0] >> dummy[1];
	switch (dummy[0]) {
	case 1:
	  charge = dummy[1];
	  break;
	case 2:
	  spin   = dummy[1];
	  break;
	case 3:
	  colour = dummy[1];
	  break;
	case 4:
	  anti   = dummy[1];
	  break;
	default:
	  assert(false);
	}
      }
      // check if particles already exist
      PDPair newParticle;
      newParticle.first = getParticleData(PDGCode);
      if(newParticle.first) Throw<SetupException>()
			      << "Particle with PDG code " << PDGCode 
			      << " whose creation was requested in a QNUMBERS Block"
			      << " already exists. Retaining the original particle" 
			      << Exception::warning;
      if(anti) {
	newParticle.second = getParticleData(-PDGCode);
	if(newParticle.second) Throw<SetupException>()
				 << "Anti-particle with PDG code " << -PDGCode 
				 << " whose creation was requested in a QNUMBERS Block"
				 << " already exists. Retaining the original particle" 
				 << Exception::warning;
	if(( newParticle.first  && !newParticle.second ) ||
	   ( newParticle.second && !newParticle.first  ) )
	  Throw<SetupException>()
	    << "Either particle or anti-particle with PDG code " << PDGCode 
	    << " whose creation was requested in a QNUMBERS Block"
	    << " already exists, but not both the particle and antiparticle. "
	    << " Something dodgy here stopping" 
	    << Exception::runerror;
      }
      // already exists continue
      if(newParticle.first) continue;
      // create the particles
      // particle with no anti particle
      if( anti == 0 ) {
	// construct the name
	if(name=="") {
	  ostringstream temp;
	  temp << PDGCode;
	  name = temp.str(); 
	}
	// create the ParticleData object
	newParticle.first = ParticleData::Create(PDGCode,name);
      }
      // particle anti-particle pair
      else {
	// construct the names
	string nameAnti;
	if(name=="") {
	  ostringstream temp;
	  temp << PDGCode;
	  name = temp.str(); 
	  ostringstream temp2;
	  temp << -PDGCode;
	  nameAnti = temp2.str(); 
	}
	else {
	  nameAnti=name;
	  for(string::iterator it=nameAnti.begin();it!=nameAnti.end();++it) {
	    if(*it=='+')      nameAnti.replace(it,it+1,"-");
	    else if(*it=='-') nameAnti.replace(it,it+1,"+");
	  }
	  if(nameAnti==name) nameAnti += "bar";
	}
	// create the ParticleData objects
	newParticle = ParticleData::Create(PDGCode,name,nameAnti);
      }
      // set the particle properties
      if(colour==1) colour = 0;
      newParticle.first->iColour(PDT::Colour(colour));
      newParticle.first->iSpin  (PDT::Spin  (spin  ));
      newParticle.first->iCharge(PDT::Charge(charge));
      // register it
      generator()->preinitRegister(newParticle.first,
				   "/Herwig/Particles/"+newParticle.first->PDGName());
      // set the antiparticle properties
      if(newParticle.second) {
	if(colour==3||colour==6) colour *= -1;
	charge = -charge;
	newParticle.second->iColour(PDT::Colour(colour));
	newParticle.second->iSpin  (PDT::Spin  (spin  ));
	newParticle.second->iCharge(PDT::Charge(charge));
	// register it
	generator()->preinitRegister(newParticle.second,
				     "/Herwig/Particles/"+newParticle.second->PDGName());
      }
    }
    // start of SLHA block ?
    else if(line.find("<slha") != string::npos) {
      readingSLHA = true;
    }
  }
  while(line!="");
  // now set any masses/decay modes
  block = headerBlock;
  line="";
  readingSLHA=false;
  bool ok=true;
  do {
    line = StringUtils::car(block,"\r\n");
    block = StringUtils::cdr(block,"\r\n");
    // are we reading the SLHA block
    if(readingSLHA) {
      // reached the end?
      if(line.find("</slha") == 0 ) {
	readingSLHA = false;
	break;
      }
      // make lower case
      transform(line.begin(),line.end(),line.begin(), pf);
      // found the mass block ?
      if(line.find("block mass")!=string::npos) {
	// read it
	line = StringUtils::car(block,"\r\n");
	// check not at end
	while(line[0] != 'D' && line[0] != 'B' &&
	      line[0] != 'd' && line[0] != 'b' &&
	      line    != "") {
	  // skip comment lines
	  if(line[0] == '#') {
	    block = StringUtils::cdr(block,"\r\n");
	    line = StringUtils::car(block,"\r\n");
	    continue;
	  }
	  // get the mass and PGD code
	  istringstream temp(line);
	  long id;
	  double mass;
	  temp >> id >> mass;
	  // skip resetting masses on SM particles
	  // as it can cause problems later on in event generation
	  if(abs(id)<=6 || (abs(id)>=11 && abs(id)<=16) ||
	     abs(id)==23 || abs(id)==24) {
	    // Throw<SetupException>() << "Standard model mass for PID " 
	    // 			    << id
	    // 			    << " will not be changed."
	    // 			    << Exception::warning;
	    block = StringUtils::cdr(block,"\r\n");
	    line = StringUtils::car(block,"\r\n");
	    continue;
	  }
	  // magnitude of mass for susy models
	  mass = abs(mass);
	  // set the mass
	  tPDPtr particle = getParticleData(id);
	  if(!particle) throw SetupException() 
			  << "LesHouchesFileReader::doinit() - Particle with PDG code not"
			  << id << " not found." << Exception::runerror;
	  const InterfaceBase * ifb = BaseRepository::FindInterface(particle,
								    "NominalMass");
	  ostringstream os;
	  os << mass;
	  ifb->exec(*particle, "set", os.str());
	  // read the next line
	  block = StringUtils::cdr(block,"\r\n");
	  line = StringUtils::car(block,"\r\n");
	}; 
      }
      // found a decay block
      else if(line.find("decay") == 0) {
	// get PGD code and width
	istringstream iss(line);
	string dummy;
	long parent(0);
	Energy width(ZERO);
	iss >> dummy >> parent >> iunit(width, GeV);
	// get the ParticleData object
	PDPtr inpart = getParticleData(parent);
	if(!inpart)  {
	  throw SetupException() 
	    << "LesHouchesFileReader::doinit() - A ParticleData object with the PDG code "
	    << parent << " does not exist. " << Exception::runerror;
	  return;
	}
	if ( abs(inpart->id()) == 6 || 
	     abs(inpart->id()) == 15 || 
	     abs(inpart->id()) == 23 || 
	     abs(inpart->id()) == 24 || 
	     abs(inpart->id()) == 25 ) {
	  Throw<SetupException>() << "\n"
	    "************************************************************************\n"
	    "* Your LHE file changes the width of " << inpart->PDGName() << ".\n"
	    "* This can cause serious problems in the event generation!\n"
	    "************************************************************************\n"
	    "\n" << Exception::warning;
	}
	else if (inpart->width() > ZERO && width <= ZERO) {
	  Throw<SetupException>() << "\n"
	    "************************************************************************\n"
	    "* Your LHE file zeroes the non-zero width of " << inpart->PDGName() << ".\n"
	    "* If " << inpart->PDGName() << " is a decaying SM particle,\n"
	    "*     this can cause serious problems in the event generation!\n"
	    "************************************************************************\n"
				  "\n" << Exception::warning;
	}
	// set the width
	inpart->width(width);
	if( width > ZERO ) {
	  inpart->cTau(hbarc/width);
	  inpart->widthCut(5.*width);
	  inpart->stable(false);
	}
	// construct prefix for DecayModes
	string prefix(inpart->name() + "->"), tag(prefix),line("");
	unsigned int nmode(0);
	// read any decay modes
	line = StringUtils::car(block,"\r\n");
	while(line[0] != 'D' && line[0] != 'B' &&
	      line[0] != 'd' && line[0] != 'b' && 
	      line[0] != '<' && line    != "") {
	  // skip comments
	  if(line[0] == '#') {
	    block = StringUtils::cdr(block,"\r\n");
	    line = StringUtils::car(block,"\r\n");
	    continue;
	  }
	  // read decay mode and construct the tag
	  istringstream is(line);
	  double brat(0.);
	  unsigned int nda(0),npr(0);
	  is >> brat >> nda;
	  while( true ) {
	    long t;
	    is >> t;
	    if( is.fail() ) break; 
	    if( t == abs(parent) )
	      throw SetupException() 
		<< "An error occurred while read a decay of the " 
		<< inpart->PDGName() << ". One of its products has the same PDG code "
		<< "as the parent particle in LesHouchesFileReader::doinit()."
		<< " Please check the Les Houches file.\n"
		<< Exception::runerror;
	    tcPDPtr p = getParticleData(t);
	    if( !p )
	      throw SetupException()
		<< "LesHouchesFileReader::doinit() -"
		<< " An unknown PDG code has been encounterd "
		<< "while reading a decay mode. ID: " << t
		<< Exception::runerror;
	    ++npr;
	    tag += p->name() + ",";
	  }
	  if( npr != nda )
	    throw SetupException()
	      << "LesHouchesFileReader::doinit() - While reading a decay of the " 
	      << inpart->PDGName() << " from an SLHA file, an inconsistency "
	      << "between the number of decay products and the value in "
	      << "the 'NDA' column was found. Please check if the spectrum "
	      << "file is correct.\n"
	      << Exception::warning;
	  // create the DecayMode
	  if( npr > 1 ) {
	    if( nmode==0 ) {
	      generator()->preinitInterface(inpart, "VariableRatio" , "set","false");
	      if(inpart->massGenerator()) {
		ok = false;
		Throw<SetupException>()
		  << inpart->PDGName() << " already has a MassGenerator set"
		  << " this is incompatible with using QNUMBERS "
		  << "Use\n"
		  << "set " << inpart->fullName() << ":Mass_generator NULL\n"
		  << "to fix this." << Exception::warning;
	      }
	      if(inpart->widthGenerator()) {
		ok = false;
		Throw<SetupException>()
		  << inpart->PDGName() << " already has a WidthGenerator set"
		  << " this is incompatible with using QNUMBERS "
		  << "Use\n"
		  << "set " << inpart->fullName() << ":Width_generator NULL\n"
		  << "to fix this." << Exception::warning;
	      }
	      unsigned int ntemp=0;
	      for(DecaySet::const_iterator dit = inpart->decayModes().begin();
		  dit != inpart->decayModes().end(); ++dit ) {
		if((**dit).on()) ++ntemp;
	      }
	      if(ntemp!=0) {
		ok = false;
		Throw<SetupException>()
		  << inpart->PDGName() << " already has DecayModes"
		  << " this is incompatible with using QNUMBERS "
		  << "Use\n"
		  << "do " << inpart->fullName() << ":SelectDecayModes none\n" 
		  << " to fix this." << Exception::warning;
	      }
	    }
	    inpart->stable(false);
	    tag.replace(tag.size() - 1, 1, ";");
	    DMPtr dm = generator()->findDecayMode(tag);
	    if(!theDecayer) Throw<SetupException>()
			      << "LesHouchesFileReader::doinit() Decayer must be set using the "
			      << "LesHouchesFileReader:Decayer"
			      << " must be set to allow the creation of new"
			      << " decay modes."
			      << Exception::runerror;
	    if(!dm) {
	      dm = generator()->preinitCreateDecayMode(tag);
	      if(!dm)
		Throw<SetupException>()  
		  << "LesHouchesFileReader::doinit() - Needed to create "
		  << "new decaymode but one could not be created for the tag " 
		  << tag << Exception::warning;
	    }
	    generator()->preinitInterface(dm, "Decayer", "set",
					  theDecayer->fullName());
	    ostringstream br;
	    br << setprecision(13) << brat;
	    generator()->preinitInterface(dm, "BranchingRatio", "set", br.str());
	    generator()->preinitInterface(dm, "OnOff", "set", "On");
	    if(dm->CC()) {
	      generator()->preinitInterface(dm->CC(), "BranchingRatio", "set", br.str());
	      generator()->preinitInterface(dm->CC(), "OnOff", "set", "On");
	    }
	    ++nmode;
	  }
	  tag=prefix;
	  // read the next line
	  block = StringUtils::cdr(block,"\r\n");
	  line = StringUtils::car(block,"\r\n");
	};
	if(nmode>0) {
	  inpart->update();
	  if(inpart->CC())
	    inpart->CC()->update();
	}
      }
    }
    // start of SLHA block ?
    else if(line.find("<slha") != string::npos) {
      readingSLHA = true;
    }
  }
  while(line!="");
  if(!ok)
    throw SetupException() << "Problem reading QNUMBERS blocks in LesHouchesFileReader::doinit()"
			   << Exception::runerror;
}

void LesHouchesFileReader::initialize(LesHouchesEventHandler & eh) {
  LesHouchesReader::initialize(eh);
  if ( LHFVersion.empty() )
    Throw<LesHouchesFileError>()
      << "The file associated with '" << name() << "' does not contain a "
      << "proper formatted Les Houches event file. The events may not be "
      << "properly sampled." << Exception::warning;
}

void LesHouchesFileReader::open() {
  if ( filename().empty() )
    throw LesHouchesFileError()
      << "No Les Houches file name. "
      << "Use 'set " << name() << ":FileName'."
      << Exception::runerror;
  cfile.open(filename());
  if ( !cfile )
    throw LesHouchesFileError()
      << "The LesHouchesFileReader '" << name() << "' could not open the "
      << "event file called '" << theFileName << "'."
      << Exception::runerror;

  cfile.readline();
  if ( !cfile.find("<LesHouchesEvents") ) return;
  map<string,string> attributes =
    StringUtils::xmlAttributes("LesHouchesEvents", cfile.getline());
  LHFVersion = attributes["version"];
  if ( LHFVersion.empty() ) return;

  bool readingHeader = false;
  bool readingInit = false;
  headerBlock = "";

  // Loop over all lines until we hit the </init> tag.
  while ( cfile.readline() && !cfile.find("</init>") ) {
    if ( cfile.find("<header") ) {
      // We have hit the header block, so we should dump this and all
      // following lines to headerBlock until we hit the end of it.
      readingHeader = true;
      headerBlock = cfile.getline() + "\n";
    }
    else if ( cfile.find("<init ") || cfile.find("<init>") ) {
      // We have hit the init block, so we should expect to find the
      // standard information in the following. But first check for
      // attributes.
      initAttributes = StringUtils::xmlAttributes("init", cfile.getline());
      readingInit = true;
      cfile.readline();
      if ( !( cfile >> heprup.IDBMUP.first >> heprup.IDBMUP.second
		    >> heprup.EBMUP.first >> heprup.EBMUP.second
	            >> heprup.PDFGUP.first >> heprup.PDFGUP.second
	            >> heprup.PDFSUP.first >> heprup.PDFSUP.second
		    >> heprup.IDWTUP >> heprup.NPRUP ) ) {
	heprup.NPRUP = -42;
	LHFVersion = "";
	return;
      }
      heprup.resize();

      for ( int i = 0; i < heprup.NPRUP; ++i ) {
	cfile.readline();
	if ( !( cfile >> heprup.XSECUP[i] >> heprup.XERRUP[i]
	              >> heprup.XMAXUP[i] >> heprup.LPRUP[i] ) ) {
	  heprup.NPRUP = -42;
	  LHFVersion = "";
	  return;
	}
      }
    }
    else if ( cfile.find("</header") ) {
      readingHeader = false;
      headerBlock += cfile.getline() + "\n";
    }
    else if ( readingHeader ) {
      // We are in the process of reading the header block. Dump the
	// line to headerBlock.
      headerBlock += cfile.getline() + "\n";
    }
    else if ( readingInit ) {
      // Here we found a comment line. Dump it to initComments.
      initComments += cfile.getline() + "\n";
    }
    else {
      // We found some other stuff outside the standard tags.
      outsideBlock += cfile.getline() + "\n";
    }
  }
  if ( !cfile ) {
    heprup.NPRUP = -42;
    LHFVersion = "";
    return;
  }

}

bool LesHouchesFileReader::doReadEvent() {
  if ( !cfile ) return false;
  if ( LHFVersion.empty() ) return false;
  if ( heprup.NPRUP < 0 ) return false;
  eventComments = "";
  outsideBlock = "";
  hepeup.NUP = 0;
  hepeup.XPDWUP.first = hepeup.XPDWUP.second = 0.0;

  // Keep reading lines until we hit the next event or the end of
  // the event block. Save any inbetween lines. Exit if we didn't
  // find an event.
  while ( cfile.readline() && !cfile.find("<event") )
    outsideBlock += cfile.getline() + "\n";

  // We found an event. First scan for attributes.
  eventAttributes = StringUtils::xmlAttributes("event", cfile.getline());
  if ( !cfile.readline()  ) return false;

  // The first line determines how many subsequent particle lines we
  // have.
  if ( !( cfile >> hepeup.NUP >> hepeup.IDPRUP >> hepeup.XWGTUP
	        >> hepeup.SCALUP >> hepeup.AQEDUP >> hepeup.AQCDUP ) )
    return false;
  hepeup.resize();
  // Read all particle lines.
  for ( int i = 0; i < hepeup.NUP; ++i ) {
    if ( !cfile.readline() ) return false;
    if ( !( cfile >> hepeup.IDUP[i] >> hepeup.ISTUP[i]
	          >> hepeup.MOTHUP[i].first >> hepeup.MOTHUP[i].second
         	  >> hepeup.ICOLUP[i].first >> hepeup.ICOLUP[i].second
	          >> hepeup.PUP[i][0] >> hepeup.PUP[i][1] >> hepeup.PUP[i][2]
	          >> hepeup.PUP[i][3] >> hepeup.PUP[i][4]
        	  >> hepeup.VTIMUP[i] >> hepeup.SPINUP[i] ) )
      return false;
    if(isnan(hepeup.PUP[i][0])||isnan(hepeup.PUP[i][1])||
       isnan(hepeup.PUP[i][2])||isnan(hepeup.PUP[i][3])||
       isnan(hepeup.PUP[i][4])) 
      throw Exception() 
	<< "nan's as momenta in Les Houches file "
	<< Exception::eventerror;
    if(hepeup.MOTHUP[i].first -1==i || 
       hepeup.MOTHUP[i].second-1==i) {
      throw Exception()
	<< "Particle has itself as a mother in Les Houches "
	<< "file, this is not allowed\n"
	<< Exception::eventerror;
    } 
  }

  // Now read any additional comments and named weights.
  optionalWeights.clear();
  while ( cfile.readline() && !cfile.find("</event>") ) {
    // parse weightinfo elements
    if ( cfile.find("<weightinfo") ) {
      map<string,string> weightAttributes =
	StringUtils::xmlAttributes("weightinfo",cfile.getline());
      if ( !cfile.readline() ) return false;
      double weightValue; cfile >> weightValue;
      if ( !cfile.readline() ) return false;
      if ( !cfile.find("</weightinfo>") ) {
	throw LesHouchesFileError()
	  << "error while parsing weight information in "
	  << theFileName << Exception::eventerror;
      }
      // ignore the single unnamed weight, but warn if multiple of the
      // same name
      map<string,string>::const_iterator weightName = weightAttributes.find("name");
      if ( weightName != weightAttributes.end() ) {
	map<string,double>::iterator wit =
	  optionalWeights.find(weightName->second);
	if ( wit == optionalWeights.end() ) {
	  optionalWeights[weightName->second] = weightValue;
	} else {
	  throw LesHouchesFileError()
	    << "multiple weights of the same name in "
	    << theFileName << Exception::eventerror;
	}
      }
      continue;
    }
    eventComments += cfile.getline() + "\n";
  }

  if ( !cfile ) return false;
  return true;

}

void LesHouchesFileReader::close() {
  cfile.close();
}

void LesHouchesFileReader::persistentOutput(PersistentOStream & os) const {
  os << neve << LHFVersion << outsideBlock << headerBlock << initComments
     << initAttributes << eventComments << eventAttributes << theFileName
     << theQNumbers << theDecayer;
}

void LesHouchesFileReader::persistentInput(PersistentIStream & is, int) {
  is >> neve >> LHFVersion >> outsideBlock >> headerBlock >> initComments
     >> initAttributes >> eventComments >> eventAttributes >> theFileName
     >> theQNumbers >> theDecayer;
  ieve = 0;
}

ClassDescription<LesHouchesFileReader>
LesHouchesFileReader::initLesHouchesFileReader;
// Definition of the static class description member.

void LesHouchesFileReader::Init() {

  static ClassDocumentation<LesHouchesFileReader> documentation
    ("ThePEG::LesHouchesFileReader is an base class to be used for objects "
     "which reads event files from matrix element generators. This class is "
     "able to read plain event files conforming to the Les Houches Event File "
     "accord.");

  static Parameter<LesHouchesFileReader,string> interfaceFileName
    ("FileName",
     "The name of a file containing events conforming to the Les Houches "
     "protocol to be read into ThePEG. A file name ending in "
     "<code>.gz</code> will be read from a pipe which uses "
     "<code>zcat</code>. If a file name ends in <code>|</code> the "
     "preceeding string is interpreted as a command, the output of which "
     "will be read through a pipe.",
     &LesHouchesFileReader::theFileName, "", false, false);

  interfaceFileName.fileType();
  interfaceFileName.rank(11);

  static Switch<LesHouchesFileReader,bool> interfaceQNumbers
    ("QNumbers",
     "Whether or not to read search for and read a QNUMBERS"
     " block in the header of the file.",
     &LesHouchesFileReader::theQNumbers, false, false, false);
  static SwitchOption interfaceQNumbersYes
    (interfaceQNumbers,
     "Yes",
     "Use QNUMBERS",
     true);
  static SwitchOption interfaceQNumbersNo
    (interfaceQNumbers,
     "No",
     "Don't use QNUMBERS",
     false);

  static Reference<LesHouchesFileReader,Decayer> interfaceDecayer
    ("Decayer",
     "Decayer to use for any decays read from the QNUMBERS Blocks",
     &LesHouchesFileReader::theDecayer, false, false, true, true, false);

}

