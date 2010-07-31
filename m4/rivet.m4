dnl ##### RIVET #####
AC_DEFUN([THEPEG_CHECK_RIVET],
[
AC_REQUIRE([THEPEG_CHECK_HEPMC])
AC_MSG_CHECKING([for Rivet location])
RIVETINCLUDE=""
LOAD_RIVET=""
RIVETLIBS="-lRivet"

AC_ARG_WITH(rivet,
        AC_HELP_STRING([--with-rivet=DIR],[Location of Rivet installation @<:@default=system libs@:>@]),
        [],
	[with_rivet=system])

if test "x$with_hepmc" = "xno"; then
	with_rivet=no
fi
 	
if test "x$with_rivet" = "xno"; then
	AC_MSG_RESULT([Rivet support disabled.])
elif test "x$with_rivet" = "xsystem"; then
        AC_MSG_RESULT([in system libraries])
	oldlibs="$LIBS"
	LIBS="$LIBS $HEPMCLIBS"
	AC_CHECK_LIB(Rivet,main,
		[],
		[with_rivet=no
		 AC_MSG_WARN([Rivet not found in system libraries])
		])
	RIVETLIBS="$LIBS"
	LIBS=$oldlibs
else
	AC_MSG_RESULT([$with_rivet])
	RIVETINCLUDE=-I$with_rivet/include
	RIVETLIBS="-L$with_rivet/lib -R$with_rivet/lib -lRivet"
fi

if test "x$with_rivet" != "xno"; then
        LOAD_RIVET="library RivetAnalysis.so"
	# Now lets see if the libraries work properly
	oldLIBS="$LIBS"
	oldLDFLAGS="$LDFLAGS"
	oldCPPFLAGS="$CPPFLAGS"
	LIBS="$LIBS $HEPMCLIBS $RIVETLIBS"
	LDFLAGS="$LDFLAGS"
	CPPFLAGS="$CPPFLAGS $HEPMCINCLUDE $RIVETINCLUDE"

	# check Rivet
	AC_MSG_CHECKING([that Rivet works])
	AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <Rivet/AnalysisHandler.hh>
]],[[Rivet::GenEvent();]])],[AC_MSG_RESULT([yes])],[AC_MSG_RESULT([no]) 
	AC_MSG_RESULT([No. Use '--with-rivet=' to set a path'.])
	with_rivet="no"
	LOAD_RIVET=""
	])

	LIBS="$oldLIBS"
	LDFLAGS="$oldLDFLAGS"
	CPPFLAGS="$oldCPPFLAGS"
fi

AM_CONDITIONAL(HAVE_RIVET,[test "x$with_rivet" != "xno"])
AC_SUBST(RIVETINCLUDE)
AC_SUBST(RIVETLIBS)
AC_SUBST(LOAD_RIVET)
])
