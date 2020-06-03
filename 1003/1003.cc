#include <stdio.h>

int main() {
    float input_length;
    while (true) {
        scanf("%f", &input_length);
        if (input_length == 0) break;
        float curlen = 0.;
        int curcard = 0;
        while (curlen < input_length) {
            curcard += 1;
            curlen += 1.0 / (curcard + 1);
        }
        printf("%d card(s)\n", curcard);
    }
    return 0;
}