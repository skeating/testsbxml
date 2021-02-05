/**
 * @file    ExpectedAttributes.cpp
 * @brief   Implementation of ExpectedAttributes, the class allowing the specification
 *          of attributes to expect.
 * @author  Ben Bornstein
 * ------------------------------------------------------------------------ -->
 */


#include <tsb/common/tsbfwd.h>
#include <tsb/common/common.h>
#include <tsb/common/TSBOperationReturnValues.h>
#include <tsb/util/ExpectedAttributes.h>

LIBTSB_CPP_NAMESPACE_BEGIN
#ifdef __cplusplus

bool ExpectedAttributes::hasAttribute(const std::string & attribute) const
{
  return (std::find(mAttributes.begin(), mAttributes.end(), attribute)
    != mAttributes.end());
}

std::string ExpectedAttributes::get(unsigned int i) const
{
  return (mAttributes.size() < i) ? mAttributes[i] : std::string();
}

void ExpectedAttributes::add(const std::string & attribute) 
{ 
  mAttributes.push_back(attribute);
}

ExpectedAttributes::ExpectedAttributes()
{
}


#endif /* __cplusplus */
/** @cond doxygenIgnored */
/** @cond doxygenLibsbmlInternal */
LIBTSB_EXTERN 
ExpectedAttributes_t *
ExpectedAttributes_create()
{
  return new ExpectedAttributes();
}

LIBTSB_EXTERN 
ExpectedAttributes_t *
ExpectedAttributes_clone(ExpectedAttributes_t *attr)
{
  if (attr == NULL) return NULL;
  return new ExpectedAttributes(*attr);
}

LIBTSB_EXTERN 
int
ExpectedAttributes_add(ExpectedAttributes_t *attr, const char* attribute)
{
  if (attr == NULL || attribute == NULL) return LIBTSB_INVALID_OBJECT;
  attr->add(std::string(attribute));
  return LIBTSB_OPERATION_SUCCESS;
}

LIBTSB_EXTERN 
char*
ExpectedAttributes_get(ExpectedAttributes_t *attr, unsigned int index)
{
  if (attr == NULL) return NULL;
  return safe_strdup(attr->get(index).c_str());
}

LIBTSB_EXTERN 
int
ExpectedAttributes_hasAttribute(ExpectedAttributes_t *attr, const char* attribute)
{
  if (attr == NULL) return (int)false;
  return attr->hasAttribute(std::string(attribute));
}
/** @endcond */
/** @endcond */

LIBTSB_CPP_NAMESPACE_END
