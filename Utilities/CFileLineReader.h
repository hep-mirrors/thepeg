// -*- C++ -*-
#ifndef THEPEG_CFileLineReader_H
#define THEPEG_CFileLineReader_H
//
// This is the declaration of the CFileLineReader class.
//

#include "ThePEG/Config/ThePEG.h"
#include "CFileLineReader.fh"
#include <cstdio>
#include <string>

namespace ThePEG {

/**
 * CFileLineReader is a wrapper around a standard C FILE stream. With
 * it one reads one line at the time (with readline()) into an
 * internal buffer from which one can then read as from a standard
 * std::istream with a limited set of operator>> functions. It can be
 * thought of as an std::ifstream where the internal buffer must be
 * filled by hand one line at the time.
 *
 * Contrary to std::ifstream the CFileLineReader can also handle
 * gipped files and pipes. Gzipped files are automatically handles by
 * a pipe using the <code>zcat</code> command if the file name ends
 * with <code>.gz</code>. Also if a file name ends with a
 * <code>|</code> sign, the preceding string is interpreted as a
 * command defining a pipe from which to read.
 *
 * Since CFileLineReader is very close to the standard C FILE stream
 * it is in many cases much faster than eg. reading from lines via
 * std::istringstream.
 */
class CFileLineReader {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline CFileLineReader();

  /**
   * Constructor taking a c-file \a f opened from the outside as
   * argument. Optionally the size \a len of the line buffer can be
   * specified.
   */
  inline CFileLineReader(FILE * f, int len = defsize);

  /**
   * Constructor taking a \a filename as argument. Optionally the size
   * \a len of the line buffer can be specified. If \a filename ends
   * with <code>.gz</code> a pipe is opened where the file is read by
   * <code>zcat</code>. If \a filename ends with a <code>|</code>
   * sign, the preceding string is interpreted as a command defining a
   * pipe from which to read.
   */
  inline CFileLineReader(string filename, int len = defsize);

  /**
   * The destructor.
   */
  virtual ~CFileLineReader();
  //@}

  /** @name Initialization functions. */
  //@{
  /**
   * Initialize with a c-file \a f opened from the outside.
   */
  inline void setFILE(FILE * f);

  /**
   * Initialize with a \a filename. If \a filename ends with
   * <code>.gz</code> a pipe is opened where the file is read by
   * <code>zcat</code>. If \a filename ends with a <code>|</code>
   * sign, the preceding string is interpreted as a command defining a
   * pipe from which to read.
   */
  void setFile(string filename);

  /**
   * If the file was opened from within this object, close it.
   */
  void close();
  //@}

  /**
   * Read a line from the underlying c-file into the line buffer.
   */
  bool readline();

  /**
   * Return a string containing what is left of the line buffer.
   */
  inline string getline() const;

  /**
   * Return the underlying c-file.
   */
  inline FILE * cfile() const;

  /**
   * Return null if a previous read failed.
   */
  inline operator void *();

  /**
   * Return true if a previous read failed.
   */
  inline bool operator!();

  /** @name Operators to read from the line buffer. */
  //@{
  /**
   * Return the next character of the line-buffer.
   */
  inline char getc();

  /**
   * Read a long from the line buffer.
   */
  inline CFileLineReader & operator>>(long & l);

  /**
   * Read an int from the line buffer.
   */
  inline CFileLineReader & operator>>(int & i);

  /**
   * Read an unsigned long from the line buffer.
   */
  inline CFileLineReader & operator>>(unsigned long & l);

  /**
   * Read an unsigned int from the line buffer.
   */
  inline CFileLineReader & operator>>(unsigned int & i);

  /**
   * Read a double from the line buffer.
   */
  inline CFileLineReader & operator>>(double & d);

  /**
   * Read a float from the line buffer.
   */
  inline CFileLineReader & operator>>(float & f);

  /**
   * Read a (whitespace delimited) string from the line buffer.
   */
  inline CFileLineReader & operator>>(std::string & s);
  //@}

private:

  /**
   * Enumerate different kinds of c-files.
   */
  enum StreamType { unknown,   /**< Unknown type opened from the outside. */
		    plainfile, /**< A plain file opened with fopen(). */
		    pipe       /**< A pipe opened with popen(). */
  };

  /**
   * The c-file to be read from.
   */
  FILE * file;

  /**
   * The length of the line buffer.
   */
  int bufflen;

  /**
   * The line buffer.
   */
  char * buff;

  /**
   * The current position in the line buffer.
   */
  char * pos;

  /**
   * The current state is bad if a read has failed.
   */
  bool bad;

  /**
   * The type of the c-file used.
   */
  StreamType type;

  /**
   * The default size of the buffer.
   */
  static const int defsize = 1024;

private:

  /**
   * The copy constructor is private and not implemented.
   */
  CFileLineReader(const CFileLineReader &);

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  CFileLineReader & operator=(const CFileLineReader &);

};

}

#include "CFileLineReader.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "CFileLineReader.tcc"
#endif

#endif /* THEPEG_CFileLineReader_H */
