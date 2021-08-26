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
 * Attempts to open filename for the given access mode and return a pointer
 * to it.  If the filename could not be opened, prints an error message and
 * exits.
 */
LIBTSB_EXTERN
FILE *
tsb_safe_reopen (const char *filename, const char *mode);


/**
 * @return a pointer to a new string which is a duplicate of the string s.
 * Memory for the string is obtained with safe_malloc() and can be freed
 * with safe_free().
 */
 LIBTSB_EXTERN
 char *
 tsb_safe_strdup (const char* s);


/**
 * Compares two strings s1 and s2, ignoring the case of the characters.
 *
 * @return an integer less than, equal to, or greater than zero if s1 is
 * found, respectively, to be less than, to match, or be greater than s2.
 */
LIBTSB_EXTERN
int
tsb_strcmp_insensitive (const char *s1, const char *s2);


/**
 * @returns @c 1 (true) if filename exists, @c 0 (false) otherwise.
 */
LIBTSB_EXTERN
int
tsb_util_file_exists (const char *filename);


/** @endcond */


/**
 * Returns a representation of @c NaN.
 * 
 * @return a (quiet) NaN.
 */
LIBTSB_EXTERN
double
tsb_util_NaN (void);


END_C_DECLS
LIBTSB_CPP_NAMESPACE_END


#endif  /** util_h **/

