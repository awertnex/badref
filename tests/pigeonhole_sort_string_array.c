
/* TASKS:    [!]: done!    [x]: deleted
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>

#include <types.h>

#include "../h/dir.h"
#include "../logic.c"

str files[FILES_MAX][NAME_MAX] =
{
    "cewfee    04",
    "abraham   03",
    "notapath  08",
    "natapath  06",
    "natapethi 07",
    "..        01",
    ".         00",
    "zylofoan  10",
    "zoro      09",
    ".Book     02",
    "linux     05",
};

void sort_str_arr()
{
    u16 count = 0;
    for (u16 i = 0; i < FILES_MAX && files[i][0]; ++i)
        ++count;

    for (u16 i = 0, smallest = 0; i < count; ++i)
    {
        smallest = i;
        for (u16 j = i + 1; j < count; ++j)
        {
            if (tolower(files[j][0]) < tolower(files[smallest][0]) && files[j][0] && files[smallest][0])
                smallest = j;

            if (tolower(files[j][0]) == tolower(files[smallest][0]) && files[j][0] && files[smallest][0])
                for (u16 k = 1; k < NAME_MAX - 1 && files[j][k - 1] && files[smallest][k - 1]; ++k)
                {
                    if (tolower(files[j][k]) < tolower(files[smallest][k]))
                    {
                        smallest = j;
                        break;
                    }
                }
        }

        swap_strings(files[i], files[smallest]);
    }

}

int main(void)
{
    for (u16 i = 0; i < FILES_MAX && files[i][0]; ++i)
        printf("%s\n", files[i]);
    printf("------------\n");
    sort_str_arr();

    for (u16 i = 0; i < FILES_MAX && files[i][0]; ++i)
        printf("%s\n", files[i]);
    return 0;
}
