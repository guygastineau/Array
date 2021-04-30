// Change the configurable macros, so we can test they
// provide the configurability they should.

#include "../src/array.h"

#include "vendor/unity.h"

#include <stdbool.h>

void setUp(void)
{
}

void tearDown(void)
{
}

static void TEST_ASSERT_EQUAL_ARRAY(Slice expected, Array *actual)
{
  TEST_ASSERT_NOT_NULL_MESSAGE(actual, "NULL pointer in array comparison");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(expected.count, actual->count,
                                   "array count doesn't match");
  for (size_t i = 0; i < expected.count; ++i) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(expected.data[i], actual->data[i],
                                  "array mismatched elements");
  }
}

static void TEST_ASSERT_SLICE_EQUAL(Slice expected, Slice actual)
{
  TEST_ASSERT_EQUAL_size_t_MESSAGE(expected.count, actual.count,
                                    "Mismatched slice counts.");
  for (size_t i = 0; i < expected.count; ++i) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(expected.data[i], actual.data[i],
                                  "slice mismatched elements");
  }
}

// Helper to ensure that arrays initializer functions work properly.
static void assert_clean_allocation(Array *arr, size_t capacity, size_t count)
{
  TEST_ASSERT_NOT_NULL_MESSAGE(arr, "mkArray failed to allocate");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(capacity, arr->cap,
                                   "mkArray failed to use ARRAY_MIN_CAP");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(count, arr->count,
                                   "mkArray new array size not 0");
  TEST_ASSERT_NOT_NULL_MESSAGE(arr->data,
                               "mkArray failed to allocate internal buffer");
}

static void test_allocate_empty_array(void)
{
  Array *arr = mkArray();
  assert_clean_allocation(arr, ARRAY_MIN_CAP, 0);
  // The only way this is tested is by running `make memcheck'.
  arrayDestroy(arr);
}

static void test_allocate_array_with_capacity_too_small(void)
{
  TEST_IGNORE();
  Array *arr = mkArrayWithCap(6);
  assert_clean_allocation(arr, ARRAY_MIN_CAP, 0);
  arrayDestroy(arr);
}

static void test_allocate_array_with_capacity_larger(void)
{
  TEST_IGNORE();
  Array *arr = mkArrayWithCap(24);
  assert_clean_allocation(arr, 24, 0);
  arrayDestroy(arr);
}

static void test_initialize_from_buffer_empty(void)
{
  TEST_IGNORE();
  Array *arr = arrayFromCArray(0, NULL);
  assert_clean_allocation(arr, ARRAY_MIN_CAP, 0);
  arrayDestroy(arr);
}

static void test_initialize_from_buffer_with_data(void)
{
  TEST_IGNORE();
  data_t data[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  Array *arr = arrayFromCArray(10, data);
  assert_clean_allocation(arr, ARRAY_MIN_CAP, 10);
  TEST_ASSERT_EQUAL_ARRAY((Slice){ 10, data }, arr);
}

static void test_initialize_from_buffer_with_more_data(void)
{
  TEST_IGNORE();
  data_t data[20] = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19
  };
  Array *arr = arrayFromCArray(20, data);
  assert_clean_allocation(arr, 20, 20);
  TEST_ASSERT_EQUAL_ARRAY((Slice){ 20, data }, arr);
}

static void test_get_slice_null_pointer(void)
{
  TEST_IGNORE();
  Slice nullSlice = { 0, NULL };
  TEST_ASSERT_SLICE_EQUAL(nullSlice, arrayGetSlice(NULL, 0, 0));
  // Just see if invalid indexes will pull up a bug here.
  TEST_ASSERT_SLICE_EQUAL(nullSlice, arrayGetSlice(NULL, 1, 4));
}

static void test_get_slice_invalid_start(void)
{
  TEST_IGNORE();
  Slice nullSlice = { 0, NULL };
  data_t data[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  Array *arr = arrayFromCArray(8, data);
  // Start must be less than end.
  TEST_ASSERT_SLICE_EQUAL(nullSlice, arrayGetSlice(arr, 1, 1));
  // Start must be less than Array.count.
  TEST_ASSERT_SLICE_EQUAL(nullSlice, arrayGetSlice(arr, 8, 9));
  arrayDestroy(arr);
}

static void test_get_slice_singleton(void)
{
  TEST_IGNORE();
  data_t data[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  Array *arr = arrayFromCArray(8, data);
  TEST_ASSERT_SLICE_EQUAL((Slice){ 1, data }, arrayGetSlice(arr, 0, 1));
  TEST_ASSERT_SLICE_EQUAL((Slice){ 1, data + 3 }, arrayGetSlice(arr, 3, 4));
  TEST_ASSERT_SLICE_EQUAL((Slice){ 1, data + 7 }, arrayGetSlice(arr, 7, 8));
  arrayDestroy(arr);
}

static void test_get_slice_whole_array(void)
{
  TEST_IGNORE();
  data_t data[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  Array *arr = arrayFromCArray(8, data);
  TEST_ASSERT_SLICE_EQUAL((Slice){ 8, data }, arrayGetSlice(arr, 0, 8));
  arrayDestroy(arr);
}

static void test_get_slice_truncate_invalid_end(void)
{
  TEST_IGNORE();
  data_t data[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  Array *arr = arrayFromCArray(8, data);
  TEST_ASSERT_SLICE_EQUAL((Slice){ 7, data + 1 }, arrayGetSlice(arr, 1, 10));
  arrayDestroy(arr);
}

int main(void)
{
   UnityBegin("test/test_array.c");

   RUN_TEST(test_allocate_empty_array);
   RUN_TEST(test_allocate_array_with_capacity_too_small);
   RUN_TEST(test_allocate_array_with_capacity_larger);
   RUN_TEST(test_initialize_from_buffer_empty);
   RUN_TEST(test_initialize_from_buffer_with_data);
   RUN_TEST(test_initialize_from_buffer_with_more_data);
   RUN_TEST(test_get_slice_null_pointer);
   RUN_TEST(test_get_slice_invalid_start);
   RUN_TEST(test_get_slice_singleton);
   RUN_TEST(test_get_slice_whole_array);
   RUN_TEST(test_get_slice_truncate_invalid_end);

   return UnityEnd();
}
