#include "hash_table.h"
#include "iterator.h"
#include "linked_list.h"
#include "common.h"

#define No_buckets 17

static entry_t *entry_create(elem_t key, elem_t val, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = val;
  new_entry->next = next;
  return new_entry;
}

static void clear_bucket_entries(ioopm_hash_table_t *ht, entry_t **buckets)
{
  for (int i = 0; i < No_buckets; i++)
  {
    entry_t *current_entry = buckets[i];
    entry_t *next_entry;

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
  clear_bucket_entries(*ht, (*ht)->buckets);
  free(*ht); // Free the hash table itself
  *ht = NULL;
}

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_eq_function fun)
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to entry_t's
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  /// Initialise the entry_t pointers to NULL
  for (int i = 0; i < No_buckets; i++)
  {
    result->buckets[i] = entry_create(int_elem(0), str_elem(NULL), NULL);
  }
  result->entries = 0;
  result->function = fun;
  return result;
}

static entry_t *find_previous_entry_for_key(entry_t **bkt, elem_t key)
{

  entry_t *fst_entry = *bkt;
  entry_t *curr = fst_entry->next;
  entry_t *prev_curr = fst_entry;

  while (curr != NULL)
  {
    if (curr->key.i == key.i)
    {
      return prev_curr;
    }
    else
    {
      prev_curr = curr;
      curr = curr->next;
    }
  }
  return prev_curr;
}

bool ioopm_int_str_ht_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value )
{
  /// Calculate the bucket for this entry
  /// Search for an existing entry for a key

  if (key.i >= 0)
  {
    int bucket = key.i % 17;
    entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
    entry_t *next = entry->next;
    ioopm_eq_function function = ht->function;

    /// Check if the next entry should be updated or not
    if (next != NULL && function(value, value))
    {
      next->value = value;
    }
    else
    {
      entry->next = entry_create(key, value, next);
      ht->entries += 1;
    }
    return true;
  }

  else
  {
    return false;
  }
}

option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
  /// Find the previous entry for key
  int hash = key.i % 17;

  if (hash >= 0)
  {
    entry_t *tmp = find_previous_entry_for_key(&ht->buckets[hash], key);
    entry_t *next = tmp->next;

    if (next && next->key.i == key.i)
    {
      option_t result = {.success = true, .value = next->value};
      return result;
    }
    else
    {
      option_t result = {.success = false, .value = str_elem(NULL)};
      return result;
    }
  }
  else
  {
    option_t result = {.success = false, .value = str_elem(NULL)};
    return result;
  }
}

void ioopm_hash_table_entry_remove(ioopm_hash_table_t *ht, elem_t key)
{
  if (key.i >= 0)
  {
    int bucket = key.i % 17;
    entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
    entry_t *next = entry->next;

    /// Check if the next entry should be updated or not
    if (next != NULL && next->key.i == key.i)
    {
      entry->next = next->next;
      free(next);
      ht->entries -= 1;
    }
    else
    {
      printf("entry already removed");
    }
  }
  else
  {
    printf("invalid key");
    return;
  }
};

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ht->entries == 0;
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
      ioopm_hash_table_entry_remove(ht, ptr->key);
      ptr = ptr_next;
    }

    ht->buckets[i]->next = NULL;
  }
  ht->entries = 0;
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht) // TODO: array -> linked_list
{
  ioopm_eq_function fun = ht->function;
  ioopm_list_t *keys = ioopm_linked_list_create(fun);
  int count = 0;

  for (int i = 0; i < 17; i++)
  {
    entry_t *ptr = ht->buckets[i]->next;

    while (NULL != ptr)
    {
      ioopm_linked_list_append(keys, ptr->key);
      count++;
      ptr = ptr->next;
    }
  }
  return keys;
}

elem_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  elem_t *vals = calloc(1, sizeof(ioopm_hash_table_t));
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

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  option_t hasKey = ioopm_hash_table_lookup(ht, key);
  return hasKey.success;
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
  elem_t *vals = ioopm_hash_table_values(ht);
  int count = 0;
  elem_t curr = vals[count];
  bool isTrue = false;
  while (curr.s != NULL)
  {
    if (curr.s == value.s)
    {
      isTrue = true;
      break;
    }
    else
    {
      count++;
      curr = vals[count];
    }
  }

  free(vals);

  return isTrue;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function f, void *x)
{
  for (int i = 0; i < 17; i++)
  {
    entry_t *ptr = ht->buckets[i]->next;

    while (NULL != ptr)
    {
      f(ptr->key, &ptr->value, x);
      ptr = ptr->next;
    }
    
  }
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate P, void *x)
{
  ioopm_list_t *keys = ioopm_hash_table_keys(ht); // TODO: array -> linked_list
  ioopm_list_iterator_t *iter = ioopm_list_iterator(keys);
  elem_t *values = ioopm_hash_table_values(ht);
  bool result = false;
  elem_t curr_key = ioopm_iterator_current(iter);

  for (size_t i = 0; i < keys->size && !result; ++i) 
  {
    result = result || P(curr_key, values[i], x);
    if (ioopm_iterator_has_next(iter)){
        curr_key = ioopm_iterator_next(iter);
    }
  }
  ioopm_iterator_destroy(&iter);
  ioopm_linked_list_destroy(&keys);
  free(values);
  return result;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate P, void *x)
{
  ioopm_list_t *keys = ioopm_hash_table_keys(ht); // TODO: array -> linked_list
  ioopm_list_iterator_t *iter = ioopm_list_iterator(keys);
  elem_t *values = ioopm_hash_table_values(ht);
  bool result = true;
  for (size_t i = 0; i < keys->size && result; ++i) 
  {
    elem_t key = ioopm_iterator_current(iter);
    result = result && P(key, values[i], x);
    if (ioopm_iterator_has_next(iter)){
        ioopm_iterator_next(iter);
    }
  }
  ioopm_iterator_destroy(&iter);
  ioopm_linked_list_destroy(&keys);
  free(values);
  return result;
}

void value_hej (elem_t key, elem_t *value, void *x){
  value->s = "hej";
}

bool search_value(elem_t key, elem_t value, void *x) {
  return strcmp(value.p, x) == 0;
}