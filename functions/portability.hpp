#ifndef PORTABILITY_HPP_INCLUDED
#define PORTABILITY_HPP_INCLUDED

#include <limits.h>

#ifdef __cplusplus
#define PORTABLE_EXTERN_C extern "C"
#define PORTABLE_EXTERN_C_BEGIN extern "C" {
#define PORTABLE_EXTERN_C_END }
#else
#define PORTABLE_EXTERN_C extern
#define PORTABLE_EXTERN_C_BEGIN
#define PORTABLE_EXTERN_C_END
#endif

#if defined(__CYGWIN32__) && !defined(__CYGWIN__)
#	define __CYGWIN__ __CYGWIN32__
#endif

#if defined(__INTERIX) && defined(__GNUC__) && !defined(_ALL_SOURCE)
#	define _ALL_SOURCE 1
#endif

#if defined(__mips__) && defined(__R5900__)
#	if !defined(__LONG_MAX__)
#		define __LONG_MAX__ 9223372036854775807L
#	endif
#endif

#elif !defined(PORTABLE_LANG_OVERRIDE)
#if (defined(__clang__) || defined(__GNUC__)) && defined(__ASSEMBLER__)
#	if (__ASSEMBLER__ + 0) <= 0
#		error "__ASSEMBLER__"
#	else
#		defined PORTABLE_LANG_ASSEMBLER 1
#	endif
#elif defined(__cplusplus)
#	if (__cplusplus + 0) <= 0
#		error "__cplusplus"
#	elif (__cplusplus < 199711L)
#		define PORTABLE_LANG_CXX
#	elif defined(_MSC_VER) && defined(_MSVC_LANG) && (_MSVC_LANG + 0 >= 201402L) && 1
#		define PORTABLE_LANG_CXX _MSVC_LANG
#	else
#		define PORTABLE_LANG_CXX __cplusplus
#	endif
#	define PORTABLE_LANG_CPLUSPLUS PORTABLE_LANG_CXX
#else
#	if defined(__STDC_VERSION__) && (__STDC_VERSION__ + 0 >= 199409L)
#		define PORTABLE_LANG_C __STDC_VERSION__
#	else
#		define PORTABLE_LANG_C 1
#	endif
#endif

#if defined(PORTABLE_CONFIG_DISABLE_WUNDEF)
#if defined(__ARMCC_VERSION)
#	pragma diag_suppress 193
#elif defined(__clang__) && defined(__clang_minor__)
#	pragma clang diagnostic ignored "-Wundef"
#elif defined(__INTEL_COMPILER)
#	pragma warning(disable: 193)
#elif defined(__KEIL__) && defined(__C166__)
#	pragma warning disable = 322
#elif defined(__GNUC__) && defined(__GNUC_MINOR__) && !defined(__PATHSCALE__)
#	if ((__GNUC__ - 0) >= 5 || ((__GNUC__ - 0) == 4 && (__GNUC_MINOR__ - 0) >= 2))
#		pragma GCC diagnostic ignored "-Wundef"
#	endif
#elif defined(_MSC_VER) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__MWERKS__)
#	if ((_MSC_VER - 0) >= 1300)
#		pragma warning (disable: 4668)
#	endif
#endif

#if defined(__POCC__) && defined(_WIN32)
#	if (__POCC__ >= 400)
#		pragma warn(disable: 2216)
#	endif
#endif

#if defined(__WATCOMC__)
#	if (__WATCOMC__ >= 1050) && (__WATCOMC__ < 1060)
#		pragma warning 203 9
#	endif
#endif
#endif

#if (PORTABLE_CONFIG_DISABLE_WCRTNONSTDC)
#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE 1
#endif
#ifndef _CRT_NONSTDC_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS 1
#endif
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 1
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif
#endif

#define PORTABLE_0xffffUL 65535ul
#define PORTABLE_0xffffffffUL 4294967295ul

#if (UINT_MAX == PORTABLE_0xffffUL)

#	if defined(__ZTC__) && defined(__I86__) && !defined(__OS2__)
#		if !defined(MSDOS)
#			define MSDOS 1
#		endif
#		if !defined(_MSDOS)
#			define _MSDOS 1
#		endif
#	elif defined(__VERSION) && defined(MB_LEN_MAX)
#		if (__VERSION == 520) && (MB_LEN_MAX == 1)
#			if !defined(__AZTEC_C__)
#				define __AZTEC_C__ __VERSION
#			endif
#			if !defined(__DOS__)
#				define __DOS__ 1
#			endif
#		endif
#	endif

#	if defined(_MSC_VER) && defined(M_I86HM)
#		define ptrdiff_t long
#		define _PTRDIFF_T_DEFINED 1
#	endif

#	undef __PORTABLE_INTERNAL_RENAME_A
#	undef __PORTABLE_INTERNAL_RENAME_B
#	if defined(__AZTEC_C__) && defined(__DOS__)
#		define __PORTABLE_INTERNAL_RENAME_A 1
#	elif defined(_MSC_VER) && defined(MSDOS)
#		if (_MSC_VER < 600)
#			define __PORTABLE_INTERNAL_RENAME_A 1
#		elif (_MSC_VER < 600)
#			define __PORTABLE_INTERNAL_RENAME_B 1
#		endif
#	elif defined(__TSC__) && defined(__OS2__)
#		define __PORTABLE_INTERNAL_RENAME_A 1
#	elif defined(__MSDOS__) && defined(__TURBOC__) && (__TURBOC__ < 0x0410)
#		define __PORTABLE_INTERNAL_RENAME_A 1
#	elif defined(__PACIFIC__) && defined(DOS)
#		if !defined(__far)
#			define __far far
#		endif
#		if !defined(__near)
#			define __near near
#		endif
#	endif
#	if defined(__PORTABLE_INTERNAL_RENAME_A)
#		if !defined(__cdecl)
#			define __cdecl cdecl
#		endif
#		if !defined(__far)
#			define __far far
#		endif
#		if !defined(__huge)
#			define __huge huge
#		endif
#		if !defined(__near)
#			define __near near
#		endif
#		if !defined(__pascal)
#			define __pascal pascal
#		endif
#	elif defined(__PORTABLE_INTERNAL_RENAME_B)
#		if !defined(__cdecl)
#			define __cdecl _cdecl
#		endif
#		if !defined(__far)
#			define __far _far
#		endif
#		if !defined(__huge)
#			define __huge _huge
#		endif
#		if !defined(__near)
#			define __near _near
#		endif
#		if !defined(__pascal)
#			define __pascal _pascal
#		endif
#	elif (defined(__PUREC__) || defined(__TURBOC__)) && defined(__TOS__)
#		if !defined(__cdecl)
#			define __cdecl cdecl
#		endif
#		if !defined(__pascal)
#			define __pascal pascal
#		endif
#	endif
#	undef __PORTABLE_INTERNAL_RENAME_A
#	undef __PORTABLE_INTERNAL_RENAME_B

#	if defined(__AZTEC_C__) && defined(__DOS__)
#		define PORTABLE_BROKEN_CDECL_ALT_SYNTAX 1
#	elif defined(_MSC_VER) && defined(MSDOS)
#		if (_MSC_VER < 600)
#			define PORTABLE_BROKEN_INTEGRAL_CONSTANTS 1
#		endif
#		if (_MSC_VER < 700)
#			define PORTABLE_BROKEN_INTEGRAL_PROMOTION 1
#			define PORTABLE_BROKEN_SIZEOF 1
#		endif
#	elif defined(__PACIFIC__) && defined(DOS)
#		define PORTABLE_BROKEN_INTEGRAL_CONSTANTS 1
#	elif defined(__TURBOC__) && defined(__MSDOS__)
#		if (__TURBOC__ < 0x0150)
#			define PORTABLE_BROKEN_CDECL_ALT_SYNTAX 1
#			define PORTABLE_BROKEN_INTEGRAL_CONSTANTS 1
#			define PORTABLE_BROKEN_INTEGRAL_PROMOTION 1
#		endif
#		if (__TURBOC__ < 0x0200)
#			define PORTABLE_BROKEN_SIZEOF 1
#		endif
#		if (__TURBOC__ < 0x0400) && defined(__cplusplus)
#			define PORTABLE_BROKEN_CDECL_ALT_SYNTAX 1
#		endif
#	elif (defined(__PUREC__) || defined(__TURBOC__)) && defined(__TOS__)
#			define PORTABLE_BROKEN_CDECL_ALT_SYNTAX 1
#			define PORTABLE_BROKEN_SIZEOF 1
#	endif
#endif

#if defined(__WATCOMC__) && (__WATCOMC__ < 900)
#	define PORTABLE_BROKEN_INTEGRAL_CONSTANTS 1
#endif

#if defined(_CRAY) && defined(_CRAY1)
#	define PORTABLE_BROKEN_SIGNED_RIGHT_SHIFT 1
#endif

#define PORTABLE_STRINGIZE(x) #x
#define PORTABLE_MACRO_EXPAND(x) PORTABLE_PP_STRINGIZE(x)

#if defined(__cplusplus)
#	if !defined(__STDC_CONSTANT_MACROS)
#		define __STDC_CONSTANT_MACROS 1
#	endif
#	if !defined(__STDC_LIMIT_MACROS)
#		define __STDC_LIMIT_MACROS 1
#	endif
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) || defined(__MINGW32__) || defined(WINNT) || defined(__WINNT) || defined(__WINNT__) || defined(__CYGWIN__)

#define PORTABLE_SYSTEM_WINDOWS

#elif defined(unix) || defined(__unix__) || defined(__unix) || defined(__linux) || defined(__linux__) || defined(__linux__) || defined(__sun) || defined(__SVR4)

#define PORTABLE_SYSTEM_UNIX

#elif defined(__APPLE__) && defined(__MACH__)

#define PORTABLE_SYSTEM_APPLE

#else
	
#define PORTABLE_SYSTEM_UNKNOWN

#endif

#if !defined(EXIT_SUCCESS)
#define EXIT_SUCCESS 0
#endif
#if !defined(EXIT_FAILURE)
#define EXIT_FAILURE 1
#endif

#if defined(LLONG_MAX)
/* If LLONG_MAX is defined in limits.h, use that */
#define PORTABLE_LLONG_MAX LLONG_MAX
#define PORTABLE_LLONG_MIN LLONG_MIN
#define PORTABLE_ULLONG_MAX ULLONG_MAX
#elif defined(__LONG_LONG_MAX__)
/* Otherwise, if GCC has the builtin defined, use that */
#define PORTABLE_LLONG_MAX __LONG_LONG_MAX__
#define PORTABLE_LLONG_MIN (-PORTABLE_LLONG_MAX - 1)
#define PORTABLE_ULLONG_MAX (__LONG_LONG_MAX__ * 2ULL + 1ULL)
#else
/* Otherwise, rely on two's complement */
#define PORTABLE_ULLONG_MAX (~0ULL)
#define PORTABLE_LLONG_MAX ((long long)(PORTABLE_ULLONG_MAX >> 1))
#define PORTABLE_LLONG_MIN (-PORTABLE_ULLONG_MAX - 1)
#endif

#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3) && (__GNUC_MINOR__ >= 1))
#define PORTABLE_DEPRECATED(VERSION_UNUSED) __attribute__((__deprecated__))
#else
#define PORTABLE_DEPRECATED(VERSION_UNUSED)
#endif

#endif