/**
 * @file    util.cpp
 * @brief   Utility functions. 
 */

#ifdef _MSC_VER
#pragma warning( push )                    // Save the current warning state.
#pragma warning( disable : 4723 )          // C4723: potential divide by 0
#endif

#include <ctype.h>
#include <locale.h>
#include <sys/stat.h>
#include <sys/types.h>
#if defined CYGWIN
#include <cstdlib>
#endif

#include <tsb/common/common.h>

#include <tsb/util/List.h>
#include <tsb/util/util.h>
#include <tsb/util/memory.h>


#include <math.h>

#if defined(_MSC_VER) || defined(__BORLANDC__)
#  include <float.h>
#endif

#ifndef __DBL_EPSILON__ 
#define __DBL_EPSILON__ DBL_EPSILON
#endif

/** @cond doxygenlibLXInternal */
LIBTSB_CPP_NAMESPACE_BEGIN

LIBTSB_EXTERN
int
util_isNaN (double d)
{
  return d != d;
}

LIBTSB_EXTERN
FILE *
tsb_safe_reopen (const char *filename, const char *mode)
{
  FILE       *fp;

  if (filename == NULL || mode == NULL) return NULL;

  fp      = fopen(filename, mode);


  if (fp == (FILE *) NULL)
  {
#ifdef EXIT_ON_ERROR
    const char *format;
    const char *modestr;
    format  = "%s: error: Could not open file '%s' for %s.\n";
    modestr = strcmp(mode, "r") ? "writing" : "reading";
    fprintf(stderr, format, PACKAGE_NAME, filename, modestr);
    exit(-1);
#endif
  }

  return fp;
}


LIBTSB_EXTERN
 char *
 tsb_safe_strdup (const char* s)
 {
   size_t  size;
   char   *duplicate;
  
   if (s == NULL) return NULL;
  
   size      = strlen(s) + 1;
   duplicate = (char *) safe_malloc(size * sizeof(char));


   strncpy(duplicate, s, size);

   return duplicate;
 }


LIBTSB_EXTERN
int
tsb_strcmp_insensitive (const char *s1, const char *s2)
{
  while ( (*s1 != '\0') && 
          (tolower( *(unsigned char *) s1) == tolower( *(unsigned char *) s2)) )
  {
    s1++;
    s2++;
  }

  return tolower( *(unsigned char *) s1) - tolower( *(unsigned char *) s2);
}


LIBTSB_EXTERN
unsigned int
tsb_streq (const char *s, const char *t)
{
  if (s == NULL)
    return t == NULL;
  else if (t == NULL)
    return 0;
  else
    return !strcmp(s, t);
}



LIBTSB_EXTERN
int
tsb_util_file_exists (const char *filename)
{
#ifdef _MSC_VER
#  define stat _stat
#endif

  struct stat buf;
  if (filename == NULL) return 0;
  return stat(filename, &buf) == 0;
}


LIBTSB_EXTERN
double
tsb_util_NaN (void)
{
  double z = 0.0;

  // MSVC++ will produce a compile error if 0.0 is used instead of z.
  return 0.0 / z;
}



#ifdef _MSC_VER
#pragma warning( pop )  // restore warning
#endif

LIBTSB_CPP_NAMESPACE_END

