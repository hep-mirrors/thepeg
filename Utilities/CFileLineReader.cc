// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the CFileLineReader class.
//

#include "CFileLineReader.h"

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
  else if ( filename.substr(filename.length()-3,3) == ".gz" ) {
    filename = "zcat " + filename;
    file = popen(filename.c_str(), "r");
    type = pipe;
  }
  else {
    std::fopen(filename.c_str(), "r");
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
