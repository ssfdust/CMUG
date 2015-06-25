#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(China Mobile Connector, alpha, https://github.com/ssfdust/CMUG)
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE(cmug, alpha)

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h memory.h stdint.h stdlib.h string.h sys/timeb.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([ftime memset strstr])

AC_OUTPUT([Makefile
						src/Makefile
						])
