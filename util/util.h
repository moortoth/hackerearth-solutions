#ifndef	_UTIL_H
#define _UTIL_H

#define LEN 1024 * 1024 * sizeof(char)

extern int parse_input(FILE* d, int* res_buf);
extern int yield(int*, int);

#endif // _UTIL_H