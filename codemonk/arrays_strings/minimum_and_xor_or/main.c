#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include "util.h"

#define SINGLE_NUM_LEN 16

typedef long long u64;

int min_and_xor_or(int* buf, int len, FILE* out) {
    assert(len >= 2);
    int buf_max = 0;
    int buf_min = INT_MAX;

    for (int i = 0; i < len; ++i) {
        if (buf_max < buf[i])
            buf_max = buf[i];
        if (buf_min > buf[i])
            buf_min = buf[i];
    }

    int res = buf_max ^ buf_min;
    char* b = calloc(SINGLE_NUM_LEN, sizeof(char));
    sprintf(b, "%d\n", res);
    fputs(b, out);

    return res;
}

void insertion_sort(int* buf, int len) {
    
}

int main() {
    FILE *i_file = fopen("test", "r");
    FILE *o_file = fopen("out", "w+");
    int *i_buf = calloc(1024 * 1024 * 32, sizeof(int));
    int i_len = parse_input(i_file, i_buf);
    int t = yield(i_buf, i_len);
    
    for (int i = 0; i < t; ++i) {
        int n = yield(i_buf, i_len);
        int* buf = calloc(n, sizeof(int));
        
        for (int j = 0; j < n; ++j) {
            buf[j] = yield(i_buf, i_len);
        }

        int res = min_and_xor_or(buf, n, o_file);
        free(buf);
    }

    fclose(i_file);
    fclose(o_file);

    free(i_buf);

    return 0;
}