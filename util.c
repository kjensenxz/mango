/* util - utilities for mangoing text!
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

#include "util.h"
#include <stdlib.h>
#include <string.h>

const char *
strrev(const char *str) {
	char *rstr = NULL;
	int strln = 0;
	unsigned int i = 0;

	strln = strlen(str) + 1;

	rstr = calloc(sizeof(char *), strln);

	for (i = 0; i < strln - 1; ++i) {
		rstr[i] = str[strln-i-2];
	}

	return (const char *) rstr;
}
