#ifndef __UTILS_PRIVATE_H__
#define __UTILS_PRIVATE_H__

typedef enum color_spec {
	BLACK,
	RED,
	GREEN,
	YELLOW,
	VIOLET,
	PURPLE,
	CYAN,
	LIGHTGREY,
	DARKGREY,
	DARKRED,
	LIGHTGREEN,
	LIGHTYELLOW,
	LIGHTVIOLET,
	LIGHTPURPLE,
	LIGHTCYAN,
	WHITE
} color;

void clrscr();
void fgcolor(color);
char * getstr(char *, int, FILE *);

#endif /* __UTILS_PRIVATE_H__ */
