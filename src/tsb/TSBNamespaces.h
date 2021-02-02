/**
 * @file TSBNamespaces.h
 * @brief Definition of the TSBNamespaces class.
 * @author DEVISER
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML. Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2019 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2013-2018 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 * 3. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2009-2013 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 * Pasadena, CA, USA
 *
 * Copyright (C) 2002-2005 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. Japan Science and Technology Agency, Japan
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation. A copy of the license agreement is provided in the
 * file named "LICENSE.txt" included with this software distribution and also
 * available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
 *
 * @class TSBNamespaces
 * @sbmlbrief{} TODO:Definition of the TSBNamespaces class.
 */


#ifndef TSBNamespaces_h
#define TSBNamespaces_h

#include <sbml/xml/XMLNamespaces.h>
#include <sbml/util/List.h>

#include <tsb/common/common.h>
#include <tsb/common/tsbfwd.h>

#ifdef __cplusplus
namespace LIBTSB_CPP_NAMESPACE 
{
  const unsigned int TSB_DEFAULT_LEVEL   = 1;
  const unsigned int TSB_DEFAULT_VERSION = 1;
  const char* const TSB_XMLNS_L1V1   = "http://testsbxml.org/l1v1";
}
#else
static const unsigned int TSB_DEFAULT_LEVEL   = 1;
static const unsigned int TSB_DEFAULT_VERSION = 1;
static const char* const TSB_XMLNS_L1V1   = "http://testsbxml.org/l1v1";
#endif

#ifdef __cplusplus

#include <string>
#include <stdexcept>

LIBTSB_CPP_NAMESPACE_BEGIN

class LIBTSB_EXTERN TSBNamespaces
{
public:

  /**
   * Creates a new TSBNamespaces object corresponding to the given TSB
   * @p level and @p version.
   *
   * @param level the TSB level
   * @param version the TSB version
   * 
   */
  TSBNamespaces(unsigned int level = TSB_DEFAULT_LEVEL, 
                 unsigned int version = TSB_DEFAULT_VERSION);


  /**
   * Destroys this TSBNamespaces object.
   */
  virtual ~TSBNamespaces();

  
  /**
   * Copy constructor; creates a copy of a TSBNamespaces.
   * 
   * @param orig the TSBNamespaces instance to copy.
   */
  TSBNamespaces(const TSBNamespaces& orig);


  /**
   * Assignment operator for TSBNamespaces.
   */
  TSBNamespaces& operator=(const TSBNamespaces& rhs);


  /**
   * Creates and returns a deep copy of this TSBNamespaces object.
   *
   * @return the (deep) copy of this TSBNamespaces object.
   */
  virtual TSBNamespaces* clone () const;


  /**
   * Returns a string representing the TSB XML namespace for the 
   * given @p level and @p version of TSB.
   *
   * @param level the TSB level
   * @param version the TSB version
   *
   * @return a string representing the TSB namespace that reflects the
   * TSB Level and Version specified.
   */
  static std::string getTSBNamespaceURI(unsigned int level,
                                         unsigned int version);

  
  /**
   * Returns a list of all supported TSBNamespaces in this version of 
   * libtsb. 
   * 
   * @return a list with supported TSB namespaces. 
   */
  static const List* getSupportedNamespaces();


  /**
   * Frees the list of supported namespaces as generated by
   * getSupportedNamespaces().
   *
   * @param supportedNS the list to be freed.
   *
   * @copydetails doc_note_static_methods
   */
  static void freeTSBNamespaces(List * supportedNS);


  /**
   * Returns a string representing the TSB XML namespace of this
   * object.
   *
   * @return a string representing the TSB namespace that reflects the
   * TSB Level and Version of this object.
   */
  virtual std::string getURI() const;


  /**
   * Get the TSB Level of this TSBNamespaces object.
   *
   * @return the TSB Level of this TSBNamespaces object.
   */
  unsigned int getLevel();


  /**
   * Get the TSB Level of this TSBNamespaces object.
   *
   * @return the TSB Level of this TSBNamespaces object.
   */
  unsigned int getLevel() const;


  /**
   * Get the TSB Version of this TSBNamespaces object.
   *
   * @return the TSB Version of this TSBNamespaces object.
   */
  unsigned int getVersion();


  /**
   * Get the TSB Version of this TSBNamespaces object.
   *
   * @return the TSB Version of this TSBNamespaces object.
   */
  unsigned int getVersion() const;


  /**
   * Get the XML namespaces list for this TSBNamespaces object.
   *
   * @return the XML namespaces of this TSBNamespaces object.
   */
  XMLNamespaces * getNamespaces();


  /**
   * Get the XML namespaces list for this TSBNamespaces object.
   * 
   * @return the XML namespaces of this TSBNamespaces object.
   */
  const XMLNamespaces * getNamespaces() const;


  /**
   * Add the given XML namespaces list to the set of namespaces within this
   * TSBNamespaces object.
   *
   * @param xmlns the XML namespaces to be added.
   *
   * @copydetails doc_returns_success_code
   * @li @tsbconstant{LIBTSB_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @tsbconstant{LIBTSB_OPERATION_FAILED, OperationReturnValues_t}
   * @li @tsbconstant{LIBTSB_INVALID_OBJECT, OperationReturnValues_t}
   */
  int addNamespaces(const XMLNamespaces * xmlns);


  /**
   * Add an XML namespace (a pair of URI and prefix) to the set of namespaces
   * within this TSBNamespaces object.
   * 
   * @param uri    the XML namespace to be added.
   * @param prefix the prefix of the namespace to be added.
   *
   * @copydetails doc_returns_success_code
   * @li @tsbconstant{LIBTSB_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @tsbconstant{LIBTSB_OPERATION_FAILED, OperationReturnValues_t}
   * @li @tsbconstant{LIBTSB_INVALID_OBJECT, OperationReturnValues_t}
   */
  int addNamespace(const std::string& uri, const std::string &prefix);


  /**
   * Removes an XML namespace from the set of namespaces within this 
   * TSBNamespaces object.
   * 
   * @param uri    the XML namespace to be added.
   *
   * @copydetails doc_returns_success_code
   * @li @tsbconstant{LIBTSB_OPERATION_SUCCESS, OperationReturnValues_t}
   * @li @tsbconstant{LIBTSB_INDEX_EXCEEDS_SIZE, OperationReturnValues_t}
   */
  int removeNamespace(const std::string& uri);


  /**
   * Predicate returning @c true if the given URL is one of TSB XML
   * namespaces.
   *
   * @param uri the URI of namespace
   *
   * @return @c true if the "uri" is one of TSB namespaces, @c false otherwise.
   */
  static bool isTSBNamespace(const std::string& uri);


  /**
   * Predicate returning @c true if the given set of namespaces represent a
   * valid set
   *
   * @return @c true if the set of namespaces is valid, @c false otherwise.
   */
  bool isValidCombination();


  /** @cond doxygenLibtsbInternal */
  void setLevel(unsigned int level);


  void setVersion(unsigned int version);


  void setNamespaces(XMLNamespaces * xmlns);
  /** @endcond */

protected:  
  /** @cond doxygenLibtsbInternal */
  void initTSBNamespace();

  unsigned int    mLevel;
  unsigned int    mVersion;
  XMLNamespaces * mNamespaces;

  /** @endcond */
};

LIBTSB_CPP_NAMESPACE_END

#endif  /* __cplusplus */


#ifndef SWIG

LIBTSB_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/**
 * Creates a new TSBNamespaces_t structure corresponding to the given TSB
 * @p level and @p version.
 *
 * TSBNamespaces_t structures are used in libTSB to communicate TSB Level
 * and Version data between constructors and other methods.  The
 * TSBNamespaces_t structure class tracks 3-tuples (triples) consisting of
 * TSB Level, Version, and the corresponding TSB XML namespace.  Most
 * constructors for TSB structures in libTSB take a TSBNamespaces_t structure
 * as an argument, thereby allowing the constructor to produce the proper
 * combination of attributes and other internal data structures for the
 * given TSB Level and Version.
 *
 * The plural name "TSBNamespaces" is not a mistake, because in TSB
 * Level&nbsp;3, structures may have extensions added by Level&nbsp;3
 * packages used by a given model; however, until the introduction of
 * TSB Level&nbsp;3, the TSBNamespaces_t structure only records one TSB
 * Level/Version/namespace combination at a time.
 *
 * @param level the TSB level
 * @param version the TSB version
 *
 * @return TSBNamespaces_t structure created
 *
 * @ifnot hasDefaultArgs @htmlinclude warn-default-args-in-docs.html @endif@~
 *
 * @memberof TSBNamespaces_t
 */
LIBTSB_EXTERN
TSBNamespaces_t *
TSBNamespaces_create(unsigned int level, unsigned int version);


/**
 * Destroys this TSBNamespaces_t structure.
 *
 * @param ns TSBNamespaces_t structure to be freed.
 *
 * @memberof TSBNamespaces_t
 */
LIBTSB_EXTERN
void
TSBNamespaces_free (TSBNamespaces_t *ns);


/**
 * Get the TSB Level of this TSBNamespaces_t structure.
 *
 * @param tsbns the TSBNamespaces_t structure to query
 *
 * @return the TSB Level of this TSBNamespaces_t structure.
 *
 * @memberof TSBNamespaces_t
 */
LIBTSB_EXTERN
unsigned int
TSBNamespaces_getLevel(TSBNamespaces_t *tsbns);


/**
 * Get the TSB Version of this TSBNamespaces_t structure.
 *
 * @param tsbns the TSBNamespaces_t structure to query
 *
 * @return the TSB Version of this TSBNamespaces_t structure.
 *
 * @memberof TSBNamespaces_t
 */
LIBTSB_EXTERN
unsigned int
TSBNamespaces_getVersion(TSBNamespaces_t *tsbns);


/**
 * Get the TSB Version of this TSBNamespaces_t structure.
 *
 * @param tsbns the TSBNamespaces_t structure to query
 *
 * @return the XMLNamespaces_t structure of this TSBNamespaces_t structure.
 *
 * @memberof TSBNamespaces_t
 */
LIBTSB_EXTERN
XMLNamespaces_t *
TSBNamespaces_getNamespaces(TSBNamespaces_t *tsbns);


/**
 * Returns a string representing the TSB XML namespace for the 
 * given @p level and @p version of TSB.
 *
 * @param level the TSB level
 * @param version the TSB version
 *
 * @return a string representing the TSB namespace that reflects the
 * TSB Level and Version specified.
 *
 * @memberof TSBNamespaces_t
 */
LIBTSB_EXTERN
char *
TSBNamespaces_getTSBNamespaceURI(unsigned int level, unsigned int version);


/**
 * Add the XML namespaces list to the set of namespaces
 * within this TSBNamespaces_t structure.
 * 
 * @param tsbns the TSBNamespaces_t structure to add to
 * @param xmlns the XML namespaces to be added.
 *
 * @memberof TSBNamespaces_t
 */
LIBTSB_EXTERN
int
TSBNamespaces_addNamespaces(TSBNamespaces_t *tsbns,
                             const XMLNamespaces_t * xmlns);


/**
 * Returns an array of TSB Namespaces supported by this version of 
 * LibTSB. 
 *
 * @param length an integer holding the length of the array
 * @return an array of TSB namespaces, or @c NULL if length is @c NULL. The array 
 *         has to be freed by the caller.
 *
 * @memberof TSBNamespaces_t
 */
LIBTSB_EXTERN
TSBNamespaces_t **
TSBNamespaces_getSupportedNamespaces(int *length);

END_C_DECLS
LIBTSB_CPP_NAMESPACE_END

#endif  /* !SWIG */
#endif  /* TSBNamespaces_h */
