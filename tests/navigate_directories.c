/* ==== _section table =========================================================
_section_testing ===============================================================
_section_main ==================================================================
 */

/* TASKS:    [!]: done!    [x]: deleted
 * [!] tokenize file info and display alongside contents (e.g. (file or dir), file format) (21 Mar 2025)
 * [!] print whether chosen content is a file or a directory (21 Mar 2025)
 * [!] navigate to directories and refresh path[] and contents[][] (23 Mar 2025)
 * [ ] navigate to symlinks that lead to directories
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include <raylib.h>

#include <types.h>

// ---- variables --------------------------------------------------------------
u8 running = 1;

str path[PATH_MAX] = {0};
str contents[264][NAME_MAX] = {0};
u16 content_index = 0;
u16 file_count = 0;
DIR *dir;
struct dirent *drnt;

// ---- signatures -------------------------------------------------------------
void get_path_absolute();
void open_directory(u16 content_index);
void load_path();
void input_listen();
char parse_file_type(u8 *type);

// ==== _section_testing =======================================================
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
            strncat(path_absolute, "/", 1);
            break;
        }

    snprintf(path, PATH_MAX, "%s", path_absolute);
    free(path_absolute);
}

void open_directory(u16 content_index)
{
    str path_next[PATH_MAX] = {0};
    snprintf(path_next, PATH_MAX, "%s%s", path, contents[content_index]);
    get_path_absolute();

    struct stat buf;
    stat(path_next, &buf);

    if (!(S_ISREG(buf.st_mode)))
    {
        printf("it's working\n"); //temp
        snprintf(path, PATH_MAX, "%s", path_next);
        get_path_absolute();
        load_path();
    }
    else printf("-- ERROR: '%s' is not a directory\n", contents[content_index]);
}

void load_path()
{
    dir = opendir(path);
    if (dir)
    {
        file_count = 0;
        for (u16 i = 0; i < 264 /*TODO: FILES_MAX*/ && contents[i][0]; ++i)
            memset(contents[i], 0, NAME_MAX);

        while ((drnt = readdir(dir)))
        {
            snprintf(contents[file_count], NAME_MAX, "%s%c", drnt->d_name, parse_file_type(&drnt->d_type));
            ++file_count;
        }

        closedir(dir);
        return;
    }

    printf("notapath\n"); //temp
}

void input_listen()
{
    if (IsKeyPressed(KEY_Q))
        running = 0;

    if (IsKeyPressed(KEY_ZERO))
    {
        content_index = 0;
        open_directory(content_index);
    }
    if (IsKeyPressed(KEY_ONE))
    {
        content_index = 1;
        open_directory(content_index);
    }
    if (IsKeyPressed(KEY_TWO))
    {
        content_index = 2;
        open_directory(content_index);
    }
    if (IsKeyPressed(KEY_THREE))
    {
        content_index = 3;
        open_directory(content_index);
    }
    if (IsKeyPressed(KEY_FOUR))
    {
        content_index = 4;
        open_directory(content_index);
    }
    if (IsKeyPressed(KEY_FIVE))
    {
        content_index = 5;
        open_directory(content_index);
    }
    if (IsKeyPressed(KEY_SIX))
    {
        content_index = 6;
        open_directory(content_index);
    }
    if (IsKeyPressed(KEY_SEVEN))
    {
        content_index = 7;
        open_directory(content_index);
    }
    if (IsKeyPressed(KEY_EIGHT))
    {
        content_index = 8;
        open_directory(content_index);
    }
    if (IsKeyPressed(KEY_NINE))
    {
        content_index = 9;
        open_directory(content_index);
    }

    if (IsKeyPressed(KEY_C))
    {
        for (u16 i = 0; i < 11 && contents[i][0] != 0; ++i)
            printf("%s\n", contents[i]);
        printf("--------------------------------------------------------------------------------\n");
    }

    if (IsKeyPressed(KEY_P))
    {
        printf("%s\n", path);
    }

    if (IsKeyPressed(KEY_R))
        load_path();
}

char parse_file_type(u8 *type)
{
	if (*type == 4)
		return '/';
	return 0;
}

// ==== _section_main ==========================================================
int main(void)
{
    InitWindow(420, 420, "badref");
	SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    SetWindowSize(420, 420);
    SetWindowPosition((1920/2) - 210, (1080/2) - 210);

    snprintf(path, PATH_MAX, "/var/log/../cache/..");
    get_path_absolute();
    load_path();

    while (running)
    {
        input_listen();

        BeginDrawing();
        ClearBackground(DARKGRAY);
        EndDrawing();
    }
    return 0;
}
