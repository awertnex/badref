#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>

#include <types.h>

#include "h/dir.h"

#define TEST_SORT_STR_ARR
#ifdef TEST_SORT_STR_ARR
str contents[2048][1024];
u16 file_count = 0;
DIR *dir;
struct dirent *drnt;

char parse_file_type(u8 *type)
{
	if (*type == 4)
		return '/';
	return 0;
}

void sort_str_arr2();

int main()
{
	dir = opendir(getenv("HOME"));
	for (u16 i = 0; i < 2048 && contents[i][0] != 0; ++i)
		memset(contents[i], 0, 1024);

	if (dir)
	{
		while ((drnt = readdir(dir)) != NULL)
		{
			snprintf(contents[file_count], 1024, "%s%c", drnt->d_name, parse_file_type(&drnt->d_type));
			++file_count;
		}
	}

	closedir(dir);
	sort_str_arr();
	swap_strings(contents[0], contents[1]);
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
	u8 parse = 1, s1, s2;
	for (u16 i = 0, j = 1;
			i < 2047 && j < 1023 && contents[i + 1][0];
			++j, parse = 1)
	{
		if (contents[i][0] == '.' && i >= 2) s1 = 1;
		else s1 = 0;
		if (contents[i + 1][0] == '.' && i >= 2) s2 = 1;
		else s2 = 0;

		if (toupper(contents[i][s1]) == toupper(contents[i + 1][s2]))
			for (; j < 1023; ++j)
			{
				if (toupper(contents[i][j + s1]) > toupper(contents[i + 1][j + s2]))
				{
					swap_strings(contents[i], contents[i + 1]);
					parse = 0;
					break;
				}
			}

		if (parse && toupper(contents[i][s1]) > toupper(contents[i + 1][s2]))
		{
			swap_strings(contents[i], contents[j]);
			i = 0;
		}
	}

	/* old: unfinished
	u8 parse = 1, s1, s2;
	for (u16 i = 0; i < 2047 && contents[i + 1][0]; ++i, parse = 1)
	{
		if (contents[i][0] == '.' && i == 2) s1 = 1;
		else s1 = 0;
		if (contents[i + 1][0] == '.' && i == 2) s2 = 1;
		else s2 = 0;

		if (toupper(contents[i][s1]) == toupper(contents[i + 1][s2]))
			for (u16 j = 1; j < 1023; ++j)
			{
				if (toupper(contents[i][j + s1]) > toupper(contents[i + 1][j + s2]))
				{
					swap_strings(contents[i], contents[i + 1]);
					parse = 0;
					break;
				}
			}

		if (parse && toupper(contents[i][s1]) > toupper(contents[i + 1][s2]))
		{
			swap_strings(contents[i], contents[i + 1]);
			i = 0;
		}
	}
	*/
	for (u16 i = 0; i < 2047 && contents[i][0] != 0; ++i)
		printf("%s\n", contents[i]); //temp
}

#endif /* TEST_SORT_STR_ARR */
