#ifndef DIR_H

#include <types.h>

#define PATH_LENGTH             2048
#define CONTENT_ARRAY_SIZE      2048
#define CONTENT_NAME_LENGTH_MIN 256
#define CONTENT_NAME_LENGTH_MAX 264

// ---- variables --------------------------------------------------------------
extern str path[PATH_LENGTH];
extern str contents[CONTENT_ARRAY_SIZE][CONTENT_NAME_LENGTH_MAX];
extern u16 content_index;
extern u16 file_count;

// ---- signatures -------------------------------------------------------------
void init_path();
void parse_path();
void update_path(str *contents);
char parse_file_type(u8 *type);

#define DIR_H
#endif
