#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include <types.h>

// ---- variables --------------------------------------------------------------
str path[128];
str path_next[128];
str contents[2048][1024];
u16 content_index = 0;
u16 file_count = 0;
DIR *dir;
struct dirent *drnt;

char parse_file_type(u8 *type)
{
	if (*type == 4)
		return '/';
	return 0;
}

int main(void)
{
	file_count = 0;
	dir = opendir("/");
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
    for (u16 i = 0; i < 2048 && contents[i][0] != 0; ++i)
        printf("%s\n", contents[i]);
    return 0;
}
