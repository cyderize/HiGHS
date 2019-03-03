/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file util/HighsSort.cpp
 * @brief Sorting routines for HiGHS
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#include "util/HighsSort.h"
#include <cstddef>

void maxheapsort(int *heap_v, int n) {
  build_maxheap(heap_v, n);
  max_heapsort(heap_v, n);
}

void maxheapsort(double *heap_v, int *heap_i, int n) {
  build_maxheap(heap_v, heap_i, n);
  max_heapsort(heap_v, heap_i, n);
}

void build_maxheap(int *heap_v, int n) {
  int i;
  for (i = n / 2; i >= 1; i--) {
    max_heapify(heap_v, i, n);
  }
}

void build_maxheap(double *heap_v, int *heap_i, int n) {
  int i;
  for (i = n / 2; i >= 1; i--) {
    max_heapify(heap_v, heap_i, i, n);
  }
}

void max_heapsort(int *heap_v, int n) {
  int temp_v;
  int i;
  for (i = n; i >= 2; i--) {
    temp_v = heap_v[i];
    heap_v[i] = heap_v[1];
    heap_v[1] = temp_v;
    max_heapify(heap_v, 1, i - 1);
  }
}

void max_heapsort(double *heap_v, int *heap_i, int n) {
  double temp_v;
  int i, temp_i;
  for (i = n; i >= 2; i--) {
    temp_v = heap_v[i];
    heap_v[i] = heap_v[1];
    heap_v[1] = temp_v;
    temp_i = heap_i[i];
    heap_i[i] = heap_i[1];
    heap_i[1] = temp_i;
    max_heapify(heap_v, heap_i, 1, i - 1);
  }
}

void max_heapify(int *heap_v, int i, int n) {
  int temp_v;
  int j;
  temp_v = heap_v[i];
  j = 2 * i;
  while (j <= n) {
    if (j < n && heap_v[j + 1] > heap_v[j]) j = j + 1;
    if (temp_v > heap_v[j])
      break;
    else if (temp_v <= heap_v[j]) {
      heap_v[j / 2] = heap_v[j];
      j = 2 * j;
    }
  }
  heap_v[j / 2] = temp_v;
  return;
}

void max_heapify(double *heap_v, int *heap_i, int i, int n) {
  double temp_v;
  int j, temp_i;
  temp_v = heap_v[i];
  temp_i = heap_i[i];
  j = 2 * i;
  while (j <= n) {
    if (j < n && heap_v[j + 1] > heap_v[j]) j = j + 1;
    if (temp_v > heap_v[j])
      break;
    else if (temp_v <= heap_v[j]) {
      heap_v[j / 2] = heap_v[j];
      heap_i[j / 2] = heap_i[j];
      j = 2 * j;
    }
  }
  heap_v[j / 2] = temp_v;
  heap_i[j / 2] = temp_i;
  return;
}

bool increasing_set_ok(int *set, int set_num_entries, int set_entry_lower, int set_entry_upper) {
  if (set_num_entries < 0) return false;
  if (set_entry_lower > set_entry_upper) return false;
  if (set == NULL) return false;
  int previous_entry = set_entry_lower;
  for (int k = 0; k < set_num_entries; k++) {
    int entry = set[k];
    if (entry < previous_entry) return false;
    if (entry > set_entry_upper) return false;
    previous_entry = entry;
  }
  return true;			
}

bool increasing_set_ok(double *set, int set_num_entries, double set_entry_lower, double set_entry_upper) {
  if (set_num_entries < 0) return false;
  if (set_entry_lower > set_entry_upper) return false;
  if (set == NULL) return false;
  double previous_entry = set_entry_lower;
  for (int k = 0; k < set_num_entries; k++) {
    double entry = set[k];
    if (entry < previous_entry) return false;
    if (entry > set_entry_upper) return false;
    previous_entry = entry;
  }
  return true;			
}
