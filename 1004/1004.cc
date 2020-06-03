#include <stdio.h>

int main() {
    float ans = 0, money;
    for (int i = 0; i < 12; ++i) {
        scanf("%f", &money);
        ans += money;
    }
    printf("$%.2f", ans / 12.0);
    return 0;
}