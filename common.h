#pragma once
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>


typedef union elem elem_t;
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);

#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }
#define str_elem(x) (elem_t) { .s=(x) }

bool string_compare(elem_t a, elem_t b);

bool int_compare(elem_t a, elem_t b);


union elem
{
  /// TODO: update the names of the fields to something better? 
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  char *s;
  /// other choices certainly possible
};
