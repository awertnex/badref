#include <stdio.h>
#include <string.h>
#include <types.h>

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

