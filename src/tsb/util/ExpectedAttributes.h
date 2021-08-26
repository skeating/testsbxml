/**
 * @file    ExpectedAttributes.h
 * @brief   Definition of ExpectedAttributes, the class allowing the specification
 *          of attributes to expect.
 * @author  Ben Bornstein
 * ------------------------------------------------------------------------ -->
 */

#ifndef EXPECTED_ATTRIBUTES_H
#define EXPECTED_ATTRIBUTES_H

#include <tsb/common/extern.h>


#ifdef __cplusplus

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

LIBTSB_CPP_NAMESPACE_BEGIN
/** @cond doxygenlibLXInternal */
#ifndef SWIG
class LIBTSB_EXTERN ExpectedAttributes
{
public:

  ExpectedAttributes();
  
  void add(const std::string& attribute);

  std::string get(unsigned int i) const;

  bool hasAttribute(const std::string& attribute) const;

private:
  std::vector<std::string> mAttributes;
};


#endif //SWIG
/** @endcond */


LIBTSB_CPP_NAMESPACE_END

#endif  /* __cplusplus */


#ifndef SWIG

LIBTSB_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS


/** @cond doxygenlibLXInternal */
LIBTSB_EXTERN 
ExpectedAttributes_t *
ExpectedAttributes_create();

/* Clone the provided ExpectedAttributes_t structure */
LIBTSB_EXTERN 
ExpectedAttributes_t *
ExpectedAttributes_clone(ExpectedAttributes_t *attr);

/* Add the provided attribute to the ExpectedAttributes_t structure */
LIBTSB_EXTERN 
int
ExpectedAttributes_add(ExpectedAttributes_t *attr, const char* attribute);

/* Get the attribute at the provided index of the provided ExpectedAttributes_t structure */
LIBTSB_EXTERN 
char*
ExpectedAttributes_get(ExpectedAttributes_t *attr, unsigned int index);

/* Check the provided ExpectedAttributes_t structure to see if it contains the provided attribute*/
LIBTSB_EXTERN 
int
ExpectedAttributes_hasAttribute(ExpectedAttributes_t *attr, const char* attribute);
/** @endcond */

END_C_DECLS
LIBTSB_CPP_NAMESPACE_END

#endif  /* !SWIG   */
#endif  /* EXPECTED_ATTRIBUTES_H */
