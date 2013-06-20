# lhapdf.m4 based on fastjet.m4
# D.Grellscheid 2013-06-20

# Search for LHAPDF and g77 compiler in standard directories
AC_DEFUN([THEPEG_SEARCH_LHAPDF],
[
dnl ckeck if a directory is specified for LHAPDF
AC_ARG_WITH(lhapdf,
            [AC_HELP_STRING([--with-lhapdf=dir], 
                            [Assume the given directory for LHAPDF])])

dnl search for the lhapdf-config script
if test "$with_lhapdf" = ""; then
   AC_PATH_PROG(lhaconfig, lhapdf-config, no)
else
   AC_PATH_PROG(lhaconfig, lhapdf-config, no, ${with_lhapdf}/bin)
fi

LOAD_LHAPDF=""

if test "${lhaconfig}" = "no"; then
   AC_MSG_CHECKING([LHAPDF])
   AC_MSG_RESULT([no]);
   $2
else

   dnl now see if LHAPDF is functional
   save_LDFLAGS="$LDFLAGS"
   save_LIBS="$LIBS"

   LDFLAGS="${LDFLAGS} -L`${lhaconfig} --libdir`"
   LIBS="${LIBS} -lLHAPDF"

   AC_MSG_CHECKING([if LHAPDF is functional])
   AC_LANG_PUSH(C++)
   AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[extern "C" { void initpdf_(int&); }]], 
   				      [[int i = 1; initpdf_(i);]])], 
				      [lhaok='yes'], [lhaok='no'])
   AC_MSG_RESULT([$lhaok])
   AC_LANG_POP()
   LDFLAGS="$save_LDFLAGS"
   LIBS="$save_LIBS"

   AC_MSG_CHECKING([LHAPDF])
   if test "${lhaok}" = "yes"; then
      LHAPDF_LDFLAGS="-L`${lhaconfig} --libdir`"
      LHAPDF_LIBS="-lLHAPDF"
      LOAD_LHAPDF="library ThePEGLHAPDF.so"
      AC_MSG_RESULT(yes)
      $1
   else
      AC_MSG_RESULT(no)
      $2
   fi
fi

AC_SUBST([LHAPDF_LIBS])
AC_SUBST(LOAD_LHAPDF)
AC_SUBST(LHAPDF_LDFLAGS)
AC_SUBST(LHAPDF_PKGDATADIR,[`${lhaconfig} --datadir`])
AM_CONDITIONAL(USELHAPDF,[test "x$LOAD_LHAPDF" = "xlibrary ThePEGLHAPDF.so"])
])
