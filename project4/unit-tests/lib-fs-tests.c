#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../LibDisk.h"
#include "../LibFS.h"
#include "../LibFS.c"

struct _test
{
  char *name;
  void (*function)();
} typedef test_t;

#define TEST_DISK_FILE "test_disk_file"

void fs_boot_should_return_success()
{
  char *file = TEST_DISK_FILE;
  char inode_bitmap[SECTOR_SIZE];
  char sector_bitmap[SECTOR_SIZE];
  char root_inode_data[SECTOR_SIZE];
  inode_t *root_inode;

  int result = FS_Boot(file);
  Disk_Read(INODE_BITMAP_START_SECTOR, inode_bitmap);
  Disk_Read(SECTOR_BITMAP_START_SECTOR, sector_bitmap);
  Disk_Read(INODE_TABLE_START_SECTOR, root_inode_data);
  root_inode = (inode_t*)root_inode_data;

  assert(result == 0);
  assert(inode_bitmap[0] == 1);
  assert(sector_bitmap[0] == 1 && sector_bitmap[DATABLOCK_START_SECTOR - 1] == 1);
  assert(root_inode->size == 0 && root_inode->type == 1);
}

void fs_boot_with_empty_filename_should_return_error()
{
  char *file = "";

  int result = FS_Boot(file);

  assert(result == -1);
}

void file_create_should_succeed()
{
  FS_Boot(TEST_DISK_FILE);
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
    printf("\n[Test Runner] Executing: %s\n", test.name);
    test.function();
  }

  printf("\n*** All tests passed! ***\n");
  return 0;
}