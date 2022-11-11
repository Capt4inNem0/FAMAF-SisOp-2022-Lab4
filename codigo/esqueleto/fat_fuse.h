#ifndef _FAT_FS_H
#define _FAT_FS_H

typedef struct global_options_s {
    int hide_logfile;
} global_options;

global_options getGlobalOptions();

#endif /* _FAT_FS_H */