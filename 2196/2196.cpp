#include <cstdio>

using namespace std;

int caldigitsum(int num, int base) {
    int ans = 0;
    while (num > 0) {
        ans += num % base;
        num /= base;
    }
    return ans;
}

int main() {
    int b10;
    for (int i = 1000; i < 10000; ++i) {
        b10 = caldigitsum(i, 10);
        if (caldigitsum(i, 16) == b10 && caldigitsum(i, 12) == b10)
            printf("%d\n", i);
    }
    return 0;
}