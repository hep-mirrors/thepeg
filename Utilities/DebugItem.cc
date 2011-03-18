// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the DebugItem class.
//

#include "DebugItem.h"
#include "ThePEG/Utilities/Debug.h"

using namespace ThePEG;

DebugItem::DebugItem(string itemname): debug(false) {
  items()[itemname] = this;
  map<string,long>::iterator it = nametics().find(itemname);
  if ( it != nametics().end() ) {
    if ( ticker() >= it->second ) debug = true;
    else itemtics().insert(make_pair(it->second, this));
  } else {
    itemname = itemname.substr(0, itemname.rfind("::")) + "::all";
    it = nametics().find(itemname);
    if ( it != nametics().end() ) {
      if ( ticker() >= it->second ) debug = true;
      else itemtics().insert(make_pair(it->second, this));
    }
  }
}

void DebugItem::tic() {
  ticker()++;
  multimap<long,DebugItem*>::iterator it = itemtics().begin();
  while ( it != itemtics().end() &&
	  ticker() >= it->first ) (it++)->second->debug = true;
  itemtics().erase(itemtics().begin(), it);
}

void DebugItem::setDebugItem(string itemname, long after) {
  nametics()[itemname] = after;
  map<string,DebugItem*>::iterator it = items().find(itemname);
  if ( it != items().end() ) {
    if ( ticker() >= after ) it->second->debug = true;
    else itemtics().insert(make_pair(after, it->second));
  } else if ( itemname.substr(itemname.length() - 5) == "::all" ) {
    itemname = itemname.substr(itemname.length() - 3);
    for ( map<string,DebugItem*>::iterator it = items().begin();
	  it != items().end(); ++it )
      if ( it->first.substr(0, itemname.length()) == itemname ) {
	if ( ticker() >= after ) it->second->debug = true;
	else itemtics().insert(make_pair(after, it->second));
      }	
  }
}

long & DebugItem::ticker() {
  static long tics = 0;
  return tics;
}

map<string,DebugItem*> & DebugItem::items() {
  static map<string,DebugItem*> itemmap;
  return itemmap;
}

multimap<long,DebugItem*> & DebugItem::itemtics() {
  static multimap<long,DebugItem*> itemmap;
  return itemmap;
}

map<string,long> & DebugItem::nametics() {
  static map<string,long> namemap;
  return namemap;
}
