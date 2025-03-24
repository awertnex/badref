#ifndef DIR_H

#include <limits.h>
#include <types.h>

#define FILES_MAX   2048
#define NAME_MIN    256

// ---- variables --------------------------------------------------------------
extern str path[PATH_MAX];
extern str files[FILES_MAX][NAME_MAX];
extern u16 file_index;
extern u16 file_count;

// ---- signatures -------------------------------------------------------------
void get_path_absolute();
void open_directory(u16 file_index);
char parse_file_type(u8 *type);

#define DIR_H
#endif
