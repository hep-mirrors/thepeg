# Check for CLHEP.
AC_DEFUN([AC_CHECK_CLHEP],
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
AC_DEFUN([AC_CHECK_THEPEG],
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
AC_SUBST(SETUPTHEPEG)
AC_SUBST(RUNTHEPEG)
AC_SUBST(AM_CPPFLAGS)
])

# Check for CLHEP.
AC_DEFUN([AC_EMPTY_SUBST],
[EMPTY=""
AC_SUBST(EMPTY)
])

AC_DEFUN([AC_CHECK_PREFIXDIR],
[AC_MSG_CHECKING([if $1 is set])
if test -z "$$1"; then
   if test "x$prefix" == "xNONE"; then
      $1=$ac_default_prefix/$2
   else
      $1=$prefix/$2
   fi
   AC_MSG_RESULT([no (using $$1)])
else
  AC_MSG_RESULT([yes ($$1)])
fi
AC_ARG_VAR($1,$3)
])


AC_DEFUN([AC_CHECK_ENVDEFAULT],
[AC_MSG_CHECKING([if $1 is set])
if test -z "$$1"; then
  $1="$2"
  AC_MSG_RESULT([no (using $$1)])
else
  AC_MSG_RESULT([yes ($$1)])
fi
AC_ARG_VAR($1,$3)
])

AC_DEFUN([AC_DEFINE_ENVDEFAULT],
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

AC_DEFUN([AC_CHECK_EXPM1],
[echo $ECHO_N "checking for expm1... $ECHO_C" 1>&6
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <cmath>
]], [[expm1(1.0);
]])],[AC_DEFINE(ThePEG_HAS_EXPM1,1,define if expm1 is available)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])])

AC_DEFUN([AC_CHECK_LOG1P],
[echo $ECHO_N "checking for log1p... $ECHO_C" 1>&6
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <cmath>
]], [[log1p(1.0);
]])],[AC_DEFINE(ThePEG_HAS_LOG1P,1,define if log1p is available)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])])

AC_DEFUN([AC_CHECK_DLOPEN],
[echo $ECHO_N "checking for dlopen... $ECHO_C" 1>&6
# do this with libtool!
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <dlfcn.h>
]], [[dlopen("", 1);
]])],[AC_DEFINE(ThePEG_HAS_DLOPEN,1,define if dlopen is available)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])])

AC_DEFUN([AC_CHECK_SSTREAM],
[echo $ECHO_N "checking for <sstream>... $ECHO_C" 1>&6
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <sstream>
]], [[std::ostringstream os;
]])],[AC_DEFINE(ThePEG_HAS_SSTREAM,1,define if sstream is available)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])])

AC_DEFUN([AC_CHECK_FPUCONTROL],
[echo $ECHO_N "checking for <fpu_control>... $ECHO_C" 1>&6
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <fpu_control.h>
]], [[fpu_control_t cw; _FPU_GETCW(cw); cw &= ~(_FPU_MASK_IM|_FPU_MASK_DM|_FPU_MASK_ZM|_FPU_MASK_OM); _FPU_SETCW(cw);
]])],[AC_DEFINE(ThePEG_HAS_FPU_CONTROL,1,define if fpucontrol is available)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])])

AC_DEFUN([AC_ADD_THEPEG_PATH],
[if test "$THEPEGBUILD" == "yes"; then
  if test -f "../$2/Config/config.h"; then
    $1="\$(top_builddir)/../$2"
    SETUPTHEPEG="$SETUPTHEPEG -L\$(top_builddir)/../$2/lib"
    RUNTHEPEG="$RUNTHEPEG -L\$(top_builddir)/../$2/lib"
    AM_CPPFLAGS="$AM_CPPFLAGS -I\$(top_builddir)/../$2/include"
  fi
else
  $1="$THEPEGPATH"
fi
AC_SUBST($1)
])

