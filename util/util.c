#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "util.h"

int parse_input(FILE* d, int* res_buf)
{
    char* buf = calloc(LEN, sizeof(char));
    int res_len = 0;

    while (fgets(buf, LEN, d)) {
        int delim = 0;
        for (int i = 0; ; ++i) {
            if (buf[i] == ' ' || buf[i] == '\n') {
                char* chunk = malloc(((i - delim) + 1) * sizeof(char));
                memcpy(chunk, buf + delim, i - delim);
                int t = atoi(chunk);
                delim = i;

                res_buf[res_len] = t;

                ++res_len;

                if (buf[delim] == '\n' || buf[delim] == '\0') 
                    break;
            }
        }
    }

    return res_len;
}

struct iter {
    int i;
    int *buf;
};

int yield(int *buf, int n)
{
    static struct iter it;

    if (it.buf != buf) {
        it = (struct iter) {
            .buf = buf,
            .i = 0
        };
    }

    if (it.i == n)
        it.i = 0;

    return it.buf[it.i++];
}