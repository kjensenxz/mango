/* mango - mango your text!
 * Copyright (C) 2018 Kenneth B. Jensen <kenneth@jensen.cf>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// TODO: errno.h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdnoreturn.h>
#include "libmango.h"

#ifndef VERSION
#define VERSION "3.0, not built with make"
#endif

// 'sys' functions -- shell/main setup for API calling
static void usage (int, char **);
static void parseopts (int, char **, unsigned char *);
static void version (void);
static const char *argvtostr (int, char **);

int
main (int argc, char **argv) {
	unsigned char rflag = 0;
	const char *msg = NULL;
	
	parseopts(argc, argv, &rflag);

	msg = argvtostr(argc, argv);

	if (msg == NULL) {
		msg = "mango";
	}
	
	switch(rflag) {
		case 1:
			printf("%s", mangor(msg));
			break;
		case 0:
		default:
			printf("%s", mango(msg));
			break;
	}

	return EXIT_SUCCESS;
}

static void 
parseopts(int argc, char **argv, unsigned char *rflag) {
	int c = 0;

	while ((c = getopt(argc, argv, "vrh?")) != -1) {
		switch (c) {
			case 'v':
				version();
				break;
			case 'r':
				*rflag = 1;
				break;
			case 'h':
			case '?':
			default :
				usage(argc, argv);
				break;
		}
	} 

	return;
}

static const char *
argvtostr (int argc, char **argv) {
	int i = 0, j = 0, k = 0;
	int ct = argc - 1; // null pointer
	char *msg = NULL;

	// find length of argv
	for (i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			continue;
		}
		for (j = 0; j < strlen(argv[i]); ++j) {
			ct++; // characters
		}
	}

	msg = calloc(sizeof(char *), ct);
	
	// load up msg with argv and spaces in between
	for (i = 1, k = 0; i < argc; ++i) {
		if (argv[i][0] == '-') {
			continue;
		}
		for (j = 0; j < strlen(argv[i]); ++j, k++) {
			msg[k] = argv[i][j]; 
		}
		msg[k++] = ' ';
	}
	msg[k-1] = '\0'; // otherwise we'll get a blank line at the end

	if (strlen(msg) < 1) {
		return NULL;
	}

	return (const char*) msg;
}


noreturn static void
usage(int argc, char **argv) {
	fprintf(stderr,
		"Usage: %s [your message with as many spaces as you want]\r\n"
		"Mango your text!\r\n"
		"\t -h, -?: This message!\r\n"
		"\t     -v: Version & license information\r\n"
		"\t     -r: Reverse mango!\r\n",
		argv[0]);
	exit(EXIT_SUCCESS);
}

noreturn static void
version(void) {
	fprintf(stderr, "mango %s - Copyright (C) 2018 Kenneth B. Jensen\r\n"
		"This program is free software as licensed under the GNU GPL, version 3.\r\n"
		"See LICENSE.md for details, or, if you did not recieve a copy of the\r\n"
		"\tGPLv3, see <http://www.gnu.org/licenses/>.\r\n"
		"For more information, please see the README.md\r\n",
		VERSION
	);
	exit(EXIT_SUCCESS);
}
