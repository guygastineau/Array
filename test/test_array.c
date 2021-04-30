// Change the configurable macros, so we can test they
// provide the configurability they should.

// The array sizes will only ever be powers of 2.x
#define ARRAY_MIN_CAP 8
#define ARRAY_GROW_RATIO 0.80
#define ARRAY_SHRINK_RATIO 0.3

#include "../src/array.h"

#include "vendor/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_allocate_empty_array(void)
{
  Array *arr = mkArray();
  TEST_ASSERT_NOT_NULL_MESSAGE(arr, "mkArray failed to allocate");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(arr->cap, ARRAY_MIN_CAP,
                                   "mkArray failed to use ARRAY_MIN_CAP");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(arr->count, 0,
                                   "mkArray new array size not 0");
  TEST_ASSERT_NOT_NULL_MESSAGE(arr->data,
                               "mkArray failed to allocate internal buffer");
}

int main(void)
{
   UnityBegin("test/test_array.c");

   RUN_TEST(test_allocate_empty_array);

   return UnityEnd();
}
