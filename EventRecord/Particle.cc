// -*- C++ -*-
//
// This is the implementation of the non-inlined member functions of
// the Particle class.
//
#include "Particle.h"
#include "ThePEG/EventRecord/Step.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/EventRecord/ColourLine.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/Config/algorithm.h"
#include "ThePEG/EventRecord/ParticleTraits.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/DecayMode.h"
#include <iostream>
#include <iomanip>
#include <cctype>

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "Particle.tcc"
#endif

using namespace ThePEG;

Particle::ParticleRep::ParticleRep()
  : theScale(-1.0*GeV2), theNumber(0) {}

Particle::ParticleRep::ParticleRep(const ParticleRep & p)
  : theParents(p.theParents), theChildren(p.theChildren),
    thePrevious(p.thePrevious), theNext(p.theNext),
    theBirthStep(p.theBirthStep), theVertex(p.theVertex),
    theLifeLength(p.theLifeLength), theScale(p.theScale),
    theNumber(p.theNumber), theExtraInfo(p.theExtraInfo.size()) {
  if ( p.theColourInfo )
    theColourInfo = dynamic_ptr_cast<CBPtr>(p.theColourInfo->clone());
  if ( theSpinInfo )
    theSpinInfo = dynamic_ptr_cast<SpinPtr>(p.theSpinInfo->clone());
  for ( int i = 0, N = p.theExtraInfo.size(); i < N; ++i )
    theExtraInfo[i] = p.theExtraInfo[i]->clone();
}

Particle::Particle(const Particle & p)
  : theData(p.theData), theMomentum(p.theMomentum), theRep(p.theRep) {
  if ( p.theRep ) theRep = new ParticleRep(*p.theRep);
}

void Particle::initFull() const {
  if ( theRep ) return;
  theRep = new ParticleRep;
  theRep->theLifeLength.setMass
    (data().generateLifeTime(mass(), data().generateWidth(mass())));
  theRep->theLifeLength.setVect((const LorentzMomentum &)
    (momentum()*(lifeTime()/max(mass(), Constants::epsilon*GeV))));
}

PPtr Particle::clone() const {
  return ptr_new<PPtr>(*this);
}

void Particle::rebind(const EventTranslationMap & trans) {
  for ( ParticleVector::iterator pit = rep().theChildren.begin();
	pit != rep().theChildren.end(); ++pit ) *pit = trans.translate(*pit);
  for ( tParticleVector::iterator pit = rep().theParents.begin();
	pit != rep().theParents.end(); ++pit ) *pit = trans.translate(*pit);
  rep().thePrevious = trans.translate(rep().thePrevious);
  rep().theNext = trans.translate(rep().theNext);
  if ( hasColourInfo() ) colourInfo()->rebind(trans);
  if ( spinInfo() ) spinInfo()->rebind(trans);
  rep().theBirthStep = trans.translate(rep().theBirthStep);
  for ( EIVector::const_iterator ie = rep().theExtraInfo.begin();
	ie != rep().theExtraInfo.end(); ++ie ) (**ie).rebind(trans);
}

tParticleSet Particle::siblings() const {
  tParticleSet theSiblings;
  for ( tParticleVector::const_iterator pit = parents().begin();
	pit != parents().end(); ++pit )
    theSiblings.insert((*pit)->children().begin(), (*pit)->children().end());
  theSiblings.erase(const_cast<Particle *>(this));
  return theSiblings;
}

tPPtr Particle::colourNeighbour(bool anti) const {
  return hasColourInfo() && hasColour(!anti) && birthStep()?
    birthStep()->colourNeighbour(this, anti): tPPtr();
}

void Particle::colourNeighbour(tPPtr p, bool anti) {
  tColinePtr line = colourLine(!anti);
  if ( !line ) line = ColourLine::create(this, !anti);
  line->addColoured(p, anti);  
}

void Particle::outgoingColour(tPPtr p, bool anti) {
  tColinePtr line = colourLine(anti);
  if ( !line ) line = ColourLine::create(this, anti);
  line->addColoured(p, anti);  
}

tPPtr Particle::incomingColour(bool anti) const {
  if ( !hasColourInfo() ) return tPPtr();
  tColinePtr line = colourLine(anti);
  if ( !line ) return tPPtr();
  for ( int i = 0, N = parents().size(); i < N; ++i )
    if ( parents()[i]->colourLine(anti) == line ) return parents()[i];
  return tPPtr();
}

tPPtr Particle::outgoingColour(bool anti) const {
  if ( !hasColourInfo() ) return tPPtr();
  tColinePtr line = colourLine(anti);
  if ( !line ) return tPPtr();
  for ( int i = 0, N = children().size(); i < N; ++i )
    if ( children()[i]->colourLine(anti) == line ) return children()[i];
  return tPPtr();
}

LorentzPoint Particle::labVertex() const {
  LorentzPoint r(rep().theBirthStep && rep().theBirthStep->collision()?
		 vertex() + rep().theBirthStep->collision()->vertex():
		 vertex());
  return r;
}

void Particle::setLabVertex(const LorentzPoint & p) {
  rep().theVertex = ( rep().theBirthStep && rep().theBirthStep->collision()?
		      p - rep().theBirthStep->collision()->vertex() : p );
}

void Particle::transform(const LorentzRotation & r) {
  if ( hasRep() && spinInfo() ) spinInfo()->transform(momentum(), r);
  theMomentum.transform(r);
  if ( !hasRep() ) return;
  rep().theVertex.transform(r);
  rep().theLifeLength.transform(r);
}

void Particle::deepTransform(const LorentzRotation & r) {
  transform(r);
  if ( !theRep ) return;
  for ( int i = 0, N = children().size(); i < N; ++i )
    rep().theChildren[i]->deepTransform(r);
  if ( rep().theNext ) rep().theNext->deepTransform(r);
}

void Particle::rotateX(double a) {
  LorentzRotation r;
  r.rotateX(a);
  transform(r);
}

void Particle::deepRotateX(double a) {
  LorentzRotation r;
  r.rotateX(a);
  deepTransform(r);
}

void Particle::rotateY(double a) {
  LorentzRotation r;
  r.rotateY(a);
  transform(r);
}

void Particle::deepRotateY(double a) {
  LorentzRotation r;
  r.rotateY(a);
  deepTransform(r);
}

void Particle::rotateZ(double a) {
  LorentzRotation r;
  r.rotateZ(a);
  transform(r);
}

void Particle::deepRotateZ(double a) {
  LorentzRotation r;
  r.rotateZ(a);
  deepTransform(r);
}

void Particle::rotate(double a, const Vector3 & axis) {
  LorentzRotation r;
  r.rotate(a, axis);
  transform(r);
}

void Particle::deepRotate(double a, const Vector3 & axis) {
  LorentzRotation r;
  r.rotate(a, axis);
  deepTransform(r);
}

string Particle::outputFormat =
"%n3%s10%i8 %p[,]0 %c(,) %^^0%vv0 %>>0%<>0 %l{,}0\n"
"                            %x10.3%y10.3%z10.3%e10.3%m10.3\n";

int getNumber(string::const_iterator & pos, int def) {
  if ( !isdigit(*pos) ) return def;
  def = *pos++ - '0';
  while ( isdigit(*pos) ) def = 10*def + *pos++ - '0';
  return def;
}

void writePrecision(ostream & os, string::const_iterator & pos,
			      int defw, int defp, double x) {
  defw = getNumber(pos, defw);
  if ( *pos == '.' ) defp = getNumber(++pos, defp);
  int oldp = os.precision();
  os << setprecision(defp) << setw(defw) << x << setprecision(oldp);
}

void writeStringAdjusted(ostream & os, bool left, int w, string str) {
  while ( !left && w-- > int(str.size()) ) os << ' ';
  os << str;
  while ( left && w-- > int(str.size()) ) os << ' ';
}

template <typename Container>
void writeParticleRanges(ostream & os, const Container & c, char sep, int w) {
  bool elipsis = false;
  int last = -10;
  for ( typename Container::const_iterator it = c.begin();
	it != c.end(); ++it) {
    int n =  (**it).number();
    int next = 0;
    typename Container::const_iterator itn = it + 1;
    if ( itn != c.end() ) next = (**itn).number();
    bool writeit = true;
    bool writesep = false;
    if ( elipsis && ( n != last + 1 || n != next - 1 ) )
      elipsis = false;
    else if ( !elipsis && n == last + 1 && n == next -1 ) {
      os << "..";
      elipsis = true;
      writeit = false;
    }
    else if ( elipsis && n == last + 1 && n == next -1 )
      writeit = false;
    else if ( it != c.begin() )
      writesep = true;
    if ( writeit ) {
      if ( writesep ) os << sep;
      os << setw(w) << n;
    }
    last = n;
  }
}

ostream & ThePEG::operator<<(ostream & os, const Particle & p) {
  tStepPtr step = p.birthStep();
  tCollPtr coll = step? step->collision(): tCollPtr();
  tEventPtr event = coll? coll->event(): tEventPtr();
  string::const_iterator pos = Particle::outputFormat.begin();
  ios::fmtflags saveflags = os.setf(ios::fixed, ios::floatfield);
  while ( pos != Particle::outputFormat.end() ) {
    if ( *pos == '%' && ++pos != Particle::outputFormat.end() ) {
      bool left = false;
      if ( *pos == '-' ) {
	left = true;
	os.setf(ios::left, ios::adjustfield);
	++pos;
      } else {
	os.setf(ios::right, ios::adjustfield);
      }
      char mark;
      char open;
      char close;
      char sep;
      int w;
      string str;
      string fill;
      if ( pos == Particle::outputFormat.end() ) break;
      bool fullColour = false;
      switch ( *pos ) {
      case 'n':
	os << setw(getNumber(++pos, 3)) << p.number();
	break;
      case 'i':
	os << setw(getNumber(++pos, 8)) << p.id();
	break;
      case 's':
	writeStringAdjusted(os, left, getNumber(++pos, 8), p.PDGName());
	break;
      case 'x':
	writePrecision(os, ++pos, 10, 3, p.momentum().x()/GeV);
	break;
      case 'y':
	writePrecision(os, ++pos, 10, 3, p.momentum().y()/GeV);
	break;
      case 'z':
	writePrecision(os, ++pos, 10, 3, p.momentum().z()/GeV);
	break;
      case 'e':
	writePrecision(os, ++pos, 10, 3, p.momentum().e()/GeV);
	break;
      case 'm':
	writePrecision(os, ++pos, 10, 3, p.momentum().mass()/GeV);
	break;
      case 'P':
	fullColour = true;
      case 'p':
	open = *++pos;
	sep = *++pos;
	close = *++pos;
	w = getNumber(++pos, 0);
	if ( p.parents().empty() ) break;
	if ( open ) os << open;
	writeParticleRanges(os, p.parents(), sep, w);
	if ( fullColour && p.hasColourInfo() &&
	     ( p.incomingColour() || p.incomingAntiColour() ) ) {
	  if ( close ) os << open;
	  if ( p.incomingColour() )
	    os << "+" << p.incomingColour()->number();
	  if ( p.incomingAntiColour() )
	    os << "-" << p.incomingAntiColour()->number();
	  if ( close ) os << close;
	}
	if ( close ) os << close;
	break;
      case 'l':
	open = *++pos;
	sep = *++pos;
	close = *++pos;
	w = getNumber(++pos, 0);
	if ( ( !p.colourLine() && !p.antiColourLine() ) || !event) break;
	if ( open ) os << open;
	if ( p.colourLine() ) {
	  p.colourLine()->write(os, event, false);
	  if ( p.antiColourLine() && sep ) os << sep;
	}
	if ( p.antiColourLine() )
	  p.antiColourLine()->write(os, event, true);
	if ( close ) os << close;
	break;
      case 'C':
	fullColour = true;
      case 'c':
	open = *++pos;
	sep = *++pos;
	close = *++pos;
	w = getNumber(++pos, 0);
	if ( p.children().empty() ) break;
	if ( open ) os << open;
	writeParticleRanges(os, p.children(), sep, w);
	if ( fullColour && p.hasColourInfo() &&
	     ( p.outgoingColour() || p.outgoingAntiColour() ) ) {
	  if ( close ) os << open;
	  if ( p.outgoingColour() )
	    os << "+" << p.outgoingColour()->number();
	  if ( p.outgoingAntiColour() )
	    os << "-" << p.outgoingAntiColour()->number();
	  if ( close ) os << close;
	}
	if ( close ) os << close;
	break;
      case '>':
	mark = *++pos;
	w = getNumber(++pos, 0);
	if ( p.hasColourInfo() && p.colourNeighbour() ) {
	  os << setw(w-1) << p.colourNeighbour()->number() << mark;
	}
	break;
      case '<':
	mark = *++pos;
	w = getNumber(++pos, 0);
	if ( p.hasColourInfo() && p.antiColourNeighbour() ) {
	  int n = p.antiColourNeighbour()->number();
	  ostringstream oss;
	  oss << mark << n;
	  writeStringAdjusted(os, left, w, oss.str());
	}
	break;
      case 'v':
	mark = *++pos;
	w = getNumber(++pos, 0);
	if ( p.next() ) {
	  if ( left && mark ) os << mark;
	  os << setw(w) << p.next()->number();
	  if ( !left && mark ) os << mark;
	}
	break;
      case '^':
	mark = *++pos;
	w = getNumber(++pos, 0);
	if ( p.previous() ) {
	  if ( left && mark ) os << mark;
	  os << setw(w) << p.previous()->number();
	  if ( !left && mark ) os << mark;
	}
	break;
      case 'd':
	switch ( *++pos ) {
	case 'x':
	  writePrecision(os, ++pos, 10, 3, p.lifeLength().x()/mm);
	  break;
	case 'y':
	  writePrecision(os, ++pos, 10, 3, p.lifeLength().y()/mm);
	  break;
	case 'z':
	  writePrecision(os, ++pos, 10, 3, p.lifeLength().z()/mm);
	  break;
	case 't':
	  writePrecision(os, ++pos, 10, 3, p.lifeLength().e()/mm);
	  break;
	case 'T':
	  writePrecision(os, ++pos, 10, 3, p.lifeLength().tau()/mm);
	  break;
	}
	break;
      case 'V':
	switch ( *++pos ) {
	case 'x':
	  writePrecision(os, ++pos, 10, 3, p.vertex().x()/mm);
	  break;
	case 'y':
	  writePrecision(os, ++pos, 10, 3, p.vertex().y()/mm);
	  break;
	case 'z':
	  writePrecision(os, ++pos, 10, 3, p.vertex().z()/mm);
	  break;
	case 't':
	  writePrecision(os, ++pos, 10, 3, p.vertex().e()/mm);
	  break;
	}
      case 'L':
	switch ( *++pos ) {
	case 'x':
	  writePrecision(os, ++pos, 10, 3, p.labVertex().x()/mm);
	  break;
	case 'y':
	  writePrecision(os, ++pos, 10, 3, p.labVertex().y()/mm);
	  break;
	case 'z':
	  writePrecision(os, ++pos, 10, 3, p.labVertex().z()/mm);
	  break;
	case 't':
	  writePrecision(os, ++pos, 10, 3, p.labVertex().e()/mm);
	  break;
	}
	break;
      default:
	os << *pos++;
      }
    } else {
      if ( pos != Particle::outputFormat.end() ) os << *pos++;
    }
  }
  os.flags(saveflags);
  return os;
}

void Particle::persistentOutput(PersistentOStream & os) const {
  EventConfig::putParticleData(os, theData);
  os << ounit(theMomentum, GeV) << bool( theRep != 0 );
  if ( !theRep ) return;
  os << rep().theParents << rep().theChildren
     << rep().thePrevious << rep().theNext << rep().theBirthStep
     << ounit(rep().theVertex, mm) << ounit(rep().theLifeLength, mm)
     << ounit(rep().theScale, GeV2) << rep().theNumber << rep().theDecayMode
     << rep().theColourInfo << rep().theSpinInfo << rep().theExtraInfo;
}

void Particle::persistentInput(PersistentIStream & is, int) {
  bool hasRep;
  EventConfig::getParticleData(is, theData);
  is >> iunit(theMomentum, GeV) >> hasRep;
  if ( !hasRep ) return;

  is >> rep().theParents >> rep().theChildren
     >> rep().thePrevious >> rep().theNext >> rep().theBirthStep
     >> iunit(rep().theVertex, mm) >> iunit(rep().theLifeLength, mm)
     >> iunit(rep().theScale, GeV2) >> rep().theNumber >> rep().theDecayMode
     >> rep().theColourInfo >> rep().theSpinInfo >> rep().theExtraInfo;
}

ClassDescription<Particle> Particle::initParticle;

void Particle::Init() {}

ThePEG_IMPLEMENT_SET(PPtr,ParticleSet);

