#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

void
die(const char *fmt, ...);

void
die(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
		fputc(' ', stderr);
		if (errno != 0)
			perror(NULL);
		else
			fprintf(stderr, "Something went wrong\n");
	} else {
		fputc('\n', stderr);
	}

	exit(EXIT_FAILURE);
}
#endif /* UTIL_H */
