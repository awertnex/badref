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
str path[PATH_LENGTH];
str path_next[PATH_LENGTH];
str contents[CONTENT_ARRAY_SIZE][CONTENT_NAME_LENGTH_MAX];
u16 content_index = 0;
u16 file_count = 0;
DIR *dir;
struct dirent *drnt;

void init_path()
{
	snprintf(path, PATH_LENGTH, "%s/", getenv("HOME"));
}

void parse_path()
{
	file_count = 0;
	dir = opendir(getenv("HOME"));
	for (u16 i = 0; i < CONTENT_ARRAY_SIZE && contents[i][0] != 0; ++i)
		memset(contents[i], 0, CONTENT_NAME_LENGTH_MAX);

	if (dir)
	{
		state |= STATE_CONTENTS_AVAILABLE;
		while ((drnt = readdir(dir)) != NULL)
		{
			snprintf(
                    contents[file_count],
                    CONTENT_NAME_LENGTH_MAX,
                    "%s%c",
                    drnt->d_name, parse_file_type(&drnt->d_type));
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
	memset(path_next, 0, PATH_LENGTH);
	snprintf(path_next, PATH_LENGTH, "%s", path);
	strncat(path_next, content, CONTENT_NAME_LENGTH_MAX);

	dir = opendir(path_next);
	if (dir)
	{
		snprintf(path, PATH_LENGTH, "%s", path_next);
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
