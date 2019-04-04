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
  char *file = "/test-file";
  char inode_bitmap[SECTOR_SIZE];
  char inode_table[SECTOR_SIZE];
  char dirent_buffer[SECTOR_SIZE];
  inode_t *root_inode;
  inode_t *file_inode;
  dirent_t *dirent;
  FS_Boot("file_create_should_succeed.disk");

  int result = File_Create(file);
  Disk_Read(INODE_BITMAP_START_SECTOR, inode_bitmap);
  Disk_Read(INODE_TABLE_START_SECTOR, inode_table);
  root_inode = (inode_t*)inode_table;
  file_inode = (inode_t*)(inode_table + 1 * sizeof(inode_t));
  Disk_Read(root_inode->data[0], dirent_buffer);
  dirent = (dirent_t*)dirent_buffer;

  assert(result == 0);
  assert(inode_bitmap[1] == 1);
  assert(root_inode->size == 1 && root_inode->type == 1);
  assert(file_inode->size == 0 && file_inode->type == 0);
  assert(dirent->inode == 1 && strstr(file, dirent->fname) != NULL);
}

void dir_create_should_succeed()
{
  char *file = "/test-dir";
  char inode_bitmap[SECTOR_SIZE];
  char inode_table[SECTOR_SIZE];
  char dirent_buffer[SECTOR_SIZE];
  inode_t *root_inode;
  inode_t *dir_inode;
  dirent_t *dirent;
  FS_Boot("dir_create_should_succeed.disk");

  int result = Dir_Create(file);
  Disk_Read(INODE_BITMAP_START_SECTOR, inode_bitmap);
  Disk_Read(INODE_TABLE_START_SECTOR, inode_table);
  root_inode = (inode_t*)inode_table;
  dir_inode = (inode_t*)(inode_table + 1 * sizeof(inode_t));
  Disk_Read(root_inode->data[0], dirent_buffer);
  dirent = (dirent_t*)dirent_buffer;

  assert(result == 0);
  assert(inode_bitmap[1] == 1);
  assert(root_inode->size == 1 && root_inode->type == 1);
  assert(dir_inode->size == 0 && dir_inode->type == 1);
  assert(dirent->inode == 1 && strstr(file, dirent->fname) != NULL);
}

file_unlink_should_succeed()
{
  char *file = "/test-file";
  char inode_bitmap[SECTOR_SIZE];
  char inode_table[SECTOR_SIZE];
  char dirent_buffer[SECTOR_SIZE];
  inode_t *root_inode;
  inode_t *dir_inode;
  dirent_t *dirent;

  FS_Boot("file_unlink_should_succeed.disk");
  File_Create(file);

  int result = File_Unlink(file);
  Disk_Read(INODE_BITMAP_START_SECTOR, inode_bitmap);
  Disk_Read(INODE_TABLE_START_SECTOR, inode_table);
  root_inode = (inode_t*)inode_table;
  dir_inode = (inode_t*)(inode_table + 1 * sizeof(inode_t));
  Disk_Read(root_inode->data[0], dirent_buffer);
  dirent = (dirent_t*)dirent_buffer;

  assert(result == 0);
  assert(inode_bitmap[1] == 0);
  assert(root_inode->size == 0 && root_inode->type == 1);
  assert(dirent->inode == -1 && strcmp(dirent->fname, "") == 0);
}

dir_unlink_should_succeed()
{
  char *file = "/test-file";
  char inode_bitmap[SECTOR_SIZE];
  char inode_table[SECTOR_SIZE];
  char dirent_buffer[SECTOR_SIZE];
  inode_t *root_inode;
  inode_t *dir_inode;
  dirent_t *dirent;

  FS_Boot("dir_unlink_should_succeed.disk");
  File_Create(file);

  int result = Dir_Unlink(file);
  Disk_Read(INODE_BITMAP_START_SECTOR, inode_bitmap);
  Disk_Read(INODE_TABLE_START_SECTOR, inode_table);
  root_inode = (inode_t*)inode_table;
  dir_inode = (inode_t*)(inode_table + 1 * sizeof(inode_t));
  Disk_Read(root_inode->data[0], dirent_buffer);
  dirent = (dirent_t*)dirent_buffer;

  assert(result == 0);
  assert(inode_bitmap[1] == 0);
  assert(root_inode->size == 0 && root_inode->type == 1);
  assert(dirent->inode == -1 && strcmp(dirent->fname, "") == 0);
}

#define TESTS_NUM 6

int main(int argc, char *argv[])
{
  test_t tests[TESTS_NUM] = 
  {
    {"fs_boot_should_return_success", &fs_boot_should_return_success},
    {"fs_boot_with_empty_filename_should_return_error", &fs_boot_with_empty_filename_should_return_error},
    {"file_create_should_succeed", &file_create_should_succeed},
    {"dir_create_should_succeed", &dir_create_should_succeed},
    {"file_unlink_should_succeed", &file_unlink_should_succeed},
    {"dir_unlink_should_succeed", &dir_unlink_should_succeed}
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