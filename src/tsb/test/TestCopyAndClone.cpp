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

#include <iostream>

#include "catch.hpp"

#include <tsb/common/common.h>
#include <tsb/TSBNamespaces.h>

LIBTSB_CPP_NAMESPACE_USE


TEST_CASE("test_NS_copyConstructor")
{
  std::cout << "in NS copy \n";
  TSBNamespaces * ns = new TSBNamespaces(1,1);

  REQUIRE(ns);
  
  REQUIRE( ns->getLevel() == 1 );
  //fail_unless( ns->getVersion() == 0 );

  //XMLNamespaces * ns2 = new XMLNamespaces(*ns);

  //fail_unless( ns2->getLength() == 1 );
  //fail_unless( ns2->isEmpty() == 0 );
  //fail_unless(ns2->getPrefix(0) == "test1");
  //fail_unless(ns2->getURI("test1") == "http://test1.org/");

  //delete ns2;
  delete ns;
}
//
//
////START_TEST ( test_NS_assignmentOperator )
////{
////  XMLNamespaces * ns = new XMLNamespaces();
////  ns->add("http://test1.org/", "test1");
////  
////  fail_unless( ns->getLength() == 1 );
////  fail_unless( ns->isEmpty() == 0 );
////  fail_unless(ns->getPrefix(0) == "test1");
////  fail_unless(ns->getURI("test1") == "http://test1.org/");
////
////  XMLNamespaces * ns2 = new XMLNamespaces();
////  (*ns2) = *ns;
////
////  fail_unless( ns2->getLength() == 1 );
////  fail_unless( ns2->isEmpty() == 0 );
////  fail_unless(ns2->getPrefix(0) == "test1");
////  fail_unless(ns2->getURI("test1") == "http://test1.org/");
////
////  delete ns2;
////  delete ns;
////}
////END_TEST
////
////
////START_TEST ( test_NS_clone )
////{
////  XMLNamespaces * ns = new XMLNamespaces();
////  ns->add("http://test1.org/", "test1");
////  
////  fail_unless( ns->getLength() == 1 );
////  fail_unless( ns->isEmpty() == 0 );
////  fail_unless(ns->getPrefix(0) == "test1");
////  fail_unless(ns->getURI("test1") == "http://test1.org/");
////
////  XMLNamespaces * ns2 = static_cast<XMLNamespaces*>(ns->clone());
////
////  fail_unless( ns2->getLength() == 1 );
////  fail_unless( ns2->isEmpty() == 0 );
////  fail_unless(ns2->getPrefix(0) == "test1");
////  fail_unless(ns2->getURI("test1") == "http://test1.org/");
////
////  delete ns2;
////  delete ns;
////}
////END_TEST
////
////
//Suite *
//create_suite_CopyAndClone (void)
//{
//  Suite *suite = suite_create("CopyAndClone");
//  TCase *tcase = tcase_create("CopyAndClone");
//
//  tcase_add_test( tcase, test_NS_copyConstructor );
//  //tcase_add_test( tcase, test_NS_assignmentOperator );
//  //tcase_add_test( tcase, test_NS_clone );
//
//  suite_add_tcase(suite, tcase);
//
//  return suite;
//}
//
