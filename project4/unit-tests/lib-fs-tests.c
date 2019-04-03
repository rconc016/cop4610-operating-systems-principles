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

void fs_boot_should_return_success()
{
  char *file = "fs_boot_should_return_success.disk";
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
  char inode_bitmap[SECTOR_SIZE];
  char root_inode_data[SECTOR_SIZE];
  char file_inode_data[SECTOR_SIZE];
  inode_t *root_inode;
  inode_t *file_inode;
  FS_Boot("file_create_should_succeed.disk");

  int result = File_Create("/test-file");
  Disk_Read(INODE_BITMAP_START_SECTOR, inode_bitmap);
  Disk_Read(INODE_TABLE_START_SECTOR, root_inode_data);
  Disk_Read(INODE_TABLE_START_SECTOR + 1, file_inode_data);
  root_inode = (inode_t*)root_inode_data;
  file_inode = (inode_t*)file_inode_data;

  assert(result == 0);
  assert(inode_bitmap[1] == 1);
  assert(root_inode->size == 1 && root_inode->type == 1);
  assert(file_inode->size == 0 && file_inode->type == 0);
}

#define TESTS_NUM 3

int main(int argc, char *argv[])
{
  test_t tests[TESTS_NUM] = 
  {
    {"fs_boot_should_return_success", &fs_boot_should_return_success},
    {"fs_boot_with_empty_filename_should_return_error", &fs_boot_with_empty_filename_should_return_error},
    {"file_create_should_succeed", &file_create_should_succeed}
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