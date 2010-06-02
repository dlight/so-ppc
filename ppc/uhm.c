#define _SVID_SOURCE
#include <dirent.h>

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* ss(char* file)
{
	FILE* f = fopen(file, "r");

	char* s = malloc(255);

	for (int i = 0, c; i < 255 && (c = getc(f)) != EOF; i++)
		s[i] = c;

	return s;
}

char* name(char* n)
{
	int q = 255;

	char* s = malloc(q);
	s[0] = '\0';

	return strncat(
		strncat(
		strncat(s, "/proc/", q), n, q), "/cmdline", q);
}

char* get_name(char* n)
{
	char* q = name(n);
	char* s = ss(q);
	free(q);
	return s;
}


int filter(const struct dirent* d)
{
	for (int i = 0; d->d_name[i] != '\0'; i++)
		if (!isdigit(d->d_name[i]))
			return 0;

	return 1;
}

int main(void)
{
	puts(ss(name("11019")));
	puts(ss("/proc/11019/cmdline"));

	struct dirent **namelist;
	int n;

	n = scandir("/proc", &namelist, filter, alphasort);

	char a[255];

	if (n < 0)
		perror("scandir");
	else {
		while (n--) {
			a[0] = '\0';

			char* q = get_name(namelist[n]->d_name);

			printf("%s %s\n", namelist[n]->d_name, q);

			//free(q);

			free(namelist[n]);
		}

		free(namelist);
	}
}

