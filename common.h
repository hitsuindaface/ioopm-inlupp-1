#pragma once


typedef union elem elem_t;
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);

union elem
{
  /// TODO: update the names of the fields to something better? 
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  /// other choices certainly possible
};
