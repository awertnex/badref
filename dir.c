#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <libgen.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "h/dir.h"
#include "h/main.h"
#include "logic.c"

// ---- variables --------------------------------------------------------------
str path[PATH_MAX];
str files[FILES_MAX][NAME_MAX];
u16 file_index = 0;
u16 file_count = 0;
DIR *dir;
struct dirent *drnt;

void get_path_absolute()
{
    str path_relative[PATH_MAX] = {0};
    str *path_absolute;

    snprintf(path_relative, PATH_MAX, "%s", path);
    path_absolute = realpath(path_relative, NULL);
    if (!path_absolute)
    {
        free(path_absolute);
        return;
    }
    for (u16 i = 0; i < (PATH_MAX - 1); ++i)
        if (path_absolute[i + 1] == 0 && path_absolute[i] != '/')
        {
            strncat(path_absolute, "/", 2);
            break;
        }

    snprintf(path, PATH_MAX, "%s", path_absolute);
    free(path_absolute);
}

void open_directory(u16 file_index)
{
    get_path_absolute();

    str path_next[PATH_MAX] = {0};
    snprintf(path_next, PATH_MAX, "%s%s", path, files[file_index]);

    struct stat buf;
    stat(path_next, &buf);

    if (S_ISDIR(buf.st_mode))
    {
        snprintf(path, PATH_MAX, "%s", path_next);
        get_path_absolute();

        dir = opendir(path);
        if (dir)
        {
            file_count = 0;
            for (u16 i = 0; i < 264 /*TODO: FILES_MAX*/ && files[i][0]; ++i)
                memset(files[i], 0, NAME_MAX);

            while ((drnt = readdir(dir)))
            {
                snprintf(files[file_count], NAME_MAX, "%s%c", drnt->d_name, parse_file_type(&drnt->d_type));
                ++file_count;
            }
            sort_string_array();
            swap_strings(files[0], files[1]);

            closedir(dir);
        }
    }
    else printf("-- ERROR: '%s' is not a directory\n", files[file_index]);
}

char parse_file_type(u8 *type)
{
	if (*type == 4)
		return '/';
	return 0;
}
