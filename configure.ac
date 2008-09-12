dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT([ThePEG],[SVN],[http://www.thep.lu.se/ThePEG/],[ThePEG])
AC_CONFIG_AUX_DIR([Config])
AC_CONFIG_MACRO_DIR([m4])

THEPEG_LIBTOOL_VERSION_INFO(5,0,0)

AC_CONFIG_SRCDIR([EventRecord/SubProcess.h])
AC_CONFIG_HEADERS([Config/config.h Config/LWH.h Config/ThePEG_Qty.h:Config/ThePEG_Qty.h.a:Config/ThePEG_Qty.h.in:Config/ThePEG_Qty.h.b])

AC_CANONICAL_HOST

case "${host}" in
  *-darwin[[0156]].*) 
    AC_MSG_ERROR([ThePEG requires OS X 10.3 or later])
    ;;
  *-darwin7.*) 
    if test "x$MACOSX_DEPLOYMENT_TARGET" != "x10.3"; then 
       AC_MSG_ERROR(
       [Please export the MACOSX_DEPLOYMENT_TARGET variable, set to 10.3]) 
    fi 
    ;;	
esac

AC_LANG(C++)
AM_INIT_AUTOMAKE([1.9 gnu dist-bzip2 -Wall]) 
dnl also include std-options once --version and --help exist

dnl Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S

LT_PREREQ([2.2])
LT_INIT([disable-static dlopen pic-only])

THEPEG_UNIT_CHECKING
THEPEG_SEARCH_LHAPDF

THEPEG_DEFINE_ENVDEFAULT(ThePEG_GZREAD_FILE,GZREAD_FILE,gunzip -c,[The command which, taking the name of a gzipped file as argument, unzips it and prints it to stdout. Default is "gunzip -c"])

THEPEG_DEFINE_ENVDEFAULT(ThePEG_GZWRITE_FILE,GZWRITE_FILE,[gzip -c > ],[The command which, taking the name of a gzipped file as argument, reads stdin, zips it and writes it to the file. Default is "gzip -c > ".])

THEPEG_DEFINE_ENVDEFAULT(ThePEG_BZ2READ_FILE,BZ2READ_FILE,bunzip2 -c,[The command which, taking the name of a bzipped file as argument, unzips it and prints it to stdout. Default is "bunzip2 -c".])

THEPEG_DEFINE_ENVDEFAULT(ThePEG_BZ2WRITE_FILE,BZ2WRITE_FILE,[bzip2 -c > ],[The command which, taking the name of a bzipped file as argument, reads stdin, zips it and writes it to the file. Default is "bzip2 -c > ".])

THEPEG_CHECK_EXPM1
THEPEG_CHECK_LOG1P
THEPEG_CHECK_DLOPEN
THEPEG_CHECK_FPUCONTROL
THEPEG_CHECK_GSL
THEPEG_CHECK_AIDA

AM_CPPFLAGS="-I\$(top_builddir)/include \$(GSLINCLUDE)"
if test "$GCC" = "yes"; then
   AM_CXXFLAGS="-ansi -pedantic -Wall -W"
fi

THEPEG_CHECK_ABS_BUG

AC_SUBST(AM_CPPFLAGS)
AC_SUBST(AM_CXXFLAGS)

THEPEG_EMPTY_SUBST

AC_PATH_PROG(PERL, perl)

AC_ARG_WITH(javagui,
            [  --with-javagui          Compile and install the java-based GUI.])

if test "x$with_javagui" != "xno"; then
  THEPEG_HAS_JAVA([1.4], [], [with_javagui=no; AC_MSG_NOTICE([Java GUI disabled])])
fi

AM_CONDITIONAL([JAVAGUI], [test "x$with_javagui" != "xno"])

AC_CONFIG_FILES([Helicity/Makefile
Helicity/WaveFunction/Makefile
Helicity/Vertex/Makefile
Helicity/Vertex/Scalar/Makefile
Helicity/Vertex/Vector/Makefile
Helicity/Vertex/Tensor/Makefile
Utilities/Makefile
include/Makefile
Interface/Makefile
LesHouches/Makefile
Vectors/Makefile
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
