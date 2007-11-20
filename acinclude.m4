# Search for LHAPDF and g77 compiler in standard directories
AC_DEFUN([THEPEG_SEARCH_LHAPDF],
[
AC_MSG_CHECKING([if LHAPDF is present and works])
HAS_LHAPDF="yes"
LHAPDF_LIBDIR=""
AC_ARG_WITH(LHAPDF,[  --without-LHAPDF        do not use LHAPDF package (requires g77 compiler)
                          (included by default --with-LHAPDF=path to specify
                          where the LHAPDF shared library is located)], [if test -n "$with_LHAPDF" -a "x$with_LHAPDF" != "xyes" -a "x$with_LHAPDF" != "xno"; then LHAPDF_LIBDIR="$with_LHAPDF"; elif test "x$with_LHAPDF" == "xno"; then HAS_LHAPDF="no"; fi])


LHAPDF_LDFLAGS=""
if test -n "$LHAPDF_LIBDIR"; then
  if test -e $LHAPDF_LIBDIR/libLHAPDF.so; then
    LHAPDF_LDFLAGS="-L$LHAPDF_LIBDIR"
  else
    HAS_LHAPDF="no"
  fi
fi

LHAPDF_LIBS="-lLHAPDF"

oldLIB="$LIBS"
oldLDFLAGS="$LDFLAGS"

if test "$HAS_LHAPDF" == "yes"; then
dnl Now lets see if the libraries work properly
  LIBS="$LIBS $LHAPDF_LIBS"
  LDFLAGS="$LDFLAGS $LHAPDF_LDFLAGS"
  AC_LINK_IFELSE([AC_LANG_PROGRAM([[extern "C" { void initpdf_(int&); }]],
                                  [[int i = 1; initpdf_(i);]])], ,
                                  HAS_LHAPDF="no")
fi

LIBS="$oldLIB"
LDFLAGS="$oldLDFLAGS"

if test "$HAS_LHAPDF" == "yes"; then
  AC_MSG_RESULT([yes])
elif test "x$with_LHAPDF" == "xno" -o "x$with_LHAPDF" == "x"; then
  AC_MSG_RESULT([no])
else
  AC_MSG_ERROR([LHAPDF was requested but the library was not found.])
fi
AC_SUBST(LHAPDF_LIBS)
AC_SUBST(LHAPDF_LDFLAGS)
AM_CONDITIONAL([USELHAPDF], [test "x$HAS_LHAPDF" == "xyes"])
])

# Search for stand-alone HepMC in standard directories
AC_DEFUN([THEPEG_SEARCH_HEPMC],
[
AC_MSG_CHECKING([if stand-alone HepMC is present and works])
HAS_HEPMC="yes"
HEPMC_LIBDIR=""
AC_ARG_ENABLE(HEPMC,[  --disable-HEPMC        do not use stand-alone HepMC package
                          (enabled by default --enable-HEPMC=path to specify
                          where the HEPMC shared library is located)], [if test -n "$enable_HEPMC" -a "$enable_HEPMC" != "yes" -a "$enable_HEPMC" != "no"; then HEPMC_LIBDIR="$enable_HEPMC"; elif test "$enable_HEPMC" == "no"; then HAS_HEPMC="no"; fi])


HEPMC_LDFLAGS=""
if test -n "$HEPMC_LIBDIR"; then
  HEPMC_LDFLAGS="-L$HEPMC_LIBDIR"
fi

HEPMC_LIBS="-lHepMC"

oldLIB="$LIBS"
oldLDFLAGS="$LDFLAGS"

if test "$HAS_HEPMC" == "yes"; then
dnl Now lets see if the libraries work properly
  LIBS="$LIBS $HEPMC_LIBS"
  LDFLAGS="$LDFLAGS $HEPMC_LDFLAGS"
  AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include "HepMC/GenEvent.h"]],
                                  [[HepMC::GenEvent * eve;]])], ,
                                  HAS_HEPMC="no")
fi

LIBS="$oldLIB"
LDFLAGS="$oldLDFLAGS"

if test "$HAS_HEPMC" == "yes"; then
  HEPMC_LIBS="-lHepMC -lHepMCfio"
  AC_MSG_RESULT([yes])
else
  AC_MSG_RESULT([no])
fi
AC_SUBST(HEPMC_LIBS)
AC_SUBST(HEPMC_LDFLAGS)
AM_CONDITIONAL([USEHEPMC], [test "x$HAS_HEPMC" == "xyes"])
])

# Search for CLHEP in standard directories using standard CLHEP names
AC_DEFUN([THEPEG_SEARCH_CLHEP],
[AC_MSG_CHECKING([if CLHEPPATH is set])
notsetp=""
notsetl=""
if test -z "$CLHEPPATH"; then
  notsetp="true"
  for dirbase in / /usr $ac_default_prefix $prefix; do
    if test -z "$CLHEPLIB"; then
      notsetl="true"
      for filename in $dirbase/lib/libCLHEP-?.?.?.?.{so,dylib} $dirbase/lib/libCLHEP.{so,dylib}; do
        if test -f $filename; then
          CLHEPPATH=$dirbase
          CLHEPLIB=`basename $filename | sed -e 's/^lib/-l/' -e 's/\.\(so\|dylib\)$//'`
        fi
      done
    else
      filename=`echo $CLHEPLIB | sed -e 's/^-l/lib/'`
      if test -f $dirbase/lib/$filename.so -o -f $dirbase/lib/$filename.dylib; then
	CLHEPPATH=$dirbase
      fi
    fi
  done
else
  if test -z "$CLHEPLIB"; then
    notsetl="true"
    for filename in $CLHEPPATH/lib/libCLHEP-?.?.?.?.{so,dylib} CLHEPPATH/lib/libCLHEP.{so,dylib}; do
      if test -f $filename; then
        CLHEPLIB=`basename $filename | sed -e 's/^lib/-l/' -e 's/\.\(so\|dylib\)$//'`
      fi
    done
  fi
fi

if test -z "$notsetp"; then
  AC_MSG_RESULT([yes ($CLHEPPATH)])
else
  AC_MSG_RESULT([no (found $CLHEPPATH)])
fi
AC_MSG_CHECKING([if CLHEPLIB is set])
if test -z "$notsetl"; then
  AC_MSG_RESULT([yes ($CLHEPLIB)])
else
  AC_MSG_RESULT([no (found $CLHEPLIB)])
fi

AC_MSG_CHECKING([if CLHEPINCLUDE is set])
if test -z "$CLHEPINCLUDE"; then
  CLHEPINCLUDE=-I$CLHEPPATH/include
  AC_MSG_RESULT([no (found $CLHEPINCLUDE)])
else
  AC_MSG_RESULT([yes ($CLHEPINCLUDE)])
fi

dnl Now lets see if the libraries work properly
oldLIB="$LIBS"
oldLDFLAGS="$LDFLAGS"
oldCPPFLAGS="$CPPFLAGS"
LIBS="$LIBS $CLHEPLIB"
LDFLAGS="$LDFLAGS -L$CLHEPPATH/lib"
CPPFLAGS="$CPPFLAGS $CLHEPINCLUDE"

dnl check CLHEP first
AC_MSG_CHECKING([that CLHEP works])
AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <CLHEP/Random/Random.h>
namespace CLHEP {}]], [[using namespace CLHEP; HepRandom r; r.flat();]])],AC_MSG_RESULT(yes),[AC_MSG_RESULT(no) 
AC_MSG_ERROR(CLHEP must be installed to continue.)
AC_SUBST(CLHEPPATH)
AC_SUBST(CLHEPLIB)
AC_SUBST(CLHEPINCLUDE)
])
    
LIBS="$oldLIB"
LDFLAGS="$oldLDFLAGS"
CPPFLAGS="$oldCPPFLAGS"

AC_ARG_VAR(CLHEPPATH,[The path to where CLHEP is installed. Default is $prefix.])
AC_ARG_VAR(CLHEPLIB,[The argument to be used when linking the CLHEP library. Default is "-lCLHEP".])

AC_ARG_VAR(CLHEPINCLUDE,[The argument used when compiling source files which uses CLHEP. Default is "-I$CLHEPPATH/include".])

])



# Check for CLHEP.
AC_DEFUN([THEPEG_CHECK_CLHEP],
[AC_MSG_CHECKING([if CLHEPPATH is set])
if test -z "$CLHEPPATH"; then
  if test "x$prefix" == "xNONE"; then
    CLHEPPATH=$ac_default_prefix
  else
    CLHEPPATH=$prefix
  fi
  AC_MSG_RESULT([no (using $CLHEPPATH)])
else
  AC_MSG_RESULT([yes ($CLHEPPATH)])
fi
AC_ARG_VAR(CLHEPPATH,[The path to where CLHEP is installed. Default is $prefix.])

AC_MSG_CHECKING([if CLHEPLIB is set])
if test -z "$CLHEPLIB"; then
  CLHEPLIB="-lCLHEP"
  AC_MSG_RESULT([no (using $CLHEPLIB)])
else
  AC_MSG_RESULT([yes ($CLHEPLIB)])
fi
AC_ARG_VAR(CLHEPLIB,[The argument to be used when linking the CLHEP library. Default is "-lCLHEP".])

AC_MSG_CHECKING([if CLHEPINCLUDE is set])
if test -z "$CLHEPINCLUDE"; then
  CLHEPINCLUDE=-I$CLHEPPATH/include
  AC_MSG_RESULT([no (using $CLHEPINCLUDE)])
else
  AC_MSG_RESULT([yes ($CLHEPINCLUDE)])
fi
AC_ARG_VAR(CLHEPINCLUDE,[The argument used when compiling source files which uses CLHEP. Default is "-I$CLHEPPATH/include".])

dnl ###############################
dnl ###############################
dnl ###############################

dnl Now lets see if the libraries work properly
oldLIB="$LIBS"
oldLDFLAGS="$LDFLAGS"
oldCPPFLAGS="$CPPFLAGS"
LIBS="$LIBS $CLHEPLIB"
LDFLAGS="$LDFLAGS -L$CLHEPPATH/lib"
CPPFLAGS="$CPPFLAGS $CLHEPINCLUDE"

dnl check CLHEP first
AC_MSG_CHECKING([that CLHEP works])
AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <CLHEP/Random/Random.h>
namespace CLHEP {}]], [[using namespace CLHEP; HepRandom r; r.flat();]])],AC_MSG_RESULT(yes),[AC_MSG_RESULT(no) 
AC_MSG_ERROR(CLHEP must be installed to continue.)
AC_SUBST(CLHEPPATH)
AC_SUBST(CLHEPLIB)
AC_SUBST(CLHEPINCLUDE)
])

LIBS="$oldLIB"
LDFLAGS="$oldLDFLAGS"
CPPFLAGS="$oldCPPFLAGS"
])

# Check for ThePEG.
AC_DEFUN([THEPEG_CHECK_THEPEG],
[THEPEGBUILD="no"

AC_MSG_CHECKING([if THEPEGPATH is set])
if test -z "$THEPEGPATH"; then
  if test -f "../ThePEG/Config/config.h"; then
    THEPEGPATH="\$(top_builddir)/../ThePEG"
    THEPEGBUILD="yes"
    AC_MSG_RESULT([no (using ../ThePEG)])
    AM_CPPFLAGS="-I\$(top_builddir)/include -I\$(top_builddir)/../ThePEG/include $CLHEPINCLUDE"
    SETUPTHEPEG="$THEPEGPATH/src/setupThePEG.bin -L $THEPEGPATH/lib"
    RUNTHEPEG="$THEPEGPATH/src/runThePEG.bin -L $THEPEGPATH/lib"
    THEPEGDOC="\$(top_builddir)/../ThePEG/Doc"
    THEPEGLIB="\$(top_builddir)/../ThePEG/lib"
  else
    if test "x$prefix" == "xNONE"; then
      THEPEGPATH=$ac_default_prefix
    else
      THEPEGPATH=$prefix
    fi
    AC_MSG_RESULT([no (using $THEPEGPATH)])
  fi
else
  AC_MSG_RESULT([yes ($THEPEGPATH)])
fi

if test "$THEPEGBUILD" == "no"; then
  AM_CPPFLAGS="-I\$(top_builddir)/include -I$THEPEGPATH/include $CLHEPINCLUDE"
  SETUPTHEPEG="$THEPEGPATH/bin/setupThePEG"
  RUNTHEPEG="$THEPEGPATH/bin/runThePEG"
  THEPEGDOC="$THEPEGPATH/share/ThePEG/Doc"
  THEPEGLIB="$THEPEGPATH/lib/ThePEG"
  AC_MSG_CHECKING([if the installed ThePEG works])
  if test -x $SETUPTHEPEG && $SETUPTHEPEG /dev/null; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR(ThePEG must be installed and THEPEGPATH set properly.)
  fi
fi
AC_ARG_VAR(THEPEGPATH,[The path to where ThePEG is installed. Default is $prefix unless we are working in a sister of the build directory of ThePEG.])

pkglibdir="\$(libdir)/ThePEG"
AC_SUBST(pkglibdir)
AC_SUBST(THEPEGPATH)
AC_SUBST(THEPEGINCLUDE)
AC_SUBST(THEPEGDOC)
AC_SUBST(THEPEGLIB)
AC_SUBST(SETUPTHEPEG)
AC_SUBST(RUNTHEPEG)
AC_SUBST(AM_CPPFLAGS)
])

# Search for ThePEG in standard places.
AC_DEFUN([THEPEG_SEARCH_THEPEG],
[THEPEGBUILD="no"

AC_MSG_CHECKING([if THEPEGPATH is set])
if test -z "$THEPEGPATH"; then
  if test -f "../ThePEG/Config/config.h"; then
    THEPEGPATH="\$(top_builddir)/../ThePEG"
    THEPEGBUILD="yes"
    AC_MSG_RESULT([no (found ../ThePEG)])
    AM_CPPFLAGS="-I\$(top_builddir)/include -I\$(top_builddir)/../ThePEG/include $CLHEPINCLUDE"
    SETUPTHEPEG="$THEPEGPATH/src/setupThePEG.bin -L $THEPEGPATH/lib"
    RUNTHEPEG="$THEPEGPATH/src/runThePEG.bin -L $THEPEGPATH/lib"
    THEPEGDOC="\$(top_builddir)/../ThePEG/Doc"
    THEPEGLIB="\$(top_builddir)/../ThePEG/lib"
  else
    for dirbase in / /usr $ac_default_prefix $prefix; do
      if test -f $dirbase/include/ThePEG/Config/config.h; then
        THEPEGPATH=$dirbase
      fi
    done
    if test -z "$THEPEGPATH"; then
      AC_MSG_RESULT([no])
      AC_MSG_ERROR(Could not find a valid ThePEG installation or build directory)
    else
      AC_MSG_RESULT([no (found $THEPEGPATH)])
    fi
  fi
else
  AC_MSG_RESULT([yes ($THEPEGPATH)])
fi

if test "$THEPEGBUILD" == "no"; then
  AM_CPPFLAGS="-I\$(top_builddir)/include -I$THEPEGPATH/include $CLHEPINCLUDE"
  SETUPTHEPEG="$THEPEGPATH/bin/setupThePEG"
  RUNTHEPEG="$THEPEGPATH/bin/runThePEG"
  THEPEGDOC="$THEPEGPATH/share/ThePEG/Doc"
  THEPEGLIB="$THEPEGPATH/lib/ThePEG"
  AC_MSG_CHECKING([if the installed ThePEG works])
  if test -x $SETUPTHEPEG && $SETUPTHEPEG /dev/null; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR(ThePEG must be installed and THEPEGPATH set properly.)
  fi
fi
AC_ARG_VAR(THEPEGPATH,[The path to where ThePEG is installed. Default is $prefix unless we are working in a sister of the build directory of ThePEG.])

pkglibdir="\$(libdir)/ThePEG"
AC_SUBST(pkglibdir)
AC_SUBST(THEPEGPATH)
AC_SUBST(THEPEGINCLUDE)
AC_SUBST(THEPEGDOC)
AC_SUBST(THEPEGLIB)
AC_SUBST(SETUPTHEPEG)
AC_SUBST(RUNTHEPEG)
AC_SUBST(AM_CPPFLAGS)
])

AC_DEFUN([THEPEG_EMPTY_SUBST],
[EMPTY=""
AC_SUBST(EMPTY)
])

AC_DEFUN([THEPEG_SEARCH_PREFIXDIR_FILES],
[AC_MSG_CHECKING([if $1 and $2 is set])
if test -z "$$1"; then
  for dirbase in / /usr $ac_default_prefix $prefix; do
    if test -z "$$2"; then
      for filename in $4; do
        if test -f $dirbase/$3/$filename; then
          $1=$dirbase/$3
	  $2=$filename
        fi
      done
    else
      if test -f $dirbase/$3/$$2; then
        $1=$dirbase/$3
      fi
    fi
  done
  if test -z "$$1" -o -z "$$2"; then
    AC_MSG_ERROR(no. Could not guess appropriate value for $1 and $2)
  else
    AC_MSG_RESULT([no (found $$1 and $$2)])
  fi
else
  if test -z "$$2"; then
    for filename in $4; do
      if test -f $$1/$filename; then
	  $2=$filename
      fi
    done
    AC_MSG_RESULT([no (found $$1 and $$2)])
  else
    if test -f $$1/$$2; then
      AC_MSG_RESULT([yes ($$1 and $$2)])
    else
      AC_MSG_ERROR(no. Could not guess appropriate value for $1 and $2)
    fi
  fi
fi
AC_ARG_VAR($1,$5)
AC_ARG_VAR($2,$6)
])

AC_DEFUN([THEPEG_CHECK_PREFIXDIR],
[AC_MSG_CHECKING([if $1 is set])
if test -z "$$1"; then
   if test -d $prefix/$2; then
      $1=$prefix/$2
   elif test -d $ac_default_prefix/$2; then
      $1=$ac_default_prefix/$2
   elif test -d /usr/$2; then
      $1=/usr/$2
   elif test -d /$2; then
      $1=/$2
   else
     AC_MSG_ERROR(no. Could not guess appropriate value for $1)
   fi
   AC_MSG_RESULT([no (using $$1)])
else
  AC_MSG_RESULT([yes ($$1)])
fi
AC_ARG_VAR($1,$3)
])


AC_DEFUN([THEPEG_CHECK_ENVDEFAULT],
[AC_MSG_CHECKING([if $1 is set])
if test -z "$$1"; then
  $1="$2"
  AC_MSG_RESULT([no (using $$1)])
else
  AC_MSG_RESULT([yes ($$1)])
fi
AC_ARG_VAR($1,$3)
])

AC_DEFUN([THEPEG_DEFINE_ENVDEFAULT],
[AC_MSG_CHECKING([if $2 is set])
if test -z "$$2"; then
  $2="$3"
  AC_MSG_RESULT([no (using $$2)])
else
  AC_MSG_RESULT([yes ($$2)])
fi
AC_ARG_VAR($2,$4)
AC_DEFINE_UNQUOTED($1,"$$2",[$4])
])

AC_DEFUN([THEPEG_CHECK_EXPM1],
[echo $ECHO_N "checking for expm1... $ECHO_C" 1>&6
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <cmath>
]], [[expm1(1.0);
]])],[AC_DEFINE(ThePEG_HAS_EXPM1,1,define if expm1 is available)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])])

AC_DEFUN([THEPEG_CHECK_LOG1P],
[echo $ECHO_N "checking for log1p... $ECHO_C" 1>&6
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <cmath>
]], [[log1p(1.0);
]])],[AC_DEFINE(ThePEG_HAS_LOG1P,1,define if log1p is available)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])])

AC_DEFUN([THEPEG_CHECK_DLOPEN],
[echo $ECHO_N "checking for dlopen... $ECHO_C" 1>&6
# do this with libtool!
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <dlfcn.h>
]], [[dlopen("", 1);
]])],[AC_DEFINE(ThePEG_HAS_DLOPEN,1,define if dlopen is available)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])])

AC_DEFUN([THEPEG_CHECK_SSTREAM],
[echo $ECHO_N "checking for <sstream>... $ECHO_C" 1>&6
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <sstream>
]], [[std::ostringstream os;
]])],[AC_DEFINE(ThePEG_HAS_SSTREAM,1,define if sstream is available)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])])

AC_DEFUN([THEPEG_CHECK_FPUCONTROL],
[echo $ECHO_N "checking for <fpu_control>... $ECHO_C" 1>&6
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <fpu_control.h>
]], [[fpu_control_t cw; _FPU_GETCW(cw); cw &= ~(_FPU_MASK_IM|_FPU_MASK_DM|_FPU_MASK_ZM|_FPU_MASK_OM); _FPU_SETCW(cw);
]])],[AC_DEFINE(ThePEG_HAS_FPU_CONTROL,1,define if fpucontrol is available)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])])

AC_DEFUN([THEPEG_ADD_THEPEG_PATH],
[if test "$THEPEGBUILD" == "yes"; then
  if test -f "../$2/Config/config.h"; then
    $1="\$(top_builddir)/../$2/lib"
    SETUPTHEPEG="$SETUPTHEPEG -L\$(top_builddir)/../$2/lib"
    RUNTHEPEG="$RUNTHEPEG -L\$(top_builddir)/../$2/lib"
    AM_CPPFLAGS="$AM_CPPFLAGS -I\$(top_builddir)/../$2/include"
  fi
else
  $1="$THEPEGLIB"
fi
AC_SUBST($1)
])

AC_DEFUN([THEPEG_HAS_JAVA],
[  hasjava=yes
   AC_PATH_PROG(JAVAC, javac)
   AC_PATH_PROG(JAVA, java)
   AC_PATH_PROG(JAR, jar)
   if test -z "$JAR" -o -z "$JAVA" -o -z "$JAVAC"; then hasjava=no; else
     AC_MSG_CHECKING([if java works])
     echo 'public class conftest { public static void main(String[[]]arg){}}' > conftest.java
     $JAVAC -source $1 conftest.java 1>&5 2>&5
     if test $? -ne 0; then hasjava=no; fi
     echo "Main-Class: conftest" > conftest.manifest
     $JAR cmf conftest.manifest conftest.jar conftest.class 1>&5 2>&5
     if test $? -ne 0; then hasjava=no; fi
     $JAVA -jar conftest.jar 1>&5 2>&5
     if test $? -ne 0; then hasjava=no; fi
     rm -f conftest.java conftest.err conftest.class conftest.manifest conftest.jar
   fi
   if test "x$hasjava" != "xno"; then
     AC_MSG_RESULT([yes])
     $2
   else
     AC_MSG_RESULT([no])
     $3
   fi
])

AC_DEFUN([THEPEG_LIBTOOL_VERSION_INFO],
[  LIBTOOLVERSIONINFO="-version-info $1:$2:$3"
   AC_SUBST(LIBTOOLVERSIONINFO)])

AC_DEFUN([THEPEG_UNIT_CHECKING],
[
AC_MSG_CHECKING([whether to include dimension checking])
AC_ARG_ENABLE(unitchecks,
        AC_HELP_STRING([--enable-unitchecks],[turns on dimension checking for physical quantities.]),
        [],
        [enable_unitchecks=no]
        )
AC_MSG_RESULT([$enable_unitchecks])
if test "x$enable_unitchecks" = "xyes"; then
   AC_DEFINE([ThePEG_HAS_UNITS_CHECKING],[1],[define if units should be checked])
fi
])
