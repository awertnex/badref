#ifndef DIR_H

#include <types.h>

// ---- variables --------------------------------------------------------------
extern str path[4096];
extern str contents[2048][1024];
extern u16 content_index;
extern u16 file_count;

// ---- signatures -------------------------------------------------------------
void init_path();
void parse_path();
void update_path(str *contents);
char parse_file_type(u8 *type);
void swap_strings(str *s1, str *s2);
void sort_str_arr();

#define DIR_H
#endif
