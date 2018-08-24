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

#define FORWARD 0
#define REVERSE 1

const char *mangoh(const char *, int);
const char *mangov(const char *, int);

// consolidated regular/backwards mango
const char *_mango(const char *, int);

inline const char *
mango(const char *str) {
	return _mango(str, FORWARD);
}

inline const char *
mangor(const char *str) {
	return _mango(str, REVERSE);
}

// _mango(str, FORWARD or REVERSE) -> forward or reverse mango
const char *
_mango (const char *str, int reverse) {
	if (str == NULL) {
		return NULL;
	}
	const char *horiz, *vert;
	int len = strlen(str);

	if (reverse == 1) {
		str = strrev(str);
		horiz = mangoh(str, len);
		vert = mangov(str, len);
	}
	else {
		horiz = mangoh(str, len);
		vert = mangov(str, len);
	}

	// two double-len strings, remove 1 null terminator
	int msglen = len * 2 * 2 - 1; 
	char *msg = calloc(sizeof(char *), msglen);

	strncat(msg, horiz, len*2);
	strncat(msg+len*2-1, vert, len*2);

	return msg;
}
// mangoh adds a space after every character, newline at the end,
// and returns it
const char *
mangoh (const char *str, int len) {
	int buflen = len * 2;
	unsigned int i = 0;

	char *msg = calloc(sizeof(char *), buflen);

	for (i = 0; i < buflen; i += 2) {
		msg[i] = str[i/2];
		msg[1+i] = ' ';
	}

	msg[i-1] = '\n';
	// msg[i] is already 0

	return msg;
}

const char *
mangov (const char *str, int len) {
	int buflen = len * 2;
	unsigned int i = 0;
	
	char *msg = calloc(sizeof(char *), buflen);

	for (i = 2; i < buflen; i += 2) {
		msg[i-2] = str[i/2];
		msg[i-1] = '\n';
	}

	return msg;
}
