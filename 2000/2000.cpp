#include <cstdio>

using namespace std;

int n, left, money, ans;

int main() {
    while (scanf("%d", &n) != EOF && n) {
        money = 1;
        left = n;
        ans = 0;
        while (left - money >= 0) {
            left -= money;
            ans += money * money;
            ++money;
        }
        ans += left * money;
        printf("%d %d\n", n, ans);
    }

    return 0;
}