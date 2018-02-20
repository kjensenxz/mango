/* libmango - libmango for mangoing your text!
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

#include "libmango.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// regular mango
static void mangoh(const char *);
static void mangov(const char *);

// wrapper for reverse mango
static void mangorv(const char *);
static void mangorh(const char *);

void
mango (const char *str) {
	if (str == NULL) {
		fprintf(stderr, "Error: mango called with null pointer\r\n"
				"Terminating with EXIT_FAILURE\r\n");
		exit(EXIT_FAILURE);
		return;
	}

	mangoh(str);
	mangov(str);

	return;
}

void
mangor (const char *str) {
	if (str == NULL) {
		fprintf(stderr, "Error: mango called with null pointer\r\n"
				"Terminating with EXIT_FAILURE\r\n");
		exit(EXIT_FAILURE);
		return;
	}

	mangorh(str);
	mangorv(str);

	return;
}

// mangoh(const char *): adds a space after every character, prints it
static void
mangoh (const char *str) {
	unsigned int i = 0;

	int buflen = (strlen(str) * 2) - 1;
	char *msgsp = calloc(sizeof(char *), buflen);

	for (i = 0; i < buflen; i += 2) {
		msgsp[i] = str[i/2];
		msgsp[1+i] = ' ';
	}

	printf("%s\r\n", msgsp);

	free(msgsp);

	return;
}

static void
mangov (const char *str) {
	unsigned int i = 0;

	for (i = 1; i < strlen(str); ++i) {
		printf("%c\r\n", i[str]);
	}

	return;
}

static void
mangorv(const char *str) {
	const char *rstr = NULL;

	rstr = strrev(str);

	mangov(rstr);

	return;
}

static void
mangorh(const char *str) {
	const char *rstr = NULL;

	rstr = strrev(str);

	mangoh(rstr);

	return;
}
