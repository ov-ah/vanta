#include "util.h"

char *read_file(const char *path)
{
	FILE *f = fopen(path, "rb");
	if (!f)
		return NULL;
	fseek(f, 0, SEEK_END);
	long len = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *buf = malloc(len + 1);
	if (!buf)
	{
		fclose(f);
		return NULL;
	}
	fread(buf, 1, len, f);
	buf[len] = '\0'; // null term
	fclose(f);
	return buf;
}
