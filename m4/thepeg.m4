# check for gcc bug http://gcc.gnu.org/bugzilla/show_bug.cgi?id=34130
AC_DEFUN([THEPEG_CHECK_ABS_BUG],
[
if test "$GCC" = "yes"; then
AC_MSG_CHECKING([for gcc abs bug])
AC_RUN_IFELSE(
	AC_LANG_PROGRAM(
		[ int foo (int i) { return -2 * __builtin_abs(i - 2); }	],
		[ if ( foo(1) != -2 || foo(3) != -2 ) return 1; ]
	),
	[ AC_MSG_RESULT([not found. Compiler is ok.]) ],
	[
	AC_MSG_RESULT([found. Builtin abs() is buggy.])
	AC_MSG_CHECKING([if -fno-builtin-abs works])
	oldcxxflags=$CXXFLAGS
	CXXFLAGS="$CXXFLAGS -fno-builtin-abs"
	AC_RUN_IFELSE(
		AC_LANG_PROGRAM(
			[
			#include <cstdlib>
			int foo (int i) { return -2 * std::abs(i - 2); }
			],
			[
			if (foo(1) != -2 || foo(3) != -2) return 1; 
			]
		),
		[
		AC_MSG_RESULT([yes. Setting -fno-builtin-abs.])
		AM_CXXFLAGS="$AM_CXXFLAGS -fno-builtin-abs"
		AM_CFLAGS="$AM_CFLAGS -fno-builtin-abs"
		],
		[
		AC_MSG_RESULT([no. Setting -fno-builtin.])
		AC_MSG_WARN([
*****************************************************************************
For this version of gcc, -fno-builtin-abs alone did not work to avoid the 
gcc abs() bug. Instead, all gcc builtin functions are now disabled.
Update gcc if possible.
*****************************************************************************])
		AM_CXXFLAGS="$AM_CXXFLAGS -fno-builtin"
		AM_CFLAGS="$AM_CFLAGS -fno-builtin"
		]
	)
	CXXFLAGS=$oldcxxflags
	]
)
fi
])

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
  if test -e $LHAPDF_LIBDIR/libLHAPDF.so -o -e $LHAPDF_LIBDIR/libLHAPDF.dylib
  then
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
  LHAPDF_PKGDATADIR="$LHAPDF_LIBDIR/../share/lhapdf"
  dnl don't need to check for existence of LHAPDF_PKGDATADIR
  dnl if this location is invalid, we'll use ThePEG's index file anyway
elif test "x$with_LHAPDF" == "xno" -o "x$with_LHAPDF" == "x"; then
  AC_MSG_RESULT([no])
else
  AC_MSG_ERROR([LHAPDF was requested but the library was not found.])
fi

AC_SUBST(LHAPDF_LIBS)
AC_SUBST(LHAPDF_LDFLAGS)
AC_SUBST(LHAPDF_PKGDATADIR)
AM_CONDITIONAL([USELHAPDF], [test "x$HAS_LHAPDF" == "xyes"])
])

dnl ##### HEPMC #####
AC_DEFUN([THEPEG_CHECK_HEPMC],
[
AC_MSG_CHECKING([for HepMC location])
HEPMCINCLUDE=""
HEPMCLIBS="-lHepMC"

AC_ARG_WITH(hepmc,
        AC_HELP_STRING([--with-hepmc=DIR],[Location of HepMC installation @<:@default=system libs@:>@]),
        [],
	[with_hepmc=system])

if test "x$with_hepmc" = "xno"; then
	AC_MSG_RESULT([HepMC support disabled.])
elif test "x$with_hepmc" = "xsystem"; then
        AC_MSG_RESULT([in system libraries])
	oldlibs="$LIBS"
	AC_CHECK_LIB(HepMC,main,
		[],
		[with_hepmc=no
		 AC_MSG_WARN([
HepMC not found in system libraries])
		])
	HEPMCLIBS="$LIBS"
	LIBS=$oldlibs
else
	AC_MSG_RESULT([$with_hepmc])
	HEPMCINCLUDE=-I$with_hepmc/include
	HEPMCLIBS="-L$with_hepmc/lib -R$with_hepmc/lib -lHepMC"
fi

if test "x$with_hepmc" != "xno"; then
	# Now lets see if the libraries work properly
	oldLIBS="$LIBS"
	oldLDFLAGS="$LDFLAGS"
	oldCPPFLAGS="$CPPFLAGS"
	LIBS="$LIBS $HEPMCLIBS"
	LDFLAGS="$LDFLAGS"
	CPPFLAGS="$CPPFLAGS $HEPMCINCLUDE"

	# check HepMC
	AC_MSG_CHECKING([that HepMC works])
	AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <HepMC/GenEvent.h>
]],[[HepMC::GenEvent();]])],[AC_MSG_RESULT([yes])],[AC_MSG_RESULT([no]) 
	AC_MSG_ERROR([Use '--with-hepmc=' to set a path or use '--without-hepmc'.])
	])

	AC_CHECK_HEADERS([HepMC/PdfInfo.h],[],[AC_MSG_ERROR([Need HepMC with PdfInfo support.])],[#include <algorithm>])
	AC_CHECK_HEADERS([HepMC/IO_GenEvent.h])
	AC_CHECK_HEADERS([HepMC/IO_ExtendedAscii.h])

	LIBS="$oldLIBS"
	LDFLAGS="$oldLDFLAGS"
	CPPFLAGS="$oldCPPFLAGS"
fi

AM_CONDITIONAL(HAVE_HEPMC,[test "x$with_hepmc" != "xno"])
AC_SUBST(HEPMCINCLUDE)
AC_SUBST(HEPMCLIBS)
AC_SUBST(CREATE_HEPMC)
AC_SUBST(LOAD_HEPMC)
])

dnl ##### RIVET #####

AC_DEFUN([THEPEG_CHECK_RIVET],
[
AC_REQUIRE([THEPEG_CHECK_HEPMC])
AC_MSG_CHECKING([for Rivet location])
RIVETINCLUDE=""
RIVETLIBS="-lRivet"

AC_ARG_WITH(Rivet,
        AC_HELP_STRING([--with-Rivet=DIR],[Location of Rivet installation @<:@default=system libs@:>@]),
        [],
	[with_Rivet=system])

if test "x$with_Rivet" = "xno"; then
	AC_MSG_RESULT([Rivet support disabled.])
elif test "x$with_hepmc" = "xsystem"; then
        AC_MSG_RESULT([in system libraries])
	oldlibs="$LIBS"
	AC_CHECK_LIB(Rivet,main,
		[],
		[with_Rivet=no
		 AC_MSG_WARN([
Rivet not found in system libraries])
		])
	RIVETLIBS="$LIBS"
	LIBS=$oldlibs
else
	AC_MSG_RESULT([$with_Rivet])
	RIVETINCLUDE=-I$with_Rivet/include
	RIVETLIBS="-L$with_Rivet/lib -R$with_Rivet/lib -lRivet"
fi

if test "x$with_Rivet" != "xno"; then
	# Now lets see if the libraries work properly
	oldLIBS="$LIBS"
	oldLDFLAGS="$LDFLAGS"
	oldCPPFLAGS="$CPPFLAGS"
	LIBS="$LIBS $HEPMCLIBS $RIVETLIBS"
	LDFLAGS="$LDFLAGS"
	CPPFLAGS="$CPPFLAGS $RIVETINCLUDE"

	# check Rivet
	AC_MSG_CHECKING([that Rivet works])
	AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <Rivet/AnalysisHandler.hh>
]],[[Rivet::GenEvent();]])],[AC_MSG_RESULT([yes])],[AC_MSG_RESULT([no]) 
	AC_MSG_ERROR([Use '--with-Rivet=' to set a path or use '--without-Rivet'.])
	])

	LIBS="$oldLIBS"
	LDFLAGS="$oldLDFLAGS"
	CPPFLAGS="$oldCPPFLAGS"
fi

AM_CONDITIONAL(HAVE_RIVET,[test "x$with_Rivet" != "xno"])
AC_SUBST(RIVETINCLUDE)
AC_SUBST(RIVETLIBS)
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
    AM_CPPFLAGS="-I\$(top_builddir)/include -I\$(top_builddir)/../ThePEG/include "
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
  AM_CPPFLAGS="-I\$(top_builddir)/include -I$THEPEGPATH/include "
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
    AM_CPPFLAGS="-I\$(top_builddir)/include -I\$(top_builddir)/../ThePEG/include "
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
  AM_CPPFLAGS="-I\$(top_builddir)/include -I$THEPEGPATH/include "
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

AC_DEFUN([THEPEG_CHECK_AIDA],
[
echo $ECHO_N "checking for installed AIDA headers... $ECHO_C" 1>&6
if $HAVE_RIVET; then
   echo "using rivet aida"
else
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include "AIDA/IAnalysisFactory.h"
]], [[AIDA::IAnalysisFactory * af;
]])],[AC_DEFINE(LWH_USING_AIDA,1,define if AIDA headers are installed)
echo "${ECHO_T}yes" 1>&6
],[echo "${ECHO_T}no" 1>&6])
fi
])

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

AC_DEFUN([THEPEG_CHECK_GSL],
[
AC_MSG_CHECKING([for gsl location])
GSLINCLUDE=""
GSLLIBS=""

AC_ARG_WITH(gsl,
        AC_HELP_STRING([--with-gsl=path],[location of gsl installation. Default: system lib]),
        [],
	[with_gsl=system])

if test "x$with_gsl" = "xno"; then
AC_MSG_ERROR([libgsl is required. Please install the GNU scientific library and header files.])
fi

if test "x$with_gsl" = "xsystem"; then
	AC_MSG_RESULT([in system libraries])
	oldlibs="$LIBS"
	AC_CHECK_LIB(m,sqrt)
	AC_CHECK_LIB(gslcblas,cblas_srot)
	AC_CHECK_LIB(gsl,gsl_ran_poisson,[],
			[
			AC_MSG_ERROR([Cannot find libgsl. Please install the GNU scientific library.])
			]
		     )
	GSLLIBS="$LIBS"
	LIBS=$oldlibs
else
	if test "`uname -m`" = "x86_64" -a -e "$with_gsl/lib64/libgsl.a" -a -d "$with_gsl/include/gsl"; then
		AC_MSG_RESULT([found in $with_gsl])
		GSLLIBS="-L$with_gsl/lib64 -R$with_gsl/lib64 -lgslcblas -lgsl"
		GSLINCLUDE="-I$with_gsl/include"
	elif test -e "$with_gsl/lib/libgsl.a" -a -d "$with_gsl/include/gsl"; then
		AC_MSG_RESULT([found in $with_gsl])
		GSLLIBS="-L$with_gsl/lib -R$with_gsl/lib -lgslcblas -lgsl"
		GSLINCLUDE="-I$with_gsl/include"
	else
		AC_MSG_RESULT([not found])
		AC_MSG_ERROR([Can't find $with_gsl/lib/libgsl.a or the headers in $with_gsl/include])
	fi
fi

dnl AM_CONDITIONAL(HAVE_GSL,[test "x$with_HepMC" != "xno"])
AC_SUBST(GSLINCLUDE)
AC_SUBST(GSLLIBS)
])

AC_DEFUN([THEPEG_OVERVIEW],
[
CXXSTRING=`$CXX --version | head -1`
cat << _THEPEG_EOF_ > config.thepeg
*****************************************************
*** $PACKAGE_STRING configuration summary
*** Please include this information in bug reports!
***--------------------------------------------------
*** Prefix:		$prefix
***
*** Dimension checks:	$enable_unitchecks
***
*** GSL:		$with_gsl
***
*** LHAPDF:		$with_LHAPDF
***
*** HepMC:		$with_hepmc
***
*** RIVET:		$with_Rivet
***
*** Host:		$host
*** CXX:		$CXXSTRING
*****************************************************
_THEPEG_EOF_
])
