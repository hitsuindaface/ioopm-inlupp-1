#include <CUnit/Basic.h>
#include "linked_list.h"
#include <stdlib.h>
#include <string.h>


int init_suite(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

void test_list_create_destroy() {
  ioopm_list_t *lst = ioopm_linked_list_create();
  ioopm_linked_list_append(lst, 1);
  ioopm_linked_list_append(lst, 2);
  ioopm_linked_list_append(lst, 3);
  CU_ASSERT_PTR_NOT_NULL(lst);
  ioopm_linked_list_destroy(&lst);
  CU_ASSERT_PTR_NULL(lst);
}

void test_link_append(){
  ioopm_list_t *lst = ioopm_linked_list_create();
  ioopm_linked_list_append(lst, 1);
  ioopm_linked_list_append(lst, 2);
  ioopm_linked_list_append(lst, 3);

  ioopm_link_t *first_elem = lst->head;
  ioopm_link_t *second_elem = first_elem->next;
  ioopm_link_t *third_elem = second_elem->next;

  int first_value = first_elem->value;
  int second_value = second_elem->value;
  int third_value = third_elem->value;

  CU_ASSERT_EQUAL(first_value, 1);
  CU_ASSERT_EQUAL(second_value, 2); 
  CU_ASSERT_EQUAL(third_value, 3);
}

void test_link_

void test_link_prepend(){
  ioopm_list_t *lst = ioopm_linked_list_create();
    ioopm_linked_list_append(lst, 1);
    ioopm_linked_list_append(lst, 2);
    ioopm_linked_list_append(lst, 3);
    ioopm_linked_list_prepend(lst, 4);
    ioopm_link_t *first_elem = lst->head;
    int value = first_elem->value;
    CU_ASSERT_EQUAL(value, 4);
    CU_ASSERT_PTR_NOT_NULL(lst);
    ioopm_linked_list_destroy(&lst);
}



int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Linked list test suite", init_suite, clean_suite);
  if (my_test_suite == NULL)
  {
    // If the test suite could not be added, tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
      (CU_add_test(my_test_suite, "Create destroy linked list", test_list_create_destroy) == NULL) ||
      (CU_add_test(my_test_suite, "Append", test_link_append) == NULL) ||
      (CU_add_test(my_test_suite, "Prepend", test_link_prepend) == NULL) ||
      0) 
  {
    // If adding any of the tests fails, we tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}