#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

<<<<<<< HEAD
#define No_buckets

static entry_t *entry_create(int key, char *val, entry_t *next)
{
=======

#define No_buckets 17

static entry_t *entry_create(int key, char *val, entry_t *next){
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = val;
  new_entry->next = next;
  return new_entry;
}

<<<<<<< HEAD
static void clear_bucket_entries(ioopm_hash_table_t *ht, entry_t **buckets)
{
  for (int i = 0; i < 17; i++)
=======
static void clear_bucket_entries(ioopm_hash_table_t *ht , entry_t **buckets)
{ 
  for (int i=0; i<No_buckets; i++)
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
  {
    entry_t *current_entry = buckets[i];
    entry_t *next_entry;

<<<<<<< HEAD
    while (current_entry != NULL) // Loop while there are entries in the bucket
    {
      next_entry = current_entry->next;
      free(current_entry); // Free the entry itself
      current_entry = next_entry;
    }
  }
}

void ioopm_hash_table_destroy(ioopm_hash_table_t **ht)
{
=======
    while (current_entry != NULL) //Loop while there are entries in the bucket
      {
        next_entry = current_entry->next;
        free(current_entry);         // Free the entry itself
        current_entry = next_entry;
      }
  }
}

void ioopm_hash_table_destroy(ioopm_hash_table_t **ht) {
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
  clear_bucket_entries(*ht, (*ht)->buckets);
  free(*ht); // Free the hash table itself
  *ht = NULL;
}

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to entry_t's
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  /// Initialise the entry_t pointers to NULL
<<<<<<< HEAD
  for (int i = 0; i < 17; i++)
  {
    result->buckets[i] = entry_create(0, NULL, NULL);
  }
  result->size = 0;
  return result;
}

static entry_t *find_previous_entry_for_key(entry_t **bkt, int key)
{
=======
  for(int i=0; i<No_buckets; i++){
    result->buckets[i] = entry_create(0, NULL, NULL);
  }
  result->entries=0;
  return result;
}

static entry_t *find_previous_entry_for_key(entry_t **bkt, int key){
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd

  entry_t *fst_entry = *bkt;
  entry_t *curr = fst_entry->next;
  entry_t *prev_curr = fst_entry;

  while (curr != NULL)
  {
    if (curr->key == key)
    {
      return prev_curr;
    }
<<<<<<< HEAD
    else
=======
    else 
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
    {
      prev_curr = curr;
      curr = curr->next;
    }
  }
  return prev_curr;
<<<<<<< HEAD
  /*
    entry_t *fs_entry = bkt;
    entry_t *prev_entry = fs_entry; //keeping track of previous entry
    entry_t *current_entry = prev_entry; //"cursor" moving through the hashtable



    while (current_entry && prev_entry->next) //kollar så de inte är NULL
    {
      if (current_entry->key == key ){
        return prev_entry;
      }
      prev_entry = current_entry;
      current_entry = current_entry->next;
    }
    return prev_entry; //the entry whose next pointer should be pointing to the entry once we have inserted it
  */
}

bool ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  /// Search for an existing entry for a key

  if (key >= 0)
  {
=======
/*
  entry_t *fs_entry = bkt;
  entry_t *prev_entry = fs_entry; //keeping track of previous entry
  entry_t *current_entry = prev_entry; //"cursor" moving through the hashtable



  while (current_entry && prev_entry->next) //kollar så de inte är NULL
  {
    if (current_entry->key == key ){
      return prev_entry;
    }
    prev_entry = current_entry;
    current_entry = current_entry->next;
  }
  return prev_entry; //the entry whose next pointer should be pointing to the entry once we have inserted it
*/
}



bool ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
  {
  /// Calculate the bucket for this entry
  /// Search for an existing entry for a key

  if (key>=0){
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
    int bucket = key % 17;
    entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
    entry_t *next = entry->next;

    /// Check if the next entry should be updated or not
    if (next != NULL && next->key == key)
<<<<<<< HEAD
    {
      next->value = value;
    }
    else
    {
      entry->next = entry_create(key, value, next);
      ht->size += 1;
    }
    return true;
  }

  else
  {
=======
      {
        next->value = value;
      }
    else
      {
        entry->next = entry_create(key, value, next);
        ht->entries+=1;
      }
      return true;
  }

  else {
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
    return false;
  }
}

<<<<<<< HEAD
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  /// Find the previous entry for key
  int hash = key % 17;

  if (hash >= 0)
  {
    entry_t *tmp = find_previous_entry_for_key(&ht->buckets[hash], key);
    entry_t *next = tmp->next;

    if (next && next->key == key)
    {
      option_t result = {.success = true, .value = next->value};
      return result;
    }
    else
    {
      option_t result = {.success = false, .value = NULL};
      return result;
    }
  }
  else
  {
    option_t result = {.success = false, .value = NULL};
    return result;
  }
}

void ioopm_hashtable_entry_remove(ioopm_hash_table_t *ht, int key)
{
  if (key >= 0)
  {
=======
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key) {
  /// Find the previous entry for key
  int hash = key%17;
  
if (hash>=0){
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[hash], key);
  entry_t *next = tmp->next;

  if (next && next->key==key)
  {
    option_t result = { .success = true, .value = next->value };
    return result;
  }
  else
  {
    option_t result = { .success = false, .value = NULL };
    return result;
  }
}
else
  {
     option_t result = { .success = false, .value = NULL };
     return result;
  }
}

void ioopm_hash_table_entry_remove(ioopm_hash_table_t *ht, int key) {
  if (key>=0){
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
    int bucket = key % 17;
    entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
    entry_t *next = entry->next;

    /// Check if the next entry should be updated or not
    if (next != NULL && next->key == key)
<<<<<<< HEAD
    {
      entry->next = next->next;
      free(next);
      ht->size -= 1;
    }
    else
    {
      printf("entry already removed");
    }
  }
  else
  {
=======
      {
        entry->next = next->next;
        free(next);
        ht->entries-=1;
      }
    else
      {
        printf("entry already removed");
      }
  }
  else {
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
    printf("invalid key");
    return;
  }
};

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
<<<<<<< HEAD
  return ht->size == 0;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  if (ioopm_hash_table_is_empty(ht))
    return;

  for (int i = 0; i < 17; i++)
  {
    entry_t *ptr = ht->buckets[i]->next;
    entry_t *ptr_next;

    while (NULL != ptr)
    {
      ptr_next = ptr->next;
      ioopm_hashtable_entry_remove(ht, ptr->key);
      ptr = ptr_next;
    }

    ht->buckets[i]->next = NULL;
  }
  ht->size = 0;
}

int *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  int *keys = calloc(1, sizeof(ioopm_hash_table_t));
  int count = 0;

  for (int i = 0; i < 17; i++)
  {
    entry_t *ptr = ht->buckets[i]->next;

    while (NULL != ptr)
    {
      keys[count] = ptr->key;
      count++;
      ptr = ptr->next;
    }
  }
  return keys;
}

char **ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  char **vals = calloc(1, sizeof(ioopm_hash_table_t));
  int count = 0;

  for (int i = 0; i < 17; i++)
  {
    entry_t *ptr = ht->buckets[i]->next;

    while (NULL != ptr)
    {
      vals[count] = ptr->value;
      count++;
      ptr = ptr->next;
    }
  }
  return vals;
}
=======
  return ht->entries == 0;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht) {
    if (ioopm_hash_table_is_empty(ht))
        return;

    for (int i = 0; i < No_buckets; i++) {
        entry_t *ptr = ht->buckets[i]->next;
        entry_t *ptr_next;

        while (NULL != ptr) {
            ptr_next = ptr->next;
            ioopm_hash_table_entry_remove(ht, ptr->key);
            ptr = ptr_next;
        }

        ht->buckets[i]->next = NULL;
    }
    ht->entries = 0;
}
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
