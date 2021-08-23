/**
 * @file    util.h
 * @brief   Utility functions
 * ---------------------------------------------------------------------- -->*/

#ifndef tsb_util_h
#define tsb_util_h

#include <stdio.h>
#include <stdarg.h>

#include <tsb/common/extern.h>

/** @cond doxygenlibLXInternal */

LIBTSB_CPP_NAMESPACE_BEGIN

BEGIN_C_DECLS

/**
 * Easier-to-read and NULL-friendly string comparison.
 */
LIBTSB_EXTERN
unsigned int
tsb_streq (const char *s, const char *t);


/**
 * @return a pointer to a new string which is a duplicate of the string s.
 * Memory for the string is obtained with safe_malloc() and can be freed
 * with safe_free().
 */
 LIBTSB_EXTERN
 char *
 tsb_safe_strdup (const char* s);


END_C_DECLS
LIBTSB_CPP_NAMESPACE_END


#endif  /** util_h **/

