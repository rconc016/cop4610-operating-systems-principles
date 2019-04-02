#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../LibFS.h"

struct _test
{
  char *name;
  void (*function)();
} typedef test_t;

void fs_boot_should_return_success()
{
  char *file = "test_disk_file";

  int result = FS_Boot(file);

  assert(result == 0);
}

void fs_boot_with_empty_filename_should_return_error()
{
  char *file = "";

  int result = FS_Boot(file);

  assert(result == -1);
}

#define TESTS_NUM 2

int main(int argc, char *argv[])
{
  test_t tests[TESTS_NUM] = 
  {
    {"fs_boot_should_return_success", &fs_boot_should_return_success},
    {"fs_boot_with_empty_filename_should_return_error", &fs_boot_with_empty_filename_should_return_error}
  };

  int index = 0;
  for (index = 0; index < TESTS_NUM; index = index + 1)
  {
    test_t test = tests[index];
    printf("[Test Runner] Executing: %s\n", test.name);
    test.function();
  }

  printf("\nAll tests passed!\n");
  return 0;
}