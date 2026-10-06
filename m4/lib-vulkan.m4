#
# Copyright (c) 2025, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2025, JetBrains s.r.o.. All rights reserved.
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
#
# This code is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 2 only, as
# published by the Free Software Foundation.  Oracle designates this
# particular file as subject to the "Classpath" exception as provided
# by Oracle in the LICENSE file that accompanied this code.
#

################################################################################
# Locate a tool using the PATH or an explicitly supplied directory.
#
# $1: variable to set
# $2: executable name, or whitespace-separated list of names
# $3: optional directory to search
# $4: optional argument passed to UTIL_FIXUP_EXECUTABLE
################################################################################
################################################################################
# Locate a tool using the PATH or an explicitly supplied directory.
#
# $1: variable to set
# $2: executable name, or whitespace-separated list of names
# $3: optional directory to search
# $4: optional argument passed to UTIL_FIXUP_EXECUTABLE
################################################################################
################################################################################
# Locate a tool using the PATH or an explicitly supplied directory.
#
# $1: variable to set
# $2: executable name, or whitespace-separated list of names
# $3: optional directory to search
# $4: optional argument passed to UTIL_FIXUP_EXECUTABLE
################################################################################
AC_DEFUN([UTIL_LOOKUP_PROGS],
[
  $1=""

  if test -n "$3"; then
    util_lookup_old_path="$PATH"
    PATH="$3"
  fi

  for name in $2; do
    AC_MSG_CHECKING([for $name])

    # First detect shell builtins and keywords.
    command_type=`type "$name" 2>/dev/null`
    case "$command_type" in
      *" is a shell builtin"*|*" is a keyword"*)
        $1="$name"
        AC_MSG_RESULT([$name [builtin]])
        break
        ;;
    esac

    util_lookup_old_ifs="$IFS"
    IFS=:

    for elem in $PATH; do
      IFS="$util_lookup_old_ifs"

      # An empty PATH element means the current directory.
      if test -z "$elem"; then
        elem=.
      fi

      full_path="$elem/$name"

      if test ! -f "$full_path" \
          && test "x$OPENJDK_BUILD_OS" = xwindows; then
        full_path="$elem/$name.exe"
      fi

      if test -x "$full_path" && test ! -d "$full_path"; then
        $1="$full_path"

	result="[$]$1"

	# Normalize a FIXPATH prefix if required.
	if test -n "$FIXPATH"; then
	  case "$result" in
	    "$FIXPATH "*)
	      result="$FIXPATH ${result#"$FIXPATH "}"
	      ;;
	  esac
	fi
        result="[$]$1"

        # Normalize a FIXPATH prefix.
        if test -n "$FIXPATH"; then
          case "$result" in
            "$FIXPATH "*)
              result="$FIXPATH ${result#"$FIXPATH "}"
              ;;
          esac
        fi

        AC_MSG_RESULT([$result])
        break 2
      fi

      IFS=:
    done

    IFS="$util_lookup_old_ifs"

    if test "x[$]$1" = x; then
      AC_MSG_RESULT([not found])
    fi
  done

  if test -n "$3"; then
    PATH="$util_lookup_old_path"
  fi
])

################################################################################
# Locate a tool using the PATH or an explicitly supplied directory.
#
# $1: variable to set
# $2: executable name, or whitespace-separated list of names
# $3: optional directory to search
# $4: optional argument passed to UTIL_FIXUP_EXECUTABLE
################################################################################


################################################################################
# Setup Vulkan
################################################################################
AC_DEFUN_ONCE([LIB_SETUP_VULKAN],
[
  AC_ARG_WITH(
    [vulkan],
    [AS_HELP_STRING(
      [--with-vulkan],
      [specify whether Vulkan support is enabled]
    )]
  )

  AC_ARG_WITH(
    [vulkan-include],
    [AS_HELP_STRING(
      [--with-vulkan-include],
      [specify the directory containing vulkan/vulkan.h]
    )]
  )

  AC_ARG_WITH(
    [vulkan-shader-compiler],
    [AS_HELP_STRING(
      [--with-vulkan-shader-compiler],
      [specify the shader compiler to use: glslc or glslangValidator]
    )]
  )

  AC_ARG_VAR(
    [VULKAN_SDK],
    [path to the Vulkan SDK]
  )

  VULKAN_ENABLED=false
  VULKAN_FLAGS=
  VULKAN_SHADER_COMPILER=

  # Vulkan is required when explicitly enabled, when an include directory
  # was specified, or when another configure option requires libvulkan.
  if test "x$NEEDS_LIB_VULKAN" = xtrue \
      || test "x$with_vulkan" = xyes \
      || test -n "$with_vulkan_include"; then

    # Check a custom include directory first.
    if test -n "$with_vulkan_include"; then
      AC_MSG_CHECKING(
        [for $with_vulkan_include/vulkan/vulkan.h]
      )

      if test -s "$with_vulkan_include/vulkan/vulkan.h"; then
        VULKAN_ENABLED=true
        VULKAN_FLAGS="-I$with_vulkan_include"
        AC_MSG_RESULT([yes])
      else
        AC_MSG_RESULT([no])
        AC_MSG_ERROR(
          [Can't find vulkan/vulkan.h under '$with_vulkan_include']
        )
      fi
    fi

    # Check the Vulkan SDK.
    if test "x$VULKAN_ENABLED" = xfalse \
        && test -n "$VULKAN_SDK"; then
      AC_MSG_CHECKING(
        [for $VULKAN_SDK/include/vulkan/vulkan.h]
      )

      if test -s "$VULKAN_SDK/include/vulkan/vulkan.h"; then
        VULKAN_ENABLED=true
        VULKAN_FLAGS="-I$VULKAN_SDK/include"
        AC_MSG_RESULT([yes])
      else
        AC_MSG_RESULT([no])
      fi
    fi

    # Check the system include directories.
    if test "x$VULKAN_ENABLED" = xfalse; then
      vulkan_save_CPPFLAGS="$CPPFLAGS"
      CPPFLAGS="$CPPFLAGS $VULKAN_FLAGS"

      AC_CHECK_HEADERS(
        [vulkan/vulkan.h],
        [VULKAN_ENABLED=true],
        [VULKAN_ENABLED=false]
      )

      CPPFLAGS="$vulkan_save_CPPFLAGS"
    fi

    if test "x$VULKAN_ENABLED" = xfalse; then
      AC_MSG_ERROR([Could not find Vulkan! $HELP_MSG])
    fi
  fi

  # Find a Vulkan shader compiler.
  if test "x$VULKAN_ENABLED" = xtrue; then
    SHADER_COMPILER=

    case "$with_vulkan_shader_compiler" in
      ""|glslc)
        UTIL_LOOKUP_PROGS([GLSLC], [glslc])

        if test -n "$GLSLC"; then
          SHADER_COMPILER="$GLSLC"
          VULKAN_SHADER_COMPILER="$GLSLC --target-env=vulkan1.3 -mfmt=num"
        fi
        ;;&

      ""|glslangValidator)
        if test -z "$SHADER_COMPILER"; then
          UTIL_LOOKUP_PROGS([GLSLANG], [glslangValidator])

          if test -n "$GLSLANG"; then
            SHADER_COMPILER="$GLSLANG"
            VULKAN_SHADER_COMPILER="$GLSLANG --target-env vulkan1-x"
          fi
        fi
        ;;
      
      *)
        AC_MSG_ERROR(
          [Unsupported Vulkan shader compiler '$with_vulkan_shader_compiler'; use glslc or glslangValidator]
        )
        ;;
    esac

    if test -z "$SHADER_COMPILER"; then
      VULKAN_ENABLED=false
      VULKAN_FLAGS=
      VULKAN_SHADER_COMPILER=
      AC_MSG_ERROR([Can't find a Vulkan shader compiler])
    fi
  fi

  AC_SUBST([VULKAN_ENABLED])
  AC_SUBST([VULKAN_FLAGS])
  AC_SUBST([VULKAN_SHADER_COMPILER])
])
