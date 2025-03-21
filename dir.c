#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <libgen.h>
#include <string.h>
#include <dirent.h>

#include "h/dir.h"
#include "h/main.h"
#include "logic.c"

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
	dir = opendir(getenv("HOME"));
	for (u16 i = 0; i < 2048 && contents[i][0] != 0; ++i)
		memset(contents[i], 0, 1024);

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
	sort_string_array();
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

char parse_file_type(u8 *type)
{
	if (*type == 4)
		return '/';
	return 0;
}

/*
void sort_string_array()
{
	u8 parse;
	for (u16 i = 0; contents[i + 1] && parse; ++i, parse = 0)
	{
		for (u16 j = 0; j < 2047 && contents[j + 1][0]; ++j)
		{
			if (tolower(contents[j][0]) > tolower(contents[j + 1][0]))
			{
				swap_strings(contents[j], contents[j + 1]);
				parse = 1;
				continue;
			}

			if (tolower(contents[j][0]) == tolower(contents[j + 1][0]))
				for (u16 k = 1; k < 1023 && (contents[i][k] || contents[i + 1][k]); ++k)
				{
					if (tolower(contents[j][k]) > tolower(contents[j + 1][k]))
					{
						swap_strings(contents[j], contents[j + 1]);
						parse = 1;
						break;
					}
				}
		}
	}
}
*/
