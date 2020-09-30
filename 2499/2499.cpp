#include <cstdio>

using namespace std;

int T, x , y, left, right, mul;

int main() {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d", &x, &y);
        left = right = 0;
        while (!(x == 1 && y == 1)) {
            if (y > x) {
                mul = (y - x) / x;
                right += mul;
                y -= x * mul;
                if (y > x) {
                    ++right;
                    y -= x;
                }
            } else {
                mul = (x - y) / y;
                left += mul;
                x -= y * mul;
                if (x > y) {
                    ++left;
                    x -= y;
                }
            }
        }
        printf("Scenario #%d:\n%d %d\n\n", t, left, right);
    }

    return 0;
}