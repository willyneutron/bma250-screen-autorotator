#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([BMA250 Autorotator], [0.1], [willyneutron2@gmail.com], [bma250_autorotator])
AM_INIT_AUTOMAKE([])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([X11], [main])
AC_CHECK_LIB([Xrandr], [main])

# Check for headers
AC_CHECK_HEADERS([stdio.h fcntl.h errno.h unistd.h stdlib.h signal.h string.h linux/i2c-dev.h X11/extensions/Xrandr.h])

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
