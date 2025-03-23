#ifndef DIR_H

#include <limits.h>
#include <types.h>

#define FILES_MAX   2048
#define NAME_MIN    256

// ---- variables --------------------------------------------------------------
extern str path[PATH_MAX];
extern str contents[FILES_MAX][NAME_MAX];
extern u16 content_index;
extern u16 file_count;

// ---- signatures -------------------------------------------------------------
void init_path();
void parse_path();
void update_path(str content[NAME_MAX]);
char parse_file_type(u8 *type);

#define DIR_H
#endif
