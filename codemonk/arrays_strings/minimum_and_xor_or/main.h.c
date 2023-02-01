#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define LEN 1024 * 1024 * sizeof(char)

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

#define SINGLE_NUM_LEN 8

int min_and_xor_or(int* buf, int len, FILE* out) {
    assert(len >= 2);

    int res = buf[0] ^ buf[1];

    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (res > buf[i] ^ buf[j])
                res = buf[i] ^ buf[j];
        }
    }

    char* b = calloc(SINGLE_NUM_LEN, sizeof(char));
    sprintf(b, "%d\n", res);
    fputs(b, out);

    return res;
}

#define i_file stdin
#define o_file stdout

int main() {
    // FILE *i_file = fopen("test", "r");
    // FILE *o_file = fopen("out", "w+");
    int *i_buf = calloc(LEN, sizeof(int));
    int i_len = parse_input(i_file, i_buf);
    
    int t = yield(i_buf, i_len);
    
    for (int i = 0; i < t; ++i) {
        int n = yield(i_buf, i_len);
        int* buf = calloc(n, sizeof(int));
        
        for (int j = 0; j < n; ++j) {
            buf[j] = yield(i_buf, i_len);
        }

        min_and_xor_or(buf, n, o_file);
        free(buf);
    }

    // fclose(i_file);
    // fclose(o_file);

    free(i_buf);

    return 0;
}