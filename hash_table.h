#pragma once
#include <stdbool.h>

<<<<<<< HEAD
=======


>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
/**
 * @file hash_table.h
 * @author Susanna och Alex
 * @date 1 Sep 2022
 * @brief Simple hash table that maps integer keys to string values.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 * @see $CANVAS_OBJECT_REFERENCE$/assignments/gb54499f3b7b264e3af3b68c756090f52
 */

typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;
<<<<<<< HEAD

typedef bool (*ioopm_predicate)(int key, char *value, void *extra);
typedef void (*ioopm_apply_function)(int key, char **value, void *extra);
=======
typedef bool(*ioopm_predicate)(int key, char *value, void *extra);
typedef void(*ioopm_apply_function)(int key, char **value, void *extra);
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(void);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t **ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
<<<<<<< HEAD
/// @preturn boolean indicationg success
=======
/// @return boolean indicationg success
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
bool ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
<<<<<<< HEAD
/// @return the value mapped to by key (FIXME: incomplete)
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: incomplete)
void ioopm_hashtable_entry_remove(ioopm_hash_table_t *ht, int key);
=======
/// @return a tuple with a boolean (if a value is found) and the value mapped to by key
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);

>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd

/// @brief remove entry in hash table
/// @param ht hash table operated upon
/// @param key key to remove
<<<<<<< HEAD
void ioopm_entry_remove(ioopm_hash_table_t *ht, int key);

typedef struct entry entry_t;

struct entry
{
    int key;       // holds the key
    char *value;   // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    entry_t *buckets[17];
    int size;
};

struct option
{
    bool success;
    char *value;
};
=======
void ioopm_hash_table_entry_remove(ioopm_hash_table_t *ht, int key);
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd

/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key => value entries in the hash table
int ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief checks if the hash table is empty
/// @param h hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief clear all the entries in a hash table
/// @param h hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param h hash table operated upon
/// @return an array of keys for hash table h
int *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param h hash table operated upon
/// @return an array of values for hash table h
char **ioopm_hash_table_values(ioopm_hash_table_t *ht);

/// @brief check if a hash table has an entry with a given key
/// @param h hash table operated upon
/// @param key the key sought
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key);

/// @brief check if a hash table has an entry with a given value
/// @param h hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);
<<<<<<< HEAD
=======

typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[17];
  int entries;
};

struct option
{
  bool success;
  char *value;
};
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
