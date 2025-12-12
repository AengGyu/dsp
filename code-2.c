#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FILTERSIZE 11

int main() {
    FILE *fp_in, *fp_out;

    unsigned char* input = (unsigned char*)malloc(sizeof(unsigned char) * 512 * 512);
    unsigned char* output = (unsigned char*)malloc(sizeof(unsigned char) * 512 * 512);

    fp_in = fopen("output_1", "rb");
    if (fp_in == NULL) {
        perror("fopen");
        exit(1);
    }

    fread(input, 1, 512 * 512, fp_in);
    fclose(fp_in);

    int half = (FILTERSIZE - 1) / 2;

    for (int n = 0; n < 512 * 512; n++) {
        int sum = 0;

        for (int k = -half; k <= half; k++) {
            int idx = n + k;
            if (idx < 0 || idx >= 512 * 512) {
                continue;
            }

            sum += input[idx];
        }

        output[n] = (unsigned char)(sum / FILTERSIZE);
    }

    fp_out = fopen("output_2", "wb");
    fwrite(output, 1, 512 * 512, fp_out);
    fclose(fp_out);

    free(input);
    free(output);

    return 0;
}