/**
 * @file TSBBase.cpp
 * @brief Implementation of the TSBBase class.
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
 */


#include <sstream>
#include <vector>

#include <sbml/xml/XMLError.h>
#include <sbml/xml/XMLErrorLog.h>
#include <sbml/xml/XMLOutputStream.h>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLToken.h>
#include <sbml/xml/XMLNode.h>

#include <sbml/util/util.h>

#include <tsb/TSBError.h>
#include <tsb/TSBErrorLog.h>
#include <tsb/TSBDocument.h>
#include <tsb/TSBListOf.h>
#include <tsb/TSBBase.h>


/** @cond doxygenIgnored */
using namespace std;
/** @endcond */

LIBTSB_CPP_NAMESPACE_BEGIN

#ifdef __cplusplus

TSBBase*
TSBBase::getElementBySId(const std::string& id)
{
  if (id.empty()) return NULL;

  return NULL;
}


const TSBBase*
TSBBase::getElementBySId(const std::string& id) const 
{
  if (id.empty()) return NULL;

  return NULL;
}


TSBBase*
TSBBase::getElementByMetaId(const std::string& metaid)
{
  if (metaid.empty()) return NULL;

  return NULL;
}

const TSBBase*
TSBBase::getElementByMetaId(const std::string& metaid) const 
{
  if (metaid.empty()) return NULL;

  return NULL;
}


List*
TSBBase::getAllElements()
{
  return NULL;
}

/** @cond doxygenLibtsbInternal */
/*
 * Creates a new TSBBase object with the given level and version.
 * Only subclasses may create TSBBase objects.
 */
TSBBase::TSBBase (unsigned int level, unsigned int version) 
 : mMetaId ("")
 , mId ("")
 , mNotes(NULL)
 , mTestAnnotation( NULL )
 , mTSB      ( NULL )
 , mTSBNamespaces (NULL)
 , mUserData(NULL)
 , mLine      ( 0 )
 , mColumn    ( 0 )
 , mParentTSBObject (NULL)
  , mHasBeenDeleted(false)
  , mEmptyString("")
 , mURI("")
{
  mTSBNamespaces = new TSBNamespaces(level, version);

  //
  // Sets the XMLNS URI of corresponding TSB Level/Version to
  // the element namespace (mURI) of this object.
  //
  //
  setElementNamespace(mTSBNamespaces->getURI());
}



/*
 * Creates a new TSBBase object with the given TSBNamespaces.
 * Only subclasses may create TSBBase objects.
 */
TSBBase::TSBBase (TSBNamespaces *tsbns) 
 : mMetaId("")
 , mId("")
 , mNotes(NULL)
 , mTestAnnotation( NULL )
 , mTSB      ( NULL )
 , mTSBNamespaces (NULL)
 , mUserData(NULL)
 , mLine      ( 0 )
 , mColumn    ( 0 )
 , mParentTSBObject (NULL)
  , mHasBeenDeleted(false)
  , mEmptyString("")
 , mURI("")
{
  if (!tsbns)
  {
    std::string err("TSBBase::TSBBase(TSBNamespaces*) : TSBNamespaces is null");
    throw TSBConstructorException(err);
  }
  mTSBNamespaces = tsbns->clone();

  setElementNamespace(static_cast<TSBNamespaces>(*mTSBNamespaces).getURI());
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * Copy constructor. Creates a copy of this TSBBase object.
 */
TSBBase::TSBBase(const TSBBase& orig)
  : mMetaId (orig.mMetaId)
  , mId (orig.mId)
  , mNotes (NULL)
  , mTestAnnotation (NULL)
  , mTSB (NULL)
  , mTSBNamespaces(NULL)
  , mUserData(orig.mUserData)
  , mLine(orig.mLine)
  , mColumn(orig.mColumn)
  , mParentTSBObject(NULL)
  , mURI(orig.mURI)
{
  if(orig.mNotes != NULL)
    this->mNotes = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(*const_cast<TSBBase&>(orig).getNotes());
  else
    this->mNotes = NULL;

  if(orig.mTestAnnotation != NULL)
    this->mTestAnnotation = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(*const_cast<TSBBase&>(orig).mTestAnnotation);
  else
    this->mTestAnnotation = NULL;

  if(orig.getTSBNamespaces() != NULL)
    this->mTSBNamespaces =
    new TSBNamespaces(*const_cast<TSBBase&>(orig).getTSBNamespaces());
  else
    this->mTSBNamespaces = NULL;

  this->mHasBeenDeleted = false;
}
/** @endcond */


/*
 * Destroy this TSBBase object.
 */
TSBBase::~TSBBase ()
{
  if (mNotes != NULL)       delete mNotes;
  if (mTestAnnotation != NULL)  delete mTestAnnotation;
  if (mTSBNamespaces != NULL)  delete mTSBNamespaces;
}

/*
 * Assignment operator
 */
TSBBase& TSBBase::operator=(const TSBBase& rhs)
{
  if(&rhs!=this)
  {
    this->mMetaId = rhs.mMetaId;
    this->mId = rhs.mId;

    delete this->mNotes;

    if(rhs.mNotes != NULL)
      this->mNotes = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(*const_cast<TSBBase&>(rhs).getNotes());
    else
      this->mNotes = NULL;

    delete this->mTestAnnotation;

    if(rhs.mTestAnnotation != NULL)
      this->mTestAnnotation = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(*const_cast<TSBBase&>(rhs).mTestAnnotation);
    else
      this->mTestAnnotation = NULL;

    this->mTSB       = rhs.mTSB;
    this->mLine       = rhs.mLine;
    this->mColumn     = rhs.mColumn;
    this->mParentTSBObject = rhs.mParentTSBObject;
    this->mUserData   = rhs.mUserData;

    delete this->mTSBNamespaces;

    if(rhs.mTSBNamespaces != NULL)
      this->mTSBNamespaces =
      new TSBNamespaces(*const_cast<TSBBase&>(rhs).mTSBNamespaces);
    else
      this->mTSBNamespaces = NULL;


    this->mURI = rhs.mURI;
  }

  return *this;
}


/*
 * @return the metaid of this TSB object.
 */
const string&
TSBBase::getMetaId () const
{
  return mMetaId;
}


/*
 * @return the metaid of this TSB object.
 */
string&
TSBBase::getMetaId ()
{
  return mMetaId;
}


const string&
TSBBase::getId() const
{
  return mId;
}


/*
 * @return the notes of this TSB object.
 */
LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*
TSBBase::getNotes()
{
  return mNotes;
}


const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*
TSBBase::getNotes() const
{
  return mNotes;
}


/*
 * @return the notes of this TSB object by string.
 */
std::string
TSBBase::getNotesString()
{
  return LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertXMLNodeToString(mNotes);
}


std::string
TSBBase::getNotesString() const
{
  return LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertXMLNodeToString(mNotes);
}


/*
 * @return the annotation of this TSB object.
 */
LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*
TSBBase::getTestAnnotation ()
{
  return mTestAnnotation;
}


const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*
TSBBase::getTestAnnotation () const
{
  return const_cast<TSBBase *>(this)->getTestAnnotation();
}


/*
 * @return the annotation of this TSB object by string.
 */
std::string
TSBBase::getTestAnnotationString ()
{
  return LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertXMLNodeToString(getTestAnnotation());
}


std::string
TSBBase::getTestAnnotationString () const
{
  return LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertXMLNodeToString(getTestAnnotation());
}


/** @cond doxygenLibtsbInternal */
std::string
TSBBase::getURI() const
{
  const TSBDocument* doc = getTSBDocument();

  if (doc == NULL)
    return getElementNamespace();

  TSBNamespaces* tsbns = doc->getTSBNamespaces();

  if (tsbns == NULL)
    return getElementNamespace();

  return getElementNamespace();
}
/** @endcond */


void *
TSBBase::getUserData() const
{
  return this->mUserData;
}


int
TSBBase::setUserData(void *userData)
{
  this->mUserData = userData;
  if (userData == NULL && mUserData == NULL)
  {
    return LIBTSB_OPERATION_SUCCESS;
  }
  else if (mUserData != NULL)
  {
    return LIBTSB_OPERATION_SUCCESS;
  }
  else
  {
    return LIBTSB_OPERATION_FAILED;
  }
}

bool
TSBBase::isSetUserData() const
{
  if (mUserData != NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int
TSBBase::unsetUserData()
{
  this->mUserData = NULL;
  if (mUserData == NULL)
  {
    return LIBTSB_OPERATION_SUCCESS;
  }
  else
  {
    return LIBTSB_OPERATION_FAILED;
  }
}

/*
 * @return the Namespaces associated with this TSB object
 */
LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces*
TSBBase::getNamespaces()
{
  if (mTSB != NULL)
    return mTSB->getTSBNamespaces()->getNamespaces();
  else
    return mTSBNamespaces->getNamespaces();
}


const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces*
TSBBase::getNamespaces() const
{
  if (mTSB != NULL)
    return mTSB->getTSBNamespaces()->getNamespaces();
  else
    return mTSBNamespaces->getNamespaces();
}


/*
 * @return the parent TSBDocument of this TSB object.
 */
const TSBDocument*
TSBBase::getTSBDocument () const
{
  if (mTSB != NULL)
  {
    // if the doc object has been deleted the pointer is
    // still valid but points to nothing
    try
    {
      if (mTSB->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mTSB;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }

  return mTSB;
}

/*
 * @return the parent TSBDocument of this TSB object.
 */
TSBDocument*
TSBBase::getTSBDocument ()
{
  if (mTSB != NULL)
  {
    // if the doc object has been deleted the pointer is
    // still valid but points to nothing
    try
    {
      if (mTSB->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mTSB;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }
  return mTSB;
}
TSBBase*
TSBBase::getParentTSBObject ()
{
  if (mParentTSBObject != NULL)
  {
    // if the parent object has been deleted the pointer is
    // still valid but points to nothing
    try
    {
      if (mParentTSBObject->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mParentTSBObject;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }

  return mParentTSBObject;
}

const TSBBase*
TSBBase::getParentTSBObject () const
{
  if (mParentTSBObject != NULL)
  {
    // if the parent object has been deleted the pointer is
    // still valid but points to nothing
    try
    {
      if (mParentTSBObject->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mParentTSBObject;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }

  return mParentTSBObject;
}


/*
 * @return the line number of this TSB object.
 */
unsigned int
TSBBase::getLine () const
{
  return mLine;
}


/*
 * @return the column number of this TSB object.
 */
unsigned int
TSBBase::getColumn () const
{
  return mColumn;
}


/*
 * @return true if the metaid of this TSB object is set, false
 * otherwise.
 */
bool
TSBBase::isSetMetaId () const
{
  return (mMetaId.empty() == false);
}


bool
TSBBase::isSetId() const
{
  return (getId().empty() == false);
}


/*
 * @return true if the notes of this TSB object is set, false
 * otherwise.
 */
bool
TSBBase::isSetNotes () const
{
  return (mNotes != NULL);
}


/*
 * @return true if the annotation of this TSB object is set,
 * false otherwise.
 */
bool
TSBBase::isSetTestAnnotation () const
{
  return (mTestAnnotation != NULL);
}


/*
 * Sets the metaid field of the given TSB object to a copy of metaid.
 */
int
TSBBase::setMetaId (const std::string& metaid)
{
  if (metaid.empty())
  {
    mMetaId.erase();
    return LIBTSB_OPERATION_SUCCESS;
  }
  else if (!(SyntaxChecker::isValidXMLID(metaid)))
  {
    return LIBTSB_INVALID_ATTRIBUTE_VALUE;
  }
  else
  {
    mMetaId = metaid;
    return LIBTSB_OPERATION_SUCCESS;
  }
}

/*
 * Sets the id field of the given TSB object to a copy of sid.
 */
int
TSBBase::setId (const std::string& sid)
{
  if (sid.empty())
  {
    mId.erase();
    return LIBTSB_OPERATION_SUCCESS;
  }
  else if (!(SyntaxChecker::isValidXMLID(sid)))
  {
    return LIBTSB_INVALID_ATTRIBUTE_VALUE;
  }
  else
  {
    mId = sid;
    return LIBTSB_OPERATION_SUCCESS;
  }
}


/*
 * Sets the annotation of this TSB object to a copy of annotation.
 */
int
TSBBase::setTestAnnotation (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annotation)
{
  if (annotation == NULL)
  {
    delete mTestAnnotation;
    mTestAnnotation = NULL;
  }

  if (mTestAnnotation != annotation)
  {
    delete mTestAnnotation;

    mTestAnnotation = annotation->clone();
  }

  return LIBTSB_OPERATION_SUCCESS;
}

/*
 * Sets the annotation (by string) of this TSB object to a copy of annotation.
 */
int
TSBBase::setTestAnnotation (const std::string& annotation)
{
  
  int success = LIBTSB_OPERATION_FAILED;
  
  if(annotation.empty())
  {
    unsetTestAnnotation();
    return LIBTSB_OPERATION_SUCCESS;
  }
  
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annt_xmln;
  
  // you might not have a document !!
  if (getTSBDocument() != NULL)
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns = getTSBDocument()->getNamespaces();
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation,xmlns);
  }
  else
  {
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation);
  }
  
  if(annt_xmln != NULL)
  {
    success = setTestAnnotation(annt_xmln);
    delete annt_xmln;
  }
  return success;  
}


/*
 * Appends annotation to the existing annotations.
 * This allows other annotations to be preserved whilst
 * adding additional information.
 */
int
TSBBase::appendTestAnnotation (const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annotation)
{
  int success = LIBTSB_OPERATION_FAILED;
  unsigned int duplicates = 0;

  if(annotation == NULL)
    return LIBTSB_OPERATION_SUCCESS;

  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* new_annotation = NULL;
  const string&  name = annotation->getName();

  // check for annotation tags and add if necessary
  if (name != "testAnnotation")
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken ann_t = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLTriple("testAnnotation", "", ""), LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes());
    new_annotation = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(ann_t);
    new_annotation->addChild(*annotation);
  }
  else
  {
    new_annotation = annotation->clone();
  }


  if (mTestAnnotation != NULL)
  {
    // if mTestAnnotation is just <annotation/> need to tell
    // it to no longer be an end
    if (mTestAnnotation->isEnd())
    {
      mTestAnnotation->unsetEnd();
    }


    // create a list of existing top level ns
      vector<string> topLevelNs;
    unsigned int i = 0;
    for(i = 0; i < mTestAnnotation->getNumChildren(); i++)
    {
          topLevelNs.push_back(mTestAnnotation->getChild(i).getName());
    }



    for(i = 0; i < new_annotation->getNumChildren(); i++)
    {
          if (find(topLevelNs.begin(), topLevelNs.end(), (new_annotation->getChild(i).getName())) != topLevelNs.end())
      {
        mTestAnnotation->addChild(new_annotation->getChild(i));
      }
      else
      {
        duplicates++;
      }
    }

    delete new_annotation;

    if (duplicates > 0)
    {
      success = LIBTSB_DUPLICATE_ANNOTATION_NS;
    }
    else
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode *copy = mTestAnnotation->clone();
      success = setTestAnnotation(copy);
      delete copy;
    }


  }
  else
  {
    success = setTestAnnotation(new_annotation);

    delete new_annotation;
  }

  return success;
}

/*
 * Appends annotation (by string) to the existing annotations.
 * This allows other annotations to be preserved whilst
 * adding additional information.
 */
int
TSBBase::appendTestAnnotation (const std::string& annotation)
{
  int success = LIBTSB_OPERATION_FAILED;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annt_xmln;
  if (getTSBDocument() != NULL)
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns = getTSBDocument()->getNamespaces();
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation,xmlns);
  }
  else
  {
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation);
  }

  if(annt_xmln != NULL)
  {
    success = appendTestAnnotation(annt_xmln);
    delete annt_xmln;
  }

  return success;
}


int
TSBBase::removeTopLevelTestAnnotationElement(const std::string elementName,
    const std::string elementURI)
{

  int success = LIBTSB_OPERATION_FAILED;
  if (mTestAnnotation == NULL)
  {
    success = LIBTSB_OPERATION_SUCCESS;
    return success;
  }

  int index = mTestAnnotation->getIndex(elementName);
  if (index < 0)
  {
    // the annotation does not have a child of this name
    success = LIBTSB_ANNOTATION_NAME_NOT_FOUND;
    return success;
  }
  else
  {
    // check uri matches
    if (elementURI.empty() == false)
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode child = mTestAnnotation->getChild(index);
      std::string prefix = child.getPrefix();

      if (prefix.empty() == false
        && elementURI != child.getNamespaceURI(prefix))
      {
        success = LIBTSB_ANNOTATION_NS_NOT_FOUND;
        return success;
      }
      else
      {
        bool match = false;
        int n = 0;

        while (match == false && n < child.getNamespacesLength())
        {
          if (elementURI == child.getNamespaceURI(n))
          {
            match = true;
          }
          n++;
        }

        if (match == false)
        {
          success = LIBTSB_ANNOTATION_NS_NOT_FOUND;
          return success;
        }
      }
    }

    // remove the annotation at the index corresponding to the name
    delete mTestAnnotation->removeChild(index);

      if (mTestAnnotation->getNumChildren() == 0)
        {
          delete mTestAnnotation;
          mTestAnnotation = NULL;
        }

    // check success
    if (mTestAnnotation == NULL || mTestAnnotation->getIndex(elementName) < 0)
    {
      success = LIBTSB_OPERATION_SUCCESS;
    }
  }

  return success;
}


int
TSBBase::replaceTopLevelTestAnnotationElement(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annotation)
{
  int success = LIBTSB_OPERATION_FAILED;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode * replacement = NULL;
  if (annotation->getName() == "testAnnotation")
  {
    if (annotation->getNumChildren() != 1)
    {
      success = LIBTSB_INVALID_OBJECT;
      return success;
    }
    else
    {
      replacement = annotation->getChild(0).clone();
    }
  }
  else
  {
    replacement = annotation->clone();
  }

  success = removeTopLevelTestAnnotationElement(replacement->getName());
  if (success == LIBTSB_OPERATION_SUCCESS)
  {
    success = appendTestAnnotation(annotation);
  }

  delete (replacement);

  return success;
}


int
TSBBase::replaceTopLevelTestAnnotationElement(const std::string& annotation)
{
  int success = LIBTSB_OPERATION_FAILED;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* annt_xmln;
  if (getTSBDocument() != NULL)
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns = getTSBDocument()->getNamespaces();
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation,xmlns);
  }
  else
  {
    annt_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(annotation);
  }

  if(annt_xmln != NULL)
  {
    success = replaceTopLevelTestAnnotationElement(annt_xmln);
  }

  delete annt_xmln;

  return success;
}


/*
 * Sets the notes of this TSB object to a copy of notes.
 */
int
TSBBase::setNotes(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* notes)
{
  if (mNotes == notes)
  {
    return LIBTSB_OPERATION_SUCCESS;
  }
  else if (notes == NULL)
  {
    delete mNotes;
    mNotes = NULL;
    return LIBTSB_OPERATION_SUCCESS;
  }

  delete mNotes;
  const string&  name = notes->getName();

  /* check for notes tags and add if necessary */

  if (name == "notes")
  {
    mNotes = static_cast<LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode*>( notes->clone() );
  }
  else
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken notes_t = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLTriple("notes", "", ""),
                                LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes());
    mNotes = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(notes_t);

    // The root node of the given XMLNode tree can be an empty XMLNode
    // (i.e. neither start, end, nor text XMLNode) if the given notes was
    // converted from an XML string whose top level elements are neither
    // "html" nor "body" and not enclosed with <notes>..</notes> tag
    // (e.g. <p ...>..</p><br/>).
    if (!notes->isStart() && !notes->isEnd() && !notes->isText() )
    {
      for (unsigned int i=0; i < notes->getNumChildren(); i++)
      {
        if (mNotes->addChild(notes->getChild(i)) < 0)
        {
          return LIBTSB_OPERATION_FAILED;
        }
      }
    }
    else
    {
      if (mNotes->addChild(*notes) < 0)
        return LIBTSB_OPERATION_FAILED;
    }
  }

    if (!SyntaxChecker::hasExpectedXHTMLSyntax(mNotes, NULL))
    {
      delete mNotes;
      mNotes = NULL;
      return LIBTSB_INVALID_OBJECT;
    }

  return LIBTSB_OPERATION_SUCCESS;

}

/*
 * Sets the notes (by std::string) of this TSB object to a copy of notes.
 */
int
TSBBase::setNotes(const std::string& notes, bool addXHTMLMarkup)
{
  int success = LIBTSB_OPERATION_FAILED;
  
  if (notes.empty())
  {
    success = unsetNotes();
  }
  else
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* notes_xmln;

    // you might not have a document !!
    if (getTSBDocument() != NULL)
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns = getTSBDocument()->getNamespaces();
      notes_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(notes,xmlns);
    }
    else
    {
      notes_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(notes);
    }

    if (notes_xmln != NULL)
    {
      if (addXHTMLMarkup == true)
      {
        if (notes_xmln->getNumChildren() == 0
            && notes_xmln->isStart() == false
            && notes_xmln->isEnd() == false
            && notes_xmln->isText() == true)
        {
          //create a parent node of xhtml type p
          LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes blank_att = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes();
          LIBSBML_CPP_NAMESPACE_QUALIFIER XMLTriple triple = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLTriple("p", "http://www.w3.org/1999/xhtml", "");
          LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces xmlns = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces();
          xmlns.add("http://www.w3.org/1999/xhtml", "");
          LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode *xmlnode = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken(triple, blank_att, xmlns));

          // create a text node from the text given
          xmlnode->addChild(*notes_xmln);
          success = setNotes(xmlnode);
          delete xmlnode;
        }
        else
        {
          success = setNotes(notes_xmln);
        }
      }
      else
      {
        success = setNotes(notes_xmln);
      }

      delete notes_xmln;
    }
  }
  return success;
}


/*
 * Appends notes to the existing notes.
 * This allows other notes to be preserved whilst
 * adding additional information.
 */
int
TSBBase::appendNotes(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* notes)
{
  int success = LIBTSB_OPERATION_FAILED;
  if(notes == NULL)
  {
    return LIBTSB_OPERATION_SUCCESS;
  }

  const string&  name = notes->getName();

  // The content of notes in TSB can consist only of the following
  // possibilities:
  //
  //  1. A complete XHTML document (minus the XML and DOCTYPE
  //     declarations), that is, XHTML content beginning with the
  //     html tag.
  //     (_NotesType is _ANotesHTML.)
  //
  //  2. The body element from an XHTML document.
  //     (_NotesType is _ANotesBody.)
  //
  //  3. Any XHTML content that would be permitted within a body
  //     element, each one must declare the XML namespace separately.
  //     (_NotesType is _ANotesAny.)
  //

  typedef enum { _ANotesHTML, _ANotesBody, _ANotesAny } _NotesType;

  _NotesType addedNotesType = _ANotesAny;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode   addedNotes;

  //------------------------------------------------------------
  //
  // STEP1 : identifies the type of the given notes
  //
  //------------------------------------------------------------

  if (name == "notes")
  {
    /* check for notes tags on the added notes and strip if present and
       the notes tag has "html" or "body" element */

    if (notes->getNumChildren() > 0)
    {
      // notes->getChild(0) must be "html", "body", or any XHTML
      // element that would be permitted within a "body" element
      // (e.g. <p>..</p>,  <br>..</br> and so forth).

      const string& cname = notes->getChild(0).getName();

      if (cname == "html")
      {
        addedNotes = notes->getChild(0);
        addedNotesType = _ANotesHTML;
      }
      else if (cname == "body")
      {
        addedNotes = notes->getChild(0);
        addedNotesType = _ANotesBody;
      }
      else
      {
        // the notes tag must NOT be stripped if notes->getChild(0) node
        // is neither "html" nor "body" element because the children of
        // the addedNotes will be added to the curNotes later if the node
        // is neither "html" nor "body".
        addedNotes = *notes;
        addedNotesType = _ANotesAny;
      }
    }
    else
    {
      // the given notes is empty
      return LIBTSB_OPERATION_SUCCESS;
    }
  }
  else
  {
    // if the XMLNode argument notes has been created from a string and
    // it is a set of subelements there may be a single empty node
    // as parent - leaving this in doesnt affect the writing out of notes
    // but messes up the check for correct syntax
    if (!notes->isStart() && !notes->isEnd() && !notes->isText() )
    {
      if (notes->getNumChildren() > 0)
      {
        addedNotes = *notes;
        addedNotesType = _ANotesAny;
      }
      else
      {
        // the given notes is empty
        return LIBTSB_OPERATION_SUCCESS;
      }
    }
    else
    {
      if (name == "html")
      {
        addedNotes = *notes;
        addedNotesType = _ANotesHTML;
      }
      else if (name == "body")
      {
        addedNotes = *notes;
        addedNotesType = _ANotesBody;
      }
      else
      {
        // The given notes node needs to be added to a parent node
        // if the node is neither "html" nor "body" element because the
        // children of addedNotes will be added to the curNotes later if the
        // node is neither "html" nor "body" (i.e. any XHTML element that
        // would be permitted within a "body" element)
        addedNotes.addChild(*notes);
        addedNotesType = _ANotesAny;
      }
    }
  }

  //
  // checks the addedNotes of "html" if the html tag contains "head" and
  // "body" tags which must be located in this order.
  //
  if (addedNotesType == _ANotesHTML)
  {
    if ((addedNotes.getNumChildren() != 2) ||
        ( (addedNotes.getChild(0).getName() != "head") ||
          (addedNotes.getChild(1).getName() != "body")
        )
       )
    {
      return LIBTSB_INVALID_OBJECT;
    }
  }

  // check whether notes is valid xhtml
  if (getLevel() > 2
    || (getLevel() == 2 && getVersion() > 1))
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode tmpNotes(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLTriple("notes","",""), LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes());

    if (addedNotesType == _ANotesAny)
    {
      for (unsigned int i=0; i < addedNotes.getNumChildren(); i++)
      {
        tmpNotes.addChild(addedNotes.getChild(i));
      }
    }
    else
    {
      tmpNotes.addChild(addedNotes);
    }

    if (!SyntaxChecker::hasExpectedXHTMLSyntax(&tmpNotes, NULL))
    {
      return LIBTSB_INVALID_OBJECT;
    }
  }


  if ( mNotes != NULL )
  {
    //------------------------------------------------------------
    //
    //  STEP2: identifies the type of the existing notes
    //
    //------------------------------------------------------------

    _NotesType curNotesType   = _ANotesAny;
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode&  curNotes = *mNotes;

    // curNotes.getChild(0) must be "html", "body", or any XHTML
    // element that would be permitted within a "body" element .

    const string& cname = curNotes.getChild(0).getName();

    if (cname == "html")
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& curHTML = curNotes.getChild(0);
      //
      // checks the curHTML if the html tag contains "head" and "body" tags
      // which must be located in this order, otherwise nothing will be done.
      //
      if ((curHTML.getNumChildren() != 2) ||
          ( (curHTML.getChild(0).getName() != "head") ||
            (curHTML.getChild(1).getName() != "body")
          )
         )
      {
        return LIBTSB_INVALID_OBJECT;
      }
      curNotesType = _ANotesHTML;
    }
    else if (cname == "body")
    {
      curNotesType = _ANotesBody;
    }
    else
    {
      curNotesType = _ANotesAny;
    }

    /*
     * BUT we also have the issue of the rules relating to notes
     * contents and where to add them ie we cannot add a second body element
     * etc...
     */

    //------------------------------------------------------------
    //
    //  STEP3: appends the given notes to the current notes
    //
    //------------------------------------------------------------

    unsigned int i;

    if (curNotesType == _ANotesHTML)
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& curHTML = curNotes.getChild(0);
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& curBody = curHTML.getChild(1);

      if (addedNotesType == _ANotesHTML)
      {
        // adds the given html tag to the current html tag

        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& addedBody = addedNotes.getChild(1);

        for (i=0; i < addedBody.getNumChildren(); i++)
        {
          if (curBody.addChild(addedBody.getChild(i)) < 0 )
            return LIBTSB_OPERATION_FAILED;
        }
      }
      else if ((addedNotesType == _ANotesBody)
             || (addedNotesType == _ANotesAny))
      {
        // adds the given body or other tag (permitted in the body) to the current
        // html tag

        for (i=0; i < addedNotes.getNumChildren(); i++)
        {
          if (curBody.addChild(addedNotes.getChild(i)) < 0 )
            return LIBTSB_OPERATION_FAILED;
        }
      }
      success = LIBTSB_OPERATION_SUCCESS;
    }
    else if (curNotesType == _ANotesBody)
    {
      if (addedNotesType == _ANotesHTML)
      {
        // adds the given html tag to the current body tag

        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode  addedHTML(addedNotes);
        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& addedBody = addedHTML.getChild(1);
        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& curBody   = curNotes.getChild(0);

        for (i=0; i < curBody.getNumChildren(); i++)
        {
          addedBody.insertChild(i,curBody.getChild(i));
        }

        curNotes.removeChildren();
        if (curNotes.addChild(addedHTML) < 0)
          return LIBTSB_OPERATION_FAILED;
      }
      else if ((addedNotesType == _ANotesBody) || (addedNotesType == _ANotesAny))
      {
        // adds the given body or other tag (permitted in the body) to the current
        // body tag

        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& curBody = curNotes.getChild(0);

        for (i=0; i < addedNotes.getNumChildren(); i++)
        {
          if (curBody.addChild(addedNotes.getChild(i)) < 0)
            return LIBTSB_OPERATION_FAILED;
        }
      }
      success = LIBTSB_OPERATION_SUCCESS;
    }
    else if (curNotesType == _ANotesAny)
    {
      if (addedNotesType == _ANotesHTML)
      {
        // adds the given html tag to the current any tag permitted in the body.

        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode  addedHTML(addedNotes);
        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode& addedBody = addedHTML.getChild(1);

        for (i=0; i < curNotes.getNumChildren(); i++)
        {
          addedBody.insertChild(i,curNotes.getChild(i));
        }

        curNotes.removeChildren();
        if (curNotes.addChild(addedHTML) < 0)
          return LIBTSB_OPERATION_FAILED;
      }
      else if (addedNotesType == _ANotesBody)
      {
        // adds the given body tag to the current any tag permitted in the body.

        LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode addedBody(addedNotes);

        for (i=0; i < curNotes.getNumChildren(); i++)
        {
          addedBody.insertChild(i,curNotes.getChild(i));
        }

        curNotes.removeChildren();
        if (curNotes.addChild(addedBody) < 0)
          return LIBTSB_OPERATION_FAILED;
      }
      else if (addedNotesType == _ANotesAny)
      {
        // adds the given any tag permitted in the boy to that of the current
        // any tag.

        for (i=0; i < addedNotes.getNumChildren(); i++)
        {
          if (curNotes.addChild(addedNotes.getChild(i)) < 0)
            return LIBTSB_OPERATION_FAILED;
        }
      }
      success = LIBTSB_OPERATION_SUCCESS;
    }
  }
  else // if (mNotes == NULL)
  {
    // setNotes accepts XMLNode with/without top level notes tags.
    success = setNotes(notes);
  }

  return success;
}

/*
 * Appends notes (by string) to the existing notes.
 * This allows other notes to be preserved whilst
 * adding additional information.
 */
int
TSBBase::appendNotes(const std::string& notes)
{
  int success = LIBTSB_OPERATION_FAILED;
  if (notes.empty())
  {
    return LIBTSB_OPERATION_SUCCESS;
  }

  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* notes_xmln;
  // you might not have a document !!
  if (getTSBDocument() != NULL)
  {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns = getTSBDocument()->getNamespaces();
      notes_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(notes,xmlns);
  }
  else
  {
      notes_xmln = LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode::convertStringToXMLNode(notes);
  }

  if(notes_xmln != NULL)
  {
    success = appendNotes(notes_xmln);
    delete notes_xmln;
  }
  return success;
}


/** @cond doxygenLibtsbInternal */
/*
 * Sets the parent TSBDocument of this TSB object.
 */
void
TSBBase::setTSBDocument (TSBDocument* d)
{
  mTSB = d;
}


/*
  * Sets the parent TSB object of this TSB object.
  *
  * @param sb the TSB object to use
  */
void
TSBBase::connectToParent (TSBBase* parent)
{
  mParentTSBObject = parent;
  if (mParentTSBObject)
  {
#if 0
    cout << "[DEBUG] connectToParent " << this << " (parent) " << TSBTypeCode_toString(parent->getTypeCode(),"core")
         << " " << parent->getTSBDocument() << endl;
#endif
    setTSBDocument(mParentTSBObject->getTSBDocument());
  }
  else
  {
    setTSBDocument(NULL);
  }
}


/*
 * Sets this TSB object to child TSB objects (if any).
 * (Creates a child-parent relationship by the parent)
 *
 * Subclasses must override this function if they define
 * one ore more child elements.
 * Basically, this function needs to be called in
 * constructors, copy constructors and assignment operators.
 */
void
TSBBase::connectToChild()
{
}
/** @endcond */

TSBBase*
TSBBase::getAncestorOfType(int type)
{
  if (type == TSB_DOCUMENT)
    return getTSBDocument();

  TSBBase *child;
  TSBBase *parent = getParentTSBObject();

  while ( parent != NULL &&
          !( parent->getTypeCode() == TSB_DOCUMENT )
        )
  {
    if (parent->getTypeCode() == type)
      return parent;
    else
    {
      child = parent;
      parent = child->getParentTSBObject();
    }
  }

  // if we get here we havent found an ancestor of this type
  return NULL;

}


const TSBBase*
TSBBase::getAncestorOfType(int type) const
{
  if (type == TSB_DOCUMENT)
    return getTSBDocument();

  const TSBBase *child;
  const TSBBase *parent = getParentTSBObject();

  while ( parent != NULL &&
          !( parent->getTypeCode() == TSB_DOCUMENT )
        )
  {
    if (parent->getTypeCode() == type)
      return parent;
    else
    {
      child = parent;
      parent = child->getParentTSBObject();
    }
  }

  // if we get here we havent found an ancestor of this type
  return NULL;

}


/*
 * Sets the namespaces relevant of this TSB object.
 *
 * @param xmlns the namespaces to set
 */
int
TSBBase::setNamespaces(LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns)
{
  if (xmlns == NULL)
  {
    mTSBNamespaces->setNamespaces(NULL);
    return LIBTSB_OPERATION_SUCCESS;
  }
  else
  {
    mTSBNamespaces->setNamespaces(xmlns);
    return LIBTSB_OPERATION_SUCCESS;
  }
}



/*
 * Unsets the metaid of this TSB object.
 */
int
TSBBase::unsetMetaId ()
{
  mMetaId.erase();

  if (mMetaId.empty())
  {
    return LIBTSB_OPERATION_SUCCESS;
  }
  else
  {
    return LIBTSB_OPERATION_FAILED;
  }
}


/*
 * Unsets the id of this TSB object.
 */
int
TSBBase::unsetId ()
{
  mId.erase();

  if (mId.empty())
  {
    return LIBTSB_OPERATION_SUCCESS;
  }
  else
  {
    return LIBTSB_OPERATION_FAILED;
  }
}


/*
 * Unsets the notes of this TSB object.
 */
int
TSBBase::unsetNotes ()
{
  delete mNotes;
  mNotes = NULL;
  return LIBTSB_OPERATION_SUCCESS;
}


/*
 * Unsets the annotation of this TSB object.
 */
int
TSBBase::unsetTestAnnotation ()
{
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode* empty = NULL;
  return setTestAnnotation(empty);
}


/*
 * @return the TSB level of this TSB object.
 */
unsigned int
TSBBase::getLevel () const
{
  if (mTSB != NULL)
    return mTSB->getLevel();
  else if (mTSBNamespaces != NULL)
    return mTSBNamespaces->getLevel();
  else
    return TSB_DEFAULT_LEVEL;
}


/*
 * @return the TSB version of this TSB object.
 */
unsigned int
TSBBase::getVersion () const
{
  if (mTSB != NULL)
    return mTSB->getVersion();
  else if (mTSBNamespaces != NULL)
    return mTSBNamespaces->getVersion();
  else
    return TSB_DEFAULT_VERSION;
}


/*
 * @return the typecode (int) of this TSB object or TSB_UNKNOWN
 * (default).
 *
 * This method MAY return the typecode of this TSB object or it MAY
 * return TSB_UNKNOWN.  That is, subclasses of TSBBase are not required to
 * implement this method to return a typecode.  This method is meant
 * primarily for the LibTSB C interface where class and subclass
 * information is not readily available.
 *
 * @see getElementName()
 */
int
TSBBase::getTypeCode () const
{
  return TSB_UNKNOWN;
}


bool
TSBBase::hasValidLevelVersionNamespaceCombination()
{
  int typecode = getTypeCode();
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces *xmlns = getNamespaces();

  return hasValidLevelVersionNamespaceCombination(typecode, xmlns);
}

/** @cond doxygenLibtsbInternal */
bool
TSBBase::matchesTSBNamespaces(const TSBBase * sb)
{
  bool match = matchesCoreTSBNamespace(sb);

  return match;
}

bool
TSBBase::matchesTSBNamespaces(const TSBBase * sb) const
{
  bool match = matchesCoreTSBNamespace(sb);

  return match;
}


bool
TSBBase::matchesRequiredTSBNamespacesForAddition(const TSBBase * sb)
{
  // if core does not match forget it
  bool match = matchesCoreTSBNamespace(sb);

  return match;
}


bool
TSBBase::matchesRequiredTSBNamespacesForAddition(const TSBBase * sb) const
{
  // if core does not match forget it
  bool match = matchesCoreTSBNamespace(sb);

  return match;
}


bool
TSBBase::matchesCoreTSBNamespace(const TSBBase * sb)
{
  bool match = false;

  TSBNamespaces *tsbns = getTSBNamespaces();
  TSBNamespaces *tsbns_rhs = sb->getTSBNamespaces();

  if (tsbns->getLevel() != tsbns_rhs->getLevel())
    return match;

  if (tsbns->getVersion() != tsbns_rhs->getVersion())
    return match;

  std::string coreNs = TSBNamespaces::getTSBNamespaceURI(
                       tsbns->getLevel(), tsbns->getVersion());

  if (tsbns->getNamespaces()->containsUri(coreNs)
    && tsbns_rhs->getNamespaces()->containsUri(coreNs))
  {
    match = true;
  }

  return match;
}


bool
TSBBase::matchesCoreTSBNamespace(const TSBBase * sb) const
{
  bool match = false;

  TSBNamespaces *tsbns = getTSBNamespaces();
  TSBNamespaces *tsbns_rhs = sb->getTSBNamespaces();

  if (tsbns->getLevel() != tsbns_rhs->getLevel())
    return match;

  if (tsbns->getVersion() != tsbns_rhs->getVersion())
    return match;

  std::string coreNs = TSBNamespaces::getTSBNamespaceURI(
                       tsbns->getLevel(), tsbns->getVersion());

  if (tsbns->getNamespaces()->containsUri(coreNs)
    && tsbns_rhs->getNamespaces()->containsUri(coreNs))
  {
    match = true;
  }

  return match;
}


bool
TSBBase::hasValidLevelVersionNamespaceCombination(int typecode, LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces *xmlns)
{


  //
  // (TODO) Currently, the following check code works only for
  //        elements in TSB core.
  //        This function may need to be extented for other elements
  //        defined in each package extension.
  //

  bool valid = true;
  bool tsbDeclared = false;
  std::string declaredURI("");

  if (xmlns != NULL)
  {
    int numNS = 0;

    if (xmlns->hasURI(TSB_XMLNS_L1V1))
    {
      // checks different TSB XMLNamespaces
      if (numNS > 0) return false;
      ++numNS;
      declaredURI.assign(TSB_XMLNS_L1V1);
    }

    // checks if the TSB Namespace is explicitly defined.
    for (int i=0; i < xmlns->getLength(); i++)
    {
      if (!declaredURI.empty() &&
                      xmlns->getURI(i) == declaredURI)
      {
        tsbDeclared = true;
        break;

      }
    }
  }

  return valid;
}

/* sets the TSBnamespaces - internal use only*/
int
TSBBase::setTSBNamespaces(TSBNamespaces * tsbns)
{
  if (tsbns == NULL)
    return LIBTSB_INVALID_OBJECT;

  TSBNamespaces* tsbnsClone = (tsbns) ? tsbns->clone() : 0;
  setTSBNamespacesAndOwn(tsbnsClone);

  return LIBTSB_OPERATION_SUCCESS;
}

/*
 * sets the TSBnamespaces - only for internal use in the
 * constructors of TSBBase subclasses in extension packages.
 */
void
TSBBase::setTSBNamespacesAndOwn(TSBNamespaces * tsbns)
{
  delete mTSBNamespaces;
  mTSBNamespaces = tsbns;

  if(tsbns != NULL)
    setElementNamespace(tsbns->getURI());
}


/* gets the TSBnamespaces - internal use only*/
TSBNamespaces *
TSBBase::getTSBNamespaces() const
{
  if (mTSB != NULL)
    return mTSB->mTSBNamespaces;
  
  // initialize TSB namespace if need be
  if (mTSBNamespaces == NULL)
    const_cast<TSBBase*>(this)->mTSBNamespaces = new TSBNamespaces(getLevel(), getVersion());
  return mTSBNamespaces;  
}
/** @endcond */



/*
 * @return the partial TSB that describes this TSB object.
 */
char*
TSBBase::toTSB ()
{
  ostringstream    os;
  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream  stream(os, "UTF-8", false);

  write(stream);

  return safe_strdup( os.str().c_str() );
}


/** @cond doxygenLibtsbInternal */
int 
TSBBase::getAttribute(const std::string& attributeName, double& value) const
{
  return LIBTSB_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
int 
TSBBase::getAttribute(const std::string& attributeName, bool& value) const
{
  return LIBTSB_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
int 
TSBBase::getAttribute(const std::string& attributeName, int& value) const
{
  return LIBTSB_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
int 
TSBBase::getAttribute(const std::string& attributeName, unsigned int& value) const
{
  return LIBTSB_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
int 
TSBBase::getAttribute(const std::string& attributeName, std::string& value) const
{
  if (attributeName == "metaid")
  {
    value = getMetaId();
    return LIBTSB_OPERATION_SUCCESS;
  }
  else if (attributeName == "id")
  {
    value = getId();
    return LIBTSB_OPERATION_SUCCESS;
  }

  return LIBTSB_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
bool 
TSBBase::isSetAttribute(const std::string& attributeName) const
{
  bool value = false;
  if (attributeName == "metaid")
  {
    value = isSetMetaId();
  }
  else if (attributeName == "id")
  {
    value = isSetId();
  }

  return value;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
int 
TSBBase::setAttribute(const std::string& attributeName, double value)
{
  return LIBTSB_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
int 
TSBBase::setAttribute(const std::string& attributeName, bool value)
{
  return LIBTSB_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
int 
TSBBase::setAttribute(const std::string& attributeName, int value)
{
  return LIBTSB_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
int 
TSBBase::setAttribute(const std::string& attributeName, unsigned int value)
{
  return LIBTSB_OPERATION_FAILED;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
int 
TSBBase::setAttribute(const std::string& attributeName, const std::string& value)
{
  int return_value = LIBTSB_OPERATION_FAILED;
  if (attributeName == "metaid")
  {
    return_value = setMetaId(value);
  }
  else if (attributeName == "id")
  {
    return_value = setId(value);
  }

  return return_value;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
int 
TSBBase::unsetAttribute(const std::string& attributeName)
{
  int value = LIBTSB_OPERATION_FAILED;
  if (attributeName == "metaid")
  {
    value = unsetMetaId();
  }
  else if (attributeName == "id")
  {
    value = unsetId();
  }

  return value;
}
/** @endcond */

/** @cond doxygenLibtsbInternal */
TSBBase* 
TSBBase::createChildObject(const std::string& elementName)
{
  return NULL;
}
/** @endcond */

/** @cond doxygenLibtsbInternal */
int
TSBBase::addChildObject(const std::string& elementName, const TSBBase* element)
{
  return LIBTSB_OPERATION_FAILED;
}
/** @endcond */

/** @cond doxygenLibtsbInternal */
TSBBase*
TSBBase::removeChildObject(const std::string& elementName, const std::string& id)
{
  return NULL;
}
/** @endcond */

/** @cond doxygenLibtsbInternal */

unsigned int
  TSBBase::getNumObjects(const std::string& objectName)
{
  return 0;
}

  /** @endcond */

  /** @cond doxygenLibtsbInternal */

TSBBase* 
TSBBase::getObject(const std::string& objectName, unsigned int index)
{
  return NULL;
}

  /** @endcond */
/** @cond doxygenLibtsbInternal */
/*
 * Reads (initializes) this TSB object by reading from XMLInputStream.
 */
void
TSBBase::read (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  if ( !stream.peek().isStart() ) return;

  const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken  element  = stream.next();
  int             position =  0;

  setTSBBaseFields( element );

  ExpectedAttributes expectedAttributes;
  addExpectedAttributes(expectedAttributes);
  readAttributes( element.getAttributes(), expectedAttributes );

  /* if we are reading a document pass the
   * TSB Namespace information to the input stream object
   * thus the MathML reader can find out what level/version
   * of TSB it is parsing
   */
  if (element.getName() == "tsb")
  {
 //   stream.setTSBNamespaces(this->getTSBNamespaces());
    // need to check that any prefix on the tsbns also occurs on element
    // remembering the horrible situation where the tsbns might be declared
    // with more than one prefix
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces * xmlns = this->getTSBNamespaces()->getNamespaces();
    if (xmlns != NULL)
    {
      int i = xmlns->getIndexByPrefix(element.getPrefix());
      if (i < xmlns->getNumNamespaces())
      {
        bool errorLoggedAlready = false;
        bool error = false;
        if (i > -1)
        {
          if (xmlns->getURI(i) != this->getTSBNamespaces()->getURI())
          {
            error = true;
          }
        }
        else if ( i == -1)
        {
          error = true;
        }

        /* if there is a mismatch in level/version this will already
         * be logged; do not need another error
         */
        for (unsigned int n = 0; n < this->getErrorLog()->getNumErrors(); n++)
        {
          unsigned int errorId =
                             this->getErrorLog()->getError(n)->getErrorId();
          if ( errorId == TsbmlDocumentAllowedCoreAttributes
            || errorId == TsbmlDocumentLevelMustBeNonNegativeInteger
            || errorId == TsbmlDocumentVersionMustBeNonNegativeInteger
            || errorId == InvalidNamespaceOnTSB)
          {
            errorLoggedAlready = true;
          }
        }

        if (error == true && errorLoggedAlready == false)
        {
          static ostringstream errMsg;
          errMsg.str("");
          errMsg << "The prefix for the <tsb> element does not match "
            << "the prefix for the TSB namespace.  This means that "
            << "the <tsb> element in not in the TSBNamespace."<< endl;

          logError(InvalidNamespaceOnTSB,
                    getLevel(), getVersion(), errMsg.str());
        }
      }
    }

  }
  else
  {
    //
    // checks if the given default namespace (if any) is a valid
    // TSB namespace
    //
    checkDefaultNamespace(mTSBNamespaces->getNamespaces(), element.getName());
    if (!element.getPrefix().empty())
    {
      LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces * prefixedNS = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces();
      prefixedNS->add(element.getURI(), element.getPrefix());
      checkDefaultNamespace(prefixedNS, element.getName(), element.getPrefix());
      delete prefixedNS;
    }
  }

  if ( element.isEnd() ) return;

  while ( stream.isGood() )
  {
    // this used to skip the text
    //    stream.skipText();
    // instead, read text and store in variable
    std::string text;
    while(stream.isGood() && stream.peek().isText())
    {
      text += stream.next().getCharacters();
    }
    setElementText(text);

    const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken& next = stream.peek();

    // Re-check stream.isGood() because stream.peek() could hit something.
    if ( !stream.isGood() ) break;

    if ( next.isEndFor(element) )
    {
      stream.next();
      break;
    }
    else if ( next.isStart() )
    {
      const std::string nextName = next.getName();

      TSBBase * object = createObject(stream);

      if (object != NULL)
      {
        position = object->getElementPosition();

        object->connectToParent(static_cast <TSBBase*>(this));

        object->read(stream);

        if ( !stream.isGood() ) break;

        checkTSBListOfPopulated(object);
      }
      else if ( !( readOtherXML(stream)
                   || readTestAnnotation(stream)
                   || readNotes(stream) ))
      {
        logUnknownElement(nextName, getLevel(), getVersion());
        stream.skipPastEnd( stream.next() );
      }
    }
    else
    {
      stream.skipPastEnd( stream.next() );
    }
  }
}
/** @endcond */


void
TSBBase::setElementText(const std::string &text)
{
}

/** @cond doxygenLibtsbInternal */
/*
 * Writes (serializes) this TSB object by writing it to XMLOutputStream.
 */
void
TSBBase::write (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const
{
  stream.startElement( getElementName(), getPrefix() );

  writeXMLNS     ( stream );
  writeAttributes( stream );
  writeElements  ( stream );

  stream.endElement( getElementName(), getPrefix() );

}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * Subclasses should override this method to write out their contained
 * TSB objects as XML elements.  Be sure to call your parents
 * implementation of this method as well.
 */
void
TSBBase::writeElements (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const
{
  if ( mNotes != NULL ) stream << *mNotes;

  if (mTestAnnotation != NULL) stream << *mTestAnnotation;
}


/** @cond doxygenLibtsbInternal */
/*
 * Subclasses should override this method to create, store, and then
 * return an TSB object corresponding to the next XMLToken in the
 * XMLInputStream.
 *
 * @return the TSB object corresponding to next XMLToken in the
 * XMLInputStream or @c NULL if the token was not recognized.
 */
TSBBase*
TSBBase::createObject (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  return NULL;
}


/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * Subclasses should override this method to read (and store) XHTML,
 * MathML, etc. directly from the XMLInputStream.
 *
 * @return true if the subclass read from the stream, false otherwise.
 */
bool
TSBBase::readOtherXML (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  bool read = false;
  return read;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * @return true if read an <annotation> element from the stream
 */
bool
TSBBase::readTestAnnotation (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  const string& name = stream.peek().getName();

  if (name == "testAnnotation")
  {
    // If an annotation already exists, log it as an error and replace
    // the content of the existing annotation with the new one.

    if (mTestAnnotation != NULL)
    {
      string msg = "An TSB <" + getElementName() + "> element ";
      msg += "has multiple <annotation> children.";
      logError(TSBMultipleTestAnnotations, getLevel(), getVersion(), msg);
    }

    delete mTestAnnotation;
    mTestAnnotation = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(stream);
    checkTestAnnotation();
    return true;
  }

  return false;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * @return true if read a <notes> element from the stream
 */
bool
TSBBase::readNotes (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLInputStream& stream)
{
  const string& name = stream.peek().getName();

  if (name == "notes")
  {
    // If a notes element already exists, then it is an error.
    // If an annotation element already exists, then the ordering is wrong.
    // In either case, replace existing content with the new notes read.

    if (mNotes != NULL)
    {
      logError(TSBOnlyOneNotesElementAllowed, getLevel(), getVersion());
    }

    delete mNotes;
    mNotes = new LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode(stream);

    //
    // checks if the given default namespace (if any) is a valid
    // TSB namespace
    //
    const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces &xmlns = mNotes->getNamespaces();
    checkDefaultNamespace(&xmlns,"notes");

    return true;
  }

  return false;
}

bool
TSBBase::getHasBeenDeleted() const
{
  return mHasBeenDeleted;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * @return the ordinal position of the element with respect to its siblings
 * or -1 (default) to indicate the position is not significant.
 */
int
TSBBase::getElementPosition () const
{
  return -1;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
TSBErrorLog*
TSBBase::getErrorLog ()
{
  return (mTSB != NULL) ? mTSB->getErrorLog() : NULL;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * Helper to log a common type of error.
 */
void
TSBBase::logUnknownAttribute( const string& attribute,
                            const unsigned int level,
                            const unsigned int version,
                            const string& element,
                            const string& prefix)
{
  ostringstream msg;

    msg << "Attribute '" << attribute << "' is not part of the "
        << "definition of an TSB Level " << level
        << " Version " << version << " <" << element << "> element.";

  if (mTSB)
  {
  //
  // (TODO) Needs to be fixed so that error can be added when
  // no TSBDocument attached.
  //
        getErrorLog()->logError(TSBUnknownCoreAttribute, level,
          version, msg.str(), getLine(), getColumn());
  }
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * Helper to log a common type of error.
 */
void
TSBBase::logUnknownElement( const string& element,
        const unsigned int level,
        const unsigned int version )
{


    ostringstream msg;

    msg << "Element '" << element << "' is not part of the definition of "
        << "TSB Level " << level << " Version " << version << ".";

    if (mTSB != NULL)
    {
      getErrorLog()->logError(TSBUnrecognizedElement,
            level, version, msg.str(), getLine(), getColumn());
    }
  

}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * Helper to log a common type of error.
 */
void
TSBBase::logEmptyString( const string& attribute,
                       const unsigned int level,
                       const unsigned int version,
                       const string& element )

{
  ostringstream msg;

  msg << "Attribute '" << attribute << "' on an "
    << element << " must not be an empty string.";

  //
  // (TODO) Needs to be fixed so that error can be added when
  // no TSBDocument attached.
  //
  if (mTSB != NULL)
    getErrorLog()->logError(TSBNotSchemaConformant,
                            level, version, msg.str(), getLine(), getColumn());
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * Convenience method for easily logging problems from within method
 * implementations.
 *
 * This is essentially a short form of getErrorLog()->logError(...)
 */
void
TSBBase::logError (  unsigned int       id
                 , const unsigned int level
                 , const unsigned int version
                 , const std::string& details )
{
  //
  // (TODO) Needs to be fixed so that error can be added when
  // no TSBDocument attached.
  //
  if ( TSBBase::getErrorLog() != NULL && mTSB != NULL)
    getErrorLog()->logError(id, getLevel(), getVersion(), details, getLine(), getColumn());
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/**
 * Subclasses should override this method to get the list of
 * expected attributes.
 * This function is invoked from corresponding readAttributes()
 * function.
 */
void
TSBBase::addExpectedAttributes(ExpectedAttributes& attributes)
{
  //
  // metaid: ID { use="optional" }  (L2v1 ->)
  //
  attributes.add("metaid");
}


/*
 * Subclasses should override this method to read values from the given
 * XMLAttributes set into their specific fields.  Be sure to call your
 * parents implementation of this method as well.
 */
void
TSBBase::readAttributes (const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes& attributes,
                       const LIBSBML_CPP_NAMESPACE_QUALIFIER ExpectedAttributes& expectedAttributes)
{
  const_cast<LIBSBML_CPP_NAMESPACE_QUALIFIER XMLAttributes&>(attributes).setErrorLog(getErrorLog());

  const unsigned int level   = getLevel  ();
  const unsigned int version = getVersion();

  //
  // check that all attributes are expected
  //
  for (int i = 0; i < attributes.getLength(); i++)
  {
    std::string name   = attributes.getName(i);
    std::string uri    = attributes.getURI(i);
    std::string prefix = attributes.getPrefix(i);

    //
    // To allow prefixed attribute whose namespace doesn't belong to
    // core or extension package.
    //
    // (e.g. xsi:type attribute in Curve element in layout extension)
    //
    if (!prefix.empty())
    {
      if ( expectedAttributes.hasAttribute(prefix + ":" + name) ) continue;
    }


    //
    // Checks if there are attributes of unknown package extensions
    //
    // if we happen to be on the tsb element (document) then
    // getPrefix() and mURI have not been set and just return defaults
    // thus a prefix does not appear to come from the right place !!!
    if (!prefix.empty() && getElementName() == "tsb")
    {
      if (!expectedAttributes.hasAttribute(name))
      {
        logUnknownAttribute(name, level, version, getElementName());
      }
    }
    else if (!expectedAttributes.hasAttribute(name))
    {
      logUnknownAttribute(name, level, version, getElementName(), prefix);
    }
  }

    bool assigned = attributes.readInto("metaid", mMetaId, getErrorLog(), false, getLine(), getColumn());

    if (assigned && mMetaId.empty())
    {
      logEmptyString("metaid", level, version,
                     TSBTypeCode_toString(getTypeCode()));
    }

    if (isSetMetaId())
    {
      if (!SyntaxChecker::isValidXMLID(mMetaId))
      {
        logError(TSBInvalidMetaidSyntax, getLevel(), getVersion(), "The metaid '" + mMetaId + "' does not conform to the syntax.");
      }
  }

}


/** @cond doxygenLibtsbInternal */
/*
 * Returns the prefix of this element.
 */
std::string
TSBBase::getPrefix() const
{
  std::string prefix = "";

  const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces *xmlns = getNamespaces();
  string uri = getURI();
  if(xmlns && mTSB)
  {
    prefix = xmlns->getPrefix(uri);
  }

  return prefix;
}


/*
 * Returns the prefix of this element.
 */
std::string
TSBBase::getTSBPrefix() const
{
  std::string prefix = "";

  const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces *xmlns = getNamespaces();
  if (xmlns == NULL)
    return getPrefix();

  for (int i = 0; i < xmlns->getNumNamespaces(); i++)
  {
    string uri = xmlns->getURI(i);
    if (TSBNamespaces::isTSBNamespace(uri))
      return xmlns->getPrefix(i);
  }

  return getPrefix();
}

/*
 * Returns the root element of this element.
 *
 * @note The root element may not be an TSBDocument element. For example,
 * this element is the root element if this element doesn't have a parent
 * TSB object (i.e. mParentTSBObject is NULL)
 */
TSBBase*
TSBBase::getRootElement()
{
  if (mTSB)
  {
    return mTSB;
  }
  else if (mParentTSBObject)
  {
    return mParentTSBObject->getRootElement();
  }
  else
  {
    return this;
  }
}


/*
 * Subclasses should override this method to write their XML attributes
 * to the XMLOutputStream.  Be sure to call your parents implementation
 * of this method as well.
 */
void
TSBBase::writeAttributes (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const
{
  string tsbPrefix    = getTSBPrefix();
  if ( !mMetaId.empty() )
  {
    stream.writeAttribute("metaid", tsbPrefix, mMetaId);
  }

}


/*
 *
 * Subclasses should override this method to write their xmlns attriubutes
 * (if any) to the XMLOutputStream.  Be sure to call your parents implementation
 * of this method as well.
 *
 */
void
TSBBase::writeXMLNS (LIBSBML_CPP_NAMESPACE_QUALIFIER XMLOutputStream& stream) const
{
  // do nothing.
}
/** @endcond */



/** @cond doxygenLibtsbInternal */
/*
  * Checks that an TSB TSBListOf element has been populated.
  * If a listOf element has been declared with no elements,
  * an error is logged.
  */
void
TSBBase::checkTSBListOfPopulated(TSBBase* object)
{
    // for now log the empty list
  if (object->getTypeCode() == TSB_LIST_OF)
  {
    if (static_cast <TSBListOf*> (object)->size() == 0)
    {
      TSBErrorCode_t error = TSBEmptyListElement;
      ostringstream errMsg;
      errMsg << object->getElementName() << " cannot be empty.";

      logError(error, getLevel(), getVersion(), errMsg.str());
    }
  }
}
/** @endcond */

//This assumes that the parent of the object is of the type TSBListOf.  If this is not the case, it will need to be overridden.
int TSBBase::removeFromParentAndDelete()
{
  TSBBase* parent = getParentTSBObject();

  if (parent==NULL) return LIBTSB_OPERATION_FAILED;
  
  TSBListOf* parentList = static_cast<TSBListOf*>(parent);
  
  if (parentList == NULL) return LIBTSB_OPERATION_FAILED;
  
  for (unsigned int i=0; i<parentList->size(); i++) 
  {
    TSBBase* sibling = parentList->get(i);
    if (sibling == this) 
    {
      parentList->remove(i);
      delete this;
      return LIBTSB_OPERATION_SUCCESS;
    }
  }
  return LIBTSB_OPERATION_FAILED;
}

/** @cond doxygenLibtsbInternal */
const std::string
TSBBase::checkMathMLNamespace(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken elem)
{
  std::string prefix = "";
  unsigned int match = 0;
  int n;
  if (elem.getNamespaces().getLength() != 0)
  {
    for (n = 0; n < elem.getNamespaces().getLength(); n++)
    {
      if (!strcmp(elem.getNamespaces().getURI(n).c_str(),
                  "http://www.w3.org/1998/Math/MathML"))
      {
        match = 1;
        break;
      }
    }
  }
  if (match == 0)
  {
    if( mTSB->getNamespaces() != NULL)
    /* check for implicit declaration */
    {
      for (n = 0; n < mTSB->getNamespaces()->getLength(); n++)
      {
        if (!strcmp(mTSB->getNamespaces()->getURI(n).c_str(),
                    "http://www.w3.org/1998/Math/MathML"))
        {
          match = 1;
          prefix = mTSB->getNamespaces()->getPrefix(n);
          break;
        }
      }
    }
  }
  if (match == 0)
  {
    logError(TSBInvalidMathElement, getLevel(), getVersion(), "The MathML namespace 'http://www.w3.org/1998/Math/MathML' was not found.");
  }

  return prefix;
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
void
TSBBase::checkDefaultNamespace(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* xmlns,
                             const std::string& elementName,
                             const std::string& prefix)
{
  //
  // checks if the given default namespace (if any) is a valid
  // TSB namespace
  //
  if (xmlns == NULL || xmlns->getLength() == 0)
    return;

  const std::string defaultURI = xmlns->getURI(prefix);
  if (defaultURI.empty() || mURI == defaultURI)
    return;

  // if this element (TSBBase derived) has notes or annotation elements,
  // it is ok for them to be in the TSB namespace!
  if ( TSBNamespaces::isTSBNamespace(defaultURI)
       && !TSBNamespaces::isTSBNamespace(mURI)
       && (elementName == "notes" || elementName == "testAnnotation"))
    return;

  static ostringstream errMsg;
  errMsg.str("");
  errMsg << "xmlns=\"" << defaultURI << "\" in <" << elementName
         << "> element is an invalid namespace." << endl;

  logError(TSBNotSchemaConformant, getLevel(), getVersion(), errMsg.str());

}

/*
  * Checks the annotation does not declare an tsb namespace.
  * If the annotation declares an tsb namespace an error is logged.
  */
void
TSBBase::checkTestAnnotation()
{
  unsigned int nNodes = 0;
  unsigned int match = 0;
  int n = 0;
  std::vector<std::string> uri_list;
  uri_list.clear();

  if (mTestAnnotation == NULL) return;

  //
  // checks if the given default namespace (if any) is a valid
  // TSB namespace
  //
  const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces &xmlns = mTestAnnotation->getNamespaces();
  checkDefaultNamespace(&xmlns,"testAnnotation");

  while (nNodes < mTestAnnotation->getNumChildren())
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode topLevel = mTestAnnotation->getChild(nNodes);

    // the top level must be an element (so it should be a start)
    if (topLevel.isStart() == false)
    {
      logError(TSBTestAnnotationNotElement, getLevel(), getVersion());
      nNodes++;
      continue;
    }
    std::string uri = topLevel.getURI();
    std::string prefix = topLevel.getPrefix();

#ifdef USE_LIBXML
    // sometimes libxml does not catch an empty ns with a prefix
    if (uri.empty() && !prefix.empty())
    {
      logError(BadXMLPrefix);
      nNodes++;
      continue;
    }
#endif

    // cannot be other toplevel element with this uri
    if (!uri.empty())
    {
      if (find(uri_list.begin(), uri_list.end(), uri)
                                               != uri_list.end())
      {
        string msg = "An TSB <" + getElementName() + "> element ";
        msg += "has an <annotation> child with multiple children with the same namespace.";
        logError(TSBDuplicateTestAnnotationNamespaces, getLevel(), getVersion(), msg);
      }
      uri_list.push_back(uri);
    }

    match = 0;
    n = 0;

    bool implicitNSdecl = false;
   // must have a namespace
    if (topLevel.getNamespaces().getLength() == 0)
    {
      // not on actual element - is it explicit ??
      if(mTSB != NULL && mTSB->getNamespaces() != NULL)
      /* check for implicit declaration */
      {
        for (n = 0; n < mTSB->getNamespaces()->getLength(); n++)
        {
          if (!strcmp(mTSB->getNamespaces()->getPrefix(n).c_str(),
                        prefix.c_str()))
          {
            implicitNSdecl = true;
            break;
          }
        }
     }


      if (!implicitNSdecl)
      {
        logError(TSBMissingTestAnnotationNamespace);
      }
    }
    // cannot declare tsb namespace
    while(!match && n < topLevel.getNamespaces().getLength())
    {
      match += !strcmp(topLevel.getNamespaces().getURI(n).c_str(),
                                          "http://testsbxml.org/l1v1");
      n++;
    }
    string msg = "An TSB <" + getElementName() + "> element ";
    if (match > 0)
    {
      msg += "uses a restricted namespace on an element in its child <annotation>.";
      logError(TSBNamespaceInTestAnnotation, getLevel(), getVersion(), msg);
      break;
    }

    if (implicitNSdecl && prefix.empty())
    {
      msg += "assumes the tsb namespace on an element in its child <annotation>.";
      logError(TSBMissingTestAnnotationNamespace, getLevel(), getVersion(), msg);
    }
    nNodes++;
  }
}
/** @endcond */


/** @cond doxygenLibtsbInternal */
/*
 * Checks that the XHTML is valid.
 * If the xhtml does not conform to the specification of valid xhtml within
 * an tsb document, an error is logged.
 */
void
TSBBase::checkXHTML(const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNode * xhtml)
{
  if (xhtml == NULL) return;

  const string&  name = xhtml->getName();
  unsigned int i, errorNS, errorXML, errorDOC, errorELEM;

  if (name == "notes")
  {
    errorNS   = TSBNotesNotInXHTMLNamespace;
    errorXML  = TSBNotesContainsXMLDecl;
    errorDOC  = TSBNotesContainsDOCTYPE;
    errorELEM = TSBInvalidNotesContent;
  }
  else                                  // We shouldn't ever get to this point.
  {
    logError(TSBUnknown);
    return;
  }

  /*
  * errors relating to a misplaced XML or DOCTYPE declaration
  * will also cause a parser error.
  * since parsing will terminate at this error, then if it has occurred
  * it will be in the XML currently being checked and so a more
  * informative message can be added
  */
  for (i = 0; i < getErrorLog()->getNumErrors(); i++)
  {
    if (getErrorLog()->getError(i)->getErrorId() == BadXMLDeclLocation)
    {
      logError(errorXML);
    }
    if (getErrorLog()->getError(i)->getErrorId() == BadlyFormedXML)
    {
      logError(errorDOC);
    }
  }

  LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces* toplevelNS = (mTSB) ? mTSB->getNamespaces() : NULL;

  /*
  * namespace declaration is variable
  * if a whole html tag has been used
  * or a whole body tag then namespace can be implicitly declared
  */
  unsigned int children = xhtml->getNumChildren();

  if (children > 1)
  {
    for (i=0; i < children; i++)
    {
      if (SyntaxChecker::isAllowedElement(xhtml->getChild(i)))
      {
        if (!SyntaxChecker::hasDeclaredNS(xhtml->getChild(i),
                                                  toplevelNS))
        {
          logError(errorNS);
        }
      }
      else
      {
        logError(errorELEM);
      }
    }
  }
  else
  {
    /* only one element which can be html or body with either implicit/explicit
    * namespace declaration
    * OR could be one of the listed elements.
    */

    const string& top_name = xhtml->getChild(0).getName();

    if (top_name != "html" && top_name != "body"
      && !SyntaxChecker::isAllowedElement(xhtml->getChild(0)))
    {
      logError(errorELEM);
    }
    else
    {
      if (!SyntaxChecker::hasDeclaredNS(xhtml->getChild(0), toplevelNS))
      {
        logError(errorNS);
      }
      if (top_name == "html"
        && !SyntaxChecker::isCorrectHTMLNode(xhtml->getChild(0)))
      {
        logError(errorELEM);
      }
    }
  }
}
/** @endcond */
/** @cond doxygenLibtsbInternal */
/* default for components that have no required attributes */
bool
TSBBase::hasRequiredAttributes() const
{
  return true;
}

/* default for components that have no required elements */
bool
TSBBase::hasRequiredElements() const
{
  return true;
}

int
TSBBase::checkCompatibility(const TSBBase * object) const
{
  if (object == NULL)
  {
    return LIBTSB_OPERATION_FAILED;
  }
  else if (!(object->hasRequiredAttributes()) || !(object->hasRequiredElements()))
  {
    return LIBTSB_INVALID_OBJECT;
  }
  else if (getLevel() != object->getLevel())
  {
    return LIBTSB_LEVEL_MISMATCH;
  }
  else if (getVersion() != object->getVersion())
  {
    return LIBTSB_VERSION_MISMATCH;
  }
  else if (this->matchesRequiredTSBNamespacesForAddition(object) == false)
  {
    return LIBTSB_NAMESPACES_MISMATCH;
  }
  else
  {
    return LIBTSB_OPERATION_SUCCESS;
  }
}

/** @endcond */

/** @cond doxygenLibtsbInternal */
/*
 * Stores the location (line and column) and any XML namespaces (for
 * roundtripping) declared on this TSB (XML) element.
 */
void
TSBBase::setTSBBaseFields (const LIBSBML_CPP_NAMESPACE_QUALIFIER XMLToken& element)
{
  mLine   = element.getLine  ();
  mColumn = element.getColumn();

  if (element.getNamespaces().getLength() > 0)
  {
    LIBSBML_CPP_NAMESPACE_QUALIFIER XMLNamespaces tmpxmlns(element.getNamespaces());
    setNamespaces(&tmpxmlns);
  }
  else
  {
    setNamespaces(NULL);
  }
}


/*
 * Sets the XML namespace to which this element belongs to.
 */
int
TSBBase::setElementNamespace(const std::string &uri)
{
  mURI = uri;

  return LIBTSB_OPERATION_SUCCESS;
}

/*
 * Gets the XML namespace to which this element belongs to.
 */
const std::string&
TSBBase::getElementNamespace() const
{
  return mURI;
}
/** @endcond */

#endif /* __cplusplus */


LIBTSB_EXTERN
int
TSBBase_getTypeCode (const TSBBase_t *sb)
{
  return (sb != NULL) ? sb->getTypeCode() : TSB_UNKNOWN;
}


LIBTSB_EXTERN
const char *
TSBBase_getMetaId (TSBBase_t *sb)
{
  return (sb != NULL && sb->isSetMetaId()) ? sb->getMetaId().c_str() : NULL;
}


LIBTSB_EXTERN
const TSBDocument_t *
TSBBase_getTSBDocument (TSBBase_t *sb)
{
  return (sb != NULL) ? sb->getTSBDocument() : NULL;
}


LIBTSB_EXTERN
const TSBBase_t *
TSBBase_getParentTSBObject (TSBBase_t *sb)
{
  return (sb != NULL) ? sb->getParentTSBObject() : NULL;
}


LIBTSB_EXTERN
const TSBBase_t *
TSBBase_getAncestorOfType (TSBBase_t *sb, int type)
{
  return (sb != NULL) ? sb->getAncestorOfType(type) : NULL;
}


LIBTSB_EXTERN
unsigned int
TSBBase_getLevel (const TSBBase_t *sb)
{
  return (sb != NULL) ? sb->getLevel() : TSB_INT_MAX;
}


LIBTSB_EXTERN
unsigned int
TSBBase_getVersion (const TSBBase_t *sb)
{
  return (sb != NULL) ? sb->getVersion() : TSB_INT_MAX;
}


LIBTSB_EXTERN
XMLNode_t *
TSBBase_getNotes (TSBBase_t *sb)
{
  return (sb != NULL) ? sb->getNotes() : NULL;
}


LIBTSB_EXTERN
char*
TSBBase_getNotesString (TSBBase_t *sb)
{
  return (sb != NULL && sb->isSetNotes()) ?
    safe_strdup(sb->getNotesString().c_str()) : NULL;
}


LIBTSB_EXTERN
XMLNode_t *
TSBBase_getTestAnnotation (TSBBase_t *sb)
{
  return (sb != NULL) ? sb->getTestAnnotation() : NULL;
}


LIBTSB_EXTERN
char*
TSBBase_getTestAnnotationString (TSBBase_t *sb)
{
  return (sb != NULL && sb->isSetTestAnnotation()) ?
    safe_strdup(sb->getTestAnnotationString().c_str()) : NULL;
}


LIBTSB_EXTERN
int
TSBBase_isSetMetaId (const TSBBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetMetaId() ) : 0;
}


LIBTSB_EXTERN
int
TSBBase_isSetNotes (const TSBBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetNotes() ) : 0;
}


LIBTSB_EXTERN
int
TSBBase_isSetTestAnnotation (const TSBBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetTestAnnotation() ) : 0;
}


LIBTSB_EXTERN
int
TSBBase_setMetaId (TSBBase_t *sb, const char *metaid)
{
  if (sb != NULL)
    return (metaid == NULL) ? sb->unsetMetaId() : sb->setMetaId(metaid);
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_setNamespaces (TSBBase_t *sb, XMLNamespaces_t *xmlns)
{
  if (sb != NULL)
    return sb->setNamespaces(xmlns);
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_setNotes (TSBBase_t *sb, XMLNode_t *notes)
{
  if (sb != NULL)
    return sb->setNotes(notes);
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_setNotesString (TSBBase_t *sb, const char *notes)
{
  if (sb != NULL)
  {
    if(notes == NULL)
    {
      return sb->unsetNotes();
    }
    else
    {
      return sb->setNotes(notes);
    }
  }
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_setNotesStringAddMarkup (TSBBase_t *sb, const char *notes)
{
  if (sb != NULL)
  {
    if(notes == NULL)
    {
      return sb->unsetNotes();
    }
    else
    {
      return sb->setNotes(notes, true);
    }
  }
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_appendNotes (TSBBase_t *sb, XMLNode_t *notes)
{
  if (sb != NULL)
    return sb->appendNotes(notes);
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_appendNotesString (TSBBase_t *sb, const char *notes)
{
  if (sb != NULL)
  {
    if (notes != NULL)
      return sb->appendNotes(notes);
    else
      return LIBTSB_INVALID_OBJECT;
  }
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_setTestAnnotation (TSBBase_t *sb, XMLNode_t *annotation)
{
  if (sb != NULL)
    return sb->setTestAnnotation(annotation);
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_setTestAnnotationString (TSBBase_t *sb, const char *annotation)
{
  if (sb != NULL)
  {
    if(annotation == NULL)
    {
      return sb->unsetTestAnnotation();
    }
    else
    {
      return sb->setTestAnnotation(annotation);
    }
  }
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_appendTestAnnotation (TSBBase_t *sb, XMLNode_t *annotation)
{
  if (sb != NULL)
    return sb->appendTestAnnotation(annotation);
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_appendTestAnnotationString (TSBBase_t *sb, const char *annotation)
{
  if (sb != NULL)
  {
    if (annotation != NULL)
      return sb->appendTestAnnotation(annotation);
    else
      return LIBTSB_INVALID_OBJECT;
  }
  else
    return LIBTSB_INVALID_OBJECT;
}

LIBTSB_EXTERN
int
TSBBase_removeTopLevelTestAnnotationElement (TSBBase_t *sb, const char *name)
{
  if (sb != NULL)
  {
    if (name != NULL)
      return sb->removeTopLevelTestAnnotationElement(name);
    else
      return LIBTSB_INVALID_OBJECT;
  }
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_removeTopLevelTestAnnotationElementWithURI (TSBBase_t *sb, const char *name,
                                              const char *uri)
{
  if (sb != NULL)
  {
    if (name != NULL && uri != NULL)
      return sb->removeTopLevelTestAnnotationElement(name, uri);
    else
      return LIBTSB_INVALID_OBJECT;
  }
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_replaceTopLevelTestAnnotationElement (TSBBase_t *sb, XMLNode_t *annotation)
{
  if (sb != NULL)
  {
    if (annotation != NULL)
      return sb->replaceTopLevelTestAnnotationElement(annotation);
    else
      return LIBTSB_INVALID_OBJECT;
  }
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_replaceTopLevelTestAnnotationElementString (TSBBase_t *sb, const char *annotation)
{
  if (sb != NULL)
  {
    if (annotation != NULL)
      return sb->replaceTopLevelTestAnnotationElement(annotation);
    else
      return LIBTSB_INVALID_OBJECT;
  }
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_unsetMetaId (TSBBase_t *sb)
{
  if (sb != NULL)
    return sb->unsetMetaId();
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_unsetNotes (TSBBase_t *sb)
{
  if (sb != NULL)
    return sb->unsetNotes();
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
int
TSBBase_unsetTestAnnotation (TSBBase_t *sb)
{
  if (sb != NULL)
    return sb->unsetTestAnnotation();
  else
    return LIBTSB_INVALID_OBJECT;
}


LIBTSB_EXTERN
const char *
TSBBase_getElementName (const TSBBase_t *sb)
{
  return (sb != NULL && !(sb->getElementName().empty())) ?
    sb->getElementName().c_str() : NULL;
}


LIBTSB_EXTERN
unsigned int
TSBBase_getLine (const TSBBase_t *sb)
{
  return (sb != NULL) ? sb->getLine() : 0;
}


LIBTSB_EXTERN
unsigned int
TSBBase_getColumn (const TSBBase_t *sb)
{
  return (sb != NULL) ? sb->getColumn() : 0;
}


LIBTSB_EXTERN
int
TSBBase_hasValidLevelVersionNamespaceCombination(TSBBase_t *sb)
{
  return (sb != NULL) ?
    static_cast <int> (sb->hasValidLevelVersionNamespaceCombination()) : 0;
}


LIBTSB_EXTERN
int
TSBBase_setUserData(TSBBase_t* sb, void *userData)
{
  if (sb == NULL) return LIBTSB_INVALID_OBJECT;
  return sb->setUserData(userData);
}


LIBTSB_EXTERN
void *
TSBBase_getUserData(const TSBBase_t* sb)
{
  if (sb == NULL) return NULL;
  return sb->getUserData();
}

LIBTSB_EXTERN
int
TSBBase_isSetUserData(const TSBBase_t* sb)
{
  if (sb == NULL) return 0;
  return static_cast <int>(sb->isSetUserData());
}

LIBTSB_EXTERN
int
TSBBase_unsetUserData(TSBBase_t* sb)
{
  if (sb == NULL) return LIBTSB_INVALID_OBJECT;
  return sb->unsetUserData();
}

LIBTSB_EXTERN
TSBBase_t*
TSBBase_getElementByMetaId(TSBBase_t* sb, const char* metaid)
{
  if (sb == NULL) return NULL;
  return sb->getElementByMetaId(metaid);
}

LIBTSB_EXTERN
List_t*
TSBBase_getAllElements(TSBBase_t* sb)
{
  if (sb == NULL) return NULL;
  return sb->getAllElements();
}

/** @endcond */

LIBTSB_CPP_NAMESPACE_END
