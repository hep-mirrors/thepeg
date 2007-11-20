// -*- C++ -*-
//
// CFileLineReader.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the CFileLineReader class.
//

#include "CFileLineReader.h"
#include "config.h"
#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "CFileLineReader.tcc"
#endif


using namespace ThePEG;

CFileLineReader::~CFileLineReader() {
  close();
}

void CFileLineReader::open(string filename) {
  close();
  pos = buff;
  if ( filename[filename.length()-1] == '|' ) {
    filename = filename.substr(0, filename.length() - 1);
    file = popen(filename.c_str(), "r");
    type = pipe;
  }
#ifdef ThePEG_GZREAD_FILE
  else if ( filename.substr(filename.length()-3,3) == ".gz" ) {
    filename = ThePEG_GZREAD_FILE " " + filename;
    file = popen(filename.c_str(), "r");
    type = pipe;
  }
#endif
#ifdef ThePEG_BZ2READ_FILE
  else if ( filename.substr(filename.length()-4,4) == ".bz2" ) {
    filename = ThePEG_BZ2READ_FILE " " + filename;
    file = popen(filename.c_str(), "r");
    type = pipe;
  }
#endif
  else {
    file = std::fopen(filename.c_str(), "r");
    type = plainfile;
  }
  bad = ( file == NULL );
}

void CFileLineReader::close() {
  if ( file != NULL ) {
    if ( type == plainfile ) fclose(file);
    if ( type == pipe ) pclose(file);
  }
  file = NULL;
}

bool CFileLineReader::readline() {
  bad = ( std::fgets(buff, bufflen, file) == NULL );
  pos = buff;
  return !bad;
}

