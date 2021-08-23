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




#ifdef _MSC_VER
#pragma warning( pop )  // restore warning
#endif

LIBTSB_CPP_NAMESPACE_END

