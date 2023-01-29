#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define RES_LEN 256

#define SQR(a) (a) * (a)
#define SQRT(a) (u64)sqrt(a)
#define u64 long long

int num_of_packs_i(int num_of_candies) {
    int res = 0;

    for (int i = 1; i <= num_of_candies ; i += 2) {
        int sum = 0;

        char* series = calloc(RES_LEN, sizeof(char));
        strcpy(series, "");

        for (int j = i; sum < num_of_candies; j += 2) {
            sum += j;

            sprintf(series, "%s %d ", series, j);
    
            if (sum == num_of_candies) {
                printf("%s \r\n", series);
                ++res;
            }
        }

        free(series);
    }

    return res;
}

int num_of_packs(u64 sn) {
    int res = sn % 2 == 1 ? 1 : 0;

    for (u64 a1 = 1; a1 < sn / 2; a1+=2) {
        u64 d = SQR(a1 - 1) + 4 * sn;
        u64 sd = SQRT(d);
        if (SQR(sd) != d) continue;
        u64 n2 = sd - a1 + 1;
        if (n2 <= 0) continue;
        if (n2 % 2 == 1) continue;
        ++res;
    }

    return res;
}

int main(int argc, char* argv[]){
    int t1 = num_of_packs(136742223);

    int t2 = num_of_packs_i(136742223);

    return 0;
}