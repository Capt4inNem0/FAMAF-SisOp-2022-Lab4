#ifndef _BIG_BROTHER_H
#define _BIG_BROTHER_H

#define BB_LOG_FILE "/bb/fs.log"
#define BB_DIRNAME "/bb"
#define LOG_FILE_BASENAME "fs"
#define LOG_FILE_EXTENSION "log"

#include "fat_file.h"

int bb_is_log_file_dentry(fat_dir_entry dir_entry);

int bb_is_log_filepath(const char *filepath);

int bb_is_log_dirpath(const char *filepath);

u32 search_bb_orphan_dir_cluster();

void bb_create_orphan_dir();

void bb_read_log(u32 start_cluster);

#endif