# IOOPM Inlupp 1: Alexander Liberman && Susanna Mårdbrant


## Table of Contents
- [IOOPM Inlupp 1](#ioopm-inlupp-1:-alexander-liberman-&&-susanna-mårdbrant)
  - [Table of Contents](#table-of-contents)
  - [Error Handling](#error-handling)
  - [Assumptions](#assumptions)
  - [Usage](#usage)
  - [Performance](#performance)

## Error handling
    `assert();` -> Makes sure the element being sent in (e.g. a list) exists and throws and error if it doesn't.
    `option_t;` -> In ioopm_hash_table_lookup(); we handle the case of finding a NULL value by returning an option_t which is a tuple consisting of a success boolean and the value found. If 'success' is true, the NULL value was inserted purposely, else the value at the key does not exist. 
    `if (x > 0);` -> Checks so that an entered key is larger than 0, returning an error message if this is inserted. This restricts the user to only positive keys, so as to stop the user from accessing a negative index. 
## Assumptions
Our main assumption is that the datastructures are created using the given functions, since we can not guarantee that a hashtable or linked list created by a user with work correctly.
## Usage 
To run the performance testing with the appropriate dependencies run the following commands: 
```bash
$ make freqtest
$ make memfreqtest
```
To run unit tests for the hashtable program and linked list program you can use hashtest and linktest repsectively as arguments after the `make` command. 
## Performance
Using `gcov` our hash table tests cover the following:
 - hash_table.c:
    - lines executed: 89.89% if 188
 - common.c: 
    - lines executed: 50% of 4
 - linked_list.c:
    - lines executed: 30.69% of 189
 - unit_tests.c:
    - lines executed: 97.55% of 286
Our linked list tests cover the following:
 - linked_list.c:
    - lines executed: 80.95% of 189
 - common.c:
    - lines executed: 50% of 4
 - hash_table.c:
    - lines executed: 0% of 188
 - linked_test.c:
    - lines executed: 98.08% of 260