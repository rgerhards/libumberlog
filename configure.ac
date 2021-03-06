dnl Process this file with autoconf to produce a configure script.
dnl

AC_INIT(libumberlog, 0.3.0, algernon@balabit.hu, libumberlog, https://github.com/algernon/libumberlog)
AM_INIT_AUTOMAKE([1.11 foreign tar-ustar no-dist-gzip dist-xz])

dnl ***************************************************************************
dnl dependencies

JSON_C_MIN_VERSION="0.7"

dnl ***************************************************************************
dnl Initial setup

AC_CONFIG_MACRO_DIR([m4])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AM_CONFIG_HEADER(config.h)

dnl ***************************************************************************
dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_STDC
AC_PROG_MAKE_SET
PKG_PROG_PKG_CONFIG
AC_PATH_PROG([RST2MAN], [rst2man])
LT_INIT([shared])

dnl ***************************************************************************
dnl Miscellanneous headers
dnl ***************************************************************************

AC_HEADER_STDC

dnl ***************************************************************************
dnl Header checks
dnl ***************************************************************************
AC_CHECK_HEADERS([syslog.h dlfcn.h limits.h wchar.h])

dnl ***************************************************************************
dnl Checks for libraries
dnl Note that program_invocation_short_name is a variable, not a function; this
dnl currently happens to work fine.
AC_CHECK_FUNCS([gethostname strdup memset __syslog_chk parse_printf_format program_invocation_short_name])

dnl The dlopen() function is in the C library for *BSD and in
dnl libdl on GLIBC-based systems
AC_SEARCH_LIBS([dlopen], [dl dld], [], [
  AC_MSG_ERROR([unable to find the dlopen() function])
])

dnl Similarly, clock_gettime is in the C library on *BSD, and in librt
dnl on GLIBC-based systems.
AC_SEARCH_LIBS([clock_gettime], [rt], [], [
  AC_MSG_ERROR([unable to find the clock_gettime() function])
])

dnl ***************************************************************************
dnl Libraries for the test suite
dnl ***************************************************************************
PKG_CHECK_MODULES(JSON, json >= $JSON_C_MIN_VERSION,[enable_tests="1"],[enable_tests="0"])
if test "x$enable_tests" = "x1"; then
  PKG_CHECK_MODULES(CHECK, check, [enable_tests="1"],[enable_tests="0"])
fi

dnl ***************************************************************************
dnl misc features to be enabled
dnl ***************************************************************************
AC_C_INLINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_PID_T
AC_TYPE_UID_T
AC_TYPE_SIZE_T

AC_ARG_ENABLE([discovery],
  AS_HELP_STRING([--disable-discovery],
                 [Do not implicitly add automatically discovered fields when using the LD_PRELOAD lib [default=enabled]]),
                 [], [enable_discovery=yes])
if test "x$enable_discovery" != xno; then
  DEFAULT_LOG_FLAGS=LOG_UL_ALL
else
  DEFAULT_LOG_FLAGS=LOG_UL_NOIMPLICIT
fi
AC_DEFINE_UNQUOTED([DEFAULT_LOG_FLAGS], [$DEFAULT_LOG_FLAGS],
                   [Default flags for the LD_PRELOAD variant of the library])

AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [package name])
AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [version number])

AM_CONDITIONAL(ENABLE_TESTS, [test "$enable_tests" = "1"])
AM_CONDITIONAL(ENABLE_MANS, [test "x$RST2MAN" != "x"])

AC_OUTPUT(
	Makefile
        data/Makefile
        lib/Makefile
	lib/libumberlog.pc
        t/Makefile
)
