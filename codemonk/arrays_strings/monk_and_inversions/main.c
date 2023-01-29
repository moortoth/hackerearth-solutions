#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define LEN 1024

int inv_num(const int **mx, int dim) {
    int res = 0;

    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            for (int p = i; p < dim; ++p) {
                for (int q = j; q < dim; ++q) {

                    if (i == p && j == q) continue;

                    if (mx[i][j] > mx[p][q]) {
                        ++res;
                    }
                }
            }
        }
    }

    return res;
}

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

    if (it.i < n) {
        return it.buf[it.i++];
    }

    return NULL;
}

int main(int argc, char* argv) {
    int* input_buf = calloc(LEN, sizeof(int));
    int res_len;

    FILE *f = fopen("test", "r");

    if (f != NULL) {
        res_len = parse_input(f, input_buf);
    }

    fclose(f);

    int t;
    t = yield(input_buf, res_len);

    int n;
    n = yield(input_buf, res_len);

    free(input_buf);

	return 0;
}