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

static void test_allocate_empty_array(void)
{
  Array *arr = mkArray();
  TEST_ASSERT_NOT_NULL_MESSAGE(arr, "mkArray failed to allocate");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(ARRAY_MIN_CAP, arr->cap,
                                   "mkArray failed to use ARRAY_MIN_CAP");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(0, arr->count,
                                   "mkArray new array size not 0");
  TEST_ASSERT_NOT_NULL_MESSAGE(arr->data,
                               "mkArray failed to allocate internal buffer");
  // The only way this is tested is by running `make memcheck'.
  arrayDestroy(arr);
}

int main(void)
{
   UnityBegin("test/test_array.c");

   RUN_TEST(test_allocate_empty_array);

   return UnityEnd();
}
