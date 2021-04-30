// Change the configurable macros, so we can test they
// provide the configurability they should.

#include "../src/array.h"

#include "vendor/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
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

int main(void)
{
   UnityBegin("test/test_array.c");

   RUN_TEST(test_allocate_empty_array);
   RUN_TEST(test_allocate_array_with_capacity_too_small);
   RUN_TEST(test_allocate_array_with_capacity_larger);

   return UnityEnd();
}
