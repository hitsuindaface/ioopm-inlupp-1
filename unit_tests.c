#include <CUnit/Basic.h>
#include "utils.h"
#include "hash_table.h"
<<<<<<< HEAD
#include <stdlib.h>

int init_suite(void)
{
=======

int init_suite(void) {
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

<<<<<<< HEAD
int clean_suite(void)
{
=======
int clean_suite(void) {
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.
<<<<<<< HEAD
void test1(void)
{
  CU_ASSERT(42);
}

void test2(void)
{
=======
void test1(void) {
  CU_ASSERT(42);
}

void test2(void) {
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
  CU_ASSERT_EQUAL(1 + 1, 2);
}

void test_create_destroy()
{
<<<<<<< HEAD
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

  ioopm_hashtable_entry_remove(ht, key1);
  option_t after_delete1 = ioopm_hash_table_lookup(ht, key1);
  CU_ASSERT_PTR_NULL(after_delete1.value);

  option_t after_delete2 = ioopm_hash_table_lookup(ht, key2);
  CU_ASSERT_EQUAL(after_delete2.value, msg2);

  ioopm_hash_table_destroy(&ht);
}

void test_entries_count()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int count_before_insert = ht->size;
  CU_ASSERT_EQUAL(count_before_insert, 0);
  bool is_true = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(is_true);
  int key1 = 1;
  char *msg = "message1";

  // Check the state of the hashtable before insertionö
  option_t beforeInsert = ioopm_hash_table_lookup(ht, key1);
  CU_ASSERT_PTR_NULL(beforeInsert.value); // It should be NULL before insertion

  // Insert key and check entries count
  ioopm_hash_table_insert(ht, key1, msg);
  int count_after_insert = ht->size;
  CU_ASSERT_EQUAL(1, count_after_insert);

  // Delete entry and check entries count
  ioopm_hashtable_entry_remove(ht, key1);
  int count_after_remove = ht->size;
  CU_ASSERT_EQUAL(0, count_after_remove);

  // testing clearing the hashtable
  ioopm_hash_table_insert(ht, 0, "message1");
  ioopm_hash_table_insert(ht, 1, "message2");
  ioopm_hash_table_insert(ht, 2, "message3");
  bool not_empty = !ioopm_hash_table_is_empty(ht); // checks that the hashtable not is empty
  CU_ASSERT_TRUE(not_empty);

  ioopm_hash_table_clear(ht);
  bool is_empty = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(is_empty);

  // Check the state of the hashtable after insertion

  ioopm_hash_table_destroy(&ht);
}

void test_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  // Create an array keys of N integers and fill it with some keys
  int array_size = 5;
  int keys[5] = {3, 5, 6, 7, 80};

  // Create another array found of N booleans, all initialized to false
  bool founds[5];
  for (int i = 0; i < array_size; i++)
  {
    founds[i] = false;
  };

  // Insert all the keys from keys into a fresh hash table
  for (int i = 0; i < array_size; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], "value");
  };

  int *ht_keys = ioopm_hash_table_keys(ht);
  int ht_size = ht->size;
  bool is_found = false;

  for (int i = 0; i < ht_size; i++)
  {

    int ht_element = ht_keys[i];

    for (int j = 0; j < array_size; j++)
    {
      if (ht_element == keys[j])
      {
        founds[j] = true;
        is_found = true;
      }
    }

    if (is_found == false)
    {
      CU_FAIL("Found a key that was never inserted!");
    }
  }

  for (int i = 0; i < array_size; ++i)
  {
    CU_ASSERT_TRUE(founds[i]);
  }
  ioopm_hash_table_destroy(&ht);
  free(ht_keys);
}

void test_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  // Create an array keys of N integers and fill it with some keys
  int array_size = 5;
  int keys[5] = {1, 2, 3, 4, 5};

  // Create another array with values
  char *values[5] = {"one", "two", "three", "four", "five"};

  // Insert all the keys and values into a fresh hash table
  for (int i = 0; i < array_size; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  };

  int *ht_keys = ioopm_hash_table_keys(ht);
  char **ht_values = ioopm_hash_table_values(ht);

  // checking that all values were found in ioopm_hash_table_values
  for (int i = 0; i < array_size; i++)
  {
    bool is_found = false;
    char *ht_value = ht_values[i];

    for (int j = 0; j < array_size; j++)
    {
      if (ht_value == values[j])
      {
        is_found = true;
      }
    }

    if (is_found == false)
    {
      CU_FAIL("Found a value that was never inserted!");
    }
  }

  // checking that the corresponding key and value in ht have the same index in the arrays.
  for (int i = 0; i < array_size - 1; i++)
  {
    int ht_key = ht_keys[i];
    option_t expected_value = ioopm_hash_table_lookup(ht, ht_key);

    CU_ASSERT_EQUAL(expected_value.value, ht_values[i]);
  }
  ioopm_hash_table_destroy(&ht);
  free(ht_keys);
  free(ht_values);
}

int main()
{
=======
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(&ht);
   CU_ASSERT_PTR_NULL(ht);
}


void test_new_key() {
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


void test_dirty_key_use() {
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

void test_invalid_key() {
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

void test_delete_key() {
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

void test_ht_size() {
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

int main() {
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
<<<<<<< HEAD
  CU_pSuite my_test_suite = CU_add_suite("Hash table test suite", init_suite, clean_suite);
  if (my_test_suite == NULL)
  {
    // If the test suite could not be added, tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
=======
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
<<<<<<< HEAD
      (CU_add_test(my_test_suite, "A simple test", test1) == NULL) ||
      (CU_add_test(my_test_suite, "Basic arithmetics", test2) == NULL) ||
      (CU_add_test(my_test_suite, "Create destroy hastable", test_create_destroy) == NULL) ||
      (CU_add_test(my_test_suite, "Valid key insert", test_new_key) == NULL) ||
      (CU_add_test(my_test_suite, "Dirty key insert", test_dirty_key_use) == NULL) ||
      (CU_add_test(my_test_suite, "Invalid key insert", test_invalid_key) == NULL) ||
      (CU_add_test(my_test_suite, "Delete key ", test_delete_key) == NULL) ||
      (CU_add_test(my_test_suite, "Entries count ", test_entries_count) == NULL) ||
      (CU_add_test(my_test_suite, "Test key array ", test_keys) == NULL) ||
      (CU_add_test(my_test_suite, "Test value array ", test_values) == NULL) ||
      0)
  {
    // If adding any of the tests fails, we tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }
=======
    (CU_add_test(my_test_suite, "A simple test", test1) == NULL) ||
    (CU_add_test(my_test_suite, "Basic arithmetics", test2) == NULL) || 
    (CU_add_test(my_test_suite, "Create destroy hastable", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "Valid key insert", test_new_key) == NULL) ||
    (CU_add_test(my_test_suite, "Dirty key insert", test_dirty_key_use) == NULL) ||
    (CU_add_test(my_test_suite, "Invalid key insert", test_invalid_key) == NULL) ||
    (CU_add_test(my_test_suite, "Delete key ", test_delete_key) == NULL) ||
    0
    )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
<<<<<<< HEAD
}
=======
} 
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
