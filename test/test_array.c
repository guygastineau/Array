#include "vendor/unity.h"
#include "../src/array.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_lib(void)
{
  TEST_ASSERT_EQUAL_STRING("Hello, World!", hello());
}

int main(void)
{
   UnityBegin("test/test_array.c");

   RUN_TEST(test_lib);

   return UnityEnd();
}
