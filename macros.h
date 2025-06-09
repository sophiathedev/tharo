//
// Created by sophia on 5/21/25.
//

#ifndef MACROS_H
#define MACROS_H

/* Define the inline directive when available */
#if defined(__GNUC__) && !defined(__cplusplus)
#define INLINE __always_inline
#elif defined(__clang__) || defined(_MSC_VER)
#define INLINE inline
#else
#define INLINE
#endif

/* Define function attributes directive when available */
#if __GNUC__ >= 3
#define REGPARM(num) __attribute__((regparm(num)))
#elif defined(_MSC_VER) || defined(__BORLANDC__)
#define REGPARM(num) __fastcall
#else
#define REGPARM(num)
#endif

/* Define constexpr directive when available */
#if (defined(__GNUC__) || defined(__clang__)) && __STDC_VERSION__ >= 202311L
#define CONSTEXPR constexpr
#else
#define CONSTEXPR const
#endif

#if __STDC_VERSION__ >= 202311L
#define NULLPTR nullptr
#else
#define NULLPTR NULL
#endif

// Define the exit code of application
#define EXIT_NORMAL  0
#define EXIT_FAILURE 1

// Define the verbosity level
#define VERBOSE_INFO  1
#define VERBOSE_DEBUG 2
#define VERBOSE_WARN  3
#define VERBOSE_ERROR 4
#define VERBOSE_ALL   99

// Define memory macros
#define MEM_LIM_UNLIMITED ULONG_MAX

// ANSI color codes
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif  //MACROS_H
