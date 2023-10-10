#include <CUnit/Basic.h>
#include "linked_list.h"
#include <stdlib.h>
#include <string.h>
#include "iterator.h"

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

/********************************************************************/
/*                         Linked List                              */
/********************************************************************/

void test_list_create_destroy()
{
  ioopm_list_t *lst = ioopm_linked_list_create();
  ioopm_linked_list_append(lst, 1);
  ioopm_linked_list_append(lst, 2);
  ioopm_linked_list_append(lst, 3);
  CU_ASSERT_PTR_NOT_NULL(lst);
  ioopm_linked_list_destroy(&lst);
  CU_ASSERT_PTR_NULL(lst);
}

void test_link_append()
{
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

  ioopm_linked_list_destroy(&lst);
}

void test_linked_list_remove()
{
  ioopm_list_t *testList = ioopm_linked_list_create();
  ioopm_linked_list_append(testList, 1);
  ioopm_linked_list_append(testList, 2);
  ioopm_linked_list_append(testList, 3);
  ioopm_linked_list_append(testList, 4);
  CU_ASSERT_EQUAL(testList->size, 4);
  int rmv_val = ioopm_linked_list_remove(testList, 1);
  CU_ASSERT_EQUAL(rmv_val, 2);
  ioopm_link_t *first_elem = testList->head;
  ioopm_link_t *second_elem = first_elem->next;
  CU_ASSERT_EQUAL(first_elem->next->value, 3);
  CU_ASSERT_EQUAL(second_elem->value, 3);
  CU_ASSERT_EQUAL(testList->size, 3);
  ioopm_linked_list_destroy(&testList);
}

void test_link_prepend()
{
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

void test_list_get()
{
  ioopm_list_t *lst = ioopm_linked_list_create();

  ioopm_linked_list_append(lst, 1);
  ioopm_linked_list_append(lst, 2);

  int val = ioopm_linked_list_get(lst, 1);

  CU_ASSERT_EQUAL(val, 2);

  ioopm_linked_list_destroy(&lst);
}

void test_linked_list_contains()
{
  ioopm_list_t *testList = ioopm_linked_list_create();
  ioopm_linked_list_append(testList, 1);
  ioopm_linked_list_append(testList, 2);
  ioopm_linked_list_append(testList, 3);
  ioopm_linked_list_append(testList, 4);

  CU_ASSERT_TRUE(ioopm_linked_list_contains(testList, 1));
  CU_ASSERT_TRUE(ioopm_linked_list_contains(testList, 3));
  CU_ASSERT_TRUE(ioopm_linked_list_contains(testList, 4));
  CU_ASSERT_FALSE(ioopm_linked_list_contains(testList, 5));

  ioopm_linked_list_destroy(&testList);
}

void test_list_size()
{
  ioopm_list_t *list = ioopm_linked_list_create();

  bool is_empty = ioopm_linked_list_is_empty(list);
  CU_ASSERT_TRUE(is_empty);
  size_t sizeIsZero = 0;
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), sizeIsZero); 

  ioopm_linked_list_append(list, 1);
  ioopm_linked_list_append(list, 2);
  ioopm_linked_list_append(list, 3);

  is_empty = ioopm_linked_list_is_empty(list);

  size_t sizeIs3 = 3;
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), sizeIs3); 
  CU_ASSERT_FALSE(is_empty);

  ioopm_linked_list_destroy(&list);
}

void test_list_clear()
{
  ioopm_list_t *list = ioopm_linked_list_create();

  ioopm_linked_list_append(list, 1);
  ioopm_linked_list_append(list, 2);
  ioopm_linked_list_append(list, 3);

  ioopm_linked_list_clear(list);

  bool is_empty = ioopm_linked_list_is_empty(list);
  CU_ASSERT_TRUE(is_empty);

  CU_ASSERT_PTR_NULL(list->head);
  CU_ASSERT_PTR_NULL(list->last);
  size_t sizeIsZero = 0;
  CU_ASSERT_EQUAL(ioopm_linked_list_size(list), sizeIsZero); 

  ioopm_linked_list_destroy(&list);
}

void test_all()
{
  ioopm_list_t *list = ioopm_linked_list_create();

  ioopm_linked_list_append(list, 1);
  ioopm_linked_list_append(list, 34);
  ioopm_linked_list_append(list, 50);

  int num = 10;
  bool pass_pred_all_1 = ioopm_linked_list_all(list, isSpecificInt, &num);
  CU_ASSERT_FALSE(pass_pred_all_1);

  ioopm_linked_list_clear(list);
  ioopm_linked_list_append(list, 10);
  ioopm_linked_list_append(list, 10);
  ioopm_linked_list_append(list, 10);

  bool pass_pred_all_2 = ioopm_linked_list_all(list, isSpecificInt, &num);
  CU_ASSERT_TRUE(pass_pred_all_2);

  ioopm_linked_list_destroy(&list);
}

void test_any()
{
  ioopm_list_t *list = ioopm_linked_list_create();

  // no elements fulfill the predicate
  ioopm_linked_list_append(list, 1);
  ioopm_linked_list_append(list, 34);
  ioopm_linked_list_append(list, 50);

  int num = 10;
  bool pass_pred_all_1 = ioopm_linked_list_any(list, isSpecificInt, &num);
  CU_ASSERT_FALSE(pass_pred_all_1);
  ioopm_linked_list_clear(list);

  // one elements fulfill the predicate
  ioopm_linked_list_clear(list);
  ioopm_linked_list_append(list, 10);
  ioopm_linked_list_append(list, 9);
  ioopm_linked_list_append(list, 8);

  bool pass_pred_all_2 = ioopm_linked_list_any(list, isSpecificInt, &num);
  CU_ASSERT_TRUE(pass_pred_all_2);

  ioopm_linked_list_clear(list);

  // all elements fulfill the predicate
  ioopm_linked_list_append(list, 10);
  ioopm_linked_list_append(list, 10);
  ioopm_linked_list_append(list, 10);
  bool pass_pred_all_3 = ioopm_linked_list_any(list, isSpecificInt, &num);
  CU_ASSERT_TRUE(pass_pred_all_3);

  ioopm_linked_list_destroy(&list);
}

void test_apply_all()
{
  ioopm_list_t *list = ioopm_linked_list_create();

  // no elements fulfill the predicate
  ioopm_linked_list_append(list, 1);
  ioopm_linked_list_append(list, 34);
  ioopm_linked_list_append(list, 50);

  int num = 10;
  CU_ASSERT_EQUAL(list->head->value, 1);
  ioopm_linked_list_apply_to_all(list, add_int, &num);

  int val1 = ioopm_linked_list_get(list, 0);
  int val2 = ioopm_linked_list_get(list, 1);
  int val3 = ioopm_linked_list_get(list, 2);

  CU_ASSERT_EQUAL(val1, 11);
  CU_ASSERT_EQUAL(val2, 44);
  CU_ASSERT_EQUAL(val3, 60);

  ioopm_linked_list_destroy(&list);
}

/********************************************************************/
/*                          Iterator                                */
/********************************************************************/

void test_iter_create_destroy()
{
  // initialize list and iterator
  ioopm_list_t *lst = ioopm_linked_list_create();

  // append one element to test iterator update
  ioopm_linked_list_append(lst, 1);

  ioopm_list_iterator_t *iter = ioopm_list_iterator(lst);

  int first = iter->current->value;
  ioopm_list_t *compList = iter->list;

  CU_ASSERT_PTR_NOT_NULL(iter);
  CU_ASSERT_EQUAL(first, lst->head->value);
  CU_ASSERT_EQUAL(compList->size, 1);
  CU_ASSERT_PTR_NOT_NULL(compList->last);

  ioopm_iterator_destroy(&iter);
  CU_ASSERT_PTR_NULL(iter);
  ioopm_linked_list_destroy(&lst);
}

void test_has_next()
{
  ioopm_list_t *lst = ioopm_linked_list_create();

  ioopm_linked_list_append(lst, 1);

  ioopm_list_iterator_t *iter1 = ioopm_list_iterator(lst);
  bool hasNext = ioopm_iterator_has_next(iter1);
  CU_ASSERT_FALSE(hasNext);

  ioopm_linked_list_append(lst, 2);

  ioopm_list_iterator_t *iter2 = ioopm_list_iterator(lst);
  hasNext = ioopm_iterator_has_next(iter2);
  CU_ASSERT_TRUE(hasNext);

  ioopm_iterator_destroy(&iter1);
  ioopm_iterator_destroy(&iter2);
  ioopm_linked_list_destroy(&lst);
}

void test_iter_next()
{
  ioopm_list_t *lst = ioopm_linked_list_create();

  ioopm_linked_list_append(lst, 1);
  ioopm_linked_list_append(lst, 2);

  ioopm_list_iterator_t *iter = ioopm_list_iterator(lst);
  int next = ioopm_iterator_next(iter);

  int val = ioopm_linked_list_get(lst, 1);
  CU_ASSERT_EQUAL(next, val);

  ioopm_iterator_destroy(&iter);
  ioopm_linked_list_destroy(&lst);
}

void test_iter_reset()
{
  ioopm_list_t *lst = ioopm_linked_list_create();

  ioopm_linked_list_append(lst, 1);
  ioopm_linked_list_append(lst, 2);

  ioopm_list_iterator_t *iter = ioopm_list_iterator(lst);

  int nonReset = iter->current->value;

  int nextIter = ioopm_iterator_next(iter);

  ioopm_iterator_reset(iter);
  int resetIter = iter->current->value;

  CU_ASSERT_NOT_EQUAL(resetIter, nextIter);
  CU_ASSERT_EQUAL(nonReset, resetIter);

  ioopm_iterator_destroy(&iter);
  ioopm_linked_list_destroy(&lst);
}

void test_iter_curr()
{
  ioopm_list_t *lst = ioopm_linked_list_create();

  ioopm_linked_list_append(lst, 1);
  ioopm_linked_list_append(lst, 2);

  ioopm_list_iterator_t *iter = ioopm_list_iterator(lst);

  int curr = ioopm_iterator_current(iter);
  int realCurr1 = ioopm_linked_list_get(lst, 0);
  CU_ASSERT_EQUAL(curr, realCurr1);

  ioopm_iterator_next(iter);
  curr = ioopm_iterator_current(iter);
  int realCurr2 = ioopm_linked_list_get(lst, 1);
  CU_ASSERT_EQUAL(curr, realCurr2);
  CU_ASSERT_NOT_EQUAL(curr, realCurr1);

  ioopm_iterator_destroy(&iter);
  ioopm_linked_list_destroy(&lst);
}

/********************************************************************/
/*                            Main                                  */
/********************************************************************/
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
      (CU_add_test(my_test_suite, "Test removal of element at index", test_linked_list_remove) == NULL) ||
      (CU_add_test(my_test_suite, "Test get value", test_list_get) == NULL) ||
      (CU_add_test(my_test_suite, "Test list contains element", test_linked_list_contains) == NULL) ||
      (CU_add_test(my_test_suite, "Test list size", test_list_size) == NULL) ||
      (CU_add_test(my_test_suite, "Test list clear", test_list_clear) == NULL) ||
      (CU_add_test(my_test_suite, "Test list pred all", test_all) == NULL) ||
      (CU_add_test(my_test_suite, "Test list pred any", test_any) == NULL) ||
      (CU_add_test(my_test_suite, "Test list apply fun all", test_apply_all) == NULL) ||
      (CU_add_test(my_test_suite, "Test iterator create destroy", test_iter_create_destroy) == NULL) ||
      (CU_add_test(my_test_suite, "Test iterator has next", test_has_next) == NULL) ||
      (CU_add_test(my_test_suite, "Test iterator next val", test_iter_next) == NULL) ||
      (CU_add_test(my_test_suite, "Test iterator reset", test_iter_reset) == NULL) ||
      (CU_add_test(my_test_suite, "Test iterator get current", test_iter_curr) == NULL) ||
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