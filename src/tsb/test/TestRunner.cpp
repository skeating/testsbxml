/**
 * \file    TestRunner.c
 * \brief   Runs all unit tests in the xml module
 * \author  Ben Bornstein and Michael Hucka
 * 
 * ---------------------------------------------------------------------- -->*/

#include <string.h>
#include <check.h>


Suite *create_suite_CopyAndClone (void);
Suite *create_suite_CommentClass (void);

int
main (int argc, char* argv[]) 
{ 
  int num_failed = 0;
  SRunner *runner = srunner_create(create_suite_CopyAndClone());
  srunner_add_suite(runner, create_suite_CommentClass());

  srunner_run_all(runner, CK_NORMAL);
  num_failed = srunner_ntests_failed(runner);

  srunner_free(runner);

  return num_failed;
}

