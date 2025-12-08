#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FILTERSIZE 11

int main() {
    FILE *fp_in, *fp_out;

    unsigned char* input = (unsigned char*)malloc(sizeof(unsigned char) * 512 * 512);
    unsigned char* output = (unsigned char*)malloc(sizeof(unsigned char) * 512 * 512);

    fp_in = fopen("lena.img", "rb");
    if (fp_in == NULL) {
        perror("fopen");
        exit(1);
    }

    fread(input, 1, 512 * 512, fp_in);
    fclose(fp_in);

    for (int y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            int idx = y * 512 + x;
            double noise = 128 * cos((2.0 * M_PI * x) / FILTERSIZE) + 128;

            int temp = input[idx] + noise;

            if (temp < 0)
                temp = 0;
            if (temp > 255)
                temp = 255;

            output[idx] = (unsigned char)temp;
        }
    }

    fp_out = fopen("output_1", "wb");
    fwrite(output, 1, 512 * 512, fp_out);
    fclose(fp_out);

    free(input);
    free(output);

    return 0;
}