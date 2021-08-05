/**
 * \file    TestCopyAndClone.cpp
 * \brief   Read LibLX unit tests
 * \author  Ben Bornstein
 * 
 * <!--------------------------------------------------------------------------
 * This file is part of libLX.  Please visit http://sbml.org for more
 * information about LX, and the latest version of libLX.
 *
 * Copyright (C) 2019 jointly by the following organizations:
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2013-2018 jointly by the following organizations:
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *     3. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2009-2013 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/

#include <tsb/common/common.h>
#include <tsb/TSBComment.h>


#include <check.h>
LIBTSB_CPP_NAMESPACE_BEGIN

START_TEST ( test_Comment_contributor )
{
  TSBComment *c = new TSBComment(1, 1);

  fail_unless(c->isSetContributor() == false);
  fail_unless(c->getContributor() == "");

  c->setContributor("sarah");

  fail_unless(c->isSetContributor() == true);
  fail_unless(c->getContributor() == "sarah");

  fail_unless(c->unsetContributor() == LIBTSB_OPERATION_SUCCESS);

  fail_unless(c->isSetContributor() == false);
  fail_unless(c->getContributor() == "");

  delete c;
}
END_TEST

Suite *
create_suite_CommentClass (void)
{
  Suite *suite = suite_create("CommentClass");
  TCase *tcase = tcase_create("CommentClass");

  tcase_add_test( tcase, test_Comment_contributor );

  suite_add_tcase(suite, tcase);

  return suite;
}

LIBTSB_CPP_NAMESPACE_END