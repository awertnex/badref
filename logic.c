#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <types.h>

#include "h/dir.h"

void print_bits(u64 x, u8 bit_count)
{
	while(bit_count--)
		putchar('0' + ((x >> bit_count) & 1));
	putchar('\n');
}

void swap_bits(char *c1, char *c2, u8 bit_count)
{
	for (u8 i = 0; i < bit_count; ++i)
	{
		if (((*c1 >> i) & 1) == ((*c2 >> i) & 1)) continue;
		*c1 ^= (1 << i);
		*c2 ^= (1 << i);
	}
}

void swap_strings(str *s1, str *s2)
{
	for (u16 i = 0; i <= strlen(s1) || i <= strlen(s2); ++i)
		swap_bits(&s1[i], &s2[i], 8);
}

//TODO: sort the last 2 strings as well
void sort_string_array()
{
	for (u16 i = 0; i < FILES_MAX - 1 && files[i + 1]; ++i)
	{
		for (u16 j = 0; j < FILES_MAX - 1 && files[j][0] && files[j + 1][0]; ++j)
		{
			if (tolower(files[j][0]) > tolower(files[j + 1][0]))
                swap_strings(files[j], files[j + 1]);

			if (tolower(files[j][0]) == tolower(files[j + 1][0]))
				for (u16 k = 1; k < NAME_MAX - 1 && files[i][k - 1] && files[i + 1][k - 1]; ++k)
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
