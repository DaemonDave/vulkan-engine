#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([vulkan-engine], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([src/engine/engine.c])
AC_CONFIG_HEADERS([config.h])

# DRE 2022 - I added missed Automake inclusion because Michael Kerrisk's project because he didn't have the .am file.\
# The command option dist-bzip2 makes this into a distribution and uses bzip2 to compress the project Logger-1.0.tar.bz2 \
# tarballs for sending outside as separately self-configuring initialized projects.
AM_INIT_AUTOMAKE([dist-bzip2 subdir-objects])

# DRE 2022 -Automake initialization MUST GO HERE
# HERE ARE SOME ADD-ONS autoscan couldn't find:
# DRE 2022 - I added missed CANONCICAL HOST that describes the operting system far better than most kludged ones. 
AC_CANONICAL_HOST
# DRE 2022 - I added missed LT_INIT which initializes autoconf and automake to create libraries - all these tools are \
# singular so you don't need them until you do.
LT_INIT
# DRE 2022 - I added missed AC_CONFIG_MACRO_DIRS that describes remake m4 files (m4 is the engine within Autoconf and Automake).
AC_CONFIG_MACRO_DIRS([m4])

m4_include([m4/lib-vulkan.m4])



# Checks for programs.
AC_PROG_CXX
AC_PROG_LEX
AC_PROG_YACC
AC_PROG_CC


# Checks for libraries.
AX_OPENMP

LIB_SETUP_VULKAN


AC_CHECK_LIB([vulkan] , [vkAllocateCommandBuffers] )

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([inttypes.h libintl.h malloc.h stdint.h unistd.h])
# Checks for header files.
AC_PATH_X
AC_CHECK_HEADERS([fcntl.h inttypes.h mach/mach.h stdint.h sys/ioctl.h sys/param.h sys/time.h sys/timeb.h unistd.h])
AC_CHECK_HEADERS([vulkan/vulkan.h])
# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_OFF_T
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])
# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([clock_gettime floor ftruncate gettimeofday memmove memset munmap pow regcomp setlocale sqrt strcasecmp strchr strcspn strerror strrchr strspn strstr strtol strtoul])


AC_CONFIG_FILES([Makefile
                 ])
AC_OUTPUT
