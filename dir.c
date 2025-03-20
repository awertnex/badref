#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <libgen.h>
#include <string.h>
#include <dirent.h>

#include "dir.h"
#include "main.h"

// ---- variables --------------------------------------------------------------
str path[4096];
str path_next[4096];
str contents[2048][1024];
u16 content_index = 0;
u16 file_count = 0;
DIR *dir;
struct dirent *drnt;

void init_path()
{
	snprintf(path, 4096, "%s/", getenv("HOME"));
}

void parse_path()
{
	file_count = 0;
	dir = opendir(path);

	if (dir)
	{
		state |= STATE_CONTENTS_AVAILABLE;
		while ((drnt = readdir(dir)) != NULL)
		{
			snprintf(contents[file_count], 1024, "%s%c", drnt->d_name, parse_file_type(&drnt->d_type));
			++file_count;
		}
	}

	closedir(dir);
	sort_str_arr();
	swap_strings(contents[0], contents[1]);
	return;
	state &= ~STATE_CONTENTS_AVAILABLE;
}

void update_path(str *content)
{
	memset(path_next, 0, strlen(path_next));
	snprintf(path_next, 4096, "%s", path);
	strncat(path_next, content, 1024);

	dir = opendir(path_next);
	if (dir)
	{
		snprintf(path, 4096, "%s", path_next);
		closedir(dir);
	}
	printf("path: %s\ncontents: %s\n", path, content); /*temp*/
}

// =============================================================================
// ==== _section_logic =========================================================
// =============================================================================
char parse_file_type(u8 *type)
{
	if (*type == 4)
		return '/';
	return 0;
}

void swap_strings(str *s1, str *s2)
{
	str temp[1024] = {0};
	snprintf(temp, 1024, "%s", s1);
	snprintf(s1, 1024, "%s", s2);
	snprintf(s2, 1024, "%s", temp);
}

void sort_str_arr()
{
	u8 parse, s1 = 0, s2 = 0;
	for (u16 i = 0; i < 2047 && contents[i + 1][0] != 0; ++i, parse = 1)
	{
		//if (contents[i][0] == '.' && i == 2) s1 = 1;
		//if (contents[i + 1][0] == '.' && i == 2) s2 = 1;

		if (tolower(contents[i][s1]) == tolower(contents[i + 1][s2]))
			for (u16 j = 1; j < 1024; ++j)
			{
				if (tolower(contents[i][j + s1]) > tolower(contents[i + 1][j + s2]))
				{
					swap_strings(contents[i], contents[i + 1]);
					parse = 0;
					break;
				}
			}

		if (parse && tolower(contents[i][s1]) > tolower(contents[i + 1][s2]))
		{
			swap_strings(contents[i], contents[i + 1]);
			i = 0;
		}
		s1 = 0;
		s2 = 0;
	}
}
