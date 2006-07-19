dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([ThePEG],[1.0],[http://www.thep.lu.se/ThePEG/],[ThePEG])
AC_CONFIG_AUX_DIR([Config])

AC_CONFIG_SRCDIR([EventRecord/SubProcess.h])
AC_CONFIG_HEADERS([Config/config.h])

AC_CANONICAL_HOST

case "${host}" in
  *-darwin[[0156]].*) 
    AC_MSG_ERROR([ThePEG requires OS X 10.3 or later])
    ;;
  *-darwin*) 
    if test "x$MACOSX_DEPLOYMENT_TARGET" != "x10.3"; then 
       AC_MSG_ERROR(
       [Please export the MACOSX_DEPLOYMENT_TARGET variable, set to 10.3]) 
    fi 
    ;;	
esac

AC_LANG(C++)
AM_INIT_AUTOMAKE

dnl Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_DISABLE_STATIC
AC_LIBTOOL_DLOPEN

AC_PROG_LIBTOOL

AC_SEARCH_CLHEP

AC_DEFINE_ENVDEFAULT(ThePEG_GZREAD_FILE,GZREAD_FILE,gunzip -c,[The command which, taking the name of a gzipped file as argument, unzips it and prints it to stdout. Default is "gunzip -c"])

AC_DEFINE_ENVDEFAULT(ThePEG_GZWRITE_FILE,GZWRITE_FILE,[gzip -c > ],[The command which, taking the name of a gzipped file as argument, reads stdin, zips it and writes it to the file. Default is "gzip -c > ".])

AC_DEFINE_ENVDEFAULT(ThePEG_BZ2READ_FILE,BZ2READ_FILE,bunzip2 -c,[The command which, taking the name of a bzipped file as argument, unzips it and prints it to stdout. Default is "bunzip2 -c".])

AC_DEFINE_ENVDEFAULT(ThePEG_BZ2WRITE_FILE,BZ2WRITE_FILE,[bzip2 -c > ],[The command which, taking the name of a bzipped file as argument, reads stdin, zips it and writes it to the file. Default is "bzip2 -c > ".])

AC_CHECK_EXPM1
AC_CHECK_LOG1P
AC_CHECK_DLOPEN
AC_CHECK_SSTREAM
AC_CHECK_FPUCONTROL


AM_CPPFLAGS="-I\$(top_builddir)/include $CLHEPINCLUDE"
AM_CXXFLAGS="-ansi -pedantic -Wall"
AC_SUBST(AM_CPPFLAGS)
AC_SUBST(AM_CXXFLAGS)

AC_EMPTY_SUBST

AC_PATH_PROG(PERL, perl)

AC_ARG_WITH(javagui,
            [  --with-javagui          Compile and install the java-based GUI.])

if test "x$with_javagui" != "xno"; then
  AC_HAS_JAVA([1.4], [], [with_javagui=no; AC_MSG_NOTICE([Java GUI disabled])])
fi

AM_CONDITIONAL([JAVAGUI], [test "x$with_javagui" != "xno"])

AC_CONFIG_FILES([Helicity/Makefile
Utilities/Makefile
include/Makefile
Interface/Makefile
LesHouches/Makefile
CLHEPWrap/Makefile
PDT/Makefile
PDF/Makefile
Persistency/Makefile
Config/Makefile
Handlers/Makefile
MatrixElement/Makefile
Pointer/Makefile
lib/Makefile
lib/Makefile.common.install
src/Makefile
ACDC/Makefile
Repository/Makefile
EventRecord/Makefile
StandardModel/Makefile
Cuts/Makefile
Analysis/Makefile
Doc/Makefile
Doc/refman.h
Doc/refman.conf
java/Makefile
Makefile])
AC_CONFIG_FILES([Doc/fixinterfaces.pl],[chmod +x Doc/fixinterfaces.pl])

AC_OUTPUT
