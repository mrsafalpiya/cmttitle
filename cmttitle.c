#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dep/util.h"

/*
 ===============================================================================
 |                                     Data                                    |
 ===============================================================================
 */

/* = Constants = */
#define TEXT_WIDTH 80

/* = Enums = */
typedef enum {
	CMT_ERR_NONE,
	CMT_ERR_LEN /* Text width is not big enough to fit the title properly */
} cmt_title_err;

/*
 ===============================================================================
 |                            Function Declarations                            |
 ===============================================================================
 */
cmt_title_err
fill_cmt_title(char *str, const char *title, unsigned int title_len,
               unsigned int text_width);
/*
 * Fills up the `str` with proper title banner.
 *
 * Banner is of the format shown with the title "Data", "Function Declarations",
 * ... in this file.
 *
 * To learn more about the algorithm, see 'cmttitle_algo.pdf' available in this
 * repo.
 */

/*
 ===============================================================================
 |                           Function Implementations                          |
 ===============================================================================
 */
cmt_title_err
fill_cmt_title(char *str, const char *title, unsigned int title_len,
               unsigned int text_width)
{
	unsigned int i, left_space, right_space;

	if (text_width < title_len + 5)
		return CMT_ERR_LEN;

	/* First and second line */
	strcpy(str, "/*\n ");
	for (i = 0; i < text_width - 1; i++) {
		strcat(str, "=");
	}
	strcat(str, "\n");

	/* title */
	strcat(str, " |");

	left_space  = (text_width - title_len - 3) / 2;
	right_space = left_space;
	/* Check for the odd remaining space */
	if ((2 + left_space + title_len + right_space + 1) != text_width)
		right_space++;

	for (i = 0; i < left_space; i++) {
		strcat(str, " ");
	}
	strcat(str, title);
	for (i = 0; i < right_space; i++) {
		strcat(str, " ");
	}

	strcat(str, "|\n ");

	/* last two lines */
	for (i = 0; i < text_width - 1; i++) {
		strcat(str, "=");
	}
	strcat(str, "\n */\0");

	return CMT_ERR_NONE;
}

int
main(int argc, char **argv)
{
	int           i;
	char         *title_cmt, *title;
	unsigned int  title_len;
	cmt_title_err cmt_err;

	/* = Usage check = */
	if (argc < 2)
		die("Usage: %s title", argv[0]);

	/* = Prerequisites = */
	/* Concatenate all arguments after the first */
	for (i = 2; i < argc; i++)
		*(argv[i] - 1) = ' ';

	title     = argv[1];
	title_len = strlen(title);
	title_cmt = malloc((TEXT_WIDTH * 3 + 9) * sizeof(char));

	/* = Main work = */
	cmt_err = fill_cmt_title(title_cmt, title, title_len, TEXT_WIDTH);
	if (cmt_err != CMT_ERR_NONE)
		die("Text width is not big enough to fit the title properly!");

	printf("%s\n", title_cmt);

	free(title_cmt);
	return 0;
}
