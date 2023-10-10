#include <CUnit/Basic.h>
#include "utils.h"
#include "hash_table.h"
#include "iterator.h"
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

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
  char *msg1 = "first msg";
  char *msg2 = "second msg";

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
  size_t pre_insert = ht->entries; 

  // Make sure size is 0 pre-insertion
  size_t comp = 0; 
  CU_ASSERT_EQUAL(pre_insert, comp);

  // Insert an element
  ioopm_hash_table_insert(ht, key, msg);

  size_t post_insert = ht->entries; 

  comp = 1;
  CU_ASSERT_EQUAL(post_insert, comp);
  // Remove an element
  ioopm_hash_table_entry_remove(ht, key);
  comp = 0;
  CU_ASSERT_EQUAL(ht->entries, comp);

  ioopm_hash_table_destroy(&ht);
}
void test_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  // Create an array keys of N integers and fill it with some keys
  size_t array_size = 5; 

  int keys[5] = {3, 5, 6, 7, 80}; 

  // Create another array found of N booleans, all initialized to false
  bool founds[5];

  for (size_t i = 0; i < array_size; i++) 
  {
    founds[i] = false;
  };

  // Insert all the keys from keys into a fresh hash table
  for (size_t i = 0; i < array_size; i++) 
  {
    ioopm_hash_table_insert(ht, keys[i], "value");
  };

  ioopm_list_t *ht_keys = ioopm_hash_table_keys(ht); // TODO: array -> linked_list
  ioopm_list_iterator_t *iter = ioopm_list_iterator(ht_keys);
  bool is_found = false;
  int ht_element;
  
  while(true) 
  {
    ht_element = ioopm_iterator_current(iter);
    for (size_t j = 0; j < array_size; j++) 
    {

      if (ht_element == keys[j]) // TODO: array -> linked_list
      {
        founds[j] = true;
        is_found = true;
      }
    }
    if (is_found == false)
    {
      CU_FAIL("Found a key that was never inserted!");
    }
    
    if (ioopm_iterator_has_next(iter))
    {
    ioopm_iterator_next(iter);  //increment element
    }
    else //curr is last element in iterator
    { 
      break; 
    }
  }

  for (size_t i = 0; i < array_size; ++i)
  {
    CU_ASSERT_TRUE(founds[i]);
  }
  ioopm_hash_table_destroy(&ht);
  ioopm_linked_list_destroy(&ht_keys);
  ioopm_iterator_destroy(&iter);
}

void test_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  // Create an array keys of N integers and fill it with some keys
  size_t array_size = 5; 
  int keys[5] = {1, 2, 3, 4, 5};

  // Create another array with values
  char *values[5] = {"one", "two", "three", "four", "five"};

  // Insert all the keys and values into a fresh hash table
  for (size_t i = 0; i < array_size; i++) 
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]); 
  };

  ioopm_list_t *ht_keys = ioopm_hash_table_keys(ht); // TODO: array -> linked_list
  char **ht_values = ioopm_hash_table_values(ht);

  // checking that all values were found in ioopm_hash_table_values
  for (size_t i = 0; i < array_size; i++) 
  {
    bool is_found = false;
    char *ht_value = ht_values[i];

    for (size_t j = 0; j < array_size; j++) 
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
  
  ioopm_list_iterator_t *iter = ioopm_list_iterator(ht_keys);
  
  // checking that the corresponding key and value in ht have the same index in the arrays.
  for (size_t i = 0; i < array_size - 1; i++)
  {
    int ht_key = ioopm_iterator_current(iter); // TODO: array -> linked_list
    option_t expected_value = ioopm_hash_table_lookup(ht, ht_key);

    ioopm_iterator_next(iter);
    CU_ASSERT_EQUAL(expected_value.value, ht_values[i]);
  }
  ioopm_hash_table_destroy(&ht);
  ioopm_linked_list_destroy(&ht_keys);
  ioopm_iterator_destroy(&iter);
  free(ht_values);
}

void test_has_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  // testing valid inserted keys
  int valid_key1 = 1;
  int valid_key2 = 2;
  int valid_key3 = 15;

  // Insert keys with any value
  ioopm_hash_table_insert(ht, valid_key1, "val1");
  ioopm_hash_table_insert(ht, valid_key2, "val2");
  ioopm_hash_table_insert(ht, valid_key3, "val3");

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, valid_key1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, valid_key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, valid_key3));

  // testing valid NOT inserted keys
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, 40));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, 13));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, 24));

  // Testing invalid keys
  CU_ASSERT_EQUAL(ioopm_hash_table_has_key(ht, -1), NULL);
  CU_ASSERT_EQUAL(ioopm_hash_table_has_key(ht, -2), NULL);
  CU_ASSERT_EQUAL(ioopm_hash_table_has_key(ht, -15), NULL);

  ioopm_hash_table_destroy(&ht);
};

void test_has_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  // testing valid inserted keys
  char *val1 = "val1";
  char *val2 = "val2";
  char *val3 = "val3";

  // Insert keys with any value
  ioopm_hash_table_insert(ht, 15, val1);
  ioopm_hash_table_insert(ht, 1, val2);
  ioopm_hash_table_insert(ht, 32, val3);

  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, val1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, val2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, val3));

  ioopm_hash_table_destroy(&ht);
}

void test_apply_to_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  char *val1 = "cola";
  char *val2 = "sprite";
  char *val3 = "hallonsoda";

  ioopm_hash_table_insert(ht, 0, val1);
  ioopm_hash_table_insert(ht, 1, val2);
  ioopm_hash_table_insert(ht, 2, val3);

  ioopm_hash_table_apply_to_all(ht, value_hej, NULL);

  option_t first_lookup = ioopm_hash_table_lookup(ht, 0);
  char *first_value = first_lookup.value;
  CU_ASSERT_STRING_EQUAL(first_value, "hej");

  option_t second_lookup = ioopm_hash_table_lookup(ht, 1);
  char *second_value = second_lookup.value;
  CU_ASSERT_STRING_EQUAL(second_value, "hej");

  option_t third_lookup = ioopm_hash_table_lookup(ht, 2);
  char *third_value = third_lookup.value;
  CU_ASSERT_STRING_EQUAL(third_value, "hej");

  ioopm_hash_table_destroy(&ht);
}

void test_any()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  //just one 
  int key1 = 1;
  int key2 = 11;
  int key3 = 132;
  int key4 = 14;

  char *value1 = "kallt";
  char *value2 = "kallt";
  char *value3 = "varmt";
  char *value4 = "bingo!";

  ioopm_hash_table_insert(ht, key1, value1);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);
  ioopm_hash_table_insert(ht, key4, value4);


  bool has_value1 = ioopm_hash_table_any(ht, search_value, "bingo!");
  CU_ASSERT_TRUE(has_value1);

  value1 = "bingo!";
  value2 = "bingo!";
  value3 = "bingo!";
  value4 = "bingo!";

  ioopm_hash_table_insert(ht, key1, value1);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);
  ioopm_hash_table_insert(ht, key4, value4);
  
  bool has_value2 = ioopm_hash_table_any(ht, search_value, "bingo!");
  CU_ASSERT_TRUE(has_value2);

  bool has_value3 = ioopm_hash_table_any(ht, search_value, "kallt");
  CU_ASSERT_FALSE(has_value3);


  ioopm_hash_table_destroy(&ht);
}

void test_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  //just one 
  int key1 = 1;
  int key2 = 11;
  int key3 = 132;
  int key4 = 14;

  char *value1 = "kallt";
  char *value2 = "kallt";
  char *value3 = "varmt";
  char *value4 = "bingo!";

  ioopm_hash_table_insert(ht, key1, value1);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);
  ioopm_hash_table_insert(ht, key4, value4);


  bool has_value1 = ioopm_hash_table_all(ht, search_value, "bingo!");
  CU_ASSERT_FALSE(has_value1);

  value1 = "bingo!";
  value2 = "bingo!";
  value3 = "bingo!";
  value4 = "bingo!";

  ioopm_hash_table_insert(ht, key1, value1);
  ioopm_hash_table_insert(ht, key2, value2);
  ioopm_hash_table_insert(ht, key3, value3);
  ioopm_hash_table_insert(ht, key4, value4);
  
  bool has_value2 = ioopm_hash_table_all(ht, search_value, "bingo!");
  CU_ASSERT_TRUE(has_value2);

  bool has_value3 = ioopm_hash_table_all(ht, search_value, "kallt");
  CU_ASSERT_FALSE(has_value3);

  ioopm_hash_table_destroy(&ht);
} 


int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Hash table test suite", init_suite, clean_suite);
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
      (CU_add_test(my_test_suite, "Create destroy hashtable", test_create_destroy) == NULL) ||
      (CU_add_test(my_test_suite, "Valid key insert", test_new_key) == NULL) ||
      (CU_add_test(my_test_suite, "Dirty key insert", test_dirty_key_use) == NULL) ||
      (CU_add_test(my_test_suite, "Invalid key insert", test_invalid_key) == NULL) ||
      (CU_add_test(my_test_suite, "Delete key ", test_delete_key) == NULL) ||
      (CU_add_test(my_test_suite, "Entries count ", test_ht_size) == NULL) ||
      (CU_add_test(my_test_suite, "Test key array ", test_keys) == NULL) ||
      (CU_add_test(my_test_suite, "Test value array ", test_values) == NULL) ||
      (CU_add_test(my_test_suite, "Test hashtable has key ", test_has_keys) == NULL) ||
      (CU_add_test(my_test_suite, "Test hashtable has value ", test_has_values) == NULL) ||
      (CU_add_test(my_test_suite, "Test apply function to entries ", test_apply_to_all) == NULL) ||
      (CU_add_test(my_test_suite, "Test apply predicate to any entry ", test_any) == NULL) ||
      (CU_add_test(my_test_suite, "Test apply predicate to all entries ", test_all) == NULL) ||
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