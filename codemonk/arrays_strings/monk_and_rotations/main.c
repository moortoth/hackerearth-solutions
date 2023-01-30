#include <stdio.h>
#include <stdlib.h>
#include "util.h"

#define SINGLE_NUM_LEN 8

void rotate(int *buf, int len, int k, FILE* out) {
    k = k % len;
    char* b = calloc(SINGLE_NUM_LEN, sizeof(char));
    
    for (int i = len - k; i < 2 * len - k; ++i) {
        sprintf(b, "%d ", buf[i % len]);
        fputs(b, out);
    }

    free(b);
}

int main(int argc, char* argv[]) {
    FILE* i_file = fopen("test", "r");
    int* i_buf = calloc(LEN, sizeof(int));
    int i_len = parse_input(i_file, i_buf);
    fclose(i_file);

    int t = yield(i_buf, i_len); // test cases

    FILE* o_file = fopen("out", "w+");

    for (int i = 0; i < t; ++i) {
        int n = yield(i_buf, i_len); // number of elements in array
        int k = yield(i_buf, i_len); // steps of rotation 
        int* i_arr = calloc(n, sizeof(int));

        for (int j = 0; j < n; ++j) {
            i_arr[j] = yield(i_buf, i_len);
        }

        rotate(i_arr, n, k, o_file);
        fputs("\n", o_file);
        free(i_arr);
    }

    free(i_buf);
    fclose(o_file);

    return 0;
}