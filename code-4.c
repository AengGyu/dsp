#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp_in, *fp_out;

    unsigned char* input = (unsigned char*)malloc(512 * 512);
    unsigned char* output = (unsigned char*)malloc(512 * 512);

    fp_in = fopen("lena.img", "rb");

    if (fp_in == NULL) {
        perror("fopen");
        exit(1);
    }

    fread(input, 1, 512 * 512, fp_in);
    fclose(fp_in);

    int mask[3][3] = {
        { +1, +2, +1 },
        {  0,  0,  0 },
        { -1, -2, -1 }
    };

    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 512; j++) {

            int sum = 0;

            for (int r = -1; r <= 1; r++) {
                for (int c = -1; c <= 1; c++) {

                    int new_i = i + r;
                    int new_j = j + c;

                    if (new_i < 0 || new_i >= 512 || new_j < 0 || new_j >= 512)
                        continue;

                    int new_idx = new_i * 512 + new_j;
                    sum += input[new_idx] * mask[r + 1][c + 1];
                }
            }

            if (sum < 0) sum = -sum;

            if (sum > 255) sum = 255;

            int idx = i * 512 + j;
            output[idx] = (unsigned char)sum;
        }
    }

    fp_out = fopen("output_4", "wb");
    fwrite(output, 1, 512 * 512, fp_out);
    fclose(fp_out);

    free(input);
    free(output);

    return 0;
}
