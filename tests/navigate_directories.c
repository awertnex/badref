/* ==== _section table =========================================================
_section_testing ===============================================================
_section_setup =================================================================
_section_main ==================================================================
 */

/* TASKS:    [!]: done!    [x]: deleted
 * [!] tokenize file info and display alongside contents (e.g. (file or dir), file format) (21 Mar 2025)
 * [!] print whether chosen content is a file or a directory (21 Mar 2025)
 * [ ] navigate to directories and refresh path[] and contents[][]
 */

#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include <raylib.h>

#include <types.h>

// ---- variables --------------------------------------------------------------
u8 running = 1;

str path[512];
str path_next[512];
str contents[264][512];
str dir_next_name[512];
u16 content_index = 0;
u16 file_count = 0;
DIR *dir;
struct dirent *drnt;

// ---- signatures -------------------------------------------------------------
void init_gui();
void update_gui();
void update_path(str *content);
void tokenize_contents(u16 content_index, u8 *type);
str untokenize_contents(u16 content_index);
bool check_is_directory(str *content);
void input_listen_navigate(u16 content_index);
void input_listen();
char parse_file_type(u8 *type);
void init_dir();


void init_gui()
{
	InitWindow(420, 420, "badref");
	SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    SetWindowSize(420, 420);
    SetWindowPosition((1920/2) - 210, (1080/2) - 210);
}

void update_gui()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    EndDrawing();
}

// ==== _section_testing =======================================================
void update_path(str *content)
{
    snprintf(path_next, 512, "%s", path);
    strncat(path_next, content, 128);
    snprintf(path, 512, "%s", path_next);
}

void tokenize_contents(u16 content_index, u8 *type)
{
    if (*type == 4)
        strncat(contents[content_index], "{.dir}", 7);
}

str untokenize_contents(u16 content_index)
{
    str string[512];
    snprintf(string, 512, "%s", contents[content_index]);
    return *string;
}

//TODO: check if symlink leads to a directory
bool check_is_directory(str *content)
{
    for (u16 i = 0; i < 511 && content[i]; ++i)
    {
        if (!(strncmp(&content[i], "{.dir}", 7)))
        {
            return true;
        }
    }
    return false;
}

void input_listen_navigate(u16 content_index)
{
    if (check_is_directory(contents[content_index]))
    {
        snprintf(dir_next_name, 512, "%s", contents[content_index]);
        printf("cd: %s\n", dir_next_name);
    }
    else
        printf("cannot navigate to '%s', not a directory\n", contents[content_index]);
}

void input_listen()
{
    if (IsKeyPressed(KEY_Q))
        running = 0;

    if (IsKeyPressed(KEY_ZERO))
    {
        content_index = 0;
        input_listen_navigate(content_index);
    }
    if (IsKeyPressed(KEY_ONE))
    {
        content_index = 1;
        input_listen_navigate(content_index);
    }
    if (IsKeyPressed(KEY_TWO))
    {
        content_index = 2;
        input_listen_navigate(content_index);
    }
    if (IsKeyPressed(KEY_THREE))
    {
        content_index = 3;
        input_listen_navigate(content_index);
    }
    if (IsKeyPressed(KEY_FOUR))
    {
        content_index = 4;
        input_listen_navigate(content_index);
    }
    if (IsKeyPressed(KEY_FIVE))
    {
        content_index = 5;
        input_listen_navigate(content_index);
    }
    if (IsKeyPressed(KEY_SIX))
    {
        content_index = 6;
        input_listen_navigate(content_index);
    }
    if (IsKeyPressed(KEY_SEVEN))
    {
        content_index = 7;
        input_listen_navigate(content_index);
    }
    if (IsKeyPressed(KEY_EIGHT))
    {
        content_index = 8;
        input_listen_navigate(content_index);
    }
    if (IsKeyPressed(KEY_NINE))
    {
        content_index = 9;
        input_listen_navigate(content_index);
    }

    if (IsKeyPressed(KEY_P))
    {
        printf("--------------------------------------------------------------------------------\n%s\n", path);
    }

    if (IsKeyPressed(KEY_E))
    {
        //TODO: fix segfault
        update_path(untokenize_contents(contents[content_index]));
        printf("--------------------------------------------------------------------------------\n");
        printf("     path:  %s\nnext path:  %s\n", path, path_next);
        printf("--------------------------------------------------------------------------------\n");
    }
}

// ==== _section_setup =========================================================
char parse_file_type(u8 *type)
{
	if (*type == 4)
		return '/';
	return 0;
}

void init_dir()
{
	file_count = 0;
	dir = opendir("/");
    //TODO: shorten path name to absolute path nam
    snprintf(path, 512, "/var/../log/../log/./");
	for (u16 i = 0; i < 264 && contents[i][0] != 0; ++i)
		memset(contents[i], 0, 264);

	if (dir)
	{
		while ((drnt = readdir(dir)) != NULL)
		{
			snprintf(contents[file_count], 264, "%s%c", drnt->d_name, parse_file_type(&drnt->d_type));
            tokenize_contents(file_count, &drnt->d_type);
			++file_count;
		}
	}

	closedir(dir);
    for (u16 i = 0; i < 11 && contents[i][0] != 0; ++i)
        printf("%s\n", contents[i]);
    printf("--------------------------------------------------------------------------------\n");
}

// ==== _section_main ==========================================================
int main(void)
{
    init_gui();
    init_dir();

    while (running)
    {
        input_listen();
        update_gui();
    }
    return 0;
}
