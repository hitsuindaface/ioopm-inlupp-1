#include <CUnit/Basic.h>
#include "utils.h"
#include "hash_table.h"

int init_suite(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void)
{
  // Change this function if you want to do something *after* you
  // These are example test functions. You should replace them with
  void test1(void)
  {
    CU_ASSERT(42);
  }

  void test2(void)
  {
    CU_ASSERT_EQUAL(1 + 1, 2);
  }

  void test_create_destroy()
  {
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    CU_ASSERT_PTR_NOT_NULL(ht);
    ioopm_hash_table_destroy(&ht);
    CU_ASSERT_PTR_NULL(ht);
  }

  void test_new_key()
  {
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    int valid_key = 17; // A valid integer key
    char *msg = "test message";

    // Check the state of the hashtable before insertion
    option_t beforeInsert = ioopm_hash_table_lookup(ht, valid_key);
    char *value = beforeInsert.value;
    CU_ASSERT_PTR_NULL(value); // It should be NULL before insertion

    // Insert with a valid key
    ioopm_hash_table_insert(ht, valid_key, msg);

    // Check the state of the hashtable after insertion
    option_t afterInsert = ioopm_hash_table_lookup(ht, valid_key);
    char *value2 = afterInsert.value;
    CU_ASSERT_FATAL(afterInsert.success);
    CU_ASSERT_STRING_EQUAL(value2, msg); // It should contain the message now

    ioopm_hash_table_destroy(&ht);
  }

  void test_dirty_key_use()
  {
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    int key = 1; // A valid integer key
    char *msg1 = "test message 1";
    char *msg2 = "test message 2";

    // Insert a key-value pair with the key (clean)
    ioopm_hash_table_insert(ht, key, msg1);

    // Attempt to insert another key-value pair with the same key (dirty)
    ioopm_hash_table_insert(ht, key, msg2);

    // Check the state of the hashtable for the key
    option_t accVal = ioopm_hash_table_lookup(ht, key);

    // Ensure that the value associated with the key is the last inserted value
    CU_ASSERT_STRING_EQUAL(accVal.value, msg2);

    ioopm_hash_table_destroy(&ht);
  }

  void test_invalid_key()
  {
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    int invalid_key = -1; // An invalid integer key
    char *msg = "test message";

    // Check the state of the hashtable before insertion
    option_t beforeInsert = ioopm_hash_table_lookup(ht, invalid_key);
    CU_ASSERT_PTR_NULL(beforeInsert.value); // It should be NULL before insertion

    // Insert with an invalid key
    ioopm_hash_table_insert(ht, invalid_key, msg);

    // Check the state of the hashtable after insertion
    option_t afterInsert = ioopm_hash_table_lookup(ht, invalid_key);
    CU_ASSERT_PTR_NULL(afterInsert.value); // It should still be NULL

    ioopm_hash_table_destroy(&ht);
  }

  void test_delete_key()
  {
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    int key1 = 0; // A valid integer key
    int key2 = 1;
    char *msg1 = "första msg";
    char *msg2 = "andra msg";

    // Check the state of the hashtable before insertion
    option_t beforeInsert = ioopm_hash_table_lookup(ht, key1);
    char *value = beforeInsert.value;
    CU_ASSERT_PTR_NULL(value); // It should be NULL before insertion

    // Insert with a valid key
    ioopm_hash_table_insert(ht, key1, msg1);
    ioopm_hash_table_insert(ht, key2, msg2);

    // Check the state of the hashtable after insertion
    option_t afterInsert = ioopm_hash_table_lookup(ht, key2);
    char *value2 = afterInsert.value;
    CU_ASSERT_FATAL(afterInsert.success);
    CU_ASSERT_STRING_EQUAL(value2, msg2); // It should contain the message now

    ioopm_hash_table_entry_remove(ht, key1);
    option_t after_delete = ioopm_hash_table_lookup(ht, key1);
    CU_ASSERT_PTR_NULL(after_delete.value);

    ioopm_hash_table_destroy(&ht);
  }

  void test_ht_size()
  {
    ioopm_hash_table_t *ht = ioopm_hash_table_create();
    int key = 1;
    char *msg = "test should return 1";
    int pre_insert = ht->entries;

    // Make sure size is 0 pre-insertion
    CU_ASSERT_EQUAL(pre_insert, 0);

    // Insert an element
    ioopm_hash_table_insert(ht, key, msg);

    int post_insert = ht->entries;

    CU_ASSERT_EQUAL(post_insert, 1);
    // Remove an element
    ioopm_hash_table_entry_remove(ht, key);

    CU_ASSERT_EQUAL(ht->entries, 0);

    ioopm_hash_table_destroy(&ht);
  }

  int main()
  {
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
      return CU_get_error();

    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
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
        (CU_add_test(my_test_suite, "A simple test", test1) == NULL) ||
        (CU_add_test(my_test_suite, "Basic arithmetics", test2) == NULL) ||
        (CU_add_test(my_test_suite, "Create destroy hastable", test_create_destroy) == NULL) ||
        (CU_add_test(my_test_suite, "Valid key insert", test_new_key) == NULL) ||
        (CU_add_test(my_test_suite, "Dirty key insert", test_dirty_key_use) == NULL) ||
        (CU_add_test(my_test_suite, "Invalid key insert", test_invalid_key) == NULL) ||
        (CU_add_test(my_test_suite, "Delete key ", test_delete_key) == NULL) ||
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