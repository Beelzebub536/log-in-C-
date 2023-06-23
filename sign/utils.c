#include <stdio.h>
#include <string.h>

#include "utils.h"

void clrscr()
{
	printf("\e[H\e[2J");
}

void fgcolor(color name)
{
	printf("\e[%um", (name < DARKGREY) ? 30 + name : 82 + name );
}

char * getstr(char *s, int size, FILE *in)
{
	fgets(s, size, in);
	s[strcspn(s, "\r\n")] = 0;
	return s;
}
