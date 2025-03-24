/* TASKS:    [!]: done!    [x]: deleted
 * [!] swap strings (Mar.18.2025)
 * [!] swap bits (Mar.19.2025)
 * [!] swap strings using swap_bits() (Mar.20.2025)
 * [!] sort string array (Mar.20.2025)
 * [ ] make selection-sort or pigeonhole-sort
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
	"cewfee",
	"abraham",
	"notapath",
	"natapath",
	"natapethi",
	"..",
	".",
	"zoro",
	"zylofoan",
	".Book",
	"linux",
    "zeez",
};

//TODO: sort the last 2 strings as well
void sort_str_arr()
{
	for (u16 i = 0; i < FILES_MAX - 1 && files[i + 1]; ++i)
	{
		for (u16 j = 0; j < FILES_MAX - 1 && files[j][0] && files[j + 1][0]; ++j)
		{
			if (tolower(files[j][0]) > tolower(files[j + 1][0]))
                swap_strings(files[j], files[j + 1]);

			if (tolower(files[j][0]) == tolower(files[j + 1][0]))
				for (u16 k = 1; k < NAME_MAX - 1 && files[i][k] && files[i + 1][k]; ++k)
				{
					if (tolower(files[j][k]) > tolower(files[j + 1][k]))
					{
						swap_strings(files[j], files[j + 1]);
						break;
					}
				}
		}
	}
}

int main(void)
{
	for (u16 i = 0; i < FILES_MAX && files[i][0]; ++i)
		printf("%s\n", files[i]);
	putchar('\n');
	sort_str_arr();
	
	for (u16 i = 0; i < FILES_MAX && files[i][0]; ++i)
		printf("%s\n", files[i]);
	return 0;
}
