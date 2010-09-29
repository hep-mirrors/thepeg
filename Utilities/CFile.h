// -*- C++ -*-
#ifndef THEPEG_CFile_H
#define THEPEG_CFile_H
//
// This is the declaration of the CFile class.
//

#include "Exception.h"

namespace ThePEG {

/**
 * Here is the documentation of the CFile class.
 */
class CFile {

public:

  enum FileType {
    undefined, plain, pipe, gzip, bzip2
  };

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  CFile(): file(0), fileType(undefined) {}

  /**
   * Create a CFile given a file name and a mode.
   */
  CFile(string filename, string mode)
  : file(0), fileType(undefined) {
    open(filename, mode);
  }
    
  /**
   * The destructor.
   */
  ~CFile() {}
  //@}


  void open(string filename, string mode);

  void close();

  operator void * () const {
    return fileType != undefined? file: 0;
  }

  bool operator!() const {
    return !(operator void * ());
  }

  char * gets(char * s, int size);

  int puts(const char * s);

  int getc();

  int putc(int c);

  int ungetc(int c);

  size_t read(void *ptr, size_t size, size_t nmemb = 1);

  size_t write(const void *ptr, size_t size, size_t nmemb = 1);

private:

  void * file;

  FileType fileType;

public:

  /** @cond EXCEPTIONCLASSES */
  /** Exception class used by CFile if reading a file fails. */
  class FileError: public Exception {};
  /** @endcond */

};

}


#endif /* THEPEG_CFile_H */
