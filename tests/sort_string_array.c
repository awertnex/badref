/* TASKS:    [!]: done!    [x]: deleted
 * [!] swap strings (Mar.18.2025)
 * [!] swap bits (Mar.19.2025)
 * [!] swap strings using swap_bits() (Mar.20.2025)
 * [!] sort string array (Mar.20.2025)
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>

#include <types.h>

#include "../h/dir.h"
#include "../logic.c"

str contents[CONTENT_ARRAY_SIZE][CONTENT_NAME_LENGTH_MAX] =
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
};

void sort_str_arr();
int main(void)
{
	for (u16 i = 0; i < CONTENT_ARRAY_SIZE && contents[i][0]; ++i)
		printf("%s\n", contents[i]);
	putchar('\n');
	sort_str_arr();
	//swap_strings(contents[0], contents[1]);
	
	for (u16 i = 0; i < CONTENT_ARRAY_SIZE && contents[i][0]; ++i)
		printf("%s\n", contents[i]);
	return 0;
}

//TODO: sort the last 2 strings as well
void sort_str_arr()
{
	for (u16 i = 0; i < CONTENT_ARRAY_SIZE - 1 && contents[i + 1]; ++i)
	{
		for (u16 j = 0; j < CONTENT_ARRAY_SIZE - 1 && contents[j][0] && contents[j + 1][0]; ++j)
		{
			if (tolower(contents[j][0]) > tolower(contents[j + 1][0]))
				swap_strings(contents[j], contents[j + 1]);

			if (tolower(contents[j][0]) == tolower(contents[j + 1][0]))
				for (u16 k = 1; k < CONTENT_NAME_LENGTH_MIN && contents[i][k] && contents[i + 1][k]; ++k)
				{
					if (tolower(contents[j][k]) > tolower(contents[j + 1][k]))
					{
						swap_strings(contents[j], contents[j + 1]);
						break;
					}
				}
		}
	}
}
